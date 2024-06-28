#include "Ar.h"

Ar::Ar() {
	PlusOneChar.push_back('b');
	PlusOneChar.push_back('f');
	PlusOneChar.push_back('a');
	PlusOneChar.push_back('g');
	PlusOneChar.push_back('d');
	PlusOneChar.push_back('h');
	PlusOneChar.push_back('c');
	PlusOneChar.push_back('e');
	/*

	PlusOneChar.push_back('b');//другой вариант
	PlusOneChar.push_back('h');
	PlusOneChar.push_back('f');
	PlusOneChar.push_back('a');
	PlusOneChar.push_back('g');
	PlusOneChar.push_back('d');
	PlusOneChar.push_back('c');
	PlusOneChar.push_back('e');
	*/

		/*
		0a
		1b
		2c
		3d
		4e
		5f
		6g
		7h
		*/
	Graph[0] = 'a';
	Graph[1] = 'b';
	Graph[2] = 'f';
	Graph[3] = 'h';
	Graph[4] = 'e';
	Graph[5] = 'd';
	Graph[6] = 'g';
	Graph[7] = 'c';
	/*
	Graph[0] = 'a';//другой
	Graph[1] = 'b';
	Graph[2] = 'h';
	Graph[3] = 'e';
	Graph[4] = 'g';
	Graph[5] = 'c';
	Graph[6] = 'f';
	Graph[7] = 'd';
	*/

	power= ("^(-?[a-h]{1,9})$");



	CreateOperatorPlus();
	CreateOperator_Shift(0);
	CreateOperatorMult();
	CreateOperator_Shift(1);
}

//+
void Ar::CreateOperatorPlus() {
	for (int i = 0; i < 8; i++) {
		OperatorPlusChar[i][0] = Dictionary[i];
		OperatorPlusChar[0][i] = Dictionary[i];
		OperatorPlusChar[i][1] = PlusOneChar[i];
		OperatorPlusChar[1][i] = PlusOneChar[i];
	}
	
	for (int i = 2; i < 8; i++) {
		for (int j = i; j < 8; j++) {
			char buf = Summ(Dictionary[i], Dictionary[j]);
			OperatorPlusChar[i][j] = buf;
			OperatorPlusChar[j][i] = buf;

		}
	}
}
//+
char Ar::Summ(char a, char b) {
	int k = 0;
	char result = a;
	char buf = b;
	char check = b;
	while (check != 'b') {
		buf = Dictionary[SearchIndex(buf)];
		check = PlusOneChar[DictionaryToInt(buf)];
		k++;
	}
	while (k > 0) {
		result = PlusOneChar[DictionaryToInt(result)];
		k--;
	}
	return result;
}
//+
void Ar::CreateOperator_Shift( bool flag) {
	int k;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			k = flag? SearchInGraph(Dictionary[i]) * SearchInGraph(Dictionary[j]) 
				: SearchInGraph(Dictionary[i]) + SearchInGraph(Dictionary[j]);
			k = k / 8;
			if (flag)
				OperatorMultChar_Shift[i][j] = Graph[k];
			else
				OperatorPlusChar_Shift[i][j] = Graph[k];
		}
	}
}

//+
void Ar::CreateOperatorMult() {
	for (int i = 0; i < 8; i++) {
		OperatorMultChar[i][0] = 'a';
		OperatorMultChar[0][i] = 'a';
		OperatorMultChar[i][1] = Dictionary[i];
		OperatorMultChar[1][i] = Dictionary[i];
	}
	for (int i = 2; i < 8; i++) {
		for (int j = i; j < 8; j++) {
			char buf = Mult(Dictionary[i], Dictionary[j]);
			OperatorMultChar[i][j] = buf;
			OperatorMultChar[j][i] = buf;

		}
	}
}
//+
char Ar::Mult(char a, char b) {
	char result = a;
	char buf = a;
	int k = SearchInGraph(b) - 1;
	while (k > 0) {
		result = SearchInPlus(result, buf);
		k--;
	}
	return result;
}


