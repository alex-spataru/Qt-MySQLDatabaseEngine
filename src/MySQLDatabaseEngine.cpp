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

#include "MySQLDatabaseEngine.h"

#include <QSqlError>
#include <QMessageBox>
#include <QApplication>

/*
 * NOTE: most of the Doxygen documentation was copy-pasted from:
 *       https://doc.qt.io/qt-5/qsqldatabase.html
 */

/*
 * Register the MySQL static plugin
 */
#ifdef MYSQLDATABASE_ENGINE_STATIC
#    include <QtPlugin>
Q_IMPORT_PLUGIN(QMYSQLDriverPlugin)
#endif

/**
 * Pointer to the singleton instance of the class
 */
static MySQLDatabaseEngine *INSTANCE = nullptr;

/**
 * Shows a macOS-like message box with the given properties
 */
static int ShowMessageBox(QString text, QString informativeText)
{
    // Create message box & set options
    QMessageBox box;
    box.setWindowTitle(qAppName());
    box.setIcon(QMessageBox::Warning);
    box.setText("<h3>" + text + "</h3>");
    box.setStandardButtons(QMessageBox::Ok);
    box.setInformativeText(informativeText);

    // Show message box & return user decision to caller
    return box.exec();
}

/**
 * Constructor function
 */
MySQLDatabaseEngine::MySQLDatabaseEngine()
{
    m_database = QSqlDatabase::addDatabase("QMYSQL");
    m_database.setHostName("localhost");
    m_database.setPort(3306);
}

/**
 * Destructor function
 */
MySQLDatabaseEngine::~MySQLDatabaseEngine()
{
    close();
}

/**
 * Returns the only instance of the class
 */
MySQLDatabaseEngine *MySQLDatabaseEngine::getInstance()
{
    if (!INSTANCE)
        INSTANCE = new MySQLDatabaseEngine;

    return INSTANCE;
}

/**
 * Returns a pointer to the database handler class
 */
QSqlDatabase *MySQLDatabaseEngine::database()
{
    return &m_database;
}

/**
 * Returns the connection's port number. The value is undefined if the port number has not
 * been set.
 */
int MySQLDatabaseEngine::port() const
{
    return m_database.port();
}

/**
 * Returns true if the database connection is currently open; otherwise returns false.
 */
bool MySQLDatabaseEngine::isOpen() const
{
    return m_database.isOpen();
}

/**
 * Returns the connection's host name; it may be empty.
 */
QString MySQLDatabaseEngine::hostName() const
{
    return m_database.hostName();
}

/**
 * Returns the connection's user name; it may be empty.
 */
QString MySQLDatabaseEngine::userName() const
{
    return m_database.userName();
}

/**
 * Returns the connection's password. An empty string will be returned if the password was
 * not set with setPassword(), and if the password was given in the open() call, or if no
 * password was used.
 */
QString MySQLDatabaseEngine::password() const
{
    return m_database.password();
}

/**
 * Returns the connection's database name, which may be empty.
 *
 * @note The database name is not the connection name.
 */
QString MySQLDatabaseEngine::databaseName() const
{
    return m_database.databaseName();
}

/**
 * Opens the database connection using the current connection values. On failure, a
 * messagebox with error description shall be shown to the user.
 */
void MySQLDatabaseEngine::open()
{
    if (!m_database.open(userName(), password()))
        ShowMessageBox(tr("Error establishing database connection"),
                       m_database.lastError().text());

    emit openChanged();
}

/**
 * Closes the database connection, freeing any resources acquired, and invalidating any
 * existing QSqlQuery objects that are used with the database.
 */
void MySQLDatabaseEngine::close()
{
    m_database.close();
    emit openChanged();
}

/**
 * Sets the connection's port number to port. To have effect, the port number must be set
 * before the connection is opened. Alternatively, you can close() the connection, set the
 * port number, and call open() again.
 */
void MySQLDatabaseEngine::setPort(const int port)
{
    m_database.setPort(port);
    emit portChanged();
}

/**
 * Sets the connection's host name to host. To have effect, the host name must be set
 * before the connection is opened. Alternatively, you can close() the connection, set the
 * host name, and call open() again.
 */
void MySQLDatabaseEngine::setHostName(const QString &hostName)
{
    m_database.setHostName(hostName);
    emit hostNameChanged();
}

/**
 * Sets the connection's user name to name. To have effect, the user name must be set
 * before the connection is opened. Alternatively, you can close() the connection, set the
 * user name, and call open() again.
 */
void MySQLDatabaseEngine::setUserName(const QString &userName)
{
    m_database.setUserName(userName);
    emit userNameChanged();
}

/**
 * Sets the connection's password to password. To have effect, the password must be set
 * before the connection is opened. Alternatively, you can close() the connection, set the
 * password, and call open() again.
 *
 * @warning This function stores the password in plain text within Qt. Use the open() call
 *          from the database() that takes a password as parameter to avoid this behavior.
 */
void MySQLDatabaseEngine::setPassword(const QString &password)
{
    m_database.setPassword(password);
    emit passwordChanged();
}

/**
 * Sets the connection's database name to name. To have effect, the database name must be
 * set before the connection is opened. Alternatively, you can close() the connection, set
 * the database name, and call open() again.
 */
void MySQLDatabaseEngine::setDatabaseName(const QString &databaseName)
{
    m_database.setDatabaseName(databaseName);
    emit databaseNameChanged();
}
