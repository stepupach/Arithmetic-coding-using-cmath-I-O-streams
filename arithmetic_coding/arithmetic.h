#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cmath>
#define _low_edge 0
#define _high_edge 65535
#define EOF_symbol '-'
#define symbol_break '\0'
using namespace std;

class arithmetic
{
	private:
		const int first_qtr = _high_edge / 4 + 1;
		const int half = 2 * first_qtr;
		const int third_qtr = 3 * first_qtr;
		// объекты для работы с текстом
		string text;
		string abc;
		string encode;
		string decode;
		int *freq; // массив частот
	public:
		void show_table(); // таблица частот и символов
		string get_encode(); // вернуть закодированную строку
		string get_decode(); // вернуть раскодированную строку
		string get_text(); // вернуть исходный текст
		void get_file(string filename); // текст из файла в string
		void input_string(string input); // текст из входной input строки в string
		void input_keyboard(); // текст с клавиатуры 
		void get_abc(); // алфавит 
		void get_frequency(); // массив частот
		void get_next_symbol(int i, int *current); // получение индекса следующего символа
		string write_bits(bool bit, int bits_to_foll); // запись битов
		void output_file(string filename); // вывести полученного текста в файл
		void encode_text(); // кодирование
		int to_int(int _pos); // перевод 16 бит строки в int
		string to_bits_16(int _value); // перевод int в биты
		int add_bit(int value, int count_taken, bool &flag); // добавление бита к int числу
		void decode_text(); // декодирование 
		void encode_file(string, string); // вывести закодированную строку в файл
};


