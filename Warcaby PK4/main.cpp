import <iostream>;
import <thread>;
import <chrono>;
import <future>;
import pola;
import Warcabnica;
import ruch;
import timer;
import regexMail;

int main() {
	Warcabnica warcabnica;
	ruch ruszanie(warcabnica);
	std::promise<int> p;
	std::future<int> f = p.get_future();
	bool warunek = true;
	std::string email;

	std::thread czas(timer, std::ref(warcabnica), std::ref(p));
	czas.detach();

	while (poleBierka::liczbaX > 0 && poleBierka::liczbaO > 0) {
		system("cls");
		warcabnica.rysuj();
		ruszanie.wykonajRuch();
	}

	if (poleBierka::liczbaX > 0) {
		std::cout << "Wygrywa X. Czas gry: " << f.get() << std::endl;

		while (warunek == true) {

			std::cout << "Podaj swoj adres email aby zapisac historie: " << std::endl;
			std::cin >> email;

			if (sprawdz(email) == true) {
				warunek = false;
			}
			else warunek = true;

		}
	}
	else { 
		std::cout << "Wygrywa O. Czas gry: " << f.get() << std::endl;

		while (warunek == true) {

			std::cout << "Podaj swoj adres email aby zapisac historie: " << std::endl;
			std::cin >> email;

			if (sprawdz(email) == true) {
				warunek = false;
			}
			else warunek = true;

		}
	}
	warcabnica.zapiszHistorie(email);

	//return 0;
	
}
