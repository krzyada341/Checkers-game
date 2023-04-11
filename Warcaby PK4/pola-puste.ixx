module;
export module pola:puste;
import <iostream>;
import :pole;

export class polePuste :public pole {
public:
	polePuste() {}

	void rysuj() {
		std::cout << "[ - ]";
	}

	bool sprawdzPole(char _gracz) { return false; }

	bool czyPuste() { return true; }

	bool czyDamka() { return false; }
};
