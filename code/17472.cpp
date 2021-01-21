// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include<stack>
#include<algorithm>
#include <vector>
#include <utility>
#include<set>

template<typename T>
void debugprint(T t) {
	//std::cout << t << std::endl;
}

class sets {
public:
	sets(int size) {
		tofind = std::vector<int>(size);
	}

	void makeset(int a) {
		tofind[a] = S.size();
		auto tmp = std::set<int>();
		tmp.insert(a);
		S.push_back(tmp);
	}

	std::vector<std::set<int>>::iterator findset(int a){
		return (S.begin() + tofind[a]);
	}

	void unionset(int a, int b){
		int setapos = tofind[a];
		auto& seta = findset(a)[0];
		auto& setb = findset(b)[0];

		seta.insert(setb.begin(), setb.end());

		for (int i : setb) {
			tofind[i] = setapos;
		}

		setb.erase(setb.begin(), setb.end());
	};

	std::vector<std::set<int>> getsets () {
		std::vector<std::set<int>> result;

		for (auto& set : S) {
			if (set.size() > 0) {
				result.push_back({ set });
			}
		}

		return result;
	}
private:
	std::vector<std::set<int>> S;
	std::vector<int> tofind;
};



class vertax {
public:
	vertax() : vertax(0, 0, 0) {}
	vertax(int e1, int e2, int v) : edge1 (e1), edge2(e2),value(v){
	}
	
	void print() {
		std::cout << edge1 << " " << edge2 << " " << value << std::endl;
	}

	vertax(const vertax&) = default;
	vertax(vertax&&) = default;
	vertax& operator= (const vertax&) = default;
	vertax& operator= (vertax&&) = default;


	int edge1;
	int edge2;
	int value;

};
struct cmpvertax {
	bool operator()(vertax& a, vertax& b) {
		return a.value > b.value;
	}
};

class map {
public:
	map() {
		int n;
		int m;
		std::cin >> n;
		std::cin >> m;
		this ->n = n;
		this->m = m;
		ma = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));

		for (auto& e : ma) {
			for (int& i : e) {
				std::cin >> i;
				if (i == 0) {
					i = -1;
				}
				else {
					i = -2;
				}
			}
		}

		int islandnum = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (ma[i][j] == -2) {
					
					this->givenumber(i, j, islandnum);
					++islandnum;
					islands.push_back({ i,j });
				}
			}
		}

	}

	map(const map&) = default;
	map(map&&) = default;
	map& operator= (const map&) = default;
	map& operator= (map&&) = default;

	void print() {
		for (auto& e : ma) {
			for (int& i : e) {
				std::cout << i;
			}
			std::cout << std::endl;
		}
	}

	std::vector<vertax> getvertax() {
		std::vector<vertax> result;
		for (int i = 0; i < n; i++) {
			int nowisland = -1;
			int length = 0;
			for (int j = 0; j < m; j++) {
				if (ma[i][j] != -1) {
					//if island;
					if (nowisland != -1) {
						//if before island is
						if (nowisland != ma[i][j]) {
							if (length >= 2) {
								result.push_back({ nowisland,ma[i][j],length });
							}
						}
					}
					length = 0;
					nowisland = ma[i][j];

				}
				else {
					//if sea;
					++length;
				}
			}
		}

		for (int j = 0; j < m; j++) {
			int nowisland = -1;
			int length = 0;
			for (int i = 0; i < n; i++) {
				if (ma[i][j] != -1) {
					//if island;
					if (nowisland != -1) {
						//if before island is
						if (nowisland != ma[i][j]) {
							if (length >= 2) {
								result.push_back({ nowisland,ma[i][j],length });
							}
						}
					}
					length = 0;
					nowisland = ma[i][j];

				}
				else {
					//if sea;
					++length;
				}
			}
		}

		return result;
	}

	int getislansnum() {
		return islands.size();
	}

private:
	std::vector<std::vector<int>> ma;
	std::vector<std::pair<int, int>> islands{};

	int n;
	int m;

	void givenumber(int a, int b, int num) {
		ma[a][b] = num;
		if (a > 0) {
			if (ma[a - 1][b] == -2) {
				this->givenumber(a - 1, b, num);
			}
		}
		if (b > 0) {
			if (ma[a][b - 1] == -2) {
				this->givenumber(a , b -1, num);
			}
		}
		if (a <n-1) {
			if (ma[a+1][b] == -2) {
				this->givenumber(a + 1, b, num);
			}
		}
		if (b <m-1) {
			if (ma[a][b + 1] == -2) {
				this->givenumber(a , b + 1, num);
			}
		}
	}
	
};

int main()
{
	map m{};
	int result = 0;
	
	
	//m.print();
	auto ver = m.getvertax();
	//m.print();

	std::priority_queue<vertax, std::vector<vertax>, cmpvertax> pque{};

	for (auto& v : ver) {
		//v.print();
		pque.push(v);
	}
	int size = m.getislansnum();
	sets S{size};
	for (int i = 0; i < size; i++) {
		S.makeset(i);
	}


	while (!pque.empty()) {
		auto& now = pque.top();
		
		if (S.findset(now.edge1) != S.findset(now.edge2)) {
			S.unionset(now.edge1, now.edge2);

			result += now.value;
		}

		pque.pop();
	}

	auto re = S.getsets();

	if (re.size() > 1) {
		std::cout << -1;
	}
	else {
		std::cout << result;
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
