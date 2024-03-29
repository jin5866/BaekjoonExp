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

bool compare(long long& a, long long& b) {
	return a > b;
}


int main()
{
	std::ios::sync_with_stdio(false);

	long long n, w;

	std::cin >> n >> w;

	std::vector<long long> list3{};
	std::vector<long long> list5{};

	std::vector<long long> accu3{};
	std::vector<long long> accu5{};

	for (long long i = 0; i < n; i++) {
		long long a, b;
		std::cin >> a >> b;

		if (a == 3) {
			list3.push_back(b);
		}
		else {
			list5.push_back(b);
		}
	}

	std::sort(list3.begin(), list3.end(), compare);
	std::sort(list5.begin(), list5.end(), compare);

	long long sum = 0;
	accu3.push_back(sum);
	for (long long a : list3) {
		sum += a;
		accu3.push_back(sum);
	}

	sum = 0;
	accu5.push_back(0);
	for (long long a : list5) {
		sum += a;
		accu5.push_back(sum);
	}

	long long max = 0;
	long long size5 = list5.size();
	for (int i = 0; i <= std::min(size5, (long long)w / 5); i++) {
		int remain = w - i * 5;
		int treemax = std::min((int)accu3.size() - 1, (remain / 3));
		max = std::max(max, accu5[i] + accu3[treemax]);
	}


	std::cout << max << std::endl;

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
