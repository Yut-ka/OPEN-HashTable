#pragma once
void ExConsole();
void setCursorPosition(int x, int y);
void setConsoleColour(unsigned short colour);
void cls();
void helpQuard();
void square(int width, int hight, int type, int posX, int posY);
void help();

class field
{
public:
	field(std::string name, int id);
	field(std::string name);

	void show(int pos);
	void Press(int pos);

	std::string name; 
private:
	int id;

};

class textblock
{
public:
	textblock(std::string name);

	void show(int pos);
	std::string Press(int pos);

	std::string name;

};


class ProgressBar
{
public:
	ProgressBar(std::string name, float value, UINT id);
	ProgressBar(std::string name, float value);
	ProgressBar(std::string name);
	void Show(int pos);
	void ChangeValue(int pos);

	float value;


private:
	UINT id;
	float max = 100.0f;
	float min = 0.0f;

	std::string name;
};


class timer
{
private:
	uint64_t internal_tick = 0;
	uint32_t interval = 0;
	bool enable = true;
	bool tick_count = false;
	void tick()
	{
		if (enable)
			tick_count = (GetTickCount64() > internal_tick);
		else
			tick_count = false;

		if (tick_count)
			internal_tick = GetTickCount64() + interval;
	}

public:

	timer()
	{
		timer::interval = 100;
		timer::enable = true;
		internal_tick = GetTickCount64() + interval;
	}

	timer(int interval, bool enable)
	{
		timer::interval = interval;
		timer::enable = enable;
		internal_tick = GetTickCount64() + interval;
	}

	// check_tick
	bool timer_on()
	{
		tick();
		return tick_count;
	}
	// stop tick
	void stop()
	{
		enable = false;
	}
	// start again
	void start()
	{
		enable = true;
	}
	// change interval
	void set_new_interval(int new_interval)
	{
		interval = new_interval;
	}
};