#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
int r = 0;
int p = 0;
int q = 0;
int speed = 25;
int image[20][10];
/*
■■■■  ■■       ■■   ■■   ■           ■     ■■■
			■■   ■■     ■■   ■■■   ■■■       ■
*/
static int brickX[7][4] = { {0,1,2,3},{0,1,1,2},{2,1,1,0},{1,1,2,2},{0,0,1,2},{2,2,1,0},{0,1,1,2} };
static int brickY[7][4] = { {0,0,0,0},{0,0,1,1},{0,0,1,1},{0,1,0,1},{0,1,1,1},{0,1,1,1},{0,0,1,0} };

//存放方块的坐标
unsigned int x[4];
unsigned int y[4];

//函数声明

void Welcome();  //欢迎界面
void Display(int binimage[20][10]); //显示游戏面板
void GotoXY(int x, int y); //输出定位函数
void Pause(); //暂停
void Block_Random();  //随机生成砖块
int move(int offsetX, int offsetY, int binimage[20][10]); //左移，右移，下移
int rotate(int binImage[20][10]); //旋转函数
void output(int binImage[20][10]); //输出到显示面板
unsigned int removeFullLines(); //判断一行是否填满
void copyimage(int destimage[20][10], int sourceimage[20][10]); //拷贝数组
int score = 0;//记录分数
int difficulty;//难度

int main()
{
	int i = 0;
	int j = 0;
	int gameOver = 0;//游戏是否结束
	int brickInFlight = 0;//砖块是否处于飞行状态
	int brickType = 0;//砖块类别
	//unsigned int initOrientation;//初始状态
	int notCollide = 0;//砖块是否冲突
	int arrowKey = 0;
	int tempimage[20][10];
	score = 0;
	difficulty = 500;
	for (i = 0; i < 20; i++)  //初始化游戏面板
	{
		for (j = 0; j < 10; j++)
		{
			image[i][j] = 0;
		}
	}
	for (i = 0; i < 20; i++)  //初始化临时游戏面板
	{
		for (j = 0; j < 10; j++)
		{
			tempimage[i][j] = 0;
		}
	}
	Welcome();//欢迎界面
	Display(image);//显示游戏界面

	//*****开始游戏！********************
	while (!gameOver)
	{
		if (!brickInFlight) //没有砖块落下，需要新建一个
		{
			copyimage(tempimage, image);
			Block_Random();
			notCollide = move(10 / 2, 0, image); //检查是否冲突
			if (notCollide)
			{
				brickInFlight = 1;
				output(tempimage);
				Display(tempimage);
			}
			else //冲突，新建砖块已经放不下，游戏结束
			{
				gameOver = 1;
				brickInFlight = 0;
			}
		}
		else
		{
			//当前有砖块正在下落，需要检测用户按键
			copyimage(tempimage, image);
			if (_kbhit())//Checks the console for keyboard input.
			{
				arrowKey = getchar();//检查用户输入
				if (arrowKey == 'd')//右移
				{
					notCollide = move(1, 0, image);
				}
				else if (arrowKey == 'a')//左移
				{
					notCollide = move(-1, 0, image);
				}
				else if (arrowKey == 'w')//旋转
				{
					notCollide = rotate(image);
				}
				else if (arrowKey == 's')//加速下落
				{
					notCollide = move(0, 1, image);
					while (notCollide)
					{
						notCollide = move(0, 1, image);
						if (notCollide)
						{
							output(tempimage);
							Display(tempimage);
						}
						copyimage(tempimage, image);
					}
				}
				else if (notCollide == 'p')//暂停
				{
					Pause();
				}
				//砖块靠重力
				Sleep(difficulty);
				notCollide = move(0, 1, image);
				if (notCollide)
				{
					output(tempimage);
					Display(tempimage);
				}
				else
				{
					//砖块落到底部或以固定砖块上，不再下落
					brickInFlight = 0;
					output(image);
					Display(tempimage);
					//检查是否需要消除一行
					switch (removeFullLines())//计分方式
					{
					case 1: score++;
						break;
					case 2: score += 3;;
						break;
					case 3: score += 5;
						break;
					case 4: score += 8;
						break;
					/*default:
						break;*/
					}
					switch (score/100)
					{
					case 0: difficulty = 500; break;
					case 1: difficulty = 200; break;
					case 2: difficulty = 170; break;
					case 3: difficulty = 150; break;
					case 4: difficulty = 120; break;
					case 5: difficulty = 100; break;
					case 6: difficulty = 70; break;
					case 7: difficulty = 50; break;
					case 8: difficulty = 20; break;
					case 9: difficulty = 10; break;
					}
					//检查消行后，更行图像面板
					copyimage(tempimage,image);
				}
				Display(tempimage);
			}
		}
		GotoXY(1,24);
		printf("Game Over !");
		getchar();
	}
	return 0;
}
//欢迎界面
void Welcome()
{
	printf("欢迎来到俄罗斯方块！");
	system("pause");
	system("cls\n");
}

