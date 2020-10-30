#pragma once
#include <string>

using std::string;

class Locatar {
private:
	int apart;
	string nume;
	double suprafata;
	string tip;	//tipul apartamentului
public:
	//constructor
	Locatar()=default;
	Locatar(int apart, string nume, double suprafata, string tip) : apart{ apart }, nume{ nume }, suprafata{ suprafata }, tip{ tip } {};
	//getters
	int get_apart() const;
	string get_nume() const;
	double get_suprafata() const;
	string get_tip() const;

	//setters 
	void set_nume(const string& nume_nou);
	void set_suprafata(const double& suprafata_noua);
	void set_tip(const string& tip_nou);
};

void test_domeniu();