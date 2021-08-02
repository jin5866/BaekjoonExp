// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 

#include <iostream>
#include<bitset>
#include <queue>
//#include<priority_queue>
#include<stack>
#include<algorithm>
#include <vector>
#include <utility>
#include<set>
#include<unordered_set>
#include<map>
#include<memory>
#include<string>
#include<algorithm>

template<typename T>
void debugprint(T t) {
	std::cout << t;
}

const int normal = 0;
const int red = 1;
const int blue = 2;

const int right = 1;
const int left = 2;
const int up = 3;
const int down = 4;

class horse;

std::vector<std::vector<int>> bo;
std::vector<std::vector<int>> bocounter;
int N,K;

std::vector<horse> horses;
std::vector<std::vector<horse*>> horsepos;

class horse {
public:
	std::pair<int, int> pos;
	int dir;
	int index;

	horse* uphorse;
	horse* downhorse;

	void init(int a, int b, int dir, int index = 0) {
		pos = { a,b };
		this->dir = dir;
		uphorse = NULL;
		downhorse = NULL;
		this->index = index;

		if (horsepos[pos.first][pos.second]) {
			horse* top = horsepos[pos.first][pos.second]->top();
			top->uphorse = this;
			downhorse = top;
		}
		else {
			horsepos[pos.first][pos.second] = this;
		}
		bocounter[pos.first][pos.second]++;

	}

	void update() {
		std::pair<int, int> newpos = pos;

		if (downhorse) {
			downhorse->uphorse = NULL;
			downhorse = NULL;
		}
		else {
			horsepos[pos.first][pos.second] = NULL;
		}


		horse* bottom = this;
		switch (dir)
		{
		case right:
			newpos.second++;
			if (newpos.second > N || bo[newpos.first][newpos.second] == blue) {

				dir = left;
				newpos.second -= 2;

				if (newpos.second <= 0 || bo[newpos.first][newpos.second] == blue) {
					newpos = pos;
				}
				else if (bo[newpos.first][newpos.second] == red) {
					bottom = swap();
				}
			}
			else if (bo[newpos.first][newpos.second] == red) {
				bottom = swap();
			}
			else {

			}

			break;
		case left:

			newpos.second--;
			if (newpos.second <= 0 || bo[newpos.first][newpos.second] == blue) {

				dir = right;
				newpos.second += 2;

				if (newpos.second > N || bo[newpos.first][newpos.second] == blue) {
					newpos = pos;
				}
				else if (bo[newpos.first][newpos.second] == red) {
					bottom = swap();
				}
			}
			else if (bo[newpos.first][newpos.second] == red) {
				bottom = swap();
			}
			else {

			}

			break;
		case up:
			newpos.first--;
			if (newpos.first <= 0 || bo[newpos.first][newpos.second] == blue) {

				dir = down;
				newpos.first += 2;

				if (newpos.first > N || bo[newpos.first][newpos.second] == blue) {
					newpos = pos;
				}
				else if (bo[newpos.first][newpos.second] == red) {
					bottom = swap();
				}
			}
			else if (bo[newpos.first][newpos.second] == red) {
				bottom = swap();
			}
			else {

			}
			break;
		case down:
			newpos.first++;
			if (newpos.first > N || bo[newpos.first][newpos.second] == blue) {

				dir = up;
				newpos.first -= 2;

				if (newpos.first <= 0 || bo[newpos.first][newpos.second] == blue) {
					newpos = pos;
				}
				else if (bo[newpos.first][newpos.second] == red) {
					bottom = swap();
				}
			}
			else if (bo[newpos.first][newpos.second] == red) {
				bottom = swap();
			}
			else {

			}
			break;
		default:
			break;
		}

		//horsepos[pos.first][pos.second] = NULL;

		bottom->move(newpos.first, newpos.second);


		if (horsepos[newpos.first][newpos.second]) {
			
			horse* top = horsepos[newpos.first][newpos.second]->top();
			if (!horsepos[newpos.first][newpos.second]->isin(bottom)) {
				top->uphorse = bottom;
				bottom->downhorse = top;
			}
		}
		else {
			horsepos[newpos.first][newpos.second] = bottom;
		}


		
	}

	horse* swap() {
		horse* downhorestmp = downhorse;
		horse* uphorestmp = uphorse;
		uphorse = NULL;
		downhorse = NULL;

		if (uphorestmp) {
			horse* bottom = uphorestmp->swap();

			downhorse = uphorestmp;
			uphorestmp->uphorse = this;
			uphorse = NULL;
			bottom->downhorse = NULL;

			if (downhorestmp) {
				downhorestmp->uphorse = NULL;
			}

			return bottom;
		}
		else {
			if (downhorestmp) {
				downhorestmp->uphorse = NULL;
			}
			
			return this;
		}



	}

	bool isin(horse* h) {
		if (h == this) {
			return true;
		}
		else if (uphorse) {
			return uphorse->isin(h);
		}

		return false;
	}

	horse* top() {
		if (uphorse) {
			return uphorse->top();
		}

		else {
			return this;
		}
	}

	void move(int a, int b) {
		if (pos.first == a && pos.second == b) {
			return;
		}

		bocounter[pos.first][pos.second]--;
		bocounter[a][b]++;
		pos = { a,b };
		if (uphorse) {
			uphorse->move(a, b);
		}
	}

};

void print() {
	for (auto& hs : bocounter) {
		for (auto h : hs) {
			std::cout << h;
		}
		std::cout << std::endl;
	}

	for (auto& hs : horsepos) {
		for (auto h : hs) {
			horse* now = h;
			bool isprint = false;
			while (now) {
				isprint = true;
				std::cout << now->index;
				switch (now->dir)
				{
				case up:
					std::cout << "↑";
					break;
				case down:
					std::cout << "↓";
					break;
				case right:
					std::cout << "→";
					break;
				case left:
					std::cout << "←";
					break;
				default:
					break;
				}
				if (now = now->uphorse) {
					std::cout << "->";
				}
			}
			if (isprint) {
				std::cout << std::endl;
			}
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);

	std::cin >> N >> K;
	bo = std::vector<std::vector<int>>(N + 1, std::vector<int>(N + 1, 0));
	bocounter = bo;
	horsepos = std::vector<std::vector<horse*>>(N + 1, std::vector<horse*>(N + 1, (horse*)NULL));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			std::cin >> bo[i][j];
		}
	}

	horses = std::vector < horse>(K);
	for (int i = 0; i < K; i++) {
		int a, b, dir;
		std::cin >> a >> b >> dir;

		horses[i].init(a, b, dir,i+1);


	}

	bool isend = false;
	int result = -1;
	for (int i = 1; i <= 1000 && (!isend); i++) {
		for (horse& h : horses) {
			h.update();

			int maxcount = 0;
			for (horse& hh : horses) {
				maxcount = std::max(maxcount, bocounter[hh.pos.first][hh.pos.second]);
			}
			if (maxcount >= 4) {
				isend = true;
				result = i;
				break;
			}

			//print();
			//std::cout << std::endl;
		}
	}

	std::cout << result << std::endl;
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
