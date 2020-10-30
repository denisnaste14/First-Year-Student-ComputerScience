#pragma once
#include "Repo.h"

class UndoException {
private:
	string mesaj;
public:
	UndoException(string mesaj) : mesaj{ mesaj } {
	};
	string get_mesaj() noexcept {
		return mesaj;
	}
};

class ActiuneUndo {
	//clasa pur virtuala, o folosesc doar ca sablon pentru clasele specializate pe diferite actiuni de undo 
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Locatar locatar_adaugat;
	Repo& repo;
public:
	UndoAdauga(const Locatar& locatar_adaugat, Repo& repo) : locatar_adaugat{ locatar_adaugat }, repo{ repo }{
	};
	void doUndo() override {
		repo.sterge_locatar(locatar_adaugat.get_apart());
	}
};

class UndoSterge : public ActiuneUndo {
	Locatar locatar_sters;
	Repo& repo;
public:
	UndoSterge(const Locatar& locatar_sters, Repo& repo) : locatar_sters{ locatar_sters }, repo{ repo }{
	};
	void doUndo() override {
		repo.add_locatar(locatar_sters);
	}
};

class UndoModifica : public ActiuneUndo {
	Locatar ultimul_locatar;
	Locatar locatar_modificat;
	Repo& repo;
public:
	UndoModifica(const Locatar& ultimul_locatar, const Locatar& locatar_modificat, Repo& repo) : ultimul_locatar{ ultimul_locatar }, locatar_modificat{ locatar_modificat }, repo{ repo }{
	};
	void doUndo() override {
		repo.sterge_locatar(ultimul_locatar.get_apart());
		repo.add_locatar(locatar_modificat);
	}
};