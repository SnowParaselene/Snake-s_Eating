//snake.h -- 贪吃蛇头文件，包含结构体snake、结构体food、结构体地图以及相应函数声明
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//蛇
typedef enum _direction
{
	up,down,left,right
}Direction;

typedef struct _snake Snake;
struct _snake
{
	int minLength;	//初始长度
	Direction drct;
	SnakeBody* bodys;
	int length;		//当前长度
};
Snake* snake = NULL;

typedef struct _snake_body
{
	int x;
	int y;
	SnakeBody* next;
}SnakeBody;

//地图
typedef enum _block
{
	mblock, //地图格
	sblock, //蛇格
	fblock	//食物格
}Block;

char mapBlock = ' ';
char snakeBlock = 'O';
char foodBlock = '*';

typedef struct _map Map;
struct _map
{
	int width;
	int high;
	int** map;
};
Map* map = NULL;

//食物
typedef struct _food
{
	int x;
	int y;
}Food;
Food* food = NULL;

//默认游戏长宽
#define WIDTH 60
#define HIGH 30
extern void createMap(int width, int high);
extern void destroyMap(void);
extern int isMapBlockFilled(int x, int y);
extern void showMap(void);

//默认蛇长度
#define LENGTH 3
extern Snake* createSnake(int length);
extern void destroySnake(void);

#define FORWARD_TIME 1000
extern void createFood(void);
extern void destroyFood(void);

extern int initGame(void);
extern int resetGame(void);
extern int exitGame(void);

extern int inputKey(void);
