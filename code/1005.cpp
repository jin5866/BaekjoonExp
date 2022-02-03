// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 

#include <iostream>
#include<iomanip>
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


int run() {
	int n, k;

	std::cin >> n >> k;

	
	std::vector<int> d(n,0);

	std::vector<int> cost(n);

	for (int& c : cost) {
		std::cin >> c;
	}

	std::vector<std::vector<int>> links(n, std::vector<int>(0));

	for (int i = 0; i < k; i++) {
		int a, b;
		std::cin >> a >> b;

		links[b-1].push_back(a-1);
	}

	int start;

	std::cin >> start;
	start--;
	std::queue<int> qu;
	std::set<int> se;
	d[start] = cost[start];

	qu.push(start);
	se.insert(start);

	int max = cost[start];

	while (!qu.empty()) {
		int now = qu.front();
		qu.pop();
		se.erase(now);

		for (int next : links[now]) {
			if (d[next] < d[now] + cost[next]) {
				d[next] = d[now] + cost[next];

				max = std::max(max, d[next]);
				if (se.find(next) == se.end()) {
					qu.push(next);
					se.insert(next);
				}

			}
			
			
		}
	}

	std::cout << max << "\n";

	return 0;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int t = 0;

	std::cin >> t;

	for (int i = 0; i < t; i++) {
		run();
	}


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
