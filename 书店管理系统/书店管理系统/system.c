#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct book
{
	char index[15];//编号
	char name[20];//书名
	char author[10];//作者
	char pub[20];//出版社
	char pubtime[15];//出版时间
	float price;//价格
	int num;//书籍数量
	char kind[5];//类别
}Book;

void login()			//登录
{
	int i=5;
	char pwin[17], pw[17];
	FILE* fp;
	if ((fp = fopen("password.txt", "r")) == NULL)
	{
		printf("程序错误，即将退出\n");
		exit(1);
	}
	fscanf(fp, "%s", pw);
	printf("请输入管理员密码(初始密码：123456)：");
	while(1)
	{
		scanf("%s", pwin);
		if (strcmp(pwin, pw) == 0)
		{
			printf("密码正确！\n");
			break;
		}
		else
		{
			i--;
			if (i == 0)
				exit(0);
			else
				printf("密码错误，请重新输入(再输入错误%d次后将退出程序):", i);
		}
	}
	fclose(fp);
}

void wSave(Book bok[], int n)                //覆盖保存信息
{
	int i;
	FILE* fp;
	if ((fp = fopen("书店管理系统.txt", "w")) == NULL)
	{
		printf("程序错误，即将退出\n");
		exit(1);
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%s %s %s %s %s %.2f %d %s\n",
			bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
	}
	fclose(fp);
}

