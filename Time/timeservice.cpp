#include "timeservice.h"
#include "../interfaces.h"

#include <QDBusAbstractInterface>
#include <QDateTime>
#include <QFile>
#include <QList>
#include <QVariant>

TimeService::TimeService(QObject *parent) : QObject(parent) {}

quint64 TimeService::GetSystemTime() const {
  const auto client = message().service();

  const auto *interface = QDBusConnection::sessionBus().interface();
  const uint PID = interface->servicePid(client);
  if (PID == 0)
    sendErrorReply(QDBusError::UnknownObject, "Unable to get PID");

  QString applicationExecPath = QString("/proc/%1/exe").arg(PID);
  applicationExecPath = QFile::symLinkTarget(applicationExecPath);

  PermissionServiceInterface permissionService;
  const auto result =
      permissionService.call("CheckApplicationHasPermission",
                             applicationExecPath, ePermissions::SystemTime);

  if (result.type() == QDBusMessage::ErrorMessage)
    sendErrorReply(QDBusError::Failed, result.errorMessage());

  QList<QVariant> args = result.arguments();
  bool status = args.isEmpty() ? false : args.first().toBool();
  if (!status)
    sendErrorReply(QDBusError::AccessDenied, "Unauthorized access");

  return QDateTime::currentMSecsSinceEpoch();
}
