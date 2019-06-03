#include <cstdlib>

#include "abr.cpp"

using namespace std;

template<typename T>
void afficher(T value) {
    cout << value;
}

int main() {

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
//    cout << boolalpha << test.contains(16) << endl;
    test.deleteElement(16);
    test.deleteElement(7);
    test.deleteElement(10);

    test.display();

    cout << endl;
    cout << "-----------------" << endl;
    cout << test.rank(11) << " " << test.rank(5) << " " << test.rank(12) << " "
         << test.rank(4) << " " << test.rank(6) << " " << test.rank(15) << " "
         << test.rank(2) << " " << test.rank(13) << endl;
    cout << "-----------------" << endl;

//    test.visitPost([](int value){
//        cout << value << " ";
//    });

    cout << test.size() << endl;

    cout << test.nth_element(3) << endl;

    BinarySearchTree<int> test2(test);

    BinarySearchTree<int> test3;
    test3.insert(100);

    BinarySearchTree<int> abr2;
    abr2.insert(17);
    abr2.insert(4);
    abr2.insert(1);
    abr2.insert(2);
    abr2.insert(3);
    abr2.insert(5);
    abr2.insert(6);
    abr2.insert(7);
    abr2.insert(8);
    abr2.insert(42);
    abr2.insert(45);
    abr2.insert(1);
    abr2.insert(2);

/*    abr2.insert(12);
    abr2.insert(6);
    abr2.insert(15);*/




    abr2.display();

    abr2.linearize();

    abr2.display();
    return EXIT_SUCCESS;
}