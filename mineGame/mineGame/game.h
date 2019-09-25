#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "stdlib.h"

#define ROW  9
#define COL  9

#define ROWS  ROW+2
#define COLS  COL+2


#define MINENUM 5 //设置10个雷

void InitBoard(char board[][COLS], int rows, int cols, char set);//初始化棋盘

void ShowBoard(char board[][COLS], int rows, int cols);//打印棋盘

void SetMine(char mine[][COLS], int row, int col,  int x, int y);//设置雷

void FirstFindMine(char mineInfo[][COLS], char mine[][COLS], int row, int col);//第一次找雷
void FindMine(char mineInfo[][COLS], char mine[][COLS], int row, int col);//找雷

void openMine(char mineInfo[][COLS], char mine[][COLS],int x, int y);

