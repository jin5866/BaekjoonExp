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

template<typename T>
void debugprint(T t) {
	std::cout << t;
}

std::vector<std::vector<std::vector<std::pair<bool, int>>>> mem;

void set(int i, int x, int y, int val) {
	i += 1;
	if (mem.size() <= i) {
		mem.resize(i + 1);
	}

	if (mem[i].size() <= x) {
		mem[i].resize(x + 1);
	}

	if (mem[i][x].size() <= y) {
		mem[i][x].resize(y + 1, std::pair<bool, int>(false, 0));
	}

	mem[i][x][y] = { true,val };
}

std::pair<bool, int> get(int i, int x, int y) {
	i += 1;
	if (mem.size() <= i) {
		return { false,0 };
	}

	if (mem[i].size() <= x) {
		return { false,0 };
	}

	if (mem[i][x].size() <= y) {
		return { false,0 };
	}

	return mem[i][x][y];
}



int dp(int i, int x, int y, std::vector<int>& list, std::vector<int>& sumlist,int size,int sum) {
	auto a = get(i, x, y);

	if (y < x) {
		return dp(i, y, x, list, sumlist, size, sum);
	}

	if (a.first) {
		return a.second;
	}

	if (i < 0) {
		int other = sum - x - y;

		int tmin = std::min(x, std::min(y,other));

		set(i, x, y, tmin);
		return tmin;
	}
	int usedsum = sum - sumlist[i];

	int other = usedsum - x - y;

	int left = dp(i - 1, x, y, list, sumlist, size, sum);


	int mid = dp(i - 1, x, std::min(y + list[i], other), list, sumlist, size, sum);

	int right = dp(i - 1, std::min(x + list[i], other), y, list, sumlist, size, sum);

	int re = std::max(left, std::max(mid, right));

	set(i, x, y, re);
	return re;
}


int main()
{
	std::ios_base::sync_with_stdio(false);

	int n;


	std::cin >> n;

	std::vector<int> list1(n);
	std::vector<int> list2(n);

	int sum = 0;

	for (int i = 0; i < n; i++) {
		int tmp;
		std::cin >> tmp;
		list1[i] = tmp;
		sum += tmp;
		list2[i] = sum;
	}

	int re = 0;

	re = dp(n - 1, 0, 0, list1, list2, n, sum);

	/*
	for (int i = 0; i < n; i++) {
		int tmp = list1[0];
		list1.erase(list1.begin());

		list1.push_back(tmp);
		re = std::max(re, knapsack2(n - 1, 0, 0, list1));
	}*/


	std::cout << re << std::endl;


	

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
