#ifndef DLLRESTAPIENGINE_H
#define DLLRESTAPIENGINE_H
#include <QtNetwork>
#include <qnetwork.h>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonDocument>
#include <QDebug>
#include <QString>
#include <iostream>

using namespace std;
class DLLRestAPIEngine : public QObject
{
    Q_OBJECT
public:
    DLLRestAPIEngine(QObject*parent = nullptr);
    ~DLLRestAPIEngine();
    void Login(QString, QString);

    void GetLogs();
    void CreateLog(double);
    void updateBalance(int action, double amount, int type);            //1 for deposit, 0 for withdraw
    void GetTries(QString card_number);
    int logs_curret_page = 1;
    int logs_total_pages = 1;
    //logs for updating logs view
    QString idSignal[10];
    QString dateSignal[10];
    QString eventSignal[10];
    QString amountSignal[10];

    double account_balance;
    QString account_name;

    QString fname;
    QString lname;
    QString profilePic;
    QByteArray pictureData;

    QString card_number;
    QString card_type;
    QString status;
    QString resMessage;
    int tries = 0;

private:
    void GetUserInfo();
    void GetCardInfo();
    void GetAccountInfo();
    void GetPictureData(QString);
    //network managament
    QNetworkAccessManager *manager = nullptr;
    QNetworkReply *reply = nullptr;
    //QByteArray response_data;
    QString auth = "";
    QString base_url="http://localhost:3000/";
    QByteArray authByteArr;
    //user data
    QString address;
    QString email;
    QString phone;
    //card data
    int account_id_int;
    QString account_id;
    //logs
    QList<QString> logs_id_list;
    QList<QString> logs_date_list;
    QList<QString> logs_event_list;
    QList<QString> logs_amount_list;
    double lastTransaction = 0;
    int lastAction = 0;
    int card_type_int;

signals:
    void SendTriesSignal(int tries);
    void AuthStatus(QString);
    void logsFinishedSignal();
    void dataGatheringFinished();
    void balanceUpdated(double);
    void errorBalanceMsg(QString);
private slots:
    void loginSlot(QNetworkReply *reply);
    void getUserInfoSlot(QNetworkReply *reply);
    void getCardInfoSlot(QNetworkReply *reply);
    void getAccountInfoSlot(QNetworkReply *reply);
    void getLogsSlot(QNetworkReply *reply);
    void createLogSlot(QNetworkReply *reply);
    void updateBalanceSlot(QNetworkReply *reply);
    void getTriesSlot(QNetworkReply *reply);
    void getPictureDataSlot(QNetworkReply *reply);
};

#endif // DLLRESTAPIENGINE_H
