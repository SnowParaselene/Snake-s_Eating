//main.c -- 贪吃蛇游戏入口和框架
#include "snake.h"

extern Snake* snake;
extern bool isExit;

int main(void)
{
	printf("Game is starting......\n");
	initGame();
	system("CLS");
	while (true)
	{
		system("cls");
		showMap();
		Direction drct = 0;
		if (drct = inputKey())
			snake->drct = drct;
		checkNext();
		if (snake->isDead)
		{
			//本局结束
			char select;
			bool answered = false;
			while (!answered)
			{
				printf("Game Over.\nStart another game?(Y\\N)\n");
				switch (scanf("%c", &select), select)
				{
				case 'y':
				case 'Y':
					resetGame();
					system("cls");
					answered = true;
					break;
				case 'n':
				case 'N':
					exitGame();
					system("cls");
					answered = true;
					break;
				default:
					printf("Please answer Y or N.\n");
				}
			}
			while (fgetc(stdin) != '\n');
		}

		if (isExit) break;
	}
	printf("Bye.");
	return 0;
}