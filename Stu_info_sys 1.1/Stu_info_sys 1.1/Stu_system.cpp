//---------------------------
//
//ѧ���ɼ�����ϵͳ
//@version  1.1
//@author   `13
//2015��12��17��
//
//----------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

#define PASSWORD "1313"											   //���������޸�
#define file_address_r "D:\\Data\\Stu_info\\Stu_info.txt"          //���������޸�
#define file_address_w "D:\\Data\\Stu_info\\New_Stu_info.txt"	   //���������޸�
#define STU_NUM_MAX 500
#define true 1

//=======================================================================
//
//���ݵ�ȫ�ֶ���
//@version  1.1��������״̬��� flag
//
//=======================================================================

struct student
{
	int num;                            //ѧ��
	char name[16];                      //����
	float c_score;                      //C���Գɼ�
	char sex[4];                        //�Ա�
	char major[16];                     //רҵ
	char category[16];                  //�������
	char nation[8];                     //����
	char political_status[16];          //������ò
	int year;                           //������
	int month;                          //��
	int day;                            //��
	char id[32];                        //���֤��
	char province[8];                   //ʡ��
	int dormitory;                      //���Һ�
	int bed;                            //��λ
	int flag;                           //״̬��� Ĭ��Ϊ1000
};

struct student stu_info_temp;           //��������ʱ����
struct student stu_info[STU_NUM_MAX];   //ѧ����Ϣ�ṹ��
struct student *p;                      //ѧ����Ϣ�ṹ��ָ��

int stu_num = 0;                          //ѧ������
int stu_info_num = 0;                     //ѧ����Ϣ����
int stu_num_1504101 = 0;                  //1504101�༶����
int stu_num_1504102 = 0;                  //1504101�༶����
int stu_num_1504103 = 0;                  //1504101�༶����
int stu_num_1504104 = 0;                  //1504101�༶����
int stu_num_1504201 = 0;                  //1504101�༶����
int stu_num_1504202 = 0;                  //1504101�༶����

FILE *fp_r;                             //��ȡ�ļ�ָ��
FILE *fp_w;                             //д���ļ�ָ��

										//=======================================================================
										//
										//                          ˵����flag��ѧ��״̬���
										//
										//flag��һλ��1 - ���� | 2 - ����Ϣ��ɾ��
										//flag�ڶ�λ��0 - ���� | X - �ٵ�������1~9��
										//flag����λ��0 - ���� | X - ���δ�����1~9��
										//flag����λ��Ԥ��
										//
										//=======================================================================

										//=======================================================================
										//
										//                      function 0xx���������ܺ���
										//
										//=======================================================================

										//function001:��ȡϵͳʱ��
										//@version  1.1 ��Ϊ��ȡ����ʱ��
										//

void get_time()
{
	time_t nowtime;
	struct tm *timeinfo;
	time(&nowtime);
	timeinfo = localtime(&nowtime);

	int year, month, day, hour, minute, second;

	year = timeinfo->tm_year + 1900;
	//printf("test000:years is %d"year);
	month = timeinfo->tm_mon + 1;
	day = timeinfo->tm_mday;
	hour = timeinfo->tm_hour;
	minute = timeinfo->tm_min;
	second = timeinfo->tm_sec;

	printf("%d��%d��%d�� %dʱ%d��%d��", year, month, day, hour, minute, second);
}

//function002����ʽ����
//@version  1.0
//

void end_format()
{
	printf("\n\n========================================");
	get_time();
	printf("===========\n");
	printf("\n");
}

//function003��ȷ��Ȩ��
//@version  2.0��������˸��������
//@p            �ַ���ָ��
//

void authority_confirm()
{
	printf("===>>> ������������룺");
	char Password[32] = PASSWORD;
	char password[32];
	char *p = password;
	char ch;
	while ((ch = getch()) != '\r')
	{
		if (ch == '\b')
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');     //�����Ļ������
			if (p != password) //�����һ����Ȥ�Ľ������Ļ�ϵ��������ֶ���ɿ������
				--p;
		}
		else
		{
			putchar('*');
			*p++ = ch;
		}
	}
	putchar('\n');
	*p = '\0';                  //����ַ���������
								//printf("test 003:you input is %s",password);
	if (strcmp(Password, password) == 0)
	{
		printf("\n\n===>>> ��½�ɹ�!\n");
		end_format();
	}
	else
	{
		printf("Error 003:�������\n");
		exit(-003);
	}
}

