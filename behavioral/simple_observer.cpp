//
// Created by Alexander Chekh on 12.08.2018.
//

#include "behavioral.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <utility>

using std::vector;
using std::remove;
using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;

class Subscriber {

    string name;

public:

    explicit Subscriber(string name) : name(std::move(name)) {

    }

    void onError() const {
        cout << name << " onError" << endl;
    }

    void onComplete() const {
        cout << name << " onComplete" << endl;
    }

    bool operator==(const Subscriber &rhs) const {
        return name == rhs.name;
    }

    bool operator!=(const Subscriber &rhs) const {
        return !(rhs == *this);
    }
};

class Publisher {

public:

    void subscribe(const Subscriber &subscriber) {
        subscribers.push_back(subscriber);
    }

    void unSubscribe(const Subscriber &subscriber) {
        auto item = remove(subscribers.begin(), subscribers.end(), subscriber);
        if (item != subscribers.end()) {
            subscribers.erase(item);
        }
    }

protected:

    void notifyComplete() {
        for (const auto &s : subscribers) {
            s.onComplete();
        }
    }

    void notifyError() {
        for (const auto &s : subscribers) {
            s.onError();
        }
    }

private:

    vector<Subscriber> subscribers;

};

class ImageDownloader : public Publisher {
    bool isError{false};

public:

    void download(const string &url) {
        if (isError) {
            Publisher::notifyError();
        } else {
            Publisher::notifyComplete();
        }
    }

    void setIsError(bool isError) {
        ImageDownloader::isError = isError;
    }
};

void behavioral_example7() {

    const string url{"http:://image.png"};

    ImageDownloader downloader;
    Subscriber subscriber{"subscriber"};
    Subscriber subscriber1{"subscriber1"};

    downloader.subscribe(subscriber);
    downloader.subscribe(subscriber1);

    downloader.setIsError(false);
    downloader.download(url);

    downloader.setIsError(true);
    downloader.download(url);

    downloader.unSubscribe(subscriber);
    downloader.unSubscribe(subscriber1);

    downloader.setIsError(true);
    downloader.download(url);
}
