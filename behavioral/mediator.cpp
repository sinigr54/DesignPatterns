//
// Created by Alexander Chekh on 28.07.2018.
//

#include "behavioral.h"
#include "User.h"
#include "ChatRoom.h"

using namespace mediator;

void behavioral_example5() {
    ChatRoom room;

    User john{0, "john"};
    User jane{1, "jane"};
    User sam{2, "sam"};

    room.join(john);
    john.say("hello, chat!");

    room.join(jane);
    jane.say("hy!");

    room.join(sam);
    jane.pm("hello, sam", sam.id);
}