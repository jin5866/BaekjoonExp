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


int main()
{
	std::ios_base::sync_with_stdio(false);

	int h, w, l;

	std::cin >> h >> w >> l;




	std::vector<std::vector<char>> bo(h,std::vector<char>(w));
	std::vector<std::vector<std::vector<long long int>>> co(l, std::vector<std::vector<long long int>>(h, std::vector<long long int>(w, 0)));

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			std::cin >> bo[i][j];
		}
	}

	std::vector<char> str(l);
	for (char& c : str) {
		std::cin >> c;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (str[0] == bo[i][j]) {
				co[0][i][j] = 1;
			}
		}
	}

	for (int c = 1; c < l; c++) {
		//std::cout << "c::" << c << std::endl;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (str[c] == bo[i][j]) {

					long long int sum = 0;

					bool up = (i > 0);

					bool down = (i < h - 1);
					bool left = (j > 0);
					bool right = (j < w - 1);

					if (up && left) {
						sum += co[c - 1][i - 1][j - 1];
					}
					if (up) {
						sum += co[c - 1][i - 1][j];
					}
					if (up && right) {
						sum += co[c - 1][i - 1][j + 1];
					}
					if (left) {
						sum += co[c - 1][i][j - 1];
					}
					if (right) {
						sum += co[c - 1][i][j + 1];
					}
					if (down && left) {
						sum += co[c - 1][i + 1][j - 1];
					}
					if (down) {
						sum += co[c - 1][i + 1][j];
					}
					if (down && right) {
						sum += co[c - 1][i + 1][j + 1];
					}

					co[c][i][j] = sum;

				}
				//std::cout << co[c][i][j];
			}
			//std::cout << std::endl;
		}
	}

	long long int sum = 0;


	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			sum += co[l-1][i][j];
		}
	}
	

	std::cout << sum << std::endl;
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