//=======================================
//              ��ʷ�汾
//=======================================
//@version  1.0
//void authority_confirm()
//{
//    char Password[32]=PASSWORD;
//    char password[32];
//    int i;
//    printf("===>>>������������룺");
//    for(i=0;i<32;i++)
//    {
//        password[i]=getch();
//        if(password[i]=='\r') break;
//        printf("*");
//    }
//    password[i]='\0';
//    //printf("you input is %s %s",password,Password);
//    if(strcmp(Password,password)==0)
//        printf("\n\n===>>>��½�ɹ�\n");
//    else
//    {
//        printf("Error 001:�������\n");
//        exit(-1);
//    }
//}

//function004��ѧ����Ϣ�ļ���ȡ
//@version  2.1��ʹ��fscanf���fgets���ع�����  //������ͳ��ѧ����Ŀ�Ĵ���
//
//@file_fp                  �ļ�ָ��
//@struct student stu_info  �洢ѧ����Ϣ�Ľṹ������
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��
//@stu_num_1504x0x          ����ѧ������
//

void read_file(FILE *file_fp)
{
	file_fp = fopen(file_address_r, "r");
	if (file_fp == NULL)
	{
		printf("Error 004_0:�ļ���ȡʧ�ܣ�����Ĭ��λ���Ƿ����ѧ����Ϣ�ļ�\n");
		printf("help 004���ļ�Ĭ�ϵ�ַ��");
		char help002[50] = file_address_r;
		printf("%s", help002);
		end_format();
		exit(-004);
	}
	printf("===>>>��ʼ��ȡ�ļ�......");
	int i;
	for (i = 0; i<STU_NUM_MAX; i++)
	{
		if (!feof(file_fp))
		{
			fscanf(file_fp, "%d", &stu_info[i].num);
			//printf("test004_0��%d",stu_info[i].num);
			if (stu_info[i].num / 100 == 1504101) stu_num_1504101++;
			if (stu_info[i].num / 100 == 1504102) stu_num_1504102++;
			if (stu_info[i].num / 100 == 1504103) stu_num_1504103++;
			if (stu_info[i].num / 100 == 1504104) stu_num_1504104++;
			if (stu_info[i].num / 100 == 1504201) stu_num_1504201++;
			if (stu_info[i].num / 100 == 1504202) stu_num_1504202++;
			fscanf(file_fp, "%s", &stu_info[i].name);
			fscanf(file_fp, "%f", &stu_info[i].c_score);
			fscanf(file_fp, "%s", &stu_info[i].sex);
			fscanf(file_fp, "%s", &stu_info[i].major);
			fscanf(file_fp, "%s", &stu_info[i].category);
			fscanf(file_fp, "%s", &stu_info[i].nation);
			fscanf(file_fp, "%s", &stu_info[i].political_status);
			//printf("tset004_1:%s",stu_info[i].political_status);
			fscanf(file_fp, "%d", &stu_info[i].year);
			fscanf(file_fp, "%d", &stu_info[i].month);
			fscanf(file_fp, "%d", &stu_info[i].day);
			fscanf(file_fp, "%s", &stu_info[i].id);
			fscanf(file_fp, "%s", &stu_info[i].province);
			fscanf(file_fp, "%d", &stu_info[i].dormitory);
			fscanf(file_fp, "%d", &stu_info[i].bed);
			//stu_info[i].flag=1000;
			fscanf(file_fp, "%d", &stu_info[i].flag);
			if (stu_info[i].flag / 1000 == 1)
				stu_num++;
		}
		else
		{
			stu_info_num = i;
			//printf("students numbers = %d",stu_num);
			break;
		}
	}
	printf("�ɹ�\n");
	end_format();
	i = fclose(file_fp);                              //����ѭ�������洢fclose�ķ���ֵ
	if (i == EOF)
	{
		printf("Error 004_1:�ļ��ر�ʧ��\n");
		end_format();
		exit(-004);
	}
}

//function005�����ĳ��ѧ������ϸ��Ϣ
//@version  2.0 ��Ҫ�޸ģ������˽ṹ���ַ����Ĵ�С���������ܹ�������ʾ
//
//@struct student stu_info  �洢ѧ����Ϣ�Ľṹ������
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��
//

