//
// Created by Alexander Chekh on 06.09.2018.
//

#include "behavioral.h"

#include <iostream>
#include <vector>

using namespace std;

struct Creature {
    int attack, health;

    Creature(int attack, int health) : attack(attack), health(health) {}
};

struct CardGame {
    vector<Creature> creatures;

    explicit CardGame(vector<Creature> creatures) : creatures(std::move(creatures)) {}

    // return the index of the creature that won (is a live)
    // example:
    // - creature1 alive, creature2 dead, return creature1
    // - creature1 dead, creature2 alive, return creature2
    // - no clear winner: return -1
    int combat(int creature1, int creature2) {
        int startCreature1Health = creatures[creature1].health;
        int startCreature2Health = creatures[creature2].health;

        Creature &c1 = creatures[creature1];
        Creature &c2 = creatures[creature2];

        int round = 0;
        while (c1.health > 0 && c2.health > 0) {
            hit(c1, c2);
            hit(c2, c1);

            if (startCreature1Health == c1.health &&
                startCreature2Health == c2.health) {
                return -1;
            }
        }

        if (creatures[creature1].health <= 0 && creatures[creature2].health <= 0) {
            return -1;
        } else if (creatures[creature1].health > 0) {
            return creature1;
        } else if (creatures[creature2].health > 0) {
            return creature2;
        } else {
            return -1;
        }
    }

    virtual void hit(Creature &attacker, Creature &other) = 0;
};

struct TemporaryCardDamageGame : CardGame {
    explicit TemporaryCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override {
        if (attacker.attack >= other.health) {
            other.health = 0;
        }
    }
};

struct PermanentCardDamageGame : CardGame {
    explicit PermanentCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override {
        other.health -= attacker.attack;
    }
};

void template_method_exercise() {
    vector<Creature> creatures{Creature{1, 4}, Creature{1, 3}};
    PermanentCardDamageGame game{creatures};
    cout << game.combat(0, 1) << endl;
}
