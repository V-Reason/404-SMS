#include "Frontend.h"

//��Ϣ����ϵͳ
void MessSys(user* user)
{
	//Ԥ������
	system("cls");

	//��ʼ��
	char key = ERROR;					//����
	int i = ERROR;						//�������� ��ʵ��
	message* point = user->mlist->next;	//�α�
	message* tmp = NULL;				//��̽�α�

	while (TRUE)
	{

		//���ó�ʼ��key
		//��Ҫ������дcls
		SetCursorPosition(0, 0);
		tmp = NULL;
		i = ERROR;

		//����������
		if (user->mlist->next == NULL)
		{
			system("cls");
			printf("��������...\n");
			printf("���ڷ���...\n");
			system("pause");
			return;
		}

		//������
		//ʱ��
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n");
		//����˵��
		printf("<֪ͨ����ϵͳ>\n");
		printf("����[ESC]����\n");
		printf("����[a/d]��ҳ\n");
		printf("����[1 2 3 4 5]ѡ��\n\n");

		//��ӡ
		printf("\n֪ͨ:\n");
		PrintNumMessage(point,MESS_NUM);

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//��Ϣѭ��
		switch (key)
		{
		//����Ӧ
		case ERROR:
		{
			break;//break switch
		}
		//�˳�ϵͳ
		case ESC:
		{
			system("cls");
			printf("�˳�֪ͨ���������\n [y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				return;
			}
			else
			{
				key = ERROR;
				system("cls");
				break;//break switch
			}

			break;//break switch
		}
		//��һҳ
		case BUTTON_LEFT:
		{
			tmp = point;
			for (i = 0; i < MESS_NUM && tmp->prior != NULL; i++)//��ֹ�ߵ�ͷ
			{
				tmp = tmp->prior;
			}
			if (i == MESS_NUM)//��֤����PAGE_NUM����
			{
				point = tmp;
			}

			//����
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//��һҳ
		case BUTTON_RIGHT:
		{
			tmp = point;
			for (i = 0; i < MESS_NUM && tmp->next != NULL; i++)//��ֹ�ߵ�ͷ
			{
				tmp = tmp->next;
			}
			if (i == MESS_NUM)//��֤����page_num����
			{
				point = tmp;
			}

			//����
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//ѡ��
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		{
			tmp = point;
			for (i = 0; i < key - '1' && tmp != NULL; i++)
			{
				tmp = tmp->next;
			}
			//�������
			if (tmp != NULL)
			{
				if (TRUE == ModifyMessage(tmp))
				{
					point = user->mlist->next;
				}
			}
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}

		}//end switch
	}//end while
}

//Ŀǰֻ��Ϊǰ��ɾ��/���֪ͨ�ĺ���  ��ɾ���ɹ��򷵻�TRUE ���򷵻�FALSE
int ModifyMessage(message* mess)
{
	//׼������
	char key = ERROR;
	system("cls");

	//ȷ��ɾ��
	printf("֪ͨ���ݣ�%s\n", mess->content);
	printf("�Ƿ�ɾ��/��᣿\n");
	printf("[y/n]\n");
	InputBox(&key, 1, MODE_KEY, OFF);
	if (key != 'y')
	{
		return FALSE;
	}
	//�û��������� ֪ͨ��ʽ���û�[V.Reason]Ͷ��:..."
	if (mess->important == IMP_USER)
	{
		char* l, * r;
		l = strchr(mess->content, '[');
		r = strchr(mess->content, ']');
		char userName[MAX_USER_NAME + 1];
		memset(userName, 0, sizeof(userName));
		strncpy(userName, l + 1, abs(l - r) - 1);
		char* content = strchr(mess->content, ':');
		content++;
		user* theUser = FindUser(uhead, userName);
		if (theUser != NULL)
		{
			message* newMess = CreatOneMessage("", IMP_SPECIAL);
			sprintf(newMess->content, "Ͷ�ߴ������(%s)", content);
			AddMessage(theUser->mlist, newMess);
		}
	}
	//��ʽɾ��
	DeleteOneMessage(mess);
	printf("ɾ��/���ɹ���\n");
	printf("���ڷ���...\n");
	system("pause");
	return TRUE;
}