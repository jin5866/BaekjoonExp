// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include<algorithm>
#include <vector>
#include <utility>

template<typename T>
void debugprint(T t) {
	//std::cout << t << std::endl;
}

enum class Dir : int {
	right = 0 ,
	left,
	up,
	down
};

bool operator== (std::pair<int, int>& a, std::pair<int, int>& b) {
	return (a.first == b.first) && (a.second == b.second);
}

std::pair<int, int> operator+ (std::pair<int, int>& a, std::pair<int, int>& b) {
	return std::pair<int, int>{a.first + b.first, a.second + b.second};
}

class distenceboard {
public:
	distenceboard(int size) {
		bo = std::vector<std::vector<std::pair<int, bool>>>(size, std::vector<std::pair<int, bool>>(size, { -1 ,false}));
	}

	int getDis(const std::pair<int, int>& pos) {
		return bo[pos.first - 1][pos.second - 1].first;
	}

	void setDis(const std::pair<int, int>& pos, int data) {
		bo[pos.first - 1][pos.second - 1].first = data;
	}

	bool getS(const std::pair<int, int>& pos) {
		return bo[pos.first - 1][pos.second - 1].second;
	}

	void setS(const std::pair<int, int>& pos, bool data) {
		bo[pos.first - 1][pos.second - 1].second = data;
	}

	distenceboard(distenceboard&) = default;
	distenceboard(distenceboard&&) = default;
	distenceboard& operator= (distenceboard&) = default;
	distenceboard& operator= (distenceboard&&) = default;


	void print() {
		for (auto& e : bo) {
			for (auto& c : e) {
				std::cout << c.first;
			}
			std::cout << std::endl;
		}
	}

	std::vector<std::vector<std::pair<int,bool>>> bo;
};




class board {
	
public :
	board() {
		int customsnum;
		std::cin >> size;
		std::cin >> customsnum;
		std::cin >> energy;

		bo = std::vector<std::vector<int>>( size, std::vector<int>(size,0) );

		for (auto& e : bo) {
			for (auto& i : e) {
				std::cin >> i;
			}
		}
		std::cin >> taxi.first;
		std::cin >> taxi.second;

		customers = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>(customsnum);

		for (auto& cu : customers) {
			std::cin >> cu.first.first;
			std::cin >> cu.first.second;
			std::cin >> cu.second.first;
			std::cin >> cu.second.second;

			//set(cu.first.first, cu.first.second, 2);
		}
	}

	std::pair<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>::iterator,int> findcustomer(const std::pair<int, int>& start) {
		
		distenceboard db(size);
		std::vector<std::pair<int, int>> Q{};

		db.setDis(start, 0);
		Q.push_back(start);
		while (Q.size() > 0) {

			std::vector<std::pair<int, int>>::iterator now;
			now = Q.begin();
			int min = db.getDis(now[0]);
			for (auto s = Q.begin(); s != Q.end(); s++) {
				if (min > db.getDis(s[0])) {
					min = db.getDis(s[0]);
					now = s;
				}
			}

			if (now == Q.end()) {
				return { customers.end(),-1 };
			}

			std::vector<std::pair<int, int>> tmp{};

			for (auto& dir : directions) {
				auto next = now[0] + dir;
				if (next.first > 0 && next.first <= size && next.second > 0 && next.second <= size) {

					if (db.getS(now[0])) {
						continue;
					}

					if (get(next) != 1) {
						int nowdis = db.getDis(now[0]);
						if ((db.getDis(next) == -1) || (db.getDis(next) > (nowdis + 1))) {
							db.setDis(next, nowdis + 1);
						}

						if (std::find_if(Q.begin(), Q.end(), [&, Q](std::pair<int, int>& a) {return (a.first == next.first) && (a.second == next.second); }) == Q.end()) {
							tmp.push_back(next);
						}
					}

				}
			}



			db.setS(now[0], true);
			Q.erase(now);

			for (auto& i : tmp) {
				Q.push_back(i);
			}
		}

		//db.print();

		int min = db.getDis(customers.begin()[0].first);
		auto mincu = customers.begin();

		for (auto cu = customers.begin(); cu != customers.end(); cu++) {
			if (min > db.getDis(cu[0].first)) {
				min = db.getDis(cu[0].first);
				mincu = cu;
			}
			else if (min == db.getDis(cu[0].first)) {
				if (mincu[0].first > cu[0].first) {
					min = db.getDis(cu[0].first);
					mincu = cu;
				}
				else if (mincu[0].first == cu[0].first) {
					if (mincu[0].second > cu[0].second) {
						min = db.getDis(cu[0].first);
						mincu = cu;
					}
				}
			}
		}

		if (min > energy) {
			return { customers.end(),-1 };
		}
		else
		{
			return {mincu, min};
		}


	}

