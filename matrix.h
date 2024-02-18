#include <iostream>
#include <initializer_list>
#include <vector>

using namespace std;

class incorrect_size{};

template <size_t N, size_t M> class Matrix {

    size_t m;
    size_t n;

    vector<vector<int>> rows;

    public:
        Matrix(initializer_list<int> init) {

            m = M;
            n = N;

            rows.reserve(m);

            for (size_t i = 0; i < m; ++i) {

                rows[i].reserve(n);
            }

            if (init.size() != (n * m)) throw incorrect_size{};

            size_t i = 0;
            size_t j = 0;

            for (auto &t : init) {
                rows[i][j++] = t;

                if (j == n) { // change this
                    i++;
                    j = 0;
                }
            }
        }

        ostream& print(ostream &out) const {

            for (size_t i = 0; i < m; ++i) {

                for (size_t j = 0; j < n; ++j) {

                    out << rows[i][j] << ' ';
                }
                out << endl;
            }

            return out;
        }

        vector<int> operator*(vector<int> &vec) const {

            if (vec.size() != n) throw incorrect_size{};

            vector<int> retval;

            for (size_t i = 0; i < m; ++i) {

                int val = 0;

                for (size_t j = 0; j < n; ++j) {

                    val += vec[j] * rows[i][j];
                }

                retval.push_back(val);
            }

            return retval;
        }
};

// Rotation matrices

const Matrix<3, 3> Umove {0, -1, 0, 1, 0, 0, 0, 0, 1};

const Matrix<3, 3> Rmove {0, 0, -1, 0, 1, 0, 1, 0, 0};

const Matrix<3, 3> Fmove {1, 0, 0, 0, 0, 1, 0, -1, 0};