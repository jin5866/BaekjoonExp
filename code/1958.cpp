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


bool isVisible(std::vector<int>& heightList, int a, int b) {
	if (b < a) {
		return isVisible(heightList, b, a);
	}

	double tan = 1.0 * (heightList[b] - heightList[a]) / (b - a);

	for (int i = a + 1; i < b; i++) {
		double lim = tan * (i - a) + heightList[a];

		if ((double)heightList[i] >= lim) {
			return false;
		}
	}

	return true;

}

int main()
{
	std::ios::sync_with_stdio(false);

	std::string a, b, c;
	int alen, blen, clen;

	std::cin >> a;
	std::cin >> b;
	std::cin >> c;
	alen = a.length() + 1;
	blen = b.length() + 1;
	clen = c.length() + 1;

	std::vector<std::vector<std::vector<int>>> bo(alen, std::vector<std::vector<int>>(blen, std::vector<int>(clen, 0)));

	for (int i = 1; i < alen; i++) {
		for (int j = 1; j < blen; j++) {
			for (int k = 1; k < clen; k++) {
				if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) {
					bo[i][j][k] = bo[i - 1][j - 1][k - 1] + 1;
				}
				else {
					bo[i][j][k] = std::max(bo[i - 1][j][k], std::max(bo[i][j - 1][k], bo[i][j][k - 1]));
				}
			}
		}
	}
	


	std::cout << bo[alen-1][blen-1][clen-1] << std::endl;


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
