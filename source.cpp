/*
 * 	Tradutor para o 4º Trabalho de SL
 *	Escrito por Mardoqueu Arruda Pimentel
 *	Contato: map@icomp.ufam.edu.br
 *	Ver: 0.5 alpha
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <unordered_map>
#define K_DELAY 1500
#define ARD_DEFINE "#define palavra(b13, b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1)\\\ndigitalWrite(13, b13);\\\ndigitalWrite(12, b12);\\\ndigitalWrite(11, b11);\\\ndigitalWrite(10, b10);\\\ndigitalWrite(9, b9);\\\ndigitalWrite(8, b8);\\\ndigitalWrite(7, b7);\\\ndigitalWrite(6, b6);\\\ndigitalWrite(5, b5);\\\ndigitalWrite(4, b4);\\\ndigitalWrite(3, b3);\\\ndigitalWrite(2, b2);\\\ndigitalWrite(A5, b1)\n"
#define ARD_VOID "\nvoid setup()\n{\n"
#define ARD_INIT "\tSerial.begin(9600);\n\tpinMode(A5, OUTPUT), digitalWrite(A5, 0); pinMode(A0, INPUT);\n\tfor(int i = 2; i <= 13; ++i) pinMode(i, OUTPUT), digitalWrite(i, 0);\n\n"

using namespace std;

ifstream entrada; ofstream saida;

inline void split(string str, const char* t, vector<string>& l)
{
	char *tk = strtok(&str[0], t);
	
	while(tk)
	{
		string aux(tk);
		l.push_back(aux);
		tk = strtok(NULL, t);
	}
}

inline void print_k(char x)
{
	for(int i = 3; i >= 0; --i)
		saida << ',' << ((x >> i) & 0x1);
}

inline void reg_end(string& x){
	if(x == "R0") saida << ",0,0";
	if(x == "R1") saida << ",0,1";
	if(x == "R2") saida << ",1,0";
	if(x == "R3") saida << ",1,1";
}
inline void reg_end(string& x, string& y, string& z){ reg_end(x); reg_end(y); reg_end(z); }

int main(int argc, char const *argv[]){
	if(argc == 1)
	{
		cout << "Erro. Especifique o arquivo de texto.\n";
		exit(1);
	}else
	{
		entrada.open(argv[1]); saida.open("./codigo/codigo.ino");
		
		if(entrada.is_open()) cout << "Lendo o arquivo de entrada...\n";
		else
		{
			cout << "Erro ao ler o arquivo de entrada.\n";
			exit(1);
		}

		if(saida.is_open()) cout << "Lendo o arquivo de saida...\n";
		else
		{	
			cout << "Pasta codigo inexistente\n";
			cout << "Criando pasta codigo...\n";
			if(system("mkdir -p ./codigo") == -1)
			{
				cout << "Erro ao criar diretório\n";
				exit(1);
			}

			cout << "Criando o arquivo de saida...\n";
			saida.open("./codigo/codigo.ino");
			
			if(!saida.is_open()){
				cout << "Erro ao criar arquivo";
				return 0;
			}
		}
	}

	saida << ARD_DEFINE << ARD_VOID << ARD_INIT;

	int n = 0;	
	string comando;

	unordered_map <string, int> com;
	com["ldi"] = 1; com["add"] = 2; com["sub"] = 3; com["and"] = 4; com["or"] = 5;
	com["not"] = 6; com["xor"] = 7;

	while(getline(entrada, comando)){
		if(comando.size() == 0) break;
		++n;
		vector<string> tks;
		split(comando, " ", tks);
		
		saida << "\tpalavra(";

		switch(com[tks[0]])
		{
			case 1: // ldi
				saida << "0,0,0,0,0,0";		//	OpULA : Don't Care
				saida << ",1";				//	MemToReg : Arduino
			
				reg_end(tks[1]);		// WriteReg

				print_k(stoi(tks[2])); // Imediato

				break;
			case 2: // add
				saida << "0,"; 				//	OpULA : M
				saida << "1,"; 				//	OpULA : Cn (lógica inversa)
				saida << "1,0,0,1"; 		//	OpULA : A plus B
				saida << ",0"; 				//	MemToReg : Ula
				
				reg_end(tks[1], tks[2], tks[3]); // Ender de Dest, A, B

				break;
			case 3: // sub
				saida << "0,";				//	OpULA : M
				saida << "0,";				//	OpULA : Cn (lógica inversa)
				saida << "0,1,1,0";			//	OpULA : A minus B
				saida << ",0";				//	MemToReg : Ula

				reg_end(tks[1], tks[2], tks[3]); // Ender de Dest, A, B

				break;
			case 4: // and
				saida << "0,";				//	OpULA : M
				saida << "0,";				//	OpULA : Cn (lógica inversa)
				saida << "1,0,1,1";			//	OpULA : A and B
				saida << ",0";				//	MemToReg : Ula

				reg_end(tks[1], tks[2], tks[3]); // Ender de Dest, A, B

				break;
			case 5: // or
				saida << "0,";				//	OpULA : M
				saida << "1,";				//	OpULA : Cn (lógica inversa)
				saida << "0,0,0,1";			//	OpULA : A or B
				saida << ",0";				//	MemToReg : Ula

				reg_end(tks[1], tks[2], tks[3]); // Ender de Dest, A, B

				break;
			case 6: // not
				saida << "1,";				//	OpULA : M
				saida << "0,";				//	OpULA : Cn (lógica inversa)
				saida << "0,0,0,0";			//	OpULA : not A
				saida << ",0";				//	MemToReg

				reg_end(tks[1], tks[1], tks[2]); // Ender de Dest, A, B

				break;
			case 7: // xor
				saida << "1,";				//	OpULA : M
				saida << "0,";				//	OpULA : Cn (lógica inversa)
				saida << "0,1,1,0";			//	OpULA : A xor B
				saida << ",0";				//	MemToReg

				reg_end(tks[1], tks[2], tks[3]); // Ender de Dest, A, B

				break;
		}
		
		saida << ");\n\twhile(digitalRead(A0) == 1){ Serial.print(\"Instrução " << n << " \\n\"); }\n\tdelay(" << K_DELAY << ");\n\n";
	}
	
	saida << "\tSerial.print(\"Fim\");\n}\nvoid loop(){}\n";

	entrada.close(); saida.close();

	if(!saida.is_open()) cout << "Tradução concluida.\n";
	else cout << "Erro desconhecido ao tentar salvar o arquivo de saida.\n";

	return 0;
}
