#ifndef ECHO_SERVICE_INSTALLER_H
#define ECHO_SERVICE_INSTALLER_H

#include "address.h"
#include "echo_service.h"
#include "service_installer.h"

class EchoServiceInstaller : public ServiceInstaller
{
private:
    // 패킷을 수신할 포트
    short listenPort_;

public:
    EchoServiceInstaller(short listenPort) : listenPort_(listenPort) {}

    // 호스트에 EchoService를 설치한다.
    EchoService *install(Host *host)
    {
        ServiceInstaller::install(host, new EchoService(host, listenPort_));
        return nullptr; // 정의되어 있는 함수를 수정할 수 없으므로, nullptr 이라도 반환한다. 틀렸을 경우 추후 수정
    }
};

#endif