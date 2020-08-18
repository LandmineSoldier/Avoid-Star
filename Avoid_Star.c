#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//#include <mmsystem.h> // 노래재생에 필요함
//#pragma comment(lib, "winmm.lib")

#pragma warning(disable:4996)

enum colorName
{
	BLACK,
	D_BLUE,
	D_GREEN,
	D_SKYBLUE,
	D_RED,
	D_VIOLET,
	D_YELLOW,
	GRAY,
	D_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

void color(int bgColor, int textColor) // 색상변환
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
}

int gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CursorView(int show) // 입력 커서 제거
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
int GameOver(int print, int moveCount, int avoidScore)
{
	if (print == 1)
	{
		color(BLACK, WHITE);
		system("cls");
		printf("+==============================+\n");
		printf("I                              I\n");
		printf("I                              I\n");
		printf("I          GAME  OVER          I\n");
		printf("I                              I\n");
		printf("I                              I\n");
		printf("+==============================+\n\n");
		printf("       이동횟수 : %d\n", moveCount);
		printf("       회피점수 : %d\n", avoidScore);
	}
	Sleep(1000);
}
int main(void)
{
	int map[10][10] = { 0, };
	int mapx[10][10] = { 0, };
	int mapy[10][10] = { 0, };
	char szChoice = 0;


	int x = 18, y = 4;


	int Life = 100;

	int bombCard = 1;

	int moveCount = 0;

	int damage = 5;


	int checkx = 0, checky = 0;
	int rand_spawn = 0;
	int counting = 0;
	int starcheck = 0;


	int avoidScore = 0;


	int starSpeed = 10; // 낮을 수록 빠름 최대 1
	//속도에 따라 별이 주는 피해가 다름
	//속도가 5라면 별은 데미지가 5*damage 가 된다.


	int maxx = 0;
	int maxy = 0;

	printf("별 속도를 입력해주세요 (1부터 50 사이)\n");
	printf("숫자가 낮을 수록 빠릅니다 (10 추천)\n");
	scanf_s("%d", &starSpeed);
	//printf("데미지를 입력해주세요\n");
	system("cls");
	printf("5초후 시작합니다..\n");
	CursorView(0);
	Sleep(1000);
	gotoxy(0, 0);
	printf("4");
	Sleep(1000);
	gotoxy(0, 0);
	printf("3");
	Sleep(1000);
	gotoxy(0, 0);
	printf("2");
	Sleep(1000);
	gotoxy(0, 0);
	printf("1");
	Sleep(1000);
	gotoxy(0, 0);
	printf("0");

	while (1)
	{
		if (counting >= starSpeed) // 별이 이동되는 텀을 둠
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map[i][j] == 8)
					{
						if (j + 1 != 10)
						{
							map[i][j] = 0;
							map[i][j + 1] = 8;
							starcheck = 1;
							break;
						}
						else
						{
							avoidScore++;
							map[i][j] = 0;
							break;
						}
					}
				}
				if (starcheck == 0)
				{
					rand_spawn = rand() % 2;
					if (rand_spawn != 0)
						map[i][0] = 8;
				}
				starcheck = 0;
			}
			counting = 0;
		}
		counting++;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mapx[i][j] = j * 2;
				mapy[i][j] = i;
				maxx = j * 2;
				maxy = i;
			}
		}

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				color(WHITE, BLACK);
				gotoxy(mapx[i][j], mapy[i][j]);
				if (mapy[i][j] != y)
				{
					if (map[i][j] == 0)
					{
						printf("■");
					}

					else if (map[i][j] == 8)
					{
						printf("★");
					}
				}
				else if (mapy[i][j] == y)
				{
					if (map[i][j] == 8)
						checky = 1;
				}
				if (mapx[i][j] != x)
				{
					if (map[i][j] == 0)
					{
						printf("■");
					}
					else if (map[i][j] == 8)
					{
						printf("★");
					}
				}
				else if (mapx[i][j] == x)
				{
					if (map[i][j] == 8)
						checkx = 1;
				}


				if (checky == 1 && checkx == 1)// 하트가 별과 겹치는지 확인
				{
					Life -= damage;
					avoidScore -= 1;
					if (Life == 0)
					{
						GameOver(1, moveCount, avoidScore);
						return 0;
					}
				}
				checky = 0;
				checkx = 0;
				color(BLACK, WHITE);
				if (j == 9 && i == 0)
				{
					gotoxy(mapx[i][j] + 2, mapy[i][j]);
					printf("현재체력 : %d", Life);
					gotoxy(mapx[i][j] + 2, mapy[i][j] + 2);
					printf("이동횟수 : %d", moveCount);
					gotoxy(mapx[i][j] + 2, mapy[i][j] + 4);
					printf("회피점수 : %d", avoidScore);
					gotoxy(mapx[i][j] + 2, mapy[i][j] + 6);
					printf("폭탄카드 : %d", bombCard);

					if ((Life - 10) < 0)
					{
						gotoxy(mapx[i][j] + 14, mapy[i][j]);
						printf(" ");
					}
					else if ((Life - 100) < 0)
					{
						gotoxy(mapx[i][j] + 15, mapy[i][j]);
						printf(" ");
					}




					if (avoidScore < 0)
					{
						gotoxy(mapx[i][j] + 2, mapy[i][j] + 8);
						printf("아직 죽을 순 없다ㅏㅏㅏ");
						system("cls");
					}
					else if ((avoidScore - 10) < 0)
					{
						gotoxy(mapx[i][j] + 14, mapy[i][j] + 4);
						printf(" ");
					}
					else if ((avoidScore - 100) < 0)
					{
						gotoxy(mapx[i][j] + 15, mapy[i][j] + 4);
						printf(" ");
					}
				}
			}
		}
		gotoxy(x, y);
		color(BLACK, WHITE);
		printf("♥");
		if (kbhit())
		{
			szChoice = getch();
			switch (szChoice)
			{
			case 'w':
				if (y != 0)
				{
					y--;
					checkx = 0;
					checky = 1;
				}
				moveCount++;
				break;
			//case 'a':
			//	if (x != 0)
			//	{
			//		if (x > 1)
			//			x -= 2;
			//		else
			//			x--;
			//		checkx = 1;
			//		checky = 0;
			//	}
			//	break;
			case 's':
				if (y != maxy)
				{
					y++;
					checkx = 0;
					checky = 1;
				}
				moveCount++;
				break;
			//case 'd':
			//	if (x != maxx)
			//	{
			//		if (x < maxx - 1)
			//			x += 2;
			//		else
			//			x++;
			//		checkx = 1;
			//		checky = 0;
			//	}
			//	break;
			case 'e':
				if (bombCard > 0)
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						map[i][j] = 0;
					}
				}
				if (bombCard > 0)
					bombCard -= 1;
				break;
			}
			Sleep(50);
		}
	}
	return 0;
}
