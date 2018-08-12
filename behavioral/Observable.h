//
// Created by Alexander Chekh on 12.08.2018.
//

#ifndef DESIGNPATTERNS_OBSERVABLE_H
#define DESIGNPATTERNS_OBSERVABLE_H

#include <string>
#include <vector>
#include <algorithm>

#include <boost/signals2.hpp>

using std::string;
using std::vector;
using std::remove;

namespace Observer {

  template<typename T>
  class Observer;

  template<typename T>
  class Observable {
  public:

      void notify(T &source, const std::string &fieldName) {
        for (auto &observer : observers) {
          observer->fieldChanged(source, fieldName);
        }
      }

      void subscribe(Observer<T> &observer) {
        observers.push_back(&observer);
      }

      void unSubscribe(Observer<T> &observer) {
        observers.erase(remove(observers.begin(), observers.end(), &observer));
      }

  private:
      vector<Observer<T> *> observers;
  };

}

namespace BoostObserver {

  template <typename T>
  class Observable {
  public:

      boost::signals2::signal<void(T&, const string &)> fieldChanged;
  };

}

#endif //DESIGNPATTERNS_OBSERVABLE_H
