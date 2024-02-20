#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "matrix.h"

using namespace std;

// describes the colour of a given piece
enum class Colour{ Y, W, R, O, B, G, N };

// may be useful later, describing the kind of piece
enum class PieceType{ Corner, Edge, Middle };

class Improper_Turn{};

class Piece {

    // stores the 3d position of the piece, 0, 0, 0 being the center of the cube
    vector<int> pos;
    vector<Colour> colour;
    PieceType type;

    public:
        Piece(int x = 0, int y = 0, int z = 0, Colour xc = Colour::N, Colour yc = Colour::N, Colour zc = Colour::N, PieceType type = PieceType::Middle):
            pos{x, y, z}, colour{xc, yc, zc}, type{type} {}
        
        vector<int>getPos() const {
            
            return pos;
        }

        vector<Colour> getColour() const {
            
            return colour;
        }
        void rotate(const Matrix<3, 3> *rotation) {

            vector<int> newPos = *rotation * pos; // rotate using matrix multiplication

            // Determine which plane the rotation was on to swap the colours accordingly
            vector<int> diff;
            for (int i = 0; i < 3; i++) {
                diff.push_back(newPos[i] - pos[i]);
            }
            pos = newPos;
            int zeroCount = 0;
            for (int i = 0; i < 3; i++) {
                if (diff[i] == 0) {
                    zeroCount++;
                }
            }
            if (zeroCount == 3) {
                return;
            }
            else if (zeroCount == 2) {
                vector<int> temp = *rotation * diff;
                for (int i = 0; i < 3; i++) {
                    diff[i] += temp[i];
                }
            }

            // Get the positions of the two non-zero elements
            int first = -1;
            int second = -1;
            for (int i = 0; i < 3; i++) {
                if (diff[i] != 0) {
                    if (first == -1) {
                        first = i;
                    }
                    else {
                        second = i;
                    }
                }
            }

            // Swap the colours
            swap(colour[first], colour[second]);
        }
};
#endif
