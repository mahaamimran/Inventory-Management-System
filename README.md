# Inventory Management System

A console-based cash-and-carry store management system written in C++.

## Features

### Inventory Management
- Display all 50 pre-loaded grocery products (name, quantity, price)
- Auto-reorder: flags any product below 100 units and adds 50 to its stock
- Update an individual product's quantity and price by name
- Price management: set a new price for a specific product, or apply a promotional discount (custom %, Ramadan 50%, Eid 25%, fixed-amount, or flat Rs. 20 off)

### Point of Sale
- Add multiple items to a shopping cart; each transaction is timestamped with the system clock
- Inventory is decremented automatically on purchase
- Apply checkout discounts: 10% off any cart item with quantity >= 3; 5% off the entire order when the total exceeds Rs. 1000
- Issue partial or full refunds — stock is restored automatically

### Reporting
- Sales report: view sold items grouped by product, by date/time, or by customer
- Inventory report: tabular view of remaining stock for all products
- Profit report: 5% margin calculation per product with a running total

## Tech

- Language: C++ (standard C++11 or later)
- Interface: interactive console menu
- Dependencies: none (stdlib only — `<iostream>`, `<ctime>`)

## Build & Run

```bash
g++ -std=c++11 Q1.cpp -o Q1
./Q1
```

Follow the on-screen menus. An annotated example walkthrough is included at the bottom of `Q1.cpp`.

---

> Early university C++ assignment (OOP, dynamic memory, inheritance).
