#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string_view> Split(std::string_view str, char d)
{
    std::vector<std::string_view> r;

    size_t start = 0;
    size_t stop = str.find_first_of(d);
    while(stop != std::string_view::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));
    return r;
}

std::vector<int> ConvertToInt(const std::vector<std::string_view>& ips_s)
{
    std::vector<int> r(ips_s.size());
    for (size_t i = 0; i < ips_s.size(); ++i) {
        r[i] = std::atoi(ips_s[i].data());
    }
    return r;
}

bool Cmp(const std::vector<int>& ip)
{
    for (const int el : ip) {
        if (el == 46) {
            return true;
        }
    }
    return false;
}

template <typename Comp>
void PrintIps(const std::vector<std::vector<int>>& ips, Comp f)
{
    for (const auto& ip : ips) {
        bool is_first = true;
        if (!f(ip)) {
            continue;
        }
        for (int el : ip) {
            if (!is_first) {
                std::cout << '.';
            }
            is_first = false;
            std::cout << el;
        }
        std::cout << '\n';
    }

}

int main()
{
    std::vector<std::vector<int>> ips;
    for (std::string line; std::getline(std::cin, line);) {
        std::vector<std::string_view> ips_s = Split(line, '\t');
        ips.push_back(ConvertToInt(Split(ips_s[0], '.')));
    }
    std::sort(ips.begin(), ips.end(), [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
                                         return lhs > rhs;});
    PrintIps(ips, [](const std::vector<int>&) {return true;});
    PrintIps(ips, [](const std::vector<int>& ips) {return ips[0] == 1;});
    PrintIps(ips, [](const std::vector<int>& ips) {return ips[0] == 46 && ips[1] == 70;});
    PrintIps(ips, Cmp);
    return 0;
}
