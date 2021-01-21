// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include<algorithm>
#include <vector>
#include <utility>

class board {
public :
	board() {
		int a;
		int b;
		std::cin >> a;
		std::cin >> b;
		bo = std::vector<std::vector<char>>( a,std::vector<char>(b) );

		for (int i = 0; i < a;i++) {
			for (int j = 0; j < b;j++) {
				char tmp;
				std::cin >> tmp;
				bo[i][j] = tmp;

				if (tmp == 'R') {
					Rpose = std::make_pair(i, j);
					bo[i][j] = '.';
				}
				else if (tmp == 'B') {
					Bpose = std::make_pair(i, j);
					bo[i][j] = '.';
				}
			}
		}

	}

	board(board&) = default;
	board(board&&) = default;
	board& operator= (board&) = default;
	board& operator= (board&&) = default;


	void print() {
		for (auto& e : bo) {
			for (char& c : e) {
				std::cout << c;
			}
			std::cout << std::endl;
		}
	}


	//성공시,blue 가 들어가버렸을시
	std::pair<bool,bool> left() {
		resetPose();
		bool canmove = true;


		bool rvalide = true;
		bool bvalide = true;

		bool rresult = false;
		bool bresult = false;

		//redmove
		canmove = true;
		while (canmove && rvalide) {
			if (bvalide && Rpose.first == Bpose.first && (Rpose.second - 1) == Bpose.second) {
				canmove = false;
			}
			else if (bo[Rpose.first][Rpose.second - 1] == '.') {
				Rpose.second -= 1;
			}
			else if (bo[Rpose.first][Rpose.second - 1] == 'O') {
				rresult = true;
				rvalide = false;
			}
			else if (bo[Rpose.first][Rpose.second - 1] == '#') {
				canmove = false;
			}
		}
		//blue
		canmove = true;
		while (canmove && bvalide) {
			if (rvalide&&Bpose.first == Rpose.first && (Bpose.second - 1) == Rpose.second) {
				canmove = false;
			}
			else if (bo[Bpose.first][Bpose.second - 1] == '.') {
				Bpose.second -= 1;
			}
			else if (bo[Bpose.first][Bpose.second - 1] == 'O') {
				bresult = true;
				bvalide = false;
			}
			else if (bo[Bpose.first][Bpose.second - 1] == '#') {
				canmove = false;
			}
		}
		//redmove
		canmove = true;
		while (canmove && rvalide) {
			if (bvalide && Rpose.first == Bpose.first && (Rpose.second - 1) == Bpose.second) {
				canmove = false;
			}
			else if (bo[Rpose.first][Rpose.second - 1] == '.') {
				Rpose.second -= 1;
			}
			else if (bo[Rpose.first][Rpose.second - 1] == 'O') {
				rresult = true;
				rvalide = false;
			}
			else if (bo[Rpose.first][Rpose.second - 1] == '#') {
				canmove = false;
			}
		}

		bo[Rpose.first][Rpose.second] = 'R';
		bo[Bpose.first][Bpose.second] = 'B';

		return std::make_pair(rresult, bresult);
	}

