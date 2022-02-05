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

std::bitset<9> getvalidnum(int posx,int posy, std::vector<std::vector<int>>& bo){
	std::bitset<9> set;
	set.reset();
	for (int i = 0; i < 9; i++) {
		if (bo[posx][i] != 0) {
			set.set(bo[posx][i] - 1);
		}
	}

	for (int i = 0; i < 9; i++) {
		if (bo[i][posy] != 0) {
			set.set(bo[i][posy] - 1);
		}
	}

	int x = posx / 3;
	int y = posy / 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (bo[x * 3 + i][y * 3 + j] != 0) {
				set.set(bo[x * 3 + i][y * 3 + j] - 1);
			}
		}
	}

	set.flip();

	return set;

}

bool solve(int posidx, std::vector<std::vector<int>>& bo,const std::vector<std::pair<int,int>>& poslist) {
	if (posidx == poslist.size()) {
		return true;
	}

	int posx = poslist[posidx].first;
	int posy = poslist[posidx].second;

	if (bo[posx][posy] != 0) {
		return solve(posidx + 1, bo, poslist);
	}

	std::bitset<9> set = getvalidnum(posx, posy, bo);

	for (int i = 0; i < 9; i++) {
		if (set[i]) {
			bo[posx][posy] = i + 1;
			if (solve(posidx + 1, bo, poslist)) {
				return true;
			}
			bo[posx][posy] = 0;
		}
	}

	return false;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
	
	std::vector<std::vector<int>> bo(9,std::vector<int>(9));

	std::vector<std::pair<int,int>> zeropos;

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			char c;
			std::cin >> c;
			bo[i][j] = c - '0';
			if (bo[i][j] == 0) {
				zeropos.push_back(std::make_pair(i, j));
			}
		}
	}

	bool result = solve(0, bo, zeropos);

	if (result) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				std::cout << bo[i][j];
			}
			std::cout << "\n";
		}
	}
	else {
		std::cout << "No Solution";
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
