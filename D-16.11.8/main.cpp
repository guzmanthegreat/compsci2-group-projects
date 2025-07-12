#include <iostream>
#include <string>
#include <cctype>
using namespace std;

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
        ++index;
        ExprNode* left = buildExprTree(expr, index);
        while (index < expr.size() && isspace(expr[index])) ++index;
        char op = expr[index++];
        ExprNode* right = buildExprTree(expr, index);
        ++index;
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

int main() {
    cout << "--- Expression Evaluator ---\n";
    cout << "Enter expression (Example: (3+(4*2))): ";
    string expr;
    getline(cin, expr);
    int idx = 0;
    ExprNode* tree = buildExprTree(expr, idx);
    cout << "Result: " << evalExprTree(tree) << endl;
    return 0;
}
