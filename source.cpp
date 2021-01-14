#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace  std;
void Printmessage(string message, bool printtop = true, bool printbottom = true)
{
	if (printtop)
	{
		cout << "+----------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << "|";
	}
	bool front = true;
	for (int i = message.length(); i < 33; i++)
	{
		if (front)
		{
			message = " " + message;
		}
		else
		{
			message = message + " ";
		}
		front = !front;
	}

	cout << message.c_str();
	if (printbottom)
	{
		cout << " |" << endl;
		cout << "+----------------------------------+" << endl;
	}
	else
	{
		cout << " |" << endl;
	}
}
void drawhangman(int guesscount = 0)
{
	if (guesscount >= 1)
		Printmessage("|", false, false);
	else
		Printmessage("", false, false);
	if (guesscount >= 2)
		Printmessage("|", false, false);
	else
		Printmessage("", false, false);
	if (guesscount >= 3)
		Printmessage("O", false, false);
	else
		Printmessage("", false, false);
	if (guesscount == 4)
		Printmessage("/  ", false, false);

	if (guesscount == 5)
		Printmessage("/| ", false, false);

	if (guesscount >= 6)
		Printmessage("/|\\", false, false);

	if (guesscount >= 7)
		Printmessage("|", false, false);
	else
		Printmessage("", false, false);
	if (guesscount == 8)
		Printmessage("/", false, false);
	if (guesscount == 9)
		Printmessage("/ \\", false, false);

}

void Printletters(string input, char from, char to)
{
	string s;
	for (char i = from; i <= to; i++)
	{
		if (input.find(i) == string::npos)
		{
			s += i;
			s += " ";
		}

		else
			s += "  ";

	}
	Printmessage(s, false, false);

}
void Printavailletters(string taken)
{
	Printmessage("AVAILABLE LETTERS");
	Printletters(taken, 'A', 'M');
	Printletters(taken, 'N', 'Z');
}
bool printwordandwincheck(string word, string guessed)
{
	bool won = true;
	string s;
	for (int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
	}
	Printmessage(s, false);
	return won;
}
string randomword(string path)
{
	int numlines = 1000;

	string word;
	ifstream reader(path);
	int lineNum = 0;
	int randomline = rand() % numlines;
	while (getline(reader, word))
	{
		if (lineNum++ == randomline) break;
	}
	return word;

}
int triesleft(string word, string guessed)
{
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == string::npos)
			error++;
	}
	return error;
}


int main()
{
	srand(time(0));
	char c;
	do {

		string c_name;
		cout << "Please enter your name : ";
		getline(cin, c_name);
		cout << "Hello and welcome : " << c_name << endl;
		cout << "Please note that this game is in early development, please use only uppercase letters.Thank You." << endl;
		cout << "PRESS ANY KEY AND ENTER TO PLAY : ";
		cin >> c;
	} while (c == 'n');
	string guesses;
	string wordtoguess;
	wordtoguess = randomword("words.txt");
	int tries = 0;
	bool win = false;
	do {

		system("cls");

		Printmessage("HANG MAN");
		drawhangman(tries);
		Printavailletters(guesses);
		Printmessage("GUESS THE WORD");

		win = printwordandwincheck(wordtoguess, guesses);

		if (win)
			break;

		char x;
		cout << ">"; cin >> x;
		if (guesses.find(x) == string::npos)
			guesses += x;
		tries = triesleft(wordtoguess, guesses);
	} while (tries < 10);



	int a, b;
	a = 400;
	b = 1000;



	if (win)
	{
		if (tries == 0)
		{
			cout << "You're Brilliant" << endl;
		}

		if (tries >= 4)
		{
			cout << "You earned " << a << " points" << endl;
		}
		else  if (tries <= 3)
		{
			cout << "You earned " << b << " points " << endl;
		}
		Printmessage("YOU WON");
	}
	else
		Printmessage("YOU LOST");



	system("pause");
	getchar();
	return 0;
}
