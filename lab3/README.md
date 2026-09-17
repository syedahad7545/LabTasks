# Lab 03: Advanced Singly Linked List Problems and Doubly Linked Lists

This directory contains simple, robust C++ solutions for all tasks of Lab 03. All solutions adhere strictly to the time and space complexity constraints, do not use STL containers, avoid memory leaks, and handle edge cases (empty lists, single-node lists, boundary conditions).

---

## Tasks Overview

### Task 1: Complete the Singly Linked List ADT (Deletion)
- **File**: `task1.cpp`
- **Implemented Functions**:
  - `deleteAtHead()`: Removes the node at the head in **$\mathcal{O}(1)$** time.
  - `deleteAtTail()`: Removes the node at the tail in **$\mathcal{O}(n)$** time (without a tail pointer).
  - `~LinkedList()`: Destructor that cleans up all dynamically allocated nodes in **$\mathcal{O}(n)$** time.
- **Key Behavior**:
  - Safely handles deletion on empty lists without crashing.
  - Resets `head` to `nullptr` when deleting the only remaining node.

### Task 2: Reverse a Linked List (Iterative)
- **File**: `task2.cpp`
- **Function**: `void reverse();`
- **Time Complexity**: **$\mathcal{O}(n)$** (single linear pass).
- **Space Complexity**: **$\mathcal{O}(1)$** extra space (in-place pointer reversal using `prev`, `curr`, `nextNode`).
- **Restrictions**: No recursion, no auxiliary arrays or STL containers.

### Task 3: Merge Two Sorted Linked Lists
- **File**: `task3.cpp`
- **Function**: `void mergeSorted(LinkedList<T>& other);`
- **Time Complexity**: **$\mathcal{O}(n + m)$** where $n$ and $m$ are list sizes.
- **Space Complexity**: **$\mathcal{O}(1)$** auxiliary space (purely in-place node relinking).
- **Key Behavior**:
  - Allocates no new nodes.
  - Leaves the `other` list empty (`other.head = nullptr`) after merging.
  - Fully handles empty list cases.

### Task 4: Complete the Doubly Linked List ADT
- **File**: `task4.cpp`
- **Class**: `DoublyLinkedList<T>` with nested `Node` (`data`, `prev`, `next`).
- **Complexity Requirements**:
  - `insertAtHead()`: **$\mathcal{O}(1)$**
  - `insertAtTail()`: **$\mathcal{O}(n)$** (no tail pointer)
  - `deleteAtHead()`: **$\mathcal{O}(1)$**
  - `deleteAtTail()`: **$\mathcal{O}(n)$** (no tail pointer)
  - `display()`: **$\mathcal{O}(n)$**
  - `displayReverse()`: **$\mathcal{O}(n)$** (walks to tail and traverses backward using `prev` pointers)
  - `size()`: **$\mathcal{O}(n)$** (on-demand counting)
  - `isEmpty()`: **$\mathcal{O}(1)$**
  - `~DoublyLinkedList()`: **$\mathcal{O}(n)$**
- **Key Behavior**:
  - Correctly maintains both `next` and `prev` pointers in both directions across all operations.
  - Empty lists display `"List is empty."` cleanly.

### Task 5: Palindrome Check (Doubly Linked List)
- **File**: `task5.cpp`
- **Function**: `bool isPalindrome();`
- **Time Complexity**: **$\mathcal{O}(n)$** (finds tail in $\mathcal{O}(n)$, inward comparison takes $\le n/2$ steps).
- **Space Complexity**: **$\mathcal{O}(1)$** extra space (two pointers inward traversal, no auxiliary arrays).
- **Key Behavior**:
  - Empty and single-node lists are correctly evaluated as palindromes.
  - Handles both even-length and odd-length palindromes.

### Task 6: Delete a Given Node
- **File**: `task6.cpp`
- **Function**: `void deleteNode(Node* nodeToDelete);`
- **Time Complexity**: **$\mathcal{O}(1)$** (unlinks node directly using its own `prev` and `next` pointers without traversing from head).
- **Space Complexity**: **$\mathcal{O}(1)$**.
- **Key Behavior**:
  - Handles deleting the `head` node correctly.
  - Handles deleting middle and `tail` nodes correctly.

---

## How to Compile and Run

Each task is self-contained with its own `main()` test driver.

### Compiling individual tasks:
```bash
g++ -std=c++17 -Wall -Wextra task1.cpp -o task1 && ./task1
g++ -std=c++17 -Wall -Wextra task2.cpp -o task2 && ./task2
g++ -std=c++17 -Wall -Wextra task3.cpp -o task3 && ./task3
g++ -std=c++17 -Wall -Wextra task4.cpp -o task4 && ./task4
g++ -std=c++17 -Wall -Wextra task5.cpp -o task5 && ./task5
g++ -std=c++17 -Wall -Wextra task6.cpp -o task6 && ./task6
```

### Or using CMake:
```bash
cmake -B build
cmake --build build
./build/task1
```
