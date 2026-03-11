# 🛒 Simple Cart Logic

A command-line shopping cart application built in C++. This project simulates a basic e-commerce cart where users can browse a catalog, manage their cart, and checkout.

---

## 📋 Features

- View cart contents with item quantities and prices
- Add items from a catalog (duplicates increase quantity automatically)
- Remove individual items from the cart
- Clear the entire cart
- Checkout with total price calculation

---

## 🗂️ Project Structure

```
simple-cart-logic/
└── cart.cpp       # All source code in a single file
```

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
g++ cart.cpp -o cart
./cart         # Linux/Mac
cart.exe       # Windows
```

---

## 🛍️ Available Catalog Items

| Item | Price |
|---|---|
| HP Legion | $1000 |
| Rolex | $2000 |
| iPhone 17 Air | $5000 |
| Men Chain Set | $150 |
| Birkin Bag | $10000 |
| Durag | $50 |
| Oraimo 20000mAh Powerbank | $70 |
| LED Light Strip | $15 |

---

## 💡 Concepts Used

- Structs
- Vectors
- Functions with pass-by-reference (`&`)
- `const` references for read-only parameters
- Switch statements
- Loops and conditionals

---

## 🔮 Planned Improvements

- [ ] Split into separate `.h` and `.cpp` files
- [ ] Refactor using classes and OOP
- [ ] Add file I/O to persist cart between sessions
- [ ] Add user accounts
- [ ] Case 4 remove item — reduce quantity before full removal

---

## 👨‍💻 Author

**Osmond** — SOE Student, Federal University of Technology Owerri (FUTO)
