#ifndef PING_SERVICE_INSTALLER_H
#define PING_SERVICE_INSTALLER_H

#include "address.h"
#include "message_service.h"
#include "service_installer.h"

class MessageServiceInstaller : public ServiceInstaller
{
private:
    // 목적지 주소
    Address destAddress_;
    // 목적지 포트
    short destPort_;

    short listenPort_;
    static short next_listenPort_;

public:
    MessageServiceInstaller(const Address &destAddress, short destPort)
        : destAddress_(destAddress), destPort_(destPort), listenPort_(next_listenPort_++) {}

    // 호스트에 MessageService를 설치한다
    MessageService *install(Host *host)
    {
        MessageService* msg_service = new MessageService(
            host, listenPort_, destAddress_, destPort_);
        ServiceInstaller::install(host, msg_service);
        return msg_service;
    }
};

#endif