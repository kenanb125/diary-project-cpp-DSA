#include "functions.cpp"

int main() {
    Stack stack; // Initialize STACK
    PriorityQueue queue; // Initialize PRIORITY QUEUE
    List list; // Initialize LIST
    int choice; // Stores the User's choice
    for(;;){ // Infinite loop
        promptUserMenu(choice); // Get the user's choice from standard input
    switch(choice){
        case 1: // User chose option 1:
            {
                 ofstream diary("diary.txt", ios::app); if(!diary) return cout << "Error", 1; // Open diary.txt in append mode
                 Unos u; // Class instance (unos object)
                 u.getUnos(); // Takes all entry information from the user EXCEPT THE ENTRY CONTENT
                 u.writeinFile(diary);  // Inserts all of that into diary.txt
                 diary.close(); // Closes the diary
                 string text; // Initializes a string (character array) for the ENTRY CONTENT
                 promptUserUnos(text); // Takes the ENTRY CONTENT from the user
                 writeInUnosIndex(text, stack, u); // Inserts text (ENTRY CONTENT) into the required folder/newfilename.txt (Which is kept on the stack)
                 queue.addToQueue(u); // Adds the Unos object to the priority queue
                 list.add(u);// Adds the Unos object to the list
            }
            break;
        case 2: // User chose option 2:
            {
                string UnosForDeletion; // Remembers the folder name for deletion
                stack.pop(UnosForDeletion); // Pops the last element from the stack
                cout << "---------------------------------------------" << endl;
                cout << "Deleted " << UnosForDeletion << "." << endl;
                cout << "---------------------------------------------" << endl;
                remove(UnosForDeletion.c_str()); // Removes the last added file in the entries folder
                removeLastLineFromDiary(); // Removes the last line from diary.txt
                queue.removeByFilename(UnosForDeletion);// Removes from queue
                list.remove();// Removes from list
            }
            break;
        case 3: // User chose option 3:
            {
                cout << "---------------------------------------------" << endl;
                cout << "The five most important entries are: " << endl;
                queue.showFiveMostImportant(); // Displays the first 5 elements in the queue
                cout << "---------------------------------------------" << endl;
            }
            break;
        case 4: // User chose option 4:
            {
                list.showYourself(); // Shows the date and description of each object in the list
                Date datum; // Object that stores the date the user wants to visit
                cout << "---------------------------------------------" << endl;
                cout << "Enter the diary date you want to view 'day month year': ";
                int dan, mjesec, godina;
                cin >> dan  >> mjesec  >> godina;
                datum.setDate(dan,mjesec,godina); // calls the setter for the data provided by the user
                list.findAndPrintByDate(datum); // Searches for that object and prints the ENTRY CONTENT
            }
            break;
        case 5:
        {
            int d1,m1,y1,d2,m2,y2;
            cout << "Enter the start date (day month year): ";
            cin >> d1 >> m1 >> y1;
            cout << "Enter the end date (day month year): ";
            cin >> d2 >> m2 >> y2;

            Date start(d1,m1,y1), end(d2,m2,y2);

            // Method call that will print filtered and sorted
            list.printFilteredByDate(start, end);
        }
            break;

        case 6: 
            return 0;
        default: "Unknown option\n";
    }
  }
}