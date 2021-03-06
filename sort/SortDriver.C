#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sorthdr.h"
#include "sortsub.h"

#define _CRT_SECURE_NO_WARNINGS
#define BUFLEN 40

//比较函数
int Compare(Element* a, Element* b) {
	if(a->data > b->data) return 1;
	else if(a->data == b->data) return 0;
	else return -1;
}

//1:冒泡排序
void BubbleSort(Element **Array, int N, CompFunc Compare)
{
	int limit;
	int countCmp=0, countSwap=0;

	/* Make steadily shorter passes ... */
	for (limit = N - 1; limit > 0; limit--)
	{
		int j, swapped;

		/* On each pass, sweep largest element to end of array */
		swapped = 0;
		for (j = 0; j < limit; j++)
		{
			countCmp++;                   //比较次数
			if (Compare(Array[j], Array[j + 1]) > 0)
			{
				Element *temp;

				temp = Array[j];
				Array[j] = Array[j + 1];
				Array[j + 1] = temp;
				swapped = 1;
				countSwap++;              //交换次数
			}
		}
		if (!swapped)
			break; /* if no swaps, we have finished */  //优化
	}

	printf("比较次数：%d,交换次数：%d\n", countCmp, countSwap);
}

//2:插入排序
void InsertionSort(Element **Array, int N, CompFunc Compare)
{
	int step;
	int countCmp = 0;
	float  countSwap = 0;

	/* Look at 2nd thru Nth elements, putting each in place */
	for (step = 1; step < N; step++)
	{
		int i;
		Element *temp;

		/* Now, look to the left and find our spot */
		temp = Array[step];
		for (i = step - 1; i >= 0; i--)
		{
			countCmp++;
			if (Compare(Array[i], temp) > 0)
			{
				/* Not there yet, so make room */
 				Array[i + 1] = Array[i];
				countSwap += (1.0)/3;       //移动算做1/3次
			}
			else /* Found it! */
				break;
		}
		/* Now insert original value from Array[step] */
		Array[i + 1] = temp;
	}
	countSwap += (2.0)/3;

	printf("比较次数：%d,交换次数：%d\n", countCmp, (int)countSwap);
}



//3:希尔排序
void ShellSort(Element **Array, int N, CompFunc Compare)
{
	int step, h;
	int countCmp = 0;
	float countSwap = 0;

	/* Find starting h */
	for (h = 1; h <= N / 9; h = 3 * h + 1)
		;

	/* Now loop thru successively smaller h's */
	for (; h > 0; h /= 3)
	{
		/* Look at hth thru Nth elements */
		for (step = h; step < N; step++)
		{
			int i;
			Element *temp;

			/* Now, look to the left and find our spot */
			temp = Array[step];
			for (i = step - h; i >= 0; i -= h)
			{
				countCmp++;     //比较次数
				if (Compare(temp, Array[i]) < 0)
				{
					/* Not there yet, so make room */
					Array[i + h] = Array[i];
					countSwap += (1.0) / 3;        //移动算为1/3次交换
				}
				else /* Found it! */
					break;
			}
			/* Now insert original value from Array[step] */
			Array[i + h] = temp;
		}
	}
	countSwap += (2.0)/ 3;
	printf("比较次数：%d,交换次数：%d\n", countCmp, (int)countSwap);
}


//4:直接选择排序
void SelectSort(Element **Array, int N, CompFunc Compare) {

	int i, j, k;
	int countCmp = 0, countSwap = 0;
	Element *temp;
	for (i = 0; i < N-1; i++) {    //进行n-1趟排序，每趟选出1个最小记录
		k = i;                      //假定起始位置为最小记录的位置
		for (j = i + 1; j < N; j++) {    //查找最小记录
			countCmp++;
			if (Compare(Array[j], Array[k]) < 0)     //记录最小值位置
				k = j;
		}
		if (i != k){        //如果k不是假定位置，则交换
		temp = Array[k];     //交换记录
		Array[k] = Array[i];
		Array[i] = temp;
		countSwap++;
		}
	}

	printf("比较次数：%d,交换次数：%d\n", countCmp, countSwap);
}

