#include "BBoard.h"
#include <fstream>
#include <iostream>
using namespace std;

/*//////PRIVATE VARIABLES/////
	string title;
	vector<User> userList;
	User currentUser;
	vector<Message> messageList;
*/////////////////////////////

	/* Constructs a board with a default title,
	* empty user & message lists,
	* and the "default" User
	*/
BBoard::BBoard() {
    title = "Crim's BB";
   // currentUser;
 //   messageList;
  //  userList;
}

	 /* Same as the default constructor except
	  * it sets the title of the board
	  */
BBoard::BBoard(const string& tit) {
    title = tit;
  //  currentUser;
  //  messageList;
  //  userList;

}

	 /* Imports all the authorized users from an input file,
	  * storing them as User objects in the vector userList
	  * The name of the input file is passed in as a parameter to this function.
	  * Returns true if the file opened, false if it did not.
	  * See specifications for file format.
	  */

bool BBoard::loadUsers(const string& namefile) {
    ifstream infil(namefile);
   // infil.open("namefile"); //open file
    if (!infil.is_open()) { //check if opened
        cerr << "Error opening file " << namefile << endl;
        return false;
    }
    string whole;
    string un;
    string pw;
    while(!infil.eof()){
        infil >> whole;
        un = whole;
        infil >> whole;
        pw = whole;
        if(un != "end"){
            User tempuse(un, pw);
            currentUser = tempuse;
            userList.push_back(currentUser);
        }
    }
   /* while (!infil.eof()) { //check if eof
        getline(infil, whole);
        int pos = whole.find(" ");   //finds where ' ' is
        int pos2 = whole.rfind(" ");
        int length = whole.length();
       // cout << "found ' '";
        un = whole.substr(0, pos); // sets username
       // cout << un << endl;
        if(un != "end"){
            pw = whole.substr(pos2 +1, -1);     //sets password
            User tempuse(un, pw);
            currentUser = tempuse;
            userList.push_back(currentUser); //sets username & password to vector
        }
    } 
    for(unsigned int i = 0; i < userList.size(); ++i){
    cout << "///" << userList.at(i).getUsername() << "///";
    cout << userList.at(i).getPassword() << "/--" << endl;
    } */
    infil.close(); //closes file
    return true;
}

	 /* Asks for and validates a user/password.
	  * Always asks for both user and password combo unless 'q' or 'Q' entered.
	  * Checks userList to validate user and password.
	  * If valid, sets currentUser to this User, outputs welcome message,
	  * then returns true.
	  * Otherwise outputs error message and then repeats request
	  * for username/password.
	  * Continues until valid user/password
	  * or until 'q' or 'Q' is entered for username.
	  * If 'q' or 'Q' is entered, does not ask for password, outputs "Bye!"
	  * and then returns false.
	  */
bool BBoard::login() {
    string un;
    string pw;
    cout << "Welcome to " << title;
    do{cout << endl<< "Enter your username ('Q' or 'q' to quit): ";
        cin >> un;
        if(ifq(un)){
            return false;
        }
        cout << endl << "Enter your password: ";
        cin >> pw;
        if(ifq(pw)){
            return false;
        }
        if(userExists(un, pw)){
            User temp2use(un, pw);
            currentUser = temp2use;
            cout << endl << "Welcome back " << un << "!" << endl;
            return true;
        }
       cout << endl << "Invalid Username or Password!" << endl;
    }while(true);
}

	 /* Contains main loop of Bulletin Board.
	  * First verifies a User has been logged in before calling this function.
	  * (Do not call login function within this function.)
	  * Returns from **function** immediately if no User logged in (Default User).
	  * Continues to display menu options to user and performs requested action
	  * until user chooses to quit.
	  * See output samples for exact format of menu.
	  */
void BBoard::run() {
    string request;
    do{ cout << endl 
            << "Menu" << endl;
        cout << "- Display Messages ('D' or 'd')" << endl
            << "- Add New Message ('N' or 'n')" << endl
            << "- Quit ('Q' or 'q')" << endl
            << "Choose an action: ";
        cin >> request;
        if((request == "D") || (request == "d")){
            display();
        }
        else if((request == "N") || (request == "n")){
            addMessage();
        }
        else if(ifq(request)){
            return;
        }
      }while(true);
}

// private:


// These are only suggestions, not required helper functions.
// Feel free to make your own private helper functions as you see fit.
void BBoard::display() const{
    cout << endl;
    if(messageList.size() > 0){
        for(unsigned int i=0; i < messageList.size(); ++i){
            cout << "---------------------------------------------------------" << endl;
            cout << "Message #" << (i+1) <<": ";
            messageList.at(i).display();
        }
        cout << "---------------------------------------------------------" << endl;
        return;
    }
    cout << "Nothing to Display." << endl;
    return;
}

void BBoard::addMessage(){
    string sub;
    string bod;
    cout << endl << "Enter Subject: ";
    cin.ignore();
    getline(cin, sub);
    cout << endl << "Enter Body: ";
    getline(cin, bod);
    cout << endl << "Message Recorded!" << endl;
    Message mess1(currentUser.getUsername(), sub, bod);
    messageList.push_back(mess1);
}

bool BBoard::userExists(const string& un, const string& pw) const{
    for(unsigned i = 0; i < userList.size(); ++i){
        if(userList.at(i).getUsername() == un){ //checks to see if us are on list
            if(userList.at(i).getPassword() == pw){ //check to see if pw
                return true;
            }
        }
    }
    return false;
}

bool BBoard::ifq(const string& mayq){
    if ((mayq == "Q") || (mayq == "q")){
        cout << endl << "Bye!" << endl;
        return true;
    }
    return false;
}
