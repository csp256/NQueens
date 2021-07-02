#include "Timer.h"
#include "NQueens.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

int main(int argc, char *argv[])
try
{
    int first = 0;
    int last = 12;

    if (argc == 2) {
        last = std::atoi(argv[1]);
    } else if (argc == 3) {
        first = std::atoi(argv[1]);
        last = std::atoi(argv[2]);
    }

    auto const hardcoded = NQueens::hardcoded();

    std::cout << "n\t\tsolutions\t\tseconds\n\n";
    for (int n = first; n <= last; n++) {
        Timer timer;
        auto solution_count = NQueens::count_solutions(n);
        auto seconds = timer.seconds();

        std::cout << std::to_string(n) 
            << "\t\t" << std::to_string(solution_count) 
            << "\t\t" << seconds << std::endl;

        if (solution_count != hardcoded[n]) {
            std::cout << "\t\tFAILURE" << std::endl;
        }
    }

    return 0;
}
catch (std::exception const& ex)
{
    std::cout << "\nEXCEPTION\n\t" << ex.what() << std::endl;
    return -1;
}