void Ar::PrintPlusOneChar() {
	printf("\nПравило \"+1\"");
	printf("\n ---------------------");
	printf("\n| + | a b c d e f g h |");
	printf("\n ---------------------");
	printf("\n| b |");
	for (int i = 0; i < 8; i++) {
		printf(" %c", PlusOneChar[i]);
	}
	printf(" |\n ---------------------\n\n");
}

void Ar::PrintOperator(char array[][8]) {
	printf("\n");
	string s;
	if (array == OperatorPlusChar)
		s = "Сложение \"+\"";
	else if (array == OperatorPlusChar_Shift)
		s = "Перенос \"+_s\"";
	else if (array == OperatorMultChar)
		s = "Умножение \"*\"";
	else if (array == OperatorMultChar_Shift)
		s = "Перенос \"*_s\"";
	
	//printf("\n %s", s);
	std::cout << '\n' << s;
	    printf("\n ------------------------");

	if (array == OperatorPlusChar)
		printf("\n|  +  | a b c d e f g h |");
	else if (array == OperatorPlusChar_Shift)
		printf("\n| +_s | a b c d e f g h |");
	else if (array == OperatorMultChar)
		printf("\n|  *  | a b c d e f g h |");
	else if (array == OperatorMultChar_Shift)
		printf("\n| *_s | a b c d e f g h |");

	printf("\n ------------------------");
	for (int i = 0; i < 8; i++) {
		printf("\n|  %c  |",Dictionary[i]);
		for (int j = 0; j < 8; j++) {
			printf(" %c", array[i][j]);
		}
		printf(" |");
	}
	printf("\n ------------------------\n\n");

}

//+
int Ar::SearchIndex(char a) {
	for (int i = 0; i < 8; i++)
		if (PlusOneChar[i]== a)
			return i;
};

//+
int Ar::DictionaryToInt(char a) {
	for (int i = 0; i < 8; i++) {
		if (a == Dictionary[i])
			return i;
	}
}

//+
int Ar::SearchInGraph(char a) {
	for (int i = 0; i < 8; i++)
		if (a == Graph[i])
			return i;
};
//+
char Ar::SearchInPlus(char a, char b) {
			return OperatorPlusChar[DictionaryToInt(a)][DictionaryToInt(b)];
};
//+
char Ar::SearchInPlus_Shift(char a, char b) {
			return OperatorPlusChar_Shift[DictionaryToInt(a)][DictionaryToInt(b)];
};

/// <summary>
/// 
/// </summary>
/// <param name="a">число из которого вычитаем (уменьшаемое)</param> 
/// <param name="b">число которое вычитаем (вычитаемое) </param> 
/// <returns></returns>
char Ar::SearchInSub(char a, char b) {	
	for (int i = 0; i < 8; i++) {
		if (OperatorPlusChar[i][DictionaryToInt(b)] == a) {
			return Dictionary[i];
		}
	}
			
};


//+
char Ar::SearchInMult(char a, char b) {	
			return OperatorMultChar[DictionaryToInt(a)][DictionaryToInt(b)];
};
//+
char Ar::SearchInMult_Shift(char a, char b) {	
			return OperatorMultChar_Shift[DictionaryToInt(a)][DictionaryToInt(b)];
};


bool Ar::Comparasion(char a, char b) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Graph[i] == a && Graph[j] == b)
				if (i < j)
					return true;
				else
					return false;
		}
	}
}


string Ar::ToSumm_or_ToSub(string a, string b, bool fl) {
	string answer = "";
	int minuses_a = 0;
	int minuses_b = 0;
	int flag;
	if (a[0] == '-') {
		minuses_a++;
		a.erase(0, 1);
	}
	if (b[0] == '-') {
		minuses_b++;
		b.erase(0, 1);
	}
	while (a.size() != b.size()) {
		a.size() < b.size() ? a = 'a' + a : b = 'a' + b;
	}

	flag = compare(a, b);
	if ((minuses_a + minuses_b) == 1 && fl == 1
		|| (minuses_a + minuses_b) != 1 && fl == 0) {
		answer = ToSub(a, b);
		if (answer.size() > 8)
			answer = "overflow";
		if (answer != "overflow" &&
			((minuses_b == 1 && flag == -1 && fl == 1) ||
				(minuses_a == 1 && flag == 1 && fl == 1) ||
				((minuses_a + minuses_b) == 0 && flag == -1 && fl == 0) ||
				((minuses_a + minuses_b) == 2 && flag == 1 && fl == 0))) {
			answer = '-' + answer;
		}
	}
	else {
		answer = ToSumm(a, b);
		if (answer.size() > 8)
			answer = "overflow";
		if (answer != "overflow" &&
			((minuses_a == 1 && flag == 1 && fl ==0) ||
				(minuses_a == 1 && flag == -1 && fl == 0) ||
				((minuses_a + minuses_b) == 2 && flag == -1 && fl == 1) ||
				((minuses_a + minuses_b) == 2 && flag == 1 && fl == 1)))
			answer = '-' + answer;
	}
	return answer;
	//std::cout << "\tОтвет: " << answer << "\n\n";
}

