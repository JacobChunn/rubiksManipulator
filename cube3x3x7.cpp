enum Colors { Orange, Red, Blue, Green, White, Yellow};
enum InitType { Default, Empty };

struct Cubie {

};

struct Corner {

};

struct Edge {
	bool isLong;
	Colors* colors;
};

struct Cube3x3x7 {
	int front[3][7];
	int back[3][7];
	int left[3][7];
	int right[3][7];
	int top[3][3];
	int bottom[3][3];

};

void main() {

}



class Cube {
	private:
		Cube3x3x7 solvedCube;
	public:
		Cube(InitType type) {
			switch(type) {
				case Empty:

					break;
				default:
			}
		}

		void setCubeToSolved() {

		}

		void setCubeToEmpty() {

		}
};