#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
typedef struct {//���ڽṹ��
	int month;
	int day;
}Date;
//��Ʒ�ṹ��
struct good {
	char code[10];//��Ʒ���
	char name[40];//��Ʒ����
	int inprice;//�ɱ�
	int outprice;//�۸�
	int storage;//���
	char type[10];//��Ʒ����
	char unit[10];//��λ
	char way[10];//֧����ʽ
	int sale_num;//�۳�����
	Date indate;//��������
	Date deadline;//���ʽ�ֹ��
	char shangjia[5];//�Ƿ��ϼ�
	char tuihuo[5];//�Ƿ��˻�
	char youhui[5];//�Ƿ��Ż�
	char origin[40];//����Դ
	char salesperson[40];//������Ա����
	struct good *next;
};

struct good* build_good();//���ļ���ȡ��Ϣ��������Ʒ���� 
void check(struct good*);//�鿴��Ʒ��Ϣ 
struct good* copy(struct good*);//��������
void myfree(struct good*);//�ͷ�����
void check1(struct good*);//����Ʒ���Ų�ѯ
void check2(struct good*);//����Ʒ���Ʋ�ѯ

void allgood_boss(struct good*);//��������Ʒ�ܱ�
void inrecord_boss(struct good*);//������������¼
void newgood_boss(struct good*);//�����������Ʒ��Ϣ
void changegood_boss(struct good*);//�������޸���Ʒ��Ϣ
void check_good(struct good*);//��������ѯ��Ʒ
void sort_storage(struct good*);//��������Ʒ��ȱ�̶�����
void check_salesperson(struct good*);//����Ա����Ʒ��Ϣ��ѯ
void inprice_up_customer(struct good*);//�˿ͣ��۸���������
void inprice_down_customer(struct goood*);//�˿ͣ��۸����򣨽���
void fruit_customer(struct good*);//�˿ͣ�ˮ��ɸѡ
void veg_customer(struct good*);//�˿ͣ��߲�ɸѡ
void way_customer(struct good*);//�˿ͣ�������Ʒ
void youhui_customer(struct good*);//�˿ͣ��Ż���Ʒ
void sale_num_customer(struct good*);//�˿ͣ���������
void check_customer(struct good*);//�˿ͣ������Ʒ


/*���º����Ļ�����һ������ֻд���й���Ʒ�ġ�
������û����д�����á�
��������Ʒ�������һ��Ϊ�������棨��ûд�������ڡ���Ʒ����ѡ��
����Ա����Ʒ������һ��Ϊ����Ա���棬���ڡ���Ʒ��Ϣ��ѡ��
�˿͵���Ʒ������һ��Ϊ�˿ͽ��棬���ڡ������Ʒ��ѡ��
������ûд����֪���˿���Ϣ*/
void meun(struct good*);//��Ʒ������
void boss_good(struct good*);//��������Ʒ����
void salesperson_good(struct good*);//����Ա����Ʒ����
void customer_good(struct good*);//�˿͵���Ʒ����
void buy(struct good*);//������
void myexit();//�˳�ϵͳ


