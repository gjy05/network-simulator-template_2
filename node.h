#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>

class Node
{
    friend class LinkInstaller;

private:
    int id_;
    static int nextId_;

protected:
    std::vector<Link *> links_;

public:
    Node() : id_(nextId_++) {}
    virtual ~Node() {}
    int id() const { return id_; }

    void add_link(Link *link)
    {
        links_.push_back(link);
    }

    virtual void receive(Packet *packet) = 0;
};

#endif