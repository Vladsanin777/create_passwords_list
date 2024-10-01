#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <thread>
#include <sstream>
#include <cmath>

using namespace std;

int long long parallelism_step = 100;

static char symbols[91] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+{}[]:;\"'<>,.?/";

void symbol_enumeration_thread(int long long number, int long long parallelism_step){
	for(int long long number_i = number; number_i<parallelism_step; ++number_i) {
		stringstream password;
		int long long number_remainder = 0;
		while (number_remainder<number_i) {
			number_remainder = number_i % 91;
			number_i -= number_remainder;
			number_i /= 91;
			password<<symbols[number_remainder];
		}
		cout<<(password).str()<<endl;
	}
	return;
}

int main(){
	int long long min_count_symbols, max_count_symbols;
	cout<<"Input min count symbols for generated password: ";
	cin>>min_count_symbols;
	cout<<"Input max count symbols for generated password: ";
	cin>>max_count_symbols;
	cout<<"Input parallelism step (defaut = 100): ";
	cin>>parallelism_step;
	cout<<"Input name list: ";
	string file_name;
	cin>>file_name;
	system(("touch "+file_name).c_str());
	ofstream outFile(file_name);
	int long long min_number, number = 0;
	min_number = pow(91, min_count_symbols-1);
	for(min_count_symbols; max_count_symbols < min_count_symbols; ++min_count_symbols) number += pow(80, min_count_symbols);
	for(min_number; number<min_number;){
		thread t(symbol_enumeration_thread, min_number, min_number+parallelism_step);
		t.detach();
		min_number += parallelism_step;
	}
	return 0;
}
