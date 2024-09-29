#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

enum eStatus
{
    Error = -1,
    Failure = 0,
    Success = 1
};

enum ePermissions { SystemTime = 0 };

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
