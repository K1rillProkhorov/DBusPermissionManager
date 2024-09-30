#ifndef INTERFACES_H
#define INTERFACES_H

#include "definitions.h"

#include <QDBusAbstractInterface>

class PermissionServiceInterface : public QDBusAbstractInterface {
  Q_OBJECT

public:
  explicit PermissionServiceInterface(QObject *parent = nullptr)
      : QDBusAbstractInterface(PERMISSION_SERVICE_NAME, "/",
                               PERMISSION_SERVICE_NAME,
                               QDBusConnection::sessionBus(), parent) {}
};

class TimeServiceInterface : public QDBusAbstractInterface {
  Q_OBJECT

public:
  explicit TimeServiceInterface(QObject *parent = nullptr)
      : QDBusAbstractInterface(TIME_SERVICE_NAME, "/", TIME_SERVICE_NAME,
                               QDBusConnection::sessionBus(), parent) {}
};

#endif // INTERFACES_H
