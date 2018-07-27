//
// Created by Alexander Chekh on 10.05.2018.
//

#include "behavioral.h"

#include <iostream>
#include <string>

#include <boost/signals2/connection.hpp>
#include <boost/signals2/signal.hpp>
#include <utility>

using std::string;
using std::ostream;
using std::cout;
using std::endl;

using namespace boost::signals2;

struct Query {
    enum Argument {
        attack,
        defence
    };

    Argument argument;
    string creatureName;
    int result;

public:

    Query(Argument argument, string creatureName, int result)
            : argument(argument),
              creatureName(std::move(creatureName)),
              result(result) {

    }
};

struct Game {
    signal<void(Query &)> queries;
};

class Creature {
    Game &game;
    int attack;
    int defence;

    string name;
public:

    Creature(Game &game, string name, int attack, int defence)
            : game(game), attack(attack), defence(defence), name(std::move(name)) {
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Creature::name = name;
    }

    int getAttack() const {
        Query q{Query::Argument::attack, name, attack};
        game.queries(q);

        return q.result;
    }

    friend ostream &operator<<(ostream &os, const Creature &creature) {
        os << " name: " << creature.name
           << " attack: " << creature.getAttack()
           << " defence: " << creature.defence;

        return os;
    }
};

class CreatureModifier {
    Game &game;
    Creature &creature;

public:

    CreatureModifier(Game &game, Creature &creature)
            : game(game), creature(creature) {

    }

    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier {
    connection conn;

public:
    DoubleAttackModifier(Game &game, Creature &creature)
            : CreatureModifier(game, creature) {

        conn = game.queries.connect([&](Query &query) {
            if (query.creatureName == creature.getName() &&
                query.argument == Query::Argument::attack) {
                query.result *= 2;
            }
        });
    }

    ~DoubleAttackModifier() override {
        conn.disconnect();
    }
};

void behavioral_example1() {
    Game game;
    Creature goblin{ game, "Strong Goblin", 2, 2 };

    cout << goblin << endl;

    {
        DoubleAttackModifier dam{ game, goblin };

        cout << goblin << endl;
    }

    cout << goblin << endl;
}
