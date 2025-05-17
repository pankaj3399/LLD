#include<bits/stdc++.h>
using namespace std;

// ==============================
// OBSERVER INTERFACE
// ==============================
class Observer {
public:
    virtual void update(const string& channelName, const string& videoTitle) = 0;
    virtual ~Observer() = default;
};

// ==============================
// SUBJECT INTERFACE
// ==============================
class Subject {
public:
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers(const string& videoTitle) = 0;
    virtual ~Subject() = default;
};

// ==============================
// CONCRETE SUBJECT: YOUTUBE CHANNEL
// ==============================
class YouTubeChannel : public Subject {
private:
    string channelName;
    vector<Observer*> observers;

public:
    YouTubeChannel(const string& name) : channelName(name) {}

    void addObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notifyObservers(const string& videoTitle) override {
        for (auto& obs : observers) {
            obs->update(channelName, videoTitle);
        }
    }

    void uploadVideo(const string& videoTitle) {
        cout << channelName << " uploaded a new video: " << videoTitle << "\n";
        notifyObservers(videoTitle);
    }
};

// ==============================
// CONCRETE OBSERVERS
// ==============================

// Email Subscriber
class EmailSubscriber : public Observer {
public:
    void update(const string& channelName, const string& videoTitle) override {
        cout << "[Email] Notifying subscribers: " << channelName << " has a new video: " << videoTitle << "\n";
    }
};

// SMS Subscriber
class SMSSubscriber : public Observer {
public:
    void update(const string& channelName, const string& videoTitle) override {
        cout << "[SMS] New video from " << channelName << ": " << videoTitle << "\n";
    }
};

// Log Subscriber
class LogSubscriber : public Observer {
public:
    void update(const string& channelName, const string& videoTitle) override {
        cout << "[LOG] Channel '" << channelName << "' published: " << videoTitle << "\n";
    }
};

// ==============================
// MAIN FUNCTION
// ==============================
int main() {
    // Create a YouTube channel
    auto channel = new YouTubeChannel("CppCrafter");

    // Create subscribers
    auto emailSub = new EmailSubscriber();
    auto smsSub = new SMSSubscriber();
    auto logSub = new LogSubscriber();

    // Subscribe them
    channel->addObserver(emailSub);
    channel->addObserver(smsSub);
    channel->addObserver(logSub);

    // Upload a video
    channel->uploadVideo("Introduction to Design Patterns");

    // Unsubscribe SMS subscriber
    channel->removeObserver(smsSub);

    // Upload another video
    channel->uploadVideo("Advanced Templates in C++");

    return 0;
}