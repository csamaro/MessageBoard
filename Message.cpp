#include "Message.h"
#include <iostream>
using namespace std;

/*//////PRIVATE VARIABLES/////
	string author;
	string subject;
	string body;
*/

	// default constructor
Message::Message() {
	author = "";
	subject = "";
	body = "";
}

	// Parameterized constructor; 
Message::Message(const string& athr, const string& sbjct, const string& bdy) {
	author = athr;
	subject = sbjct;
	body = bdy;
}

	/* Displays the Message using the following format:
	 *
	 * subject
	 * from author: body
	 */
void Message::display() const {
    cout << subject << endl;
    cout << "from " << author <<": " << body << endl;

}