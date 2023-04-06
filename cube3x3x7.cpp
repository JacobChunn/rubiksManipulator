#include <string.h>

#define CORNER_CUBIES 3
#define CORNER_COUNT 8

#define EDGE_LONG_CUBIES 3
#define EDGE_LONG_COUNT 8

#define EDGE_SHORT_CUBIES 1
#define EDGE_SHORT_COUNT 4

#define DIR_COUNT 6
#define BIDIRECTIONAL_MOVE_COUNT 36
#define MOVETYPE_COUNT 12

enum Color { Orange, Red, Blue, Green, White, Yellow};
enum InitType { Default, Empty };
enum Direction { Front, Back, Left, Right, Up, Down};
enum Moves { mFront, mBack, mLeft, mRight, mUp, mDown,
	mFrontS1, mBackS1, mLeftS1, mRightS1, mUpS1, mDownS1,
	mFrontS2, mBackS2, mLeftS2, mRightS2, mUpS2, mDownS2,
	mFrontS2, mBackS2, mLeftS2, mRightS2, mUpS2, mDownS2 };
enum MoveTypes { mtFront, mtFronti, mtBack, mtBacki, mtLeft, mtLefti,
	mtRight, mtRighti, mtUp, mtUpi, mtDown, mtDowni};


struct Cubie {
	Color* colors;
};

struct Corner {
	Direction dirPrimary;
	Direction dirSecondary;
	Cubie* cubies;
};

struct Edge {
	bool isLong;
	Direction dirPrimary;
	Direction dirSecondary;
	Cubie* cubies;
};

struct Cube3x3x7 {
	Corner corners[8];
	Edge edges[12];
};

void main() {

}



class Cube {

	private:
		Cube3x3x7 cube;
		Direction** nextDirTable;

	public:
		Cube(InitType type) {

			nextDirTableInit();

			switch(type) {
				case Empty:
					setCubeToEmpty();
					break;
				default:
					setCubeToSolved();
			}
		}

		void nextDirTableInit() {
			Direction** dirCycles = new Direction*[MOVETYPE_COUNT];
			for (int i = 0; i < MOVETYPE_COUNT; i++) {
				dirCycles[i] = new Direction[4];
			}
			
			dirCycles[mtFront] = (Direction[]){Up, Right, Down, Left};
			dirCycles[mtFronti] = (Direction[]){Left, Down, Right, Up};

			dirCycles[mtBack] = (Direction[]){Up, Right, Down, Left};
			dirCycles[mtBacki] = (Direction[]){Left, Down, Right, Up};
			
			dirCycles[mtLeft] = (Direction[]){Up, Front, Down, Back};
			dirCycles[mtLefti] = (Direction[]){Back, Down, Front, Up};

			dirCycles[mtRight] = (Direction[]){Up, Back, Down, Front};
			dirCycles[mtRighti] = (Direction[]){Front, Down, Back, Up};

			dirCycles[mtUp] = (Direction[]){Back, Right, Front, Left};
			dirCycles[mtUpi] = (Direction[]){Left, Front, Right, Back};

			dirCycles[mtDown] = (Direction[]){Back, Left, Front, Right};
			dirCycles[mtDowni] = (Direction[]){Right, Front, Left, Back};

			ComputeNextDirArray(dirCycles, 4);
		}

		void ComputeNextDirArray(Direction** dirCycles, int cycleLen) {
			for (int j = 0; j < MOVETYPE_COUNT; j++) {
				for (int i = 0; i < DIR_COUNT; i++) {
					nextDirTable[j][i] = (Direction)i;
				}

				for (int i = 0; i < cycleLen; i++) {
					nextDirTable[j][dirCycles[j][i]] = dirCycles[j][(i + 1) % cycleLen];
				}	
			}
		}

		void setCubeToSolved() {

			setCubeToEmpty();

			fillCorner(&cube.corners[0], Red, Green, Yellow, Back, Up);
			fillCorner(&cube.corners[1], Blue, Red, Yellow, Right, Up);
			fillCorner(&cube.corners[2], Orange, Blue, Yellow, Front, Up);
			fillCorner(&cube.corners[3], Green, Orange, Yellow, Left, Up);

			fillCorner(&cube.corners[4], Green, Red, White, Left, Down);
			fillCorner(&cube.corners[5], Red, Blue, White, Back, Down);
			fillCorner(&cube.corners[6], Blue, Orange, White, Right, Down);
			fillCorner(&cube.corners[7], Orange, Green, White, Front, Down);

			fillLongEdge(&cube.edges[0], Red, Yellow, Back, Up);
			fillLongEdge(&cube.edges[1], Blue, Yellow, Right, Up);
			fillLongEdge(&cube.edges[2], Orange, Yellow, Front, Up);
			fillLongEdge(&cube.edges[3], Green, Yellow, Left, Up);

			fillShortEdge(&cube.edges[4], Red, Green, Back, Left);
			fillShortEdge(&cube.edges[5], Blue, Red, Right, Back);
			fillShortEdge(&cube.edges[6], Orange, Blue, Front, Right);
			fillShortEdge(&cube.edges[7], Green, Orange, Left, Front);

			fillLongEdge(&cube.edges[8], Red, White, Back, Down);
			fillLongEdge(&cube.edges[9], Blue, White, Right, Down);
			fillLongEdge(&cube.edges[10], Orange, White, Front, Down);
			fillLongEdge(&cube.edges[11], Green, White, Left, Down);
		}

