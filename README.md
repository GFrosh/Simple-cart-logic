# 🛒 Simple Cart Logic — DSA Edition

A command-line shopping cart application built in C++, extended to teach core **Data Structures and Algorithms** concepts. The original cart logic is preserved in `cart.cpp`; a DSA-enhanced version lives in `dsa_cart.cpp`.

---

## 📋 Features

- View cart contents with item quantities and prices
- Add items from a catalog (duplicates increase quantity automatically)
- Remove individual items from the cart
- Clear the entire cart
- Checkout with total price calculation
- **NEW:** Undo last action *(Stack-powered)*
- **NEW:** Sort cart by price *(Bubble Sort)*
- **NEW:** Search catalog — side-by-side Linear vs. Binary Search demo

---

## 🗂️ Project Structure

```
simple-cart-logic/
├── cart.cpp        # Original cart — std::vector, structs, loops
└── dsa_cart.cpp    # DSA edition — Linked List, Stack, sorting & searching
```

### Files

| File | Description |
|---|---|
| `cart.cpp` | Original implementation using `std::vector`, structs, and loops |
| `dsa_cart.cpp` | DSA-enhanced version demonstrating Linked List, Stack, Bubble Sort, Merge Sort, Linear Search, and Binary Search |

### Code Structure inside `cart.cpp`

| Section | Description |
|---|---|
| `struct Item` | Holds item name, price, and quantity |
| `main()` | Catalog data, cart loop, and menu switch |
| `displayCart()` | Prints current cart contents |
| `addItem()` | Adds item from catalog, increments quantity if already in cart |
| `removeItem()` | Removes a specific item by index |
| `clearCart()` | Clears all items from the cart |
| `checkout()` | Calculates total and processes payment |

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (g++ recommended)

### Compile & Run

```bash
# Original cart
g++ cart.cpp -o cart
./cart         # Linux/Mac
cart.exe       # Windows

# DSA-enhanced cart
g++ dsa_cart.cpp -o dsa_cart
./dsa_cart     # Linux/Mac
dsa_cart.exe   # Windows
```

---

## 🧠 Data Structures & Algorithms

`dsa_cart.cpp` deliberately applies each concept to the shopping cart so the ideas feel concrete, not abstract.

### Data Structures

#### 1. Singly Linked List — Cart Storage

Instead of `std::vector`, the cart is stored as a hand-rolled singly linked list.

```
HEAD -> [HP Legion] -> [Rolex] -> [Durag] -> nullptr
```

| Operation | Time Complexity |
|---|---|
| Append item to cart | O(n) — traverse to end |
| Remove item by index | O(n) — traverse to position |
| Display all items | O(n) — traverse all nodes |

**Why a linked list?** Each `CartNode` is an independently allocated piece of memory connected by a pointer. This makes the "chain of items" structure explicit and teaches pointer-based data structure management that `std::vector` hides.

#### 2. Stack — Undo History

Every `addItem` and `removeItem` call pushes an `UndoAction` onto a hand-rolled LIFO stack. Selecting "Undo" pops the most recent action and reverses it.

```
TOP  [REMOVE: Rolex]      <- most recent — popped first
     [ADD_QTY: HP Legion]
     [ADD_NEW: HP Legion] <- oldest — popped last
```

| Operation | Time Complexity |
|---|---|
| Push (record action) | O(1) |
| Pop (undo action) | O(1) |

---

### Algorithms

#### 3. Bubble Sort — Sort Cart by Price

Repeatedly compare adjacent elements and swap them if out of order until no swaps remain.

```
Before: [HP Legion $1000,  Durag $50,  Rolex $2000]
Pass 1: compare(1000,50)  -> swap  -> [Durag $50, HP Legion $1000, Rolex $2000]
        compare(1000,2000) -> ok   -> [Durag $50, HP Legion $1000, Rolex $2000]
Pass 2: no swaps — sorted!
```

- **Time:** O(n²) average and worst case
- **Space:** O(1) in-place

#### 4. Merge Sort — Sort Catalog Alphabetically

Divide-and-conquer approach that splits the list in half, recursively sorts each half, then merges.

```
[Rolex, HP Legion, Durag]
   ↓ split
[Rolex, HP Legion]   [Durag]
   ↓ sort each half
[HP Legion, Rolex]   [Durag]
   ↓ merge
[Durag, HP Legion, Rolex]
```

- **Time:** O(n log n) always
- **Space:** O(n) auxiliary

