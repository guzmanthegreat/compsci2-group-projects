#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Person {
private:
    string name;
    vector<string> friends;

public:
    Person(string personName) {
        name = personName;
    }

    void befriend(Person p) {
        if (find(friends.begin(), friends.end(), p.name) == friends.end()) {
            friends.push_back(p.name);
        }
    }

    void unfriend(Person p) {
        auto it = find(friends.begin(), friends.end(), p.name);
        if (it != friends.end()) {
            friends.erase(it);
        }
    }

    string get_friend_names() {
        string result = "";
        for (size_t i = 0; i < friends.size(); ++i) {
            result += friends[i];
            if (i != friends.size() - 1) {
                result += " ";
            }
        }
        return result;
    }

    string get_name() {
        return name;
    }
};

int main() {
    Person alice("Alice");
    Person bob("Bob");
    Person carol("Carol");

    alice.befriend(bob);
    alice.befriend(carol);
    cout << "Alice's friends: " << alice.get_friend_names() << endl;

    alice.unfriend(bob);
    cout << "Alice's friends after unfriending Bob: " << alice.get_friend_names() << endl;

    return 0;
}