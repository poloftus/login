#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>


using namespace std;


/*The login And Registration System project in C++ involves mainly the user 
registration process. User Credentials like usernames and passwords are asked 
from the user. If the registration of the user is successful then with the given 
credentials a file will be created of a particular user in the database.*/



string username;
string newUsername;
string password;
string newPassword;

void clearConsole(); // Declare the Clear Console function
void wipeFile(); // Declares the Wipe File function
void login(); // Declares the Start member function
void set_newUsername(); // Declares the Register function
void set_newPassword(); // Declares the set_newPassword function
bool check_newUsername(string newUsername); // Declares the check_newUsername function
bool check_newPassword(string newPassword, string newPassword_match); // Declares the create_newPassword function
void verifyUser(string username, string password); // Declares the Login function
void adminOptions(); // Declares the Admins Options function
void deleteUser(); // Declares the Delete User function



	void clearConsole() {

	system("cls");

}


	
	void wipeFile() {

		ofstream outFile("User Information.txt", ios::trunc); // Opens file in Truncation mode (clears the file)
		outFile.close();

	}



	void login() { // Defines the Start function

		cout << "\n\nPlease Enter Login Information.\n\nIf you'd like to register an account,\nplease enter 'register' as a username.";
		cout << "\n\nTo enter Administrative Options, enter 'admin' and 'password";
		cout << "\n\nTo exit the program enter '.' as a username\n\n";
		
		cout << "Username: ";
		username.clear();
		cin >> username;

		if (username == "register") {

			clearConsole();
			set_newUsername();
			set_newPassword();

		} else if (username == ".") { // Kills the program

			clearConsole();
			exit(0);
		
		} else {

			char ch;
			
			cout << "Password: ";
			password.clear();
			while (true) {

				ch = _getch(); // Read character from console withouth echoing

				if (ch == '\b') { // Checks for a backspace

					if (!password.empty()) {

						cout << "\b \b"; // Removes last asterisk screen
						password.pop_back(); // Removes last character from password string

					}

				}
				else if (ch == '\r') { // Checks for an enter

					cout << endl;
					break;

				}
				else {

					cout << "*"; // Prints an asterisk to the screen
					password += ch; // Adds the character to the password string

				}
			}

			verifyUser(username, password);

		}

	}



	void set_newUsername() {

		bool is_username_taken = true; // Declares the bool is_username_taken

		while (is_username_taken == true) { // checks if username is taken while is_username_taken is true

			cout << "\n\nPlease enter your desired username: ";
			cin >> newUsername; // Prompts user for new username
			
			is_username_taken = check_newUsername(newUsername); // Runs check on username until check_newUsername returns false;

		}

		clearConsole();
		
		
	}



	bool check_newUsername(string newUsername) {
		
		string line; // Declares the string line

		ifstream inFile("User Information.txt"); // Opens File in Read mode


		while (getline(inFile, line)) { // Searches file line by line

			if (line.find(newUsername) != string::npos) { // If username is not found in npos or no position (i.e. if the username is found)

				clearConsole();
				cout <<  newUsername << " is already taken... Try again";
				inFile.close(); // Closes the file
				return true; // keeps is_username_taken set to true

			}

		}
	
		inFile.close(); // If the username IS NOT found
		return false; // sets is_username_taken to false

	}
		


	void set_newPassword() {

		string newPassword;
		string newPassword_match;
		char ch;
		bool do_passwords_match = false;


		cout << "\n\nPlease Enter your desired username: " << newUsername << endl;
		cout << "Please enter your desired password: ";


		while (do_passwords_match == false) {

			newPassword.clear(); // Clears newPassword
			newPassword_match.clear(); // Clears newPassword_match

			while (true) {

				ch = _getch(); // Read character from console withouth echoing

				if (ch == '\b') { // Checks for a backspace

					if (!newPassword.empty()) {

						cout << "\b \b"; // Removes last asterisk screen
						newPassword.pop_back(); // Removes last character from password string

					}

				}
				else if (ch == '\r') { // Checks for an enter

					cout << endl;
					break;

				}
				else {

					cout << "*"; // Prints an asterisk to the screen
					newPassword += ch; // Adds the character to the password string

				}
			}


			cout << "Please reenter your desired password: ";

			while (true) {

				ch = _getch();

				if (ch == '\b') { // Checks for backspace

					if (!newPassword_match.empty()) {

						cout << "\b \b";
						newPassword_match.pop_back(); // Removes last character from string newPassword_match

					}

				}
				else if (ch == '\r') { // Checks for enter

					cout << endl;
					break;

				}
				else {

					cout << "*";
					newPassword_match += ch; // Adds the character pressed to the string newPassword_match


				}

			}

			do_passwords_match = check_newPassword(newPassword, newPassword_match);

		}

		ofstream outFile("User Information.txt", ios::app); // Opens the file 'User Information.txt' in append mode; creates a file if none exists


		outFile << newUsername << ":" << newPassword << endl; // Adds the new username and password to file - username:password
		outFile.close(); // Closes the file

	
		newUsername.clear(); // Clears the string newUsername
		newPassword.clear(); // Clears the string newPassword
		newPassword_match.clear(); // Clears the string newPassword_match
		
		
		clearConsole(); // Clears console
		login(); // Sends back to login screen

	}



	bool check_newPassword(string newPassword, string newPassword_match) {

		if (newPassword != newPassword_match) {

			clearConsole();
			cout << "\n\nPlease enter your desired username: " << newUsername << endl;
			cout << "Passwords do not match... Try again: ";
			return false;

		} else {

			return true;

		}
	}



	void verifyUser(string username, string password) {
		
		string line;
		string userinfo = username + ":" + password; // Formats info into username:password as is in file
		bool userinfo_found = false;

		
		if (username == "admin" && password == "password") {
			
			clearConsole();
			adminOptions();

		} else {


			ifstream inFile("User Information.txt"); // Opens file in read mode


			while (getline(inFile, line)) { // Reads file line by line

				if (line.find(userinfo) != string::npos && username != "admin") { // If username:password combo is found in the file

					userinfo_found = true;
					inFile.close();

				}

			}


			if (userinfo_found == true) {

				inFile.close();
				clearConsole();
				cout << "congrats";
				this_thread::sleep_for(chrono::seconds(2));
				clearConsole();
				login();

			}
			else if (userinfo_found == false) {

				inFile.close();
				clearConsole();
				cout << "\n\nUsername or Password Incorrect... Try again";
				this_thread::sleep_for(chrono::seconds(2));
				clearConsole();
				login();

			}

		}

	}



	void adminOptions() {

		string choice;

		cout << "\n\nOptions: Delete User ('del'), Return to Menu ('ret')\n\n";
		cout << "Choice: ";
		cin >> choice;

		if (choice == "del") {

			clearConsole();
			deleteUser();

		}
		else if (choice == "ret") {

			clearConsole();
			login();

		}
		else {

			clearConsole();
			cout << choice << "is not a valid option at this time";
			adminOptions();

		}

		/*cout << "You are the admin. Nice";
		this_thread::sleep_for(chrono::seconds(2));
		clearConsole();
		login();*/

	}



	void deleteUser() {

		string line; // Declares the string Line
		string file_content; // Declares the string File Content
		string user_to_delete; // Declares the string user_to_delete

		ifstream inFile("User Information.txt"); // Opens the file in read mode


		while (getline(inFile, line)) { // Reads the file line by line

			cout << line << endl; // Prints the file to the console
			file_content += line + "\n"; // Stores a copy of the file in the string file_content

		}


		inFile.close(); // Closes the file
		line.clear(); // Clears the string line


		cout << "\n\nPlease choose a user to delete: ";
		cin >> user_to_delete; // Prompts admin to select a user


		if (file_content.find(user_to_delete) != string::npos) { // If user_to_delete is found in file_content 
		
			size_t start_pos = file_content.find(user_to_delete); // assigns the start position of user_to_delete as start_pos
			size_t end_pos = file_content.find('\n', start_pos); // assigns the end position of user_to_delete as end_pos
			file_content.erase(start_pos, end_pos - start_pos + 1); // Removes the entire line from file content
			
			
			ofstream outFile("User Information.txt", ios::trunc); // Deletes the entire file upon opening

			outFile << file_content; // write the now modified file_content back to file
			outFile.close(); // Closes the file

			
			clearConsole();
			cout << "\n\nUser was found and deleted";

			this_thread::sleep_for(chrono::seconds(2));
			clearConsole();
			adminOptions();
		
		} else {
		
			clearConsole();
			cout << "\n\nUser was not found";

			this_thread::sleep_for(chrono::seconds(2));
			clearConsole();
			adminOptions();
		
		}
		
		
		/*ofstream outFile("User Information", ios::app); // Opens the file in append mode

		
		while (getline(inFile, line)) {

			if (line.find(user_to_delete) != string::npos) { // If user info typed is found
	


			}

	*/	}
		


int main() {

	clearConsole();
	login();

}