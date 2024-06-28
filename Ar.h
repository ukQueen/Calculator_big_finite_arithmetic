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
	//�������� �����
	string a;
	string b;


	char OperatorPlusChar[8][8];//��������
	char OperatorPlusChar_Shift[8][8];//�������� �������
	char OperatorMultChar[8][8];//������������
	char OperatorMultChar_Shift[8][8];//������������ �������
	//char OperatorSubChar[8][8];//���������
	//char OperatorDivChar[8][8][8];//�������
	
	char Dictionary[8] = { 'a','b','c','d','e','f','g','h' };
	
	void CreateOperatorPlus();  //+
	/// <summary>
	/// 
	/// </summary>
	/// <param name="array"></param>
	/// <param name="mult"></param>
	///  ���� 1, �� ����� ���������, ���� 0 - ��������
	void CreateOperator_Shift( bool flag);
	void CreateOperatorMult(); 
	//void CreateOperatorMult_Shift();

	char Summ(char a, char b); //+
	int DictionaryToInt(char a);//+
	int SearchIndex(char a);//���������� ������� � ������� ���� 1//+
	char Mult(char a, char b);//��������� ���������
	int SearchInGraph(char a); // ����� �� ����� (��� ���������) //+
	char SearchInPlus(char a,char b); // ����� �� ������� ��������
	char SearchInPlus_Shift(char a,char b); // ����� �� ������� �������� � ��������

	char SearchInSub(char a,char b);// ����� ���������� � �������� �� ������� ��������
	char SearchInMult(char a,char b); // ����� �� ������� ���������
	char SearchInMult_Shift(char a,char b); // ����� �� ������� �������� � ���������
	//int IndexInDictionary(char s);// ������� �� ����� � ����� 
	string Check();
	void PrintPlusOneChar();
	void PrintOperator(char array[][8]);
	string ToSumm(string a, string b);//�����
	string ToSub(string a, string b);//���������
	string ToMult(string a, string b);//���������
	string ToMult_Base(string a, string b);//���������
	vector <string> ToDiv(string a, string b, vector <string> result);//�������
	/// <summary>
	/// ����������, ��� ������������ ������� (1-�����, 0-���������)
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