//��������
struct good* copy(struct good* head1) {
	struct good* head2, * p0, * p1,*tmp;
	head2 = (struct good*)malloc(sizeof(struct good));
	p0 = head2;
	tmp = head1->next;
	while (tmp != NULL) {    //��ʼ����
		p1 = (struct good*)malloc(sizeof(struct good));
		p0->next = p1;
		*p1 = *tmp;
		p1->next = NULL;
		p0 = p1;
		tmp = tmp->next;
	}
	return head2;//���ؿ���������ͷ
}
//�ͷ�����
void myfree(struct good* head) {
	struct good* tmp,*p;
	tmp = head;
	if (tmp == NULL)return;
	else {
		while (tmp != NULL) {
			p = tmp;
			tmp = tmp->next;
			free(p);
		}
	}
}
//���ļ���ȡ��Ϣ��������Ʒ����
struct good* build_good(){
	struct good* head, * tmp, * p;
	head = NULL;
	head = (struct good*)malloc(sizeof(struct good));
	tmp = head;
	FILE* fp = fopen("good.txt", "r");
	if (fp == NULL) {
		printf("���ļ�ʧ��");
		return head;
	}
	getc(fp);//�ȶ�ȡһ���ַ�
	if (feof(fp)) {//����ļ�Ϊ�գ���ʱָ�����û���κ��ַ���EOF�ѱ���ȡ������feof��fp��Ϊ��
		printf("�ļ�����Ʒ");
		return head;
	}
	else {
		rewind(fp);//��Ϊ֮ǰ�Ѷ�ȡһ���ַ�������Ҫ��ָ������ָ���ļ��Ŀ�ʼλ��
		while (!feof(fp)) {
			p = (struct good*)malloc(sizeof(struct good));
			fscanf(fp, "%s %s %d %d %d %s %s %s %d %d %d %d %d %s %s %s %s %s",
				p->code, p->name,&p->inprice,&p->outprice,&p->storage,p->type,p->unit,p->way,
				&p->sale_num,&p->indate.month,&p->indate.day,&p->deadline.month,&p->deadline.day,
				p->shangjia,p->tuihuo,p->youhui,p->origin,p->salesperson);
			p->next = NULL;
			tmp->next = p;
			tmp = p;
			getc(fp);//�ѻ��з���ȡ
		}//while
	}//else
	return head;
}
//��ѯ��Ʒ��Ϣ
void check(struct good* head) {
	if (head == NULL) {
		printf("û����Ʒ");
		return;
	}
	struct good* p;
	p = head->next;
	printf("��Ʒ���� ���� �ɱ� �۸� ��� ��λ �۳����� �������� ���ʽ�ֹ�� �Ƿ��ϼ� �Ƿ������˻� ������Ա\n");
	while (p != NULL) {
		printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
			p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
			p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
			p->shangjia,p->tuihuo, p->salesperson);
		p = p->next;
	}
}
//����Ʒ���Ų�ѯ
void check1(struct good* head) {
	struct good* p;
	bool flag = false;
	p = head->next;
	printf("\n��������Ʒ���ţ�");
	char str[10];
	scanf("%s", str);
	printf("\n");
	while (p != NULL) {
		if (strcmp(str, p->code) == 0) {
			flag = true;
			break;
		}
		p = p->next;
	}
	if (flag) {
		printf("��Ʒ���� ���� �ɱ� �۸� ��� ��λ �۳����� �������� ���ʽ�ֹ�� �Ƿ��ϼ� �Ƿ������˻� ������Ա\n");
		printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%12s",
			p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
			p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
			p->shangjia,p->tuihuo, p->salesperson);
		printf("\n");
	}
	else {
		printf("�޴���Ʒ��\n");
	}
}
//����Ʒ���Ʋ�ѯ
void check2(struct good* head) {
	struct good* p;
	bool flag = false;
	p = head->next;
	printf("\n��������Ʒ���ƣ�");
	char str[40];
	scanf("%s", str);
	printf("\n");
	while (p != NULL) {
		if (strcmp(str, p->name) == 0) {
			flag = true;
			break;
		}
		p = p->next;
	}
	if (flag) {
		printf("��Ʒ���� ���� �ɱ� �۸� ��� ��λ �۳����� �������� ���ʽ�ֹ�� �Ƿ��ϼ� �Ƿ������˻� ������Ա\n");
		printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%12s",
			p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
			p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
			p->shangjia,p->tuihuo, p->salesperson);
		printf("\n");
	}
	else {
		printf("�޴���Ʒ��\n");
	}
}
//�˳�
void myexit() {
	printf("����");
	exit(0);
}


