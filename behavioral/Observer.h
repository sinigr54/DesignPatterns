//
// Created by Alexander Chekh on 12.08.2018.
//

#ifndef DESIGNPATTERNS_OBSERVER_H
#define DESIGNPATTERNS_OBSERVER_H

#include <string>

using std::string;

namespace Observer {

  template<typename T>
  class Observer {
  public:
      virtual void fieldChanged(T &source, const string &fieldName) = 0;
  };

}

#endif //DESIGNPATTERNS_OBSERVER_H
