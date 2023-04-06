#include <string.h>

#define CORNER_CUBIES 3
#define CORNER_COUNT 8

#define EDGE_LONG_CUBIES 3
#define EDGE_LONG_COUNT 8

#define EDGE_SHORT_CUBIES 1
#define EDGE_SHORT_COUNT 4

#define DIR_COUNT 6
#define BIDIRECTIONAL_MOVE_COUNT 36
#define MOVEDirection_COUNT 12

enum Color { Orange, Red, Blue, Green, White, Yellow};
enum InitType { Default, Empty };
enum Direction { Front, Back, Left, Right, Up, Down};
enum MoveType { mtWhole, mtSliceInner, mtSliceMiddle, mtSliceOuter };
enum MoveDirection { mdFront, mdFronti, mdBack, mdBacki, mdLeft, mdLefti,
	mdRight, mdRighti, mdUp, mdUpi, mdDown, mdDowni};


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
		// move[moveDirection][move][Corner/Edge Cycle (or 0/1 respectively)]
		int**** move;
		Direction** nextDirTables;

	public:
		Cube(InitType type) {

			nextDirTablesInit();

			switch(type) {
				case Empty:
					setCubeToEmpty();
					break;
				default:
					setCubeToSolved();
			}
		}

		void nextDirTablesInit() {
			Direction** dirCycles = new Direction*[MOVEDirection_COUNT];
			for (int i = 0; i < MOVEDirection_COUNT; i++) {
				dirCycles[i] = new Direction[4];
			}
			
			dirCycles[mdFront] = (Direction[]){Up, Right, Down, Left};
			dirCycles[mdFronti] = (Direction[]){Left, Down, Right, Up};

			dirCycles[mdBack] = (Direction[]){Up, Right, Down, Left};
			dirCycles[mdBacki] = (Direction[]){Left, Down, Right, Up};
			
			dirCycles[mdLeft] = (Direction[]){Up, Front, Down, Back};
			dirCycles[mdLefti] = (Direction[]){Back, Down, Front, Up};

			dirCycles[mdRight] = (Direction[]){Up, Back, Down, Front};
			dirCycles[mdRighti] = (Direction[]){Front, Down, Back, Up};

			dirCycles[mdUp] = (Direction[]){Back, Right, Front, Left};
			dirCycles[mdUpi] = (Direction[]){Left, Front, Right, Back};

			dirCycles[mdDown] = (Direction[]){Back, Left, Front, Right};
			dirCycles[mdDowni] = (Direction[]){Right, Front, Left, Back};

			ComputeNextDirArray(dirCycles, 4);
		}

		void ComputeNextDirArray(Direction** dirCycles, int cycleLen) {
			for (int j = 0; j < MOVEDirection_COUNT; j++) {
				for (int i = 0; i < DIR_COUNT; i++) {
					nextDirTables[j][i] = (Direction)i;
				}

				for (int i = 0; i < cycleLen; i++) {
					nextDirTables[j][dirCycles[j][i]] = dirCycles[j][(i + 1) % cycleLen];
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
		void cycleWhole(T (&pieceArr)[], int pieceCycle[], MoveDirection moveDirection, int arrLen) {
			T temp = pieceArr[0];
			for (int i = 0; i < arrLen - 1; i++) {
				pieceArr[i] = pieceArr[i + 1];
				pieceArr[i].dirPrimary = nextDirTables[ pieceArr[i].dirPrimary ];
				pieceArr[i].dirSecondary = nextDirTables[ pieceArr[i].dirSecondary ];
			}
			pieceArr[arrLen - 1] = temp;
		}

		template <typename T>
		void cycleMidOrInSlice(T (&pieceArr)[], int slice, int pieceCycle[], MoveDirection moveDirection, int arrLen) {
			T temp = pieceArr[0].cubies[slice];
			for (int i = 0; i < arrLen - 1; i++) {
				pieceArr[i].cubies[slice] = pieceArr[i + 1].cubies[slice];
			}
			pieceArr[arrLen - 1].cubies[slice] = temp;
		}

		template <typename T>
		void cycleOutSlice(T (&pieceArr)[], int slice, int pieceCycle[], MoveDirection moveDirection, int arrLen) {
			T temp = pieceArr[0].cubies[slice];
			for (int i = 0; i < arrLen - 1; i++) {
				pieceArr[i].cubies[slice] = pieceArr[i + 1].cubies[slice];
				pieceArr[i].dirSecondary = nextDirTables[ pieceArr[i].dirSecondary ];
			}
			pieceArr[arrLen - 1] = temp;
		}

		void cycleWholeHelper(int cornerCycle[], int edgeCycle[], MoveDirection mt, int len) {
			cycleWhole<Corner>(cube.corners, cornerCycle, mt, len);
			cycleWhole<Edge>(cube.edges, edgeCycle, mt, len);
		}

		void cycleMidOrInSliceHelper() {

		}

		void cycleOutSliceHelper() {
			
		}

		void moveInit() {
			move = new int***[MOVEDirection_COUNT];
			for (int i = 0; i < MOVEDirection_COUNT; i++) {
				move[i] = new int**[4];
				for (int j = 0; j < 4; j++) {
					move[i][j] = new int*[2];
				}
			}
			move[mdFront][mtWhole][0] = (int[]){3, 2, 6, 7};
			move[mdFront][mtWhole][1] = (int[]){2, 6, 10, 7};

			// TO DO: Finish inputting correct corner/edge cycle values
			// EDIT: How does slicing formatting work?
			move[mdFront][mtWhole][0] = (int[]){3, 2, 6, 7};
			move[mdFront][mtWhole][1] = (int[]){2, 6, 10, 7};

			move[mdFront][mtWhole][0] = (int[]){3, 2, 6, 7};
			move[mdFront][mtWhole][1] = (int[]){2, 6, 10, 7};

			move[mdFront][mtWhole][0] = (int[]){3, 2, 6, 7};
			move[mdFront][mtWhole][1] = (int[]){2, 6, 10, 7};
		}

		void front() {
			int cornerCycle[] = {3, 2, 6, 7};
			int edgeCycle[] = {2, 6, 10, 7};
			cycleWholeHelper(cornerCycle, edgeCycle, mdFront, 4);
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

		void frontS1() {
			cycleSlice<Corner>();
		}
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