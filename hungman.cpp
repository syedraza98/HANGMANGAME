#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<time.h>
using namespace std;
void printmessage(string message,bool printTop=true,bool printbottom=true ){
	if(printTop){
		cout<<"+---------------------------------+"<<endl;
		cout<<"|";

	}
	else{
		cout<<"|";
	}
	bool front=true;
	for(int i=message.length();i<33;i++ ){
		if(front){
			message=" "+message;

		}
		else{
			message=message+" ";
		}
		front=!front;
	}
	cout<<message;

	if(printbottom){
		 cout<<"|";
		 cout<<endl<<"+---------------------------------+"<<endl;
		
	}
	else{
		cout<<"|"<<endl;
	}
}
void drawhangman(int guesscount=0){
	if (guesscount >= 1)
		printmessage("|", false, false);
	else
		printmessage("", false, false);

	if (guesscount >= 2)
		printmessage("|", false, false);
	else
		printmessage("", false, false);

	if (guesscount >= 3)
		printmessage("O", false, false);
	else
		printmessage("", false, false);

	if (guesscount == 4)
		printmessage("/  ", false, false);
	
	if (guesscount == 5)
		printmessage("/| ", false, false);

	if (guesscount >= 6)
		printmessage("/|\\", false, false);
	else
		printmessage("", false, false);

	if (guesscount >= 7)
		printmessage("|", false, false);
	else
		printmessage("", false, false);

	if (guesscount == 8)
		printmessage("/", false, false);

	if (guesscount >= 9)
		printmessage("/ \\", false, false);
	else
		printmessage("", false, false);
	

}
void PrintLetters(string input, char from, char to)
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
	printmessage(s, false, false);
}
void PrintAvailableLetters(string taken)
{
	printmessage("Available letters");
	PrintLetters(taken, 'A', 'M');
	PrintLetters(taken, 'N', 'Z');
}
bool PrintWordAndCheckWin(string word, string guessed)
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
	printmessage(s, false);
	return won;
}
string LoadRandomWord(string path)
{
	int lineCount = 0;
	string word;
	vector<string> v;
	ifstream reader(path);
	if (reader.is_open())
	{
		while (std::getline(reader, word))
			v.push_back(word);

		int randomLine = rand() % v.size();

		word = v.at(randomLine);
		reader.close();
	}
	return word;
}
int TriesLeft(string word, string guessed)
{
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == string::npos)
			error++;
	}
	return error;
}

int main(){
    srand(time(0));
	string guesses;
	string wordToGuess;
	wordToGuess = LoadRandomWord("word.txt");
	int tries = 0;
	bool win = false;
	do
	{
		
		printmessage("HANGMAN");
		drawhangman(tries);
		PrintAvailableLetters(guesses);
		printmessage("Guess the word");
		win = PrintWordAndCheckWin(wordToGuess, guesses);

		if (win)
			break;

		char x;
		cout << ">"; cin >> x;

		if (guesses.find(x) == string::npos)
			guesses += x;

		tries = TriesLeft(wordToGuess, guesses);

	} while (tries < 10);

	if (win)
		printmessage("YOU WON!");
	else
		printmessage("GAME OVER");

	
	
	return 0;
}

