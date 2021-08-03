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

std::vector<long long> tree;
int size;


int parent(int i) {
	return i / 2;
}

int left(int i) {
	return i * 2;
}

int right(int i) {
	return i * 2 + 1;
}

bool isroot(int i) {
	return i == 1;
}

bool isleaf(int i) {
	return i >= size;
}

long long settree(int i) {
	if (isleaf(i)) {
		return tree[i];
	}
	else {
		tree[i] = settree(left(i)) + settree(right(i));
		return tree[i];
	}
}

int getleaf(int index) {
	return size + index - 1;
}

void printtree(int i = 1) {
	
	for (auto t = tree.begin(); t != tree.end(); t++) {
		std::cout << t[0] << " ";
	}
	
}

void updatetree(int index, long long data) {
	int node = getleaf(index);

	long long beforedata = tree[node];

	long long diff = data - beforedata;

	while (true) {

		tree[node] += diff;
		

		if (isroot(node)) {
			break;
		}

		node = parent(node);
	}
}

long long getsum(int start, int end, int samecount = 0 , int acc = 0) {
	if (end < start) {
		return getsum(end, start);
	}

	//int acc = 0;
	int same = 1 << (30 - samecount);


	int midbit = 1;

	int mid;
	/*while (mid < start && end >= mid) {
		mid *= 2;
	}*/

	int issame = ~(start ^ end);


	while (true) {

		if (!same) {
			break;
		}

		if (issame & same) {
			acc |= same;
			same >>= 1;
			samecount++;
		}
		else {
			midbit = acc + same;
			break;
		}
	}
	int count = 0;
	while (true) {
		if (!same) {
			break;
		}

		if (( ~start & same) && (end & same)) {
			same >>= 1;
			count++;
		}
		else {
			break;
		}
	}

	if (!same) {
		int node = getleaf(start+1);
		for (int i = 0; i < count; i++) {
			node = parent(node);
		}

		return tree[node];
	}
	else {
		mid = end & midbit;
		return getsum(start, mid - 1, samecount, acc) + getsum(mid, end, samecount, acc);
	}

}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
	int N, Q;

	std::cin >> N >> Q;

	size = 1;

	while (size < N) {
		size *= 2;
	}

	tree = std::vector<long long>(size * 2,0);

	for (int i = size; i < size + N; i++) {
		std::cin >> tree[i];
	}

	settree(1);
	//printtree();
	//std::cout << std::endl;

	for (int i = 0; i < Q; i++) {
		int x, y, a, b;
		std::cin >> x >> y >> a >> b;

		std::cout << getsum(x-1, y-1) << '\n';

		updatetree(a, b);
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
