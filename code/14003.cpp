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
	
		
	int n;

	std::cin >> n;

	std::vector<int> a(n + 1, 0);

	std::vector<int> d(n + 1, 0);

	std::vector<int> parent(n + 1, 0);

	std::vector<std::pair<int,std::pair<int,int>>> dd;

	dd.push_back({ 0,{0,0} }); //count, {velue,index}

	int max = 0;
	int maxidx = 0;

	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];

	}

	for (int i = 1; i <= n; i++) {
		a[i];



		int left = 0;

		int right = dd.size() - 1;
		int mid = (left + right) / 2;

		while ( right - left > 1) {
			mid = (left + right) / 2;

			if (dd[mid].second.first >= a[i]) {
				right = mid;
			}
			else {
				left = mid;
			}
		}

		if (dd[right].second.first < a[i]) {
			left = right;
		}

		int count = dd[left].first + 1;

		parent[i] = dd[left].second.second;

		d[i] = count;
		
		if (max < count) {
			max = count;
			maxidx = i;
		}

		if (left + 1 >= dd.size()) {
			dd.push_back({ count,{a[i],i} });
		}
		else {
			if (dd[left + 1].second.first > a[i]) {
				dd[left + 1].second.first = a[i];
				dd[left + 1].second.second = i;
			}
			
		}
		

	}

	std::cout << max << "\n";

	std::vector<int> trace;

	int nowidx = maxidx;

	while (nowidx != 0) {
		trace.push_back(a[nowidx]);

		nowidx = parent[nowidx];
	}


	std::reverse(trace.begin(), trace.end());

	for (int i : trace) {
		std::cout << i << " ";
	}

	std::cout << "\n";
	//return 0;
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
