#include <iostream>
#include <vector>
using namespace std;

class CashRegisterTax {
private:
    double tax_rate;
    vector<double> items;
    vector<double> taxable_items;

public:
    CashRegisterTax(double rate) : tax_rate(rate) {}

    void add_item(double price) { items.push_back(price); }

    void add_taxable_item(double price) { taxable_items.push_back(price); }

    double get_total() {
        double total = 0;
        for (double p : items) total += p;
        for (double p : taxable_items) total += p;
        total += get_total_tax();
        return total;
    }

    double get_total_tax() {
        double tax = 0;
        for (double p : taxable_items) tax += p * tax_rate;
        return tax;
    }
};

int main() {
    CashRegisterTax register1(0.08); // 

    register1.add_item(10.00);           
    register1.add_taxable_item(20.00);   
    register1.add_taxable_item(5.00);    

    cout << "Total tax: $" << register1.get_total_tax() << endl;
    cout << "Total amount: $" << register1.get_total() << endl;

    return 0;
}