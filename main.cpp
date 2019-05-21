#include <cstdlib>

#include "abr.cpp"

using namespace std;

template <typename T>
void afficher(T value){
    cout << value ;
}

int main(){

    BinarySearchTree<int> test;

    test.insert(10);
    test.insert(12);
    test.insert(16);
    test.insert(15);
    test.insert(7);
    test.insert(1);
    test.insert(12);
    test.insert(5);
    test.insert(11);
    test.insert(4);
    test.insert(2);
    test.insert(6);
    test.insert(0);
    test.insert(13);

    test.deleteMin();
    test.deleteMin();

    test.deleteElement(10);
    cout << boolalpha << test.contains(16) << endl;
    test.deleteElement(16);
    test.deleteElement(7);
    test.deleteElement(10);



//    test.visitPost([](int value){
//        cout << value << " ";
//    });
    test.display();
    return EXIT_SUCCESS;
}