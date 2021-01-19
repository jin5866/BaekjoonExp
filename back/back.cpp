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
	graph(int size) : size(size) {
		capacity = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
		flow = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
		parent = std::vector<int>(size, -1);
	}
	graph(const graph&) = default;
	graph(graph&&) = default;
	graph& operator = (const graph&) = default;
	graph& operator = (graph&&) = default;

	int residual(int from, int to) {
		return capacity[from][to] - flow[from][to];
	}

	void setcapacity(int from, int to, int value) {
		capacity[from][to] = value;
		//capacity[to][from] = -value;
	}

	void setflow(int from, int to, int value) {
		flow[from][to] = value;
		flow[to][from] = -value;
	}

	int getflow(int from, int to) {
		return flow[from][to];
	}

	void printnode() {
		for (auto& f : capacity) {
			for (int i : f) {
				std::cout << i;
			}
			std::cout << std::endl;
		}
	}

	void printflow() {
		for (auto& f : flow) {
			for (int i : f) {
				std::cout << i;
			}
			std::cout << std::endl;
		}
	}

	void resetflow() {
		flow = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
	}

	std::pair < std::vector<std::vector<int>>, int> findflow(int start, int end) {

		int total = 0;
		while (true) {
			std::fill(parent.begin(), parent.end(), -1);
			std::queue<int> Q;

			Q.push(start);
			parent[start] = start;

			while ((!Q.empty()) && parent[end] == -1) {
				int now = Q.front();
				Q.pop();



				for (int other = 0; other < capacity[now].size(); other++) {
					if (this->residual(now, other) > 0 && parent[other] == -1) {
						parent[other] = now;
						Q.push(other);
					}
				}
			}

			if (parent[end] == -1) {
				break;
			}

			int min = this->residual(parent[end], end);

			for (int p = end; p != start; p = parent[p]) {
				min = std::min(min, this->residual(parent[p], p));
			}

			for (int p = end; p != start; p = parent[p]) {
				flow[parent[p]][p] += min;
				flow[p][parent[p]] -= min;
			}

			//total += min;
		}

		for (int i : flow[start]) {
			total += i;
		}

		return { flow ,total };
	}


private:
	std::vector<std::vector<int>> capacity;
	std::vector<std::vector<int>> flow;
	std::vector<int> parent;
	int size;
};

int main()
{
	int jiminnum;
	int hansunum;
	int gamecount = 0;
	int hansucount = 0;

	std::cin >> jiminnum;
	std::cin >> hansunum;

	std::vector<int> jiminmaxrun(jiminnum);
	std::vector<int> hansumaxrun(hansunum);

	for (int& i : jiminmaxrun)
	{
		std::cin >> i;
		gamecount += i;
	}

	for (int& i : hansumaxrun)
	{
		std::cin >> i;
		hansucount += i;
	}

	if (gamecount != hansucount) {
		std::cout << -1 << std::endl;
		return 0;
	}

	int nodenum = 2 + jiminnum + hansunum;

	graph g{ nodenum };

	int startnode = 0;
	int endnode = nodenum - 1;

	std::vector<int> jiminnodes(jiminnum);
	for (int i = 0; i < jiminnum; i++) {
		jiminnodes[i] = 1 + i;
		g.setcapacity(startnode, 1 + i, jiminmaxrun[i]);
	}

	std::vector<int> hansumnodes(hansunum);
	for (int i = 0; i < hansunum; i++) {
		hansumnodes[i] = 1 + jiminnum + i;//endnode - i - 1;//
		g.setcapacity(1 + jiminnum + i, endnode, hansumaxrun[i]);
	}
	for (int from : jiminnodes) {
		for (int to : hansumnodes) {
			g.setcapacity(from, to, 1);
		}
	}
	//g.printnode();
	auto result = g.findflow(startnode, endnode);
	//g.printflow();



	if (result.second != gamecount) {

		std::cout << -1 << std::endl;
		return 0;

	}


	for (int ji : jiminnodes) {
		for (int han : hansumnodes) {
			if (result.first[ji][han] == 1) {
				graph origin{ g };

				g.setcapacity(ji, han, 0);
				g.setflow(ji, han, 0);
				int flowtmp = g.getflow(startnode, ji);
				int flowtmp2 = g.getflow(han, endnode);
				g.setflow(startnode, ji, flowtmp - 1);
				g.setflow(han, endnode, flowtmp2 - 1);



				auto tmpresult = g.findflow(startnode, endnode);

				if (tmpresult.second == gamecount) {
					result = tmpresult;
				}
				else {
					g = std::move(origin);
				}
			}
			else if (result.first[ji][han] == 0) {
				g.setcapacity(ji, han, 0);
			}

		}
	}

	//print;
	for (int ji : jiminnodes) {
		for (int han : hansumnodes) {
			std::cout << result.first[ji][han];
		}
		std::cout << std::endl;
	}
	return 0;
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
