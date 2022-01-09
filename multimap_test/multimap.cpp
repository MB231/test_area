#include <iostream>
#include <map>
#include <utility>

// Message class holding message data and its own meta data
class Message {
        public:
    Message(int pri, int type, int data) : priority(pri), type(type), data(data) {}
    int priority = 0;
    int type = 0;
    int data = 0;
};

int main() {
    // Create Multimap and classes that are going in. Key is priority level, then the message itself that will also get
    // sorted for type later
    std::multimap<int, Message> M;
    Message test1(1, 1, 1);
    Message test2(1, 2, 1);
    Message test3(5, 3, 1);
    Message test4(2, 4, 1);
    Message test5(2, 5, 1);
    Message swapM(2, 4, 10);

    // load map up
    M.emplace(test1.priority, test1);
    M.emplace(test2.priority, test2);
    M.emplace(test3.priority, test3);
    M.emplace(test4.priority, test4);
    M.emplace(test5.priority, test5);
    // print full map. Notice multiple values per key
    std::cout << "Full multimap" << std::endl;
    for (auto const& m : M) {
        std::cout << m.first << ", " << m.second.type << std::endl;
    }

    // ***NOTE*** using find returns iterator to ANY of the elements matching the key. Though multimap is in order of
    // key there is no defined order for additional values of that key, though generally in order of entry. Use the
    // equal range to return a PAIR of iterators with all the matching elements to the key and then loop through those.
    std::cout << "range from multimap" << std::endl;
    auto range = M.equal_range(2);
    for (auto m = range.first; m != range.second; m++) {
        std::cout << m->first << ", " << m->second.type << " data: " << m->second.data << std::endl;
    }
    // Example of finding first all matching values to key then finding a specific element from that range and swapping
    // it out. Here a swap function could be used, but erasing and emplacing negates necessity for a defined swap
    // function to exist.
    for (auto m = range.first; m != range.second; m++) {
        if (m->second.type == 4) {
            M.erase(m);
            M.emplace(swapM.priority, swapM);
        }
    }
    // Must get new range after erasing one of the elements in the range and emplacing a new element in the map
    range = M.equal_range(2);
    std::cout << "range from multimap AFTER swap" << std::endl;
    for (auto m = range.first; m != range.second; m++) {
        std::cout << m->first << ", " << m->second.type << " data: " << m->second.data << std::endl;
    }
    // show what an empty check would do for range
    std::cout << "empty range check" << std::endl;
    range = M.equal_range(3);
    if (range.first == range.second) {
        std::cout << "found empty range" << std::endl;
    }
    for (auto m = range.first; m != range.second; m++) {
        std::cout << m->first << ", " << m->second.type << " data: " << m->second.data << std::endl;
    }
    // Even if a single element returned iterators do not equal one another
    std::cout << "Single Element range check" << std::endl;
    range = M.equal_range(5);
    if (range.first == range.second) {
        std::cout << "found empty range" << std::endl;
    }
    for (auto m = range.first; m != range.second; m++) {
        std::cout << m->first << ", " << m->second.type << " data: " << m->second.data << std::endl;
    }
    return 0;
}
