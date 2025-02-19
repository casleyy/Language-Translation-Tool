#include <iostream>
#include <cctype>
#include <string>
using namespace std;

//added some new features: user sign up, multiple users can use/execute the program, can see past users and scores, how to use the program page

//functions:
//function to display menu: take quiz, how to use program, past scores of players, exit
void DisplayMenu();

//function  for user signup page, before taking quiz
void UserInput(string& username, int& age);

//function for taking quiz, shows phrase and asks for input from user
void TakeQuiz(string& username, string phrase[][2], int QuizSize, int& score, string& UserAnswer, int& i);

//function to check the phrase and its corresponding translation in the array, then updates the score everytime its right, if not displays the correct translation
void CheckPhrase(string& UserAnswer, string translation[][2], int& score, int& i);

//funct. that display the final score out of the total items of the user
void DisplayFinalScore(string& username, int& score, int TotalItems);

//function to display instructions to user, how this program  works, and remiinders before taking quiz
void HowToUse();

//function used to immediately terminate/finish the program
void Exit();

int main()
{
	//constant variables
	const int MAX_USERS = 100;
	const int MAX_ITEMS = 10;

	//struct to show past history ofu users and scores
	struct UserHistory {
		string PersonName;
		int FinalScore;
	};

	//array for past scores and users who have used the program
	UserHistory UserLogs[MAX_USERS];

	//2d array for phrases + translaton
	string Quiz[MAX_ITEMS][2] = {
		{"magandang araw!", "good day!"},
		{"kamusta ka?", "how are you?"},
		{"ano pangalan mo?", "what is your name?"},
		{"magkano ito?", "how much is this?"},
		{"nagugutom ako.","i am hungry."},
		{"isang milyon.", "one million."},
		{"ngayon, bukas, kahapon.", "today, tomorrow, yesterday."},
		{"ngayong linggo, sa susunod na linggo, nakaraang linggo.", "this week, next week, last week."},
		{"mahal kita.", "i love you."},
		{"nagsasalita ka ba ng ingles?","do you speak english?"},
	};

	string username, UserAnswer;
	char newuser;
	int i, age, choice, score, usercount = 0;

	cout << "Welcome to the Language Translation Practice Tool <3 , Dear user !\n\n";
	system("pause");

	do {
		score = 0;

		DisplayMenu();
		//what player wants to do
		cout << "What would you like to do: ";
		cin >> choice;

		switch (choice) {
		case 1:
			//asking user for input first
			UserInput(username, age);
			UserLogs[usercount % MAX_USERS].PersonName = username; //indexing into array

			TakeQuiz(username, Quiz, MAX_ITEMS, score, UserAnswer, i);

			UserLogs[usercount % MAX_USERS].FinalScore = score;
			usercount++; //every successful attempt of quiz they count the user to one more

			break;
		case 2:
			HowToUse();
			break;
		case 3:
			system("cls");
			//displaying past scores
			cout << "- - -[PAST USER SCORES]- - -\n";

			if (usercount == 0) {
				cout << "\nNo History yet!\n\n";
			}
			else {
				//showing the array of past users and scores
				for (int i = 0; i < usercount; i++) {
					cout << UserLogs[i].PersonName << "\t-\tScore: " << UserLogs[i].FinalScore << "/10" << endl;
				}
			}
			system("pause");
			break;
		case 4:
			Exit();
			break;
		default:
			cout << "\nInvalid Input ! Please try again!!\n\n";
			system("pause");
			break;
		}
	} while (choice != 4);

	return 0;
}


//for signing up of user + age
void UserInput(string& username, int& age) {
	char correctinfo;
	do {
		system("cls");
		cout << "- - -[USER INFO]- - -"
			<< "\nHello, Dear User!"
			<< "\n\nPlease enter your name: ";

		cin.ignore(); //i use this because it skips the input of the username when function called -- part of iostream library.
		getline(cin, username);


		do {
			cout << "\nPlease enter your age: ";
			cin >> age;

			if (age <= 0) {
				cout << "\nInvalid Input! Please try again!\n";
			}
		} while (age <= 0);

		cout << "\n\nYour name is: " << username << " and you are " << age << " years old!"
			<< "\n\nIs the info above correct? (Y/N): ";
		cin >> correctinfo;

		correctinfo = toupper(correctinfo);

		while (correctinfo != 'Y' && correctinfo != 'N') {
			cout << "\nInvalid Input ! Please try again!\n\n";
			cin >> correctinfo;
			correctinfo = toupper(correctinfo);
		}

		if (correctinfo == 'N') {
			cout << "\n\nOur bad! Let us sign you up again...\n\n";
			system("pause");

		}
	} while (correctinfo == 'N');
	cout << "\nYou have successfully signed up! Moving on to the Quiz...\n\n";
	system("pause");
}

