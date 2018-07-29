//
// Created by Alexander Chekh on 29.07.2018.
//

#ifndef DESIGNPATTERNS_CHATROOM_H
#define DESIGNPATTERNS_CHATROOM_H

#include <vector>
#include <string>

#include "User.h"

using namespace std;

namespace mediator {

  struct ChatRoom {
      vector<User> users;

      void broadcast(const string &message, const string &origin);

      void message(const string &message, const string &origin, long whoId);

      void join(User &user);
  };

}


#endif //DESIGNPATTERNS_CHATROOM_H