	std::pair<bool, bool> right() {
		resetPose();
		bool canmove = true;


		bool rvalide = true;
		bool bvalide = true;

		bool rresult = false;
		bool bresult = false;

		//redmove
		canmove = true;
		while (canmove&&rvalide) {
			if (bvalide&&Rpose.first == Bpose.first && (Rpose.second + 1) == Bpose.second) {
				canmove = false;
			}
			else if (bo[Rpose.first][Rpose.second + 1] == '.') {
				Rpose.second += 1;
			}
			else if (bo[Rpose.first][Rpose.second + 1] == 'O') {
				rresult = true;
				rvalide = false;
			}
			else if (bo[Rpose.first][Rpose.second + 1] == '#') {
				canmove = false;
			}
		}
		//blue
		canmove = true;
		while (canmove&& bvalide) {
			if (rvalide&&Bpose.first == Rpose.first && (Bpose.second + 1) == Rpose.second) {
				canmove = false;
			}
			else if (bo[Bpose.first][Bpose.second + 1] == '.') {
				Bpose.second += 1;
			}
			else if (bo[Bpose.first][Bpose.second + 1] == 'O') {
				bresult = true;
				bvalide = false;
			}
			else if (bo[Bpose.first][Bpose.second + 1] == '#') {
				canmove = false;
			}
		}
		//redmove
		canmove = true;
		while (canmove&&rvalide) {
			if (bvalide && Rpose.first == Bpose.first && (Rpose.second + 1) == Bpose.second) {
				canmove = false;
			}
			else if (bo[Rpose.first][Rpose.second + 1] == '.') {
				Rpose.second += 1;
			}
			else if (bo[Rpose.first][Rpose.second + 1] == 'O') {
				rresult = true;
				rvalide = false;
			}
			else if (bo[Rpose.first][Rpose.second + 1] == '#') {
				canmove = false;
			}
		}

		bo[Rpose.first][Rpose.second] = 'R';
		bo[Bpose.first][Bpose.second] = 'B';

		return std::make_pair(rresult, bresult);
	}

	std::pair<bool, bool> up() {
		resetPose();

		bool canmove = true;


		bool rvalide = true;
		bool bvalide = true;

		bool rresult = false;
		bool bresult = false;

		//redmove
		canmove = true;
		while (canmove && rvalide) {
			if (bvalide && (Rpose.first - 1) == Bpose.first && (Rpose.second) == Bpose.second) {
				canmove = false;
			}
			else if (bo[Rpose.first - 1][Rpose.second] == '.') {
				Rpose.first -= 1;
			}
			else if (bo[Rpose.first - 1][Rpose.second] == 'O') {
				rresult = true;
				rvalide = false;
			}
			else if (bo[Rpose.first- 1][Rpose.second] == '#') {
				canmove = false;
			}
		}
		//blue
		canmove = true;
		while (canmove && bvalide) {
			if (rvalide && (Bpose.first-1) == Rpose.first && (Bpose.second ) == Rpose.second) {
				canmove = false;
			}
			else if (bo[Bpose.first - 1][Bpose.second] == '.') {
				Bpose.first -= 1;
			}
			else if (bo[Bpose.first - 1][Bpose.second] == 'O') {
				bresult = true;
				bvalide = false;
			}
			else if (bo[Bpose.first - 1][Bpose.second] == '#') {
				canmove = false;
			}
		}
		//redmove
		canmove = true;
		while (canmove && rvalide) {
			if (bvalide && (Rpose.first - 1) == Bpose.first && (Rpose.second) == Bpose.second) {
				canmove = false;
			}
			else if (bo[Rpose.first - 1][Rpose.second] == '.') {
				Rpose.first -= 1;
			}
			else if (bo[Rpose.first - 1][Rpose.second] == 'O') {
				rresult = true;
				rvalide = false;
			}
			else if (bo[Rpose.first - 1][Rpose.second] == '#') {
				canmove = false;
			}
		}

		bo[Rpose.first][Rpose.second] = 'R';
		bo[Bpose.first][Bpose.second] = 'B';
		
		return std::make_pair(rresult, bresult);
	}