void show_stu_info(struct student *p)
{
	if (p->flag / 1000 == 1)
	{
		printf("%d\t", p->num);
		printf("%s\t", p->name);
		printf("%.1f\t", p->c_score);
		printf("%s\t", p->sex);
		printf("%s\t", p->major);
		printf("%s\t", p->category);
		printf("%s\t", p->nation);
		printf("%s\t", p->political_status);
		printf("%d\t", p->year);
		printf("%d\t", p->month);
		printf("%d\t", p->day);
		printf("%s\t", p->id);
		printf("%s\t", p->province);
		printf("%d\t", p->dormitory);
		printf("%d\t", p->bed);
		//printf("\n test:flag=%d\t",p->flag);
		printf("\n");
		p = stu_info;                          //ָ������
	}
	else puts("��ѧ����Ϣ�����ڻ����Ѿ����ϳ�");
	p = stu_info;                              //ָ������
}

//function005_1�����ĳ��ѧ���ļ�����Ϣ
//@version  1.0
//
//@struct student stu_info  �洢ѧ����Ϣ�Ľṹ������
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��

void short_show_stu_info(struct student *p)
{
	if (p->flag / 1000 == 1)
	{
		printf("%d\t", p->num);
		printf("%s\t", p->name);
		printf("%.1f\t", p->c_score);
		printf("\n");
		p = stu_info;                         //ָ������
	}
	else puts("��ѧ����Ϣ�����ڻ����Ѿ����ϳ�");
	p = stu_info;                         //ָ������
}

//function006���������ѧ������ϸ��Ϣ
//@version  1.0
//
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��
//@number                   Ҫ��ʾ��ѧ����Ϣ������number<=0ʱ��ʾȫ����
//

void show_stu_infos(struct student *p, int number)
{
	p = stu_info;
	int i, j;
	if (number <= 0)  j = stu_num;
	else j = number;

	for (i = 0; i<j; i++)
	{
		show_stu_info(p + i);
		p = stu_info;
	}
	end_format();
}

//function006_1���������ѧ���ļ�����Ϣ
//@version  1.0
//
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��
//@number                   Ҫ��ʾ��ѧ����Ϣ������number<=0ʱ��ʾȫ����

void short_show_stu_infos(struct student *p, int number)
{
	p = stu_info;
	int i, j;
	if (number <= 0)  j = stu_num;
	else j = number;

	for (i = 0; i<j; i++)
	{
		short_show_stu_info(p + i);
		p = stu_info;
	}
	p = stu_info;
	end_format();
}

//function007���ѵ�ǰ�ṹ��д���ļ��д���
//@version  1.1 ���������޸�Ϊstu_num-1
//
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��
//

void write_file(FILE *file_fp)
{
	file_fp = fopen(file_address_w, "w");
	if (file_fp == NULL)
	{
		printf("Error 007_0:�ļ�д��ʧ��\n");
		printf("help 007���ļ�Ĭ�ϵ�ַ��");
		char help007[50] = file_address_r;
		printf("%s", help007);
		end_format();
		exit(-007);
	}
	printf("===>>>��ʼд���ļ�......");
	int i;
	for (i = 0; i<stu_info_num; i++)                        //���������޸�Ϊstu_num-1
	{
		//if(stu_info[i].flag/1000!=1)                   //��Ϊȫ��д��
		//{
		fprintf(file_fp, "%d ", stu_info[i].num);
		fprintf(file_fp, "%s ", stu_info[i].name);
		fprintf(file_fp, "%.1f ", stu_info[i].c_score);
		fprintf(file_fp, "%s ", stu_info[i].sex);
		fprintf(file_fp, "%s ", stu_info[i].major);
		fprintf(file_fp, "%s ", stu_info[i].category);
		fprintf(file_fp, "%s ", stu_info[i].nation);
		fprintf(file_fp, "%s ", stu_info[i].political_status);
		fprintf(file_fp, "%d ", stu_info[i].year);
		fprintf(file_fp, "%d ", stu_info[i].month);
		fprintf(file_fp, "%d ", stu_info[i].day);
		fprintf(file_fp, "%s ", stu_info[i].id);
		fprintf(file_fp, "%s ", stu_info[i].province);
		fprintf(file_fp, "%d ", stu_info[i].dormitory);
		fprintf(file_fp, "%d ", stu_info[i].bed);
		fprintf(file_fp, "%d", stu_info[i].flag);
		fprintf(file_fp, "\n");
		//}

	}
	printf("�ɹ�\n");
	end_format();
	i = fclose(file_fp);
	if (i == EOF)
	{
		printf("Error 007_1:�ļ��ر�ʧ��\n");
		end_format();
		exit(-007);
	}
}

