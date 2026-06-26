Diary Management System
A C++ console-based application designed to manage personal diary entries efficiently. The program allows users to create, view, filter, and delete entries while utilizing custom-implemented data structures.
Features:
-Diary Entries: Create new entries with descriptions, timestamps, dates, and priority levels.
-Priority Management: View the top 5 most important entries based on priority levels using a Priority Queue.
-Filtering: List entries filtered by a specific date range, automatically sorted by date.
-History & Navigation: Search for specific entries by date to display their full content.
-Dynamic Cleanup: Easily delete the last added entry, which automatically updates the diary history.
Data Structures Used:
This project implements fundamental data structures from scratch to ensure optimal performance and memory management:
-Stack (LIFO): Used for the "undo" functionality (deleting the last entry). It stores file paths of entries to ensure quick access and removal.  
-Priority Queue: Implemented using a doubly linked list. It keeps entries sorted by importance upon insertion, allowing for efficient priority-based retrieval. 
-Singly Linked List: Manages the chronological collection of diary entries. 
-A temporary list is used for date-range filtering to provide sorted results without altering the original order.  
Project Structure
-Classes.h: Contains the core class definitions (Time, Date, Entries, Stack, PriorityQueue, List) and their respective node structures.
-functions.cpp: Implements the UI logic and file handling utilities.
-main.cpp: The entry point of the application, handling the main menu loop and user interactions.
Getting Started:
Ensure you have a C++ compiler (like G++).Create a folder named entries in the same directory as the executable to store entry files.Compile and run the program.
License: This project was developed as a university assignment (Data Structures and Algorithms)
