#include "timeservice.h"

#include <QDBusConnectionInterface>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  TimeService timeService;

  if (!QDBusConnection::sessionBus().registerService(TIME_SERVICE_NAME))
    qWarning() << "Unable to register service: "
             << QDBusConnection::sessionBus().lastError().message();

  if (!QDBusConnection::sessionBus().registerObject(
          "/", &timeService, QDBusConnection::ExportAllSlots))
    qWarning() << "Unable to register object: "
             << QDBusConnection::sessionBus().lastError().message();

  qDebug() << "Service running...";

  return a.exec();
}
