//
// Created by Alexander Chekh on 25.07.2018.
//

#include <iostream>
#include <vector>

using namespace std;

class BankAccount {
    int balance{0};
    int overdraft_limit{-500};

public:

    void deposit(int amount) {
        balance += amount;

        cout << "deposit: " << amount << " " << *this << endl;

    }

    bool withdraw(int amount) {
        if (balance - amount >= overdraft_limit) {
            balance -= amount;

            cout << "withdrew: " << amount << " " << *this << endl;

            return true;
        }

        return false;
    }

    friend ostream &operator<<(ostream &os, const BankAccount &account) {
        os << "balance: " << account.balance;
        return os;
    }
};

struct Command {
    bool succeeded{false};

    virtual void call() = 0;

    virtual void undo() = 0;
};

struct BankAccountCommand : Command {

    enum Operation {
        deposit, withdraw
    };

    BankAccountCommand(BankAccount &bankAccount,
                       Operation operation,
                       int amount) : bankAccount(bankAccount),
                                     operation(operation),
                                     amount(amount) {}

    void call() override {
        switch (operation) {
            case deposit:
                bankAccount.deposit(amount);
                succeeded = true;
                break;
            case withdraw:
                succeeded = bankAccount.withdraw(amount);
                break;
        }
    }

    void undo() override {
        if (!succeeded) {
            return;
        }

        switch (operation) {
            case deposit:
                bankAccount.withdraw(amount);
                break;
            case withdraw:
                bankAccount.deposit(amount);
                break;
        }
    }

private:

    BankAccount &bankAccount;
    int amount;
    Operation operation;
};

struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command {
    CompositeBankAccountCommand(const initializer_list<value_type> &items)
            : vector(items) {

    }

    void call() override {
        for (auto &command : *this) {
            command.call();
        }
    }

    void undo() override {
        for (auto it = rbegin(); it != rend(); ++it) {
            it->undo();
        }
    }
};

struct DependentBankAccountCommand : CompositeBankAccountCommand {

    DependentBankAccountCommand(const initializer_list<BankAccountCommand> &items)
            : CompositeBankAccountCommand(items) {

    }

    void call() override {
        bool isOk = true;
        for (auto &cmd : *this) {
            if (isOk) {
                cmd.call();
                isOk = cmd.succeeded;
            } else {
                cmd.succeeded = false;
            }
        }
    }

    void undo() override {

    }
};

struct MoneyTransferCommand : DependentBankAccountCommand {
    MoneyTransferCommand(
            BankAccount &from,
            BankAccount &to,
            int amount
    ) : DependentBankAccountCommand(
            {
                    BankAccountCommand{from, BankAccountCommand::withdraw, amount},
                    BankAccountCommand{to, BankAccountCommand::deposit, amount}
            }) {

    }
};

void behavioral_example2() {
    BankAccount bankAccount1, bankAccount2;
    bankAccount1.deposit(350);

    cout << bankAccount1 << endl << bankAccount2 << endl;

    MoneyTransferCommand command(bankAccount1, bankAccount2, 5500);
    command.call();

    cout << bankAccount1 << endl << bankAccount2 << endl;

    command.undo();

    cout << bankAccount1 << endl << bankAccount2 << endl;
}
