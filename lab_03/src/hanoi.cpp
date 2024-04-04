#include "hanoi.hpp"
int main() {
    LinkedList list;
    int n = 3; // Количество дисков
    hanoi(n, 1, 3, list);
    list.printList();
    return 0;
}
