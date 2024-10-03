#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <thread>
#include <sstream>
#include <cmath>

using namespace std;

static ofstream outFile;

static int long long parallelism_step = 100;

static string symbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+{}[]:;\"'<>,.?/";

static int long long size_symbols = symbols.length();

static void generateCombinations(string current, int long long length) {
    if (current.size() == length) {
        outFile << current << endl;
        return;
    }
    
    for (char ch : symbols){
		thread t(generateCombinations, current + ch, length);
		t.detach();
	}
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
	outFile.open(file_name);
	outFile.is_open();
    for (min_count_symbols; max_count_symbols>min_count_symbols ; ++min_count_symbols) {
        thread t(generateCombinations, "", min_count_symbols);
		t.detach();
    }
	return 0;
}
