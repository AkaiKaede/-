#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct book
{
	char index[15];//���
	char name[20];//����
	char author[10];//����
	char pub[20];//������
	char pubtime[15];//����ʱ��
	float price;//�۸�
	int num;//�鼮����
	char kind[5];//���
}Book;

void login()			//��¼
{
	int i=5;
	char pwin[17], pw[17];
	FILE* fp;
	if ((fp = fopen("password.txt", "r")) == NULL)
	{
		printf("������󣬼����˳�\n");
		exit(1);
	}
	fscanf(fp, "%s", pw);
	printf("���������Ա����(��ʼ���룺123456)��");
	while(1)
	{
		scanf("%s", pwin);
		if (strcmp(pwin, pw) == 0)
		{
			printf("������ȷ��\n");
			break;
		}
		else
		{
			i--;
			if (i == 0)
				exit(0);
			else
				printf("�����������������(���������%d�κ��˳�����):", i);
		}
	}
	fclose(fp);
}

void wSave(Book bok[], int n)                //���Ǳ�����Ϣ
{
	int i;
	FILE* fp;
	if ((fp = fopen("������ϵͳ.txt", "w")) == NULL)
	{
		printf("������󣬼����˳�\n");
		exit(1);
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%s %s %s %s %s %.2f %d %s\n",
			bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
	}
	fclose(fp);
}

