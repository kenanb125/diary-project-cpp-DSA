#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Time {  
    int second, minute, hour; // seconds, minutes, hours

    public:
    Time(int s=0, int m=0, int h=0){ // Constructor (turns extra seconds into minutes, minutes into hours)
            m += s / 60;  
            s %= 60;       
            h += m / 60;
            m %= 60;
            second = s;
            minute = m;
            hour= h;
    }
   
    void printTime() const { // Prints time on screen
            cout << hour << ":" << minute << ":" << second << endl;
    }

    void setTime(int s, int m, int h){ // Setter method for time
            m += s / 60;
            s %= 60;
            h += m / 60;
            m %= 60;
            second = s;
            minute = m;
            hour = h;
    }

    friend class Unos; 
};

class Date { // CLASS FOR DATE
    int day, month, year; // day, month, year

    public:
    Date(int d=1, int m=1, int y=2000) : day(d), month(m), year(y) {} // Parameterized constructor for date
    
    void printDate() const { // Prints the Date on the screen
             cout << day << "." << month << "." << year << endl;
    }

    void setDate(int d, int m, int y){ // Setter method for date
            day = d;
            month = m;
            year = y;
    }

    friend class Unos; // Class Unos explicitly uses these data members
    friend class List; // Class List explicitly uses these data members
};

class Unos { // ENTRY CLASS (REMEMBERS EVERYTHING FOR THE ENTRY EXCEPT THE CONTENT)
    string opis; // Description of the entry
    Time time; // Time of the entry
    Date date; // Date of the entry
    int importancy; // Importance of the entry
    string filename; // Path to the .txt file where the entry is written
    
    public:
void printUnos() const { // Prints the entry data on the screen (DOES NOT PRINT THE ENTRY CONTENT ITSELF)
            cout << "Description: " << opis << ", " << "Time: "; 
            time.printTime();
            cout << ", " << "Date: "; 
            date.printDate();
            cout << ", " << "Priority: " << importancy << endl;
}

Unos(string opis = "", int sec = 0, int min = 0, int hour = 0, int day = 1, 
    int mon = 1 , int year = 2000, int imp = 0, string filename = "") :
    opis(opis), time(sec, min, hour), date(day, mon, year), importancy(imp) {} // Parameterized constructor

void getUnos() { // Getter method 
            cout << "Enter description: ";
            cin.ignore();        // Standard Cpp maneuver to take a string 
            getline(cin, opis);    
                
            int sec,min,hour;
            cout << "Enter time (hours minutes seconds): ";
            cin >> hour >> min >> sec;
            time.setTime(sec,min,hour);// Calls setter for Time

            int day,mon,year;
            cout << "Enter date (day month year): ";
            cin >> day >> mon >> year;
            date.setDate(day,mon,year);  // Calls setter for Date  

            cout << "Enter importance (1-10): ";
            cin >> importancy;
}

void writeinFile(ofstream &fileHandle) const { // Inserts into the file diary.txt
        fileHandle << opis << " " << time.hour << ":"
        << time.minute << ":" << time.second << " " <<
        date.day << "." << date.month << "." << date.year << " " 
        << importancy << endl;
}

    void setFilename(string &name) {filename = name;} // Setter for filename
    friend class Node;
    friend class PriorityQueue;
    friend class List;
};

class NodeStack{ // Class for a node that uses a stack, differs from others because it only remembers the folder name for the entry
    string data; // filePath to the entry
    NodeStack *next; // Holds a reference to the next node in the list
    public:
        NodeStack(const string &data) : data(data), next(nullptr) {} // Constructor
    friend class Stack;
};

