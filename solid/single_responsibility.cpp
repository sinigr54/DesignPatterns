//
// Created by sinigr on 4/21/18.
//

#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "solid.h"

using namespace std;

struct Journal {
    string title;
    vector<string> entries;

    explicit Journal(string title);

    void add(const string &entry);

    // persistence is a separate concern
    void save(const string &filename);
};

Journal::Journal(string title) : title(move(title)) {

}

void Journal::add(const string &entry) {
    static int count = 1;
    entries.push_back(to_string(count++) + ": " + entry);
}

void Journal::save(const string &filename) {
    ofstream ofs(filename);
    for (const auto &entry : entries) {
        ofs << entry << endl;
    }
}

struct PersistenceManager {
    void save(const Journal &journal, const string &filename);
};

void PersistenceManager::save(const Journal &journal, const string &filename) {
    ofstream ofs(filename);
    for (const auto &entry : journal.entries) {
        ofs << entry << endl;
    }
}

void solid_example1() {
    Journal journal{"Dear Diary"};
    journal.add("I ate a bug");
    journal.add("I cried today");

    // journal.save("diary.txt");

    PersistenceManager persistenceManager;
    persistenceManager.save(journal, "diary.txt");
}
