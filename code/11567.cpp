// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 

#include <iostream>
#include<bitset>
#include <queue>
#include<stack>
#include<algorithm>
#include <vector>
#include <utility>
#include<set>
#include<map>
#include<memory>
#include<string>

template<typename T>
void debugprint(T t) {
	std::cout << t;
}



std::vector<std::bitset<500>> bo;
std::vector<std::bitset<500>> bostate;
int n, m;
std::pair<short, short> start;
std::pair<short, short> end;

class state {
public:
	//std::vector<std::bitset<500>> bo;
	std::pair<short, short> pos;
	bool ismove;

	state( std::pair<short, short> pos,bool ismove = true) : pos(pos), ismove(ismove) {}
	state() = default;
	state(const state&) = default;
	state(state&&) = default;
	state& operator= (const state&) = default;
	state& operator= (state&&) = default;

	std::vector<std::pair<short, short>> getPossibleMove() {

		return getPossibleMove(pos);
	}

	static std::vector<std::pair<short, short>> getPossibleMove(std::pair<short, short> pos) {
		std::vector<std::pair<short, short>> result;
		//up
		if (pos.first > 0) {
			if (bostate[pos.first - 1][pos.second] || (pos.first - 1 == end.first && pos.second == end.second)) {
				result.push_back({ -1,0 });
			}
		}

		//left
		if (pos.second > 0) {
			if (bostate[pos.first][pos.second - 1] || (pos.first  == end.first && pos.second-1 == end.second)) {
				result.push_back({ 0,-1 });
			}
		}

		if (pos.first < n - 1) {
			if (bostate[pos.first + 1][pos.second] || (pos.first + 1 == end.first && pos.second == end.second)) {
				result.push_back({ 1,0 });
			}
		}

		if (pos.second < m - 1) {
			if (bostate[pos.first][pos.second + 1] || (pos.first == end.first && pos.second + 1 == end.second)) {
				result.push_back({ 0,1 });
			}
		}

		return result;
	}

	static bool isadjcentofend(std::pair<short, short> pos) {
		
		//up
		if (pos.first > 0) {
			if ( (pos.first - 1 == end.first && pos.second == end.second)) {
				return true;
			}
		}

		//left
		if (pos.second > 0) {
			if ( (pos.first == end.first && pos.second - 1 == end.second)) {
				return true;
			}
		}

		if (pos.first < n - 1) {
			if ((pos.first + 1 == end.first && pos.second == end.second)) {
				return true;
			}
		}

		if (pos.second < m - 1) {
			if ( (pos.first == end.first && pos.second + 1 == end.second)) {
				return true;
			}
		}

		return false;
	}


};

bool solve() {
	std::stack<state> qu;
	qu.push({ start , false});

	int routecount = state::getPossibleMove(end).size();
	bool endfirststate = bo[end.first][end.second];
	bool startfirststate = bo[start.first][start.second];
	//if (!bo[start.first][start.second]) return false;

	if (state::isadjcentofend(start)) {
		routecount += 1;
	}

	while (!qu.empty()) {
		state now = std::move(qu.top());
		qu.pop();

		if (now.pos == end && now.ismove) {
			if (endfirststate) {
				return routecount >= 2;
			}
			else {
				return true;
			}
		}

		auto routes = now.getPossibleMove();

		bostate[now.pos.first][now.pos.second] = false;

		for (auto route : routes) {
			qu.push({ {now.pos.first + route.first,now.pos.second + route.second} });
		}

	}

	return false;
}

int main()
{
	std::ios::sync_with_stdio(false);

	std::cin >> n >> m;
	
	bo = std::vector<std::bitset<500>>(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			std::cin >> c;

			bo[i][j] = (c == '.');
			//bostate[i][j] = bo[i][j];
		}
	}

	bostate = bo;

	std::cin >> start.first >> start.second;
	std::cin >> end.first >> end.second;

	start.first--;
	start.second--;
	end.first--;
	end.second--;
	//state start{ bo,start };

	
	bool result = solve();

	
	std::cout << ((result) ? "YES" : "NO") << std::endl;
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
