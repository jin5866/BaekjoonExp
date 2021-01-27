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
	std::cout << t;
}

class graph {
public:

	graph(int size) : size(size),flow(size, std::vector<int>(size,0)), cost(size, std::vector<int>(size, 0)), capacity(size, std::vector<int>(size, 0)){
		
	}

	

	graph(const graph&) = default;
	graph(graph&&) = default;
	graph& operator= (const graph&) = default;
	graph& operator= (graph&&) = default;

	int residual(int from, int to) {
		return capacity[from][to] - flow[from][to];
	}

	void printnode() {
		for (auto& f : capacity) {
			for (int i : f) {
				std::cout << i<<"	";
			}
			std::cout << std::endl;
		}
	}

	void printflow() {
		for (auto& f : flow) {
			for (int i : f) {
				std::cout << i <<"	";
			}
			std::cout << std::endl;
		}
	}

	void printcost() {
		for (auto& f : cost) {
			for (int i : f) {
				std::cout << i << "	";
			}
			std::cout << std::endl;
		}
	}


	void setcost(int from, int to, int value) {
		cost[from][to] = value;
		cost[to][from] = -value;
	}
	void setcapacity(int from, int to, int value) {
		capacity[from][to] = value;
	}

	void setflow(int from, int to, int value) {
		flow[from][to] = value;
		flow[to][from] = -value;
	}

	std::pair < std::vector<std::vector<int>>, int> findflow() {
		return findflow(0, size-1);
	}

	bool inQueue(const std::vector<int>& a,int v) {
		for (auto& i : a) {
			if (i == v) {
				return true;
			}
		}

		return false;
	}

	std::pair < std::vector<std::vector<int>>, int> findflow(int start, int end) {

		int total = 0;
		while (true) {
			std::vector<int> parent(size );
			std::vector<int> d(size , 100000);
			std::fill(parent.begin(), parent.end(), -1);
			std::queue<int> Q;
			std::vector<bool> inQ(size);

			Q.push(start);
			inQ[start] = true;
			parent[start] = start;
			d[start] = 0;
			while ((!Q.empty())) {
				int now = Q.front();
				Q.pop();
				inQ[now] = false;


				for (int other = 0; other < capacity[now].size(); other++) {
					if ((capacity[now][other]>0 || capacity[other][now]>0) && residual(now, other) > 0 ) {
						if (d[now] + cost[now][other] < d[other]) {
							d[other] = d[now] + cost[now][other];
							parent[other] = now;
							if (!inQ[other]) {
								Q.push(other);
								inQ[other] = true;
							}
						}
					}
				}
			}

			if (parent[end] == -1) {
				break;
			}

			int min = residual(parent[end], end);

			for (int p = end; p != start; p = parent[p]) {
				min = std::min(min, residual(parent[p], p));
			}
			int now_cost = 0;
			for (int p = end; p != start; p = parent[p]) {

				total += min * cost[parent[p]][p];
				flow[parent[p]][p] += min;
				flow[p][parent[p]] -= min;
			}



			total += now_cost;
		}
		/*
		for (int i : flow[start]) {
			total += i;
		}*/

		return { flow ,total };
	}

private:
	int size;
	std::vector<std::vector<int>> flow;
	std::vector<std::vector<int>> cost;
	std::vector<std::vector<int>> capacity;

};

int getvalue(char a, char b) {
	int arr[6][6] = { {100,70,40,0,0,0},{70,50,30,0,0,0},{40,30,20,0,0,0},{0,0,0,0,0,0} ,{0,0,0,0,0,0} ,{0,0,0,0,0,0} };

	return arr[a - 'A'][b - 'A'];
}

int getcost(char a, char b) {
	

	return 100 - getvalue(a,b);
}

int main()
{
	int n;

	std::cin >> n;
	std::vector<std::vector<char>> dubu(n, std::vector<char>(n));
	for (auto& line : dubu) {
		for (char& c : line) {
			std::cin >> c;
		}
	}

	graph g{ n*n+2 };
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((i & 1) == (j & 1)) {
				++count;
				//짝짝 홀홀
				g.setcapacity(0, i * n + j + 1,1);
				g.setcost(0, i * n + j + 1, 0);

				int x = 0;
				int y = 0;

				if (i > 0 ) {
					//up
					x = -1;
					y = 0;
					g.setcapacity(i * n + j + 1, (i + x) * n + (j + y) + 1, 1);
					g.setcost(i * n + j + 1, (i + x) * n + (j + y) + 1, getcost(dubu[i + x][(j + y)], dubu[i][j]));
				}

				if (j > 0) {
					x = 0;
					y = -1;
					g.setcapacity(i * n + j + 1, (i + x) * n + (j + y) + 1, 1);
					g.setcost(i * n + j + 1, (i + x) * n + (j + y) + 1, getcost(dubu[i + x][(j + y)], dubu[i][j]));
				}

				if (i < n - 1) {
					x = 1;
					y = 0;
					g.setcapacity(i * n + j + 1, (i + x) * n + (j + y) + 1, 1);
					g.setcost(i * n + j + 1, (i + x) * n + (j + y) + 1, getcost(dubu[i + x][(j + y)], dubu[i][j]));
				}

				if (j < n - 1) {
					x = 0;
					y = 1;
					g.setcapacity(i * n + j + 1, (i + x) * n + (j + y) + 1, 1);
					g.setcost(i * n + j + 1, (i + x) * n + (j + y) + 1, getcost(dubu[i + x][(j + y)], dubu[i][j]));
				}

				g.setcapacity(i * n + j + 1, n * n + 1, 1);
				g.setcost(i * n + j + 1, n * n + 1, 100);

			}
			else {
				g.setcapacity(i * n + j + 1, n * n + 1, 1);
				g.setcost(i * n + j + 1, n * n + 1, 0);
			}

			//g.setcapacity();
			//g.setcost();
			//g.setflow();

		}
	}
	//g.printnode();
	//std::cout << std::endl;
	//g.printcost();
	//std::cout << std::endl;
	auto result = g.findflow();

	auto flows = result.first;
	int cost = result.second;
	

	//g.printflow();

	std::cout << (count * 100 - cost) << std::endl;
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
