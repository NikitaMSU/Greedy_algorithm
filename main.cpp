#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Item
{
    double value;
    double weight;
    double val_wei_ratio() const {
        return value / weight;
    }
};

void tester(string filename)
{
    auto start = std::chrono::high_resolution_clock::now();
    cout << filename << endl;
    ifstream input(filename, ios::in);
    int n;
    double W;
    input >> n >> W;
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        input >> items[i].value >> items[i].weight;
    }
    input.close();
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (items[j].val_wei_ratio() > items[max_idx].val_wei_ratio()) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swap(items[i], items[max_idx]);
        }
    }
    double res = 0.0, max_weight = W;
    for (const auto &item : items) {
        if (max_weight <= 0)
            break;
        if (item.weight <= max_weight) {
            res += item.value;
            max_weight -= item.weight;
        }
        else {
            res += item.val_wei_ratio() * max_weight;
            max_weight = 0;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto work_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Work time: " << work_time << endl;
    cout << "Max weight: " << res << endl << endl;

    return;
}

int main()
{
    tester("ks_4_0");
    tester("ks_30_0");
    tester("ks_100_0");
    tester("ks_300_0");
    return 0;
}
