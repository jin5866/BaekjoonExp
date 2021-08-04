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
std::vector<std::vector<int>> child;

void unionset(int a, int b) {
	int aparent = parent[a];
	int bparent = parent[b];

	if (aparent == bparent) {
		return;
	}

	else if (aparent < bparent) {
		child[aparent].insert(child[aparent].end(), child[bparent].begin(), child[bparent].end());
		for (int c : child[bparent]) {
			parent[c] = aparent;
		}
		child[bparent].clear();

	}
	else {
		child[bparent].insert(child[bparent].end(), child[aparent].begin(), child[aparent].end());
		for (int c : child[aparent]) {
			parent[c] = bparent;
		}
		child[aparent].clear();
	}

}

bool isset(int a, int b) {
	int aparent = parent[a];
	int bparent = parent[b];

	if (aparent == bparent) {
		return true;
	}

	return false;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int N, M;
	std::cin >> N >> M;
	parent = std::vector<int>(N);

	child = std::vector< std::vector<int>>(N);
	

	for (int i = 0; i < N; i++) {
		parent[i] = i;
		child[i].push_back(i);
	}


	int knowscount;
	std::cin >> knowscount;
	std::vector<int> knows(knowscount);

	for (int& k : knows) {
		std::cin >> k;
		k--;
	}

	std::vector<std::vector<int>> partymembers(M);

	for (auto& partymem : partymembers) {
		int c;
		std::cin >> c;

		partymem = std::vector<int>(c);

		for (auto& mem : partymem) {
			std::cin >> mem;
			mem--;
		}
		int fir = partymem[0];
		for (auto& mem : partymem) {
			unionset(mem, fir);
		}
	}

	int count = 0;
	for (auto& partymem : partymembers) {
		bool cantalk = true;;
		for (int& k : knows) {
			if (isset(partymem[0], k)) {
				cantalk = false;
				break;
			}
		}

		if (cantalk) {
			count++;
		}
		
	}

	std::cout << count << "\n";



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