void aSave(Book bok[],int n)                //追加保存信息
{
	int i;
	FILE* fp;
	if ((fp = fopen("书店管理系统.txt", "a")) == NULL)
	{
		printf("程序错误，即将退出\n");
		exit(1);
	}
	for(i=0;i<n;i++)
	{
		fprintf(fp, "%s %s %s %s %s %.2f %d %s\n",
			bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
	}
	fclose(fp);
}

int Booknum()                              //查询文件里有几本书
{
	char a;
	int i = 0;
	FILE* fp;
	if ((fp = fopen("书店管理系统.txt", "r")) == NULL)
	{
		printf("程序错误，即将退出\n");
		exit(1);
	}
	while ((a = fgetc(fp))!=EOF)
	{
		if (a == '\n')
			i++;
	}
	fclose(fp);
	return i;
}

void Open(Book* bok,int n)                         //获取文件信息,并将其以编号从小到大排序，返回值为数组指针
{
	int i;
	FILE* fp;
	if ((fp = fopen("书店管理系统.txt", "r")) == NULL)
	{
		printf("程序错误，即将退出\n");
		exit(1);
	}
	for (i = 0; i < n; i++)
		fscanf(fp, "%s%s%s%s%s%f%d%s",
			bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, &bok[i].price, &bok[i].num, bok[i].kind);
	fclose(fp);
}

void Input()    //录入书籍
{
	char index1[15];
	int i=0,n,j,flag=0;
	Book * bok,*fbok;
	char a;
	FILE* fp;
	n = Booknum();
	fbok = (Book*)malloc(n * sizeof(Book));
	Open(fbok, n);
	printf("-------------------------\n");
	printf("        书籍信息录入     \n");
	printf("-------------------------\n");
	printf("请依次输入所要录入书籍的以下信息\n");
	bok = (Book*)malloc(sizeof(Book));
	while(1)
	{
		flag = 0;
		bok = (Book*)realloc(bok, (i + 1) * sizeof(Book));
		printf("编号：");
		scanf("%s", index1);
		for (j = 0; j < i; j++)
			if (strcmp(index1, bok[j].index) == 0)
			{
				printf("该编号已存在，请检查编号是否正确");
				flag = 1;
			}
		for (j = 0; j < n; j++)
			if (strcmp(index1, fbok[j].index) == 0)
			{
				printf("该编号已存在，请检查编号是否正确\n");
				flag = 1;
			}
		if(flag==0)
		{
			strcpy(bok[i].index, index1);
			printf("书名：");
			scanf("%s", bok[i].name);
			printf("作者：");
			scanf("%s", bok[i].author);
			printf("出版社：");
			scanf("%s", bok[i].pub);
			printf("出版时间：");
			scanf("%s", bok[i].pubtime);
			printf("价格：");
			scanf("%f", &bok[i].price);
			printf("书籍数量：");
			scanf("%d", &bok[i].num);
			printf("类别：");
			scanf("%s", bok[i].kind);
			i++;
			printf("录入成功！\n");
		}
		printf("输入‘1’继续录入,输入‘0’返回主菜单，输入其他字符退出程序：");
		while ((a = getchar()) == '\n');
		if (a == '0')
		{
			aSave(bok,i);
			free(bok);
			break;
		}
		else if (a != '1')
		{
			aSave(bok,i);
			exit(0);
		}
	}
}

void Look()    //浏览书籍
{
	int i, n, j, a, b;
	Book* bok, bk;
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	printf("------------------------------------以下为本店书籍信息-----------------------------------------------\n");
	printf("编号\t书名\t\t\t作者\t\t出版社\t\t\t出版时间\t价格\t数量\t类别\n");
	for (i = 0; i < n; i++)
		printf("%-8s%-24s%-16s%-24s%-16s%-8.2f%-8d%s\n",
			bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
	printf("-----------------------------------------------------------------------------------------------------\n");
	free(bok);
}

void Delete()  //删除书籍
{
	char a;
	int i, n;
	Book* bok;
	char index1[15];
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	printf("-------------------------\n");
	printf("        书籍信息删除     \n");
	printf("-------------------------\n");
	while(1)
	{
		printf("请输入你想删除书籍的编号：");
		scanf("%s", index1);
		for (i = 0; i < n; i++)
		{
			if (strcmp(index1, bok[i].index)==0)
			{
				printf("---------------------------------------以下是此书的信息----------------------------------------\n");
				printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
					bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
				printf("-----------------------------------------------------------------------------------------------\n");
				printf("是否确认删除?“Y/N”：");
				while ((a = getchar()) == '\n');
				if (a == 'Y')
				{
					for (i++; i < n; i++)
						bok[i - 1] = bok[i];
					wSave(bok, n - 1);
					n--;
					printf("删除成功！\n");
				}
				break;
			}
			if (i == n - 1)
				printf("没有找到该编号，请检查输入编号是否正确。\n");
		}
		printf("输入‘1’继续删除,输入‘0’返回主菜单，输入其他字符退出程序：");
		while ((a = getchar()) == '\n');
		if (a == '0')
		{
			free(bok);
			break;
		}
		else if (a != '1')
		{
			exit(0);
		}
	}
}

void Find()    //查询书籍
{
	int min, max;
	float fmin, fmax;
	int i, n,j;
	Book* bok,bk;
	int a;
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	while(1)
	{
		printf("---------------------------\n");
		printf("           书籍查询        \n");
		printf("---------------------------\n");
		printf("          1.查询编号       \n");
		printf("          2.查询书名       \n");
		printf("          3.查询作者       \n");
		printf("          4.查询出版社     \n");
		printf("          5.查询价格       \n");
		printf("          6.查询类别       \n");
		printf("          7.查询数量       \n");
		printf("          0.取消查询       \n");
		printf("---------------------------\n");
		printf("请选择你要查询的信息(1-7)：");
		scanf("%d", &a);
		if (a == 0)
			break;
		switch (a)
		{
		case 1:
			printf("请输入所要查询的编号：");
			scanf("%s", bk.index);
			printf("----------------------------------------------以下是搜索结果-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.index, bok[i].index) == 0)
				{
					printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                很抱歉，没有找到你所查询的书籍。                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 2:
			printf("请输入所要查询的书名：");
			scanf("%s", bk.name);
			printf("----------------------------------------------以下是搜索结果-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.name, bok[i].name) == 0)
				{
					printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                很抱歉，没有找到你所查询的书籍。                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 3:
			printf("请输入所要查询的作者：");
			scanf("%s", bk.author);
			printf("----------------------------------------------以下是搜索结果-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.author, bok[i].author) == 0)
				{
					printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                很抱歉，没有找到你所查询的书籍。                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 4:
			printf("请输入所要查询的出版社：");
			scanf("%s", bk.pub);
			printf("----------------------------------------------以下是搜索结果-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.pub, bok[i].pub) == 0)
				{
					printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                很抱歉，没有找到你所查询的书籍。                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 5:
			printf("请输入所要查询的价格区间：>=");
			scanf("%f", &fmin);
			printf("                          <=");
			scanf("%f", &fmax);
			printf("----------------------------------------------以下是搜索结果-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (bok[i].price >= fmin && bok[i].price <= fmax)
				{
					printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                很抱歉，没有找到你所查询的书籍。                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 6:
			printf("请输入所要查询的类别：");
			scanf("%s", bk.kind);
			printf("----------------------------------------------以下是搜索结果-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.kind, bok[i].kind) == 0)
				{
					printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                很抱歉，没有找到你所查询的书籍。                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 7:
			printf("请输入所要查询的数量区间：>=");
			scanf("%d", &min);
			printf("                          <=");
			scanf("%d", &max);
			printf("----------------------------------------------以下是搜索结果-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (bok[i].num >= min && bok[i].num <= max)
				{
					printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                很抱歉，没有找到你所查询的书籍。                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		default:break;
		}
		printf("输入‘1’继续查询,输入‘0’返回主菜单，输入其他字符退出程序：");
		while ((a = getchar()) == '\n');
		if (a == '0')
		{
			free(bok);
			break;
		}
		else if (a != '1')
		{
			exit(0);
		}
	}
}

void Change()  //修改书籍信息
{
	int a,j;
	char index1[15];
	int i, n;
	Book* bok;
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	printf("---------------------------\n");
	printf("         书籍信息修改       \n");
	printf("---------------------------\n");
	while(1)
	{
		printf("请输入所要修改书籍的编号：");
		scanf("%s", index1);
		for (i = 0,j=0; i < n; i++)
			if (strcmp(index1, bok[i].index) == 0)                                                                               //找到所要修改的书
			{
				j++;
				while (1)
				{
					printf("---------------------------------------以下是此书的信息----------------------------------------\n");
					printf("编号：%s，书名：%s，作者：%s，出版社：%s，出版时间：%s，价格：%.2f，书籍数量：%d，类别：%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					printf("-----------------------------------------------------------------------------------------------\n");
					printf("---------------------------\n");
					printf("          1.书名           \n");
					printf("          2.作者           \n");
					printf("          3.出版社         \n");
					printf("          4.出版时间       \n");
					printf("          5.价格           \n");
					printf("          6.数量           \n");
					printf("          7.类别           \n");
					printf("          0.取消修改       \n");
					printf("---------------------------\n");
					printf("请输入你要修改的信息：");
					scanf("%d", &a);
					if (a == 0)
						break;
					switch (a)
					{
					case 1:
						printf("请输入你想要修改成的信息：");
						scanf("%s", bok[i].name);
						printf("修改成功！");
						break;
					case 2:
						printf("请输入你想要修改成的信息：");
						scanf("%s", bok[i].author);
						printf("修改成功！");
						break;
					case 3:
						printf("请输入你想要修改成的信息：");
						scanf("%s", bok[i].pub);
						printf("修改成功！");
						break;
					case 4:
						printf("请输入你想要修改成的信息：");
						scanf("%s", bok[i].pubtime);
						printf("修改成功！");
						break;
					case 5:
						printf("请输入你想要修改成的信息：");
						scanf("%f", &bok[i].price);
						printf("修改成功！");
						break;
					case 6:
						printf("请输入你想要修改成的信息：");
						scanf("%d", &bok[i].num);
						printf("修改成功！");
						break;
					case 7:
						printf("请输入你想要修改成的信息：");
						scanf("%s", bok[i].kind);
						printf("修改成功！");
						break;
					default:break;
					}
					printf("输入‘1’继续修改此书,输入‘0’退回上一级，输入其他字符退出程序：");
					while ((a = getchar()) == '\n');
					if (a == '0')
						break;
					else if (a != '1')
					{
						wSave(bok, n);
						exit(0);
					}
				}
				break;
			}
		if (j == 0)
			printf("抱歉，未能找到您想修改的书籍");
			printf("输入‘1’继续修改其他书籍,输入‘0’返回主菜单，输入其他字符退出程序：");
			while ((a = getchar()) == '\n');
			if (a == '0')
			{
				wSave(bok, n);
				break;
			}
			else if (a != '1')
			{
				wSave(bok, n);
				exit(0);
			}
	
	}
}

void order()                 //排序书籍
{
	int i, n, j, a, b;
	Book* bok, bk;
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	while(1)
	{
		printf("---------------------------\n");
		printf("         书籍排序          \n");
		printf("---------------------------\n");
		Look();
		printf("---------------------------\n");
		printf("          1.编号           \n");
		printf("          2.书名           \n");
		printf("          3.作者           \n");
		printf("          4.出版社         \n");
		printf("          5.出版时间       \n");
		printf("          6.价格           \n");
		printf("          7.数量           \n");
		printf("          8.类别           \n");
		printf("          0.取消排序       \n");
		printf("---------------------------\n");
		printf("请选择以哪个信息进行排序(0-8)：");
		scanf("%d",&a);
		if (a == 0)
			break;
		printf("请选择你要排序的方式，“1”为由小到大，“0”为由大到小：");
		scanf("%d",&b);
		switch (a)
		{
		case 1:
			if (b == 1)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].index, bok[j + 1].index) > 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			if (b == 0)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].index, bok[j + 1].index) < 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			break;

		case 2:
			if (b == 1)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].name, bok[j + 1].name) > 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			if (b == 0)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].name, bok[j + 1].name) < 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			break;

		case 3:
			if (b == 1)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].author, bok[j + 1].author) > 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			if (b == 0)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].author, bok[j + 1].author) < 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			break;

		case 4:
			if (b == 1)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].pub, bok[j + 1].pub) > 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			if (b == 0)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].pub, bok[j + 1].pub) < 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			break;

		case 5:
			if (b == 1)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].pubtime, bok[j + 1].pubtime) > 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			if (b == 0)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].pubtime, bok[j + 1].pubtime) < 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			break;

		case 6:
			if (b == 1)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (bok[j].price > bok[j + 1].price)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			if (b == 0)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (bok[j].price < bok[j + 1].price)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			break;

		case 7:
			if (b == 1)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (bok[j].num > bok[j + 1].num)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			if (b == 0)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (bok[j].num < bok[j + 1].num)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			break;

		case 8:
			if (b == 1)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].kind, bok[j + 1].kind) > 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			if (b == 0)
				for (i = 0; i < n - 1; i++)
					for (j = 0; j < n - 1 - i; j++)
						if (strcmp(bok[j].kind, bok[j + 1].kind) < 0)
						{
							bk = bok[j];
							bok[j] = bok[j + 1];
							bok[j + 1] = bk;
						}
			break;

		default:break;
		}
		wSave(bok, n);
		printf("排序成功！\n");
		Look();
		printf("输入‘1’重新排序,输入‘0’返回主菜单，输入其他字符退出程序：");
		while ((a = getchar()) == '\n');
		if (a == '0')
		{
			break;
		}
		else if (a != '1')
		{
			exit(0);
		}
	}
}

