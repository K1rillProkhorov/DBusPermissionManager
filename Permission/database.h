#ifndef DATABASE_H
#define DATABASE_H

#include "../definitions.h"

#include <QtSql>

class DataBase
{
public:
    explicit DataBase(const QString& dbName);
    virtual ~DataBase() noexcept;
    DataBase(const DataBase& other) = default;
    DataBase(const DataBase&& other) noexcept;
    DataBase& operator=(const DataBase& other) = default;
    DataBase& operator=(DataBase&& other) noexcept;

    bool AddPermission(const QString& path, const int& permission);
    eStatus CheckPermission(const QString& path, const int& permission);

private:
    QSqlDatabase m_oDB;
};

#endif // DATABASE_H
