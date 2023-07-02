#include "timer.h"

#include <vector>

int main()
{
    std::vector<int> v;
    v.reserve(1000000+10000);

    for (int i = 0; i < 1000000; i++) {
        Timer t("test");

        v.emplace_back(i);
    }

    for (int i =0; i< 10000; i++)
        {
            Timer t("inside");

            v.emplace_back(i);
        }

    std::cout<< v.size() << std::endl;

    Timer::outputTimings();
}