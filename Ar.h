#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

class Ar
{
	vector <char> PlusOneChar;

	regex power; 
	//regex powerful; 
	char Graph[8];
	//regex out; 
	string buf;
	//вводимые числа
	string a;
	string b;


	char OperatorPlusChar[8][8];//сложение
	char OperatorPlusChar_Shift[8][8];//сложение перенос
	char OperatorMultChar[8][8];//произведение
	char OperatorMultChar_Shift[8][8];//произведение перенос
	//char OperatorSubChar[8][8];//вычитание
	//char OperatorDivChar[8][8][8];//деление
	
	char Dictionary[8] = { 'a','b','c','d','e','f','g','h' };
	
	void CreateOperatorPlus();  //+
	/// <summary>
	/// 
	/// </summary>
	/// <param name="array"></param>
	/// <param name="mult"></param>
	///  если 1, то будет умножение, если 0 - сложение
	void CreateOperator_Shift( bool flag);
	void CreateOperatorMult(); 
	//void CreateOperatorMult_Shift();

	char Summ(char a, char b); //+
	int DictionaryToInt(char a);//+
	int SearchIndex(char a);//нахождение индекса в правиле плюс 1//+
	char Mult(char a, char b);//находение умножения
	int SearchInGraph(char a); // поиск по графу (для умножения) //+
	char SearchInPlus(char a,char b); // поиск по таблице сложения
	char SearchInPlus_Shift(char a,char b); // поиск по таблице переноса в сложении

	char SearchInSub(char a,char b);// поиск слагаемого в разности по таблице сложения
	char SearchInMult(char a,char b); // поиск по таблице умножения
	char SearchInMult_Shift(char a,char b); // поиск по таблице переноса в умножении
	//int IndexInDictionary(char s);// переход от цифры к букве 
	string Check();
	void PrintPlusOneChar();
	void PrintOperator(char array[][8]);
	string ToSumm(string a, string b);//сумма
	string ToSub(string a, string b);//вычитание
	string ToMult(string a, string b);//умножение
	string ToMult_Base(string a, string b);//умножение
	vector <string> ToDiv(string a, string b, vector <string> result);//деление
	/// <summary>
	/// показывает, где используется функция (1-сумма, 0-вычитание)
	/// </summary>
	string ToSumm_or_ToSub(string a, string b, bool flag);
	void PringGraph();
	bool Comparasion(char a, char b);
	int compare(string a, string b);
	void SummCalculator();
	void SubCalculator();
	void MultCalculator();
	void DivCalculator();
		
	
	
public:
	void Menu();
	Ar();
};

