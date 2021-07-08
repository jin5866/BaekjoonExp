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
#include<map>
#include<memory>
#include<string>

template<typename T>
void debugprint(T t) {
	std::cout << t;
}

class Node {
private:
	std::vector<std::pair<char, std::unique_ptr<Node>>> next;
	int index = -1;
	std::string substr;


public:
	int search(std::string& str,int searchIndex) {
		//std::cout << next.capacity() << std::endl;
		//std::cout << next.size() << std::endl;
		if (str.size() == searchIndex ) {
			return index;
		}
		if (substr.size() > 0) {
			return substr.find(str.substr(searchIndex)) == 0 ? index : -1;
		}

		auto a = std::find_if(next.begin(), next.end(), [&str, searchIndex](const std::pair<char, std::unique_ptr<Node>>& x) {return x.first == str[searchIndex]; });
		//auto a = next.find(str[searchIndex]);
		if (a != next.end()) {
			return a->second->search(str, searchIndex + 1);
		}

		return -1;
	}

	void push(std::string& str, int searchIndex, int value) {


		if (str.size() == searchIndex) {
			if (index == -1 ) {
				index = value;
			}
			return;
		}
		else {
			if (index == -1 ) {
				index = value;
			}
		}

		if (substr.size() == 0 && next.size() == 0 && index == value) {
			//on no more
			substr = str.substr(searchIndex);
		}
		else {
			if (substr.size() > 0) {

				next.push_back({ substr[0] ,std::make_unique<Node>() });
				next[next.size() - 1].second->push(substr, 1, index);
				substr.clear();
			}

			auto a = std::find_if(next.begin(), next.end(), [str, searchIndex](const std::pair<char, std::unique_ptr<Node>>& x) {return x.first == str[searchIndex]; });
			//auto a = next.find(str[searchIndex]);
			if (a != next.end()) {
				a->second->push(str, searchIndex + 1, value);
			}
			else {
				//next.reserve(next.size() + 1);
				next.push_back({ str[searchIndex] ,std::make_unique<Node>() });
				next[next.size() - 1].second->push(str, searchIndex + 1, value);
			}
		}

		

	}

};

class Trie {
	Node root;

public:
	int search(std::string& str) {
		return root.search(str, 0);
	}

	void push(std::string& str, int value) {
		root.push(str, 0, value);
	}
};

class BigNumber {
	std::string num;
	int e;



public:
	BigNumber(int a) {
		num = std::to_string(a);
		std::reverse(num.begin(), num.end());
		e = 0;
	}
	BigNumber() = default;
	BigNumber(const BigNumber&) = default;
	BigNumber(BigNumber&&) = default;
	BigNumber& operator= (const BigNumber&) = default;
	BigNumber& operator= (BigNumber&&) = default;

	BigNumber(std::string& num,int e) : num(num),e(e) {}
	//BigNumber(std::string num, int e) : num(num), e(e) {}

	BigNumber operator+ (const BigNumber& other) {
		std::string result;
		int mystart = 0;
		int otherstart = 0;
		int newe = 0;
		int carry = 0;

		if (e > other.e) {
			int diff = e - other.e;
			otherstart = diff;
			newe = e;
		}
		else {
			int diff = other.e - e;
			mystart = diff;
			newe = other.e;
		}

		for (; num.size() > mystart || other.num.size() > otherstart; mystart++, otherstart++) {
			char mynum = 0;
			char othernum = 0;

			if (num.size() > mystart) {
				mynum = num[mystart] - '0';
			}

			if (other.num.size() > otherstart) {
				othernum = other.num[otherstart] - '0';
			}

			char newnum = carry + mynum + othernum;

			carry = newnum / 10;
			newnum %= 10;

			result.push_back(newnum + '0');
		}

		if (carry) {
			result.push_back('1');
		}

		if (result.size() > 60) {
			int remove = result.size() - 60;
			newe += remove;

			result.erase(0, remove);
		}


		BigNumber a{ result,newe };

		return a;

	}

	std::string toString() {
		std::string s = num;
		std::reverse(s.begin(), s.end());

		s.push_back('e');
		s.append(std::to_string(e));

		return s;
	}

	std::string toFrontString() {
		std::string s = num;
		std::reverse(s.begin(), s.end());

		if (s.size() >= 40) {
			return s.substr(0, 40);
		}

		return s;
	}

};


int main()
{
	std::ios::sync_with_stdio(false);


	Trie t;
	/*std::string bb = "2222";
	BigNumber a{ bb,18 };
	BigNumber b{ bb,20 };
	BigNumber c = a + b;

	std::cout << a.toString() << std::endl;
	std::cout << b.toString() << std::endl;
	std::cout << c.toString() << std::endl;*/


	BigNumber a0{ 1 };
	BigNumber a1{ 1 };

	std::string s0 = a0.toFrontString();
	std::string s1 = a1.toFrontString();

	t.push(s0, 0);
	t.push(s1, 1);

	BigNumber n0 = a0;
	BigNumber n1 = a0;
	BigNumber n2 = a1;

	for (int i = 2; i < 100000; i++) {

		n0 = n1;
		n1 = n2;
		n2 = n1 + n0;

		std::string s = n2.toFrontString();

		t.push(s, i);
	}

	int count;

	std::cin >> count;

	for (int i = 0; i < count; i++) {
		std::string str;
		std::cin >> str;

		std::cout << "Case #" << i + 1 << ": " << t.search(str) << " "<< std::endl;
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
