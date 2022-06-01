#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

char* findLCSubStr(const char* X, const char* Y, int m, int n) {
	int** LCSuff = new int* [m + 1];

	for (int i = 0; i < m + 1; i++) {
		LCSuff[i] = new int[n + 1];

		for (int j = 0; j < n + 1; j++)
			LCSuff[i][j] = 0;
	}

	int len = 0;
	int row, col;

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				LCSuff[i][j] = 0;

			else if (X[i - 1] == Y[j - 1]) {
				LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
				if (len < LCSuff[i][j]) {
					len = LCSuff[i][j];
					row = i;
					col = j;
				}
			}
			else
				LCSuff[i][j] = 0;
		}
	}

	if (len == 0) {
		return 0;
	}

	char* resultStr = (char*)malloc((len + 1) * sizeof(char));

	for (int i = 0; i < len + 1; i++)
		resultStr[i] = 0;

	while (LCSuff[row][col] != 0) {
		resultStr[--len] = X[row - 1]; 

		row--;
		col--;
	}

	return resultStr;
}

// функция замены подстроки на символы.
// второй аргумент передаём по константной ссылке
// это для того, чтобы substr не копировалось каждый раз в функцию
void replace_substr(string& str, const string& substr, char sym) {
	size_t pos = str.find(substr);

	for(int i = pos; i < pos + substr.length(); i++)
		str[i] = sym;
}


// argv[1] - X
// argv[2] - Y
// argv[3] - output
int main(int argc, char** argv) {
	string X; /*"AGCTGGATC"*/;
	string Y; /*"GATCAGGCT"*/;
	string Z = "";
	string M = "";

    ifstream file1(argv[1]);
    ifstream file2(argv[2]);
    file1 >> X;
    file2 >> Y;
    file1.close();
    file2.close();

	// M с пробелами
	string M_nice = "";
	
	string X_original = X;
	string Y_original = Y;

	unsigned int m = X.length();
	unsigned int n = Y.length();

	unsigned int summary_size = 0;
	unsigned int parts_count = 0;

	string tmp_part = "";

	// тут храним результат поиска
	// если он nullptr - больше подстрок нет
	char* tmp_part_c_str = nullptr;

	while (summary_size != X.length()) {

		// удаляем каждый раз прошлый поиск
		// чтоб память не занимать
		if(tmp_part_c_str != nullptr)
			delete[] tmp_part_c_str;

		tmp_part_c_str = findLCSubStr(X.c_str(), Y.c_str(), m, n);

		// если подстрок больше нет, а размер не совпадает,
		// значит, что-то пошло не так
		// а если совпадает, выходим, ибо всё готово
		if(tmp_part_c_str == nullptr) {
			/*if(summary_size != X.length()) {
				cout << "No common sequences" << endl;
				exit(0);
			} else {
				break;
			}*/

			break;
		}

		tmp_part = string(tmp_part_c_str);
		parts_count++;

		M += tmp_part;
		M_nice += tmp_part + " ";

		summary_size += tmp_part.length();

		// заменяем подстроку в X на .
		// в Y на *
		replace_substr(X, tmp_part, '.');
		replace_substr(Y, tmp_part, '*');
	}

	//cout << "X: " << X_original << endl;
	//cout << "Y: " << Y_original << endl;
	//cout << "M: " << M_nice << endl;

	//cout << M_nice << endl;
	//cout <<  M.length() / X_original.length() * 100 << "%" << endl;

    ofstream fileo(argv[3]);

    fileo << M_nice << endl;

	fileo.close();

	return 0;
}