//显示游戏面板
void Display(int binimage[20][10])
{
	int i, j;
	GotoXY(1, 1);
	for (i = 0; i < 20; i++)
	{
		printf("■");
		for (j = 0; j < 10; j++)
		{
			switch (binimage[i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("■");
				break;
			}
		}
		printf("■");
		for (i = 0; i < 12; i++)
		{
			GotoXY(1, 22);
			printf("SCORE:%d", score);
			GotoXY(1, 23);
			printf("LEVEL=%d", score / 100);
		}
	}

}

//输出定位函数
void GotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//拷贝数组
void copyimage(int destimage[20][10], int sourceimage[20][10])
{
	int i, j;
	for (i = 0; i < 20; i++)  //初始化游戏面板
	{
		for (j = 0; j < 10; j++)
		{
			destimage[i][j] = sourceimage[i][j];
		}
	}
}

//随机生成砖块
void Block_Random()
{
	int k, i;
	k = (rand() % 7);
	for (i = 0; i < 4; i++)
	{
		x[i] = brickX[k][i];
		y[i] = brickY[k][i];
	}
}


//左移，右移，下移
int move(int offsetX, int offsetY, int binimage[20][10])
{
	int i;
	int X[4], Y[4];
	for (i = 0; i < 4; i++)
	{
		X[i] = x[i] + offsetX;
		Y[i] = y[i] + offsetY;
		if (X[i] < 0 || X[i] >= 10 || y[i] < 0 || y[i] >= 20)//判断能否移动成功
		{
			return 0;
		}
		if (binimage[Y[i]][X[i]] != 0)
		{
			return 0;
		}
	}
	for (i = 0; i < 4; i++)
	{
		x[i] = X[i];
		y[i] = Y[i];
	}
	return 1;
}

//输出到显示面板
void output(int binImage[20][10])
{
	int i;
	for (i = 0; i < 4; i++)
	{
		binImage[y[i]][x[i]] = 1;
	}
}

//旋转函数
int rotate(int binImage[20][10])
{
	int i;
	int xt[4], yt[4];
	for (i = 0; i < 4; i++)
	{
		xt[i] = y[i] + x[1] - y[1];
		yt[i] = x[i] + y[1] - x[1];
		if (xt[i] < 0 || xt[i] >= 10 || yt[i] < 0 || yt[i] >= 20)//判断能否移动成功
		{
			return 0;
		}
		if (binImage[yt[i]][xt[i]] != 0)
		{
			return 0;
		}
	}
	for (i = 0; i < 4; i++)
	{
		x[i] = xt[i];
		y[i] = yt[i];
	}
	return 1;
}

//暂停
void Pause()
{
	char c;
	GotoXY(1, 23);
	printf("pause!");
	do
	{
		c = getchar();
	} while (c != 'p');
}
//判断一行是否填满
unsigned int removeFullLines()
{
	unsigned int flag, EmptyLine = 0;
	unsigned int i, j, m;
	for (i = 0; i < 20; i++)
	{
		flag = 0;
		for (j = 0; j < 10; j++)
		{
			if (image[i][j] == 0)
			{
				flag = 1;
			}
			//一行被填满
			if (flag == 0)
			{
				for (m = i; m > 0; m--)
				{
					for (j = 0; j < 10; j++)
					{
						image[m][j] = image[m - 1][j];
					}
				}
			}
			for (j = 0; j < 10; j++)
			{
				image[0][j] = 0;
			}
			EmptyLine++;
			i--;

		}
	}
	return EmptyLine;
}