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

class accdata {
public:
	//std::bitset<101> isvisit;
	int acccost;
	int acctime;
	int nowpos;
	bool final;

	static const int INF = 2147483647;

	void init() {
		acccost = 0;
		acctime = 2147483647;
		nowpos = 0;
		final = false;
		//isvisit.reset();
	}

	bool operator> (const accdata& other) const {
		return acctime > other.acctime;
	}

	bool operator< (const accdata& other) const {
		return acctime < other.acctime;
	}
	bool operator== (const accdata& other) const {
		return acctime == other.acctime && nowpos == other.nowpos;
	}

};

class connect {
public:
	int next;
	int cost;
	int time;
};


int oneroute(int N, int M, int K, std::vector<std::vector<connect>>& conns) {

	std::vector<std::vector<std::pair<int, bool>>> dp(N + 1, std::vector<std::pair<int, bool>>(M + 1, { accdata::INF ,false}));

	std::set<accdata> queue;
	//std::vector<accdata> queue;
	//std::vector<accdata>, std::greater<accdata>
	accdata lower{};
	lower.init();
	lower.acctime = -1;


	accdata start{};
	

	start.init();
	start.nowpos = 1;
	start.acctime = 0;
	//std::vector<std::vector<connect>> conns = std::vector<std::vector<connect>>(N + 1);

	accdata inf;
	inf.init();

	//std::vector<accdata> d(N + 1, inf);
	//std::bitset<101> isvisit;
	//isvisit.reset();

	//d[1] = start;




	int result = -1;
	queue.insert(start);

	//dp[1][0] = 0;

	while (!queue.empty()) {
		accdata now;
		now.init();
		//std::vector<accdata>::iterator todel;
		auto todel = queue.upper_bound(lower);
		now = *todel;

		/*for (auto q = queue.begin(); q != queue.end(); q++) {
			if (now > q[0]) {
				now = q[0];
				todel = q;
			}
		}*/

		queue.erase(todel);

		//queue.pop();

		if (now.acccost > M) {
			continue;
		}

		if (dp[now.nowpos][now.acccost].first < now.acctime) {
			continue;
		}

		/*if (now.nowpos == N) {
			result = now.acctime;
			break;
		}*/



		//now.isvisit[now.nowpos] = true;
		//isvisit[now.nowpos] = true;

		dp[now.nowpos][now.acccost].first = now.acctime;
		dp[now.nowpos][now.acccost].second = true;

		for (connect& con : conns[now.nowpos]) {

			accdata newacc = now;

			newacc.nowpos = con.next;
			newacc.acctime += con.time;
			newacc.acccost += con.cost;


			if (newacc.acccost > M) continue;
			if (dp[newacc.nowpos][newacc.acccost].second) continue;
			if (dp[newacc.nowpos][newacc.acccost].first <= newacc.acctime) continue;

			bool result = false;
			std::vector<accdata>::iterator todel;

			//q
			accdata accfind = newacc;
			accfind.acctime = dp[newacc.nowpos][newacc.acccost].first;
			auto tofind = queue.find(accfind);


			if (tofind != queue.end() && *tofind == accfind) {
				queue.erase(tofind);
			}

			dp[newacc.nowpos][newacc.acccost].first = newacc.acctime;
			queue.insert(newacc);
			


			/*for (auto q = queue.begin(); q != queue.end(); q++) {
				if (q[0] == newacc) {
					result = true;
					todel = q;
					if (q[0] > newacc) {
						;
						queue.erase(todel);
						queue.push_back(newacc);
					}
					
					
				}
			}*/

			/*if (!result) {
				
			}*/

		}

	}
	result = accdata::INF;
	for (auto d = dp[N].begin(); d != dp[N].end(); d++) {
		if (result > d[0].first) {
			result = d[0].first;
		}
	}

	if (result == accdata::INF) {
		result = -1;
	}

	return result;
}

std::string oneroute() {
	int N, M, K;
	std::cin >> N >> M >> K;
	int maxre = -1;

	std::vector<std::vector<connect>> conns = std::vector<std::vector<connect>>(N + 1);

	for (int i = 0; i < K; i++) {
		int u, v, c, d;

		std::cin >> u >> v >> c >> d;

		connect conn{};
		conn.next = v;
		conn.cost = c;
		conn.time = d;

		conns[u].push_back(conn);
	}


	maxre = std::max(maxre, oneroute(N, M, K,conns));
	
	
	
	if (maxre == -1) {
		return "Poor KCM";
	}
	else {
		return std::to_string(maxre);
	}

	//std::cout << ((result == -1) ? "Poor KCM" : std::to_string(result)) << std::endl;
}


int main()
{
	std::ios::sync_with_stdio(false);

	int count;

	std::cin >> count;

	std::string out;

	for (int i = 0; i < count; i++) {
		std::string re = oneroute();
		out.append(re);

		out.append("\n");
	}

	std::cout << out << std::endl;;

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
