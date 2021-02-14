#include "repository.h"
#include "convertorservice.h"
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonDocument>
Repository::Repository()
{

}


void Repository::createBook(QString book_id, QString title, QString subject, QString publisher,
                            QString language, QString author, QString translator, QString edition)
{
    QSqlQuery q;
    query = "INSERT INTO book VALUES (:book_id, :title, :subject, :publisher, :language,"
            " :author, :translator, :edition);";
    qDebug() << query << endl;
    q.prepare(query);
    q.bindValue(":book_id", book_id);
    q.bindValue(":title", title);
    q.bindValue(":subject", subject);
    q.bindValue(":publisher", publisher);
    q.bindValue(":language", language);
    q.bindValue(":translator", translator);
    q.bindValue(":edition", edition);
    q.bindValue(":author", author);
    q.exec();
    qDebug() << q.lastError() << endl;
}


void Repository::updateBook(QString book_id, QString title, QString subject, QString publisher,
                            QString language, QString author, QString translator, QString edition)
{
    QSqlQuery q;
    query = "UPDATE  book SET title = :title, subject = :subject, publisher = :publisher, language = :language, author = :author, translator = :translator, edition = :edition WHERE book_id = :book_id;";
    qDebug() << query << endl;
    q.prepare(query);
    q.bindValue(":book_id", book_id.toInt());
    q.bindValue(":title", title);
    q.bindValue(":subject", subject);
    q.bindValue(":publisher", publisher);
    q.bindValue(":language", language);
    q.bindValue(":translator", translator);
    q.bindValue(":edition", edition);
    q.bindValue(":author", author);
    q.exec();
    qDebug() << q.lastError() << endl;
}


void Repository::deleteBook(QString book_id)
{
    QSqlQuery q;
    query="DELETE FROM book WHERE book_id=:book_id";
    q.prepare(query);
    q.bindValue(":book_id",book_id);
    q.exec();
    q.clear();
}


QJsonDocument Repository::readBooksById(QString book_id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model=new QSqlQueryModel();
    QString query;
    query = "SELECT * FROM book WHERE book_id LIKE '%";
    query += book_id;
    query += "%';";
    model->setQuery(query);
    return ConvertorService::toJson(model);
}

QJsonDocument Repository::readBooksByTitle(QString title)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model=new QSqlQueryModel();
    QString query;
    query = "SELECT * FROM book WHERE title LIKE '%";
    query += title;
    query += "%';";
    model->setQuery(query);
    return ConvertorService::toJson(model);
}


QJsonDocument Repository::readBooksBySubject(QString subject)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model=new QSqlQueryModel();
    QString query;
    query = "SELECT * FROM book WHERE subject LIKE '%";
    query += subject;
    query += "%';";
    model->setQuery(query);
    return ConvertorService::toJson(model);
}


void Repository::createBookItem(QString book_id, QString status, QString barcode) {
    QSqlQuery q;
    query = "INSERT INTO book_item(book_id, status, barcode)"
            "VALUES (:book_id, :status, :barcode)";
    q.prepare(query);
    q.bindValue(":book_id", book_id);
    q.bindValue(":status", status);
    q.bindValue(":barcode", barcode);
    q.exec();
}


void Repository::updateBookItem(QString book_item_id, QString status)
{
    QSqlQuery q;
    qDebug() << book_item_id << " " << status << endl;
    query = "UPDATE  book_item SET status = :status"
            " WHERE book_item_id = :book_item_id;";
    qDebug() << query << endl;
    q.prepare(query);
    q.bindValue(":book_item_id", book_item_id);
    q.bindValue(":status", status);
    q.exec();
}


void Repository::deleteBookItem(QString book_item_id)
{
    QSqlQuery q;
    query="DELETE FROM book_item WHERE book_item_id=:book_item_id";
    q.prepare(query);
    q.bindValue(":book_item_id",book_item_id);
    q.exec();
    q.clear();
}

void Repository::addPenalty(QString account_id, QString penalty) {
    int penal;
    QSqlQuery q;
    qDebug() << penalty << " " << account_id << endl;
    query="select * from member WHERE account_id=";
    query+=account_id;
    q.exec(query);
    while (q.next()) {

        QString penalty_member=q.value("penalty").toString();
        penal=penalty_member.toInt()+penalty.toInt();
    }
    query="update member set penalty=:penlat where account_id=:id_account";
    qDebug()<<"addad"<<penal;
    q.prepare(query);
    q.bindValue(":penlat", QString::number(penal));
    q.bindValue(":id_account", account_id);

    q.exec();
    q.clear();
    qDebug() << q.lastError() << endl;

}

