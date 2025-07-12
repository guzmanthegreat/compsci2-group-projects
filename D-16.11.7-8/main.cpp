#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

struct Fact {
    string values;
};

struct DecisionNode {
    bool isLeaf;
    string decision;
    int criterionIndex;
    DecisionNode* yesChild;
    DecisionNode* noChild;

    DecisionNode(string val, bool leaf = false, int index = -1)
        : decision(val), isLeaf(leaf), criterionIndex(index), yesChild(nullptr), noChild(nullptr) {}
};

double entropy(double p) {
    if (p == 0 || p == 1) return 0;
    return -p * log2(p) - (1 - p) * log2(1 - p);
}

double computeUncertainty(int criterionIndex, const vector<Fact*>& data, int numCriteria) {
    int yesTotal = 0, yesPositive = 0, noTotal = 0, noPositive = 0;
    for (auto f : data) {
        if (f->values[criterionIndex] == 'Y') {
            yesTotal++;
            if (f->values[numCriteria] == 'Y') yesPositive++;
        } else {
            noTotal++;
            if (f->values[numCriteria] == 'Y') noPositive++;
        }
    }
    double uYes = yesTotal ? entropy((double)yesPositive / yesTotal) : 0;
    double uNo = noTotal ? entropy((double)noPositive / noTotal) : 0;
    return ((double)yesTotal / data.size()) * uYes + ((double)noTotal / data.size()) * uNo;
}

DecisionNode* buildTree(vector<Fact*>& data, vector<string>& criteriaNames, vector<bool>& used, int numCriteria) {
    int positive = 0, negative = 0;
    for (auto f : data) {
        if (f->values[numCriteria] == 'Y') positive++;
        else negative++;
    }
    if (positive == 0 || negative == 0) {
        return new DecisionNode(positive ? "Yes" : "No", true);
    }

    double minU = 1e9;
    int bestIndex = -1;
    for (int i = 0; i < numCriteria; ++i) {
        if (!used[i]) {
            double u = computeUncertainty(i, data, numCriteria);
            if (u < minU) {
                minU = u;
                bestIndex = i;
            }
        }
    }

    if (bestIndex == -1) return new DecisionNode(positive >= negative ? "Yes" : "No", true);

    used[bestIndex] = true;
    vector<Fact*> yesData, noData;
    for (auto f : data) {
        if (f->values[bestIndex] == 'Y') yesData.push_back(f);
        else noData.push_back(f);
    }

    DecisionNode* node = new DecisionNode(criteriaNames[bestIndex], false, bestIndex);
    node->yesChild = buildTree(yesData, criteriaNames, used, numCriteria);
    node->noChild = buildTree(noData, criteriaNames, used, numCriteria);
    used[bestIndex] = false;

    return node;
}

void classify(DecisionNode* root) {
    while (!root->isLeaf) {
        cout << root->decision << " [Y/N]: ";
        char ans;
        cin >> ans;
        root = (toupper(ans) == 'Y') ? root->yesChild : root->noChild;
    }
    cout << "Result: " << root->decision << endl;
}

void loadData(const string& filename, vector<string>& criteriaNames, string& objectiveName, vector<Fact>& facts) {
    ifstream file(filename);
    string line;
    while (getline(file, line) && !line.empty()) criteriaNames.push_back(line);
    getline(file, objectiveName);
    while (getline(file, line)) if (!line.empty()) facts.push_back({line});
}

//16.11.8

struct ExprNode {
    string value;
    ExprNode* left;
    ExprNode* right;
    ExprNode(string v) : value(v), left(nullptr), right(nullptr) {}
};

ExprNode* buildExprTree(const string& expr, int& index) {
    while (index < expr.size() && isspace(expr[index])) ++index;

    if (isdigit(expr[index])) {
        string num;
        while (index < expr.size() && isdigit(expr[index])) num += expr[index++];
        return new ExprNode(num);
    }

    if (expr[index] == '(') {
        ++index; // skip (
        ExprNode* left = buildExprTree(expr, index);
        while (index < expr.size() && isspace(expr[index])) ++index;
        char op = expr[index++];
        ExprNode* right = buildExprTree(expr, index);
        ++index; // skip )
        ExprNode* root = new ExprNode(string(1, op));
        root->left = left;
        root->right = right;
        return root;
    }
    return nullptr;
}

int evalExprTree(ExprNode* root) {
    if (!root->left && !root->right) return stoi(root->value);
    int l = evalExprTree(root->left);
    int r = evalExprTree(root->right);
    if (root->value == "+") return l + r;
    if (root->value == "-") return l - r;
    if (root->value == "*") return l * r;
    if (root->value == "/") return l / r;
    return 0;
}

void runExpressionEvaluator() {
    cout << "Enter expression (e.g. (3+(4*2))): ";
    string expr;
    getline(cin, expr);
    int idx = 0;
    ExprNode* tree = buildExprTree(expr, idx);
    cout << "Result: " << evalExprTree(tree) << endl;
}

int main() {
    // 16.11.7
    vector<string> criteria;
    string objective;
    vector<Fact> facts;
    loadData("facts.txt", criteria, objective, facts);

    vector<Fact*> factPtrs;
    for (auto& f : facts) factPtrs.push_back(&f);
    vector<bool> used(criteria.size(), false);
    DecisionNode* tree = buildTree(factPtrs, criteria, used, criteria.size());

    cout << "\n--- ID3 Decision Tree ---\n";
    classify(tree);

    // 16.11.8
    cout << "\n--- Expression Evaluator ---\n";
    cin.ignore();
    runExpressionEvaluator();

    return 0;
}