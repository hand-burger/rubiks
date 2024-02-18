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
        Piece(int x, int y, int z, Colour xc, Colour yc, Colour zc, PieceType type):
            pos{x, y, z}, colour{xc, yc, zc}, type{type} {}

        Piece() = default;
        
        vector<int>getPos() const {
            
            return pos;
        }
        void rotate(const Matrix<3, 3> &rotation) {

            vector<int> newPos = rotation * pos; // rotate using matrix multiplication

            // bad way of determining turn type
            if (newPos[0] == pos[0]) {
                
                // x matches so F turn
                
                // Colour temp {colour[1]};
                // colour[1] = colour[2];
                // colour[2] = temp;
                swap(colour[1], colour[2]);
            } else if (newPos[1] == pos[1]) {

                // y matches so R turn

                // Colour temp {colour[0]};
                // colour[0] = colour[2];
                // colour[2] = temp;
                swap(colour[0], colour[2]);
            } else if (newPos[2] == pos[2]) {

                // z matches so U turn

                // Colour temp {colour[0]};
                // colour[0] = colour[1];
                // colour[1] = temp;
                swap(colour[0], colour[1]);
            } else {

                // not a valid turn
                throw Improper_Turn{};
            }
            pos = newPos;
        }
};
#endif
