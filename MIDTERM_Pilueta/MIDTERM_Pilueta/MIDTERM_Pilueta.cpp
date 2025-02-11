#include <iostream>
#include <cctype>
#include <string>
using namespace std;

//added some new features: user sign up, multiple users can use/execute the program, can see past users and scores, how to use the program page

void UserInput(string& username, int& age); 
void DisplayMenu();
void HowToUse();
void Exit();
void TakeQuiz(int& score, string& username);

int main()
{
	//user input
	string username;
	int age, usercount = 0;
	char newuser;//asking if another user is gonna use the program
	int choice, score;
	const int MAX_USERS = 100; 

	//struct to show past history ofu users and scores
	struct UserHistory {
		string PersonName;
		int FinalScore;
	};

	//array for past scores
	UserHistory UserLogs[MAX_USERS];  

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

					TakeQuiz(score, username); 
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
							cout << UserLogs[i].PersonName << "\t-\tScore: " << UserLogs[i].FinalScore<<"/10"<<endl;  
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



void DisplayMenu() {
	system("cls");
	cout << "- - -[LANGUAGE TRANSLATION PRACTICE TOOL]- - -\n"
		<<"1.\tTake the Quiz\n"
		<<"2.\tHow to Use\n"
		<<"3.\tPast Scores\n"
		<<"4.\tExit\n";
}

void HowToUse() {
	system("cls");
	cout << "- - -[HOW TO USE]- - -\n"
		<<"Welcome to the Language Translation Practice Tool! (made by yours truly, casley <3)\n"
		<<"Here, we will prompt you, dear user, some phrases in tagaolg!"
		<<"\nYour goal is to translate them into english. But please remember that...\n"
		<<"\n-\tEverytime you have to take the quiz, you would need to sign in first."
		<<"\n-\tNo retries! if you want a new score you'd have to sign in again!"
		<<"\n-\tPlease follow the punctuation in the phrases, sometimes it will mark you wrong for it not being the same."
		<<"\n-\tThe phrases are case sensitive. Thus, answer them in lower case as much as possible."
		<<"\n-\tUnfortunately, you can't go back to previous questions."
		<<"\n-\tPlease do not cheat!"
		<<"\n\nAre you ready now? Let us start!\n\n";

	system("pause");
}

void Exit() {
	system("cls");
	cout << "- - -[EXIT]- - -\n"
		<< "Thank you for using the program! See you next time <3\n\n";

	exit(0);
}

void TakeQuiz(int &score, string &username) {
	//intializing struct + arrays for quiz items + variabes
	string UserAnswer;
	int i; //for the array loop
	const int MAX_ITEMS = 10;

	struct Translate {
		string phrase;
		string translatedPhrase;
	};

	//array based on struct for phrases + translaton
	Translate Quiz[MAX_ITEMS] = {
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

	cin.ignore(); //had to use it cuz without it, iniignore nya yung input sa first line tas agad wrong input. (p.s. sir kasama ito sa iostream library ha di ito advanced BWAHAHA)

	//displaying the phrase and asks for user translation
	for (i = 0; i < MAX_ITEMS; i++) {

		system("cls");

		cout << "- - -[QUIZ]- - -\t\t\t\t\t\t\t\t|User: " << username
			<< "\nInstruction: Translate the tagalog phrases into english. Good luck!\t\t|Score: " << score << endl;

		cout << "\nPhrase: " << Quiz[i].phrase
			<< "\nAnswer: ";
		getline(cin, UserAnswer);


		//the answer will be checked immediately updating the user what is their score
		if (UserAnswer == Quiz[i].translatedPhrase) {
			cout << "\n\nDING! Congrats you got it right! +1";
			score++;
			cout << "\nScore: " << score << endl<<endl;
			system("pause");
		}
		else {
			cout << "\n\nBZZT! You are wrong !"
				<< "\nCorrect Answer: " << Quiz[i].translatedPhrase 
				<<"\nScore: "<< score << endl << endl;
			system("pause"); 
		}
	}

	system("cls");
	cout << "- - -[QUIZ FINISHED- - -"
		<<"\nYou have finished the Quiz, "<<username<<"! Your final score is : " << score << " / " << MAX_ITEMS << endl<<endl; 
	system("pause");
}
