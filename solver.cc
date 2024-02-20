#include <iostream>
#include "solver.h"

using namespace std;

int main() {
    Cube c;
    c.print();
    c.scramble();
    cout << endl << endl;
    c.print();
    Solver s{c};
    s.solve();
    return 0;
}