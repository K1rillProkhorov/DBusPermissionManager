#include "permissionservice.h"

#include <QCoreApplication>
#include <QDBusConnectionInterface>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  PermissionService permissionService;

  if (!QDBusConnection::sessionBus().registerService(PERMISSION_SERVICE_NAME))
    qWarning() << "Unable to register service: "
               << QDBusConnection::sessionBus().lastError().message();

  if (!QDBusConnection::sessionBus().registerObject(
          "/", &permissionService, QDBusConnection::ExportAllSlots))
    qWarning() << "Unable to register object: "
               << QDBusConnection::sessionBus().lastError().message();

  qDebug("Service running...");

  return a.exec();
}
