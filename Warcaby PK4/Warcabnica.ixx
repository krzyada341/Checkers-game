export module Warcabnica;
import pola;
import <iostream>;
import <vector>;
import <memory>;
import <cctype>;
import <cmath>;
import <algorithm>;
import <fstream>;
import <filesystem>;
import <string>;

export class Warcabnica {
	std::vector<std::vector<std::shared_ptr<pole>>> poleGry;
	std::vector<std::pair<char, int>> wspolrzedneRuchu;
	char aktywnyGracz;
	char przeciwnik;

	void bicie(std::shared_ptr<pole>& pole) {
		pole = std::make_shared<polePuste>();
	}

	void promocja(std::shared_ptr<pole>& pole) {
		pole = std::shared_ptr<poleDamka>(new poleDamka(aktywnyGracz));
	}

	double obliczOdleglosc(int& kolumna_P, int& wiersz_P, int& kolumna_K, int& wiersz_K) {
		return sqrt(pow((kolumna_K - kolumna_P), 2) + pow((wiersz_K - wiersz_P), 2));
	}

	bool sprawdzenieRuchu(int& kolumna_P, int& wiersz_P, int& kolumna_K, int& wiersz_K) {
		if (!sprawdzBicia(kolumna_P, wiersz_P, kolumna_K, wiersz_K)) {
			if ((aktywnyGracz == 'x' && wiersz_P > wiersz_K) || (aktywnyGracz == 'o' && wiersz_P < wiersz_K) || poleGry[wiersz_P][kolumna_P]->czyDamka()) {
				double odleglosc = obliczOdleglosc(kolumna_P, wiersz_P, kolumna_K, wiersz_K);

				if (odleglosc != sqrt(2) && odleglosc != 2 * sqrt(2)) {
					throw 1;
					return false;
				}
				else {
					if (odleglosc == sqrt(2)) {
						std::swap(poleGry[wiersz_K][kolumna_K], poleGry[wiersz_P][kolumna_P]);
						throw 0;
						return true;
					}
					if (odleglosc == 2 * sqrt(2)) {
						int sredniaWierszy = (wiersz_K + wiersz_P) / 2;
						int sredniaKolumn = (kolumna_K + kolumna_P) / 2;
						if (!poleGry[sredniaWierszy][sredniaKolumn]->sprawdzPole(przeciwnik)) {
							throw 2;
							return false;
						}
						else {
							bicie(poleGry[sredniaWierszy][sredniaKolumn]);
							std::swap(poleGry[wiersz_K][kolumna_K], poleGry[wiersz_P][kolumna_P]);
							if (szukajBicia(wiersz_K, kolumna_K).size() > 0) {
								system("cls");
								throw 3;
								return false;
							}
							throw 0;
							return true;
						}
					}
				}
			}
			else {
				throw 4;
				return false;
			}
		}
		else {
			throw 5;
		}
		return false;
	}


public:
	Warcabnica() {
		std::vector<std::shared_ptr<pole>> temp;
		aktywnyGracz = 'x';
		przeciwnik = 'o';
		for (int j = 0; j < 8; j++) {
			temp.clear();
			for (int i = 0; i < 8; i++) {
				if (i % 2 == 1 && j % 2 == 0 && j < 3) {
					temp.push_back(std::shared_ptr<poleBierka>(new poleBierka('o')));
				}
				else if (i % 2 == 0 && j % 2 == 1 && j < 3) {
					temp.push_back(std::shared_ptr<poleBierka>(new poleBierka('o')));
				}
				else if (j >= 3 && j < 5 && i % 2 == 1 && j % 2 == 0) {
					temp.push_back(std::shared_ptr<polePuste>(new polePuste()));
				}
				else if (j >= 3 && j < 5 && i % 2 == 0 && j % 2 == 1) {
					temp.push_back(std::shared_ptr<polePuste>(new polePuste()));
				}
				else if (j >= 5 && j < 8 && i % 2 == 1 && j % 2 == 0) {
					temp.push_back(std::shared_ptr<poleBierka>(new poleBierka('x')));
				}
				else if (j >= 5 && j < 8 && i % 2 == 0 && j % 2 == 1) {
					temp.push_back(std::shared_ptr<poleBierka>(new poleBierka('x')));
				}
				else {
					temp.push_back(std::shared_ptr<poleNiemozliwe>(new poleNiemozliwe()));
				}
			}
			poleGry.push_back(temp);
		}
	}

	/*Warcabnica() {
		std::vector<std::shared_ptr<pole>> temp;
		aktywnyGracz = 'x';
		przeciwnik = 'o';
		for (int j = 0; j < 8; j++) {
			temp.clear();
			for (int i = 0; i < 8; i++) {
				if (i % 2 == 1 && j % 2 == 0 && j < 3) {
					temp.push_back(std::shared_ptr<polePuste>(new polePuste()));
				}
				else if (i % 2 == 0 && j % 2 == 1 && j < 3) {
					temp.push_back(std::shared_ptr<poleBierka>(new poleBierka('o')));
				}
				else if (j >= 3 && j < 5 && i % 2 == 1 && j % 2 == 0) {
					temp.push_back(std::shared_ptr<polePuste>(new polePuste()));
				}
				else if (j >= 3 && j < 5 && i % 2 == 0 && j % 2 == 1) {
					temp.push_back(std::shared_ptr<polePuste>(new polePuste()));
				}
				else if (j >= 5 && j < 8 && i % 2 == 1 && j % 2 == 0) {
					temp.push_back(std::shared_ptr<poleBierka>(new poleBierka('x')));
				}
				else if (j >= 5 && j < 8 && i % 2 == 0 && j % 2 == 1) {
					temp.push_back(std::shared_ptr<polePuste>(new polePuste()));
				}
				else {
					temp.push_back(std::shared_ptr<poleNiemozliwe>(new poleNiemozliwe()));
				}
			}
			poleGry.push_back(temp);
		}
	}*/