//=======================================================================
//
//      function 1xx�����ݲ���������ɾ�����޸�ĳ�����ֵ������
//
//=======================================================================

//function101������һ��ѧ���ĸ�����Ϣ
//@version  1.0
//
//@stu_info_num             �ṹ����Ŀ
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��
//@stu_num                  ѧ����Ŀ
//

void add_new_stu_info(struct student *p)
{
	p = stu_info;
	if (stu_info_num >= STU_NUM_MAX - 1)
	{
		puts("Error 101:ѧ����Ŀ�ﵽ���ޣ��޷��������\n");
		end_format();
		exit(-101);
	}
	else
	{
		printf("���������������ѧ���ĸ�����Ϣ\n");
		puts("�������ѧ��ѧ�ţ�");
		scanf("%d", &stu_info[stu_info_num - 1].num);
		puts("�������ѧ��������");
		scanf("%s", &stu_info[stu_info_num - 1].name);
		puts("�������ѧ��C���Գɼ���");
		scanf("%f", &stu_info[stu_info_num - 1].c_score);
		puts("�������ѧ��    �Ա�");
		scanf("%s", &stu_info[stu_info_num - 1].sex);
		puts("�������ѧ��    רҵ��");
		scanf("%s", &stu_info[stu_info_num - 1].major);
		puts("�������ѧ���������");
		scanf("%s", &stu_info[stu_info_num - 1].category);
		puts("�������ѧ��    ���壺");
		scanf("%s", &stu_info[stu_info_num - 1].nation);
		puts("�������ѧ��������ò��");
		scanf("%s", &stu_info[stu_info_num - 1].political_status);
		puts("�������ѧ��    ���꣺");
		scanf("%d", &stu_info[stu_info_num - 1].year);
		puts("�������ѧ��    ���£�");
		scanf("%d", &stu_info[stu_info_num - 1].month);
		puts("�������ѧ��    ���գ�");
		scanf("%d", &stu_info[stu_info_num - 1].day);
		puts("�������ѧ��    ���֤�ţ�");
		scanf("%s", &stu_info[stu_info_num - 1].id);
		puts("�������ѧ��    ʡ�ݣ�");
		scanf("%s", &stu_info[stu_info_num - 1].province);
		puts("�������ѧ��    ���Һţ�");
		scanf("%d", &stu_info[stu_info_num - 1].dormitory);
		puts("�������ѧ��    ��λ�ţ�");
		scanf("%d", &stu_info[stu_info_num - 1].bed);
		stu_info[stu_info_num - 1].flag = 1000;
		puts("ѧ����Ϣ������ɣ���ȷ�����������Ϣ��");
		p = stu_info;
		p += stu_info_num;
		p -= 1;
		show_stu_info(p);
		puts("¼����̽���\n");
		p = stu_info;
		stu_num++;
		stu_info_num++;
		end_format();
	}
}

//function102��ɾ��һ��ѧ���ĸ�����Ϣ
//@version  1.0
//
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��
//@stu_num                  ѧ����Ŀ
//@stu_info_num             �ṹ����Ŀ
//
void delete_stu_info(struct student *p)
{
	p->flag += 1000;

	puts("ѧ����Ϣɾ�����\n");
	stu_num--;
	end_format();
	p = stu_info;
}


