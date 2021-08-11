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

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
	
	int n , m;

	std::cin >> n >> m;

	std::vector<std::vector<std::pair<int,int>>> links(n + 1);
	std::vector<int> track(n + 1, 0);
	std::vector<int> cost(n + 1, 1000000000);

	std::vector<bool> isvisit(n + 1, false);

	for (int i = 1; i <= m; i++) {
		int a, b, c;

		std::cin >> a >> b >> c;

		links[a].push_back({ c,b });
	}

	int start, end;

	std::cin >> start >> end;

	cost[start] = 0;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> qu;

	qu.push({ 0,start });

	while (!qu.empty()) {

		int nowcost = qu.top().first;
		int nowpos = qu.top().second;

		qu.pop();


		if (isvisit[nowpos]) continue;

		isvisit[nowpos] = true;


		for (std::pair<int, int> link : links[nowpos]) {

			if (cost[nowpos] + link.first < cost[link.second]) {
				cost[link.second] = cost[nowpos] + link.first;
				track[link.second] = nowpos;
				qu.push({ cost[link.second] ,link.second });
			}
		}

	}

	std::stack<int> t;
	int nowp = end;
	
	t.push(end);

	while (true) {
		nowp = track[nowp];

		t.push(nowp);

		if (nowp == start) {
			break;
		}
	}



	std::cout << cost[end] << "\n";


	std::cout << t.size() << "\n";

	while (!t.empty()) {
		std::cout << t.top() << " ";
		t.pop();
	}

	std::cout << "\n";

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
