#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>
#include <cstdlib>

class Host : public Node
{
    friend class ServiceInstaller;

private:
    // 호스트의 주소
    Address address_;

    // 설치된 서비스 목록
    std::vector<Service *> services_;

public:
    Address address() { return address_; }
    Host(Address address) : address_(address) {}
    ~Host() override
    {
        services_.clear();
    }

    // 호스트와 설치된 서비스를 전부 초기화한다.
    void initialize() {}

    // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
    void send(Packet *packet)
    { // 설치된 서비스에서 실행한다
        std::cout << "Host #" << id()
                  << ": sending packet (from: " << packet->srcAddress().toString()
                  << ", to: " << packet->destAddress().toString()
                  << ", " << packet->data().size() << " bytes)" << std::endl;

        links_[std::rand() % links_.size()]->forward(this, packet);
    }

    void receive(Packet *packet) override
    {
        std::cout << "Host #" << id();

        for (Service *service : services_)
        {
            if (service->port() == packet->destPort())
            {
                std::cout << ": received packet, destination port: " << packet->destPort()
                          << std::endl;
                service->receive(packet);
                return;
            }
        }

        // 못 찾을 경우 아래가 실행됨
        std::cout << ": no service for packet (from: " << packet->srcAddress().toString()
                  << ", to: " << packet->destAddress().toString()
                  << ", " << packet->data().size() << " bytes)" << std::endl;

        delete packet;
    }
};

#endif