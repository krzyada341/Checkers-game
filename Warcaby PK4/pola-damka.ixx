module;
export module pola:damka;
import <iostream>;
import <cctype>;
import :pole;

export class poleDamka :public pole {
	char gracz = ' ';
public:
	poleDamka(char _gracz) {
		this->gracz = _gracz;
		if (gracz == 'x') liczbaX++;
		if (gracz == 'o') liczbaO++;
	}

	void rysuj() {
		std::cout << "[ " << (char)(std::toupper(gracz)) << " ]";
	}

	bool sprawdzPole(char _gracz) {
		if (gracz == _gracz) {
			return true;
		}
		return false;
	}

	bool czyPuste() { return false; }

	bool czyDamka() { return true; }

	~poleDamka() {
		if (gracz == 'x') liczbaX--;
		if (gracz == 'o') liczbaO--;
	}
};
