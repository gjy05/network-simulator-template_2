#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry
{
public:
    Address destination;
    Link *nextLink;
};

class Router : public Node
{
protected:
    std::vector<RoutingEntry> routingTable_;

public:
    void receive(Packet *packet) override
    {
        std::cout << "Router #" << id() << ": ";
        for (RoutingEntry routing_entry : routingTable_)
        {
            if (routing_entry.destination == packet->destAddress())
            {
                std::cout << "forwarding packet (from: " << packet->srcAddress().toString()
                          << ", to: " << packet->destAddress().toString()
                          << ", " << packet->data().size() << " bytes)" << std::endl;

                routing_entry.nextLink->forward(this, packet);
                return;
            }
        }

        // 못 찾을 경우 아래가 실행됨
        std::cout << "no route for packet (from: " << packet->srcAddress().toString()
                  << ", to: " << packet->destAddress().toString()
                  << ", " << packet->data().size() << " bytes)" << std::endl;
    }
};

#endif