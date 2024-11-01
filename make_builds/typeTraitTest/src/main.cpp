#include <iostream>
#include <memory>
#include <map>
#include <ostream>
#include <type_traits>
#include "TimerNoCopy.hpp"

int main(int argc, char *argv[]) {

    std::cout << "\n\n\nMOVE CONSTRUCT TEST\n\n\n";
    std::cout << std::boolalpha
              << "TimerNoCopy is nothrow move-constructible? "
              << std::is_nothrow_move_constructible<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is move-constructible? "
              << std::is_move_constructible<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is trivially move-constructible? "
              << std::is_trivially_move_constructible<TimerNoCopy>::value << '\n';
    std::cout << "\n\n\nMOVE ASSIGN TEST\n\n\n";
    std::cout << std::boolalpha
              << "TimerNoCopy is nothrow move-assignable? "
              << std::is_nothrow_move_assignable<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is move-assignable? "
              << std::is_move_assignable<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is trivially move-assignable? "
              << std::is_trivially_move_assignable<TimerNoCopy>::value << '\n';

    std::cout << "\n\n\nCOPY CONSTRUCT TEST\n\n\n";
    std::cout << std::boolalpha
              << "TimerNoCopy is copy-constructible? "
              << std::is_copy_constructible<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is trivially-copy-constructible? "
              << std::is_trivially_copy_constructible<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is nothrow copy-constructible? "
              << std::is_nothrow_copy_constructible<TimerNoCopy>::value << '\n';

    std::cout << "\n\n\nCOPY ASSIGN TEST\n\n\n";
    std::cout << std::boolalpha
              << "TimerNoCopy is trivially-copy-assignable? "
              << std::is_trivially_copy_assignable<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is nothrow copy-assignable? "
              << std::is_nothrow_copy_assignable<TimerNoCopy>::value << '\n';

    std::cout << "\n\n\nDEFAULT CONSTRUCT  TEST\n\n\n";
    std::cout << std::boolalpha
              << "TimerNoCopy is nothrow default_constructible? "
              << std::is_nothrow_default_constructible<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is default-constructible? "
              << std::is_default_constructible<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is trivially default_constructible? "
              << std::is_trivially_default_constructible<TimerNoCopy>::value << '\n';

    std::cout << "\n\n\nDEFAULT CONSTRUCT  TEST\n\n\n";
    std::cout << std::boolalpha
              << "TimerNoCopy is nothrow destructible? "
              << std::is_nothrow_destructible<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is trivially destructible? "
              << std::is_trivially_destructible<TimerNoCopy>::value << '\n'
              << "TimerNoCopy is destructible? "
              << std::is_destructible<TimerNoCopy>::value << '\n';

    std::cout << "\n\n\nDEFAULT CONSTRUCT  TEST\n\n\n";
    std::cout << std::boolalpha
              << "TimerNoCopy is trivially assignable from const TimerNoCopy? "
              << std::is_trivially_assignable<TimerNoCopy, const TimerNoCopy>::value << '\n';

    return 0;
}