	void rysuj() {
		std::cout << "Aktualny gracz: " << aktywnyGracz << std::endl;
		for (char i = 'A'; i < 'I'; i++)
			std::cout << "  " << (char)i << "  ";

		std::cout << std::endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				poleGry[i][j]->rysuj();
			}
			std::cout << " " << i;
			std::cout << std::endl;
		}
	}

	bool sprawdzWspolrzedne(int kolumna, int wiersz) {
		if (kolumna > 7 || kolumna < 0) return false;
		if (wiersz > 7 || wiersz < 0) return false;
		return true;
	}

	std::vector<std::pair<int, int>>szukajBicia(int wiersz, int kolumna) {
		std::vector<std::pair<int, int>> wynik;
		std::pair<int, int> wspolrzedne;
		for (int i = -1; i < 2; i += 2) {
			for (int j = -1; j < 2; j += 2) {
				if (sprawdzWspolrzedne(wiersz + i, kolumna + j) && sprawdzWspolrzedne(wiersz + 2 * i, kolumna + 2 * j)) {
					if (poleGry[wiersz][kolumna]->czyDamka()) {
						if (poleGry[wiersz + i][kolumna + j]->sprawdzPole(przeciwnik) && poleGry[wiersz + 2 * i][kolumna + 2 * j]->czyPuste()) {
							wspolrzedne = std::make_pair(wiersz + 2 * i, kolumna + 2 * j);
							wynik.push_back(wspolrzedne);
						}
					}
					else {
						if (aktywnyGracz == 'x' && wiersz > wiersz + 2 * i) {
							if (poleGry[wiersz + i][kolumna + j]->sprawdzPole(przeciwnik) && poleGry[wiersz + 2 * i][kolumna + 2 * j]->czyPuste()) {
								wspolrzedne = std::make_pair(wiersz + 2 * i, kolumna + 2 * j);
								wynik.push_back(wspolrzedne);
							}
						}
						if (aktywnyGracz == 'o' && wiersz < wiersz + 2 * i) {
							if (poleGry[wiersz + i][kolumna + j]->sprawdzPole(przeciwnik) && poleGry[wiersz + 2 * i][kolumna + 2 * j]->czyPuste()) {
								wspolrzedne = std::make_pair(wiersz + 2 * i, kolumna + 2 * j);
								wynik.push_back(wspolrzedne);
							}
						}
					}
				}

			}
		}
		return wynik;
	}

	bool sprawdzBicia(int& kolumna_P, int& wiersz_P, int& kolumna_K, int& wiersz_K) {
		bool wynik = false;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (poleGry[i][j]->sprawdzPole(aktywnyGracz)) {
					std::vector<std::pair<int, int>> mozliweBicia = szukajBicia(i, j);
					if (mozliweBicia.size() > 0) {
						for (int k = 0; k < mozliweBicia.size(); k++) {
							if (kolumna_P == j && wiersz_P == i && wiersz_K == mozliweBicia[k].first && kolumna_K == mozliweBicia[k].second) {
								return false;
							}
							else {
								wynik = true;
							}
						}
					}
				}
			}
		}
		return wynik;
	}

	bool dostepnyRuch(int& wiersz_P, int& kolumna_P) {
		for (int i = -1; i < 2; i += 2) {
			for (int j = -1; j < 2; j += 2) {
				if (sprawdzWspolrzedne(kolumna_P + j, wiersz_P + i)) {
					if (poleGry[wiersz_P][kolumna_P]->czyDamka()) {
						if (poleGry[wiersz_P + i][kolumna_P + j]->czyPuste() || szukajBicia(wiersz_P, kolumna_P).size() > 0)
							return true;
					}
					else {
						if (aktywnyGracz == 'x' && ((wiersz_P > wiersz_P + i && poleGry[wiersz_P + i][kolumna_P + j]->czyPuste()) || szukajBicia(wiersz_P, kolumna_P).size() > 0)) {
							return true;
						}
						if (aktywnyGracz == 'o' && ((wiersz_P < wiersz_P + i && poleGry[wiersz_P + i][kolumna_P + j]->czyPuste()) || szukajBicia(wiersz_P, kolumna_P).size() > 0)) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	void zapiszHistorie(std::string& email) {
		std::filesystem::path historia{ email };
		std::filesystem::create_directories(historia);
		historia.append("historia.txt");
		std::ofstream plik(historia);
		for (int i = 0; i < wspolrzedneRuchu.size(); i++) {
			if (i % 2 == 0 && i != 0) {
				plik << "\n";
			}
			plik << wspolrzedneRuchu[i].first << wspolrzedneRuchu[i].second << " ";
		}
	}

	bool sprawdzPole(int& wiersz_P, int& kolumna_P) {
		return poleGry[wiersz_P][kolumna_P]->sprawdzPole(aktywnyGracz);
	}

	bool czyPuste(int wiersz_P, int kolumna_P) {
		return poleGry[wiersz_P][kolumna_P]->czyPuste();
	}

	bool czyDamka(int& wiersz_P, int& kolumna_P) {
		return poleGry[wiersz_P][kolumna_P]->czyDamka();
	}
	friend class ruch;
};