		void setCubeToEmpty() {

			for (int i = 0; i < CORNER_COUNT; i++) {
				cube.corners[i].cubies = new Cubie[CORNER_CUBIES];

				cube.corners[i].cubies[0].colors = new Color[3];
				for (int j = 1; j < CORNER_CUBIES; j++) {
					cube.corners[i].cubies[j].colors = new Color[2];
				}
			}

			int edgeIter = 0;
			for (int i = 0; i < EDGE_LONG_COUNT / 2; i++, edgeIter++) {
				cube.edges[edgeIter].cubies = new Cubie[EDGE_LONG_CUBIES];

				cube.edges[edgeIter].cubies[0].colors = new Color[2];
				for (int j = 1; j < EDGE_LONG_CUBIES; j++) {
					cube.edges[edgeIter].cubies[j].colors = new Color[1];
				}
			}

			for (int i = 0; i < EDGE_SHORT_COUNT; i++, edgeIter++) {
				cube.edges[edgeIter].cubies = new Cubie[EDGE_SHORT_COUNT];

				cube.edges[edgeIter].cubies[0].colors = new Color[2];
			}

			for (int i = 0; i < EDGE_LONG_COUNT / 2; i++, edgeIter++) {
				cube.edges[edgeIter].cubies = new Cubie[EDGE_LONG_CUBIES];

				cube.edges[edgeIter].cubies[0].colors = new Color[2];
				for (int j = 1; j < EDGE_LONG_CUBIES; j++) {
					cube.edges[edgeIter].cubies[j].colors = new Color[1];
				}
			}
		}

		void fillCorner(Corner* c, Color col0, Color col1, Color col2,
			Direction col0dir, Direction col2dir) {

			c->dirPrimary = col2dir;
			c->dirSecondary = col0dir;
			c->cubies[0].colors[2] = col2;
			for (int i = 0; i < 3; i++) {
				c->cubies[i].colors[0] = col0;
				c->cubies[i].colors[1] = col1;
			}
		}

		void fillLongEdge(Edge* e, Color col0, Color col1, Direction col0dir,
			Direction col1dir) {

			e->dirPrimary = col1dir;
			e->dirSecondary = col0dir;
			e->cubies[0].colors[1] = col1;
			for (int i = 0; i < 3; i++) {
				e->cubies[i].colors[0] = col0;
			}
		}

		void fillShortEdge(Edge* e, Color col0, Color col1, Direction col0dir,
			Direction col1dir) {

			e->dirPrimary = col1dir;
			e->dirSecondary = col0dir;
			e->cubies[0].colors[0] = col0;
			e->cubies[0].colors[1] = col1;
		}

		template <typename T>
		void cycle(int* pieceArr, Direction* dirArr, int arrLen) {
			Direction nextDirTable[DIR_COUNT];

			// Avoids Warp Divergence if ran on GPU
			for (int i = 0; i < DIR_COUNT; i++) {
				nextDirTable[i] = i;
			}

			for (int i = 0; i < arrLen; i++) {
				nextDirTable[ dirArr[i] ] = dirArr[ (i + 1) % 4 ];
			}

			T temp = arr[0];
			for (int i = 0; i < arrLen - 1; i++) {
				arr[i] = arr[i + 1];
				arr[i].dirPrimary = nextDirTable[ arr[i].dirPrimary ];
				arr[i].dirSecondary = nextDirTable[ arr[i].dirSecondary ];
			}
			arr[arrLen - 1] = temp;
		}

		void front(bool inverted, Direction* nextDirArray) {
			//TODO: put nextDirTable precomputed in move function

			int pieceCycle[] = {4, 3, 7, 8};
			Direction dirCycle[] = {Up, Right, Down, Left};
			cycle<Corner>(pieceCycle, dirCycle, 4);
		}
		void back()
		void left()
		void right()
		void up()
		void down()

		void fronti()
		void backi()
		void lefti()
		void righti()
		void upi()
		void downi()

		void frontS1()
		void backS1()
		void leftS1()
		void rightS1()
		void upS1()
		void downS1()

		void frontS1i()
		void backS1i()
		void leftS1i()
		void rightS1i()
		void upS1i()
		void downS1i()

		void frontS2()
		void backS2()
		void leftS2()
		void rightS2()
		void upS2()
		void downS2()

		void frontS2i()
		void backS2i()
		void leftS2i()
		void rightS2i()
		void upS2i()
		void downS2i()

		void frontS3()
		void backS3()
		void leftS3()
		void rightS3()
		void upS3()
		void downS3()

		void frontS3i()
		void backS3i()
		void leftS3i()
		void rightS3i()
		void upS3i()
		void downS3i()

		~Cube() {

		}
};