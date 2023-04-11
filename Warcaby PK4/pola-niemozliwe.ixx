module;
export module pola:niemozliwe;
import <iostream>;
import :pole;

export class poleNiemozliwe :public pole {
public:
	poleNiemozliwe() {}
	void rysuj() {
		std::cout << "[   ]";
	}
	bool sprawdzPole(char _gracz) { return false; }
	bool czyPuste() { return false; }
	bool czyDamka() { return false; }
};