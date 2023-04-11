export module timer;
import <iostream>;
import <thread>;
import <chrono>;
import <future>;

import pola;
import Warcabnica;
import ruch;

export void timer(Warcabnica& warcabnica, std::promise<int>& p) {
	std::chrono::milliseconds DELAY(1000);
	int seconds = 0;

	while (poleBierka::liczbaX > 0 && poleBierka::liczbaO > 0) {
		seconds++;
		std::this_thread::sleep_for(DELAY);
	}
	p.set_value(seconds);
}