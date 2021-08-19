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

std::vector<int> parent;

std::vector<std::vector<int>> sets;

void unionset(int a, int b) {
	int apa = std::min(parent[a],parent[b]);
	int bpa = std::max(parent[a], parent[b]);

	if (apa == bpa) {
		return;
	}

	sets[apa].insert(sets[apa].end(),sets[bpa].begin(), sets[bpa].end());

	for (int e : sets[bpa]) {
		parent[e] = apa;
	}

	sets[bpa].clear();

}

bool issame(int a, int b) {
	return parent[a] == parent[b];
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
	
		
	int v, e;

	std::cin >> v >> e;

	std::vector<std::pair<int, std::pair<int, int>>> arr;
	parent = std::vector<int>(v + 1);

	sets = std::vector<std::vector<int>>(v + 1);

	for (int i = 1; i <= v; i++) {
		parent[i] = i;
		sets[i].push_back(i);
	}

	for (int i = 1; i <= e; i++)
	{
		int a, b, c;

		std::cin >> a >> b >> c;
		arr.push_back({ c,{a,b} });
	}

	std::sort(arr.begin(), arr.end());


	long long acc = 0;

	for (auto& i : arr) {
		int a = i.second.first;
		int b = i.second.second;
		int c = i.first;
		if (!issame(a, b)) {
			unionset(a, b);
			acc += c;
		}
	}

	std::cout << acc << "\n";

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
