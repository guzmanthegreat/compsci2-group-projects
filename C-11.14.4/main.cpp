#include <iostream>
#include <string>
#include <memory>
using namespace std;

class PermutationIterator {
private:
    string original;
    int current_pos;
    unique_ptr<PermutationIterator> tail_iterator;
    string current_prefix;

public:
    PermutationIterator(string s) : original(s), current_pos(0), tail_iterator(nullptr) {
        if (!original.empty()) {
            current_prefix = original.substr(current_pos, 1);
            string tail = original.substr(0, current_pos) + original.substr(current_pos + 1);
            tail_iterator = make_unique<PermutationIterator>(tail);
        }
    }

    bool has_more_permutations() {
        return current_pos < original.length();
    }

    string next_permutation() {
        if (tail_iterator == nullptr || !tail_iterator->has_more_permutations()) {
            current_pos++;
            if (current_pos >= original.length()) return "";

            current_prefix = original.substr(current_pos, 1);
            string tail = original.substr(0, current_pos) + original.substr(current_pos + 1);
            tail_iterator = make_unique<PermutationIterator>(tail);
        }

        return current_prefix + tail_iterator->next_permutation();
    }
};

// example
int main() {
    PermutationIterator iter("eat");

    while (iter.has_more_permutations()) {
        string perm = iter.next_permutation();
        if (!perm.empty())
            cout << perm << endl;
    }

    return 0;
}