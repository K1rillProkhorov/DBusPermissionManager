#include "permissionservice.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto database = std::make_unique<DataBase>(DATABASE_NAME);
    PermissionService permissionService(std::move(database));

    if (!QDBusConnection::sessionBus().registerService(PERMISSION_SERVICE_NAME))
        qDebug() << "Unable to register service: " << QDBusConnection::sessionBus().lastError().message();

    if (!QDBusConnection::sessionBus().registerObject("/", &permissionService, QDBusConnection::ExportAllSlots))
        qDebug() << "Unable to register object: " << QDBusConnection::sessionBus().lastError().message();

    qDebug("Service running...");

    return a.exec();
}
