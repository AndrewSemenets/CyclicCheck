#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>


using namespace std;
//vector<bool> polynomial = { 1, 1, 0, 0, 1};
vector<bool> polynomial = {1, 0, 0, 0, 1, 1, 1, 0, 1};  //Порождающий полином  x^8 + x^4 + x^3 + x^2 + 1
#define R 8											    //степень порождающего полинома

vector<bool> vect_bits;

void encode(char* bits);
void decode(char* bits);
vector<bool> get_remainder(vector<bool> a);


int main(int argc, char *argv[])
{
	if (argc < 3) printf("\n Bad arguments \nTry: CyclicCheck e or d (bits)\n");
	if (argv[1][0] == 'e') encode(argv[2]);
	else if (argv[1][0] == 'd') decode(argv[2]);
	else throw "Invalid first argument";

	cout << endl;
	system("pause");
	return 0;
}

void encode(char * bits)
{
	//-------------------------------------------------формируем вектор входных данных
	for (int i = 0; i < strlen(bits); i++)
	{
		if (bits[i] == '0') vect_bits.push_back(0);
		else if (bits[i] == '1') vect_bits.push_back(1);
		else throw "Invalid bits string";
	}
	
	vector<bool> remainder = get_remainder(vect_bits);//находим остаток от деления входных данных на порождающий полином
	for (int i = 0; i < R - remainder.size(); i++) vect_bits.push_back(0);//добавляем к входным данным чексумму
	vect_bits.insert(vect_bits.end(), remainder.begin(), remainder.end());
	
	cout << "Encoded:";
	for (bool bit : vect_bits)
	{
		cout << bit;
	}
	cout << endl;
}

void decode(char * bits)
{
	//-------------------------------------------------формируем вектор входных данных
	for (int i = 0; i < strlen(bits); i++)
	{
		if (bits[i] == '0') vect_bits.push_back(0);
		else if (bits[i] == '1') vect_bits.push_back(1);
		else throw "Invalid bits string";
	}

	cout << "Input message:";
	for (int i = 0; i < vect_bits.size() - R; i++) cout << vect_bits[i];
	cout << endl;

	bool bool_check = false;
	cout << "Remainder:";
	vector<bool> check = get_remainder(vect_bits);//находим остаток от деления сообщения на порождающий полином
	for (bool bit : check)
	{
		cout << bit;
		bool_check += bit;						  //проверяем, 0 ли он
	}
	cout << endl;

	if (bool_check) cout << "The message contains an error";
	else cout << "The message contains no errors";
}

vector<bool> get_remainder(vector<bool> a)
{
	vector<bool> remainder, dividend = a;
	
	for (int i = 0; i < R; i++)	dividend.push_back(0); //добавляем к делимому многочлену R нулей справа

	do
	{																						  //пока степень остатка не станет меньше степени порождающего полинома
		for (int i = 0; i < R + 1; i++)	remainder.push_back(dividend[i] ^ polynomial[i]);     //r+1 старших разрядов информационного полинома складываются по модулю 2 с порождающим полиномом
		while (remainder[0] == 0 && remainder.size() != 1) remainder.erase(remainder.begin());//убираем нули вначале текущего отстатка
		remainder.insert(remainder.end(), dividend.begin() + R + 1, dividend.end());	      //добавляем к текущему остатку конец входного многочлена
		dividend = remainder;
		remainder.erase(remainder.begin(), remainder.end());
	} while (dividend.size() >= polynomial.size());
	remainder = dividend;
	
	return remainder;
}