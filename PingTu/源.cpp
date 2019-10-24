/******************************************************
�ļ�����: Դ.cpp
ʵ�ֹ���: �����ƴͼ��Ϸ
���뻷��: vs2015,esayXͼ�ο�
��������: 2017��6��5��      by--��С�
*********************************************************/


#include<Windows.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>//kbhit�ж����޼�������  _getch��ȡ��������
#include<time.h>
//#include"resource.h"

//************ �궨�岿�� *****************************

#define WINDOW_WIDTH        360           //���ڿ��
#define WINDOW_HEIGHT       480           //���ڸ߶�
#define ROW    3                          //�����±�
#define COL    4                          //�����±�

#define img_sizeC    (WINDOW_HEIGHT/COL)  //  480 / 4 = 120
int map[ROW][COL];

//***************** ������������ **********************


void cutimage(IMAGE img, IMAGE image[12]);
void messup();
void draw(IMAGE image[12]);
void playgame();

//************ ��������� ******************************
int main() {
	IMAGE img;                  //����ԭͼƬ����
	IMAGE image[12];            //�����и�ͼƬ����
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  //���ڴ�С
	setbkcolor(WHITE);          //�ð�ɫˢ�±�����Ļ,�����ɻ�������ɫӢ�Ĵ�д
	srand((unsigned)time(NULL)); //�������������
	int k = 0;
	k = rand() % 4 + 101;    //���ȡ��ϵͳ�����ͼƬ�ڴ��ַ, 
	loadimage(&img, L"JPG", MAKEINTRESOURCE(k), WINDOW_WIDTH, WINDOW_HEIGHT);    //�������Դ�ļ�����ԭͼ
	messup();
	cutimage(img, image);
	while (1)
	{
		draw(image);
		playgame();
	}
	return 0;
}

//*************** �и�ͼƬ ***************************
void cutimage(IMAGE img, IMAGE image[12]) {
	SetWorkingImage(&img);         //���ع�����
	int n = 0;                       //�洢����
	for (int i = 0; i < ROW; i++)  //��ͼƬ
	{
		for (int j = 0; j < COL; j++)
		{
			//�и��ͼƬ�����image[0~12] ,�и�ͼƬ��ֵ����120��120����
			//getimage(&image[ n++], img.getwidth() / 4 * j, img.getheight() / 3 * i, img.getwidth() / 4, img.getheight() / 3);	 //ͼƬҪ��ŵ�λ��  �и������  �и��С
			getimage(&image[n++], img_sizeC * i, img_sizeC * j, img_sizeC, img_sizeC);																													  //ͼƬҪ��ŵ�λ��  �и������  �и��С
		}
	}
	SetWorkingImage(NULL);//�رչ�����
}

//**************** ���һ�ͼ���õ�����map ***************
void messup() {
	int k;   //arr�±�
	int size = 12;
	int arr[12];
	//int arr[12];��������{0,1,2,3,4,5,6,7,8,9,10,11}

	for (int i = 0; i < 12; i++) {
		arr[i] = i;
	}
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			k = rand() % size;
			map[i][j] = arr[k];//ȡ��arr�����е�k��Ԫ�ش����map����,�����ظ�
			for (int j = k; j < size; j++)    //arr[k]�����Ԫ�ض���ǰ�ƶ�
			{
				arr[j] = arr[j + 1];
			}
			size--;
		}
	}
}

//******************** �����Һ��ͼ*********************
void draw(IMAGE image[12]) {

	BeginBatchDraw();//����
	cleardevice();//ˢ����Ļ
				  //�������->��ͼ  
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//	printf("%d\t",map[i][j]);
			if (map[i][j] == 11) continue;
			putimage(img_sizeC * i, img_sizeC* j, &image[map[i][j]]);
		}   //printf("\n");
	}
	EndBatchDraw();//�������
}

//********************* ����Ϸ**************************
void playgame() {
	//�ҵ�δ��ͼ��ɫ��
	int i, j;
	int mouseR, mouseC;
	int blankR, blankC;
	MOUSEMSG msg = { 0 };
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (map[i][j] == 11)
			{
				blankR = i;
				blankC = j;
			}
		}
	}
	msg = GetMouseMsg();//��ȡ�����Ϣ
	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN:

		mouseR = msg.x / img_sizeC;
		mouseC = msg.y / img_sizeC;

		//�жϿհ׺͵㵽�����Ƿ�����, ���λ���ϡ��¡�������հ����
		if (map[mouseR - 1][mouseC] == map[blankR][blankC] || map[mouseR + 1][mouseC] == map[blankR][blankC] ||
			map[mouseR][mouseC - 1] == map[blankR][blankC] || map[mouseR][mouseC + 1] == map[blankR][blankC])
		{
			//����������Ч, ��������ֵ, �ﵽ�ƶ�Ч��
			map[blankR][blankC] = map[mouseR][mouseC];
			map[mouseR][mouseC] = 11;
			break;
		}
	}
}
