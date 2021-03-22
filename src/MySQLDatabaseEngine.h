/*
 * Copyright (c) 2021 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MYSQL_DATABASE_ENGINE_H
#define MYSQL_DATABASE_ENGINE_H

#include <QObject>
#include <QSqlDatabase>

class MySQLDatabaseEngine : public QObject
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(int port
               READ port
               WRITE setPort
               NOTIFY portChanged)
    Q_PROPERTY(QString hostName
               READ hostName
               WRITE setHostName
               NOTIFY hostNameChanged)
    Q_PROPERTY(QString userName
               READ userName
               WRITE setUserName
               NOTIFY userNameChanged)
    Q_PROPERTY(QString password
               READ password
               WRITE setPassword
               NOTIFY passwordChanged)
    Q_PROPERTY(QString databaseName
               READ databaseName
               WRITE setDatabaseName
               NOTIFY databaseNameChanged)
    Q_PROPERTY(bool isOpen
               READ isOpen
               NOTIFY openChanged)
    // clang-format on

signals:
    void openChanged();
    void portChanged();
    void hostNameChanged();
    void userNameChanged();
    void passwordChanged();
    void databaseNameChanged();

public:
    static MySQLDatabaseEngine *getInstance();

    QSqlDatabase *database();

    int port() const;
    bool isOpen() const;
    QString hostName() const;
    QString userName() const;
    QString password() const;
    QString databaseName() const;

public slots:
    void open();
    void close();
    void setPort(const int port);
    void setHostName(const QString &hostName);
    void setUserName(const QString &userName);
    void setPassword(const QString &password);
    void setDatabaseName(const QString &databaseName);

private:
    MySQLDatabaseEngine();
    ~MySQLDatabaseEngine();

private:
    QSqlDatabase m_database;
};

#endif
