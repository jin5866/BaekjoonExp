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

int f(std::vector<int>& lis, int start, int end) {
	if (start == end) {
		return lis[start];
	}

	int mid = (start + end) / 2;

	int a1 = f(lis, start, mid);
	int a2 = f(lis, mid + 1, end);
	int a3 = 0;

	int leftmax = std::min(lis[mid], lis[mid + 1]);
	int leftindex = mid;
	int rightmax = leftmax;
	int rightindex = mid + 1;

	a3 = rightmax * 2;

	while (start<leftindex || end> rightindex) {
		if ((leftmax >= rightmax || rightindex == end) && leftindex>start) {
			//move left
			leftindex--;
			leftmax = std::min(leftmax, lis[leftindex]);
			if (leftmax <= rightmax) {
				a3 = std::max(a3, (rightindex - leftindex + 1) * leftmax);
			}
			else {
				a3 = std::max(a3, (rightindex - leftindex) * leftmax);
			}
			
		}

		else if ((rightmax >= leftmax || leftindex==start) && rightindex < end){
			//move right
			rightindex++;
			rightmax = std::min(rightmax, lis[rightindex]);
			if (leftmax >= rightmax) {
				a3 = std::max(a3, (rightindex - leftindex + 1) * rightmax);
			}
			else {
				a3 = std::max(a3, (rightindex - leftindex) * rightmax);
			}
			
		}

	}

	//a3 = std::max(a3, std::min(rightmax, leftmax) * (start - end + 1));

	return std::max(a3, std::max(a1, a2));
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	std::set<int> lenset;
	std::vector<int> lenlist;

	int N;
	const int max = 2000000000;



	std::cin >> N;

	int maxlen = 0;

	std::vector<int> lis(N);

	for (int& i : lis) {
		std::cin >> i;
		
	}

	int maxsize = 0;

	std::cout << f(lis, 0, N - 1)<<"\n";

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
