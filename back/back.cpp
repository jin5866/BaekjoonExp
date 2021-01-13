// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include<algorithm>
#include <vector>
#include <utility>

enum class Dir : int {
	right = 0 ,
	left,
	up,
	down
};

bool operator== (std::pair<int, int>& a, std::pair<int, int>& b) {
	return (a.first == b.first) && (a.second == b.second);
}

std::pair<int, int> operator+ (std::pair<int, int>& a, std::pair<int, int>& b) {
	return std::pair<int, int>{a.first + b.first, a.second + b.second};
}

class board {
	
public :
	board() {
		std::cin >> size;

		int applecount;
		std::cin >> applecount;
		apples = std::vector<std::pair<int, int>>( applecount ,std::pair<int,int>(0,0));
		for (auto& apple : apples) {
			std::cin >> apple.first;
			std::cin >> apple.second;
		}

		int movecount;
		std::cin >> movecount;
		
		for (int i = 0; i < movecount; i++) {
			int turn;
			char direction;

			std::cin >> turn;
			std::cin >> direction;
			moves.push(std::pair<int, char>(turn, direction));
		}

		snake.push_back({ 1,1 });

		dir = Dir::right;
		time = 0;
	}

	
	board(board&) = default;
	board(board&&) = default;
	board& operator= (board&) = default;
	board& operator= (board&&) = default;

	/*
	void print() {
		for (auto& e : bo) {
			for (char& c : e) {
				std::cout << c;
			}
			std::cout << std::endl;
		}
	}*/

	bool next() {
		time += 1;
		auto& head = snake.back();
		std::pair<int, int> newhead;

		switch (dir)
		{
		case Dir::right:
			newhead = head + right;
			break;
		case Dir::left:
			newhead = head + left;
			break;
		case Dir::up:
			newhead = head + up;
			break;
		case Dir::down:
			newhead = head + down;
			break;
		default:
			break;
		}

		if (!isin(newhead)) {
			return false;
		}

		bool appleeat = false;
		for (auto apple = apples.begin(); apple != apples.end();apple++) {
			if (apple[0] == newhead) {
				appleeat = true;
				apples.erase(apple);
				break;
			}
		}

		if (isselfblock(newhead, snake)) {
			return false;
		}

		if (!appleeat) {
			snake.erase(snake.begin());
		}
		

		snake.push_back(newhead);

		return true;
		
	}
	
	bool isin(const std::pair<int, int>& a) {
		return (a.first <= size) && (a.first > 0) && (a.second <= size) && (a.second > 0);
	}

	

	bool isselfblock(const std::pair<int, int>& newhead, const std::vector<std::pair<int, int>>& body) {
		for (auto& block : body) {
			if (block == newhead) {
				return true;
			}
		}
		return false;
	}

	int simulateall() {
		while (next()) {
			if ((!moves.empty()) && moves.front().first == time) {
				switch (dir)
				{
				case Dir::right:
					if (moves.front().second == 'D') {
						dir = Dir::down;
					}
					else {
						dir = Dir::up;
					}
					break;
				case Dir::left:
					if (moves.front().second == 'D') {
						dir = Dir::up;
					}
					else {
						dir = Dir::down;
					}
					break;
				case Dir::up:
					if (moves.front().second == 'D') {
						dir = Dir::right;
					}
					else {
						dir = Dir::left;
					}
					break;
				case Dir::down:
					if (moves.front().second == 'D') {
						dir = Dir::left;
					}
					else {
						dir = Dir::right;
					}
					break;
				default:
					break;
				}

				moves.pop();
			}
		}

		return time;
	}


private:
	int size;
	std::vector<std::pair<int, int>> snake;
	std::vector<std::pair<int, int>> apples;
	std::queue<std::pair<int, char>> moves;
	Dir dir;
	int time;

	std::pair<int, int> right = std::pair<int, int>{0, 1};
	std::pair<int, int> left = std::pair<int, int>{ 0, -1 };
	std::pair<int, int> up = std::pair<int, int>{ -1, 0 };
	std::pair<int, int> down = std::pair<int, int>{ 1, 0 };

};




int main()
{


	board b{};
	std::cout << b.simulateall() << std::endl;


}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