void aSave(Book bok[],int n)                //׷�ӱ�����Ϣ
{
	int i;
	FILE* fp;
	if ((fp = fopen("������ϵͳ.txt", "a")) == NULL)
	{
		printf("������󣬼����˳�\n");
		exit(1);
	}
	for(i=0;i<n;i++)
	{
		fprintf(fp, "%s %s %s %s %s %.2f %d %s\n",
			bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
	}
	fclose(fp);
}

int Booknum()                              //��ѯ�ļ����м�����
{
	char a;
	int i = 0;
	FILE* fp;
	if ((fp = fopen("������ϵͳ.txt", "r")) == NULL)
	{
		printf("������󣬼����˳�\n");
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

void Open(Book* bok,int n)                         //��ȡ�ļ���Ϣ,�������Ա�Ŵ�С�������򣬷���ֵΪ����ָ��
{
	int i;
	FILE* fp;
	if ((fp = fopen("������ϵͳ.txt", "r")) == NULL)
	{
		printf("������󣬼����˳�\n");
		exit(1);
	}
	for (i = 0; i < n; i++)
		fscanf(fp, "%s%s%s%s%s%f%d%s",
			bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, &bok[i].price, &bok[i].num, bok[i].kind);
	fclose(fp);
}

void Input()    //¼���鼮
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
	printf("        �鼮��Ϣ¼��     \n");
	printf("-------------------------\n");
	printf("������������Ҫ¼���鼮��������Ϣ\n");
	bok = (Book*)malloc(sizeof(Book));
	while(1)
	{
		flag = 0;
		bok = (Book*)realloc(bok, (i + 1) * sizeof(Book));
		printf("��ţ�");
		scanf("%s", index1);
		for (j = 0; j < i; j++)
			if (strcmp(index1, bok[j].index) == 0)
			{
				printf("�ñ���Ѵ��ڣ��������Ƿ���ȷ");
				flag = 1;
			}
		for (j = 0; j < n; j++)
			if (strcmp(index1, fbok[j].index) == 0)
			{
				printf("�ñ���Ѵ��ڣ��������Ƿ���ȷ\n");
				flag = 1;
			}
		if(flag==0)
		{
			strcpy(bok[i].index, index1);
			printf("������");
			scanf("%s", bok[i].name);
			printf("���ߣ�");
			scanf("%s", bok[i].author);
			printf("�����磺");
			scanf("%s", bok[i].pub);
			printf("����ʱ�䣺");
			scanf("%s", bok[i].pubtime);
			printf("�۸�");
			scanf("%f", &bok[i].price);
			printf("�鼮������");
			scanf("%d", &bok[i].num);
			printf("���");
			scanf("%s", bok[i].kind);
			i++;
			printf("¼��ɹ���\n");
		}
		printf("���롮1������¼��,���롮0���������˵������������ַ��˳�����");
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

void Look()    //����鼮
{
	int i, n, j, a, b;
	Book* bok, bk;
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	printf("------------------------------------����Ϊ�����鼮��Ϣ-----------------------------------------------\n");
	printf("���\t����\t\t\t����\t\t������\t\t\t����ʱ��\t�۸�\t����\t���\n");
	for (i = 0; i < n; i++)
		printf("%-8s%-24s%-16s%-24s%-16s%-8.2f%-8d%s\n",
			bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
	printf("-----------------------------------------------------------------------------------------------------\n");
	free(bok);
}

void Delete()  //ɾ���鼮
{
	char a;
	int i, n;
	Book* bok;
	char index1[15];
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	printf("-------------------------\n");
	printf("        �鼮��Ϣɾ��     \n");
	printf("-------------------------\n");
	while(1)
	{
		printf("����������ɾ���鼮�ı�ţ�");
		scanf("%s", index1);
		for (i = 0; i < n; i++)
		{
			if (strcmp(index1, bok[i].index)==0)
			{
				printf("---------------------------------------�����Ǵ������Ϣ----------------------------------------\n");
				printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
					bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
				printf("-----------------------------------------------------------------------------------------------\n");
				printf("�Ƿ�ȷ��ɾ��?��Y/N����");
				while ((a = getchar()) == '\n');
				if (a == 'Y')
				{
					for (i++; i < n; i++)
						bok[i - 1] = bok[i];
					wSave(bok, n - 1);
					n--;
					printf("ɾ���ɹ���\n");
				}
				break;
			}
			if (i == n - 1)
				printf("û���ҵ��ñ�ţ������������Ƿ���ȷ��\n");
		}
		printf("���롮1������ɾ��,���롮0���������˵������������ַ��˳�����");
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

void Find()    //��ѯ�鼮
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
		printf("           �鼮��ѯ        \n");
		printf("---------------------------\n");
		printf("          1.��ѯ���       \n");
		printf("          2.��ѯ����       \n");
		printf("          3.��ѯ����       \n");
		printf("          4.��ѯ������     \n");
		printf("          5.��ѯ�۸�       \n");
		printf("          6.��ѯ���       \n");
		printf("          7.��ѯ����       \n");
		printf("          0.ȡ����ѯ       \n");
		printf("---------------------------\n");
		printf("��ѡ����Ҫ��ѯ����Ϣ(1-7)��");
		scanf("%d", &a);
		if (a == 0)
			break;
		switch (a)
		{
		case 1:
			printf("��������Ҫ��ѯ�ı�ţ�");
			scanf("%s", bk.index);
			printf("----------------------------------------------�������������-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.index, bok[i].index) == 0)
				{
					printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                �ܱ�Ǹ��û���ҵ�������ѯ���鼮��                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 2:
			printf("��������Ҫ��ѯ��������");
			scanf("%s", bk.name);
			printf("----------------------------------------------�������������-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.name, bok[i].name) == 0)
				{
					printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                �ܱ�Ǹ��û���ҵ�������ѯ���鼮��                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 3:
			printf("��������Ҫ��ѯ�����ߣ�");
			scanf("%s", bk.author);
			printf("----------------------------------------------�������������-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.author, bok[i].author) == 0)
				{
					printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                �ܱ�Ǹ��û���ҵ�������ѯ���鼮��                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 4:
			printf("��������Ҫ��ѯ�ĳ����磺");
			scanf("%s", bk.pub);
			printf("----------------------------------------------�������������-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.pub, bok[i].pub) == 0)
				{
					printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                �ܱ�Ǹ��û���ҵ�������ѯ���鼮��                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 5:
			printf("��������Ҫ��ѯ�ļ۸����䣺>=");
			scanf("%f", &fmin);
			printf("                          <=");
			scanf("%f", &fmax);
			printf("----------------------------------------------�������������-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (bok[i].price >= fmin && bok[i].price <= fmax)
				{
					printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                �ܱ�Ǹ��û���ҵ�������ѯ���鼮��                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 6:
			printf("��������Ҫ��ѯ�����");
			scanf("%s", bk.kind);
			printf("----------------------------------------------�������������-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (strcmp(bk.kind, bok[i].kind) == 0)
				{
					printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                �ܱ�Ǹ��û���ҵ�������ѯ���鼮��                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		case 7:
			printf("��������Ҫ��ѯ���������䣺>=");
			scanf("%d", &min);
			printf("                          <=");
			scanf("%d", &max);
			printf("----------------------------------------------�������������-------------------------------------------------\n");
			for (i = 0, j = 0; i < n; i++)
				if (bok[i].num >= min && bok[i].num <= max)
				{
					printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					j++;
				}
			if (j == 0)
				printf("                                �ܱ�Ǹ��û���ҵ�������ѯ���鼮��                                     \n");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			break;

		default:break;
		}
		printf("���롮1��������ѯ,���롮0���������˵������������ַ��˳�����");
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

void Change()  //�޸��鼮��Ϣ
{
	int a,j;
	char index1[15];
	int i, n;
	Book* bok;
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	printf("---------------------------\n");
	printf("         �鼮��Ϣ�޸�       \n");
	printf("---------------------------\n");
	while(1)
	{
		printf("��������Ҫ�޸��鼮�ı�ţ�");
		scanf("%s", index1);
		for (i = 0,j=0; i < n; i++)
			if (strcmp(index1, bok[i].index) == 0)                                                                               //�ҵ���Ҫ�޸ĵ���
			{
				j++;
				while (1)
				{
					printf("---------------------------------------�����Ǵ������Ϣ----------------------------------------\n");
					printf("��ţ�%s��������%s�����ߣ�%s�������磺%s������ʱ�䣺%s���۸�%.2f���鼮������%d�����%s\n",
						bok[i].index, bok[i].name, bok[i].author, bok[i].pub, bok[i].pubtime, bok[i].price, bok[i].num, bok[i].kind);
					printf("-----------------------------------------------------------------------------------------------\n");
					printf("---------------------------\n");
					printf("          1.����           \n");
					printf("          2.����           \n");
					printf("          3.������         \n");
					printf("          4.����ʱ��       \n");
					printf("          5.�۸�           \n");
					printf("          6.����           \n");
					printf("          7.���           \n");
					printf("          0.ȡ���޸�       \n");
					printf("---------------------------\n");
					printf("��������Ҫ�޸ĵ���Ϣ��");
					scanf("%d", &a);
					if (a == 0)
						break;
					switch (a)
					{
					case 1:
						printf("����������Ҫ�޸ĳɵ���Ϣ��");
						scanf("%s", bok[i].name);
						printf("�޸ĳɹ���");
						break;
					case 2:
						printf("����������Ҫ�޸ĳɵ���Ϣ��");
						scanf("%s", bok[i].author);
						printf("�޸ĳɹ���");
						break;
					case 3:
						printf("����������Ҫ�޸ĳɵ���Ϣ��");
						scanf("%s", bok[i].pub);
						printf("�޸ĳɹ���");
						break;
					case 4:
						printf("����������Ҫ�޸ĳɵ���Ϣ��");
						scanf("%s", bok[i].pubtime);
						printf("�޸ĳɹ���");
						break;
					case 5:
						printf("����������Ҫ�޸ĳɵ���Ϣ��");
						scanf("%f", &bok[i].price);
						printf("�޸ĳɹ���");
						break;
					case 6:
						printf("����������Ҫ�޸ĳɵ���Ϣ��");
						scanf("%d", &bok[i].num);
						printf("�޸ĳɹ���");
						break;
					case 7:
						printf("����������Ҫ�޸ĳɵ���Ϣ��");
						scanf("%s", bok[i].kind);
						printf("�޸ĳɹ���");
						break;
					default:break;
					}
					printf("���롮1�������޸Ĵ���,���롮0���˻���һ�������������ַ��˳�����");
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
			printf("��Ǹ��δ���ҵ������޸ĵ��鼮");
			printf("���롮1�������޸������鼮,���롮0���������˵������������ַ��˳�����");
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

void order()                 //�����鼮
{
	int i, n, j, a, b;
	Book* bok, bk;
	n = Booknum();
	bok = (Book*)malloc(n * sizeof(Book));
	Open(bok, n);
	while(1)
	{
		printf("---------------------------\n");
		printf("         �鼮����          \n");
		printf("---------------------------\n");
		Look();
		printf("---------------------------\n");
		printf("          1.���           \n");
		printf("          2.����           \n");
		printf("          3.����           \n");
		printf("          4.������         \n");
		printf("          5.����ʱ��       \n");
		printf("          6.�۸�           \n");
		printf("          7.����           \n");
		printf("          8.���           \n");
		printf("          0.ȡ������       \n");
		printf("---------------------------\n");
		printf("��ѡ�����ĸ���Ϣ��������(0-8)��");
		scanf("%d",&a);
		if (a == 0)
			break;
		printf("��ѡ����Ҫ����ķ�ʽ����1��Ϊ��С���󣬡�0��Ϊ�ɴ�С��");
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
		printf("����ɹ���\n");
		Look();
		printf("���롮1����������,���롮0���������˵������������ַ��˳�����");
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

void password(char pwin[]) //�������뺯��
{
	int i=0;
	char a;
	while ((a = getchar()) == '\n');               //�Իس�
	while (1)
	{
		if (('a' <= a && a <= 'z') || ('A' <= a && a <= 'Z') || ('0' <= a&&a <= '9'))
		{
			pwin[i] = a;
			a = getchar();
			i++;
			if (i == 16&&a!='\n')
			{
				while (a != '\n')                  //��ջ�����
					a = getchar();
				printf("�ַ���̫�࣬���������룺");
				i = 0;
				a = getchar();
			}
			else if (a == '\n' && i >= 6)
				break;
		}
		else if (a == '\n')
		{
			printf("�ַ���̫�٣����������룺");
			i = 0;
			a = getchar();
		}
		else
		{
			printf("��δ֪�ַ������������룺");
			while ((a = getchar()) != '\n');            //�ѻس�ǰ���ַ�ȫ���Ե�
			i = 0;
			a = getchar();
		}
	}
	pwin[i] = '\0';									//ȷ���ַ����Ľ�β
}

void Setpw()   //�޸Ĺ���Ա����
{
	char pwin1[17],pwin2[17];
	FILE* fp;
	login();
	printf("��������Ҫ�޸ĵ�����(6-16λ����ĸ���������)��");
	while(1)
	{
		password(pwin1);
		printf("��ȷ��������룺");
		password(pwin2);
		if (strcmp(pwin1, pwin2) == 0)
		{
			if ((fp = fopen("password.txt", "w")) == NULL)
			{
				printf("������󣬼����˳�\n");
				exit(1);
			}
			fprintf(fp, "%s", pwin1);
			printf("�޸ĳɹ�\n");
			break;
		}
		else
			printf("�������벻һ�£�����������:");
	}
	fclose(fp);
}

void menu()    //���˵�
{
	printf("------------------------------\n");
	printf("          ������ϵͳ        \n");
	printf("------------------------------\n");
	printf("          1.¼���鼮          \n");
	printf("          2.ɾ���鼮          \n");
	printf("          3.����鼮          \n");
	printf("          4.��ѯ�鼮          \n");
	printf("          5.�޸��鼮��Ϣ      \n");
	printf("          6.�����鼮          \n");
	printf("          7.�޸Ĺ���Ա����    \n");
	printf("          0.�˳�              \n");
	printf("������Ҫִ�в�������ţ�");
}

int main()
{
	login();
	int a = 0;
	while (1)
	{
		menu();                               //��ӡ��ҳ
		scanf("%d", &a);
		while (1)                              //ȷ��������ǿ�ѡѡ��
		{
			if (a < 0 || a>7)
			{
				printf("����Ų����ڣ�����������;");
				scanf("%d", &a);
			}
			else
				break;
		}
		if (a == 0)                           //a=0���˳�����
			break;
		else
			switch (a)                        //���������ѡ�Ĳ����Ӻ���
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