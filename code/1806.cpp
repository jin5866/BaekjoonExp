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

	int n, s;
	std::cin >> n >> s;
	int start = 0, end = 0;

	int nowval = 0;

	int result = 1000000001;

	std::vector<int> bo(n);



	for (auto st = bo.begin(); st != bo.end();st++) {
		std::cin >> *st;
	}

	nowval = 0;

	while (end <= n ) {
		if (nowval >= s) {
			
			nowval -= bo[start];
			start++;
		}
		else {
			if (end == n) {
				break;
			}
			nowval += bo[end];
			end++;
		}

		if (nowval >= s) {
			result = std::min(result, end - start);
		}
	}



	if (result == 1000000001) {
		result = 0;
	}

	std::cout << result << std::endl;
	
	
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