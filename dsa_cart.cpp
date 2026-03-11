/*
 * ============================================================
 *   DSA-Enhanced Shopping Cart  (dsa_cart.cpp)
 *
 *   This file reimplements the cart from cart.cpp using six
 *   core Data Structures and Algorithms concepts:
 *
 *   Data Structures
 *     1. Singly Linked List  — stores cart items
 *     2. Stack (LIFO)        — stores undo history
 *
 *   Algorithms
 *     3. Bubble Sort         — sorts cart items by price    O(n^2)
 *     4. Merge Sort          — sorts catalog alphabetically O(n log n)
 *     5. Linear Search       — searches unsorted catalog    O(n)
 *     6. Binary Search       — searches sorted catalog      O(log n)
 *
 *   All cart features from cart.cpp are preserved, plus:
 *     - Undo last action  (powered by the Stack)
 *     - Sort cart by price  (powered by Bubble Sort)
 *     - Search catalog demo  (Linear Search vs Binary Search)
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ============================================================
//  BASE DATA TYPE: Item
// ============================================================
struct Item {
    string name;
    int price;
    int quantity;
};

// ============================================================
//  DATA STRUCTURE 1: SINGLY LINKED LIST
//
//  A linked list is a sequence of nodes where each node holds
//  data and a pointer to the next node.
//
//  HEAD -> [Node1] -> [Node2] -> [Node3] -> nullptr
//
//  Time Complexity:
//    Append (insert at end) : O(n)  — must traverse to end
//    Remove by index        : O(n)  — must traverse to position
//    Traverse all nodes     : O(n)
//  Space Complexity: O(n)
//
//  Contrast with std::vector (used in cart.cpp):
//    Vector random access is O(1), but its memory is a
//    contiguous block that must be reallocated when it grows.
//    A linked list allocates each node independently — no
//    reallocation, but no O(1) random access.
// ============================================================
struct CartNode {
    Item data;
    CartNode* next;
    CartNode(const Item& item) : data(item), next(nullptr) {}
};

class LinkedListCart {
private:
    CartNode* head;
    int size;

public:
    LinkedListCart() : head(nullptr), size(0) {}

    ~LinkedListCart() { clear(); }

    // Append a new node at the end — O(n)
    void append(const Item& item) {
        CartNode* newNode = new CartNode(item);
        if (!head) {
            head = newNode;
        } else {
            CartNode* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = newNode;
        }
        size++;
    }

    // Remove node at given index — O(n)
    bool removeAt(int index) {
        if (index < 0 || index >= size || !head) return false;
        CartNode* temp;
        if (index == 0) {
            temp = head;
            head = head->next;
        } else {
            CartNode* cur = head;
            for (int i = 0; i < index - 1; i++) cur = cur->next;
            temp = cur->next;
            cur->next = temp->next;
        }
        delete temp;
        size--;
        return true;
    }

    // Delete all nodes and reset the list — O(n)
    void clear() {
        while (head) {
            CartNode* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    // Return pointer to item at given index — O(n)
    Item* at(int index) {
        if (index < 0 || index >= size) return nullptr;
        CartNode* cur = head;
        for (int i = 0; i < index; i++) cur = cur->next;
        return &cur->data;
    }

    CartNode* getHead() const { return head; }
    int getSize()       const { return size; }
    bool isEmpty()      const { return size == 0; }
};

// ============================================================
//  DATA STRUCTURE 2: STACK  (LIFO — Last In, First Out)
//
//  A stack only allows insert (push) and remove (pop) from
//  the same end, called the top.  The last item pushed is
//  always the first item popped — perfect for undo history.
//
//  TOP  [Action3]  <- most recent, popped first
//       [Action2]
//       [Action1]  <- oldest, popped last
//
//  Time Complexity:
//    Push : O(1)
//    Pop  : O(1)
//    Peek : O(1)
//  Space Complexity: O(n)
// ============================================================
struct UndoAction {
    string type;  // "ADD_NEW", "ADD_QTY", or "REMOVE"
    Item item;
};

struct StackNode {
    UndoAction data;
    StackNode* next;
    StackNode(const UndoAction& a) : data(a), next(nullptr) {}
};

class UndoStack {
private:
    StackNode* top;
    int size;

public:
    UndoStack() : top(nullptr), size(0) {}

    ~UndoStack() {
        while (top) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // Push a new action onto the top — O(1)
    void push(const UndoAction& action) {
        StackNode* node = new StackNode(action);
        node->next = top;
        top = node;
        size++;
    }

    // Pop the top action — O(1)
    bool pop(UndoAction& out) {
        if (!top) return false;
        out = top->data;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        size--;
        return true;
    }

    bool isEmpty() const { return !top; }
    int getSize()  const { return size; }
};

// ============================================================
//  ALGORITHM 1: BUBBLE SORT  (sort cart items by price, asc)
//
//  Compare adjacent elements and swap them if they are in
//  the wrong order. Repeat until no swaps occur in a pass.
//
//  Example: [1000, 50, 2000]
//    Pass 1: compare(1000,50)->swap   -> [50, 1000, 2000]
//            compare(1000,2000)->ok   -> [50, 1000, 2000]
//    Pass 2: no swaps needed.  Done!
//
//  Time Complexity : O(n^2) average and worst case
//  Space Complexity: O(1) in-place
// ============================================================
void bubbleSort(vector<Item>& items) {
    int n = (int)items.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].price > items[j + 1].price) {
                Item temp  = items[j];
                items[j]   = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

// ============================================================
//  ALGORITHM 2: MERGE SORT  (sort catalog alphabetically)
//
//  Divide the array in half, recursively sort each half,
//  then merge the two sorted halves into one sorted array.
//
//  Example: ["Rolex", "HP Legion", "Durag"]
//    Split : ["Rolex", "HP Legion"]  and  ["Durag"]
//    Sort  : ["HP Legion", "Rolex"]  and  ["Durag"]
//    Merge : ["Durag", "HP Legion", "Rolex"]
//
//  Time Complexity : O(n log n) always
//  Space Complexity: O(n) auxiliary (for the temporary arrays)
// ============================================================
void merge(vector<Item>& items, int left, int mid, int right) {
    vector<Item> L(items.begin() + left,  items.begin() + mid + 1);
    vector<Item> R(items.begin() + mid + 1, items.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < (int)L.size() && j < (int)R.size()) {
        items[k++] = (L[i].name <= R[j].name) ? L[i++] : R[j++];
    }
    while (i < (int)L.size()) items[k++] = L[i++];
    while (j < (int)R.size()) items[k++] = R[j++];
}

void mergeSort(vector<Item>& items, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(items, left, mid);
        mergeSort(items, mid + 1, right);
        merge(items, left, mid, right);
    }
}

// ============================================================
//  ALGORITHM 3: LINEAR SEARCH
//
//  Scan every element one by one from the start until the
//  target is found or the end is reached.
//  Works on UNSORTED data.
//
//  Time Complexity : O(n) worst case
//  Space Complexity: O(1)
//
//  Returns the index of the found item, or -1 if not found.
// ============================================================
int linearSearch(const vector<Item>& catalog, const string& name) {
    for (int i = 0; i < (int)catalog.size(); i++) {
        if (catalog[i].name == name) return i;
    }
    return -1;
}

// ============================================================
//  ALGORITHM 4: BINARY SEARCH
//
//  Check the middle element; if not the target, discard the
//  half where the target cannot be.  Repeat on the remaining
//  half.  REQUIRES sorted input to work correctly.
//
//  Time Complexity : O(log n)
//  Space Complexity: O(1) iterative
//
//  Returns the index of the found item, or -1 if not found.
// ============================================================
int binarySearch(const vector<Item>& sortedCatalog, const string& name) {
    int low = 0, high = (int)sortedCatalog.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if      (sortedCatalog[mid].name == name) return mid;
        else if (sortedCatalog[mid].name <  name) low  = mid + 1;
        else                                       high = mid - 1;
    }
    return -1;
}

// ============================================================
//  CART FUNCTIONS  (same interface as cart.cpp, different impl)
// ============================================================

void displayCart(const LinkedListCart& cart) {
    cout << "========= Cart (Linked List) ==========" << endl;
    if (!cart.isEmpty()) {
        CartNode* cur = cart.getHead();
        int i = 1;
        while (cur) {
            cout << "\n" << i++ << ". " << cur->data.name
                 << " - " << cur->data.quantity << " pcs"
                 << " - $" << cur->data.price * cur->data.quantity;
            cur = cur->next;
        }
    } else {
        cout << "\ncart is empty" << endl;
    }
    cout << "\n=======================================" << endl;
}

void checkout(LinkedListCart& cart) {
    int decision;
    cout << "Proceed to checkout ??\n1. yes\n2. no" << endl;
    cin >> decision;
    if (decision == 1) {
        if (!cart.isEmpty()) {
            int total = 0;
            CartNode* cur = cart.getHead();
            while (cur) {
                total += cur->data.price * cur->data.quantity;
                cur = cur->next;
            }
            cout << "Pay $" << total << " ?\n1. yes\n2. no" << endl;
            cin >> decision;
            if (decision == 1) {
                cout << "$" << total << " paid successfully" << endl;
                cart.clear();
            } else if (decision == 2) {
                return;
            } else {
                cout << "invalid operation" << endl;
            }
        } else {
            cout << "cart is empty" << endl;
        }
    } else if (decision == 2) {
        return;
    } else {
        cout << "invalid operation" << endl;
    }
}

void clearCart(LinkedListCart& cart) {
    if (!cart.isEmpty()) {
        int decision;
        cout << "By proceeding, you will remove all items from your cart. Proceed?\n1. yes\n2. no" << endl;
        cin >> decision;
        if (decision == 1) {
            cout << "You have successfully cleared your cart" << endl;
            cart.clear();
        } else if (decision == 2) {
            return;
        } else {
            cout << "invalid option" << endl;
        }
    } else {
        cout << "cart is empty" << endl;
    }
}

void addItem(LinkedListCart& cart, const vector<Item>& catalog, UndoStack& history) {
    bool done = false;
    int decision;
    while (!done) {
        cout << "======= Catalog ======" << endl;
        for (int i = 0; i < (int)catalog.size(); i++) {
            cout << i + 1 << ". " << catalog[i].name << " - $" << catalog[i].price << "\n";
        }
        cout << "======================\n";
        cin >> decision;

        if (decision >= 1 && decision <= (int)catalog.size()) {
            const Item& selected = catalog[decision - 1];

            // Linear search through linked list to check if item is already in cart
            bool inCart = false;
            CartNode* cur = cart.getHead();
            while (cur) {
                if (cur->data.name == selected.name) {
                    cur->data.quantity++;
                    inCart = true;
                    history.push({"ADD_QTY", selected});
                    break;
                }
                cur = cur->next;
            }
            if (!inCart) {
                cart.append(selected);
                history.push({"ADD_NEW", selected});
            }

            cout << "Is that all??\n1. No, add more\n2. yes" << endl;
            cin >> decision;
            if (decision == 2) {
                done = true;
            } else if (decision != 1) {
                cout << "invalid option" << endl;
                done = true;
            }
        } else {
            cout << "No such item" << endl;
            done = true;
        }
    }
}

void removeItem(LinkedListCart& cart, UndoStack& history) {
    if (!cart.isEmpty()) {
        int decision;
        cout << "What item would you like to remove from the cart?" << endl;
        CartNode* cur = cart.getHead();
        int i = 1;
        while (cur) {
            cout << "\n" << i++ << ". " << cur->data.name
                 << " - " << cur->data.quantity << " pcs"
                 << " - $" << cur->data.price * cur->data.quantity;
            cur = cur->next;
        }
        cout << endl;
        cin >> decision;

        if (decision >= 1 && decision <= cart.getSize()) {
            Item* item = cart.at(decision - 1);
            if (item) {
                history.push({"REMOVE", *item});
                cout << item->name << " has been removed from your cart" << endl;
                cart.removeAt(decision - 1);
            }
        } else {
            cout << "invalid option" << endl;
        }
    } else {
        cout << "cart is empty" << endl;
    }
}

// Pops the most recent action from the Stack and reverses it
void undoLastAction(LinkedListCart& cart, UndoStack& history) {
    UndoAction action;
    if (!history.pop(action)) {
        cout << "Nothing to undo" << endl;
        return;
    }

    if (action.type == "ADD_NEW") {
        // Find and remove the item that was added
        CartNode* cur = cart.getHead();
        int idx = 0, lastFound = -1;
        while (cur) {
            if (cur->data.name == action.item.name) lastFound = idx;
            idx++;
            cur = cur->next;
        }
        if (lastFound != -1) {
            cart.removeAt(lastFound);
            cout << "Undo: removed \"" << action.item.name << "\" from cart" << endl;
        }
    } else if (action.type == "ADD_QTY") {
        // Decrement quantity of the item whose quantity was incremented
        CartNode* cur = cart.getHead();
        int idx = 0;
        while (cur) {
            if (cur->data.name == action.item.name) {
                if (cur->data.quantity > 1) {
                    cur->data.quantity--;
                } else {
                    cart.removeAt(idx);
                }
                cout << "Undo: decremented quantity of \"" << action.item.name << "\"" << endl;
                break;
            }
            idx++;
            cur = cur->next;
        }
    } else if (action.type == "REMOVE") {
        // Restore the removed item
        cart.append(action.item);
        cout << "Undo: restored \"" << action.item.name << "\" to cart" << endl;
    }
}

// Copy cart to a vector, apply Bubble Sort, display result
void sortCartByPrice(const LinkedListCart& cart) {
    if (cart.isEmpty()) {
        cout << "cart is empty" << endl;
        return;
    }
    vector<Item> items;
    CartNode* cur = cart.getHead();
    while (cur) {
        items.push_back(cur->data);
        cur = cur->next;
    }

    bubbleSort(items);

    cout << "=== Cart sorted by price — Bubble Sort O(n^2) ===" << endl;
    for (int i = 0; i < (int)items.size(); i++) {
        cout << i + 1 << ". " << items[i].name
             << " - " << items[i].quantity << " pcs"
             << " - $" << items[i].price * items[i].quantity << endl;
    }
    cout << "==================================================" << endl;
}

// Demo: sort the catalog with Merge Sort, then compare
// Linear Search (on original order) vs Binary Search (on sorted order)
void searchCatalog(const vector<Item>& catalog) {
    if (catalog.empty()) {
        cout << "catalog is empty" << endl;
        return;
    }

    // Build a sorted copy using Merge Sort
    vector<Item> sorted = catalog;
    mergeSort(sorted, 0, (int)sorted.size() - 1);

    cout << "=== Search Catalog ===" << endl;
    cout << "Original catalog order:" << endl;
    for (int i = 0; i < (int)catalog.size(); i++) {
        cout << "  " << i + 1 << ". " << catalog[i].name << endl;
    }
    cout << "\nSorted catalog (Merge Sort, alphabetical — required for Binary Search):" << endl;
    for (int i = 0; i < (int)sorted.size(); i++) {
        cout << "  " << i + 1 << ". " << sorted[i].name << endl;
    }

    cout << "\nEnter catalog item number to search for (1-" << catalog.size() << "): ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > (int)catalog.size()) {
        cout << "invalid option" << endl;
        return;
    }
    string target = catalog[choice - 1].name;
    cout << "\nSearching for: \"" << target << "\"\n" << endl;

    // --- Linear Search on unsorted catalog ---
    cout << "[Linear Search — O(n) — no sorting required]" << endl;
    cout << "Scanning: ";
    int linSteps = 0, linResult = -1;
    for (int i = 0; i < (int)catalog.size(); i++) {
        linSteps++;
        cout << "\"" << catalog[i].name << "\" ";
        if (catalog[i].name == target) {
            linResult = i;
            break;
        }
    }
    cout << "\n  -> Found at original index " << linResult
         << " after " << linSteps << " step(s)" << endl;

    // --- Binary Search on sorted catalog ---
    cout << "\n[Binary Search — O(log n) — sorted input required]" << endl;
    int low = 0, high = (int)sorted.size() - 1, binSteps = 0, binResult = -1;
    while (low <= high) {
        binSteps++;
        int mid = low + (high - low) / 2;
        cout << "  Step " << binSteps << ": check mid = \""
             << sorted[mid].name << "\"" << endl;
        if (sorted[mid].name == target) {
            binResult = mid;
            break;
        } else if (sorted[mid].name < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << "  -> Found at sorted index " << binResult
         << " after " << binSteps << " step(s)\n" << endl;

    cout << "Comparison: Linear Search = " << linSteps
         << " step(s),  Binary Search = " << binSteps << " step(s)" << endl;
    cout << "With " << catalog.size()
         << " items the difference is small, but grows as n increases!" << endl;
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    bool closeCart = false;
    int decision;

    LinkedListCart cart;
    UndoStack history;

    vector<Item> catalog = {
        {"HP Legion",               1000, 1},
        {"Rolex",                   2000, 1},
        {"iPhone 17 Air",           3000, 1},
        {"Men Chain Set",            150, 1},
        {"Birkin Bag",             10000, 1},
        {"Durag",                     50, 1},
        {"Oraimo 20000mAh Powerbank", 70, 1},
        {"LED Light Strip",           15, 1}
    };

    cout << "=============================================" << endl;
    cout << "       DSA-Enhanced Shopping Cart           " << endl;
    cout << "  Cart Storage   : Singly Linked List       " << endl;
    cout << "  Undo History   : Stack (LIFO)             " << endl;
    cout << "  Sort Cart      : Bubble Sort  O(n^2)      " << endl;
    cout << "  Sort Catalog   : Merge Sort   O(n log n)  " << endl;
    cout << "  Catalog Search : Linear O(n) / Binary O(log n)" << endl;
    cout << "=============================================" << endl;

    while (!closeCart) {
        displayCart(cart);
        cout << "\nWhat would you like to carry out in your cart?" << endl;
        cout << "1. Checkout" << endl;
        cout << "2. Clear cart" << endl;
        cout << "3. Add item to cart" << endl;
        cout << "4. Remove an item from cart" << endl;
        cout << "5. Undo last action  [Stack]" << endl;
        cout << "6. Sort cart by price  [Bubble Sort]" << endl;
        cout << "7. Search catalog  [Linear vs Binary Search]" << endl;
        cout << "8. Exit cart" << endl;
        cin >> decision;

        if (decision < 1 || decision > 8) {
            cout << "invalid option" << endl;
        } else {
            switch (decision) {
                case 1: checkout(cart);                         break;
                case 2: clearCart(cart);                        break;
                case 3: addItem(cart, catalog, history);        break;
                case 4: removeItem(cart, history);              break;
                case 5: undoLastAction(cart, history);          break;
                case 6: sortCartByPrice(cart);                  break;
                case 7: searchCatalog(catalog);                 break;
                case 8: cout << "cart exited" << endl;
                        closeCart = true;                       break;
                default: break;
            }
        }
    }

    return 0;
}
