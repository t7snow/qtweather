#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}, m_manager(new QNetworkAccessManager(this))
{}

void NetworkManager::replyFinished(QNetworkReply *reply){

}