QJsonDocument Repository::readBookItem(QString book_item_id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;

    model=new QSqlQueryModel();
    QString query;
    query="SELECT * from book_item WHERE book_item_id = ";
    query+= book_item_id;
    model->setQuery(query);
    return ConvertorService::toJson(model);

}

QJsonDocument Repository::readAllBookItem(QString book_id){
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    model=new QSqlQueryModel();
    QString query;
    query="SELECT * from book_item WHERE book_id = ";
    query+= book_id;
    model->setQuery(query);
    return ConvertorService::toJson(model);
}

void Repository::add_payment(QString account_id, QString payment)
{
    int penal;
    QSqlQuery q;
    query="select * from member WHERE account_id=";
    query+=account_id;
    q.exec(query);
    while (q.next()) {

        QString penalty_member=q.value("penalty").toString();
        penal=penalty_member.toInt()-payment.toInt();
    }
    query="update member set penalty=:penlat where account_id=:id_account";
    qDebug()<<penal;
    q.prepare(query);
    q.bindValue(":penlat", QString::number(penal));
    q.bindValue(":id_account", account_id);

    q.exec();
    q.clear();
    qDebug() << q.lastError() << endl;
}

QJsonDocument Repository::readPenalty(QString account_id)
{
    QString penalty;
    QSqlQuery q;
    query="select * from member WHERE account_id=";
    query+=account_id;
    q.exec(query);
    while (q.next()) {

        penalty=q.value("penalty").toString();

    }

    QJsonObject jsonObject;


        jsonObject.insert("penalty",QJsonValue::fromVariant(penalty));


    QJsonDocument returnDoc(jsonObject);

    return returnDoc;




}



void Repository::createMember(QString member_id, QString card_number, QString account_id,
                              QString card_expire_date, QString name, QString email,
                              QString birthday, QString address, QString phone_number) {

    QSqlQuery q;

    query= "insert into account (account_id, name,email,birthday,address,phone_number) "
           "values (:account_id,:name,:email,:birthday,:address,:phone_number)";

    q.prepare(query);
    q.bindValue(":account_id", account_id);
    q.bindValue(":name", name);
    q.bindValue(":email",email);
    q.bindValue(":birthday", birthday);
    q.bindValue(":address", address);
    q.bindValue(":phone_number", phone_number);
    q.exec();
    q.clear();
    query = "INSERT INTO member(member_id, card_number, account_id, card_expire_date, penalty) "
            "VALUES(:member_id, :card_number, :account_id, :card_expire_date, '0');";

    q.prepare(query);
    q.bindValue(":member_id", member_id);
    q.bindValue(":card_number", card_number);
    q.bindValue(":account_id", account_id);
    q.bindValue(":card_expire_date", card_expire_date);
    q.exec();
    q.clear();
    //query
}

void Repository::renewMember(QString account_id, QString card_expire_date) {

    QSqlQuery q;
    query="UPDATE member set card_expire_date = :card_expire_date WHERE account_id=:id_account";
    q.prepare(query);
    q.bindValue(":card_expire_date", card_expire_date);
    q.bindValue(":id_account", account_id);
    q.exec();
    q.clear();
}

void Repository::deleteMember(QString account_id)
 {

     QSqlQuery q;


     query="delete from account where account_id = :account_id;";

     q.prepare(query);
     q.bindValue(":account_id",account_id);
     q.exec();
     q.clear();
     query="delete from member where account_id=:account_d";
     q.prepare(query);
     q.bindValue(":account_d",account_id);
     q.exec();
     q.clear();

 }

void Repository::updateMember(QString account_id, QString email,
                              QString address, QString phone_number,
                              QString card_number)
 {
     qDebug() << account_id << endl;
     QSqlQuery q;
     query= "update account set  email=:email,address=:address,phone_number=:phone_number where account_id=:id_account;";
     q.prepare(query);
     q.bindValue(":email",email);
     q.bindValue(":address",address);
     q.bindValue(":phone_number",phone_number);
     q.bindValue(":id_account",account_id);
     q.exec();
     q.clear();



     query="  update member set card_number=:card_n where account_id=:id_account;";
     q.prepare(query);
     q.bindValue(":card_n",card_number);
     q.bindValue(":id_account",account_id);
     q.exec();
     q.clear();

 }


