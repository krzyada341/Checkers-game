module;
export module pola:pole;

export class pole {
public:
	static int liczbaX;
	static int liczbaO;
	virtual void rysuj() = 0;
	virtual bool sprawdzPole(char _gracz) = 0;
	virtual bool czyPuste() = 0;
	virtual bool czyDamka() = 0;
	friend class Warcabnica;
};

int pole::liczbaX = 0;
int pole::liczbaO = 0;