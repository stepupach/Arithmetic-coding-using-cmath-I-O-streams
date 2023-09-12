﻿#include "Arithmetic.h"
using namespace std;

void arithmetic::input_keyboard()
{
	cin >> text;
	text.push_back(symbol_break);
}

void arithmetic::show_table()
{
	cout << endl << text << endl;
	cout << abc << endl;
	for (int i = 0; i < abc.size(); i++) cout << abc[i] << " - " << freq[i] << endl;
}

string arithmetic::get_text()
{
	return text;
}

string arithmetic::get_decode()
{
	return decode;
}

string arithmetic::get_encode()
{
	return encode;
}

void arithmetic::input_string(string input)
{
	text = input;
	text.push_back(symbol_break);
}

void arithmetic::get_file(string filename)
{
	fstream input;
	input.open(filename, ios::in);
	while (!input.eof())
	{
		string temp;
		getline(input, temp);
		if (!input.eof()) temp += '\n';
		text += temp;
	}
	text.push_back(symbol_break);
	input.close();
}

void arithmetic::get_abc()
{
	// добавить символ - в начало
	bool exit_flag = 0;
	abc.push_back(EOF_symbol);
	for (int i = 0; i < text.size(); i++)
	{
		exit_flag = 0;
		for (int j = 0; j < abc.size(); j++)
		{
			if (abc[j] == text[i])						//если в нашем алфавите уже есть такая буква
			{
				exit_flag = 1;							//выходим, если нашли такую букву
				break;
			}
		}
		if (exit_flag == 1)								//если находили букву ранее
		{
			continue;									//переход на следующую итерацию для след. буквы
		}
		else											//если буква найдена не была
		{
			abc.push_back(text[i]);
			continue;
		}
	}
}

void arithmetic::get_frequency()
{
	freq = new int[abc.size()];
	for (int i = 0; i < abc.size(); i++) freq[i] = 0;
	for (int j = 0; j < abc.size(); j++)
	{
		for (int i = 0; i < text.size(); i++)
		{
			if (abc[j] == text[i])	freq[j]++;
		}
		if (j > 0) freq[j] += freq[j - 1];
	}
}

void arithmetic::get_next_symbol(int i, int *current)
{
	// индекс символа из текста в алфавите
	bool exit = false;
	for (i; i < text.size() && !exit; i++)
	{
		char temp_text = text[i];
		for (int j = 0; j < abc.size(); j++)
		{
			char temp_abc = abc[j];
			if (temp_text == temp_abc)
			{
				*current = j;
				exit = true;
				break;
			}
		}
	}
}

string arithmetic::write_bits(bool bit, int bits_to_foll)
{
	string temp;
	temp += to_string(bit);
	while (bits_to_foll > 0)
	{
		temp += to_string(!bit);
		bits_to_foll -= 1;
	}
	return temp;
}

void arithmetic::output_file(string filename)
{
	fstream file;
	file.open(filename, ios::out);
	for (int i = 0; i < text.size() - 1; i++)
	{
		file << text[i];
	}
	file.close();
}

void arithmetic::encode_file(string filename, string data)
{
	fstream file;
	file.open(filename, ios::out);
	for (int i = 0; i < data.size() - 1; i++) 
	{
		file << data[i];
	}
	file.close();
}

void arithmetic::encode_text()
{
	int mass_size = text.length();
	unsigned short int *_low = new unsigned short int[mass_size];
	unsigned short int *_high = new unsigned short int[mass_size];
	_low[0] = _low_edge;
	_high[0] = _high_edge;
	int current = 1;	// какой элемент берём
	int i = 0;			// где находимся 
	unsigned int range = 0;
	int del = freq[abc.size() - 1]; //последняя накопленная частота
	int bits_to_foll = 0;
	string code = "";
	int r;
	while (i < text.length())
	{
		get_next_symbol(i, &current);
		i += 1;
		range = _high[i - 1] - _low[i - 1] + 1;
		_low[i] = _low[i - 1] + (range*freq[current - 1]) / del;
		_high[i] = _low[i - 1] + (range*freq[current]) / del - 1;
		for (;;)
		{
			if (_high[i] < half)
			{
				code += write_bits(0, bits_to_foll);
				bits_to_foll = 0;
			}
			else if (_low[i] >= half)
			{
				code += write_bits(1, bits_to_foll);
				bits_to_foll = 0;
				_low[i] -= half;
				_high[i] -= half;
			}
			else if (_low[i] >= first_qtr && _high[i] < third_qtr)
			{
				bits_to_foll += 1;
				_low[i] -= first_qtr;
				_high[i] -= first_qtr;
			}
			else break;
			_low[i] = 2 * _low[i];
			_high[i] = 2 * _high[i] + 1;
		}
	}
	encode = code;
	r = range;
}

int arithmetic::to_int(int _pos)
{
	int n = 0;
	for (int i = _pos; i < sizeof(short) * 8 + _pos; i++)
	{
		n <<= 1;
		n |= encode[i] - '0';
	}
	return n;
}

string arithmetic::to_bits_16(int _value)
{
	bitset<16> a(_value); 
	string mystring = a.to_string<char, char_traits<char>, allocator<char> >();
	return mystring;
}

int arithmetic::add_bit(int value, int count_taken, bool & flag)
{
	bitset<16> a(value); // создаем битсет объекты
	if (flag == 1) // проверяем первый бит в буффере
	{
		a.reset(0);
	}
	else if (count_taken >= encode.length())
	{
		a.set(0);
		flag = 1;
	}
	else if (encode[count_taken] == '1')
	{
		a.set(0);
	}
	else if (encode[count_taken] == '0')
	{
		a.reset(0);
	}
	value = (unsigned short int)(a.to_ulong());
	return value;
}

void arithmetic::decode_text()
{
	string decode_text = "";
	int mass_size = text.length();
	unsigned short int *_low = new unsigned short int[mass_size];
	unsigned short int *_high = new unsigned short int[mass_size];
	_low[0] = _low_edge;
	_high[0] = _high_edge;

	unsigned int range = 0;
	unsigned int cum = 0;
	int del = freq[abc.size() - 1];

	unsigned short int value = to_int(0);		// забираем 16 бит в value
	int count_taken = 16;

	bool flag = 0;

	for (int i = 1;; i++)
	{
		range = (_high[i - 1] - _low[i - 1]) + 1;
		cum = (((value - _low[i - 1]) + 1) * del - 1) / range;

		int symbol;
		for (symbol = 1; freq[symbol] <= cum; symbol++); // другой знак

		_low[i] = _low[i - 1] + (range * freq[symbol - 1]) / del;
		_high[i] = _low[i - 1] + (range * freq[symbol]) / del - 1;

		decode_text += abc[symbol];

		if (abc[symbol] == symbol_break)
		{
			decode = decode_text;
			return;
		}

		for (;;)
		{
			if (_high[i] >= half)
			{
				if (_low[i] >= half)
				{
					value -= half;
					_low[i] -= half;
					_high[i] -= half;
				}
				else if (_low[i] >= first_qtr && _high[i] < third_qtr)
				{
					value -= first_qtr;
					_low[i] -= first_qtr;
					_high[i] -= first_qtr;
				}
				else
				{
					break;
				}
			}

			_low[i] = 2 * _low[i];
			_high[i] = 2 * _high[i] + 1;
			value = add_bit(2 * value, count_taken, flag);
			count_taken++;
		}
	}
}