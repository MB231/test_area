#include <iostream>
#include <memory>
#include <vector>
#include <ostream>

class Message
{
private: 
    std::unique_ptr<int> one;
    std::unique_ptr<int> two;
    std::unique_ptr<int> three;
public:
    std::vector<int> v; //made public only for ease of printing in example. Otherwise getter required
    friend void swap(Message& first, Message& second){
        first.one.swap(second.one);
        first.two.swap(second.two);
        std::swap(first.three, second.three); // std::swap can be used, but above is better
        first.v.swap(second.v);

    }
    //constructor
    Message(int first, int second, int third, std::vector<int> vect) : one(new int(first)), two(new int(second)), three(new int(third)), v(vect) {}
    //destructor
    ~Message()= default;
    //copy constructor
    Message(const Message& other)= delete;
    //copy assignment
    Message& operator=( const Message& other)= delete;
    //move constructor
    //Message(Message&& other) =delete; For testing just move assignment
    Message(Message&& other) noexcept : one(std::move(other.one)), two(std::move(other.two)), three(std::move(other.three)), v(std::move(other.v)) {
        //std::swap(*this, other);
        other.one.reset(new int(0));
        other.two.reset(new int(0));
        other.three.reset(new int(0));
        other.v.clear();
    }
    //move assignment
    /* This can be used if there is a move constructor **BUT swap will use move constructor 
     * In this example with unique ptr they will destruct going out of scope of std::swap().
     * This example will seg fault once the moved class object memeber ptrs are used
    Message& operator=(Message&& other) noexcept {
        std::swap(*this, other); 
        return *this;
    }
    */
    Message& operator=(Message&& other) noexcept {
        swap(*this, other); //**std::swap needs move constructor to function
        return *this;
    }
    int getone() {
        return *one;
    }
    int gettwo() {
        return *two;
    }
    int getthree() {
        return *three;
    }
};


int main(int argc, char *argv[])
{
    int once(1);
    int twice(2);
    int thrice(3);
    std::vector<int> vec{1,2,3,4,5,6};
    std::cout << "test move consructor" << std::endl;
    Message message(once, twice, thrice, vec);
    Message newMessage(std::move(message));
    std::cout <<std::endl << "moved to class" << std::endl;
    std::cout << newMessage.getone() <<std::endl;
    std::cout << newMessage.gettwo() <<std::endl;
    std::cout << newMessage.getthree() <<std::endl;
    for (auto i = newMessage.v.begin(); i!= newMessage.v.end(); ++i) { std::cout << *i << ' ';}
    std::cout <<std::endl << "moved from class ** notice cleared vector doesn't print" << std::endl;
    std::cout << message.getone() <<std::endl;
    std::cout << message.gettwo() <<std::endl;
    std::cout << message.getthree() <<std::endl;
    for (auto i = message.v.begin(); i!= message.v.end(); ++i) { std::cout << *i << ' ';}

    std::cout << "test move assignment" <<std::endl;
    Message othermessage(once, twice, thrice, vec);
    std::vector<int> stuff{13,14,15,16};
    Message newerMessage(4,5,6, stuff); 
    newerMessage = std::move(othermessage);
    std::cout <<std::endl << "moved to class" << std::endl;
    std::cout << newerMessage.getone() <<std::endl;
    std::cout << newerMessage.gettwo() <<std::endl;
    std::cout << newerMessage.getthree() <<std::endl;
    for (auto i = newerMessage.v.begin(); i!= newerMessage.v.end(); ++i) { std::cout << *i << ' ';}
    std::cout <<std::endl << "moved from class **notice swapped not zeroed values" << std::endl;
    std::cout << othermessage.getone() <<std::endl;
    std::cout << othermessage.gettwo() <<std::endl;
    std::cout << othermessage.getthree() <<std::endl;
    for (auto i = othermessage.v.begin(); i!= othermessage.v.end(); ++i) { std::cout << *i << ' ';}
    return 0;
}
