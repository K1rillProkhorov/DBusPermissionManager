#include "permissionservice.h"

#include <QDebug>

PermissionService::PermissionService(std::unique_ptr<DataBase> db,
                                     QObject *parent)
    : QObject(parent), m_oDB(std::move(db)) {}

void PermissionService::RequestPermission(const int &permissionEnumCode) {
  const auto client = message().service();
  const auto *interface = QDBusConnection::sessionBus().interface();
  const uint PID = interface->servicePid(client);
  if (PID == 0)
    sendErrorReply(QDBusError::UnknownObject, "Unable to get PID");

  QString applicationExecPath = QString("/proc/%1/exe").arg(PID);
  applicationExecPath = QFile::symLinkTarget(applicationExecPath);

  if (applicationExecPath.isEmpty())
    sendErrorReply(QDBusError::UnknownObject, "Unable to get executable path");
  else if (!m_oDB->AddPermission(applicationExecPath, permissionEnumCode))
    sendErrorReply(QDBusError::Failed, "Unable to add permission in database");
  else
    qDebug() << "Request permission: " << QString::number(permissionEnumCode)
             << "from: " << applicationExecPath;
}

bool PermissionService::CheckApplicationHasPermission(
    const QString &applicationExecPath, const int &permissionenumCode) {
  eStatus status =
      m_oDB->CheckPermission(applicationExecPath, permissionenumCode);
  if (status == eStatus::Error)
    sendErrorReply(QDBusError::Failed, "Failure permission validating");

  return status == eStatus::Success;
}