/*������������к�������*/
//��������Ʒ�ܱ�
void allgood_boss(struct good* head) {
	system("cls");
	if (head == NULL || head->next == NULL) {
		printf("û����Ʒ��\n");
	}
	else {
		printf("��Ʒ���š����ơ���桪�Ƿ��ϼܡ��ɱ�������Ա����\n");
		struct good* p;
		p = head->next;
		while (p != NULL) {
			printf("%s%10s%5d%8s%8d%10s\n", 
				p->code, p->name, p->storage, p->shangjia,p->inprice, p->salesperson);
			p = p->next;
		}
	}
	int choice;
	printf("1.������һ��\n");
	printf("2.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://���ص�����Ʒ����
		boss_good(head);
		break;
	case 2://�˳�
		myexit();
		break;
	}

}
//������������¼
void inrecord_boss(struct good* head) {
	system("cls");
	if (head == NULL || head->next == NULL) {
		printf("û����Ʒ��");
	}
	else {
		printf("�������ڡ���Ʒ���š�-����-��-�۸�-��-��λ-��-���-�����ʽ�ֹ����-����Դ\n");
		struct good* p;
		p = head->next;
		while (p != NULL) {
			printf("%d/%d%11s%10s%8d%7s%8d%8d/%d%13s\n",
				p->indate.month,p->indate.day,p->code,p->name,p->outprice,p->unit,
				p->storage,p->deadline.month,p->deadline.day,p->origin);
			p = p->next;
		}
	}
	int choice;
	printf("1.������һ��\n");
	printf("2.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://���ص�����Ʒ����
		boss_good(head);
		break;
	case 2://�˳�
		myexit();
		break;
	}
}
//������¼����Ʒ��Ϣ
void newgood_boss(struct good* head) {
	system("cls");
	struct good* p, * tmp;
	tmp = head;
	while (tmp->next != NULL) tmp = tmp->next;
	p = (struct good*)malloc(sizeof(struct good));
	tmp->next = p;
	printf("������Ʒ���ţ� ");
	scanf("%s", p->code);
	printf("������Ʒ���ƣ�");
	scanf("%s", p->name);
	printf("������Ʒ�ɱ���");
	scanf("%d", &p->inprice);
	printf("������Ʒ�۸�");
	scanf("%d", &p->outprice);
	printf("������Ʒ��棺");
	scanf("%d", &p->storage);
	printf("������Ʒ���ͣ���ˮ��/�߲ˣ�");
	scanf("%s", p->type);
	printf("������Ʒ��λ������/��/�У�");
	scanf("%s", p->unit);
	printf("������Ʒ֧����ʽ��������/�ֽ���");
	scanf("%s", p->way);
	printf("������Ʒ�۳�������");
	scanf("%d", &p->sale_num);
	printf("������Ʒ�������ڣ����£�");
	scanf("%d", &p->indate.month);
	printf("������Ʒ�������ڣ����գ�");
	scanf("%d", &p->indate.day);
	printf("������Ʒ���ʽ�ֹ���ڣ����£�");
	scanf("%d", &p->deadline.month);
	printf("������Ʒ���ʽ�ֹ���ڣ����գ�");
	scanf("%d", &p->deadline.day);
	printf("��Ʒ�Ƿ��ϼܣ�����/��");
	scanf("%s", p->shangjia);
	printf("��Ʒ�Ƿ������˻�������/��");
	scanf("%s", p->tuihuo);
	printf("��Ʒ��Ϊ�Ż���Ʒ������/��");
	scanf("%s", p->youhui);
	printf("����Դ��");
	scanf("%s", p->origin);
	printf("������Ա��");
	scanf("%s", p->salesperson);
	p->next = NULL;
	FILE* fp = fopen("good.txt", "a");
	char ch = '\n';
	fputc(ch, fp);
	fprintf(fp, "%s %s %d %d %d %s %s %s %d %d %d %d %d %s %s %s %s %s",
		p->code, p->name, p->inprice, p->outprice, p->storage, p->type, p->unit, p->way,
		p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
		p->shangjia, p->tuihuo, p->youhui, p->origin, p->salesperson);
	fclose(fp);
	int choice;
	printf("1.����¼����Ʒ��Ϣ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://����¼�룬���µ���¼����Ʒ����
		newgood_boss(head);
		break;
	case 2://���ص�����Ʒ����
		boss_good(head);
		break;
	case 3://�˳�
		myexit();
		break;
	}
}
//�������޸���Ʒ��Ϣ
void changegood_boss(struct good* head) {
	system("cls");
	struct good* p, * tmp;
	char str[40];
	printf("�����޸���Ʒ���ƣ�");
	scanf("%s", str);
	bool flag = false;
	p = head;
	while (p != NULL) {
		if (strcmp(str, p->name) == 0) {
			flag = true;
			break;
		}
		else p = p->next;
	}
	if (flag) {
		int choice;
		printf("1.�޸ĳɱ�\n");
		printf("2.�޸ļ۸�\n");
		printf("3.�޸Ŀ��\n");
		printf("4.�޸ĵ�λ\n");
		printf("5.�޸�֧����ʽ\n");
		printf("6.�޸��۳�����\n");
		printf("7.�޸Ľ�������\n");
		printf("8.�޸ı��ʽ�ֹ��\n");
		printf("9.�޸��Ƿ��ϼ�\n");
		printf("10.�޸��Ƿ������˻�\n");
		printf("11.�޸��Ƿ��Ż�\n");
		printf("12.�޸Ľ���Դ\n");
		printf("13.�޸�������Ա\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:printf("����ɱ�\n");
			scanf("%d", &p->inprice);
			break;
		case 2:printf("����۸�\n");
			scanf("%d", &p->outprice);
			break;
		case 3:printf("������\n");
			scanf("%d", &p->storage);
			break;
		case 4:printf("���뵥λ����/��/�У�\n");
			scanf("%s", p->unit);
			break;
		case 5:printf("����֧����ʽ������/�ֽ���\n");
			scanf("%s", p->way);
			break;
		case 6:printf("�����۳�����\n");
			scanf("%d", &p->sale_num);
			break;
		case 7:printf("����������ڣ��£�\n");
			scanf("%d", &p->indate.month);
			printf("����������ڣ��գ�\n");
			scanf("%d", &p->indate.day);
			break;
		case 8:printf("���뱣�ʽ�ֹ�ڣ��£�\n");
			scanf("%d", &p->deadline.month);
			printf("���뱣�ʽ�ֹ�ڣ��գ�\n");
			scanf("%d", &p->deadline.day);
			break;
		case 9:printf("�����Ƿ��ϼ�\n");
			scanf("%s", p->shangjia);
			break;
		case 10:printf("�Ƿ������˻�\n");
			scanf("%s", p->tuihuo);
			break;
		case 11:printf("�Ƿ��Ż�\n");
			scanf("%s", p->youhui);
			break;
		case 12:printf("�޸Ľ���Դ\n");
			scanf("%s", p->origin);
			break;
		case 13:printf("�޸�������Ա\n");
			scanf("%s", p->salesperson);
			break;
		default:printf("����ȷ����ѡ�");
			changegood_boss(head);
		}//switch
		printf("1.�����޸�\n");
		printf("2.���޸���\n");
		int choice2;
		scanf("%d", &choice2);
		switch (choice2) {
		case 1://�����޸ģ����µ����޸���Ʒ��Ϣ����
			changegood_boss(head);
			break;
		case 2://��������
			break;
		}


	}//if
	else {
		printf("�޴���Ʒ��");
		changegood_boss(head);
	}
	//���޸ĺ����Ϣ����¼�뵽�ļ���
	FILE* fp = fopen("good.txt", "w");
	tmp = head->next;
	while (tmp != NULL) {
		fprintf(fp, "%s %s %d %d %d %s %s %s %d %d %d %d %d %s %s %s %s %s",
			tmp->code, tmp->name, tmp->inprice, tmp->outprice, tmp->storage, tmp->type, tmp->unit, tmp->way,
			tmp->sale_num, tmp->indate.month, tmp->indate.day, tmp->deadline.month, tmp->deadline.day,
			tmp->shangjia, tmp->tuihuo, tmp->youhui, tmp->origin, tmp->salesperson);
		if (tmp->next != NULL) {
			char ch = '\n';
			fputc(ch, fp);
		}
		tmp = tmp->next;
	}
	fclose(fp);
	//���ص�������Ʒ����
	boss_good(head);
}
//��������ѯ��Ʒ
void check_good(struct good* head) {
	system("cls");
	int choice;
	printf("1.����Ʒ���Ų�ѯ\n");
	printf("2.����Ʒ���Ʋ�ѯ\n");
	printf("3.������һ��\n");
	printf("4.�˳�\n");
	printf("\n������ѡ� ");
	scanf("%d", &choice);
	switch (choice) {
	case 1://����Ʒ���Ų�ѯ
		check1(head);
		break;
	case 2://����Ʒ���Ʋ�ѯ
		check2(head);
		break;
	case 3://���ص�����Ʒ��Ϣ
		boss_good(head);
		break;
	case 4://�˳�ϵͳ
		myexit();
		break;
	}
	printf("\n");
	int choice2;
	printf("1.������ѯ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("�����룺");
	scanf("%d", &choice2);
	switch (choice2) {
	case 1://������ѯ�����µ��ò�ѯ��Ʒ����
		check_good(head);
		break;
	case 2://���ص�����Ʒ����
		boss_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit(head);
		break;
	}
}
//��������Ʒ��ȱ�̶Ȳ�ѯ������
void sort_storage(struct good* head) {
	system("cls");
	struct good* head2 = copy(head);
	struct good* p, * p0, * r, * r0, * q;
	p0 = NULL;
	p = head2->next;
	//�������򣨵�����
	while (p != NULL) {
		r = head2->next;
		while ((r->storage < p->storage) && (r != p)) {
			r0 = r;
			r = r->next;
		}
		//p����r0��r֮��
		if (r != p) {
			q = p;
			p0->next = p->next;
			p = p0;
			if (r == head2->next) {
				q->next = head2->next;
				head2->next = q;
			}
			else {
				q->next = r;
				r0->next = q;
			}//if(r==head2->next)
		}//if(r!=p)
		p0 = p;
		p = p->next;
	}//while

	check(head2);
	myfree(head2);
	int choice;
	printf("1.������һ��\n");
	printf("2.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://���ص�����Ʒ����
		boss_good(head);
		break;
	case 2://�˳�ϵͳ
		myexit();
		break;
	}
}

/*����Ա��Ʒ�����к���*/
//����Ա����Ʒ��Ϣ��ѯ
void check_salesperson(struct good* head) {
	system("cls");
	struct good* p;
	bool flag = false;
	p = head->next;
	printf("����������Ա������");
	char str[40];
	scanf("%s", str);
	printf("\n");
	while (p != NULL) {
		if (strcmp(str, p->salesperson) == 0) {
			flag = true;
			break;
		}
		p = p->next;
	}
	if (flag) {
		printf("��Ʒ����  ����   �۸� ��� ��λ  �������� ���ʽ�ֹ�� �Ƿ��ϼ� �Ƿ������˻�\n");
		printf("%s%10s%5d%5d%5s%5d/%d%8d/%d%10s%10s",
			p->code, p->name,  p->outprice, p->storage, p->unit,
			p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
			p->shangjia, p->tuihuo);
		printf("\n");
	}
	else {
		printf("���޴��ˣ�\n");
	}
	printf("1.������һ��\n");
	printf("2.�˳�\n");
	int choice;
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://��������Ա��Ʒ����
		salesperson_good(head);
		break;
	case 2://�˳�ϵͳ
		myexit();
		break;
	}
}