	int findroute(const std::pair<int,int>& start, const std::pair<int, int>& dest,int energy) {
		distenceboard db(size);
		std::vector<std::pair<int, int>> Q{};
		
		db.setDis(start, 0);
		Q.push_back(start);
		while (Q.size() > 0) {

			std::vector<std::pair<int, int>>::iterator now;
			now = Q.begin();
			int min = db.getDis(now[0]);
			for (auto s = Q.begin(); s != Q.end(); s++) {
				if (min > db.getDis(s[0]) ){
					min = db.getDis(s[0]);
					now = s;
				}
			}

			if (now == Q.end()) {
				return -1;
			}

			std::vector<std::pair<int, int>> tmp{};

			for (auto& dir : directions) {
				auto next = now[0] + dir;
				if (next.first > 0 && next.first <= size && next.second > 0 && next.second <= size) {	

					if (db.getS(now[0])) {
						continue;
					}

					if (get(next) != 1) {
						int nowdis = db.getDis(now[0]);
						if ((db.getDis(next) == -1) || (db.getDis(next) > (nowdis + 1))) {
							db.setDis(next, nowdis + 1);
						}

						if (std::find_if(Q.begin(), Q.end(), [&, Q](std::pair<int, int>& a) {return (a.first == next.first) && (a.second == next.second); }) == Q.end()) {
							tmp.push_back(next);
						}
					}

				}
			}



			db.setS(now[0], true);
			Q.erase(now);

			for (auto& i : tmp) {
				Q.push_back(i);
			}
		}

		//db.print();

		int consume = db.getDis(dest);

		if (consume > energy) {
			return -1;
		}
		else {
			return consume;
		}
	}

	
	board(board&) = default;
	board(board&&) = default;
	board& operator= (board&) = default;
	board& operator= (board&&) = default;

	
	void print() {
		for (auto& e : bo) {
			for (auto& c : e) {
				std::cout << c;
			}
			std::cout << std::endl;
		}
	}

	int get(const std::pair<int, int>& pos) {
		return get(pos.first, pos.second);
	}

	void set(const std::pair<int, int>& pos, int data) {
		set(pos.first, pos.second, data);
	}

	
	int get(int a, int b) {
		return bo[a - 1][b - 1];
	}

	void set(int a, int b, int data) {
		bo[a - 1][b - 1] = data;
	}

	int simulateall() {
		while (!customers.empty()) {
			auto a = findcustomer(taxi);
			auto& cus = a.first;
			int consumed = a.second;

			//debugprint(consumed);

			if (consumed == -1) {
				return -1;
			}

			taxi = cus[0].first;
			energy -= consumed;

			int consumewithcustomer = findroute(taxi, cus[0].second,energy);
			//debugprint(consumewithcustomer);
			if (consumewithcustomer == -1) {
				return -1;
			}
			
			energy += consumewithcustomer;

			taxi = cus[0].second;
			customers.erase(cus);
		}

		return energy;
	}


private:
	std::vector<std::vector<int>> bo;
	int size;
	std::pair<int, int> taxi;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> customers;
	int energy;

	std::pair<int, int> right = std::pair<int, int>{0, 1};
	std::pair<int, int> left = std::pair<int, int>{ 0, -1 };
	std::pair<int, int> up = std::pair<int, int>{ -1, 0 };
	std::pair<int, int> down = std::pair<int, int>{ 1, 0 };
	
	std::vector<std::pair<int, int>> directions = { right,left,up,down };


};




int main()
{


	board b{};
	//b.print();
	std::cout << b.simulateall() << std::endl;
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
