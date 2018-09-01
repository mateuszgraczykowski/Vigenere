#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>


class cipher
{
private:
	int horizontalLetter;
	int verticalLetter;
	std::string cipheredText;
	char *replacement=new char[100];
	void saveTexttoFile();
	void takeKeyAndTextLetter();
	

public:
	std::string text;
	std::string key;
	char  toCode()
	{
		return (horizontalLetter % 97 + verticalLetter % 97) % 26 + 97;
	}
	char toDecode();
	int switchReplacement;
	void printAndCopyToVariable();
	void openFileandCipher(std::string);
};
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
char cipher::toDecode()
{
	
	if (verticalLetter <= horizontalLetter)
	{
		return horizontalLetter-verticalLetter+97;
	}
	else 
	{
		return 123-verticalLetter+horizontalLetter;
	}
	
}

void cipher::saveTexttoFile()
{
	std::cout << "\nPress (1) if you want to save a ciphered message, press (2) if you don't. " << std::endl;
	

	int option;
	std::cin >> option;

	if (option == 1)
	{
		std::ofstream createdFile("CipheredMessage.txt");
		createdFile.write(&cipheredText[0],text.length());
		std::cout << "\nCipher is saved." << std::endl;
		createdFile.close();
	}
	else
		exit(0);	
}
void cipher::openFileandCipher(std::string pathofFile)
{
	std::fstream myFile(pathofFile, std::ios::in|std::ios::binary);
	if (myFile.good())
	{
		std::getline(myFile, text);
		printAndCopyToVariable();
		myFile.close();
	}		
	else
		std::cout << "\nSomething went wrong." << std::endl;
}

void cipher::takeKeyAndTextLetter()
{
	key.erase(remove_if(key.begin(), key.end(), isspace), key.end());
	transform(key.begin(), key.end(), key.begin(), ::tolower);
	text.erase(remove_if(text.begin(), text.end(), isspace), text.end());
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	for (int i = 0; i < text.length(); i++)
	{
		verticalLetter = key[i%key.length()];
		horizontalLetter = text[i];
		if(switchReplacement==1)
		replacement[i] = toCode();
		if(switchReplacement==2)
		replacement[i] = toDecode();
	}
}

void cipher::printAndCopyToVariable()
{
	takeKeyAndTextLetter();
	for (int i = 0; i < text.length(); i++)
	{
		std::cout << replacement[i];
	}
	
	cipheredText=replacement;
	std::cout <<std::endl;

	saveTexttoFile();
}

int main()
{
	cipher object_1;	
	int option;
	std::string pathofFile;

	while (true)
	{
		std::cout << "Press (1) if you want to (de)cipher .txt file.\nPress (2) if you want insert text manually.\nPress (any other key) if you want to end a programme. ";
		std::cout << "\n\nVigenere cipher doesn't support digits and special characters, but you can use them if you want to." << std::endl;
		std::cin >> option;
		
		switch (option)
		{
		case 1:
			std::cout << std::endl;
			std::cout << "\nIf you want to cipher text press (1) if to decipher, press (2). " << std::endl;
			std::cin >> object_1.switchReplacement; std::cin.ignore();
			std::cout << "\nPut path of your file: ";
			std::getline(std::cin, pathofFile);
			std::cout << "\nWrite a key: " << std::endl;
			std::getline(std::cin, object_1.key);
			std::cout << "------------------------------------------" << std::endl;
			object_1.openFileandCipher(pathofFile);
			break;
		case 2:			
			std::cout << std::endl;
			std::cout << "\nIf you want to cipher text press (1) if to decipher, press (2)." << std::endl;
			std::cin >>object_1.switchReplacement;
			std::cin.ignore();
			std::cout << "\nWrite a massage which you want to cipher." << std::endl;
			std::getline(std::cin, object_1.text);
			std::cout << "\nWrite a key: " << std::endl;
			std::getline(std::cin, object_1.key);
			std::cout << "------------------------------------------" << std::endl;
			object_1.printAndCopyToVariable();
			break;
		default:
			exit(0);
		}

	}
	system("pause");	
}