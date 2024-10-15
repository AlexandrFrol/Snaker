#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>

int* RandomPos() 
{
	int* XY = new int[2];
	XY[0] = rand() % 29;
	XY[1] = rand() % 29;
	return XY;
}

void CoutString(std::string str, int delay) 
{
	for (int i = 0; i < str.size(); i++) 
	{
		std::cout << str[i];
		Sleep(delay);
	}
}

int main()
{
	srand(time(0));

	char snake_head = '^';
	int* snake_XY = new int[2];
	snake_XY[0] = 29;
	snake_XY[1] = 14;

	int* snake_Previous_XY = new int[2];
	snake_Previous_XY[0] = 29;
	snake_Previous_XY[1] = 14;

	int snake_size = 3, direction = 0, area_sizeY = 29, area_sizeX = area_sizeY * 2;

	int** area = new int* [area_sizeY];
	for (int i = 0; i < area_sizeY; i++) 
	{
		area[i] = new int[area_sizeX];
		for (int e = 0; e < area_sizeX; e++) 
		{
			area[i][e] = 0;
		}
	}
	int* FruitXY = RandomPos();
	bool FruitPresent = false, out_of_range = false;
	int msec = 0, time = 0, select = 1;

	system("pause");

	time_t t_time = clock();
	while (true) 
	{
		if (clock() - t_time > 80) 
		{
			if (_kbhit()) 
			{
				char x = _getch();
				switch (x) 
				{
					case 'w': 
					{
						if (direction != 2)
						{
							direction = 0;
							snake_head = '^';
						}
						break;
					}
					case 'a': 
					{
						if (direction != 3)
						{
							direction = 1;
							snake_head = '<';
						}
						break;
					}
					case 's': 
					{
						if (direction != 0)
						{
							direction = 2;
							snake_head = 'v';
						}
						break;
					}
					case 'd': 
					{
						if (direction != 1)
						{
							direction = 3;
							snake_head = '>';
						}
						break;
					}
				}
			}
			snake_Previous_XY[0] = snake_XY[0];
			snake_Previous_XY[1] = snake_XY[1];

			printf("\x1b[H");

			switch (direction) 
			{
				case 0: 
				{
					snake_XY[1] -= 1;
					break;
				}
				case 1: 
				{
					snake_XY[0] -= 1;
					break;
				}
				case 2: 
				{
					snake_XY[1] += 1;
					break;
				}
				case 3: 
				{
					snake_XY[0] += 1;
					break;
				}
			}

			if (snake_XY[1] == area_sizeY || snake_XY[1] < 0 || snake_XY[0] > area_sizeX || snake_XY[0] < 0) 
			{
				out_of_range = true;
			}

			if (out_of_range == true || area[snake_XY[1]][snake_XY[0]] != 0 && area[snake_XY[1]][snake_XY[0]] != -2) 
			{
				break;
			}

			if (FruitPresent == false) 
			{
				while (FruitPresent == false)
				{
					FruitXY = RandomPos();
					if (area[FruitXY[1]][FruitXY[0]] == 0) 
					{
						FruitPresent = true;
					}
				}
				area[FruitXY[1]][FruitXY[0]] = -2;			}

			if (FruitXY[0] == snake_XY[0] && FruitXY[1] == snake_XY[1]) 
			{
				snake_size++;
				FruitPresent = false;
			}

			area[snake_XY[1]][snake_XY[0]] = -1;

			area[snake_Previous_XY[1]][snake_Previous_XY[0]] = 1;

			for (int i = 0; i < area_sizeY; i++) 
			{
				for (int e = 0; e < area_sizeX; e++) 
				{
					if (area[i][e] == 0) 
					{ 
						std::cout << "."; 
					}
					else if (area[i][e] == -2) 
					{ 
						std::cout << "@"; 
					}
					else if (area[i][e] == -1) 
					{ 
						std::cout << snake_head; 
					}
					else if (area[i][e] > 0) 
					{
						if (area[i][e] >= snake_size) 
						{
							area[i][e] = 0;
							std::cout << ".";
						}
						else 
						{
							area[i][e]++;
							std::cout << "#";
						}
					}

				}
				if (i == 5) 
				{ 
					std::cout << "  Time: " << t_time / 1000; 
				}
				if (i == 6)
				{ 
					std::cout << "  Score: " << int(t_time / 1000) + (snake_size * 2) - 6; 
				}
				std::cout << std::endl;

				t_time = clock();
			}
		}
		
	}
	system("cls");

	std::cout << "\n\n Death\n  Score: " << int(t_time / 1000) + (snake_size * 2) - 6 << "\n\n\n";

	system("pause");

	return 0;
}