class Stack{ // STACK class
    NodeStack *tos; // Pointer to the top of the stack (In this case, top is the beginning of the list to avoid iteration)
    public:
    Stack() : tos(nullptr) {} // Constructor
    ~Stack() { // Destructor for the stack deletes all elements in the stack when the stack ceases to exist (out of scope)
    NodeStack *temp;
    while(tos){
        temp = tos;
        tos = tos->next;
        delete temp;
    }
}

void push(string &newString) { // Standard push operation (adds an element to the beginning of the list)
        NodeStack *p = new NodeStack(newString); 
            p->next = tos;
            tos = p;
        
}

void pop(string &info) { // Standard pop operation that returns (as a side effect) the deleted element
        if(tos) {
        NodeStack *q = tos;
        info = q->data;
        tos=tos->next;
        delete q;
        }
    }

};

class NodeQueue{ // Class for a node that uses a priority queue (realized by a doubly linked list)
    Unos u;
    NodeQueue *right, *left;
    public:
    NodeQueue(const Unos &u) : u(u), right(nullptr), left(nullptr) {} // Constructor
    friend class PriorityQueue;
};

class PriorityQueue{ // PRIORITYQUEUE class
    NodeQueue *head, *tail;
    public:
    PriorityQueue() : head(nullptr), tail(nullptr) {} // Constructor
    ~PriorityQueue(){ // Destructor 
        NodeQueue *temp;
        while(head){
            temp = head;
            head = head->right;
            temp->right = temp->left = nullptr;
            delete temp;
        }
}

void addToQueue(Unos &u) { // Adding to the priority queue
    NodeQueue *p = new NodeQueue(u); // A new node is created
    if(!head) { // if the list is empty, head and tail are set to the new element
        head = tail = p;
        return;
    }
    if (p->u.importancy < head->u.importancy) { // if the priority of the new one is less than the head's, it is set as the head
        p->right = head;
        head->left = p;
        head = p;
        return;
    }
    NodeQueue *temp = head; // we keep a pointer to the head because we don't want to lose access to the beginning of the list by iterating the head (memory leak/data loss)
    while(temp->right && temp->right->u.importancy <= p->u.importancy) // As long as we can move further with temp and while the priority of the next is less than/equal to the priority of the new one
        temp = temp->right; // iteration
    // We have reached the desired position for insertion
    p->right = temp->right;
    if(temp->right) temp->right->left = p; // If it is not the end of the list, we link the next element with p
    else tail = p; // if it is the end of the list and we cannot do that, we set the tail to the element
    temp->right = p;
    p->left = temp;
}


void showFiveMostImportant() const { // Shows the 5 elements closest to the end
    NodeQueue *temp = tail; // We don't change temp because we don't want to lose access to the last element
    for(int i = 0; i < 5 && temp; i++) {
        cout << temp->u.filename << " (Importance: " << temp->u.importancy << ")" << endl;
        temp = temp->left;
    }
} 

void removeByFilename(const string &filename) { // Deletes the element with this key
    NodeQueue *temp = head;
    while(temp) {
        if(temp->u.filename == filename) { // If we found the desired element 
            if(temp->left) temp->left->right = temp->right; // We check if the element with the key is the head
            else head = temp->right;

            if(temp->right) temp->right->left = temp->left; // We check if the element with the key is the tail
            else tail = temp->left;  

            delete temp;
            return;
        }
        temp = temp->right; // Iterative step of the loop
    }
}

};

class NodeList{ // Class for a node used by a list
    Unos u;
    NodeList *next;
    public:
    NodeList(const Unos &u) : u(u), next(nullptr) {} // Constructor
    friend class List;
};

class List{ // LIST class
    NodeList *head;
    public:
    List() : head(nullptr) {} // Constructor
    ~List(){ // Destructor
        NodeList *temp;
        while(head){
            temp = head;
            head = head->next;
            temp->next = nullptr;
            delete temp;
        }
    }



