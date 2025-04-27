# Shortest-Path-and-Course-Scheduling-System-Dijkstra-Topological-Sort-
# Project Overview

This project involves three major C programs, each designed to manage and manipulate different types of data structures and algorithms.

## 1. Text Editor with Undo/Redo Functionality

**Main Idea:**
- Develop a text editor where users can insert and delete text.
- Supports Undo/Redo operations using two stacks.
- Load initial text from a file and save the modified text back to a file.

**Data Structures:**
- **Queue**: Manage insertion words.
- **Stack**: Manage undo and redo operations.

**Features:**
- Insert string into the text at specific locations.
- Remove specific strings from the text.
- Undo the last action.
- Redo the previously undone action.
- Save the modified text to a file.

## 2. AVL Tree and Hash Table Word Analysis

**Main Idea:**
- Load words from a file into an AVL Tree.
- Analyze word frequencies.
- Transfer data into a Hash Table with Rehashing support.

**Data Structures:**
- **AVL Tree**: Maintain balanced binary search tree for words.
- **Hash Table**: Store and manage words with collision handling and rehashing.

**Features:**
- Insert and delete words from AVL Tree.
- Search and retrieve word frequency.
- Rehash the Hash Table if the load factor exceeds 2/3.
- Identify and display:
  - Unique words.
  - Most frequent words.
  - Words exceeding a specific frequency threshold.

## 3. Graph Algorithms (Shortest Path & Topological Sort)

**Main Idea:**
- Manage buildings and courses as graphs.
- Perform Dijkstra's algorithm for shortest paths.
- Perform Topological Sort for course planning.

**Data Structures:**
- **Adjacency Matrix**: Represent buildings and courses.
- **Heap**: Optimize Dijkstra's shortest path calculations.
- **Stack**: Manage Topological Sort.

**Features:**
- Load building distances and course prerequisites from files.
- Calculate and display shortest paths between buildings.
- Print the total cost/distance between two buildings.
- Perform Topological Sort on courses based on prerequisites.

# Author
- **Name:** Ahmad Shaher Sous
- **ID:** 1221371
- **Supervisor:** Doctor Radi Jarrar

---
