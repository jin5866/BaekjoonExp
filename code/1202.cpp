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

struct cmp {
	bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
		return a.second < b.second;
	}

};


int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
	std::vector<std::pair<int, int>> gems;
	std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, cmp> qu;
	
	int n, k;

	std::cin >> n >> k;

	for (int i = 0; i < n; i++) {
		int a, b;
		std::cin >> a >> b;

		gems.push_back({ a,b });
	}

	std::sort(gems.begin(), gems.end(),std::less<std::pair<int,int>>());

	std::vector<int> bagcappa(k);

	for (int i = 0; i < k; i++) {
		int n;
		std::cin >> n;
		bagcappa[i] = n;

	}

	std::sort(bagcappa.begin(), bagcappa.end(),std::less<int>());

	long long int result = 0;

	int i = 0;

	for (int cap : bagcappa) {
		for (; i < n&& gems[i].first <= cap ; i++) {
			qu.push(gems[i]);
		}
		if (qu.size() > 0) {

			result += qu.top().second;
			qu.pop();
		}
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
