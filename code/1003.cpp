#include <iostream>
#include <tuple>
#include <vector>

std::tuple<int, int> operator + (std::tuple<int, int> a, std::tuple<int, int> b) {
    return std::make_tuple(std::get<0>(a) + std::get<0>(b), std::get<1>(a) + std::get<1>(b));
}

std::tuple<int,int> fibonacci(int n) {
    std::vector<std::tuple<int, int>> list(n + 1);
    if(n>=0)
        list[0]= std::make_tuple(1, 0);
    if(n >= 1)
        list[1]= std::make_tuple(0, 1);

    for (int i = 2; i <= n; i++) {
        list[i] = list[i - 1] + list[i - 2];
    }
    return list[n];
}

int main()
{
    int c;
    std::cin >> c;

    for (int i = 0; i < c; i++) {
        int a;
        std::cin >> a;
        auto re = fibonacci(a);

        std::cout << std::get<0>(re)<< " " << std::get<1>(re) << std::endl;
    }

}