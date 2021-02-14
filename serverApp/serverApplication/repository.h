#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QDebug>
#include <QSqlQueryModel>
#include <QJsonDocument>

class Repository
{
public:
    Repository();
    void createLend(QString book_item_id, QString member_id, QString renew_times,
                    QString loan_date, QString return_date);
    void deleteLend(QString lend_id);
    void updateLend(QString lend_id, QString renew_times, QString return_date);
    QJsonDocument readLend(QString lend_id);
    QJsonDocument readLendByMember(QString member_id);
    QJsonDocument readLendByBook(QString book_item_id);

    void createTransactionItem(QString member_id, QString payment, QString payment_date);
    void deleteTransactionItem(QString transaction_id);
    void updateTransactionItem(QString transaction_id,QString member_id,QString payment,
                               QString payment_id);
    QJsonDocument readTransactionId(QString transaction_id);
    QJsonDocument readTransactionByMember(QString Member_id);

    void createLibrarian(QString account_id,QString name,QString email,
                                     QString birthday,QString address,QString phone_number,
                                     QString librarian_id,QString password,QString username );
    void updateLibrarian(QString account_id, QString name, QString email, QString address,
                                     QString phone_number, QString password);
    void deleteLibrarian(QString account_id);
    QJsonDocument readLibrarian(QString account_id);

    void createMember(QString member_id, QString card_number, QString account_id,
                      QString card_expire_date, QString name, QString email, QString birthday,
                      QString address, QString phone_number);
    void updateMember(QString account_id, QString email, QString address,
                                  QString phone_number, QString card_number);
    void renewMember(QString account_id, QString card_expire_date);
    void deleteMember(QString account_id);
    void addPenalty(QString account_id, QString penalty);
    QJsonDocument readMembersByAccountId(QString account_id);
    QJsonDocument readMembersByName(QString name);
    QJsonDocument readMembersByMemberId(QString member_id);


    void createBook(QString book_id, QString title, QString subject, QString publisher,
                    QString language, QString author, QString translator, QString edition);
    void updateBook(QString book_id, QString title, QString subject, QString publisher,
                        QString language, QString author, QString translator, QString edition);
    void deleteBook(QString book_id);
    QJsonDocument readBooksBySubject(QString subject);
    QJsonDocument readBooksByTitle(QString title);
    QJsonDocument readBooksById(QString book_id);

    void createBookItem(QString book_id, QString status, QString barcode);
    void updateBookItem(QString barcode, QString status);
    void deleteBookItem(QString book_item_id);
    QJsonDocument readBookItem(QString book_item_id);
    QJsonDocument readAllBookItem(QString book_id);


    void add_payment(QString account_id,QString payment);

    QJsonDocument readPenalty(QString account);


    ~Repository();
private:

protected:
    QString query;
};

#endif // REPOSITORY_H
