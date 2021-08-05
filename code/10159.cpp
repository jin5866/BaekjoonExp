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

	std::bitset<101> allfalse;
	allfalse.reset();

	std::vector<std::bitset<101>> bigger;
	std::vector<std::bitset<101>> smaller;

	int N, M;

	std::cin >> N >> M;

	bigger = std::vector<std::bitset<101>>(N + 1, allfalse);
	smaller = std::vector<std::bitset<101>>(N + 1, allfalse);

	for (int i = 0; i < M; i++) {
		int a, b;
		std::cin >> a >> b;

		bigger[a][b] = true;
		smaller[b][a] = true;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= N; k++) {
				bigger[j][k] = bigger[j][k] || (bigger[j][i] && bigger[i][k]);
				smaller[j][k] = smaller[j][k] || (smaller[j][i] && smaller[i][k]);
			}
		}
	}


	for (int i = 1; i <= N; i++) {
		int counter = 0;
		for (int j = 1; j <= N; j++) {
			if (i == j) continue;

			if ((!bigger[i][j]) && (!smaller[i][j])) {
				counter++;
			}
		}

		std::cout << counter << std::endl;
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