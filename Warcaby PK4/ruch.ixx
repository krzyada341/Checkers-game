export module ruch;
import <iostream>;
import <memory>;
import <cctype>;
import Warcabnica;

export class ruch {
	Warcabnica* warcabnica;
public:
	ruch(Warcabnica& _warcabnica) {
		warcabnica = &_warcabnica;
	}
	void wykonajRuch() {
		char kolumna_temp;
		int kolumna_P, wiersz_P, kolumna_K, wiersz_K;
		bool sprawdzenie, glownyWarunek = true;
		std::pair<char, int> wspolrzedne;

		do {
			do {
				std::cout << "Wybierz pole pionka, ktorego chcesz ruszyc: ";
				std::cin >> kolumna_temp >> wiersz_P;

				if (std::cin.fail()) {
					system("pause");
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				kolumna_P = std::toupper(kolumna_temp) - 65;

				if (warcabnica->sprawdzWspolrzedne(kolumna_P, wiersz_P)) {
					sprawdzenie = warcabnica->poleGry[wiersz_P][kolumna_P]->sprawdzPole(warcabnica->aktywnyGracz) * warcabnica->dostepnyRuch(wiersz_P, kolumna_P);
				}
				else {
					sprawdzenie = false;
				}

				if (!sprawdzenie) std::cout << "Nieprawidlowe pole pionka \n";
			} while (!sprawdzenie);

			wspolrzedne = std::make_pair((char)(kolumna_P + 65), wiersz_P);
			warcabnica->wspolrzedneRuchu.push_back(wspolrzedne);

			do {
				std::cout << "Wybierz pole na ktore chcesz sie ruszyc: ";
				std::cin >> kolumna_temp >> wiersz_K;

				if (std::cin.fail()) {
					system("pause");
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				kolumna_K = std::toupper(kolumna_temp) - 65;

				if (warcabnica->sprawdzWspolrzedne(kolumna_K, wiersz_K)) {
					sprawdzenie = warcabnica->poleGry[wiersz_K][kolumna_K]->czyPuste();
				}
				else {
					sprawdzenie = false;
				}

				if (!sprawdzenie) std::cout << "Nie mozesz sie ruszyc na to pole \n";
			} while (!sprawdzenie);

			try {
				!warcabnica->sprawdzenieRuchu(kolumna_P, wiersz_P, kolumna_K, wiersz_K);
			}
			catch (const int wyjatek) {
				switch (wyjatek) {
				case 0:
					glownyWarunek = false;
					break;
				case 1:
					glownyWarunek = true;
					std::cout << "Mozesz sie ruszyc tylko po skosie \n";
					break;
				case 2:
					glownyWarunek = true;
					std::cout << "Nie wolno sie ruszac o wiecej niz 1 pole bez bicia \n";
					break;
				case 3:
					glownyWarunek = true;
					warcabnica->rysuj();
					std::cout << "Mozliwosc kolejnego bicia \n";
					break;
				case 4:
					glownyWarunek = true;
					std::cout << "Nie wolno sie ruszac do tylu \n";
					break;
				case 5:
					glownyWarunek = true;
					std::cout << "Wykryto obowiazkowe bicie \n";
					break;
				}
			}
		} while (glownyWarunek);

		if ((wiersz_K == 0 && warcabnica->aktywnyGracz == 'x') || (wiersz_K == 7 && warcabnica->aktywnyGracz == 'o')) {
			warcabnica->promocja(warcabnica->poleGry[wiersz_K][kolumna_K]);
		}

		wspolrzedne = std::make_pair((char)(kolumna_K + 65), wiersz_K);
		warcabnica->wspolrzedneRuchu.push_back(wspolrzedne);

		std::swap(warcabnica->aktywnyGracz, warcabnica->przeciwnik);
	}
};