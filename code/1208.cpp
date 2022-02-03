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

void make_all(const std::vector<int>& a, int nowindex, int nownum, std::vector<int>& made) {

	if (a.size() == 0) {
		return;
	}

	if (nowindex == a.size() - 1) {
		made.push_back(nownum);
		made.push_back(nownum + a[nowindex]);
	}
	else {
		make_all(a, nowindex + 1, nownum, made);
		make_all(a, nowindex + 1, nownum + a[nowindex], made);
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
	
	int n, s;

	
	std::vector<int> tmlist;

	std::cin >> n >> s;

	std::vector<int> b(n / 2), a(n / 2 + (n % 2 == 1 ? 1 : 0));

	for (int i = 0; i < n; i++) {
		int num;
		std::cin >> num;
		tmlist.push_back(num);
	}

	std::sort(tmlist.begin(), tmlist.end());

	std::copy(tmlist.begin(), tmlist.begin() + n / 2 , b.begin());
	std::copy(tmlist.begin() + n / 2, tmlist.end(), a.begin());
	std::vector<int> al, bl;

	make_all(a, 0, 0, al);
	make_all(b, 0, 0, bl);

	std::sort(al.begin(), al.end(), std::greater<int>());
	std::sort(bl.begin(), bl.end(), std::less<int>());

	int i = 0, j = 0;
	long long result = 0;

	while (i<al.size() && j<bl.size()) {
		if (al[i] + bl[j] == s) {
			long long counta = 0;
			long long countb = 0;

			for (; i + counta < al.size() && al[i + counta] == al[i]; counta++);
			for (; j + countb <bl.size() && bl[j + countb] == bl[j]; countb++);

			result += (counta * countb);

			i += counta;
			j += countb;
			
		}
		else if (al[i] + bl[j] > s) {
			i++;
		}
		else {
			j++;
		}
	}
	
	if (bl.size() == 0) {
		for (int i : al) {
			if (i == s) {
				result++;
			}
		}
	}

	if (s == 0) result--;

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