/*�˿���Ʒ�����к���*/
//�˿ͣ��۸���������
void inprice_up_customer(struct good* head) {
	system("cls");
	struct good* head2 = copy(head);
	struct good* p, * p0, * r, * r0, * q;
	p0 = NULL;
	p = head2->next;
	//�������򣨵�����
	while (p != NULL) {
		r = head2->next;
		while ((r->inprice < p->inprice) && (r != p)) {
			r0 = r;
			r = r->next;
		}
		//p����r0��r֮��
		if (r != p) {
			q = p;
			p0->next = p->next;
			p = p0;
			if (r == head2->next) {
				q->next = head2->next;
				head2->next = q;
			}
			else {
				q->next = r;
				r0->next = q;
			}//if(r==head2->next)
		}//if(r!=p)
		p0 = p;
		p = p->next;
	}//while
	check(head2);
	myfree(head2);
	int choice;
	printf("1.������Ʒ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://������Ʒ
		buy(head);
		break;
	case 2://���ع˿���Ʒ����
		customer_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit();
		break;
	}
}
//�˿ͣ��۸����򣨽���
void inprice_down_customer(struct goood* head) {
	system("cls");
	struct good* head2 = copy(head);
	struct good* p, * p0, * r, * r0, * q;
	p0 = NULL;
	p = head2->next;
	//�������򣨵ݼ���
	while (p != NULL) {
		r = head2->next;
		while ((r->inprice > p->inprice) && (r != p)) {
			r0 = r;
			r = r->next;
		}
		//p����r0��r֮��
		if (r != p) {
			q = p;
			p0->next = p->next;
			p = p0;
			if (r == head2->next) {
				q->next = head2->next;
				head2->next = q;
			}
			else {
				q->next = r;
				r0->next = q;
			}//if(r==head2->next)
		}//if(r!=p)
		p0 = p;
		p = p->next;
	}//while
	check(head2);
	myfree(head2);
	int choice;
	printf("1.������Ʒ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://������Ʒ
		buy(head);
		break;
	case 2://���ع˿���Ʒ����
		customer_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit();
		break;
	}
}
//�˿ͣ�ˮ��ɸѡ
void fruit_customer(struct good* head) {
	system("cls");
	printf("��Ʒ���� ���� �ɱ� �۸� ��� ��λ �۳����� �������� ���ʽ�ֹ�� �Ƿ��ϼ� �Ƿ������˻� ������Ա\n");
	struct good* p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->type, "ˮ��") == 0) {
			printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
				p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
				p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
				p->shangjia, p->tuihuo ,p->salesperson);
		}
		p = p->next;
	}
	int choice;
	printf("1.������Ʒ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://������Ʒ
		buy(head);
		break;
	case 2://���ع˿���Ʒ����
		customer_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit();
		break;
	}
}
//�˿ͣ��߲�ɸѡ
void veg_customer(struct good* head) {
	system("cls");
	printf("��Ʒ���� ���� �ɱ� �۸� ��� ��λ �۳����� �������� ���ʽ�ֹ�� �Ƿ��ϼ� �Ƿ������˻� ������Ա\n");
	struct good* p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->type, "�߲�") == 0) {
			printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
				p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
				p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
				p->shangjia,p->tuihuo , p->salesperson);
		}
		p = p->next;
	}
	int choice;
	printf("1.������Ʒ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://������Ʒ
		buy(head);
		break;
	case 2://���ع˿���Ʒ����
		customer_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit();
		break;
	}
}
//�˿ͣ�������Ʒ
void way_customer(struct good* head) {
	system("cls");
	printf("��Ʒ���� ���� �ɱ� �۸� ��� ��λ �۳����� �������� ���ʽ�ֹ�� �Ƿ��ϼ� �Ƿ������˻� ������Ա\n");
	struct good* p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->way, "����") == 0) {
			printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
				p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
				p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
				p->shangjia,p->tuihuo , p->salesperson);
		}
		p = p->next;
	}
	int choice;
	printf("1.������Ʒ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://������Ʒ
		buy(head);
		break;
	case 2://���ع˿���Ʒ����
		customer_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit();
		break;
	}
}
//�˿ͣ��Ż���Ʒ
void youhui_customer(struct good* head) {
	system("cls");
	printf("��Ʒ���� ���� �ɱ� �۸� ��� ��λ �۳����� �������� ���ʽ�ֹ�� �Ƿ��ϼ� �Ƿ������˻� ������Ա\n");
	struct good* p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->youhui, "��") == 0) {
			printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
				p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
				p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
				p->shangjia,p->tuihuo, p->salesperson);
		}
		p = p->next;
	}
	int choice;
	printf("1.������Ʒ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://������Ʒ
		buy(head);
		break;
	case 2://���ع˿���Ʒ����
		customer_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit();
		break;
	}
}
//�˿ͣ���������
void sale_num_customer(struct good* head) {
	system("cls");
	struct good* head2 = copy(head);
	struct good* p, * p0, * r, * r0, * q;
	p0 = NULL;
	p = head2->next;
	//�������򣨵�����
	while (p != NULL) {
		r = head2->next;
		while ((r->sale_num > p->sale_num) && (r != p)) {
			r0 = r;
			r = r->next;
		}
		//p����r0��r֮��
		if (r != p) {
			q = p;
			p0->next = p->next;
			p = p0;
			if (r == head2->next) {
				q->next = head2->next;
				head2->next = q;
			}
			else {
				q->next = r;
				r0->next = q;
			}//if(r==head2->next)
		}//if(r!=p)
		p0 = p;
		p = p->next;
	}//while
	check(head2);
	myfree(head2);
	int choice;
	printf("1.������Ʒ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://������Ʒ
		buy(head);
		break;
	case 2://���ع˿���Ʒ����
		customer_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit();
		break;
	}
}
//�˿ͣ������Ʒ
void check_customer(struct good* head) {
	check2(head);
	int choice;
	printf("1.������Ʒ\n");
	printf("2.������һ��\n");
	printf("3.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch (choice) {
	case 1://������Ʒ
		buy(head);
		break;
	case 2://���ع˿���Ʒ����
		customer_good(head);
		break;
	case 3://�˳�ϵͳ
		myexit();
		break;
	}
}



