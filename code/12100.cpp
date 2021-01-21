#include <iostream>
#include <queue>
#include<algorithm>
#include <vector>

class board {
public :
	static board make_board() {
		int size;
		std::cin >> size;
		std::vector<std::vector<int>> a( size );
		for (auto& e : a) {
			e = std::vector<int>( size );
			for (int& i : e) {
				std::cin >> i;
			}
		}

		return board(a);
	}

	board(std::vector<std::vector<int>> bo) {
		this->bo = bo;
		this->size = bo.size();
	}

	board(board&) = default;
	board(board&&) = default;
	board& operator= (board&) = default;
	board& operator= (board&&) = default;

	void print() {
		for(auto& e :bo)
		{
			for (auto& i : e)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}
	}

	void left(){
		
		for (int i = 0; i < size; i++) {
			std::queue<int> line;
			for (int j = 0; j < size; j++) {
				if (bo[i][j] != 0) {
					line.push(bo[i][j]);
				}
			}
			int a = 0;
			if (!line.empty()) {
				a = line.front();
				line.pop();
			}
			for (int j = 0; j < size; j++) {
				if (a == 0){
					bo[i][j] = 0;
				}
				else{
					if ((!line.empty()) && (a == line.front())) {
						bo[i][j] = 2 * a;
						line.pop();
						a = 0;
						if (!line.empty()) {
							a = line.front();
							line.pop();
						}
						
					}
					else {
						bo[i][j] = a;
						a = 0;
						if (!line.empty()) {
							a = line.front();
							line.pop();
						}
					}

				}
			}
		}
	}

	void right(){
		for (int i = 0; i < size; i++) {
			std::queue<int> line;
			for (int j = size - 1; j >= 0; j--) {
				if (bo[i][j] != 0) {
					line.push(bo[i][j]);
				}
			}
			int a = 0;
			if (!line.empty()) {
				a = line.front();
				line.pop();
			}
			for (int j = size - 1; j >= 0; j--) {
				if (a == 0) {
					bo[i][j] = 0;
				}
				else {
					if ((!line.empty()) && (a == line.front())) {
						bo[i][j] = 2 * a;
						line.pop();
						a = 0;
						if (!line.empty()) {
							a = line.front();
							line.pop();
						}

					}
					else {
						bo[i][j] = a;
						a = 0;
						if (!line.empty()) {
							a = line.front();
							line.pop();
						}
					}

				}
			}
		}
	}

	void up() {
		for (int j = 0; j < size; j++) {
			std::queue<int> line;
			for (int i = 0; i < size; i++) {
				if (bo[i][j] != 0) {
					line.push(bo[i][j]);
				}
			}
			int a = 0;
			if (!line.empty()) {
				a = line.front();
				line.pop();
			}
			for (int i = 0; i < size; i++) {
				if (a == 0) {
					bo[i][j] = 0;
				}
				else {
					if ((!line.empty()) && (a == line.front())) {
						bo[i][j] = 2 * a;
						line.pop();
						a = 0;
						if (!line.empty()) {
							a = line.front();
							line.pop();
						}

					}
					else {
						bo[i][j] = a;
						a = 0;
						if (!line.empty()) {
							a = line.front();
							line.pop();
						}
					}

				}
			}
		}
	}

	void down() {
		for (int j = 0; j < size; j++) {
			std::queue<int> line;
			for (int i = size - 1; i >= 0; i--) {
				if (bo[i][j] != 0) {
					line.push(bo[i][j]);
				}
			}
			int a = 0;
			if (!line.empty()) {
				a = line.front();
				line.pop();
			}
			for (int i = size - 1; i >= 0; i--) {
				if (a == 0) {
					bo[i][j] = 0;
				}
				else {
					if ((!line.empty()) && (a == line.front())) {
						bo[i][j] = 2 * a;
						line.pop();
						a = 0;
						if (!line.empty()) {
							a = line.front();
							line.pop();
						}

					}
					else {
						bo[i][j] = a;
						a = 0;
						if (!line.empty()) {
							a = line.front();
							line.pop();
						}
					}

				}
			}
		}
	}

	int max() {
		int max = 0;
		for (auto& e : bo) {
			for (int& i : e) {
				if (i > max) {
					max = i;
				}
			}
		}

		return max;
	}
private:
	std::vector<std::vector<int>> bo;
	int size;


};

int get_max(int count, board b) {
	if (count == 0) {
		return b.max();
	}

	board left(b);
	board right(b);
	board up(b);
	board down(b);
	int c = count - 1;
	left.left();
	right.right();
	up.up();
	down.down();

	return std::max(std::max(get_max(c, left), get_max(c, right)), std::max(get_max(c, up), get_max(c, down)));
}

int main()
{

	board b = board::make_board();
	int max = get_max(5, b);
	std::cout << max << std::endl;



}