	std::pair<bool, bool> down() {
		resetPose();

		bool canmove = true;

		bool rvalide = true;
		bool bvalide = true;

		bool rresult = false;
		bool bresult = false;

		//redmove
		canmove = true;
		while (canmove && rvalide) {
			if (bvalide && (Rpose.first+1) == Bpose.first && (Rpose.second ) == Bpose.second) {
				canmove = false;
			}
			else if (bo[Rpose.first + 1][Rpose.second ] == '.') {
				Rpose.first += 1;
			}
			else if (bo[Rpose.first+ 1][Rpose.second ] == 'O') {
				rresult = true;
				rvalide = false;
			}
			else if (bo[Rpose.first + 1][Rpose.second ] == '#') {
				canmove = false;
			}
		}
		//blue
		canmove = true;
		while (canmove && bvalide) {
			if (rvalide && (Bpose.first+1) == Rpose.first && (Bpose.second ) == Rpose.second) {
				canmove = false;
			}
			else if (bo[Bpose.first + 1][Bpose.second ] == '.') {
				Bpose.first += 1;
			}
			else if (bo[Bpose.first+1][Bpose.second ] == 'O') {
				bresult = true;
				bvalide = false;
			}
			else if (bo[Bpose.first+ 1][Bpose.second ] == '#') {
				canmove = false;
			}
		}
		//redmove
		canmove = true;
		while (canmove && rvalide) {
			if (bvalide && (Rpose.first + 1) == Bpose.first && (Rpose.second) == Bpose.second) {
				canmove = false;
			}
			else if (bo[Rpose.first + 1][Rpose.second] == '.') {
				Rpose.first += 1;
			}
			else if (bo[Rpose.first + 1][Rpose.second] == 'O') {
				rresult = true;
				rvalide = false;
			}
			else if (bo[Rpose.first + 1][Rpose.second] == '#') {
				canmove = false;
			}
		}

		bo[Rpose.first][Rpose.second] = 'R';
		bo[Bpose.first][Bpose.second] = 'B';

		return std::make_pair(rresult, bresult);
	}
	void setBoard(const std::pair<std::pair<int, int>, std::pair<int, int>>& pose) {
		setBoard(pose.first, pose.second);
	}
	void setBoard(const std::pair<int, int>& rp, const std::pair<int, int>& bp) {
		resetPose();

		Rpose = rp;
		Bpose = bp;
	}
	std::pair<int, int>& getRpose() {
		return Rpose;
	}

	std::pair<int, int>& getBpose() {
		return Bpose;
	}

	void resetPose() {
		bo[Rpose.first][Rpose.second] = '.';
		bo[Bpose.first][Bpose.second] = '.';
	}
private:
	std::vector<std::vector<char>> bo;
	std::pair<int, int> Rpose;
	std::pair<int, int> Bpose;


};


int iscanout(board bo) {
	std::queue<std::pair<std::pair<std::pair<int, int>,std::pair<int, int>>,int>> bas{};
	bas.push(std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, int>{ {bo.getRpose(),bo.getBpose()}, 0 });
	while (!bas.empty()) {

		auto& now = bas.front();
		if (now.second == 10) {
			return -1;
		}

		bo.setBoard(now.first);
		auto leftre = bo.left();
		if (leftre.second) {
			
		}
		else if (leftre.first) {
			return now.second + 1;
		}
		else {
			bas.push({ {bo.getRpose(),bo.getBpose()}, now.second + 1 });
		}
		bo.setBoard(now.first);
		auto rightre = bo.right();
		if (rightre.second) {
			
		}
		else if (rightre.first) {
			return now.second + 1;
		}
		else {
			bas.push({ {bo.getRpose(), bo.getBpose()}, now.second + 1 });
		}
		bo.setBoard(now.first);
		auto upre = bo.up();
		if (upre.second) {
			
		}
		else if (upre.first) {
			return now.second + 1;
		}
		else {
			bas.push({ { bo.getRpose(), bo.getBpose() }, now.second + 1 });
		}

		bo.setBoard(now.first);
		auto downre = bo.down();

		if (downre.second) {
			
		}
		else if (downre.first) {
			return now.second + 1;
		}
		else {
			bas.push({ { bo.getRpose(), bo.getBpose()}, now.second + 1 });
		}
		bas.pop();
	}

	return -1;

}


int main()
{


	board b{};
	int count = iscanout(b);
	std::cout << count << std::endl;



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
