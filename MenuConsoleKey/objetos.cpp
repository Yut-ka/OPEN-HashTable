#include "head.h"
#include "objetos.h"


UINT ID_itens = 0;
// Checkbox
void ExConsole()
{
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	COORD NewSBSize;
	int Status;

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hOut, &SBInfo);
	NewSBSize.X = SBInfo.dwSize.X;
	NewSBSize.Y = SBInfo.dwSize.Y;

	Status = SetConsoleScreenBufferSize(hOut, NewSBSize);
	if (Status == 0)
	{
		Status = GetLastError();
		std::cout << "SetConsoleScreenBufferSize() failed! Reason : " << Status << std::endl;
		exit(Status);
	}

	GetConsoleScreenBufferInfo(hOut, &SBInfo);
}
std::string Shadow[5] = { "","\xB0","\xB1","\xB2"," " };
std::string  Style[5][12] = {
{""," "," "," "," "," "," "," "," "," "," "," " },
{"","\xDA","\xC4","\xBF","\xB3","\xD9","\xC0","\xC3","\xB4","\xC2","\xB3","\xC1"},
{"","\xC9","\xCD","\xBB","\xBA","\xBC","\xC8","\xCC","\xB9","\xCB","\xBA","\xCA"},
{"","\xD5","\xCD","\xB8","\xB3","\xBE","\xD4","\xC6","\xB9","\xD1","\xB3","\xCF"},
{"","\xD6","\xC4","\xB7","\xBA","\xBD","\xD3","\xC7","\xC6","\xD2","\xBA","\xD0"}
};

void helpQuard()
{
	std::cout << "SHADOW" << std::endl;
	for (int i = 0; i < 5; ++i)
		std::cout << " " << Shadow[i];
	std::cout << std::endl;
	std::cout << "Quard type 1" << std::endl;
	for (int i = 0; i < 12; ++i)
		std::cout << Style[1][i];
	std::cout << std::endl;
	std::cout << "Quard type 2" << std::endl;
	for (int i = 0; i < 12; ++i)
		std::cout << Style[2][i];
	std::cout << std::endl;
	std::cout << "Quard type 3" << std::endl;
	for (int i = 0; i < 12; ++i)
		std::cout << Style[3][i];
	std::cout << std::endl;
	std::cout << "Quard type 4" << std::endl;
	for (int i = 0; i < 12; ++i)
		std::cout << Style[4][i];

}

void help()
{
	cls();
	std::cout << "Help command use HELP or ?\n";

	std::cout << "\t\t*HELP*\n";
	std::cout << "[quard] use this for drawn a square you need this paraments : widht, hight, type, Position X and Y\n";
	std::cout << "[SetCursorPosition] use this for set position for next text or drawn, paraments needed is : Position X and Y\n";
	std::cout << "[setConsoleColour] use this for set color for next text or drawn, paraments needed is : int color\n";
	std::cout << "[cls] use this for clear all text\n";
	std::cout << "[checkbox] Drawn one checkbox, for set true or false value return, paraments needed is : name, check, id\n";
	std::cout << "Or only Name, for use this is .show() and change value is .ChangeValue(POSITION)\n";
	std::cout << "[TextEdit] Drawn one TextEdit, for set new text value, paraments needed is: name, lenght , buffer, id\n";
	std::cout << "for show use .show(), and change value use .ChangeValue(POSITION)\n";
	std::cout << "[TrackBar] Drawn one TrackBar, for set value or change value, paraments needed is: name, min, max, value, id\n";
	std::cout << "Or only Name,  Min, Max, for show this use : .show(), and chenge value is .ChangeValue(POSIITION)\n";
	std::cout << "[ComboBox] Drawn one ComboBox, for set  new text value, paraments needed is: name, list, lenght, id\n";
	std::cout << "Or only Name, for show this use : .show(), and chenge value is .ChangeValue(POSIITION)\n";
	std::cout << "[ProgressBar] Drawn one progressBar, for show and value or load anything, paramets needed is: name, value, max and id\n";
	std::cout << "Or only Name, for show this use : .show(), and chenge value is .ChangeValue(POSIITION)\n";
}


void square(int width, int hight, int type, int posX, int posY)
{

	std::string space = std::string(width, ' ');
	//Desenha a primiera curva superior
	setCursorPosition(posX, posY);
	std::cout << Style[type][1];

	//Desenha a superior inferior horizontal
	for (int i = 0; i < width; ++i) std::cout << Style[type][2];
	//Desenha a segunda curva superior
	std::cout << Style[type][3];
	int line = 1;
	for (line = 1; line < hight; ++line)
	{
		//Desenha a primeira linha vertical
		setCursorPosition(posX, posY + line);
		std::cout << Style[type][4];

		//Limpa as linhas
		setCursorPosition(posX + 1, posY + line);
		std::cout << space;

		//Desenha a segunda linha vertical
		setCursorPosition(width + 1, posY + line);
		std::cout << Style[type][4];
	}
	//desenha a primeira curva inferior
	setCursorPosition(posX, posY + line);
	std::cout << Style[type][6];

	//Desenha a linha inferior horizontal
	for (int i = 0; i < width; ++i) std::cout << Style[type][2];
	//desenha a segunda curva inferior
	std::cout << Style[type][5];

}

void setCursorPosition(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	std::cout.clear();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void setConsoleColour(unsigned short colour)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	SetConsoleTextAttribute(hOut, colour);
}



void cls()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };
	std::cout.flush();
	std::cin.clear();
	if (!GetConsoleScreenBufferInfo(hOut, &csbi))
		abort();

	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written;
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(hOut, topLeft);
}

/*
* Name, check and id
*/
field::field(std::string name, int id)
{
	field::id = id;
	field::name = name;
	++ID_itens;
}

/*
*	 Name only
*/
field::field(std::string name)
{
	field::id = ID_itens;
	field::name = name;
	++ID_itens;
}

void field::show(int pos)
{
	if (pos == field::id)
		std::cout << ">  " << field::name << "   " << std::endl;
	else
		std::cout << "  " << field::name << "    " << std::endl;
}

void field::Press(int pos)
{
	ID_itens = 0;
}




/*
*	 Name only
*/
textblock::textblock(std::string name)
{
	textblock::name = name;
	
}

void textblock::show(int pos)
{
	std::cout << ">  " << textblock::name << "   \n";
		
}

std::string textblock::Press(int pos)
{
	std::string a;
	std::cin >> a;
	return a;
}



ProgressBar::ProgressBar(std::string name, float value, UINT id)
{
	ProgressBar::id = id;
	ProgressBar::name = name;
	ProgressBar::value = value;
}

ProgressBar::ProgressBar(std::string name, float value)
{
	ProgressBar::id = ID_itens;
	ProgressBar::name = name;
	ProgressBar::value = value;
	++ID_itens;
}

ProgressBar::ProgressBar(std::string name)
{
	ProgressBar::id = ID_itens;
	ProgressBar::name = name;
	ProgressBar::value = 0;
	++ID_itens;
}
 
void ProgressBar::Show(int pos)
{
	std::string bar;
	bar.clear();
	bar.append("[");
	for (int x = 0; x <= max; ++x)
	{
		if (x <= value)
			bar.append("|");
		else	
			bar.append(".");
	}
	bar.append("]");
	std::cout << bar << std::endl;

}

void ProgressBar::ChangeValue(int pos)
{
	value += 0.5f;
}
