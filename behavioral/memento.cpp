//
// Created by Alexander Chekh on 29.07.2018.
//

#include "behavioral.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace Memento {

  class Memento {
      int balance;
  public:
      Memento(int balance)
              : balance(balance) {
      }

      friend class BankAccount;

      friend class BankAccount2;
  };

  class BankAccount {
      int balance = 0;
  public:
      explicit BankAccount(const int balance)
              : balance(balance) {
      }

      Memento deposit(int amount) {
          balance += amount;
          return {balance};
      }

      void restore(const Memento &m) {
          balance = m.balance;
      }

      friend ostream &operator<<(ostream &os, const BankAccount &obj) {
          return os << "balance: " << obj.balance;
      }
  };

  class BankAccount2 // supports undo/redo
  {
      int balance = 0;
      vector<shared_ptr<Memento>> changes;
      int current;
  public:
      explicit BankAccount2(const int balance)
              : balance(balance) {
          changes.emplace_back(make_shared<Memento>(balance));
          current = 0;
      }

      shared_ptr<Memento> deposit(int amount) {
          balance += amount;
          auto m = make_shared<Memento>(balance);
          changes.push_back(m);
          ++current;
          return m;
      }

      void restore(const shared_ptr<Memento> &m) {
          if (m) {
              balance = m->balance;
              changes.push_back(m);
              current = static_cast<int>(changes.size() - 1);
          }
      }

      shared_ptr<Memento> undo() {
          if (current > 0) {
              --current;
              auto m = changes[current];
              balance = m->balance;
              return m;
          }
          return {};
      }

      shared_ptr<Memento> redo() {
          if (current + 1 < changes.size()) {
              ++current;
              auto m = changes[current];
              balance = m->balance;
              return m;
          }
          return {};
      }

      friend ostream &operator<<(ostream &os, const BankAccount2 &obj) {
          return os << "balance: " << obj.balance;
      }
  };

}

void behavioral_example6() {

}
