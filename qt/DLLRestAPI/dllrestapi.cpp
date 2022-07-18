#include "dllrestapi.h"

DLLRestAPI::DLLRestAPI(QObject *parent) : QObject(parent)
{
    engine = new DLLRestAPIEngine;
    connect(engine, SIGNAL(SendTriesSignal(int)),
            this,SLOT(GetTriesSlot(int)));

    connect(engine, SIGNAL(AuthStatus(QString)), this, SLOT(LoginStatusSlot(QString)));
    connect(engine, SIGNAL(logsFinishedSignal()), this, SLOT(GetLogs10()));
    connect(engine, SIGNAL(dataGatheringFinished()), this, SLOT(GetInfo()));
    connect(engine, SIGNAL(balanceUpdated(double)), this, SLOT(sendBalanceToExe(double)));
    connect(engine, SIGNAL(errorBalanceMsg(QString)), this, SLOT(balanceErrorSlot(QString)));
}

DLLRestAPI::~DLLRestAPI()
{
    qDebug()<<"rest api dest";
    disconnect(engine, SIGNAL(AuthStatus(QString)), this, SLOT(LoginStatusSlot(QString)));
    disconnect(engine, SIGNAL(logsFinishedSignal()), this, SLOT(GetLogs10()));
    disconnect(engine, SIGNAL(dataGatheringFinished()), this, SLOT(GetInfo()));
    disconnect(engine, SIGNAL(balanceUpdated(double)), this, SLOT(sendBalanceToExe(double)));
    disconnect(engine, SIGNAL(errorBalanceMsg(QString)), this, SLOT(balanceErrorSlot(QString)));
    delete engine;
    engine = nullptr;
}

void DLLRestAPI::GetLogs10()
{

    for(int i = 0; i<10; i++){
        qDebug()<<engine->dateSignal[i];
//        logData[i][0] = engine->dateSignal[i].replace(10, 1," ");
        logData[i][0] = engine->dateSignal[i];

        logData[i][1] = engine->eventSignal[i];
        logData[i][2] = engine->amountSignal[i];
        logData[i][3] = engine->idSignal[i];
        qDebug()<<logData[i][0];
    }

    emit logsUpdatedSignal();
}

void DLLRestAPI::UpdateLogs(int i)
{
    engine->CreateLog(i);
}

void DLLRestAPI::GetInfo()
{
    qDebug()<<"info signal sent";
    emit InfoSignal(engine->account_balance,engine->account_name,engine->fname,engine->lname,engine->card_number,engine->card_type,engine->pictureData);
}

void DLLRestAPI::GetTriesFromApi(QString card_number){
    engine->GetTries(card_number);
}

void DLLRestAPI::GetTriesSlot(int tries)
{
    emit SendTriesToExe(tries);
}

void DLLRestAPI::LoginStatusSlot(QString status)
{
    qDebug() << "Sending Login status info to exe";
    emit StatusToExe(status);
}

void DLLRestAPI::LoginSlot(QString card, QString pin)
{
    engine->Login(card, pin);
}

void DLLRestAPI::updateBalance(int action, double amount, int type)
{
    engine->updateBalance(action, amount, type);
//    emit InfoSignal(engine->account_balance,engine->account_name,engine->fname,engine->lname,engine->card_number,engine->card_type,engine->pictureData);
}
void DLLRestAPI::sendBalanceToExe(double amount){
    qDebug()<<"interface emitting saldo update";
    emit saldoUpdated(amount);
}

void DLLRestAPI::balanceErrorSlot(QString err)
{
    emit balanceErrorToExe(err);
}

void DLLRestAPI::getLogsByPage(int page)
{

    switch (page) {
        case 0:
            engine->logs_curret_page = engine->logs_curret_page+1;
            break;
        case -1:
            engine->logs_curret_page = engine->logs_curret_page-1;
            break;
    default:
        engine->logs_curret_page = page;
    }

    engine->GetLogs();

}

