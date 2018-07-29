//
// Created by Alexander Chekh on 29.07.2018.
//

#ifndef DESIGNPATTERNS_USER_H
#define DESIGNPATTERNS_USER_H

#include <string>
#include <vector>

using namespace std;

namespace mediator {

  struct ChatRoom;

  struct User {
      long id;
      string name;

      ChatRoom *room{nullptr};

      vector<string> messages_log;

      User(long id, const string &name);

      void say(const string &message) const ;
      void pm(const string &message, long whoId) const ;

      void receive(const string &origin, const string &message);
  };

}


#endif //DESIGNPATTERNS_USER_H
