#ifndef PERMISSIONSERVICE_H
#define PERMISSIONSERVICE_H

#include "database.h"

#include <QDBusContext>
#include <QObject>

class PermissionService : public QObject, public QDBusContext {
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", PERMISSION_SERVICE_NAME)

public:
  explicit PermissionService(QObject *parent = nullptr);

public slots:
  Q_SCRIPTABLE void RequestPermission(const int &permissionEnumCode);
  Q_SCRIPTABLE bool
  CheckApplicationHasPermission(const QString &applicationExecPath,
                                const int &permissionenumCode);

private:
  DataBase m_oDB;
};

#endif // PERMISSIONSERVICE_H
