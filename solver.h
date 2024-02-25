#include <iostream>
#include <vector>
#include "cube.h"

using namespace std;

class Solver {
    Cube cube;
    vector<string> solution;
    public:
        Solver(Cube c): cube{c} {}
        void solve() {
            // Ok so basically we need to make pruning tables, transition tables, and then we use IDA* to solve the cube
            // So there will be one for each phase
        }
};