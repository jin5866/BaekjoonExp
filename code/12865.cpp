 back.cpp  이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
 

#include iostream
#includebitset
#include queue
#includepriority_queue
#includestack
#includealgorithm
#include vector
#include utility
#includeset
#includeunordered_set
#includemap
#includememory
#includestring
#includealgorithm

templatetypename T
void debugprint(T t) {
	stdcout  t;
}

stdvectorstdvectorint dp;

int nep(int i, int remainw, stdvectorint& w, stdvectorint& v) {
	if (i  0) {
		dp[i][remainw] = 0;
		return 0;
	}

	if (dp[i][remainw] != -1) {
		return dp[i][remainw];
	}

	

	if (w[i]  remainw) {
		dp[i][remainw] = nep(i - 1, remainw, w, v);
		return dp[i][remainw];
	}
	else {
		int left = nep(i - 1, remainw, w, v);
		int right = nep(i - 1, remainw - w[i], w, v);
		dp[i][remainw] = stdmax(left, v[i] + right);
		return dp[i][remainw];
	}
}

int main()
{
	stdiossync_with_stdio(false);
	stdcout.tie(0);
	stdcin.tie(0);
	
	int n, k;
	stdvectorint w, v;
	stdcin  n  k;

	dp = stdvectorstdvectorint(n, stdvectorint(k+1, -1));

	for (int i = 0; i  n; i++)
	{
		int a, b;

		stdcin  a  b;

		w.push_back(a);
		v.push_back(b);
	}

	stdcout  nep(n - 1, k, w, v)  n;

	return 0;
}



 프로그램 실행 Ctrl+F5 또는 [디버그]  [디버깅하지 않고 시작] 메뉴
 프로그램 디버그 F5 키 또는 [디버그]  [디버깅 시작] 메뉴

 시작을 위한 팁 
   1. [솔루션 탐색기] 창을 사용하여 파일을 추가관리합니다.
   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
   4. [오류 목록] 창을 사용하여 오류를 봅니다.
   5. [프로젝트]  [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트]  [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
   6. 나중에 이 프로젝트를 다시 열려면 [파일]  [열기]  [프로젝트]로 이동하고 .sln 파일을 선택합니다.
