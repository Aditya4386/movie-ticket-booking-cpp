# 🎬 Movie Ticket Booking System

A C++ CLI application managing theater reservations. It demonstrates practical memory management and core data structures.

## ✨ Core Features

* **Interactive Seating:** View a real-time matrix of available (`0`) and booked (`1`) seats.
* **Direct Booking:** Reserve specific seats using row and column coordinates.
* **Smart Auto-Allocation System:** * When the theater reaches **House Full** capacity, new users can join a waiting list.
  * If a user **cancels** their ticket, the system automatically dequeues the first person from the waiting list and instantly assigns them the newly opened seat.
* **Manage Reservations:** Look up ticket status by seat number, view all active bookings, or wipe the entire system clean.

## 🧠 Data Structures & Benefits

| Data Structure | Where It Is Used | The Technical Benefit |
| :--- | :--- | :--- |
| **2D Array** | The seating matrix | Provides $O(1)$ time complexity for checking if a specific coordinate is available or booked. |
| **Singly Linked List** | Active ticket storage | Dynamic memory allocation. It only consumes RAM for actual bookings, preventing wasted space. |



| Data Structure | Where It Is Used | The Technical Benefit |
| :--- | :--- | :--- |
| **Circular Queue** | The House Full waitlist | True First-In-First-Out (FIFO) logic. Reuses empty array indexes instantly without the CPU overhead of shifting elements. |


