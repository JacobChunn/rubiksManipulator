enum Color { Orange, Red, Blue, Green, White, Yellow};
enum InitType { Default, Empty };
enum Direction { Back, Front, Left, Right, Up, Down};

struct Cubie {
	Direction direction;
	Color* colors;
};

struct Corner {
	Cubie* cubies;
};

struct Edge {
	bool isLong;
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

		const int cornerCubies = 3;
		const int cornerCount = 8;

		const int edgeLongCubies = 3;
		const int edgeLongCount = 8;

		const int edgeShortCubies = 1;
		const int edgeShortCount = 4;

	public:
		Cube(InitType type) {

			switch(type) {
				case Empty:
					setCubeToEmpty();
					break;
				default:
					setCubeToSolved();
			}
		}

		void setCubeToSolved() {

			setCubeToEmpty();

			fillCorner(&cube.corners[0], Back, Red, Green, Yellow);
			fillCorner(&cube.corners[1], Back, Blue, Red, Yellow);
			fillCorner(&cube.corners[2], Front, Orange, Blue, Yellow);
			fillCorner(&cube.corners[3], Front, Green, Orange, Yellow);

			fillCorner(&cube.corners[4], Back, Green, Red, White);
			fillCorner(&cube.corners[5], Back, Red, Blue, White);
			fillCorner(&cube.corners[6], Front, Blue, Orange, White);
			fillCorner(&cube.corners[7], Front, Orange, Green, White);

			fillLongEdge(&cube.edges[0], Back, Red, Yellow);
			fillLongEdge(&cube.edges[1], Right, Blue, Yellow);
			fillLongEdge(&cube.edges[2], Front, Orange, Yellow);
			fillLongEdge(&cube.edges[3], Left, Green, Yellow);

			fillShortEdge(&cube.edges[4], Back, Red, Green);
			fillShortEdge(&cube.edges[5], Back, Blue, Red);
			fillShortEdge(&cube.edges[6], Front, Orange, Blue);
			fillShortEdge(&cube.edges[7], Front, Green, Orange);

			fillLongEdge(&cube.edges[8], Back, Red, White);
			fillLongEdge(&cube.edges[9], Right, Blue, White);
			fillLongEdge(&cube.edges[10], Front, Orange, White);
			fillLongEdge(&cube.edges[11], Left, Green, White);
		}

		void setCubeToEmpty() {

			for (int i = 0; i < cornerCount; i++) {
				cube.corners[i].cubies = new Cubie[cornerCubies];

				cube.corners[i].cubies[0].colors = new Color[3];
				for (int j = 1; j < cornerCubies; j++) {
					cube.corners[i].cubies[j].colors = new Color[2];
				}
			}

			int edgeIter = 0;
			for (int i = 0; i < edgeLongCount / 2; i++, edgeIter++) {
				cube.edges[edgeIter].cubies = new Cubie[edgeLongCubies];

				cube.edges[edgeIter].cubies[0].colors = new Color[2];
				for (int j = 1; j < edgeLongCubies; j++) {
					cube.edges[edgeIter].cubies[j].colors = new Color[1];
				}
			}

			for (int i = 0; i < edgeShortCount; i++, edgeIter++) {
				cube.edges[edgeIter].cubies = new Cubie[edgeShortCubies];

				cube.edges[edgeIter].cubies[0].colors = new Color[2];
			}

			for (int i = 0; i < edgeLongCount / 2; i++, edgeIter++) {
				cube.edges[edgeIter].cubies = new Cubie[edgeLongCubies];

				cube.edges[edgeIter].cubies[0].colors = new Color[2];
				for (int j = 1; j < edgeLongCubies; j++) {
					cube.edges[edgeIter].cubies[j].colors = new Color[1];
				}
			}
		}

		void fillCorner(Corner* c, Direction dir, Color colA, Color colB,
			 Color colC) {

			c->cubies[0].colors[2] = colC;
			for (int i = 0; i < 3; i++) {
				c->cubies[i].direction = dir;
				c->cubies[i].colors[0] = colA;
				c->cubies[i].colors[1] = colB;
			}
		}

		void fillLongEdge(Edge* e, Direction dir, Color colA, Color colB) {

			e->cubies[0].colors[1] = colB;
			for (int i = 0; i < 3; i++) {
				e->cubies[i].direction = dir;
				e->cubies[i].colors[0] = colA;
			}
		}

		void fillShortEdge(Edge* e, Direction dir, Color colA, Color colB) {

			e->cubies[0].direction = dir;
			e->cubies[0].colors[0] = colA;
			e->cubies[0].colors[1] = colB;
		}

		void front()
		void fronti()
		void front2()
		void front2i()
		void front3()
		void front3i()

		void back()
		void backi()
		void back2()
		void back2i()
		void back3()
		void back3i()

		void left()
		void lefti()
		void left2()
		void left2i()
		void left3()
		void left3i()

		void right()
		void righti()
		void right2()
		void right2i()
		void right3()
		void right3i()

		void up()
		void upi()
		void up2()
		void up2i()
		void up3()
		void up3i()

		void down()
		void downi()
		void down2()
		void down2i()
		void down3()
		void down3i()

		~Cube() {

		}
};