QJsonDocument Repository::readMembersByAccountId(QString account_id)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery q;

    model=new QSqlQueryModel();
    QString query;
    query="select * from account join member on member.account_id =";
    query+=account_id;
    query+=" and account.account_id=";
    query+=account_id;
    qDebug()<<query;
    model->setQuery(query);
    return ConvertorService::toJson(model);
}

QJsonDocument Repository::readMembersByName(QString name)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery q;
    QSqlQuery member;
    model=new QSqlQueryModel();
    QString query;
    query="SELECT * FROM account JOIN member on account.name like '%";
    query+=name;
    query+="%'";
    int i=0;
    q.exec(query);
    query+=" where ";
    while( q.next())
    {
        if (i>0)
            query+=" or ";
        QString account_id= q.value("account_id").toString();
        QString member_id= q.value("account_id").toString();
        query+="  (member.account_id=";
        query+=member_id;
        query+=" and account.account_id=";
        query+=account_id;
        query+=")";

        i++;
    }
    model->setQuery(query);
    return ConvertorService::toJson(model);
    QJsonDocument d;
    return d;
}

QJsonDocument Repository::readMembersByMemberId(QString member_id)
{
    QString account_id;
    QSqlQuery q;
    query = "SELECT * FROM member WHERE member_id =";
    query += member_id;
    q.exec(query);
    while(q.next())
    {
         account_id = q.value("account_id").toString();
    }
    q.clear();
    return readMembersByAccountId(account_id);
}

void Repository::createLibrarian(QString account_id,QString name,QString email,
                                 QString birthday,QString address,QString phone_number,
                                 QString librarian_id,QString password,QString username ) {

    QSqlQuery q;

    query= "insert into account (account_id,name,email,birthday,address,phone_number) "
           "values (:account_id,:name,:email,:birthday,:address,:phone_number)";

    q.prepare(query);
    q.bindValue(":account_id",account_id);
    q.bindValue(":name",name);
    q.bindValue(":email",email);
    q.bindValue(":birthday",birthday);
    q.bindValue(":address",address);
    q.bindValue(":phone_number",phone_number);
    q.exec();
    q.clear();
    query="  insert into librarian (librarian_id,account_id,password,username) values "
          "(:librarian_id,:account_id,:password,:username)";

    q.prepare(query);
    q.bindValue(":librarian_id",librarian_id);
    q.bindValue(":account_id",account_id);
    q.bindValue(":password",password);
    q.bindValue(":username",username);
    q.exec();

    qDebug()<<"the librarian added";
    q.clear();

}



void Repository::updateLibrarian(QString account_id, QString name, QString email, QString address,
                                 QString phone_number, QString password)
{

    QSqlQuery q;


    query= "update account set name=:name,email=:email,address=:address,phone_number=:phone_number where account_id=:id_account";
    q.prepare(query);
    q.bindValue(":name",name);
    q.bindValue(":email",email);
    q.bindValue(":address",address);
    q.bindValue(":phone_number",phone_number);
    q.bindValue(":id_account",account_id);
    q.exec();
    q.clear();

    query="update librarian set "
          "password=:password where account_id=:id_account";
    q.prepare(query);
   // q.bindValue(":librarian_id",librarian_id);
    //q.bindValue(":account_id",account_id);
    q.bindValue(":password",password);
    q.bindValue(":id_account",account_id);
    q.exec();
    q.clear();
   qDebug()<<account_id<<  name<< email<< address<< phone_number<< password;

}


QJsonDocument Repository::readLibrarian(QString account_id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    model = new QSqlQueryModel();
    QString query;
    query = "SELECT * FROM account JOIN librarian ON librarian.account_id = ";
    query += account_id;
    query += " AND account.account_id = ";
    query += account_id;
    qDebug() << query;
    model->setQuery(query);
    return ConvertorService::toJson(model);
}



void Repository::deleteLibrarian(QString librarian_id)
{
    QSqlQuery q;
    query="DELETE FROM librarian WHERE librarian_id = :librarian_id";
    q.prepare(query);
    q.bindValue(":librarian_id",librarian_id);
    q.exec();
    q.clear();
}


