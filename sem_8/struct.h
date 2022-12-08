struct Node {
    int value;
    char* pathname_cr = nullptr;
    char* pathname_last = nullptr;
    Node(int val, char* name) {
        value = val;
        pathname_cr = name;
        pathname_last = name;
    }
    bool IsDefined() { return pathname != nullptr; }
};

typedef struct Node Node;
