
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// A node of the Huffman Tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
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

    // Moving a node upward to maintain heap order
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (heap[parent]->freq <= heap[i]->freq)
                break;

            swapNodes(parent, i);
            i = parent;
        }
    }

    // Moving a node downward to maintain heap order
    void heapifyDown(int i) {
        int size = heap.size();

        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size &&
                heap[left]->freq < heap[smallest]->freq)
                smallest = left;

            if (right < size &&
                heap[right]->freq < heap[smallest]->freq)
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

    int size() {
        return heap.size();
    }
};

// Printing Huffman codes using preorder traversal
void printCodes(Node* root, string code) {
    if (root == nullptr)
        return;

    // A leaf node represents an original character
    if (root->left == nullptr && root->right == nullptr) {
        if (code == "")
            code = "0";

        cout << root->ch << " : " << code << endl;
        return;
    }

    // Visiting  root, then left subtree, then right subtree
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// Building the Huffman Tree
Node* buildHuffmanTree(char characters[], int frequencies[], int n) {
    MinHeap minHeap;

    // Inserting all characters into the min heap
    for (int i = 0; i < n; i++) {
        minHeap.insert(new Node(characters[i], frequencies[i]));
    }

    // Keeping combining the two smallest frequency nodes
    while (minHeap.size() > 1) {
        Node* left = minHeap.extractMin();
        Node* right = minHeap.extractMin();

        // Creaine a parent node
        Node* parent = new Node('$', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        minHeap.insert(parent);
    }

    // The remaining node is the root
    return minHeap.extractMin();
}

int main() {
    int n;

    cout << "Enter number of distinct characters: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of characters." << endl;
        return 0;
    }

    char* characters = new char[n];
    int* frequencies = new int[n];

    cout << "Enter each character and its frequency:" << endl;

    for (int i = 0; i < n; i++) {
        cin >> characters[i] >> frequencies[i];

        if (frequencies[i] <= 0) {
            cout << "Frequency must be positive." << endl;
            delete[] characters;
            delete[] frequencies;
            return 0;
        }
    }

    Node* root = buildHuffmanTree(characters, frequencies, n);

    cout << "\nHuffman Codes (Preorder Traversal):" << endl;
    printCodes(root, "");

    delete[] characters;
    delete[] frequencies;

    return 0;
}

