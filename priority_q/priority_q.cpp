#include <functional>
#include <queue>
#include <vector>
#include <iostream>
 
namespace GC {

template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
    while(!q.empty()) {
        std::cout << q.top() << ' ';
        q.pop();
    }
    std::cout << '\n';
}

template <int I>
struct Int2Type
{
  enum { value = I };
};

// template alias example
template<typename ElementType, typename ComparisonFunc>
using pq = std::priority_queue<ElementType, std::vector<ElementType>, ComparisonFunc>;
using test = Int2Type<1>;
//using test = Int2Type<2>; // this will error if uncommented


template<typename T>
void printTest() {
    std::cout << "basic type" << std::endl;
};

template<>
void printTest<Int2Type<1>> () {
    std::cout << "Test Type" << std::endl;
};
 
}
int main() {
    std::priority_queue<int> q;
 
    const auto data = {1,8,5,6,3,4,0,9,7,2};
 
    for(int n : data)
        q.push(n);
 
    GC::print_queue(q);

    // use of template alias example. NOTE only use list init{} not ()
    GC::pq<int, std::greater<int>> q2{data.begin(), data.end()};
    /* push works for this as well
    for(int n : data)
        q2.push(n);
    */
    // direct instantiation of a priority_queue template instead of template alias. NOTE () is used
    //std::priority_queue<int, std::vector<int>, std::greater<int>> q2(data.begin(), data.end());
    GC::print_queue(q2);


    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
 
    for(int n : data)
        q3.push(n);
 
    GC::print_queue(q3);

 
    // test of multiple type aliases in one block
    std::cout << "test of multiple type aliases" << std::endl;
    std::cout << "Expect Test Type" << std::endl;
    GC::printTest<GC::test>();
    std::cout << "Expect Basic Type" << std::endl;
    GC::printTest<int>();
    return 0;
}


// Output should be:
// 9 8 7 6 5 4 3 2 1 0 
// 0 1 2 3 4 5 6 7 8 9 
// 8 9 6 7 4 5 2 3 0 1
