#include "../interfaces.h"

#include <QDateTime>
#include <QDebug>

int main() {
  TimeServiceInterface timeService;
  if (!timeService.isValid()) {
    qWarning() << "Unable to connect time service";
    return -1;
  }

  PermissionServiceInterface permissionService;
  if (!permissionService.isValid()) {
    qWarning() << "Unable to connect parmission service";
    return -1;
  }

  QDateTime dateTime;
  const auto reply1 = timeService.call("GetSystemTime");
  if (reply1.type() == QDBusMessage::ErrorMessage) {
    if (timeService.lastError().type() == QDBusError::AccessDenied)
      qDebug() << "Access denied, request permission";

    const auto reply2 =
        permissionService.call("RequestPermission", ePermissions::SystemTime);

    if (reply2.type() != QDBusMessage::ErrorMessage) {
      const auto reply3 = timeService.call("GetSystemTime");
      QList<QVariant> resultList = reply3.arguments();
      dateTime =
          QDateTime::fromMSecsSinceEpoch(resultList.first().toULongLong());
    } else
      qDebug() << "Failed to request permission";
  } else {
    QList<QVariant> resultList = reply1.arguments();
    dateTime = QDateTime::fromMSecsSinceEpoch(resultList.first().toULongLong());
  }

  if (dateTime.isNull()) {
    qWarning() << "Unable to get system time";
    return -1;
  } else
    qDebug() << "Date: " << dateTime.toString("dd-MM-yyyy HH:mm:ss");

  return 0;
}
