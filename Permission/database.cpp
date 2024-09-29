#include "database.h"
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <type_traits>

DataBase::DataBase(const QString& dbName) :
    m_oDB(QSqlDatabase::addDatabase("QSQLITE"))
{
    m_oDB.setDatabaseName(dbName);

    if (m_oDB.open())
    {
        qDebug("Database open");

        QSqlQuery query;
        if (!query.exec("CREATE TABLE IF NOT EXISTS permissions (Path TEXT, "
                        "Permission INTEGER, PRIMARY KEY(Path, Permission))"))
            qDebug() << "Unable to create table: " << query.lastError().text();
    }
    else
        qDebug() << "Unable to open database: " << m_oDB.lastError().text();
}

DataBase::~DataBase() noexcept
{
    if (m_oDB.isOpen()) m_oDB.close();
}

DataBase::DataBase(const DataBase &&other) noexcept
{
    *this = other;
}

DataBase& DataBase::operator=(DataBase&& other) noexcept
{
    if (&other == this)
        return *this;

    m_oDB = std::move(other.m_oDB);
    other.m_oDB.close();

    return *this;
}

bool DataBase::AddPermission(const QString &path, const int &permission)
{
    QSqlQuery query;
    if (!query.exec("INSERT INTO permissions (Path, Permission) VALUES('" +
                    path + "', " + QString::number(permission) + ")"))
    {
        qDebug() << "Unable to save permission: " << query.lastError().text();
        return false;
    }

    return true;
}

eStatus DataBase::CheckPermission(const QString& path, const int& permission)
{
    eStatus status = eStatus::Success;
    QSqlQuery query;
    if (!query.exec("SELECT * FROM Permissions WHERE Path = '" +
                    path + "' AND Permission = " + QString::number(permission)))
    {
        qDebug() << "Unable to validate permission: " << query.lastError().text();
        status = eStatus::Error;
    }
    else if (!query.next())
    {
        qDebug("No Permission");
        status = eStatus::Failure;
    }

    return status;
}