//��Ʒ������
void meun(struct good* head) {
	system("cls");
	int choice;
	printf("\t0.�˳�ϵͳ\n");
	printf("\t1.����\n");
	printf("\t2.����Ա\n");
	printf("\t3.�˿�\n");
	printf("������\n");
	scanf("%d", &choice);
	switch (choice) {
	case 0://�˳�ϵͳ
		myexit();
		break;
	case 1://������Ʒ����
		boss_good(head);
		break;
	case 2://����Ա��Ʒ����
		salesperson_good(head);
		break;
	case 3://�˿���Ʒ����
		customer_good(head);
		break;
	default:printf("�������\n");
		break;
	}
}
//��������Ʒ����
void boss_good(struct good* head) {
	system("cls");
	int choice;
	printf("\t0.������һ��\n");
	printf("\t1.��Ʒ�ܱ�\n");
	printf("\t2.������¼\n");
	printf("\t3.��Ʒ���\n");
	printf("\t4.��Ʒ��Ϣ�޸�\n");
	printf("\t5.��Ʒ��Ϣ��ѯ\n");
	printf("\t6.��Ʒ��ȱ�̶Ȳ�ѯ\n");
	printf("\t7.�˳�\n");
	printf("������\n");
	scanf("%d", &choice);
	switch (choice) {
	case 0:meun(head);
		break;
	case 1:allgood_boss(head);
		break;
	case 2:inrecord_boss(head);
		break;
	case 3:newgood_boss(head);
		break;
	case 4:changegood_boss(head);
		break;
	case 5:check_good(head);
		break;
	case 6:sort_storage(head);
		break;
	case 7:myexit();
		break;
	}
}
//����Ա����Ʒ����
void salesperson_good(struct good* head) {
	system("cls");
	printf("\t1.��ʼ��Ʒ��Ϣ��ѯ\n");
	printf("\t2.������һ��\n");
	printf("\t3.�˳�\n");
	printf("�����룺");
	int choice;
	scanf("%d", &choice);
	switch (choice) {
	case 1:check_salesperson(head);
		break;
	case 2:meun(head);
		break;
	case 3:myexit();
		break;
	}
}
//�˿͵���Ʒ����
void customer_good(struct good* head) {
	system("cls");
	int choice;
	printf("\t1.���۸���������\n");
	printf("\t2.���۸�������\n");
	printf("\t3.ɸѡˮ��\n");
	printf("\t4.ɸѡ�߲�\n");
	printf("\t5.������Ʒ�б�\n");
	printf("\t6.�Ż���Ʒ�б�\n");
	printf("\t7.�������а�\n");
	printf("\t8.�����Ʒ\n");
	printf("\t9.������һ��\n");
	printf("\t10.�˳�\n");
	printf("������ѡ�");
	scanf("%d", &choice);
	switch(choice){
	case 1:inprice_up_customer(head);
		break;
	case 2:inprice_down_customer(head);
		break;
	case 3:fruit_customer(head);
		break;
	case 4:veg_customer(head);
		break;
	case 5:way_customer(head);
		break;
	case 6:youhui_customer(head);
		break;
	case 7:sale_num_customer(head);
		break;
	case 8:check_customer(head);
	case 9:meun(head);
		break;
	case 10:myexit();
		break;
	}
}
//������
void buy(struct good* head) {
	printf("�Ρ�������\n");
	printf("����ɹ�\n");
	int choice;
	printf("1.���ع˿ͽ���\n");
	printf("2.�˳�\n");
	printf("�����룺");
	scanf("%d", &choice);
	switch (choice) {
	case 1:customer_good(head);
		break;
	case 2:myexit();
		break;
	}
}



int main() {
	struct good* Goods = build_good();
	meun(Goods);
	return 0;
}