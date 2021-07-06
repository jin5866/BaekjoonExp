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

template<typename T>
void debugprint(T t) {
	std::cout << t;
}

std::vector<int> primes{};
std::bitset<10000001> nums = {}; //false is prime
const int BIG_NUM = 1000000007;

// a * b
int product(int a, int b) {
	
	long long re = (long long)a * (long long)b;
	return re % BIG_NUM;
}
// a ^ b
int power(int a, int b) {
	
	int result = 1;
	int remain = 1;

	int apowern = 1;

	// a ^ 1
	remain = b % 2;
	b = b / 2;
	apowern = a;

	if (remain == 1) {
		result = product(result, apowern);
	}

	for (; b > 0; ) {
		remain = b % 2;
		b = b / 2;
		apowern = product(apowern,apowern);

		if (remain == 1) {
			result = product(result, apowern);
		}
	}

	return result;
}

void setPrimes(int max) {
	
	for (int i = 2; i <= 10000000; i++) {
		if (!nums[i]) {
			//if prime
			primes.push_back(i);
			for (int j = 2; j * i <= 10000000; j++) {
				nums[j * i] = true;
			}
		}
	}


	//for (; num <= max; num += 2) {
	//	bool isPrime = true;
	//	//check prime
	//	for (auto s = primes.begin(); s[0]*s[0] <= num ; s++) {
	//		if (num % s[0] == 0) {
	//			isPrime = false;
	//			break;
	//		}
	//	}

	//	if (isPrime) {
	//		primes.push_back(num);
	//	}
	//}
}


int main()
{
	std::ios::sync_with_stdio(false);

	//primes.push_back(2);
	//primes.push_back(3);
	//std::cout<<power(2, 31);
	
	setPrimes(1);

	while (true)
	{
		int num;
		std::cin >> num;
		if (num == 0) break;
		

		std::vector<int> counts{};

		int result = 1;

		for (auto s = primes.begin(); s != primes.end() && s[0] <= num; s++) {
			int numtmp = num;
			int count = 0;

			while (numtmp != 0) {
				count += numtmp / s[0];
				numtmp /= s[0];
			}

			count = count / 2 * 2;
			result = product(result, power(s[0], count));
			//counts.push_back(count);
		}

		std::cout << result << std::endl;


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