//displays menu to: take quiz, how to use the program, display the pas scores of users, exit program
void DisplayMenu() {
	system("cls");
	cout << "- - -[LANGUAGE TRANSLATION PRACTICE TOOL]- - -\n"
		<< "1.\tTake the Quiz\n"
		<< "2.\tHow to Use\n"
		<< "3.\tPast Scores\n"
		<< "4.\tExit\n";
}

//instructions, general use or point of the program +reminders to do and pay attention off before taking quiz
void HowToUse() {
	system("cls");
	cout << "- - -[HOW TO USE]- - -\n"
		<< "Welcome to the Language Translation Practice Tool! (made by yours truly, casley <3)\n"
		<< "Here, we will prompt you, dear user, some phrases in tagalog!"
		<< "\nYour goal is to translate them into english. But please remember that...\n"
		<< "\n-\tEverytime you have to take the quiz, you would need to sign in first."
		<< "\n-\tNo retries! if you want a new score you'd have to sign in again!"
		<< "\n-\tPlease follow the punctuation in the phrases, sometimes it will mark you wrong for it not being the same."
		<< "\n-\tThe phrases are case sensitive. Thus, answer them in lower case as much as possible."
		<< "\n-\tUnfortunately, you can't go back to previous questions."
		<< "\n-\tPlease do not cheat!"
		<< "\n\nAre you ready now? Let us start!\n\n";

	system("pause");
}

//function to immediately terminate the program if the person wants to exit
void Exit() {
	system("cls");
	cout << "- - -[EXIT]- - -\n"
		<< "Thank you for using the program! See you next time <3\n\n";

	exit(0);
}

//start of taking the quiz, displays the username plus score at the right. Displays phrase from array and prompts user to translate...
// uses the checkphrase function to check if phrase inputted by the user is correct
// uses display final score function that displays the results once for loop is finished
void TakeQuiz(string& username, string phrase[][2], int QuizSize, int& score, string& UserAnswer, int& i) {

	cin.ignore(); //had to use it cuz without it, iniignore nya yung input sa first line tas agad wrong input. 

	//displaying the phrase and asks for user translation
	for (i = 0; i < QuizSize; i++) {

		system("cls");

		cout << "- - -[QUIZ]- - -\t\t\t\t\t\t\t\t|User: " << username
			<< "\nInstruction: Translate the tagalog phrases into english. Good luck!\t\t|Score: " << score << endl;

		cout << "\nPhrase: " << phrase[i][0] //gets phrase from the 1st column [0] of the array increases by each row[i]
			<< "\nAnswer: ";
		getline(cin, UserAnswer);

		CheckPhrase(UserAnswer, phrase, score, i);
	}
	DisplayFinalScore(username, score, QuizSize);
}

//checks the answer of the user is the same as the translated  phrase in the array, if correct, the user gets a point, if not, the correct answer is displayed
void CheckPhrase(string& UserAnswer, string translation[][2], int& score, int& i) {
	//the answer will be checked immediately updating the user what is their score on the second colume [1]pf array
	if (UserAnswer == translation[i][1]) {
		cout << "\n\nDING! Congrats you got it right! +1";
		score++;
		cout << "\nScore: " << score << endl << endl;
		system("pause");
	}
	else {
		cout << "\n\nBZZT! You are wrong !"
			<< "\nCorrect Answer: " << translation[i][1]
			<< "\nScore: " << score << endl << endl;
		system("pause");
	}
}

//finalizes the quiz results, showing the username, the  score out of 10
void DisplayFinalScore(string& username, int& score, int TotalItems)
{
	system("cls");
	cout << "- - -[QUIZ FINISHED]- - -"
		<< "\nYou have finished the Quiz, " << username << "! Your final score is : " << score << " / " << TotalItems << endl << endl;
	system("pause");
}