// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 

#include <iostream>
#include<bitset>
#include <queue>
#include<stack>
#include<algorithm>
#include <vector>
#include <utility>
#include<set>
#include<unordered_set>
#include<map>
#include<memory>
#include<string>

template<typename T>
void debugprint(T t) {
	std::cout << t;
}

class accu {
public:
	std::vector<short> counts;

	bool operator== (const accu& other) {
		for (int i = 0; i < 26; i++) {
			if (counts[i] != other.counts[i]) {
				return false;
			}
		}

		return true;
	}
	accu operator- (const accu& other) {
		accu result{};
		result.init();
		for (int i = 0; i < 26; i++) {
			result.counts[i] = counts[i] - other.counts[i];
		}

		return result;
	}

	accu operator+ (const accu& other) {
		accu result{};
		result.init();
		for (int i = 0; i < 26; i++) {
			result.counts[i] = counts[i] + other.counts[i];
		}

		return result;
	}

	bool operator< (const accu& other) {
		for (int i = 0; i < 26; i++) {
			if (counts[i] < other.counts[i]) {
				return true;
			}
			else if (counts[i] > other.counts[i]) {
				return false;
			}
		}
	}
	void init() {
		counts = std::vector<short>(26);
		for (int i = 0; i < 26; i++) {
			counts[i] = 0;
		}
	}
};

class comp {
public:
	bool operator() (const accu& a, const accu& b) const {
		for (int i = 0; i < 26; i++) {
			if (a.counts[i] < b.counts[i]) {
				return true;
			}
			else if (a.counts[i] > b.counts[i]) {
				return false;
			}
		}
	}
};

int main()
{
	std::ios::sync_with_stdio(false);

	std::string sa;
	std::string sb;

	std::vector<accu> acca;
	std::vector<accu> accb;

	std::cin >> sa >> sb;

	accu acc{};
	acc.init();
	acca.push_back(acc);
	for (char a : sa) {
		acc.counts[a - 'a'] += 1;
		acca.push_back(acc);
	}

	acc.init();
	accb.push_back(acc);
	for (char b : sb) {
		acc.counts[b - 'a'] += 1;
		accb.push_back(acc);
	}

	int maxlen = std::min(sa.length(), sb.length());

	int alast = sa.length();
	int blast = sb.length();

	int max = 0;

	

	std::set<std::vector<short>> s;

	for (int len = 1; len <= maxlen; len++) {
		for (int astart = 0; astart <= alast - len; astart++) {
			accu aaa = acca[astart + len] - acca[astart];
			if (s.find(aaa.counts) == s.end()) {
				s.insert(aaa.counts);
			}

		}
	}

	for (int len = 1; len <= maxlen; len++) {
		for (int bstart = 0; bstart <= blast - len; bstart++) {
			auto same = s.find((accb[bstart + len] - accb[bstart]).counts);

			if (same != s.end()) {
				max = len;
				break;
			}
		}
	}


	std::cout << max << std::endl;

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