void Repository::createLend(QString book_item_id, QString member_id,
                            QString renew_times, QString loan_date, QString return_date)
{
    QSqlQuery q;
    query="INSERT INTO lend(book_item_id,member_id,renew_times,loan_date,return_date) VALUES(:book_item_id,:member_id,:renew_times,:loan_date,:return_date)";
    q.prepare(query);
    q.bindValue(":book_item_id",book_item_id);
    q.bindValue(":member_id",member_id);
    q.bindValue(":renew_times",renew_times);
    q.bindValue(":loan_date",loan_date);
    q.bindValue(":return_date",return_date);
    q.exec();
    q.clear();
}


void Repository::deleteLend(QString lend_id)
{
    QSqlQuery q;
    query="delete from lend where lend_id=:lend_id";
    q.prepare(query);
    q.bindValue(":lend_id",lend_id);
    q.exec();
    q.clear();
}


void Repository::updateLend(QString lend_id, QString renew_times, QString return_date)
{
    QSqlQuery q;
    qDebug() << lend_id << endl;
    query="UPDATE lend "
          "SET renew_times = :renew_times, return_date = :return_date "
          "WHERE lend_id = :lend_id;";
    q.prepare(query);
    q.bindValue(":lend_id",lend_id);
    q.bindValue(":renew_times",renew_times);
    q.bindValue(":return_date",return_date);
    q.exec();
    q.clear();
}


QJsonDocument Repository::readLend(QString lend_id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    model = new QSqlQueryModel();
    QString query;
    query = "select * from lend where lend_id=";
    query += lend_id;
    model->setQuery(query);
    return ConvertorService::toJson(model);
}


QJsonDocument Repository::readLendByMember(QString member_id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    model = new QSqlQueryModel();
    QString query;
    query = "select * from lend where member_id = ";
    query += member_id;
    model->setQuery(query);
    return ConvertorService::toJson(model);
}

QJsonDocument Repository::readLendByBook(QString book_item_id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;
    model = new QSqlQueryModel();
    QString query;
    query = "select * from lend where book_item_id = ";
    query += book_item_id;
    model->setQuery(query);
    return ConvertorService::toJson(model);
}

void Repository::createTransactionItem(QString member_id, QString payment,
                                       QString payment_date)
{
    QSqlQuery q;
    query="INSERT INTO transaction_item(member_id,payment,payment_date)"
          "VALUES (:mem, :pay, :pay_date)";
    q.prepare(query);

    q.bindValue(":mem",member_id);
    q.bindValue(":pay",payment);
    q.bindValue(":pay_date",payment_date);
    q.exec();
    q.clear();
}


void Repository::deleteTransactionItem(QString transaction_id)
{
    QSqlQuery q;
    query="delete from transaction_item where  transaction_id =:id_transaction ";
    q.prepare(query);
    q.bindValue(":id_transaction",transaction_id);
    q.exec();
    q.clear();
}


void Repository::updateTransactionItem(QString transaction_id, QString member_id, QString payment,
                                       QString payment_id)
{
    QSqlQuery q;

    query="UPDATE transaction_item "
          "SET transaction_id = :transaction_id, member_id = :member_id,"
          " payment = :payment, payment_date = :payment_date "
          "WHERE transaction_id = :id_transaction";
    q.prepare(query);

    q.bindValue(":transaction_id", transaction_id);
    q.bindValue(":member_id", member_id);
    q.bindValue(":payment", payment);
    q.bindValue(":payment_date", payment_id);
    q.bindValue(":id_transaction", transaction_id);
    q.exec();
    q.clear();
}

QJsonDocument Repository::readTransactionId(QString transaction_id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;

    model=new QSqlQueryModel();
    QString query;
    query = "SELECT * FROM transaction_item WHERE transaction_id = ";
    query += transaction_id;
    model->setQuery(query);
    return ConvertorService::toJson(model);

}

QJsonDocument Repository::readTransactionByMember(QString member_id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q;

    model=new QSqlQueryModel();
    QString query;
    query = "SELECT * FROM transaction_item WHERE member_id = ";
    query += member_id;
    model->setQuery(query);
    return ConvertorService::toJson(model);

}

Repository::~Repository() {

}