string Ar::ToSub(string a, string b) {
	int flag;
	char solution;
	string answer = "";
	flag = compare(a, b);
	if (flag == 0) {
		answer = 'a';
	}
	else {
		if (flag == -1) {
			a.swap(b);
		}
		for (int i = a.size() - 1; i >= 0; i--) {
			if (i > 0) {
				if (Comparasion(a[i], b[i])) {
					int j = i - 1;
					while (j >= 0){
						if (a[j] != 'a') {
							a[j] = SearchInSub(a[j], 'b');
							break;
						}
						else
							a[j] = SearchInSub(a[j], 'b');
							j--;
				}
					solution = SearchInSub('c', b[i]);
					solution = SearchInPlus('b', solution);
					solution = SearchInPlus(a[i], solution);
				}
				else {
					solution = SearchInSub(a[i], b[i]);
				}
				answer = solution + answer;
			}
			else {
				solution = SearchInSub(a[i], b[i]);
				answer = solution == 'a' ? answer : solution + answer;
			}
		}
	}
	while (answer.size() > 1 && answer[0] == 'a')
		answer.erase(0, 1);
	
	return answer;
}

string Ar::ToSumm(string a, string b) {
	char shift1 = 'a';
	char shift2 = 'a';
	char shift3 = 'a';
	char solution;
	string answer = "";
	while (a.size() != b.size()) {
		a.size() < b.size() ? a = 'a' + a : b = 'a' + b;
	}
	for (int i = a.size() - 1; i >= 0; i--) {
		solution = SearchInPlus(a[i], b[i]);
		shift2 = SearchInPlus_Shift(a[i], b[i]);
		shift3 = SearchInPlus_Shift(solution, shift1);
		solution = SearchInPlus(solution, shift1);
		shift1 = SearchInPlus(shift2, shift3);
		answer = solution + answer;
		shift3 = 'a';
		shift2 = 'a';
		if (i == 0 && shift1 != 'a')
			answer = shift1 + answer;
	}
	while (answer.size() > 1 && answer[0] == 'a')
		answer.erase(0, 1);

	return answer;
}

string Ar::ToMult(string a, string b) {
	string answer = "a";
	int minuses_a = 0;
	 int minuses_b = 0;
	if (a[0] == '-') {
		minuses_a++;
		a.erase(0, 1);
	}
	if (b[0] == '-') {
		minuses_b++;
		b.erase(0, 1);
	}
	while (a.size() != b.size()) {
		a.size() < b.size() ? a = 'a' + a : b = 'a' + b;
	}

	answer = ToMult_Base(a, b);

	while (answer.size() > 1 && answer[0] == 'a')
		answer.erase(0, 1);

	if (answer.size() > 8)
		answer = "overflow";

	if (answer[0] != 'a' && answer != "overflow" && (minuses_a + minuses_b) == 1)
		answer = '-' + answer;
	return answer;
}


