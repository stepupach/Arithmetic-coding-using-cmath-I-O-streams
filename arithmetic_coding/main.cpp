#include "arithmetic.h"
#define file_input "input.txt"
#define file_output "output.txt"
#define file_encode "encode.txt"
#define symbol_break '\0'
using namespace std;

void logo()
{
	cout << "   " << endl;
	cout << "          Arithmetic coding " << endl;
	cout << "   " << endl;
	cout << " ***       ***         ***       ***" << endl;
	cout << "* * *     * * *         /\\       /\\" << endl;
	cout << " ***       ***" << endl;
	cout << "     *   *                 *   *   " << endl;
	cout << "      ***                   *** " << endl;
	cout << "   " << endl;
}

int main()
{
		system("color b0");
		logo();
		arithmetic coding;
		cout << "Input text: " << endl;
		cout << "---> 1. From file" << endl;
		cout << "----> 2. From keyboard" << endl;
		cout << "-----> 3. Exit " << endl;
		cout << "\nChoose, please (1 or 2 or 3): ";
		int choose;
		cin >> choose;
		cout << endl;

		if (choose == 3)
		{
			cout << "Goodbye!" << endl;
			exit(1);
		}
		else if (choose == 2)
		{
			cout << "Write text to encode: ";
			coding.input_keyboard();
		}
		else if (choose == 1)
		{
			cout << "Write file's name to open (0 - def): ";
			string filename_in;
			cin >> filename_in;
			if (filename_in.at(0) == '0')
			{
				filename_in = file_input;
			}
			coding.get_file(filename_in);
		}
		else
		{
			cout << "Ooops...Error!" << endl;
			exit(1);
		}

		coding.get_abc();
		coding.get_frequency();
		coding.encode_text();
		coding.show_table();
		string encode = coding.get_encode();
		int k = coding.get_text().length()/1.3;
		coding.encode_file(file_encode, coding.get_encode().substr(0, k));
		cout << "\n***RESULTS***" << endl;
		cout << "encode str: " << endl << coding.get_encode().substr(0,k) << endl;
		coding.show_table();
		coding.decode_text();
		coding.output_file(file_output);
		cout << "\ndecode str: " << endl << coding.get_decode() << endl;
		if (coding.get_text() == coding.get_decode()) cout << "\nYAAAY! input text = decode text" << endl;
		else cout << "\nOH NO...input text != decode text" << endl;
	return 0;
}