#include<stdio.h>
#include<stdlib.h>
#include<stdafx.h>
#include<string.h>
#include<malloc.h>

//salary 工资，就用int 就行了，不然你字符串，加的时候，还需要转换。下面加这个值的时候，int可以直接+=，但是字符串不可以+=所以后面出错了 
typedef struct {
	char num[5];
	char name[9];
	int salary;
}Datatype;

typedef struct node {
	Datatype Data;
	struct node * next;
}listnode;

//指针声明的时候，要初始化，不然是一个野指针。
listnode *head=NULL;


int select();//作出功能选择的返回。
void Buildlist();//建立链表和输入数据。
listnode * Listfind();//查找姓名或者编号。
void Sort(listnode *p);//返回的是Listnode。对工资排序。
void aver(listnode *p);
void add(listnode *p);//增加新的信息
void delnode(listnode *p);//删除一个人的信息。
void change(listnode *p);//更改一个人的信息。

int main (void)
{
	int select_num=-1;// 初始化select_num为-1.
	listnode *p =  NULL;

	for(;;){
		select_num=select();//对菜单的选择
		switch(select_num){
		
		case 1:
			printf("工资链表的建立\n");
			Buildlist();
			break;
		case 2:
			if(head!=NULL){
				printf("工资链表的查询\n");
				//p木有声明就使用，p 要么是全局变量才可以在任何地方随意使用，否则你就需要在函数体内声明。 main 函数下面
				//声明 Listnode *p; 并且初始化为空。
				p=Listfind();
				if(p!=NULL){
					printf("--------------------\n");
					printf("编号 姓名 工资\n");
					printf("-----------------\n");
					//优先级自己搞不清楚的，用括号括起来， 
					printf("%s  %s  %d\n",(p->Data).num,(p->Data).name,(p->Data).salary);
					printf("-------------------\n");
				}else{
					printf("没有找到。\n");
				}
				break;
			}else{
				printf("链表没有建立！\n");
				break;
			}
		case 3:
			printf("工资的排序\n");
			Sort(head);
			break;
		case 4:
			printf("平均工资\n");
			//这个函数你定义的时候木有输入参数，但是这块传入了，按道理来说应该是需要入参的，定义和声明需要更改
			aver(head);
			break;
		case 5:
			printf("增加信息：\n");
			printf("-------------------------------------------------------\n");
			printf("请按顺序输入：（1）编号	（2）姓名	（3）工资：\n  ");
			printf("-------------------------------------------------------\n");
			add(head);//加入信息。
			break;
		case 6:
			printf("删除信息：\n");
			delnode(head);
			break;
		case 7:
			printf("更改信息：\n");
			change(head);
			break;
		case 0:
			printf("再见！\n");
			return 0;
		}
	}


}

int select()//功能的选择
{
	int s=-1;
	//少一个分号，在语句最后；
	//printf("     工资管理\n")
	printf("     工资管理\n");

	printf("=====================\n");
	printf("  1:工资链表的建立\n");
	printf("  2:工资链表的查询\n");
	printf("  3:工资排序\n");
	printf("  4:工资平均\n");
	printf("  5:增加信息\n");
	printf("  6:删除信息\n");
	printf("  7:更改信息\n");
	printf("  0:退出\n");
	printf("=====================\n");
	printf("请输入0-7的值：\n");
	
	for(;;){
		scanf("%d",&s);
		if(s<0||s>7){
			printf("请输入0—7之间的数!\n");//只能选择0-7.
		}else{
			break;
		}
	}
	return s;
}

void Buildlist()//建立链表
{
	head=(listnode *)malloc(sizeof(listnode));
	listnode *p,*rear;
	rear=head;
	int flag=1;
	
	while(flag==1){
		p=(listnode *)malloc(sizeof(listnode));
		printf("请输入（1）编号 （2）姓名 （3）工资\n");
		scanf("%s%s%d",&((p->Data).num),&((p->Data).name),&((p->Data).salary));  //(p->Data).num代表的是数而不是地址。
		rear->next=p;
		rear=p;
		printf("继续输入吗？（1（继续）/2(退出)）\n");
		scanf("%d",&flag);
	}
	rear->next=NULL;
	
}


