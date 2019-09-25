#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

//初始化棋盘
void InitBoard(char board[][ROW], int row, int col)
{
	//int i = 0;
	//int j = 0;
	//for (i = 0; i < row; i++)
	//{
	//	for (j = 0; j < col; j++)
	//	{
	//		board[i][j] = ' ';
	//	}
	//}
	memset(board, ' ', row*col * sizeof(char));//将数组初始化为0

}

//打印棋盘
void ShowBoard(char board[][ROW], int row, int col)
{
	printf("\n");
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			printf("|");
		}
		printf("\n");
		if (i < row - 1)
		{
			for (j = 0; j < col; j++)
			{
				printf("___");
				printf("|");
			}
		}
		else
		{
			for (j = 0; j < col; j++)
			{
				printf("   |");
			}
		}
		printf("\n");
	}
	printf("\n");
}

//玩家移动
void PlayerMove(char board[][ROW], int row, int col)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("玩家下棋！\n");
		printf("请输入您下的位置(1-3)：\n");
		scanf("%d%d", &x, &y);
		if (x > 0 && x < 4 && y>0 && y < 4)//判断输入的位置是否合法
		{
			if (board[x - 1][y - 1] == ' ')//判断该位置是否有棋子
			{
				board[x - 1][y - 1] = 'X';
				break;
			}
			else
			{
				printf("该位置已有棋子！\n");
			}
		}
		else
		{
			printf("输入不合法！");
		}
	}
}

//电脑移动
void ComputerMove(char board[][ROW], int row, int col)
{
	int x = 0;
	int y = 0;
	printf("电脑下棋！\n");
	while (1)
	{
		x = rand() % row;//产生随机坐标
		y = rand() % col;
		if (board[x][y] == ' ')//判断该位置是否有棋子
		{
			board[x][y] = 'Y';
			break;
		}
	}
}

//判断输赢
int IsWin(char board[][ROW], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		//横向判断
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
		{
			return board[i][0];
		}

		//纵向判断
		else if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
		{
			return board[0][i];
		}

		//左对角线判断
		else if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
		{
			return board[1][1];
		}

		//右对角线判断
		else if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
		{
			return board[1][1];
		}

		//判断棋盘是否放满
		else if (IsFull(board, row, col == 1))
		{
			return 0;
		}
	}
	return 1;

}

//判断棋盘是否放满
int IsFull(char board[][ROW], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			//遇到空格即表示棋盘没满，返回0
			if (board[i][j == ' '])
			{
				return 1;
			}
		}
	}
	return 0;//表示棋盘已放满棋子
}