string Ar::ToMult_Base(string a, string b) {
	string answer = "a";
	string answer_buf = "";
	char shift1 = 'a';
	char shift2 = 'a';
	char shift3 = 'a';
	char solution;
	int flag;
	

	int k = 0;
	for (int i = b.size() - 1; i >= 0; i--) {
		for (int j = a.size() - 1; j >= 0; j--) {
			solution = SearchInMult(a[j], b[i]);
			shift2 = SearchInMult_Shift(a[j], b[i]);
			shift3 = SearchInPlus_Shift(solution, shift1);
			solution = SearchInPlus(solution, shift1);
			shift1 = SearchInPlus(shift2, shift3);
			answer_buf = solution + answer_buf;
			shift3 = 'a';
			shift2 = 'a';
			if (j == 0 && shift1 != 'a')
				answer_buf = shift1 + answer_buf;
		}

		shift1 = 'a';
		int s = k;
		while (s > 0) {
			answer_buf += 'a';
			s--;
		}
		k++;
		answer = ToSumm(answer, answer_buf);
		answer_buf = "";
	}
	
	return answer;
}

vector <string> Ar::ToDiv(string a, string b, vector<string> result) {
	//string buf = a;
	string answer = "a";// делитель
	string answer_buf = "a";//частное
	int minuses_a = 0;
	int minuses_b = 0;
	char shift1 = 'a';
	char shift2 = 'a';
	char shift3 = 'a';
	char solution;
	int flag;
	
	if (a[0] == '-') {
		minuses_a++;
		a.erase(0, 1);
	}
	if (b[0] == '-') {
		minuses_b++;
		b.erase(0, 1);
	}

	if (compare(a, "a") == 0 && compare(b, "a") == 0) { //две переменные равны "a" -> запысываем в вектор "1"
		result.push_back(answer);
		result.push_back(answer_buf);
		result.push_back("1");
	}
	else if (compare(a, "a") != 0 && compare(b, "a") == 0) {//только делитель равен "а" -> записываем "2"
		result.push_back(answer);
		result.push_back(answer_buf);
		result.push_back("2");
	}
	else if (compare(a, "a") == 0 && compare(b, "a") != 0) {//только делимое равено "а" -> записываем "0",
		//то есть получаем какоето число, а именно "a"
		result.push_back(answer);
		result.push_back(answer_buf);
		result.push_back("0");
	}
	else {

		while (a.size() != b.size()) {
			a.size() < b.size() ? a = 'a' + a : b = 'a' + b;
		}


		//ТУТ МНОГО ФОРОВ ДЛЯ ОПТИМИЗАЦИИ ДЕЛЕНИЯ
		while (true) {
			if (compare(ToMult_Base(b, ToSumm(answer, "b")), a) != 1) {
				if (compare(ToMult_Base(b, ToSumm(answer, "ba")), a) != 1) {
					if (compare(ToMult_Base(b, ToSumm(answer, "baa")), a) != 1) {
						if (compare(ToMult_Base(b, ToSumm(answer, "baaa")), a) != 1) {
							if (compare(ToMult_Base(b, ToSumm(answer, "baaaa")), a) != 1) {
								if (compare(ToMult_Base(b, ToSumm(answer, "baaaaa")), a) != 1) {
									if (compare(ToMult_Base(b, ToSumm(answer, "baaaaaa")), a) != 1) {
										if (compare(ToMult_Base(b, ToSumm(answer, "baaaaaaa")), a) != 1) {
											answer = ToSumm(answer, "baaaaaaa");
										}
										else
											answer = ToSumm(answer, "baaaaaa");
									}
									else
										answer = ToSumm(answer, "baaaaa");
								}
								else
									answer = ToSumm(answer, "baaaa");
							}
							else
								answer = ToSumm(answer, "baaa");
						}
						else

							answer = ToSumm(answer, "baa");
					}
					else
						answer = ToSumm(answer, "ba");
				}
				else
					answer = ToSumm(answer, "b");
			}
			else
				break;
		}
		while (a.size() > 1 && a[0] == 'a')
			a.erase(0, 1);

		a = minuses_a == 1 ? '-' + a : a;
		
		while (b.size() > 1 && b[0] == 'a')
			b.erase(0, 1);
		
		b = minuses_b == 1 ? '-' + b : b;

		if (minuses_a == 0 && minuses_b == 1) {
			answer = '-' + answer;
			//answer_buf = ToSub(a, ToMult(b, answer));
		}
		else if (minuses_a == 1 && minuses_b == 0) {
			answer = '-' + answer;
			string m =  ToMult(b, answer);
			if (compare(ToMult(b, answer), a) != 0)
				answer = ToSumm_or_ToSub(answer, "b", 0); //вычитаем один
			//answer_buf = ToSub(a, ToMult(b, answer));
		}
		else if (minuses_a + minuses_b == 2) {
			if (compare(ToMult(b, answer), a) != 0)
				answer = ToSumm_or_ToSub(answer, "b", 1);// прибавляем 1
		}

		answer_buf = ToSumm_or_ToSub(a, ToMult(b, answer), 0);

		result.push_back(answer);
		result.push_back(answer_buf);
		result.push_back("0");
	}
	return result;

}



