#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
typedef struct {//日期结构体
	int month;
	int day;
}Date;
//商品结构体
struct good {
	char code[10];//商品序号
	char name[40];//商品名称
	int inprice;//成本
	int outprice;//价格
	int storage;//库存
	char type[10];//商品类型
	char unit[10];//单位
	char way[10];//支付方式
	int sale_num;//售出单数
	Date indate;//进货日期
	Date deadline;//保质截止期
	char shangjia[5];//是否上架
	char tuihuo[5];//是否退货
	char youhui[5];//是否优惠
	char origin[40];//进货源
	char salesperson[40];//销售人员姓名
	struct good *next;
};

struct good* build_good();//从文件读取信息，创建商品链表 
void check(struct good*);//查看商品信息 
struct good* copy(struct good*);//复制链表
void myfree(struct good*);//释放链表
void check1(struct good*);//以商品代号查询
void check2(struct good*);//以商品名称查询

void allgood_boss(struct good*);//店主：商品总表单
void inrecord_boss(struct good*);//店主：进货记录
void newgood_boss(struct good*);//店主：添加商品信息
void changegood_boss(struct good*);//店主：修改商品信息
void check_good(struct good*);//店主：查询商品
void sort_storage(struct good*);//店主：商品紧缺程度排序
void check_salesperson(struct good*);//销售员：商品信息查询
void inprice_up_customer(struct good*);//顾客：价格排序（升序）
void inprice_down_customer(struct goood*);//顾客：价格排序（降序）
void fruit_customer(struct good*);//顾客：水果筛选
void veg_customer(struct good*);//顾客：蔬菜筛选
void way_customer(struct good*);//顾客：积分商品
void youhui_customer(struct good*);//顾客：优惠商品
void sale_num_customer(struct good*);//顾客：热销排序
void check_customer(struct good*);//顾客：浏览商品


/*以下函数的还有上一级，我只写了有关商品的。
主界面没认真写，别用。
店主的商品界面的上一级为店主界面（我没写），属于“商品管理”选项
销售员的商品界面上一级为销售员界面，属于“商品信息”选项
顾客的商品界面上一级为顾客界面，属于“浏览商品”选项
购买函数没写，不知道顾客信息*/
void meun(struct good*);//商品主界面
void boss_good(struct good*);//店主的商品界面
void salesperson_good(struct good*);//销售员的商品界面
void customer_good(struct good*);//顾客的商品界面
void buy(struct good*);//购买函数
void myexit();//退出系统


//复制链表
struct good* copy(struct good* head1) {
	struct good* head2, * p0, * p1,*tmp;
	head2 = (struct good*)malloc(sizeof(struct good));
	p0 = head2;
	tmp = head1->next;
	while (tmp != NULL) {    //开始拷贝
		p1 = (struct good*)malloc(sizeof(struct good));
		p0->next = p1;
		*p1 = *tmp;
		p1->next = NULL;
		p0 = p1;
		tmp = tmp->next;
	}
	return head2;//返回拷贝的链表头
}
//释放链表
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
//从文件读取信息，创建商品链表
struct good* build_good(){
	struct good* head, * tmp, * p;
	head = NULL;
	head = (struct good*)malloc(sizeof(struct good));
	tmp = head;
	FILE* fp = fopen("good.txt", "r");
	if (fp == NULL) {
		printf("打开文件失败");
		return head;
	}
	getc(fp);//先读取一个字符
	if (feof(fp)) {//如果文件为空，此时指针后面没有任何字符（EOF已被读取），则feof（fp）为真
		printf("文件无商品");
		return head;
	}
	else {
		rewind(fp);//因为之前已读取一个字符，所以要把指针重新指向文件的开始位置
		while (!feof(fp)) {
			p = (struct good*)malloc(sizeof(struct good));
			fscanf(fp, "%s %s %d %d %d %s %s %s %d %d %d %d %d %s %s %s %s %s",
				p->code, p->name,&p->inprice,&p->outprice,&p->storage,p->type,p->unit,p->way,
				&p->sale_num,&p->indate.month,&p->indate.day,&p->deadline.month,&p->deadline.day,
				p->shangjia,p->tuihuo,p->youhui,p->origin,p->salesperson);
			p->next = NULL;
			tmp->next = p;
			tmp = p;
			getc(fp);//把换行符读取
		}//while
	}//else
	return head;
}
//查询商品信息
void check(struct good* head) {
	if (head == NULL) {
		printf("没有商品");
		return;
	}
	struct good* p;
	p = head->next;
	printf("商品代号 名称 成本 价格 库存 单位 售出单数 进货日期 保质截止期 是否上架 是否予以退货 销售人员\n");
	while (p != NULL) {
		printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
			p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
			p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
			p->shangjia,p->tuihuo, p->salesperson);
		p = p->next;
	}
}
//以商品代号查询
void check1(struct good* head) {
	struct good* p;
	bool flag = false;
	p = head->next;
	printf("\n请输入商品代号：");
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
		printf("商品代号 名称 成本 价格 库存 单位 售出单数 进货日期 保质截止期 是否上架 是否予以退货 销售人员\n");
		printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%12s",
			p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
			p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
			p->shangjia,p->tuihuo, p->salesperson);
		printf("\n");
	}
	else {
		printf("无此商品！\n");
	}
}
//以商品名称查询
void check2(struct good* head) {
	struct good* p;
	bool flag = false;
	p = head->next;
	printf("\n请输入商品名称：");
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
		printf("商品代号 名称 成本 价格 库存 单位 售出单数 进货日期 保质截止期 是否上架 是否予以退货 销售人员\n");
		printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%12s",
			p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
			p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
			p->shangjia,p->tuihuo, p->salesperson);
		printf("\n");
	}
	else {
		printf("无此商品！\n");
	}
}
//退出
void myexit() {
	printf("退了");
	exit(0);
}


