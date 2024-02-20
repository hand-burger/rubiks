#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <string>
#include <format>
#include <stdexcept>
#include <map>
#include <memory>
#include "piece.h"
#include "matrix.h"

using namespace std;

class Cube {
    Piece faces[6];
    Piece edges[12];
    Piece corners[8];
    vector<Piece*> pieces;

    map<Colour, std::string> colorMap {
        {Colour::Y, "Y "},
        {Colour::W, "W "},
        {Colour::R, "R "},
        {Colour::O, "O "},
        {Colour::B, "B "},
        {Colour::G, "G "},
        {Colour::N, "N "}
    };
    vector<vector<int>> facePositions {
        {0, 0, 1}, // Up
        {0, -1, 0}, // Left
        {1, 0, 0}, // Front
        {0, 1, 0}, // Right
        {-1, 0, 0}, // Back
        {0, 0, -1} // Down
    };
    public:
        Cube(string s = "OOOOOOOOOGGGWWWBBBYYYGGGWWWBBBYYYGGGWWWBBBYYYRRRRRRRRR") {

            if (s.size() != 54) {
                throw invalid_argument("Cube string must be 54 characters long.");
            }

            /*
                +x is front -x is back
                +y is right -y is left
                +z is up -z is down
            */

            /* This is what the cube looks like

                      U U U                         0  1  2
                      U U U                         3  4  5
                      U U U                         6  7  8
                L L L F F F R R R B B B    9 10 11 12 13 14 15 16 17 18 19 20
                L L L F F F R R R B B B   21 22 23 24 25 26 27 28 29 30 31 32
                L L L F F F R R R B B B   33 34 35 36 37 38 39 40 41 42 43 44
                      D D D                        45 46 47
                      D D D                        48 49 50
                      D D D                        51 52 53

            */

            // Initialize the faces

            // Right face
            faces[0] = Piece(0, 1, 0, Colour::N, charToColour(s[28]), Colour::N, PieceType::Middle);
            
            // Left face
            faces[1] = Piece(0, -1, 0, Colour::N, charToColour(s[22]), Colour::N, PieceType::Middle);

            // Up face
            faces[2] = Piece(0, 0, 1, Colour::N, Colour::N, charToColour(s[4]), PieceType::Middle);

            // Down face
            faces[3] = Piece(0, 0, -1, Colour::N, Colour::N, charToColour(s[49]), PieceType::Middle);

            // Front face
            faces[4] = Piece(1, 0, 0, charToColour(s[25]), Colour::N, Colour::N, PieceType::Middle);

            // Back face
            faces[5] = Piece(-1, 0, 0, charToColour(s[31]), Colour::N, Colour::N, PieceType::Middle);

            // Initialize the edges
            edges[0] = Piece(0, 1, 1, Colour::N, charToColour(s[16]), charToColour(s[5]), PieceType::Edge);
            edges[1] = Piece(-1, 0, 1, charToColour(s[19]), Colour::N, charToColour(s[1]), PieceType::Edge);
            edges[2] = Piece(0, -1, 1, Colour::N, charToColour(s[10]), charToColour(s[3]), PieceType::Edge);
            edges[3] = Piece(1, 0, 1, charToColour(s[13]), Colour::N, charToColour(s[7]), PieceType::Edge);
            edges[4] = Piece(0, 1, -1, Colour::N, charToColour(s[40]), charToColour(s[50]), PieceType::Edge);
            edges[5] = Piece(-1, 0, -1, charToColour(s[43]), Colour::N, charToColour(s[52]), PieceType::Edge);
            edges[6] = Piece(0, -1, -1, Colour::N, charToColour(s[34]), charToColour(s[48]), PieceType::Edge);
            edges[7] = Piece(1, 0, -1, charToColour(s[37]), Colour::N, charToColour(s[46]), PieceType::Edge);
            edges[8] = Piece(1, 1, 0, charToColour(s[26]), charToColour(s[27]), Colour::N, PieceType::Edge);
            edges[9] = Piece(-1, 1, 0, charToColour(s[30]), charToColour(s[29]), Colour::N, PieceType::Edge);
            edges[10] = Piece(-1, -1, 0, charToColour(s[32]), charToColour(s[21]), Colour::N, PieceType::Edge);
            edges[11] = Piece(1, -1, 0, charToColour(s[24]), charToColour(s[23]), Colour::N, PieceType::Edge);

            // Initialize the corners
            corners[0] = Piece(1, 1, 1, charToColour(s[14]), charToColour(s[15]), charToColour(s[8]), PieceType::Corner);
            corners[1] = Piece(-1, 1, 1, charToColour(s[18]), charToColour(s[17]), charToColour(s[2]), PieceType::Corner);
            corners[2] = Piece(-1, -1, 1, charToColour(s[20]), charToColour(s[9]), charToColour(s[0]), PieceType::Corner);
            corners[3] = Piece(1, -1, 1, charToColour(s[12]), charToColour(s[11]), charToColour(s[6]), PieceType::Corner);
            corners[4] = Piece(1, 1, -1, charToColour(s[38]), charToColour(s[39]), charToColour(s[47]), PieceType::Corner);
            corners[5] = Piece(-1, 1, -1, charToColour(s[42]), charToColour(s[41]), charToColour(s[53]), PieceType::Corner);
            corners[6] = Piece(-1, -1, -1, charToColour(s[44]), charToColour(s[33]), charToColour(s[51]), PieceType::Corner);
            corners[7] = Piece(1, -1, -1, charToColour(s[36]), charToColour(s[35]), charToColour(s[45]), PieceType::Corner);

            // Initialize the pieces
            for (int i = 0; i < 8; i++) {
                pieces.push_back(&corners[i]);
            }
            for (int i = 0; i < 12; i++) {
                pieces.push_back(&edges[i]);
            }
            for (int i = 0; i < 6; i++) {
                pieces.push_back(&faces[i]);
            }
        }

