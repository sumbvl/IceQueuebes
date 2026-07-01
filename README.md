# IceQueuebes 🍦

A console-based ice cream parlor management system built in C++ for our Data Structures & Algorithms coursework. The project simulates real-world parlor operations — order handling, inventory, and customer records — using core data structures implemented entirely from scratch (no STL containers used).

## Overview

IceQueuebes was built as a DSA project to demonstrate practical application of fundamental data structures in a single cohesive system. Instead of using isolated textbook examples, each structure powers a real feature of the parlor: orders move through a queue, actions can be undone via a stack, customer/product records live in a custom linked list, and lookups are optimized with a hash map.

Every menu in the system includes a **quit/exit option**, so the user is never stuck without a way out.

## Data Structures Used

- **Queue** — processes customer orders in the order they arrive (FIFO)
- **Stack** — handles undo/history of recent actions (LIFO)
- **Linked List** — custom class for managing dynamic records (no `std::list` used)
- **Hash Map** — fast lookup for inventory items and customer data

## Features

- 🧾 Order queue system — customers are served in arrival order
- ↩️ Undo functionality via stack-based action history
- 🔗 Fully custom linked list implementation (own `Node` class, no built-ins)
- ⚡ Hash map for O(1) average lookup on inventory/customer records
- 📋 Menu-driven console interface with a quit option at every level
- 🧩 Modular code structure — each data structure isolated in its own file/class

## Project Structure

```
IceQueuebes/
├── main.cpp
├── Queue.h / Queue.cpp
├── Stack.h / Stack.cpp
├── LinkedList.h / LinkedList.cpp
├── HashMap.h / HashMap.cpp
└── README.md
```
*(Update this to match your actual file layout)*

## Getting Started

### Prerequisites
- A C++ compiler (e.g., g++, MinGW, or any standard C++ IDE)

### Build & Run

```bash
git clone https://github.com/sumbvl/IceQueuebes.git
cd IceQueuebes
g++ main.cpp -o icequeuebes
./icequeuebes
```
