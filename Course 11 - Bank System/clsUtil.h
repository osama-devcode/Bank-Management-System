#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsUtil
{

	public:

		enum enCharType {
			SamallLetter = 1, CapitalLetter = 2,
			Digit = 3, MixChars = 4, SpecialCharacter = 5
		};


	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int from, int to)
	{
		int randNum = rand() % (to - from + 1) + from;
		return randNum;
	}

	static char GetRandomCharacter(enCharType CharType)
	{

		//updated this method to accept mixchars
		if (CharType == MixChars)
		{
			//Capital/Samll/Digits only
			CharType = (enCharType)RandomNumber(1, 3);

		}

		switch (CharType)
		{

		case enCharType::SamallLetter:
		{
			return char(RandomNumber(97, 122));
			break;
		}
		case enCharType::CapitalLetter:
		{
			return char(RandomNumber(65, 90));
			break;
		}
		case enCharType::SpecialCharacter:
		{
			return char(RandomNumber(33, 47));
			break;
		}
		case enCharType::Digit:
		{
			return char(RandomNumber(48, 57));
			break;
		}
	defualt:
		{
			return char(RandomNumber(65, 90));
			break;
		}
		}
	}

	static string GenerateWord(int wordLength, enCharType charType)
	{
		string word = "";

		for (int i = 0; i < wordLength; i++)
		{
			word += GetRandomCharacter(charType);
		}

		return word;
	}

	static string GenerateKey(int groupLength, int groupCount, enCharType charType)
	{
		string key = "";
		for (int i = 0; i < groupCount; i++)
		{
			key += GenerateWord(groupLength, charType);
			if (i < groupCount - 1)
			{
				key = key + "-";
			}
		}

		return key;
	}

	static void GenerateKeys(int num, int groupLength, int groupCount, enCharType charType)
	{
		for (int i = num; i > 0; i--)
		{
			cout << "Key [" << num - i + 1 << "]: " << GenerateKey(groupLength, groupCount, charType);
			cout << endl;
		}
	}

	static void Swap(int &A,int &B)
	{
		int Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(string& A, string& B)
	{
		string Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(double& A, double& B)
	{
		double Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(clsDate& A, clsDate& B)
	{
		clsDate Temp;
		Temp = A;
		A = B;
		B = Temp;
	}


	static void ShuffleArray(int arr[100], int arrLength)
	{
		int j = 0;
		for (int i = arrLength - 1; i >= 0; i--)
		{
			j = RandomNumber(0, i);
			Swap(arr[j], arr[i]);
		}
	}

	static void ShuffleArray(string arr[100], int arrLength)
	{
		int j = 0;
		for (int i = arrLength - 1; i >= 0; i--)
		{
			j = RandomNumber(0, i);
			Swap(arr[j], arr[i]);
		}
	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrayLength, int from, int To)
	{

		for (int i = 0; i < arrayLength; i++)
		{
			arr[i] = RandomNumber(1, 100);
		}
	}

	static void FillArrayWithRandomWords(string arr[100], int arrayLength, enCharType CharType, int WordLength)
	{

		for (int i = 0; i < arrayLength; i++)
		{
			arr[i] = GenerateWord(WordLength,CharType);
		}
	}

	static void FillArrayWithRandomKeys(string arr[100], int arrayLength, enCharType CharType)
	{

		for (int i = 0; i < arrayLength; i++)
		{
			arr[i] = GenerateKey(4,5,CharType);
		}
	}

	static string  Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i < NumberOfTabs; i++)
		{
			t = t + "\t";
			cout << t;
		}
		return t;

	}

	static string  EncryptText(string Text, short EncryptionKey)
	{

		for (int i = 0; i <= Text.length(); i++)
		{

			Text[i] = char((int)Text[i] + EncryptionKey);

		}

		return Text;

	}

	static string  DecryptText(string Text, short EncryptionKey)
	{

		for (int i = 0; i <= Text.length(); i++)
		{

			Text[i] = char((int)Text[i] - EncryptionKey);

		}
		return Text;

	}
};

