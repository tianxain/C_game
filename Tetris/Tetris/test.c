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
��������  ����       ����   ����   ��           ��     ������
			����   ����     ����   ������   ������       ��
*/
static int brickX[7][4] = { {0,1,2,3},{0,1,1,2},{2,1,1,0},{1,1,2,2},{0,0,1,2},{2,2,1,0},{0,1,1,2} };
static int brickY[7][4] = { {0,0,0,0},{0,0,1,1},{0,0,1,1},{0,1,0,1},{0,1,1,1},{0,1,1,1},{0,0,1,0} };

//��ŷ��������
unsigned int x[4];
unsigned int y[4];

//��������

void Welcome();  //��ӭ����
void Display(int binimage[20][10]); //��ʾ��Ϸ���
void GotoXY(int x, int y); //�����λ����
void Pause(); //��ͣ
void Block_Random();  //�������ש��
int move(int offsetX, int offsetY, int binimage[20][10]); //���ƣ����ƣ�����
int rotate(int binImage[20][10]); //��ת����
void output(int binImage[20][10]); //�������ʾ���
unsigned int removeFullLines(); //�ж�һ���Ƿ�����
void copyimage(int destimage[20][10], int sourceimage[20][10]); //��������
int score = 0;//��¼����
int difficulty;//�Ѷ�

int main()
{
	int i = 0;
	int j = 0;
	int gameOver = 0;//��Ϸ�Ƿ����
	int brickInFlight = 0;//ש���Ƿ��ڷ���״̬
	int brickType = 0;//ש�����
	//unsigned int initOrientation;//��ʼ״̬
	int notCollide = 0;//ש���Ƿ��ͻ
	int arrowKey = 0;
	int tempimage[20][10];
	score = 0;
	difficulty = 500;
	for (i = 0; i < 20; i++)  //��ʼ����Ϸ���
	{
		for (j = 0; j < 10; j++)
		{
			image[i][j] = 0;
		}
	}
	for (i = 0; i < 20; i++)  //��ʼ����ʱ��Ϸ���
	{
		for (j = 0; j < 10; j++)
		{
			tempimage[i][j] = 0;
		}
	}
	Welcome();//��ӭ����
	Display(image);//��ʾ��Ϸ����

	//*****��ʼ��Ϸ��********************
	while (!gameOver)
	{
		if (!brickInFlight) //û��ש�����£���Ҫ�½�һ��
		{
			copyimage(tempimage, image);
			Block_Random();
			notCollide = move(10 / 2, 0, image); //����Ƿ��ͻ
			if (notCollide)
			{
				brickInFlight = 1;
				output(tempimage);
				Display(tempimage);
			}
			else //��ͻ���½�ש���Ѿ��Ų��£���Ϸ����
			{
				gameOver = 1;
				brickInFlight = 0;
			}
		}
		else
		{
			//��ǰ��ש���������䣬��Ҫ����û�����
			copyimage(tempimage, image);
			if (_kbhit())//Checks the console for keyboard input.
			{
				arrowKey = getchar();//����û�����
				if (arrowKey == 'd')//����
				{
					notCollide = move(1, 0, image);
				}
				else if (arrowKey == 'a')//����
				{
					notCollide = move(-1, 0, image);
				}
				else if (arrowKey == 'w')//��ת
				{
					notCollide = rotate(image);
				}
				else if (arrowKey == 's')//��������
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
				else if (notCollide == 'p')//��ͣ
				{
					Pause();
				}
				//ש�鿿����
				Sleep(difficulty);
				notCollide = move(0, 1, image);
				if (notCollide)
				{
					output(tempimage);
					Display(tempimage);
				}
				else
				{
					//ש���䵽�ײ����Թ̶�ש���ϣ���������
					brickInFlight = 0;
					output(image);
					Display(tempimage);
					//����Ƿ���Ҫ����һ��
					switch (removeFullLines())//�Ʒַ�ʽ
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
					//������к󣬸���ͼ�����
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
//��ӭ����
void Welcome()
{
	printf("��ӭ��������˹���飡");
	system("pause");
	system("cls\n");
}

//��ʾ��Ϸ���
void Display(int binimage[20][10])
{
	int i, j;
	GotoXY(1, 1);
	for (i = 0; i < 20; i++)
	{
		printf("��");
		for (j = 0; j < 10; j++)
		{
			switch (binimage[i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("��");
				break;
			}
		}
		printf("��");
		for (i = 0; i < 12; i++)
		{
			GotoXY(1, 22);
			printf("SCORE:%d", score);
			GotoXY(1, 23);
			printf("LEVEL=%d", score / 100);
		}
	}

}

//�����λ����
void GotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//��������
void copyimage(int destimage[20][10], int sourceimage[20][10])
{
	int i, j;
	for (i = 0; i < 20; i++)  //��ʼ����Ϸ���
	{
		for (j = 0; j < 10; j++)
		{
			destimage[i][j] = sourceimage[i][j];
		}
	}
}

//�������ש��
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


//���ƣ����ƣ�����
int move(int offsetX, int offsetY, int binimage[20][10])
{
	int i;
	int X[4], Y[4];
	for (i = 0; i < 4; i++)
	{
		X[i] = x[i] + offsetX;
		Y[i] = y[i] + offsetY;
		if (X[i] < 0 || X[i] >= 10 || y[i] < 0 || y[i] >= 20)//�ж��ܷ��ƶ��ɹ�
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

//�������ʾ���
void output(int binImage[20][10])
{
	int i;
	for (i = 0; i < 4; i++)
	{
		binImage[y[i]][x[i]] = 1;
	}
}

//��ת����
int rotate(int binImage[20][10])
{
	int i;
	int xt[4], yt[4];
	for (i = 0; i < 4; i++)
	{
		xt[i] = y[i] + x[1] - y[1];
		yt[i] = x[i] + y[1] - x[1];
		if (xt[i] < 0 || xt[i] >= 10 || yt[i] < 0 || yt[i] >= 20)//�ж��ܷ��ƶ��ɹ�
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

//��ͣ
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
//�ж�һ���Ƿ�����
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
			//һ�б�����
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