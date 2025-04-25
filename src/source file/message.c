#include "Backend.h"

//通知排序算法（冒泡排序）传入值必须是哨兵
void MessageSort(message* head) 
{
	if (head == NULL || head->prior != NULL)
	{
		printf("非法传入了NULL指针!!!（MessageSort)\n");
		system("pause");
		return;
	}

	//不能跳过哨兵！！！
	//空链表，直接返回
	if (head->next == NULL)
		return;
	//单元链表，直接返回
	if(head->next->next==NULL)
		return;

	//开始排序
	int flag = FALSE;
	do
	{
		flag = FALSE;
		message* a = head->next;
		message* b = head->next->next;

		while (b != NULL)
		{
			if (a->important < b->important)
			{
				message* aPrior = a->prior;
				message* bNext = b->next;

				a->next = bNext;
				a->prior = b;
				b->next = a;
				b->prior = aPrior;


				message* tmp = a;
				a = b;
				b = tmp;

				aPrior->next = a;
				if (bNext != NULL)
					bNext->prior = b;

				flag = TRUE;
			}
			a = a->next;
			b = b->next;
		}

	} while (flag);
}

// 创建头结点
message* CreatMessageList() {
	message* messhead = (message*)malloc(sizeof(message));
	memset(messhead, 0, sizeof(message));
	return messhead;
}

//创建单个message 传入DEFAULT 可设定为默认值
message* CreatOneMessage(char* content, int important)
{
	message* mess = (message*)malloc(sizeof(message));
	memset(mess, 0, sizeof(message));
	strcpy(mess->content, DEF_STR);
	mess->important = DEF_NUM;
	if (content != (char*)DEFAULT)
	{
		strcpy(mess->content, content);
	}
	if (important != (int)DEFAULT)
	{
		mess->important = important;
	}
	return mess;
}

//打印单个通知
void PrintOneMessage(message* mess)
{
	if (mess == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintOneMessage)\n");
		system("pause");
		return;
	}
	printf("%s", mess->content);
}

//打印指定数量通知
void PrintNumMessage(message* head,int num)
{
	if (head == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintNumMessage)\n");
		system("pause");
		return;
	}
	if (head->prior == NULL)
	{
		if (head->next == NULL)
		{
			printf("今日无事...\n");
			return;
		}
		else
		{
			head = head->next;
		}
	}
	int cnt = 1;
	while (head != NULL && cnt <= num)
	{
		printf("%d.%s\n", cnt, head->content);
		cnt++;
		head = head->next;
	}
}

//打印所有通知
void PrintAllMessage(message* head)
{
	if (head == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintAllMessage)\n");
		system("pause");
		return;
	}
	if (head->prior == NULL)
	{
		if (head->next == NULL)
		{
			printf("今日无事...\n");
			return;
		}
		else
		{
			head = head->next;
		}
	}
	int cnt = 1;
	while (head != NULL)
	{
		printf("%d.%s\n", cnt, head->content);
		cnt++;
		head = head->next;
	}
}

//添加Message节点 添加完后立刻排序
void AddMessage(message* head, message* mes)
{
	message* tail = head;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = mes;
	mes->prior = tail;
	mes->next = NULL;
	//添加完后立刻排序
	MessageSort(head);
}

//删除通知
void DeleteOneMessage(message* mess)
{
	if (mess->next == NULL)
	{
		if (mess->prior == NULL)
		{
			free(mess);
			return;
		}
		mess->prior->next = NULL;
		free(mess);
		return;
	}
	mess->prior->next = mess->next;
	mess->next->prior = mess->prior;
	free(mess);
}

//删除head在内的所有通知
void DeleteAllMessage(message* head)
{
	while (head->next != NULL)
	{
		head = head->next;
		free(head->prior);
	}
	free(head);
}

//计算通知数量
int CountMessage(message* head)
{
	int cnt;
	if (head->prior == NULL)
		cnt = 0;
	else
		cnt = 1;

	head = head->next;

	while (head != NULL)
	{
		cnt++;
		head = head->next;
	}

	return cnt;

}

//复制通知 返回新mess
message* CpyMessage(message* mess)
{
	message* newMess = CreatOneMessage(mess->content, mess->important);
	return newMess;
}