#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string jednosci[] = {"" ,"jeden", "dwa", "trzy", "cztery", "pięć", "sześć", "siedem", "osiem", "dziewięć"};
string nascie[] = {"dziesięć","jedenaście", "dwanaście", "trzynaście", "czternaście", "piętnaście", "szesnaście", "siedemnaście", "osiemnaście", "dziewiętnaście", "dwadzieścia"};
string dziesiatki[] = {"", "dziesięć", "dzieścia", "dzieści", "dzieści", "dziesiąt", "dziesiąt", "dziesiąt", "dziesiąt", "dziesiąt"};
string setki[] = {"", "sto", "dwieście", "sta", "sta", "set", "set", "set", "set", "set"};
string tysiace[] = {"tysięcy", "tysięcy", "tysiące", "tysiące", "tysiące", "tysięcy", "tysięcy", "tysięcy", "tysięcy", "tysięcy"};

void NumToText(int n) {
	int n2 = n;
	int *digits = new int [7];
	int length = 0;
	for(int i = 0; i < 7; i++) digits[i] = 0; //zerowanie tablicy cyfr
	for(int i = 6; n != 0; n/=10) { //wczytywanie cyfr do tablicy
		digits[i] = n%10;
		length++;
		i--;
	}	
	for(int i = 7 - length; i < 7; i++) {
		switch(i) {
			case 0:
				cout << "milion";
				break;
			case 1: // setki tysięcy
				if(digits[i] == 1) cout << setki[1] << " ";
				else if(digits[i] == 2) cout << setki[2] << " ";
				else cout << jednosci[digits[i]] + setki[digits[i]] << " ";
				break;
			case 2: //dziesiątki i jedności tysięcy
				if(digits[i] == 0) { //x0xxxx
					if(digits[i+1]) 
						cout << jednosci[digits[i+1]] << " ";
					if(n2 != 1000000) cout << tysiace[digits[i+1]] << " ";				
				}
				else if(digits[i] == 1) { //x1xxxx										
					cout << nascie[digits[i+1]] << " tysięcy ";					
				}
				else { //x2-9xxxx					
					cout << jednosci[digits[i]] + dziesiatki[digits[i]] << " "; 
					if(digits[i+1])
						cout << jednosci[digits[i+1]] << " " << tysiace[digits[i+1]] << " "; 					
				}
				i+=1;
				break;
			case 3: // tysiące
				if(digits[i] == 1) cout << "tysiąc ";
				else cout << jednosci[digits[i]] << " " << tysiace[digits[i]] << " ";
				break;
			case 4: //setki
				if(digits[i] == 0);
				else if(digits[i] == 1) cout << setki[1] << " ";
				else if(digits[i] == 2) cout << setki[2] << " ";
				else cout << jednosci[digits[i]] + setki[digits[i]] << " ";
				break;
			case 5: //dziesiątki i jedności
				if(digits[i] == 0);
				else if(digits[i] == 1) {										
					cout << nascie[digits[i+1]] << " "; 
					i+=2;
				}
				else {					
					cout << jednosci[digits[i]] + dziesiatki[digits[i]] << " "; 
					if(digits[i+1])
						cout << jednosci[digits[i+1]] << " "; 
					i+=2;
				}
				break;
			case 6: //jedności
				if(digits[i] != 0)
					cout << jednosci[digits[i]] << " ";
				break;
		}
	}
	cout << endl;
	delete [] digits;
}
void findk(int number) {
	int number2 = number;
	int length = 0;
	unsigned long long k = 2;
	bool check = 1;
	int wynik = 0;
	int *digits = new int [7];

	while(check) {
		for(int i = 6; number != 0; number/=10) { //wczytywanie cyfr do tablicy
			digits[i] = number%10;
			length++;
			i--;
		}
		check = 0;
		for(int j = 7-length; j < 7; j++) { //sprawdzanie cyfr
			if(digits[j] != 0 && digits[j] != 1) {
				check = 1;
				number = number2 * k;
				k++;
				length = 0;
			}
		}
		if(number > 1000000) break;
	}
	int j = 1;
	if(!check) {
		for(int i = 7-length; i < 7; i++) { //tworzenie wyniku
			wynik += (digits[i] * pow(10, length - j));
			j++;
		}
		NumToText(wynik);
	}
	else cout << "Liczba wyszla poza zakres" << endl;
	delete [] digits;
}

int main(int argc, char *argv[])
{
	int number = atoi(argv[1]);	
	if(number > 1000000 || number < 0) {
		cout << "Proszę podać liczbę z zakresu 0 - 1000000: ";
		cin >> number;
	}
	findk(number);
}