/******************************************************
文件名称: 源.cpp
实现功能: 鼠标点击拼图游戏
编译环境: vs2015,esayX图形库
创建日期: 2017年6月5日      by--《小念》
*********************************************************/


#include<Windows.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>//kbhit判断有无键盘输入  _getch获取键盘输入
#include<time.h>
//#include"resource.h"

//************ 宏定义部分 *****************************

#define WINDOW_WIDTH        360           //窗口宽度
#define WINDOW_HEIGHT       480           //窗口高度
#define ROW    3                          //数组下标
#define COL    4                          //数组下标

#define img_sizeC    (WINDOW_HEIGHT/COL)  //  480 / 4 = 120
int map[ROW][COL];

//***************** 函数声明部分 **********************


void cutimage(IMAGE img, IMAGE image[12]);
void messup();
void draw(IMAGE image[12]);
void playgame();

//************ 主函数入口 ******************************
int main() {
	IMAGE img;                  //保存原图片变量
	IMAGE image[12];            //保存切割图片变量
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  //窗口大小
	setbkcolor(WHITE);          //用白色刷新背景屏幕,参数可换其他颜色英文大写
	srand((unsigned)time(NULL)); //播下随机数种子
	int k = 0;
	k = rand() % 4 + 101;    //随机取得系统分配的图片内存地址, 
	loadimage(&img, L"JPG", MAKEINTRESOURCE(k), WINDOW_WIDTH, WINDOW_HEIGHT);    //随机从资源文件载入原图
	messup();
	cutimage(img, image);
	while (1)
	{
		draw(image);
		playgame();
	}
	return 0;
}

//*************** 切割图片 ***************************
void cutimage(IMAGE img, IMAGE image[12]) {
	SetWorkingImage(&img);         //加载工作区
	int n = 0;                       //存储变量
	for (int i = 0; i < ROW; i++)  //切图片
	{
		for (int j = 0; j < COL; j++)
		{
			//切割的图片存放在image[0~12] ,切割图片的值按宽120高120比例
			//getimage(&image[ n++], img.getwidth() / 4 * j, img.getheight() / 3 * i, img.getwidth() / 4, img.getheight() / 3);	 //图片要存放的位置  切割的坐标  切割大小
			getimage(&image[n++], img_sizeC * i, img_sizeC * j, img_sizeC, img_sizeC);																													  //图片要存放的位置  切割的坐标  切割大小
		}
	}
	SetWorkingImage(NULL);//关闭工作区
}

//**************** 打乱画图所用的数组map ***************
void messup() {
	int k;   //arr下标
	int size = 12;
	int arr[12];
	//int arr[12];辅助数组{0,1,2,3,4,5,6,7,8,9,10,11}

	for (int i = 0; i < 12; i++) {
		arr[i] = i;
	}
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			k = rand() % size;
			map[i][j] = arr[k];//取出arr数组中第k个元素存放在map数组,且无重复
			for (int j = k; j < size; j++)    //arr[k]后面的元素都往前移动
			{
				arr[j] = arr[j + 1];
			}
			size--;
		}
	}
}

//******************** 画打乱后的图*********************
void draw(IMAGE image[12]) {

	BeginBatchDraw();//缓冲
	cleardevice();//刷新屏幕
				  //数组打乱->贴图  
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//	printf("%d\t",map[i][j]);
			if (map[i][j] == 11) continue;
			putimage(img_sizeC * i, img_sizeC* j, &image[map[i][j]]);
		}   //printf("\n");
	}
	EndBatchDraw();//缓冲结束
}

//********************* 玩游戏**************************
void playgame() {
	//找到未贴图黑色区
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
	msg = GetMouseMsg();//获取鼠标消息
	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN:

		mouseR = msg.x / img_sizeC;
		mouseC = msg.y / img_sizeC;

		//判断空白和点到部分是否相邻, 鼠标位置上、下、左、右与空白相等
		if (map[mouseR - 1][mouseC] == map[blankR][blankC] || map[mouseR + 1][mouseC] == map[blankR][blankC] ||
			map[mouseR][mouseC - 1] == map[blankR][blankC] || map[mouseR][mouseC + 1] == map[blankR][blankC])
		{
			//相邻则点击有效, 交换数组值, 达到移动效果
			map[blankR][blankC] = map[mouseR][mouseC];
			map[mouseR][mouseC] = 11;
			break;
		}
	}
}
