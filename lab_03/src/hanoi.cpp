#include <iostream>
using namespace std;

class Node {
public:
    int from, to;
    Node* prev;
    Node* next;

    Node(int from, int to) {
        this->from = from;
        this->to = to;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(int from, int to) {
        Node* newptr = new Node(from, to);
        if (tail == nullptr) 
        {
            head = tail = newptr;
        } 
        else 
        {
            tail->next = newptr;
            newptr->prev = tail;
            tail = newptr;
        }
    }

    void printList() {
        Node* current = head;
        while (current != nullptr) {
            cout << "С " << current->from << " переместить на: " << current->to << endl;
            current = current->next;
        }
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

void hanoi(int n, int from, int to, LinkedList& list) {
    if (n == 1) {
        list.push_back(from, to);
        return;
    }
    int other;
    other = 6 - from - to;
    hanoi(n - 1, from, other, list);
    list.push_back(from, to);
    hanoi(n - 1, other, to, list);
}

int main() {
    LinkedList list;
    int n = 3; // Количество дисков
    hanoi(n, 1, 3, list);
    list.printList();
    return 0;
}