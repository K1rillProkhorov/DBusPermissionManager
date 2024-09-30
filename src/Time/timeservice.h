#ifndef TIMESERVICE_H
#define TIMESERVICE_H

#include "../definitions.h"

#include <QDBusContext>
#include <QObject>

class TimeService : public QObject, public QDBusContext {
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", TIME_SERVICE_NAME)

public:
  explicit TimeService(QObject *parent = nullptr);

public slots:
  Q_SCRIPTABLE quint64 GetSystemTime() const;
};

#endif // TIMESERVICE_H
