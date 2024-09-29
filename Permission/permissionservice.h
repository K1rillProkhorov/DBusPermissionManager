#ifndef PERMISSIONSERVICE_H
#define PERMISSIONSERVICE_H

#include "database.h"

#include <QObject>
#include <QDBusConnectionInterface>
#include <QDBusContext>
#include <QFile>
#include <memory>

class PermissionService : public QObject, public QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.system.permissions")

public:
    explicit PermissionService(std::unique_ptr<DataBase> db,
                               QObject *parent = nullptr);

public slots:
    Q_SCRIPTABLE void RequestPermission(const int& permissionEnumCode) const;
    Q_SCRIPTABLE bool CheckApplicationHasPermission(const QString& applicationExecPath,
                                                    const int& permissionenumCode) const;

private:
    std::unique_ptr<DataBase> m_oDB;
};

#endif // PERMISSIONSERVICE_H
