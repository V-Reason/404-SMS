#include "Backend.h"

// 打印单个用户信息
void PrintOneUser(user* head)
{
	if (head == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintOneUser）\n");
		return;
	}
	printf("  _姓名:\t密码:\t电话:\t等级:\n");
	printf("  %s\t%s\t%s\t     %d\n",
		head->name, "*********", head->tele_num, head->level);
}

//打印所有用户信息
void PrintAllUser(user* head)
{
	if (head == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintAllUser)\n");
		return;
	}
	int cnt = 0;
	printf("  _姓名:\t密码:\t电话:\t等级:\n");
	while (head->next != NULL)
	{
		cnt++;
		head = head->next;
		printf("%d.%s\t%s\t%s     %d\n",
			cnt, head->name, head->password, head->tele_num, head->level);
	}
}

//打印指定数量的用户,自动判断head
void PrintOneAdmin(user* head)
{
	if (head == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintAllPackage）\n");
		system("pause");
		return;
	}

	if (head->prior == NULL)
		head = head->next;

	printf("  名称\t 电话\t 密码\t \n");
	printf(" %s\t %s\t %s\t \n",
		 head->name, head->tele_num, head->password);
	printf("\n");

}
//打印指定数量的用户,自动判断head
void PrintNumAdmin(user* head, int num)
{
	int cnt = 1;
	if (head == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintAllPackage）\n");
		system("pause");
		return;
	}

	//自动判断head
	user* tmp = NULL;
	if (head->prior == NULL)
		tmp = head->next;
	else
		tmp = head;

	printf("  名称\t 电话\t 密码\t \n");
	while (tmp != NULL && cnt <= num)
	{
		printf("[%d].%s\t %s\t %s\t \n",
			cnt, tmp->name, tmp->tele_num, tmp->password);
		tmp = tmp->next;
		cnt++;
	}
	printf("\n");

}

//计算用户数量
int CountUser(user* head)
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

//创建用户链表
user* CreatUserList()
{
	user* head = (user*)malloc(sizeof(user));
	memset(head, 0, sizeof(user));
	head->mlist = CreatMessageList();//防止报错，后面会清理掉的
	head->clist = CreatCouponList();//防止报错，后面会清理掉的
	return head;
}

//创建用户对象 传入DEFAULT表示默认值0
user* CreatOneUser()
{
	user* _user = (user*)malloc(sizeof(user));
	memset(_user, 0, sizeof(user));
	_user->level = NORMAL_USER;
	_user->exp = DEF_NUM;
	strcpy(_user->name, DEF_STR);
	strcpy(_user->password, DEF_STR);
	strcpy(_user->tele_num, DEF_STR);
	strcpy(_user->address_1, DEF_STR);
	strcpy(_user->address_2, DEF_STR);
	strcpy(_user->address_3, DEF_STR);
	_user->address_default = _user->address_1;
	_user->mlist = CreatMessageList();
	_user->clist = CreatCouponList();
	return _user;
}

//仅测试使用函数  创建用户对象 传入DEFAULT表示默认值0
user* _CreatOneUser(char* name, char* password, char* tele_num, int level)
{
	user* _user = (user*)malloc(sizeof(user));
	memset(_user, 0, sizeof(user));
	_user->level = DEF_NUM;
	_user->exp = DEF_NUM;
	strcpy(_user->name, DEF_STR);
	strcpy(_user->password, DEF_STR);
	strcpy(_user->tele_num, DEF_STR);
	strcpy(_user->address_1, DEF_STR);
	strcpy(_user->address_2, DEF_STR);
	strcpy(_user->address_3, DEF_STR);
	_user->address_default = _user->address_1;
	_user->mlist = CreatMessageList();
	_user->clist = CreatCouponList();
	if (name != (char*)DEFAULT)
	{
		strcpy(_user->name, name);
	}
	if (password != (char*)DEFAULT)
	{
		strcpy(_user->password, password);
	}
	if (tele_num != (char*)DEFAULT)
	{
		strcpy(_user->tele_num, tele_num);
	}
	if (level != DEFAULT)
	{
		_user->level = level;
	}
	return _user;
}


//将用户信息添加至链表末尾
void AddUser(user* head, user* _user) //head为头指针，puser为待添加的用户信息
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = _user;
	_user->prior = head;
}

//删除单个用户信息
void DeleteOneUser(user* _user) //head为头指针，puser为待删除的用户信息
{
	if (_user->next == NULL)
	{
		DeleteAllMessage(_user->mlist);
		DeleteAllCoupon(_user->clist);
		if (_user->prior == NULL)
		{
			free(_user);
			return;
		}
		_user->prior->next = NULL;
		free(_user);
		return;
	}
	_user->prior->next = _user->next;
	_user->next->prior = _user->prior;
	DeleteAllMessage(_user->mlist);
	DeleteAllCoupon(_user->clist);
	free(_user);
}

//删除包括head在内的所有用户信息
void DeleteAllUser(user* head)
{
	while (head->next != NULL)
	{
		DeleteAllMessage(head->mlist);
		DeleteAllCoupon(head->clist);
		head = head->next;
		free(head->prior);
	}
	DeleteAllMessage(head->mlist);
	DeleteAllCoupon(head->clist);
	free(head);
}

//基于名字和电话 查找用户信息 返回找到的用户指针 否则返回NULL
user* FindUser(user* head, char* str) {          //head为头指针，password为待查找的用户password
	user* temp = head->next;
	while (temp != NULL) {
		if (strcmp(temp->name, str) == 0 || strcmp(temp->tele_num, str) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//名字查重复
int isRepeatName(const char* name)
{
	user* point = uhead->next;
	while (point != NULL)
	{
		if (strcmp(name, point->name) == 0)
			return TRUE;
		point = point->next;
	}
	point = ahead->next;
	while (point != NULL)
	{
		if (strcmp(name, point->name) == 0)
			return TRUE;
		point = point->next;
	}
	return FALSE;
}

//手机号查重复
int isRepeatTele(const char* teleNum)
{
	user* point = uhead->next;
	while (point != NULL)
	{
		if (strcmp(teleNum, point->tele_num) == 0)
			return TRUE;
		point = point->next;
	}
	point = ahead->next;
	while (point != NULL)
	{
		if (strcmp(teleNum, point->tele_num) == 0)
			return TRUE;
		point = point->next;
	}
	return FALSE;
}