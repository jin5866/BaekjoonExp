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

long long  dp[60][38][30][26] = {0};

long long solve(long long n, int k,int a2,int a3,int a4,int a5) {
	if (k == 0) return n;
	if (n == 0) return 0;


	long long re = dp[a2][a3][a4][a5];
	if (re != 0) {
		return re;
	}

	long long r2 = solve(n/2, k - 1, a2 + 1, a3, a4, a5) + ((n ) % 2);
	long long r3 = solve(n/3, k - 1, a2, a3 + 1, a4, a5) + ((n ) % 3);
	long long r4 = solve(n/4, k - 1, a2, a3, a4 + 1, a5) + ((n ) % 4);
	long long r5 = solve(n/5, k - 1, a2, a3, a4, a5 + 1) + ((n ) % 5);

	re = std::min(std::min(r2, r3), std::min(r4, r5));

	dp[a2][a3][a4][a5] = re;

	return re;
}


int main()
{
	std::ios::sync_with_stdio(false);
	
	long long n;
	int k;

	std::cin >> n;
	std::cin >> k;

	long long re = solve(n, k-1,0,0,0,0);
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
