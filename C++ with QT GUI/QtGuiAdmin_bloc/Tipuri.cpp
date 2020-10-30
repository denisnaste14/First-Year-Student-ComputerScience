#include "Tipuri.h"

void Tipuri::cate_dinFiecare() {
	tip_nr.insert(std::make_pair<std::string, int>("circular", 0));
	tip_nr.insert(std::make_pair<std::string, int>("decomandat", 0));
	tip_nr.insert(std::make_pair<std::string, int>("semidecomandat", 0));
	tip_nr.insert(std::make_pair<std::string, int>("nedecomandat", 0));
	tip_nr.insert(std::make_pair<std::string, int>("open-space", 0));

	for (auto loc : srv.toti_din_cos()) {
		tip_nr.find(loc.get_tip())->second++;
	}
	notify();
}

vector<int> Tipuri::get_valori() {
	vector<int> valori;
	valori.push_back(tip_nr.find("circular")->second);
	valori.push_back(tip_nr.find("decomandat")->second);
	valori.push_back(tip_nr.find("semidecomandat")->second);
	valori.push_back(tip_nr.find("nedecomandat")->second);
	valori.push_back(tip_nr.find("open-space")->second);

	notify();
	return valori;
}