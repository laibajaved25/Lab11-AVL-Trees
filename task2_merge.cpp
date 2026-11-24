
#include <iostream>
#include <vector>
using namespace std;

// Node of a linked list
struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Custom Min Heap
class MinHeap {
private:
    vector<Node*> heap;

    void swapNodes(int i, int j) {
        Node* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // Moving smaller element upward
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (heap[parent]->data <= heap[i]->data)
                break;

            swapNodes(parent, i);
            i = parent;
        }
    }

    // Moving smaller element downward
    void heapifyDown(int i) {
        int size = heap.size();

        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size &&
                heap[left]->data < heap[smallest]->data)
                smallest = left;

            if (right < size &&
                heap[right]->data < heap[smallest]->data)
                smallest = right;

            if (smallest == i)
                break;

            swapNodes(i, smallest);
            i = smallest;
        }
    }

public:
    void insert(Node* node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    Node* extractMin() {
        if (heap.empty())
            return nullptr;

        Node* minimum = heap[0];

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return minimum;
    }

    bool isEmpty() {
        return heap.empty();
    }
};

// Merging K sorted linked lists
Node* mergeKLists(vector<Node*>& lists) {
    MinHeap minHeap;

    // Inserting the first node of every non-empty list
    for (int i = 0; i < lists.size(); i++) {
        if (lists[i] != nullptr) {
            minHeap.insert(lists[i]);
        }
    }

    // Dummy node helps build the final linked list
    Node dummy(-1);
    Node* tail = &dummy;

    while (!minHeap.isEmpty()) {

        // Removing the smallest node from the heap
        Node* smallest = minHeap.extractMin();

        // Saving its next node
        Node* nextNode = smallest->next;

        // Adding the next node of the same list to the heap
        if (nextNode != nullptr) {
            minHeap.insert(nextNode);
        }

        // Attaching the smallest node to the merged list
        tail->next = smallest;
        tail = smallest;
    }

    // Ending the merged linked list
    tail->next = nullptr;

    return dummy.next;
}

// Displaying the linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data;

        if (head->next != nullptr)
            cout << " -> ";

        head = head->next;
    }

    cout << endl;
}

int main() {
    int k;

    cout << "Enter number of linked lists: ";
    cin >> k;

    if (k <= 0) {
        cout << "Invalid number of linked lists." << endl;
        return 0;
    }

    vector<Node*> lists(k, nullptr);

    // Taking input for every sorted linked list
    for (int i = 0; i < k; i++) {
        int n;

        cout << "Enter number of elements in list " << i + 1 << ": ";
        cin >> n;

        if (n < 0) {
            cout << "Invalid list size." << endl;
            return 0;
        }

        Node* head = nullptr;
        Node* tail = nullptr;

        cout << "Enter " << n << " elements in ascending order: ";

        for (int j = 0; j < n; j++) {
            int value;
            cin >> value;

            Node* newNode = new Node(value);

            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        lists[i] = head;
    }

    // Merging all lists
    Node* mergedHead = mergeKLists(lists);

    cout << "\nMerged Sorted Linked List:" << endl;
    printList(mergedHead);

    // Freeing the allocated memory
    while (mergedHead != nullptr) {
        Node* temp = mergedHead;
        mergedHead = mergedHead->next;
        delete temp;
    }

    return 0;
}

