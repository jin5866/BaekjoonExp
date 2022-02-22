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

int cappri = 1;

struct cmp{
	bool operator()(const std::pair<int,std::pair<int,int>>& a, const std::pair<int,std::pair<int,int>>& b) const {
		return a.first < b.first;
	}
};

bool isSmallLetter(char c){
	return (c >= 'a') && (c <= 'z');
}

bool isCapitalLetter(char c){
	return (c >= 'A') && (c <= 'Z');
}

bool isMoveable(char c,std::set<char>& keyset){
	return c == '.' || c == '$' || ((c >= 'a') && (c <= 'z')) || (keyset.find(c) != keyset.end());
}

bool isNotWall(char c) {
	return c != '*';
}

int getpriarity(char c){
	return (isCapitalLetter(c) ? cappri : 2);
}

void printboard(std::vector<std::vector<char>>& board){
	for(auto& row : board){
		for(auto& c : row){
			std::cout << c;
		}
		std::cout << std::endl;
	}
}

void run(){
	std::priority_queue<std::pair<int,std::pair<int,int>>,std::vector<std::pair<int,std::pair<int,int>>>,cmp> qu;
	int h,w;

	std::cin >> h >> w;
	std::vector<std::vector<char>> board(h, std::vector<char>(w ));

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			std::cin >> board[i][j];

			if(isNotWall(board[i][j])){
				if(i ==0 || j == 0 || i == h-1 || j == w-1){
					int pri = getpriarity(board[i][j]);
					qu.push(std::make_pair(pri, std::make_pair(i, j)));
				}
			}
		}
	}

	std::string s;

	std::cin >> s;
	std::set<char> keyset{};
	if (s[0] != '0') {
		for (char c : s) {
			keyset.insert(c - 'a' + 'A');
		}
	}
	


	

	int cnt = 0;

	while(!qu.empty()){
		auto p = qu.top();
		qu.pop();

		int x = p.second.first;
		int y = p.second.second;

		if(isMoveable(board[x][y],keyset)){
			if(x > 0 && isNotWall(board[x-1][y])){
				qu.push(std::make_pair(getpriarity(board[x-1][y]), std::make_pair(x-1, y)));
			}
			if(y > 0 && isNotWall(board[x][y-1])){
				int pri = getpriarity(board[x][y - 1]);
				qu.push(std::make_pair(pri, std::make_pair(x, y-1)));
			}
			if(x < h-1 && isNotWall(board[x+1][y])){
				qu.push(std::make_pair(getpriarity(board[x+1][y]), std::make_pair(x+1, y)));
			}
			if(y < w-1 && isNotWall(board[x][y+1])){
				qu.push(std::make_pair(getpriarity(board[x][y+1]), std::make_pair(x, y+1)));
			}

			if(isSmallLetter(board[x][y])){
				keyset.insert(board[x][y] - 'a' + 'A');
			}

			if(isCapitalLetter(board[x][y])){
				cappri = p.first;
			}

			if(board[x][y]=='$'){
				cnt++;
			}
			//board[x][y] = '+';

			//printboard(board);

			board[x][y] = '#';
		}
		else{
			if (isCapitalLetter(board[x][y])) {
				qu.push(std::make_pair(std::min(p.first,cappri) - 1, std::make_pair(x, y)));
				if(cappri - 2 == p.first){
					break;
				}
			}
		}
	}

	std::cout<<cnt<<std::endl;

}

int main() {
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	

	int count =0;
	std::cin>>count;

	for(int i=0;i<count;i++){
		run();
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