Used to sort the catalog alphabetically before Binary Search.

#### 5. Linear Search — O(n)

Scan every element from the start until the target is found. Works on **unsorted** data.

```
Searching "Durag" in [HP Legion, Rolex, iPhone 17 Air, Men Chain Set, Birkin Bag, Durag, ...]
Step 1: "HP Legion"? No
Step 2: "Rolex"? No
...
Step 6: "Durag"? Yes! Found after 6 steps.
```

#### 6. Binary Search — O(log n)

Check the middle element; discard the half where the target cannot be. Repeat. **Requires sorted input.**

```
Searching "Durag" in sorted [Birkin Bag, Durag, HP Legion, LED Light Strip, ...]
Step 1: mid = "LED Light Strip" → "Durag" < "LED" → search left half
Step 2: mid = "Durag" → match! Found after 2 steps.
```

The menu option **"Search catalog"** runs both algorithms live and prints a step-by-step comparison.

---

## 🛍️ Available Catalog Items

| Item | Price |
|---|---|
| HP Legion | $1000 |
| Rolex | $2000 |
| iPhone 17 Air | $3000 |
| Men Chain Set | $150 |
| Birkin Bag | $10000 |
| Durag | $50 |
| Oraimo 20000mAh Powerbank | $70 |
| LED Light Strip | $15 |

---

## 💡 Concepts Used

### Original (`cart.cpp`)
- Structs
- `std::vector`
- Functions with pass-by-reference (`&`)
- `const` references for read-only parameters
- Switch statements
- Loops and conditionals

### DSA Edition (`dsa_cart.cpp`)
- **Singly Linked List** — custom `CartNode` pointer chain
- **Stack** — custom `StackNode` LIFO structure
- **Bubble Sort** — O(n²) in-place comparison sort
- **Merge Sort** — O(n log n) divide-and-conquer sort
- **Linear Search** — O(n) sequential scan
- **Binary Search** — O(log n) halving search on sorted input
- Dynamic memory management (`new` / `delete`)
- Classes with encapsulation
- Pointer traversal

---

## 🔮 Planned Improvements

- [ ] Split into separate `.h` and `.cpp` files
- [ ] Refactor using full OOP (inheritance, polymorphism)
- [ ] Add file I/O to persist cart between sessions
- [ ] Add user accounts
- [ ] Remove item — reduce quantity before full removal
- [ ] Replace Linked List cart lookup with a Hash Map for O(1) access

---

## 🪞 Reflection

### From Vector to Linked List

When I first built this cart, I used `std::vector` — a dynamic array that manages its own memory. It was simple and effective. Replacing it with a hand-rolled **singly linked list** revealed what `vector` abstracts away: every node is a separately allocated block of memory connected by a raw pointer. Traversal now means following a chain of pointers rather than jumping to a numeric index.

The trade-off is real: vectors offer O(1) random access while linked lists are O(n). But the linked list makes the *structure* of "items chained together" visible in code, and forces you to think carefully about allocation and ownership — skills that matter in systems programming.

### The Stack and "Undo"

Adding undo history with a **stack** changed how I think about state. In the original cart, every action was permanent — removing an item was gone forever. Treating each action as a reversible event that gets pushed onto a stack changes the mental model. Push cost is O(1), pop cost is O(1), and the program can undo any sequence of actions in the order they happened. This is exactly how most real-world "undo" systems work under the hood.

### Sorting: Bubble Sort vs. Merge Sort

I implemented **bubble sort** first because it is the easiest algorithm to trace mentally — two adjacent items swap if out of order, repeat until clean. But O(n²) means 8 items could require up to 64 comparisons. **Merge sort** cuts that to O(n log n), roughly 24 comparisons for 8 items. With 1,000 catalog items, the gap would be roughly 1,000,000 operations vs. 10,000 — a 100× difference that matters enormously in production.

### Searching: Linear vs. Binary

The most revealing insight: **binary search is faster, but it requires sorted data.** In `cart.cpp` the catalog is never sorted, so only linear search is possible. In `dsa_cart.cpp`, I first sort the catalog alphabetically with merge sort, then unlock binary search. This dependency — sort once, search faster every time afterwards — reflects a genuine engineering trade-off: pay the sorting cost upfront and save on every subsequent lookup.

---

## 👨‍💻 Author

**Osmond** — SOE Student, Federal University of Technology Owerri (FUTO)
