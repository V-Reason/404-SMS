#include "Backend.h"

// ��ӡ�����û���Ϣ
void PrintOneUser(user* head)
{
	if (head == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintOneUser��\n");
		return;
	}
	printf("  _����:\t����:\t�绰:\t�ȼ�:\n");
	printf("  %s\t%s\t%s\t     %d\n",
		head->name, "*********", head->tele_num, head->level);
}

//��ӡ�����û���Ϣ
void PrintAllUser(user* head)
{
	if (head == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintAllUser)\n");
		return;
	}
	int cnt = 0;
	printf("  _����:\t����:\t�绰:\t�ȼ�:\n");
	while (head->next != NULL)
	{
		cnt++;
		head = head->next;
		printf("%d.%s\t%s\t%s     %d\n",
			cnt, head->name, head->password, head->tele_num, head->level);
	}
}

//��ӡָ���������û�,�Զ��ж�head
void PrintOneAdmin(user* head)
{
	if (head == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintAllPackage��\n");
		system("pause");
		return;
	}

	if (head->prior == NULL)
		head = head->next;

	printf("  ����\t �绰\t ����\t \n");
	printf(" %s\t %s\t %s\t \n",
		 head->name, head->tele_num, head->password);
	printf("\n");

}
//��ӡָ���������û�,�Զ��ж�head
void PrintNumAdmin(user* head, int num)
{
	int cnt = 1;
	if (head == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintAllPackage��\n");
		system("pause");
		return;
	}

	//�Զ��ж�head
	user* tmp = NULL;
	if (head->prior == NULL)
		tmp = head->next;
	else
		tmp = head;

	printf("  ����\t �绰\t ����\t \n");
	while (tmp != NULL && cnt <= num)
	{
		printf("[%d].%s\t %s\t %s\t \n",
			cnt, tmp->name, tmp->tele_num, tmp->password);
		tmp = tmp->next;
		cnt++;
	}
	printf("\n");

}

//�����û�����
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

//�����û�����
user* CreatUserList()
{
	user* head = (user*)malloc(sizeof(user));
	memset(head, 0, sizeof(user));
	head->mlist = CreatMessageList();//��ֹ����������������
	head->clist = CreatCouponList();//��ֹ����������������
	return head;
}

//�����û����� ����DEFAULT��ʾĬ��ֵ0
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

//������ʹ�ú���  �����û����� ����DEFAULT��ʾĬ��ֵ0
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


//���û���Ϣ���������ĩβ
void AddUser(user* head, user* _user) //headΪͷָ�룬puserΪ����ӵ��û���Ϣ
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = _user;
	_user->prior = head;
}

//ɾ�������û���Ϣ
void DeleteOneUser(user* _user) //headΪͷָ�룬puserΪ��ɾ�����û���Ϣ
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

//ɾ������head���ڵ������û���Ϣ
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

//�������ֺ͵绰 �����û���Ϣ �����ҵ����û�ָ�� ���򷵻�NULL
user* FindUser(user* head, char* str) {          //headΪͷָ�룬passwordΪ�����ҵ��û�password
	user* temp = head->next;
	while (temp != NULL) {
		if (strcmp(temp->name, str) == 0 || strcmp(temp->tele_num, str) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//���ֲ��ظ�
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

//�ֻ��Ų��ظ�
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