//function103���޸�һ��ѧ���ĸ�����Ϣ       (��ģ�ȫ������д��)
//@version  1.0
//
//@struct student *p;       ѧ����Ϣ�Ľṹ��ָ��
//@stu_num                  ѧ����Ŀ
//@stu_info_num             �ṹ����Ŀ
//
void all_change_stu_info(struct student *p)
{
	puts("��ѧ��ԭʼ��Ϣ���£�\n");
	show_stu_info(p);
	printf("�����������޸�ѧ���ĸ�����Ϣ\n");
	puts("�������ѧ��ѧ�ţ�");
	scanf("%d", &p->num);
	puts("�������ѧ��������");
	scanf("%s", &p->name);
	puts("�������ѧ��C���Գɼ���");
	scanf("%f", &p->c_score);
	puts("�������ѧ��    �Ա�");
	scanf("%s", &p->sex);
	puts("�������ѧ��    רҵ��");
	scanf("%s", &p->major);
	puts("�������ѧ���������");
	scanf("%s", &p->category);
	puts("�������ѧ��    ���壺");
	scanf("%s", &p->nation);
	puts("�������ѧ��������ò��");
	scanf("%s", &p->political_status);
	puts("�������ѧ��    ���꣺");
	scanf("%d", &p->year);
	puts("�������ѧ��    ���£�");
	scanf("%d", &p->month);
	puts("�������ѧ��    ���գ�");
	scanf("%d", &p->day);
	puts("�������ѧ��    ���֤�ţ�");
	scanf("%s", &p->id);
	puts("�������ѧ��    ʡ�ݣ�");
	scanf("%s", &p->province);
	puts("�������ѧ��    ���Һţ�");
	scanf("%d", &p->dormitory);
	puts("�������ѧ��    ��λ�ţ�");
	scanf("%d", &p->bed);
	puts("��ѧ���޸���Ϣ���£�\n");
	show_stu_info(p);
	p = stu_info;
	end_format();
}
//function104���Գɼ���Ϊ�ؼ�������
//@version  1.1             �����Ż��㷨
//@stu_num                  ѧ����Ŀ
//@stu_info_num             �ṹ����Ŀ
//
void sort_by_c_socore()
{
	//printf("test: stu_info_num=%d",stu_info_num);
	//end_format();
	int i, j, sflag;
	for (j = 0; j<stu_info_num; j++)
	{
		sflag = 0;
		for (i = 0; i<stu_info_num - j; i++)
		{
			//            puts("change has orrcured!");
			if (stu_info[i].c_score<stu_info[i + 1].c_score)
			{
				//                 memcpy(&stu_info_temp, &stu_info[i], sizeof(stu_info));
				//                 memcpy(&stu_info[i], &stu_info[i+1], sizeof(stu_info));
				//                 memcpy(&stu_info[i+1], &stu_info_temp, sizeof(stu_info));
				stu_info_temp = stu_info[i];
				stu_info[i] = stu_info[i + 1];
				stu_info[i + 1] = stu_info_temp;
				sflag = 1;
			}
		}
		if (sflag == 0) break;
	}
	end_format();
}

//function105����ѧ����Ϊ�ؼ�������
//@version  1.0
//@stu_num                  ѧ����Ŀ
//@stu_info_num             �ṹ����Ŀ
//
void sort_by_num()
{

	int i, j, nflag;
	for (j = 0; j<stu_info_num; j++)
	{
		nflag = 0;
		for (i = 0; i<stu_info_num - j; i++)
		{
			if (stu_info[i].num<stu_info[i + 1].num)
			{
				stu_info_temp = stu_info[i];
				stu_info[i] = stu_info[i + 1];
				stu_info[i + 1] = stu_info_temp;
				nflag = 1;
			}
		}
		if (nflag == 0) break;
	}
	end_format();
}

//function106����ѧ����Ϊ�ؼ���ѡ��ѧ��
//@version  1.0
//@stu_num                  ѧ����Ŀ
//@stu_info_num             �ṹ����Ŀ
//@p                        �ṹ��ָ��
//
int select_stu_by_num()
{
	int i, s_num, flag = 0;
	p = stu_info;
	printf("������Ŀ��ѧ����ѧ�ţ�");
	scanf("%d", &s_num);
	for (i = 0; i<stu_info_num; i++)
	{
		if (stu_info[i].num == s_num)
		{
			p += i;
			//show_stu_info(p);
			flag = 1;
			return 1;
			break;

		}
	}
	if (flag == 0)
	{
		puts("Error 106 δ��ѯ����ѧ�Ŷ�Ӧ��ѧ����Ϣ");
		return 0;

	}

}
//=======================================================================
//
//                      function 2xx������Ա����
//
//=======================================================================

//function201����ʾ����ѡ������
//@version  1.0
//
//@stu_info_num             ������Ŀ
//@stu_num                  ѧ����Ŀ
//
void show_stu_num()
{
	printf("�μӱ��ε�ѧ������Ϊ�� %d\n", stu_num);
	printf("�洢��ѧ����Ϣ����Ϊ�� %d\n", stu_info_num);
	printf("1504101��ѧ������Ϊ�� %d\n", stu_num_1504101);
	printf("1504102��ѧ������Ϊ�� %d\n", stu_num_1504102);
	printf("1504103��ѧ������Ϊ�� %d\n", stu_num_1504103);
	printf("1504104��ѧ������Ϊ�� %d\n", stu_num_1504104);
	printf("1504201��ѧ������Ϊ�� %d\n", stu_num_1504201);
	printf("1504202��ѧ������Ϊ�� %d\n", stu_num_1504202);
	end_format();
}

