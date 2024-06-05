#include "node.h"
#include "host.h"
#include "router.h"
#include "manual_router.h"

#include "service.h"
#include "echo_service.h"
#include "message_service.h"

#include "service_installer.h"
#include "echo_service_installer.h"
#include "message_service_installer.h"

#include "link.h"
#include "link_installer.h"

#include "packet.h"
#include "address.h"

// 헤더 파일에서 구현하면 오류가 생기는 것들을 여기서 구현한다.

int Node::nextId_ = 0;
short MessageServiceInstaller::next_listenPort_ = 1000;

void Link::forward(Node *sending_node, Packet *packet)
{
    std::cout << "Link: forwarding packet from node #" << sending_node->id()
              << ", to node #" << other(sending_node)->id() << std::endl;
    other(sending_node)->receive(packet);
}