/// <summary>
/// a<b -> -1
/// a==b -> 0
/// a>b -> 1
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
int Ar::compare(string a, string b) {
	if (a[0] == '-') {
		a.erase(0, 1);
	}
	if (b[0] == '-') {
		b.erase(0, 1);
	}
	while (a.size() != b.size()) {
		a.size() < b.size() ? a = 'a' + a : b = 'a' + b;
	}
	for (int i = 0; i < a.size(); i++) {
		if (Comparasion(a[i], b[i])) //a<b
			return -1;
		if (Comparasion(b[i], a[i])) //a>b
			return 1;
		if (i == a.size() - 1)
			return 0;
	}

}




void Ar::PringGraph() {
	cout << "\nОтношение порядка\n\n";
	for (int i = 0; i < 8; i++) {
		cout << Graph[i];
		if (i != 7)
			cout << " < ";
	}
	cout << endl<<endl;
}

string Ar::Check() {
	while (true) {
		cin >> buf;
		if ((buf[0]=='-'&& buf.size()<=9|| buf[0] != '-' && buf.size() <= 8) &&regex_match(buf, power) && buf != "-" || buf == "0") {
			break; // Ввод соответствует регулярному выражению, выходим из цикла
		}
		else {
			std::cout << "Ошибка ввода! Ведите число в диапозоне [-cccccccc;cccccccc]\n";
		}
	}
	return buf;
}

void Ar::SummCalculator() {
	string answer = "";
	printf("\n --------------------------------------");
	printf("\n Вы перешли в калькулятор сложения.");
	printf("\n Для выхода в главное меню введите [0].\n\n");
	while (true) {
		printf("Что вы хотите сложить?\n");
		a = Check();
		if (a == "0")
			break;
		printf("\"+\"\n");
		b = Check();
		if (b == "0")
			break;
		answer=ToSumm_or_ToSub(a, b,1);
		if (answer == "overflow") {
			std::cout << "\nОтвет: "  << answer << "\n";
		}
		else if (b[0] == '-')
			std::cout << "\nОтвет: " << a << " + (" << b << ") = " << answer << "\n";
		else
			std::cout << "\nОтвет: " << a << " + " << b << " = " << answer << "\n";
	printf(" --------------------------------------\n");

	}
}

void Ar::SubCalculator() {
	string answer = "";
	printf("\n --------------------------------------");
	printf("\n Вы перешли в калькулятор вычитания.");
	printf("\n Для выхода в главное меню введите [0].\n\n");
	while (true) {
		printf("Что вы хотите вычесть?\n");
		a = Check();
		if (a == "0")
			break;
		printf(" \"-\"\n");
		b = Check();
		if (b == "0")
			break;
		answer=ToSumm_or_ToSub(a, b,0);
		if (answer == "overflow") {
			std::cout << "\nОтвет: " << answer << "\n";
		}
		else if (b[0] == '-')
			std::cout << "\nОтвет: " << a << " - (" << b << ") = " << answer << "\n\n";
		else
			std::cout << "\nОтвет: " << a << " - " << b << " = " << answer << "\n\n";
	}
}

void Ar::MultCalculator() {
	string answer = "";
	printf("\n --------------------------------------");
	printf("\n Вы перешли в калькулятор умножения.");
	printf("\n Для выхода в главное меню введите [0].\n\n");
	while (true) {
		printf("Что вы хотите перемножить?\n");
		a = Check();
		if (a == "0")
			break;
		printf(" \"*\"\n");
		b = Check();
		if (b == "0")
			break;
		answer=ToMult(a, b);
		if (answer == "overflow") {
			std::cout << "\nОтвет: " << answer << "\n";
		}
		else if (b[0] == '-')
			std::cout << "\nОтвет: " << a << " * (" << b << ") = " << answer << "\n\n";
		else
			std::cout << "\nОтвет: " << a << " * " << b << " = " << answer << "\n\n";
	}
}

