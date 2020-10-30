#pragma once
#include "Locatar.h"
#include <string>
using std::string;

class ValidError {
private:
	string mesaj;
public:
	ValidError(const string& mesaj) : mesaj{ mesaj } {
	}
	string get_mesaj() const;
};

class Validator {
private:
	Locatar loc;
public:
	//Constructor
	Validator(const Locatar& loc) :loc{ loc } {
	}
	void valid();
};

//teste
void test_validare();