//
// Created by Alexander Chekh on 29.07.2018.
//

#include "ChatRoom.h"

#include <exception>

void mediator::ChatRoom::broadcast(const string &message, const string &origin) {
    for (auto &&user : users) {
        if (user.name != origin) {
            user.receive(origin, message);
        }
    }
}

void mediator::ChatRoom::message(const string &message, const string &origin, long whoId) {
    auto target = find_if(users.begin(), users.end(), [&whoId](const User &user) {
        return user.id == whoId;
    });

    if (target != users.cend()) {
        target->receive(origin, message);
    }
}

void mediator::ChatRoom::join(mediator::User &user) {
    string join_msg = user.name + " joins the chat";
    broadcast(join_msg, "room");

    user.room = this;

    users.push_back(user);
}
