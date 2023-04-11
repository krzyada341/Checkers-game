module;
export module pola:bierka;
import <iostream>;
import :pole;

export class poleBierka :public pole {
	char gracz = ' ';
public:
	poleBierka(char _gracz) {
		this->gracz = _gracz;
		if (gracz == 'x') liczbaX++;
		if (gracz == 'o') liczbaO++;
	}

	void rysuj() {
		std::cout << "[ " << gracz << " ]";
	}

	bool sprawdzPole(char _gracz) {
		if (gracz == _gracz) {
			return true;
		}
		return false;
	}

	bool czyPuste() { return false; }

	bool czyDamka() { return false; }

	~poleBierka() {
		if (gracz == 'x') liczbaX--;
		if (gracz == 'o') liczbaO--;
	}
};