//function202���������
//@version  1.0
//
//@stu_info_num             ������Ŀ
//@stu_num                  ѧ����Ŀ
//test:�ɹ�����������һ��ѧ��
//
void select_random_student()
{
	int point = 0;
	p = stu_info;
	srand((unsigned)time(NULL));
	point = rand() % stu_info_num;
	p += point;
	printf("ѧ�ţ�%d  ����%s\n", p->num, p->name);
	p = stu_info;
	end_format();

}
//function203����ĳ�˼ӷ�
//@version  1.1             ȥ����ָ�벿�ֵĴ���
//
//@stu_info_num             ������Ŀ
//
void add_someone_c_score()
{
	int s_num, i, flag = 0;
	float score;
	printf("������Ҫ�ӷ�ѧ����ѧ��:");
	scanf("%d", &s_num);
	printf("������Ҫ�ӷ�ѧ���ķ���:");
	scanf("%f", &score);
	for (i = 0; i<stu_info_num; i++)
	{
		if (stu_info[i].num == s_num)
		{
			flag = 1;
			stu_info[i].c_score += score;
			//show_stu_info(p);
			printf("����  %s ��ǰ�ɼ� % .1f\n", stu_info[i].name, stu_info[i].c_score);
			end_format();
			break;
		}
	}
	if (flag == 0)
	{
		puts("Error203��δ�ҵ���ѧ�Ŷ�Ӧ��ѧ��");
		end_format();
	}
}
//function204����ĳ������ӷ�
//@version  1.0
//
//@stu_info_num             ������Ŀ
//
void add_class_c_socre()
{
	int class_num, i, flag = 0;
	float score;
	printf("������Ҫ�ӷְ༶�İ��:");
	scanf("%d", &class_num);
	printf("������Ҫ�ӷְ༶�ķ���:");
	scanf("%f", &score);
	for (i = 0; i<stu_info_num; i++)
	{
		if (stu_info[i].num / 100 == class_num)
		{
			flag = 1;
			stu_info[i].c_score += score;
			//show_stu_info(p);
			printf("����  %s\t ��ǰ�ɼ� % .1f\n", stu_info[i].name, stu_info[i].c_score);
		}

	}
	end_format();
	if (flag == 0)
	{
		puts("Error204���ð�Ų�����");
		end_format();
	}
}

//function205��չʾ������ǰ��ѧ��
//@version  1.0
//
//@stu_info_num             ������Ŀ
//
void top_stu(int n)
{
	printf("һ����ǰ%d��ͬѧ��ѧ�ţ��������ɼ���\n", n);
	sort_by_c_socore();
	short_show_stu_infos(p, n);
}

//function207����Ǳ��ֲ��ѧ��
//@version  1.0
//
//@stu_info_num             ������Ŀ
//
void flag_stu()
{
	p = stu_info;
	int i, flag_num, f = 0, fflag;
	printf("�������¼ѧ���ĵ�ѧ��:");
	scanf("%d", &flag_num);
	for (i = 0; i<stu_info_num; i++)
	{
		//printf("test: %d %d\n",flag_num,stu_info[i].num);
		if (stu_info[i].num == flag_num)
		{
			p += i;
			printf("===>>>%s\n", p->name);
			f = 1;
			break;
		}
	}
	if (f == 0) puts("Error 207_0:��ѧ�Ų�����");
	else
	{
		printf("�����������ݶ�Ӧ�����֣�\n");
		printf("1,�ٵ�\n");
		printf("2,����\n");
		scanf("%d", &fflag);
		if (fflag == 1)
		{
			stu_info[i].flag += 100;
		}
		else if (fflag == 2)
		{
			stu_info[i].flag += 10;
		}
		else puts("Error 207_1��δ�ҵ���Ӧ���ֵı������");
	}
	p = stu_info;
}

