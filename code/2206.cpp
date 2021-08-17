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

const int mod = 1000;

int n, m;

bool upable(std::pair<int, int> a) {
	return a.first > 1;
}

bool downable(std::pair<int, int> a) {
	return a.first < n;
}

bool leftable(std::pair<int, int> a) {
	return a.second > 1;
}

bool rightable(std::pair<int, int> a) {
	return a.second < m;
}


int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);
	
	

	std::cin >> n >> m;

	std::vector<std::vector<bool>> bo(n + 1, std::vector<bool>(m + 1));

	std::bitset<2> res;

	res.reset();

	std::vector<std::vector<std::bitset<2>>> isvisit(n + 1, std::vector<std::bitset<2>>(m + 1, res));

	

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c;
			std::cin >> c;

			bo[i][j] = (c == '1');
		}
	}

	std::queue<std::pair<int,std::pair<std::pair<std::pair<int, int>,bool>, std::pair<int, int>>>> qu;

	qu.push({ 1,{ {{1,1},false},{-1,-1} } });


	int re = -1;

	while (!qu.empty()) {

		auto now = qu.front();
		qu.pop();


		int nowcost = now.first;

		std::pair<int, int> nowpos = now.second.first.first;

		bool isbreak = now.second.first.second;

		std::pair<int, int> nextpos = now.second.second;

		if (isvisit[nowpos.first][nowpos.second][isbreak]) continue;

		if (!bo[nowpos.first][nowpos.second]) isvisit[nowpos.first][nowpos.second][isbreak] = true;

		if (nowpos.first == n && nowpos.second == m) {
			if (re == -1)re = nowcost;
			else {
				re = std::min(re, nowcost);
			}
			break;
		}

		if (nextpos.first == -1 && nextpos.second == -1) {
			if (upable(nowpos)) {
				std::pair<int, int> next{ nowpos };
				next.first -= 1;
				if (bo[next.first][next.second]) {
					//if wall
					if (upable(next) && (!isbreak)) {
						if (!bo[next.first - 1][next.second]) {
							if (!isvisit[next.first - 1][next.second][true]) {
								qu.push({ nowcost + 1,{{next,true},{next.first - 1,next.second}} });
							}
						}
					}

				}
				else {
					//if not wall
					if (!isvisit[next.first][next.second][isbreak]) {
						qu.push({ nowcost + 1,{{next,isbreak},{-1,-1}} });
					}
				}

			}

			if (downable(nowpos)) {
				std::pair<int, int> next{ nowpos };
				next.first += 1;
				if (bo[next.first][next.second]) {
					//if wall
					if (downable(next) && (!isbreak)) {
						if (!bo[next.first + 1][next.second]) {
							if (!isvisit[next.first + 1][next.second][true]) {
								qu.push({ nowcost + 1,{{next,true},{next.first + 1,next.second}} });
							}
						}
					}

				}
				else {
					//if not wall
					if (!isvisit[next.first][next.second][isbreak]) {
						qu.push({ nowcost + 1,{{next,isbreak},{-1,-1}} });
					}
				}

			}

			if (leftable(nowpos)) {
				std::pair<int, int> next{ nowpos };
				next.second -= 1;
				if (bo[next.first][next.second]) {
					//if wall
					if (leftable(next) && (!isbreak)) {
						if (!bo[next.first][next.second - 1]) {
							if (!isvisit[next.first][next.second - 1][true]) {
								qu.push({ nowcost + 1,{{next,true},{next.first,next.second - 1}} });
							}
						}
					}

				}
				else {
					//if not wall
					if (!isvisit[next.first][next.second][isbreak]) {
						qu.push({ nowcost + 1,{{next,isbreak},{-1,-1}} });
					}
				}

			}

			if (rightable(nowpos)) {
				std::pair<int, int> next{ nowpos };
				next.second += 1;
				if (bo[next.first][next.second]) {
					//if wall
					if (rightable(next) && (!isbreak)) {
						if (!bo[next.first][next.second + 1]) {
							if (!isvisit[next.first][next.second + 1][true]) {
								qu.push({ nowcost + 1,{{next,true},{next.first,next.second + 1}} });
							}
						}
					}

				}
				else {
					//if not wall
					if (!isvisit[next.first][next.second][isbreak]) {
						qu.push({ nowcost + 1,{{next,isbreak},{-1,-1}} });
					}
				}

			}


		}
		else {
			qu.push({ nowcost + 1,{{nextpos,isbreak},{-1,-1}} });
		}

		

	}


	std::cout << re << "\n";
	//return 0;
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