listnode *Listfind()//查找
{
	listnode *p;
	char num[5];
	char name[8];
	int x;
	printf("使用姓名查找（1），用编号查找（2）：\n");
	printf("请输入选项：\n");
	scanf("%d",&x);
	p=head->next;//跳过哑元。
	if(x==1){
		printf("请输入要查找的姓名：\n");
		scanf("%s",name);
		while(p && strcmp(p->Data.name,name)!=0){//输入的和查找到的姓名不一样，则指向下一个。
			p=p->next;
		}
	}else{
		if(x==2){
			printf("请输入要查找的编号：\n");
			scanf("%s",num);
			while(p && strcmp(p->Data.num,num)<0) //比较输入的和找到的，不对应指向下一个。
				p=p->next;
			if(p==NULL && strcmp(p->Data.num,num)>0){
				p=NULL;
				printf("没有找到这个编号。\n");
			}
		}
			
	}
	return p;
}

void Sort(listnode *p)//排序
{
	if(p!=NULL){
		listnode *x,*y,*r;
		listnode temp;
		for(x=p->next;x!=NULL;x=x->next){
			for(y=x->next;y!=NULL;y=y->next){
				if(x->Data.salary<y->Data.salary){
					temp.Data=x->Data;
					x->Data=y->Data;
					y->Data=temp.Data;
				}
			}
		}
		r=p->next;
		printf("按工资排序后序列是：\n");
		while(r!=NULL){			//打印排序后的数据
			printf("--------------------\n");
			printf("编号	姓名	工资\n");
			printf("%s	%s	%d\n",r->Data.num,r->Data.name,r->Data.salary);
			printf("----------------------\n");
			r=r->next;
		}
	}else{
		printf("链表没有建立。\n");
		return;//排序前先检测p是否为空.
	}
	
}

//Listnode 跟 listnode 是不同的东西，大小写要注意
void aver(listnode *p)//平均
{
	if(p!=NULL){
		int x=0;
		int y=0;

	
		p=head->next;
		while(p!=NULL){
			x += (p->Data).salary;
			p=p->next;
			y++;
		}
		x=x/y;
		printf("-----------------\n");
		printf("平均工资是%d\n",x);
		printf("-----------------\n");
	}else{
		printf("链表没有建立。\n");
		return;
	}
	//void 返回值，就不要返回了。
	//return 0;
}

void add(listnode *p)//添加
{
	if(p!=NULL){
		listnode *p1=NULL;
		listnode *p2=NULL;
		listnode *q=NULL;
		q=(listnode *)malloc(sizeof (listnode));
		scanf("%s%s%d",&(q->Data).num,&(q->Data).name,&(q->Data).salary);
		p1=head;
		p2=p1->next;
		while(p2!=NULL && strcmp((p2->Data).num,(q->Data).num)<0){
			p1=p2;//p1指向刚才访问的结点。
			p2=p2->next;//指向下一个结点。
		}
		p1->next=q;//将q插入链表。
		q->next=p2;//将链表连接起来。
	}else{
		printf("链表没有建立。\n");
		return;	
	}

}

void delnode(listnode *p)//删除
{
	if(p!=NULL){
		int j;
		listnode *q=NULL;
		listnode *h=NULL;
		h=Listfind();//找到要删除的人，并赋给h。
		if(h==NULL){
			printf("没有找到要删除的人。\n");//判断是否找到要删除的人。
		}else{
			printf("编号：%s姓名： %s工资：%d\n",(h->Data).num,(h->Data).name,(h->Data).salary);
			printf("确定要删除吗？（1确定/2否定）");
			scanf("%d",&j);
			if(j==1){
				q=head;
				while(q!=NULL && q->next!=h){
					q=q->next;//找到h所在的位置。
				}
			}
		q->next=h->next;//将h空出来。
		free(h);//释放h的内存。
		printf("此人信息已删除\n");
		}
	}else{
		printf("链表没有建立。\n");
		return;
	}
}
void change(listnode *p)
{
	int x=0;
	if(p!=NULL){
		p=Listfind();
		printf("请确认是否是要更改的信息：\n");
		printf("(1)编号 （2）姓名 （3）工资：");
		printf("%s	%s	%d\n",(p->Data).num,(p->Data).name,(p->Data).salary);
		printf("是否更改？（1(是)/2（否））\n");
		scanf("%d",&x);
		while(x==1){
			printf("请输入正确的信息：\n");
			printf("(1)编号 （2）姓名 （3）工资：\n");
			scanf("%s%s%d",&(p->Data).num,&(p->Data).name,&(p->Data).salary);
			x=-1;
		}

	}else{
		printf("链表没有建立。\n");
		return;
	}
}