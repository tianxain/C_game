#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"game.h" 

//打印菜单
void menu()
{
	printf("**********************\n");
	printf("********0.exit********\n");
	printf("********1.play********\n");
	printf("**********************\n");
}

//游戏
void game()
{
	int ret = 0;
	char board[3][3] = { 0 };//定义数组作为棋盘
	InitBoard(board, ROW, COL);//初始化棋盘 
	ShowBoard(board, ROW, COL);//打印棋盘 
	while (1)
	{
		PlayerMove(board, ROW, COL);//玩家下棋
		ShowBoard(board, ROW, COL); //打印棋盘
		ret = IsWin(board, ROW, COL);//每次都要判断是否赢了比赛 
		if (ret != 1)//平局，结束游戏
		{
			break;
		}
		ComputerMove(board, ROW, COL);//电脑下棋
		ShowBoard(board, ROW, COL);//打印棋盘
		ret = IsWin(board, ROW, COL);//每次都要判断是否赢了比赛
		if (ret != 1)//平局，结束游戏
		{
			break;
		}
	}
	if (ret == 'X')//玩家获胜，游戏结束
	{
		printf("玩家获胜\n");
	}
	if (ret == 'Y')//电脑获胜，游戏结束
	{
		printf("电脑获胜\n");
	}
	if (ret == 0)//平局，游戏结束
	{
		printf("平局\n");
	}
}
int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));//产生随机种子
	do
	{
		menu();//打印菜单
		printf("\n请选择你的操作：\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("\n游戏开始！\n");
			game();
			break;
		case 0:
			printf("游戏退出！\n\n");
			break;
		default:
			printf("请输入正确的数字：\n");
			break;
		}
	} while (input);
	return 0;
}
