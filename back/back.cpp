// back.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include<stack>
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


class machine {

public:
	machine(int memsize) : mem( memsize ,0) {
		
	}

	machine() {

	}


	machine(machine&) = default;
	machine(machine&&) = default;
	machine& operator= (machine&) = default;
	machine& operator= (machine&&) = default;

	void setcom(const std::vector<char>& comm) {
		std::stack<int> opened{};

		for (int i = 0; i < comm.size(); i++) {
			switch (comm[i])
			{
			case '-':
				com.push_back({ commandtype::pminus,0 });
				break;
			case '+':
				com.push_back({ commandtype::ppuls,0 });
				break;
			case '<':
				com.push_back({ commandtype::pleft,0 });
				break;
			case '>':
				com.push_back({ commandtype::pright,0 });
				break;
			case '[':
				com.push_back({ commandtype::jumprightifzero,0 });
				opened.push(i);
				break;
			case ']':
			{com.push_back({ commandtype::jumpleftifnotzero,0 });
			int pair = opened.top();
			opened.pop();
			com[pair].data = i;
			com[i].data = pair; }
				break;
			case '.':
				com.push_back({ commandtype::print,0 });
				break;
			case ',':
				com.push_back({ commandtype::read,0 });
				break;
			default:
				break;
			}
		}
	}

	void setinput(const std::vector<char>& input)  {
		this->input = std::vector<char>(input);
		nowread = 0;
	}

	void run() {
		std::vector<int> sample{};

		while (nowrun < com.size()&&counter <= 100000000) {
			runonce();
			++counter;

			if (counter % 9803 == 0) {
				sample.push_back(nowrun);
			}
		}

		if (counter > 50000000) {
			int max = 0;
			
			if (com[lastloop].lastcall <= 50000000) {
				for (int i = lastloop - 1; i >= 0; i--) {
					if (com[i].ctype == commandtype::jumpleftifnotzero && com[i].lastcall >= 50000000) {
						lastloop = i;
						break;
					}
				}
			}

			std::cout << "Loops " << com[lastloop].data << " " << lastloop << std::endl;
		}
		else {
			std::cout << "Terminates"<<std::endl;
		}
	}



private:

	enum class commandtype : int {
		pminus = 0,
		ppuls,
		pleft,
		pright,
		jumprightifzero,
		jumpleftifnotzero,
		print,
		read
	};
	struct command {
		command(commandtype ctype, int data) : ctype(ctype) ,data(data){

		}

		commandtype ctype;
		int data;
		int lastcall = 0;
	};
	std::vector<char> mem;
	std::vector<command> com;
	std::vector<char> input;
	int nowread;

	int pointer = 0;
	int nowrun = 0;
	int counter = 0;
	
	int lastloop = 0;

	void runonce() {
		switch (com[nowrun].ctype)
		{
		case machine::commandtype::pminus:
			--(mem[pointer]);
			break;
		case machine::commandtype::ppuls:
			++(mem[pointer]);
			break;
		case machine::commandtype::pleft:
			pointer--;
			if (pointer < 0) {
				pointer += mem.size();
			}
			break;
		case machine::commandtype::pright:
			pointer = (pointer + 1) % mem.size();
			break;
		case machine::commandtype::jumprightifzero:
			if (mem[pointer] == 0) {
				nowrun = (com[nowrun].data );
			}
			break;
		case machine::commandtype::jumpleftifnotzero:
			if (mem[pointer] != 0) {
				if (lastloop < nowrun) {
					lastloop = nowrun;
				}
				com[nowrun].lastcall = counter;
				nowrun = (com[nowrun].data );
				
			}
			break;
		case machine::commandtype::print:
			//std::cout << mem[pointer];
			break;
		case machine::commandtype::read:
			if (nowread < input.size()) {
				mem[pointer] = input[nowread];
				nowread++;
			}
			else
			{
				mem[pointer] = 255;
			}
			break;
		default:
			break;
		}

		++nowrun;
	}
};



int main()
{
	int mc;
	std::cin >> mc;

	std::vector<machine> machs(mc);
	
	for (auto& mach : machs) {
		int memsize;
		int commsize;
		int inputsize;
		std::cin >> memsize;
		std::cin >> commsize;
		std::cin >> inputsize;

		std::vector<char> comm(commsize);
		std::vector<char> input(inputsize);

		for (char& com : comm) {
			std::cin >> com;
		}

		for (char& in : input) {
			std::cin >> in;
		}

		mach = machine(memsize);

		mach.setcom(comm);
		mach.setinput(input);

	}

	for (auto& mach : machs) {
		mach.run();
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