    void add (Unos &u) { // adding elements to the beginning of a singly linked list
        NodeList *p = new NodeList(u);
        p->next = head;
        head = p;
    }
    void showYourself() const { // iterates through the entire list and displays the description and date of objects
        NodeList *temp = head;
        while(temp) {
            cout << "Date: "; 
            temp->u.date.printDate();
            cout << "Entry description: " << temp->u.opis << endl;
            temp = temp->next; // Iterative step of the loop
        }
}

void findAndPrintByDate(const Date &datum) { // finding an object with the date and printing the content
    NodeList *temp = head; // pointer to head
    bool found = false; 
    while(temp) { // we iterate as long as temp points to something
        if(temp->u.date.day == datum.day && // if each element of the entered date matches the date of the current object
           temp->u.date.month == datum.month &&
           temp->u.date.year == datum.year) 
        {
            ifstream file(temp->u.filename);// we open the file for reading (filename is a data member of that object) 
                cout << "Entry content: ";
                string line; // string that stores a line from the entry file
                while(getline(file, line)) // puts line by line into the line variable until we reach EOF
                    cout << line << endl; // prints the line
                file.close(); // closes the open file
                found = true; // indicates that the object has been found
        }
            temp=temp->next; // Iterative step of the loop
        }
         if(!found) cout << "No entries for this date." << endl; // Notify that the element was not found
    }
void remove() { // Removes the first element from the singly linked list
        NodeList *q = head;
        head=head->next;
        delete q;
}

void printFilteredByDate(Date &start, Date &end) const {
    List tempList; // We create a temporary list that will store sorted elements

    NodeList *temp = head;
    while(temp){ // Check if the date is not in range
    if(temp->u.date.year < start.year ||
    (temp->u.date.year == start.year && temp->u.date.month < start.month) ||
    (temp->u.date.year == start.year && temp->u.date.month == start.month && temp->u.date.day < start.day) ||
    temp->u.date.year > end.year ||
    (temp->u.date.year == end.year && temp->u.date.month > end.month) ||
    (temp->u.date.year == end.year && temp->u.date.month == end.month && temp->u.date.day > end.day)) { 
        temp = temp->next; continue; // iterate and start over if it is not
    }


        // Inserting the element sorted by date into the temporary list
        NodeList *p = new NodeList(temp->u);
        if(!tempList.head || // If the list is empty or if the date of the new node is less than the head, set the head to the new node
            (temp->u.date.year < tempList.head->u.date.year) || 
            (temp->u.date.year == tempList.head->u.date.year && temp->u.date.month < tempList.head->u.date.month) ||
            (temp->u.date.year == tempList.head->u.date.year && temp->u.date.month == tempList.head->u.date.month && temp->u.date.day <= tempList.head->u.date.day)) {
                p->next = tempList.head; 
                tempList.head = p;
        } else {
        NodeList *tempNew = tempList.head; // tempNew is set for iteration through the newly created sorted list
        // While there is a next node and while the date of the next node is less than the new date
            while(tempNew->next && 
                (tempNew->next->u.date.year < temp->u.date.year ||
                (tempNew->next->u.date.year == temp->u.date.year && tempNew->next->u.date.month < temp->u.date.month) ||
                (tempNew->next->u.date.year == temp->u.date.year && tempNew->next->u.date.month == temp->u.date.month && tempNew->next->u.date.day <= temp->u.date.day))) 
                 {
                    tempNew = tempNew->next; // Iterative step of the loop
                 }

        // Inserting the new node in the appropriate place
        p->next = tempNew->next;
        tempNew->next = p;

        }
        temp = temp->next; // Iterative step of the main loop
    }

    // Printing the filtered and sorted list with description, date, and entry content
    temp = tempList.head; 
    while(temp){
        cout << "Date: "; temp->u.date.printDate();
        cout << "Entry description: " << temp->u.opis << endl;

        ifstream file(temp->u.filename);
        cout << "Entry content: ";
        string line;
        while(getline(file, line)) // Takes line by line into line and prints to the standard screen
            cout << line << endl;
        file.close();

        cout << "--------------------" << endl;
        temp = temp->next; // Iterative step of the loop
    }
}
};