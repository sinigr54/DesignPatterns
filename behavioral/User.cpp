//
// Created by Alexander Chekh on 29.07.2018.
//

#include "User.h"
#include "ChatRoom.h"

#include <iostream>

void mediator::User::say(const string &message) const {
    if (room != nullptr) {
        room->broadcast(message, name);
    }
}

void mediator::User::pm(const string &message, long whoId) const {
    if (room != nullptr) {
        room->message(message, name, whoId);
    }
}

void mediator::User::receive(const string &origin, const string &message) {
    string fmt_msg{origin + ": \"" + message + "\""};
    string msg{"[" + name + "'s chat session]" + fmt_msg};

    cout << msg << endl;

    messages_log.push_back(msg);
}

mediator::User::User(long id, const string &name) : id(id), name(name) {

}
