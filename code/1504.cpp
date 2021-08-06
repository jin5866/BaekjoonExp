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

const int INF = 1000000000;

std::vector<int> dst(std::vector<std::vector<int>>& link, int from) {

	int N = link.size() - 1;
	std::vector<int> dis(link.size(), INF);
	dis[from] = 0;
	std::vector<bool> isvisit(link.size(), false);

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> qu;

	qu.push({ 0,from });

	while (!qu.empty()) {
		std::pair<int, int> now = qu.top();
		qu.pop();


		int nowpos = now.second;
		int nowcost = now.first;

		if (isvisit[nowpos]) continue;

		isvisit[nowpos] = true;

		for (int nextpos = 1; nextpos <= N; nextpos++ ) {
			if (link[nowpos][nextpos] < INF) {
				if (!isvisit[nextpos]) {
					if (dis[nextpos] > dis[nowpos] + link[nowpos][nextpos]) {
						dis[nextpos] = dis[nowpos] + link[nowpos][nextpos];
						qu.push({ dis[nextpos] ,nextpos });
					}
				}
			}
		}

	}

	return dis;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
	
	int N, E;
	std::cin >> N >> E;

	std::vector<std::vector<int>> link(N + 1, std::vector<int>(N + 1, INF));

	for (int i = 0; i < E; i++) {
		int a, b, c;

		std::cin >> a >> b >> c;

		link[a][b] = c;
		link[b][a] = c;
	}
	int v1, v2;
	std::cin >> v1 >> v2;

	std::vector<int> disfromv1 = dst(link, v1);
	std::vector<int> disfromv2 = dst(link, v2);

	int dis1 = std::min(INF, std::min(INF, disfromv1[1] + disfromv1[v2]) + disfromv2[N]);


	int dis2 = std::min(INF, disfromv2[1] + std::min(INF, disfromv2[v1] + disfromv1[N]));

	int result = std::min(dis1, dis2);

	if (result == INF) {
		result = -1;
	}

	std::cout << result << "\n";
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
