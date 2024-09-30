#include "timeservice.h"

#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  TimeService timeService;

  if (!QDBusConnection::sessionBus().registerService(TIME_SERVICE_NAME))
    qDebug() << "Unable to register service: "
             << QDBusConnection::sessionBus().lastError().message();

  if (!QDBusConnection::sessionBus().registerObject(
          "/", &timeService, QDBusConnection::ExportAllSlots))
    qDebug() << "Unable to register object: "
             << QDBusConnection::sessionBus().lastError().message();

  qDebug() << "Service running...";

  return a.exec();
}