void Ar::DivCalculator() {
	vector<string> answer;
	printf("\n --------------------------------------");
	printf("\n Вы перешли в калькулятор Деления.");
	printf("\n Для выхода в главное меню введите [0].\n\n");
	while (true) {
		printf("Что вы хотите поделить?\n");
		a = Check();
		if (a == "0")
			break;
		printf(" \"/\"\n");
		b = Check();
		if (b == "0")
			break;
		answer=ToDiv(a, b, answer);
		if (answer[2] == "0") {
			if (b[0] == '-')
				std::cout << "\nОтвет: " << a << " / (" << b << ") = " << answer[0] << "\n";
			else
				std::cout << "\nОтвет: " << a << " / " << b << " = " << answer[0] << "\n";
			std::cout << "       остаток = " << answer[1] << "\n\n";
			std::cout << "Проверка остатка:\n";

			std::cout<< a << " - ";

			if (b[0] == '-')
				std::cout << "(";
			std::cout << b;
			if (b[0] == '-')
				std::cout << ")";
			
			std::cout << " * ";

			if (answer[0][0] == '-')
				std::cout << "(";
			std::cout << answer[0];
			if (answer[0][0] == '-')
				std::cout << ")";

			std::cout<<" = "<< a << " - ";

			if (ToMult(b,answer[0])[0] == '-')
				std::cout << "(";
			std::cout << ToMult(b, answer[0]);
			if (ToMult(b,answer[0])[0] == '-')
				std::cout << ")";

			std::cout<<" = "<< ToSumm_or_ToSub(a,ToMult(b,answer[0]),0)<<"\n\n";

			
		}
		else if (answer[2] == "1") {
			std::cout << "\nОтвет: [-cccccccc; cccccccc]"  << "\n\n";
		}
		else {
			std::cout << "\nОтвет: пустое множество" << "\n\n";
		}
	answer.clear();
	}
}

void Ar::Menu() {
	cout << "\n\tДобро пожаловать в калькулятор \"большой\" конечной арифметики\n";
	while (true) {
		bool out = 0;
		printf("\n\nВот что вы можете сделать:");
		printf("\n Вывести ... ");
		printf("\n [1] Правило \"+1\"");
		printf("\n [2] Таблицу сложения \"+\"");
		printf("\n [3] Таблицу умножения \"*\"");
		printf("\n [4] Отношение порядка");
		printf("\n Перейти в... ");
		printf("\n [5] Калькулятор сложения\"+\"");
		printf("\n [6] Калькулятор вычитания\"-\"");
		printf("\n [7] Калькулятор умножения\"*\"");
		printf("\n [8] Калькулятор деления\"/\"");
		printf("\n Выйти из... ");
		printf("\n [0] Программы\n\n");

		while (true) {
			cin >> buf;
			try {
				if (stoi(buf) >= 0 && stoi(buf) <= 8) {
					break;
				}
				else {
					std::cout << "Ошибка ввода! Ведите число от 0 до 8\n";
				}
			}
			catch (const std::invalid_argument& e) {
				std::cout << "Ошибка ввода! Неверный формат числа\n";
			}
			
		}
		int n = stoi(buf);

		switch (n) {
		case 0:
			out = 1;
			break;

		case 1:
			PrintPlusOneChar();
			break;

		case 2:
			PrintOperator(OperatorPlusChar);
			PrintOperator(OperatorPlusChar_Shift);
			break;

		case 3:
			PrintOperator(OperatorMultChar);
			PrintOperator(OperatorMultChar_Shift);
			break;
		case 4:
			PringGraph();
			break;

		case 5:
			SummCalculator();
			break;

		case 6:
			SubCalculator();
			break;
			
		case 7:
			MultCalculator();
			break;
			
		case 8:
			DivCalculator();
			break;



		}
			if (out)
				break;
			system("pause");
	}
}

