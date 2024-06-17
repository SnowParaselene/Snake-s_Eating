//snake.c -- 贪吃蛇游戏函数定义

#define _CRT_SECURE_NO_WARNINGS
#include "snake.h"

void createMap(int width, int high)
{
	int** temp;
	int row;
	int col;

	map = (Map*)malloc(sizeof(Map));
	if (2 < width || 2 < high)
	{
		map->high = HIGH;
		map->width = WIDTH;
		printf("地图长宽不合法，已重置为 %d * %d\n", WIDTH, HIGH);
	}
	else
	{
		map->high = high;
		map->width = width;
	}

	//创建地图
	temp = (int**)malloc(high * sizeof(int*));	//申请地图行
	for (row = 0; row < high; row++)
	{
		temp[row] = (int*)malloc(width * sizeof(int));//申请该行的地图列
		for (col = 0; col < width; col++)
		{
			temp[row][col] = 0; //地图格初始化
		}
	}
	map->map = temp;

	return;
}

void destroyMap(void)
{
	if (!map) return;
	int row;
	int** temp;

	temp = map->map;
	for (row = 0; row < map->high; row++)
	{
		free(temp[row]);
	}
	free(temp);
	free(map);
	map = NULL;
	return;
}

int isMapBlockFilled(int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->high) return 1;

	int i;
	SnakeBody* body = snake->bodys;

	//检查蛇每一节是否占据目标位置
	for (i = 0; i < snake->length; i++)
	{
		if (x == body->x && y == body->y) return 1;
		body = body->next;
	}

	return 0;
}

void showMap(void)
{
	int row, col;
	int len;
	SnakeBody* body = snake->bodys;

	//刷新地图
	for (row = 0; row < map->high; row++)
	{
		for (col = 0; col < map->width; col++)
			map->map[row][col] = mblock;
	}

	for (len = 0; len < snake->length; len++)
	{
		map->map[body->y][body->x] = sblock;
		body = body->next;
	}

	map->map[food->y][food->x] = fblock;

	//打印地图
	for (row = 0; row < map->high; row++)
	{
		for (col = 0; col < map->width; col++)
			//枚举是哪种类型，显示
			//printf("%d", map->map[row][col]);
			switch (map->map[row][col])
			{
			case mblock:
				printf("%c ", mapBlock);
				break;
			case sblock:
				printf("%c ", snakeBlock);
				break;
			case fblock:
				printf("%c ", foodBlock);
				break;
			default:
				break;
			}
		printf("\n");
	}
}

Snake* createSnake(int length)
{
	if ((map->width / 2) < length)
	{
		length = LENGTH;
		printf("蛇初始长度不合法，已重置为 %d\n", LENGTH);
	}

	int i;
	SnakeBody* body = NULL;

	//蛇体创建
	for (i = length - 1; i >= 0; i--)
	{
		SnakeBody* head = (SnakeBody*)malloc(sizeof(SnakeBody));
		head->next = body;
		head->y = map->high / 2;
		head->x = map->width / 2 - i;
		body = head;
	}

	//创建蛇
	snake = (Snake*)malloc(sizeof(Snake));
	snake->drct = right;
	snake->bodys = body;
	snake->minLength = length;
	snake->length = length;

	return snake;
}

void destroySnake(void)
{
	if (!snake) return;
	int i;
	SnakeBody* temp = NULL;

	for (i = 0; i < snake->length; i++)
	{
		temp = snake->bodys;
		snake->bodys = snake->bodys->next;
		free(temp);
	}
	free(snake);
	snake = NULL;
	return;
}

void createFood(void)
{
	int x, y;

	if (!food) food = (Food*)malloc(sizeof(Food));
	while (1) {
		x = rand() % map->width;
		y = rand() % map->high;
		if (!isMapBlockFilled(x, y))
			break;
	}

	food->x = x;
	food->y = y;
	return;
}

void destroyFood(void)
{
	if (!food) return;
	free(food);
}

int initGame(void)
{
	//设置随机数种子
	srand((time_t)time(NULL));

	//初始化地图、蛇、食物
	createMap(60, 30);
	createSnake(3);
	createFood();

	return 0;
}

int resetGame(void)
{
	//重置蛇的长度、重置水果位置
	int i;
	SnakeBody* body = NULL;

	for (i = 0; i < snake->length; i++)
	{
		SnakeBody* temp = snake->bodys;
		snake->bodys = snake->bodys->next;
		free(temp);
	}
	for (i = 0; i < snake->minLength; i++)
	{
		SnakeBody* head = (SnakeBody*)malloc(sizeof(SnakeBody));
		head->next = body;
		head->y = map->high / 2;
		head->x = map->width / 2 - i;
		body = head;
	}
	snake->length = snake->minLength;

	createFood();

	return 0;
}

int exitGame(void)
{
	//释放地图、蛇、食物
	destroyFood();
	destroySnake();
	destroyMap();

	return 0;
}