//function208��չʾ���ֲ��ѧ��
//@version  1.0
//
//@stu_info_num             ������Ŀ
//
void show_flag_stu()
{
	int xflag = 0;
	int i;
	for (i = 0; i<stu_info_num; i++)
	{
		if (stu_info[i].flag != 1000)
		{
			printf("%s\t", stu_info[i].name);
			if (stu_info[i].flag % 1000 / 100 != 0)
			{
				printf("�ٵ� %d��\t", stu_info[i].flag % 1000 / 100);
				xflag = 1;
			}
			if (stu_info[i].flag % 100 / 10 != 0)
			{
				printf("���� %d��\t", stu_info[i].flag % 100 / 10);
				xflag = 1;
			}
			printf("\n");
		}
	}
	if (xflag == 0) puts("��ʱû�б��ֲ��ͬѧ");

}

//=======================================================================
//
//                      function 3xx����ʽ����
//
//=======================================================================

//function301����ʼ��ʽ
//@version  1.0
//

void welcome()
{

	end_format();
	authority_confirm();
	read_file(fp_r);
	p = stu_info;
	printf("*****************************************************************************\n");
	printf("*                                                                           *\n");
	printf("*                      ѧ �� �� �� �� �� ϵ ͳ                              *\n");
	printf("*                                                                           *\n");
	printf("*                                                     version 2.0           *\n");
	printf("*                                                     author  `13           *\n");
	printf("*                                                                           *\n");
	printf("*****************************************************************************\n");;
	printf("\n");
	printf("\n");
	end_format();
	printf("\n");
	printf("\n");

}
//function302��չʾȫ������
//@version  1.0
//
void show_func()
{
	end_format();
	printf(" 1����ʾѡ�����\n");
	printf(" 2���������\n");
	printf(" 3�����˼ӷ�\n");
	printf(" 4��ȫ��ӷ�\n");
	printf(" 5��չʾ���óɼ�ǰN����ͬѧ\n");
	printf(" 6����¼���ñ��ֲ��ѧ��\n");
	printf(" 7��չʾ���ñ��ֲ��ѧ��\n");
	printf(" 8��չʾ�����˵ļ�����Ϣ\n");
	printf(" 9��չʾ�����˵���ϸ��Ϣ\n");
	printf("10������һ��ѧ���ĸ�����Ϣ\n");
	printf("11���޸�һ��ѧ���ĸ�����Ϣ\n");
	printf("12��ɾ��һ��ѧ���ĸ�����Ϣ\n");
	printf("13��չʾһ��ѧ���ĸ�����Ϣ\n");
	printf("14����ʾ�����б�\n");
	printf("15���˳�\n");
	printf("Do not input a letter!\n");
	end_format();
}

//function303�����˵�
//@version  1.1     //��������ĸ�����б�
//@fn           ѡ���ܱ���
//@num          ��¼���ݱ���
//
void menu()
{
	int fn, num;
	printf("===>>>�������Ӧ��Ž��빦��:");
	scanf("%d", &fn);
	if (fn / 10000 != 0)
	{
		puts("Error 303:��������벻Ҫ������ĸ��");
		exit(-303);
	}
	switch (fn)
	{
	case 1:
	{
		show_stu_num();
		break;
	}
	case 2:
	{
		select_random_student();
		break;
	}
	case 3:
	{
		add_someone_c_score();
		break;
	}
	case 4:
	{
		add_class_c_socre();
		break;
	}
	case 5:
	{
		printf("������Ҫ�鿴��ͬѧ������");
		scanf("%d", &num);
		sort_by_c_socore();
		short_show_stu_infos(p, num);
		num = 0;
		break;
	}
	case 6:
	{
		flag_stu();
		break;
	}
	case 7:
	{
		show_flag_stu();
		break;
	}
	case 8:
	{
		short_show_stu_infos(p, -1);
		break;
	}
	case 9:
	{
		show_stu_infos(p, -1);
		break;
	}
	case 10:
	{
		add_new_stu_info(p);
		break;
	}
	case 11:
	{
		num = select_stu_by_num();
		if (num)
			all_change_stu_info(p);
		break;
	}
	case 12:
	{
		num = select_stu_by_num();
		if (num)
			delete_stu_info(p);
		break;
	}
	case 13:
	{
		num = select_stu_by_num();
		if (num)
			show_stu_info(p);
		break;
	}
	case 14:
	{
		show_func();
		break;
	}
	case 15:
	{
		sort_by_num();
		write_file(fp_w);
		exit(000);
	}
	default:
	{
		puts("�����˴������ţ�����������");
		end_format();
		break;
	}
	}
}


//=======================================================================
//
//                             ���������
//
//=======================================================================


int main(void)
{
	welcome();
	show_func();
	while (true)
	{
		menu();
	}
	return 0;
}