void password(char pwin[]) //密码输入函数
{
	int i=0;
	char a;
	while ((a = getchar()) == '\n');               //吃回车
	while (1)
	{
		if (('a' <= a && a <= 'z') || ('A' <= a && a <= 'Z') || ('0' <= a&&a <= '9'))
		{
			pwin[i] = a;
			a = getchar();
			i++;
			if (i == 16&&a!='\n')
			{
				while (a != '\n')                  //清空缓冲区
					a = getchar();
				printf("字符数太多，请重新输入：");
				i = 0;
				a = getchar();
			}
			else if (a == '\n' && i >= 6)
				break;
		}
		else if (a == '\n')
		{
			printf("字符数太少，请重新输入：");
			i = 0;
			a = getchar();
		}
		else
		{
			printf("有未知字符，请重新输入：");
			while ((a = getchar()) != '\n');            //把回车前的字符全部吃掉
			i = 0;
			a = getchar();
		}
	}
	pwin[i] = '\0';									//确定字符串的结尾
}

void Setpw()   //修改管理员密码
{
	char pwin1[17],pwin2[17];
	FILE* fp;
	login();
	printf("请输入你要修改的密码(6-16位由字母和数字组成)：");
	while(1)
	{
		password(pwin1);
		printf("请确认你的密码：");
		password(pwin2);
		if (strcmp(pwin1, pwin2) == 0)
		{
			if ((fp = fopen("password.txt", "w")) == NULL)
			{
				printf("程序错误，即将退出\n");
				exit(1);
			}
			fprintf(fp, "%s", pwin1);
			printf("修改成功\n");
			break;
		}
		else
			printf("两次输入不一致，请重新输入:");
	}
	fclose(fp);
}

void menu()    //主菜单
{
	printf("------------------------------\n");
	printf("          书店管理系统        \n");
	printf("------------------------------\n");
	printf("          1.录入书籍          \n");
	printf("          2.删除书籍          \n");
	printf("          3.浏览书籍          \n");
	printf("          4.查询书籍          \n");
	printf("          5.修改书籍信息      \n");
	printf("          6.排序书籍          \n");
	printf("          7.修改管理员密码    \n");
	printf("          0.退出              \n");
	printf("请输入要执行操作的序号：");
}

int main()
{
	login();
	int a = 0;
	while (1)
	{
		menu();                               //打印主页
		scanf("%d", &a);
		while (1)                              //确保输入的是可选选项
		{
			if (a < 0 || a>7)
			{
				printf("该序号不存在，请重新输入;");
				scanf("%d", &a);
			}
			else
				break;
		}
		if (a == 0)                           //a=0，退出程序
			break;
		else
			switch (a)                        //否则进入所选的操作子函数
			{
			case 1:Input(); break;
			case 2:Delete(); break;
			case 3:Look(); break;
			case 4:Find(); break;
			case 5:Change(); break;
			case 6:order(); break;
			case 7:Setpw(); break;
			default:break;
			}
	}
	return 0;
}