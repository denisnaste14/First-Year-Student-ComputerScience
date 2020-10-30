#include "UI.h"
#include <iostream>



void all_tests();

int main() {
	{
		all_tests();
		Repo repo;
		Service srv{ repo };
		UI ui{ srv };
		ui.run();
	}
	
	return 0;
}


void all_tests() {
	test_domeniu();
	test_add_repo();
	test_validare();
	test_add_srv();
	test_sterge_repo();
	test_sterge_srv();
	test_modificare_repo();
	test_modifica_srv();
	test_caut_locatar();
	test_cauta_srv();
	test_filtrare_dupa_suprafata();
	test_filtrare_dupa_tip();
	test_sortare_dupa_nume();
	test_sortare_dupa_suprafata();
	test_sortare_dupa_tip_si_suprafata();
	range_for_test();
	test_vector_dinamic_iterator();
}