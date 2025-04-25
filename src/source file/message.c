#include "Backend.h"

//֪ͨ�����㷨��ð�����򣩴���ֵ�������ڱ�
void MessageSort(message* head) 
{
	if (head == NULL || head->prior != NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��MessageSort)\n");
		system("pause");
		return;
	}

	//���������ڱ�������
	//������ֱ�ӷ���
	if (head->next == NULL)
		return;
	//��Ԫ����ֱ�ӷ���
	if(head->next->next==NULL)
		return;

	//��ʼ����
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

// ����ͷ���
message* CreatMessageList() {
	message* messhead = (message*)malloc(sizeof(message));
	memset(messhead, 0, sizeof(message));
	return messhead;
}

//��������message ����DEFAULT ���趨ΪĬ��ֵ
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

//��ӡ����֪ͨ
void PrintOneMessage(message* mess)
{
	if (mess == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintOneMessage)\n");
		system("pause");
		return;
	}
	printf("%s", mess->content);
}

//��ӡָ������֪ͨ
void PrintNumMessage(message* head,int num)
{
	if (head == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintNumMessage)\n");
		system("pause");
		return;
	}
	if (head->prior == NULL)
	{
		if (head->next == NULL)
		{
			printf("��������...\n");
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

//��ӡ����֪ͨ
void PrintAllMessage(message* head)
{
	if (head == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintAllMessage)\n");
		system("pause");
		return;
	}
	if (head->prior == NULL)
	{
		if (head->next == NULL)
		{
			printf("��������...\n");
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

//���Message�ڵ� ��������������
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
	//��������������
	MessageSort(head);
}

//ɾ��֪ͨ
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

//ɾ��head���ڵ�����֪ͨ
void DeleteAllMessage(message* head)
{
	while (head->next != NULL)
	{
		head = head->next;
		free(head->prior);
	}
	free(head);
}

//����֪ͨ����
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

//����֪ͨ ������mess
message* CpyMessage(message* mess)
{
	message* newMess = CreatOneMessage(mess->content, mess->important);
	return newMess;
}