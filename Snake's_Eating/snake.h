//snake.h -- 贪吃蛇头文件，包含结构体snake、结构体food、结构体地图以及相应函数声明
#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>

//蛇
typedef enum _direction Direction;
enum _direction
{
	nul = 0, up = 72, down = 80, left = 75, right = 77
};

typedef struct _snake_body SnakeBody;
struct _snake_body
{
	int x;
	int y;
	SnakeBody* next;
};

typedef struct _snake Snake;
struct _snake
{
	int minLength;	//初始长度
	Direction drct;
	bool isDead;
	SnakeBody* bodys;
	int length;		//当前长度
};

//地图
typedef enum _block Block;
enum _block
{
	mblock, //地图格
	sblock, //蛇格
	fblock	//食物格
};

typedef struct _map Map;
struct _map
{
	int width;
	int high;
	int** map;
};


//食物
typedef struct _food Food;
struct _food
{
	int x;
	int y;
};


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
extern void forward(SnakeBody* nextBlock, SnakeBody* finalBody);
extern void eat(SnakeBody* nextBlock);
extern void die(void);
extern void destroySnake(void);

#define FORWARD_TIME 1000
extern void createFood(void);
extern void destroyFood(void);

extern int initGame(void);
extern int resetGame(void);
extern int exitGame(void);

extern void checkNext(void);
extern Direction inputKey(void);

#endif // !__SNAKE_H__