/*店主界面的所有函数定义*/
//店主：商品总表单
void allgood_boss(struct good* head) {
	system("cls");
	if (head == NULL || head->next == NULL) {
		printf("没有商品！\n");
	}
	else {
		printf("商品代号—名称—库存—是否上架—成本—销售员姓名\n");
		struct good* p;
		p = head->next;
		while (p != NULL) {
			printf("%s%10s%5d%8s%8d%10s\n", 
				p->code, p->name, p->storage, p->shangjia,p->inprice, p->salesperson);
			p = p->next;
		}
	}
	int choice;
	printf("1.返回上一级\n");
	printf("2.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://返回店主商品界面
		boss_good(head);
		break;
	case 2://退出
		myexit();
		break;
	}

}
//店主：进货记录
void inrecord_boss(struct good* head) {
	system("cls");
	if (head == NULL || head->next == NULL) {
		printf("没有商品！");
	}
	else {
		printf("进货日期—商品代号—-名称-—-价格-—-单位-—-库存-—保质截止日期-—货源\n");
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
	printf("1.返回上一级\n");
	printf("2.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://返回店主商品界面
		boss_good(head);
		break;
	case 2://退出
		myexit();
		break;
	}
}
//店主：录入商品信息
void newgood_boss(struct good* head) {
	system("cls");
	struct good* p, * tmp;
	tmp = head;
	while (tmp->next != NULL) tmp = tmp->next;
	p = (struct good*)malloc(sizeof(struct good));
	tmp->next = p;
	printf("输入商品代号： ");
	scanf("%s", p->code);
	printf("输入商品名称：");
	scanf("%s", p->name);
	printf("输入商品成本：");
	scanf("%d", &p->inprice);
	printf("输入商品价格：");
	scanf("%d", &p->outprice);
	printf("输入商品库存：");
	scanf("%d", &p->storage);
	printf("输入商品类型：（水果/蔬菜）");
	scanf("%s", p->type);
	printf("输入商品单位：（斤/个/盒）");
	scanf("%s", p->unit);
	printf("输入商品支付方式：（积分/现金余额）");
	scanf("%s", p->way);
	printf("输入商品售出单数：");
	scanf("%d", &p->sale_num);
	printf("输入商品进货日期：（月）");
	scanf("%d", &p->indate.month);
	printf("输入商品进货日期：（日）");
	scanf("%d", &p->indate.day);
	printf("输入商品保质截止日期：（月）");
	scanf("%d", &p->deadline.month);
	printf("输入商品保质截止日期：（日）");
	scanf("%d", &p->deadline.day);
	printf("商品是否上架：（是/否）");
	scanf("%s", p->shangjia);
	printf("商品是否予以退货：（是/否）");
	scanf("%s", p->tuihuo);
	printf("商品否为优惠商品：（是/否）");
	scanf("%s", p->youhui);
	printf("进货源：");
	scanf("%s", p->origin);
	printf("销售人员：");
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
	printf("1.继续录入商品信息\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://继续录入，重新调用录入商品函数
		newgood_boss(head);
		break;
	case 2://返回店主商品界面
		boss_good(head);
		break;
	case 3://退出
		myexit();
		break;
	}
}
//店主：修改商品信息
void changegood_boss(struct good* head) {
	system("cls");
	struct good* p, * tmp;
	char str[40];
	printf("输入修改商品名称：");
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
		printf("1.修改成本\n");
		printf("2.修改价格\n");
		printf("3.修改库存\n");
		printf("4.修改单位\n");
		printf("5.修改支付方式\n");
		printf("6.修改售出单数\n");
		printf("7.修改进货日期\n");
		printf("8.修改保质截止期\n");
		printf("9.修改是否上架\n");
		printf("10.修改是否予以退货\n");
		printf("11.修改是否优惠\n");
		printf("12.修改进货源\n");
		printf("13.修改销售人员\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:printf("输入成本\n");
			scanf("%d", &p->inprice);
			break;
		case 2:printf("输入价格\n");
			scanf("%d", &p->outprice);
			break;
		case 3:printf("输入库存\n");
			scanf("%d", &p->storage);
			break;
		case 4:printf("输入单位（斤/个/盒）\n");
			scanf("%s", p->unit);
			break;
		case 5:printf("输入支付方式（积分/现金余额）\n");
			scanf("%s", p->way);
			break;
		case 6:printf("输入售出单数\n");
			scanf("%d", &p->sale_num);
			break;
		case 7:printf("输入进货日期（月）\n");
			scanf("%d", &p->indate.month);
			printf("输入进货日期（日）\n");
			scanf("%d", &p->indate.day);
			break;
		case 8:printf("输入保质截止期（月）\n");
			scanf("%d", &p->deadline.month);
			printf("输入保质截止期（日）\n");
			scanf("%d", &p->deadline.day);
			break;
		case 9:printf("输入是否上架\n");
			scanf("%s", p->shangjia);
			break;
		case 10:printf("是否予以退货\n");
			scanf("%s", p->tuihuo);
			break;
		case 11:printf("是否优惠\n");
			scanf("%s", p->youhui);
			break;
		case 12:printf("修改进货源\n");
			scanf("%s", p->origin);
			break;
		case 13:printf("修改销售人员\n");
			scanf("%s", p->salesperson);
			break;
		default:printf("请正确输入选项！");
			changegood_boss(head);
		}//switch
		printf("1.继续修改\n");
		printf("2.不修改了\n");
		int choice2;
		scanf("%d", &choice2);
		switch (choice2) {
		case 1://继续修改，重新调用修改商品信息函数
			changegood_boss(head);
			break;
		case 2://继续运行
			break;
		}


	}//if
	else {
		printf("无此商品！");
		changegood_boss(head);
	}
	//将修改后的信息重新录入到文件中
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
	//返回到店主商品界面
	boss_good(head);
}
//店主：查询商品
void check_good(struct good* head) {
	system("cls");
	int choice;
	printf("1.以商品代号查询\n");
	printf("2.以商品名称查询\n");
	printf("3.返回上一级\n");
	printf("4.退出\n");
	printf("\n请输入选项： ");
	scanf("%d", &choice);
	switch (choice) {
	case 1://以商品代号查询
		check1(head);
		break;
	case 2://以商品名称查询
		check2(head);
		break;
	case 3://返回店主商品信息
		boss_good(head);
		break;
	case 4://退出系统
		myexit();
		break;
	}
	printf("\n");
	int choice2;
	printf("1.继续查询\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入：");
	scanf("%d", &choice2);
	switch (choice2) {
	case 1://继续查询，重新调用查询商品函数
		check_good(head);
		break;
	case 2://返回店主商品界面
		boss_good(head);
		break;
	case 3://退出系统
		myexit(head);
		break;
	}
}
//店主：商品紧缺程度查询（升序）
void sort_storage(struct good* head) {
	system("cls");
	struct good* head2 = copy(head);
	struct good* p, * p0, * r, * r0, * q;
	p0 = NULL;
	p = head2->next;
	//插入排序（递增）
	while (p != NULL) {
		r = head2->next;
		while ((r->storage < p->storage) && (r != p)) {
			r0 = r;
			r = r->next;
		}
		//p插入r0与r之间
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
	printf("1.返回上一级\n");
	printf("2.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://返回店主商品界面
		boss_good(head);
		break;
	case 2://退出系统
		myexit();
		break;
	}
}

/*销售员商品的所有函数*/
//销售员：商品信息查询
void check_salesperson(struct good* head) {
	system("cls");
	struct good* p;
	bool flag = false;
	p = head->next;
	printf("请输入销售员姓名：");
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
		printf("商品代号  名称   价格 库存 单位  进货日期 保质截止期 是否上架 是否予以退货\n");
		printf("%s%10s%5d%5d%5s%5d/%d%8d/%d%10s%10s",
			p->code, p->name,  p->outprice, p->storage, p->unit,
			p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
			p->shangjia, p->tuihuo);
		printf("\n");
	}
	else {
		printf("查无此人！\n");
	}
	printf("1.返回上一级\n");
	printf("2.退出\n");
	int choice;
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://返回销售员商品界面
		salesperson_good(head);
		break;
	case 2://退出系统
		myexit();
		break;
	}
}