        vector<Piece*> getFace(vector<int> facePos) {
            vector<Piece*> facePieces;

            // Loop over the pieces and check if their dot product with the face position is > 0
            for (int i = 0; i < 26; i++) {
                int dp = pieces[i]->getPos()[0] * facePos[0] + pieces[i]->getPos()[1] * facePos[1] + pieces[i]->getPos()[2] * facePos[2];
                if (dp > 0) {
                    facePieces.push_back(pieces[i]);
                }
            }
            
            return facePieces;
        }

        // done with unique pointers
        void rotateFace(vector<int> facePos, Matrix<3, 3> rotation) {

            rotatePieces(getFace(facePos), rotation);
        }

        // done with unique pointers
        void rotatePieces(vector<Piece*> facePieces, Matrix<3, 3> rotation) {

            for (int i = 0; i < 9; ++i) {

                facePieces[i]->rotate(rotation);
            }
        }

        void R() {rotateFace({0, 1, 0}, ROT_CW_XZ);}
        void Ri() {rotateFace({0, 1, 0}, ROT_CCW_XZ);}
        void L() {rotateFace({0, -1, 0}, ROT_CCW_XZ);}
        void Li() {rotateFace({0, -1, 0}, ROT_CW_XZ);}
        void U() {rotateFace({0, 0, 1}, ROT_CW_XY);}
        void Ui() {rotateFace({0, 0, 1}, ROT_CCW_XY);}
        void D() {rotateFace({0, 0, -1}, ROT_CCW_XY);}
        void Di() {rotateFace({0, 0, -1}, ROT_CW_XY);}
        void F() {rotateFace({1, 0, 0}, ROT_CW_YZ);}
        void Fi() {rotateFace({1, 0, 0}, ROT_CCW_YZ);}
        void B() {rotateFace({-1, 0, 0}, ROT_CCW_YZ);}
        void Bi() {rotateFace({-1, 0, 0}, ROT_CW_YZ);}

        void print() {
            int coordinates[6] {2, 1, 0, 1, 0, 2};

            for (int i = 0; i < 6; i++) {
                vector <Colour> faceColours;
                vector<Piece*> face = getFace(facePositions[i]);

                for (int j = 0; j < 9; j++) {

                    faceColours.push_back(face[j]->getColour()[coordinates[i]]);
                }

                for (int j = 0; j < 9; j++) {
                    cout << colorMap[faceColours[j]];
                    if (j % 3 == 2) {
                        cout << endl;
                    }
                }

                if (i == 0 || i == 4) {
                    cout << endl;
                }

            }
            cout << endl;
        }

    private:
        Colour charToColour(char c) {
            switch (c) {
                case 'Y':
                    return Colour::Y;
                case 'W':
                    return Colour::W;
                case 'R':
                    return Colour::R;
                case 'O':
                    return Colour::O;
                case 'B':
                    return Colour::B;
                case 'G':
                    return Colour::G;
                default:
                    return Colour::N;
            }
        }
};

#endif