void main(int argc, char **argv){
	Element **Array;
	int Items = 2000;
	char inbuf[BUFLEN],*s;
	for (;;) {
		fputs("Action (? for help): ", stdout);
		fflush(stdout);
		fgets(inbuf, BUFLEN, stdin);
		s = inbuf + strlen(inbuf);
		while (iscntrl(*s)) *s-- = '\0';

		switch (inbuf[0]) {
		case '?':
			fputs(
				"---------输入数字(1~4)@文件名----------\n"
				"---------1:对指定文件冒泡排序----------\n"
				"---------2:对指定文件插入排序----------\n"
				"---------3:对指定文件希尔排序----------\n"
				"---------4:对指定文件选择排序----------\n"
				"---------输入5自动测试所有文件---------\n"
				"---------输入q退出程序-----------------\n"
				, stdout);
			fflush(stdout);
			break;

		case '1':   //冒泡排序

			if ((Items = LoadArray(inbuf+2, Items, &Array)) == -1)
				return; /* Couldn't load file */

			BubbleSort(Array, Items, (CompFunc)Compare);
			break;

		case '2':   //插入排序

			if ((Items = LoadArray(inbuf + 2, Items, &Array)) == -1)
				return; /* Couldn't load file */

			InsertionSort(Array, Items, (CompFunc)Compare);
			break;

		case '3':   //希尔排序
			
			if ((Items = LoadArray(inbuf + 2, Items, &Array)) == -1)
					return; /* Couldn't load file */

			ShellSort(Array, Items, (CompFunc)Compare);
			break;
		case '4':     //选择排序
			if ((Items = LoadArray(inbuf + 2, Items, &Array)) == -1)
				return; /* Couldn't load file */

			SelectSort(Array, Items, (CompFunc)Compare);

			break;
		case '5':   //对所有文件进行测试
			printf("\n\nBubbleSort:\n\n");
			printf("TestData1：\n");
			Items = LoadArray("TestData1.txt", Items, &Array);
			BubbleSort(Array, Items, (CompFunc)Compare);
			printf("TestData2：\n");
			Items = LoadArray("TestData2.txt", Items, &Array);
			BubbleSort(Array, Items, (CompFunc)Compare);
			printf("TestData3：\n");
			Items = LoadArray("TestData3.txt", Items, &Array);
			BubbleSort(Array, Items, (CompFunc)Compare);
			printf("TestData4：\n");
			Items = LoadArray("TestData4.txt", Items, &Array);
			BubbleSort(Array, Items, (CompFunc)Compare);
			printf("TestData5：\n");
			Items = LoadArray("TestData5.txt", Items, &Array);
			BubbleSort(Array, Items, (CompFunc)Compare);


			printf("\n\nInsertionSort:\n\n");
			printf("TestData1：\n");
			Items = LoadArray("TestData1.txt", Items, &Array);
			InsertionSort(Array, Items, (CompFunc)Compare);
			printf("TestData2：\n");
			Items = LoadArray("TestData2.txt", Items, &Array);
			InsertionSort(Array, Items, (CompFunc)Compare);
			printf("TestData3：\n");
			Items = LoadArray("TestData3.txt", Items, &Array);
			InsertionSort(Array, Items, (CompFunc)Compare);
			printf("TestData4：\n");
			Items = LoadArray("TestData4.txt", Items, &Array);
			InsertionSort(Array, Items, (CompFunc)Compare);
			printf("TestData5：\n");
			Items = LoadArray("TestData5.txt", Items, &Array);
			InsertionSort(Array, Items, (CompFunc)Compare);


			printf("\n\nShellSort:\n\n");
			printf("TestData1：\n");
			Items = LoadArray("TestData1.txt", Items, &Array);
			ShellSort(Array, Items, (CompFunc)Compare);
			printf("TestData2：\n");
			Items = LoadArray("TestData2.txt", Items, &Array);
			ShellSort(Array, Items, (CompFunc)Compare);
			printf("TestData3：\n");
			Items = LoadArray("TestData3.txt", Items, &Array);
			ShellSort(Array, Items, (CompFunc)Compare);
			printf("TestData4：\n");
			Items = LoadArray("TestData4.txt", Items, &Array);
			ShellSort(Array, Items, (CompFunc)Compare);
			printf("TestData5：\n");
			Items = LoadArray("TestData5.txt", Items, &Array);
			ShellSort(Array, Items, (CompFunc)Compare);


			printf("\n\nSelectSort:\n\n");
			printf("TestData1：\n");
			Items = LoadArray("TestData1.txt", Items, &Array);
			SelectSort(Array, Items, (CompFunc)Compare);
			printf("TestData2：\n");
			Items = LoadArray("TestData2.txt", Items, &Array);
			SelectSort(Array, Items, (CompFunc)Compare);
			printf("TestData3：\n");
			Items = LoadArray("TestData3.txt", Items, &Array);
			SelectSort(Array, Items, (CompFunc)Compare);
			printf("TestData4：\n");
			Items = LoadArray("TestData4.txt", Items, &Array);
			SelectSort(Array, Items, (CompFunc)Compare);
			printf("TestData5：\n");
			Items = LoadArray("TestData5.txt", Items, &Array);
			SelectSort(Array, Items, (CompFunc)Compare);

			printf("\n\n");

			break;

		case 'q':   //退出
			return;

		default:    //输入命令错误
			fputs(" Not a valid command\n", stdout);
			break;
		}
	}
}