/*顾客商品的所有函数*/
//顾客：价格排序（升序）
void inprice_up_customer(struct good* head) {
	system("cls");
	struct good* head2 = copy(head);
	struct good* p, * p0, * r, * r0, * q;
	p0 = NULL;
	p = head2->next;
	//插入排序（递增）
	while (p != NULL) {
		r = head2->next;
		while ((r->inprice < p->inprice) && (r != p)) {
			r0 = r;
			r = r->next;
		}
		//p插入r0与r之间
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
	printf("1.购买商品\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://购买商品
		buy(head);
		break;
	case 2://返回顾客商品界面
		customer_good(head);
		break;
	case 3://退出系统
		myexit();
		break;
	}
}
//顾客：价格排序（降序）
void inprice_down_customer(struct goood* head) {
	system("cls");
	struct good* head2 = copy(head);
	struct good* p, * p0, * r, * r0, * q;
	p0 = NULL;
	p = head2->next;
	//插入排序（递减）
	while (p != NULL) {
		r = head2->next;
		while ((r->inprice > p->inprice) && (r != p)) {
			r0 = r;
			r = r->next;
		}
		//p插入r0与r之间
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
	printf("1.购买商品\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://购买商品
		buy(head);
		break;
	case 2://返回顾客商品界面
		customer_good(head);
		break;
	case 3://退出系统
		myexit();
		break;
	}
}
//顾客：水果筛选
void fruit_customer(struct good* head) {
	system("cls");
	printf("商品代号 名称 成本 价格 库存 单位 售出单数 进货日期 保质截止期 是否上架 是否予以退货 销售人员\n");
	struct good* p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->type, "水果") == 0) {
			printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
				p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
				p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
				p->shangjia, p->tuihuo ,p->salesperson);
		}
		p = p->next;
	}
	int choice;
	printf("1.购买商品\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://购买商品
		buy(head);
		break;
	case 2://返回顾客商品界面
		customer_good(head);
		break;
	case 3://退出系统
		myexit();
		break;
	}
}
//顾客：蔬菜筛选
void veg_customer(struct good* head) {
	system("cls");
	printf("商品代号 名称 成本 价格 库存 单位 售出单数 进货日期 保质截止期 是否上架 是否予以退货 销售人员\n");
	struct good* p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->type, "蔬菜") == 0) {
			printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
				p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
				p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
				p->shangjia,p->tuihuo , p->salesperson);
		}
		p = p->next;
	}
	int choice;
	printf("1.购买商品\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://购买商品
		buy(head);
		break;
	case 2://返回顾客商品界面
		customer_good(head);
		break;
	case 3://退出系统
		myexit();
		break;
	}
}
//顾客：积分商品
void way_customer(struct good* head) {
	system("cls");
	printf("商品代号 名称 成本 价格 库存 单位 售出单数 进货日期 保质截止期 是否上架 是否予以退货 销售人员\n");
	struct good* p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->way, "积分") == 0) {
			printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
				p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
				p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
				p->shangjia,p->tuihuo , p->salesperson);
		}
		p = p->next;
	}
	int choice;
	printf("1.购买商品\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://购买商品
		buy(head);
		break;
	case 2://返回顾客商品界面
		customer_good(head);
		break;
	case 3://退出系统
		myexit();
		break;
	}
}
//顾客：优惠商品
void youhui_customer(struct good* head) {
	system("cls");
	printf("商品代号 名称 成本 价格 库存 单位 售出单数 进货日期 保质截止期 是否上架 是否予以退货 销售人员\n");
	struct good* p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->youhui, "是") == 0) {
			printf("%s%10s%3d%5d%5d%5s%5d%8d/%d%8d/%d%10s%10s%10s\n",
				p->code, p->name, p->inprice, p->outprice, p->storage, p->unit,
				p->sale_num, p->indate.month, p->indate.day, p->deadline.month, p->deadline.day,
				p->shangjia,p->tuihuo, p->salesperson);
		}
		p = p->next;
	}
	int choice;
	printf("1.购买商品\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://购买商品
		buy(head);
		break;
	case 2://返回顾客商品界面
		customer_good(head);
		break;
	case 3://退出系统
		myexit();
		break;
	}
}
//顾客：热销排序
void sale_num_customer(struct good* head) {
	system("cls");
	struct good* head2 = copy(head);
	struct good* p, * p0, * r, * r0, * q;
	p0 = NULL;
	p = head2->next;
	//插入排序（递增）
	while (p != NULL) {
		r = head2->next;
		while ((r->sale_num > p->sale_num) && (r != p)) {
			r0 = r;
			r = r->next;
		}
		//p插入r0与r之间
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
	printf("1.购买商品\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://购买商品
		buy(head);
		break;
	case 2://返回顾客商品界面
		customer_good(head);
		break;
	case 3://退出系统
		myexit();
		break;
	}
}
//顾客：浏览商品
void check_customer(struct good* head) {
	check2(head);
	int choice;
	printf("1.购买商品\n");
	printf("2.返回上一级\n");
	printf("3.退出\n");
	printf("请输入选项：");
	scanf("%d", &choice);
	switch (choice) {
	case 1://购买商品
		buy(head);
		break;
	case 2://返回顾客商品界面
		customer_good(head);
		break;
	case 3://退出系统
		myexit();
		break;
	}
}



//商品主界面
void meun(struct good* head) {
	system("cls");
	int choice;
	printf("\t0.退出系统\n");
	printf("\t1.店主\n");
	printf("\t2.销售员\n");
	printf("\t3.顾客\n");
	printf("请输入\n");
	scanf("%d", &choice);
	switch (choice) {
	case 0://退出系统
		myexit();
		break;
	case 1://店主商品界面
		boss_good(head);
		break;
	case 2://销售员商品界面
		salesperson_good(head);
		break;
	case 3://顾客商品界面
		customer_good(head);
		break;
	default:printf("输入错误！\n");
		break;
	}
}
//店主的商品界面
void boss_good(struct good* head) {
	system("cls");
	int choice;
	printf("\t0.返回上一级\n");
	printf("\t1.商品总表单\n");
	printf("\t2.进货记录\n");
	printf("\t3.商品添加\n");
	printf("\t4.商品信息修改\n");
	printf("\t5.商品信息查询\n");
	printf("\t6.商品紧缺程度查询\n");
	printf("\t7.退出\n");
	printf("请输入\n");
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
//销售员的商品界面
void salesperson_good(struct good* head) {
	system("cls");
	printf("\t1.开始商品信息查询\n");
	printf("\t2.返回上一级\n");
	printf("\t3.退出\n");
	printf("请输入：");
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
//顾客的商品界面
void customer_good(struct good* head) {
	system("cls");
	int choice;
	printf("\t1.按价格升序排序\n");
	printf("\t2.按价格降序排序\n");
	printf("\t3.筛选水果\n");
	printf("\t4.筛选蔬菜\n");
	printf("\t5.积分商品列表\n");
	printf("\t6.优惠商品列表\n");
	printf("\t7.热销排行榜\n");
	printf("\t8.浏览商品\n");
	printf("\t9.返回上一级\n");
	printf("\t10.退出\n");
	printf("请输入选项：");
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
//购买函数
void buy(struct good* head) {
	printf("滴————\n");
	printf("购买成功\n");
	int choice;
	printf("1.返回顾客界面\n");
	printf("2.退出\n");
	printf("请输入：");
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