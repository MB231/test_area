#include <iostream>
#include <memory>
class myclass {
  public:
    int callsomefunc(int i, int j) { return (this->somefunc(i, j)); }

  private:
      int somefunc(int i, int j) { return (i + j); }
};
class otherclass {
  public:
    myclass thisclass;
};
int main() {
    std::unique_ptr<otherclass> ptr(new otherclass());

    std::cout << "output: " << ptr->thisclass.callsomefunc(10, 16) << std::endl;

    return 0;
}
