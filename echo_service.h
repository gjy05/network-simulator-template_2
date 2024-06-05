#ifndef ECHO_SERVICE_H
#define ECHO_SERVICE_H

#include "host.h"
#include "service.h"
#include <iostream>
#include <string>

// 수신한 패킷을 전송자에게 다시 전송하는 서비스
class EchoService : public Service
{
    friend class EchoServiceInstaller;

private:
    EchoService(Host *host, short port) : Service(host, port) {}

public:
    void receive(Packet *packet)
    {
        std::cout << "EchoService: received \"" << packet->dataString()
                  << "\" from " << packet->srcAddress().toString() << ":" << packet->srcPort()
                  << ", send reply with same data" << std::endl;

        Packet *echo_packet = new Packet(
            host_->address(), packet->srcAddress(),
            port_, packet->srcPort(), packet->data());

        delete packet;

        host_->send(echo_packet);
    }
};

#endif