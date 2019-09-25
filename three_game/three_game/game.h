#pragma once
#define    GAME_H 	
#include<stdlib.h>
#include<time.h>
#include<String.h>
#define ROW 3
#define COL 3

//初始化棋盘
void InitBoard(char board[][ROW], int row, int col);

//打印棋盘
void ShowBoard(char board[][ROW], int row, int col);

//玩家移动
void PlayerMove(char board[][ROW], int row, int col);

//是否赢得了胜利
int IsWin(char board[][ROW], int row, int col);

//电脑移动
void ComputerMove(char board[][ROW], int row, int col);

//判断输赢
int IsWin(char board[][ROW], int row, int col);

//判断棋盘是否放满
int IsFull(char board[][ROW], int row, int col);