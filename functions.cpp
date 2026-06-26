#include "Classes.h"

void promptUserMenu(int &choice) { // Offer options to the user
    cout << "---------------------------------------------" << endl;
    cout << "Choose one of the desired options:\n";
    cout << "1. Diary entry\n";
    cout << "2. Delete last entry\n";
    cout << "3. Show the 5 most important entries\n";
    cout << "4. Diary overview (Date and description)\n";
    cout << "5. Filter by range and display sorted.\n";
    cout << "6. Exit program\n";
    cout << "---------------------------------------------" << endl;
    cin >> choice;
}

void promptUserUnos(string &s) { // Take option from the user
    cout << "Enter the entry: ";
    cin.ignore();               
    getline(cin, s);
}

void writeInUnosIndex(string &text, Stack &stack, Unos &u){
                 static int index = 1; // Static integer that remembers the last part of the name e.g. entry"1", entry"2"...
                 string unosIndexString = "entries/entry" + to_string(index++) + ".txt"; // Concatenation into the required folder/filename.txt
                 u.setFilename(unosIndexString); // Calls Setter member function for the data member filename ("entries/entry1.txt")
                 stack.push(unosIndexString); // Push filename to the stack (more on that in case 2)
                 ofstream unos(unosIndexString); // Opens a new file in the required directory/naming convention
                 unos << text << endl; // Inserts user text (ENTRY CONTENT) into the file entries\entry"Index"
                 unos.close(); // Closes the specified file
}



void removeLastLineFromDiary() {
    ifstream in("diary.txt"); // Creates a new file for reading
    ofstream out("temp.txt"); // Creates a new temporary file for appending

    string line, lineBefore; // line - currently read line, lineBefore - previously read line
    while (getline(in, line)) { // Reads line by line from diary.txt
        if (!lineBefore.empty()) out << lineBefore << endl;  // Writes only the previous line to out
        lineBefore = line;
    }
    in.close(); // Closes the original file
    out.close(); // Closes the temporary file
    remove("diary.txt"); // Removes the original file
    rename("temp.txt", "diary.txt"); // Renames the temporary file to the original

}