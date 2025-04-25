#include "Frontend.h"

//��������Ա����ϵͳ
//���˹���Ա�����й�����
//��ͨ�û���ģ����˰�
//1.��������Ա��Ϣ
//2.��ɾ����Ա�˺�
//3.�ܿ���user���룿���˰�
//ע������Ա���û����Σ�����������
void TopAdminSys(user* admin)
{
	//��ʼ��
	system("cls");
	char key = ERROR;					//���յ�������
	char search[MAX_SEARCH_LENGTH];		//�����ַ�������
	memset(search, 0, sizeof(search));	//����
	package* pack_search = NULL;
	user* user_search = NULL;
	struct tm* nowTime = GetNowTime();
	struct tm* lastTime_S = nowTime;
	struct tm* lastTime_L = nowTime;

	//ÿ���״ε�½����
	if (logoutTime.tm_year != 0
		&& (logoutTime.tm_year != nowTime->tm_year
			|| logoutTime.tm_mon != nowTime->tm_mon
			|| logoutTime.tm_mday != nowTime->tm_mday))
	{
		//����ף��
		festival* fes = isFestival();
		if (fes != NULL)
		{
			message* mess = CreatOneMessage("", IMP_SPECIAL);
			sprintf(mess->content, "%s ���֣�", fes->name);
			AddMessage(admin->mlist, mess);
		}
		//��������
		GoThroughPackage();
	}

	while (TRUE)
	{
		//��ʱ����
		nowTime = GetNowTime();
		if (AutoRegular__TimeSeg_S <= GetTimeSeg_Min(lastTime_S, nowTime))
		{
			AdminRegular_S(admin);
			lastTime_S = nowTime;
		}
		if (AutoRegular__TimeSeg_L <= GetTimeSeg_Min(lastTime_L, nowTime))
		{
			AdminRegular_L(admin);
			lastTime_L = nowTime;
		}

		//���ó�ʼ��key
		//��Ҫ������дcls
		SetCursorPosition(0, 0);
		memset(search, 0, sizeof(search));
		pack_search = NULL;
		user_search = NULL;

		//������
		//ʱ��
		printf("<��������Ա������>\n");
		printf("��ǰʱ�䣺");
		PrintNowTime();

		//�Ʊ�
		printf("\n�ܲƲ���%lf\n", fund);

		//֪ͨ
		printf("\n֪ͨ:\n");
		PrintNumMessage(admin->mlist, MESS_NUM);
		printf("\n");
		//����˵��
		printf("���¶�Ӧ������ѡ����...\n\n");

		printf("[ESC]�˳�\n\n");

		printf("����֪ͨ��\n");
		printf("[`]����֪ͨ\n\n");

		printf("�ڹ�����\n");
		printf("[0]�ڹ�����\n\n");

		printf("��ѯ���ܣ�\n");
		printf("[1]����\n");
		printf("[2]����\n");
		printf("[3]�û�\n");
		printf("[4]��ʷ��¼\n\n");

		printf("¼�빦�ܣ�\n");
		printf("[5]¼�����\n\n");
		printf("[6]�������\n\n");

		printf("�㲥���ܣ�\n");
		printf("[7]�㲥���û�\n");
		printf("[8]�㲥������Ա\n\n");

		printf("������Ϣ�޸�:\n");
		printf("[9]�޸ĸ�����Ϣ\n\n");

		printf("�������Ա��\n");
		printf("[a]��ѯ����Ա\n");
		printf("[b]��������Ա\n\n");

		printf("������\n");
		printf("[s]����ѡ��\n");
		printf("[q]�˳���½\n\n");

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//�����ж�->��Ϣѭ��
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
			printf("�˳�����\n [y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				//��¼�˳�ʱ��
				RecordLogoutTime();
				//��¼�˳��˺�
				RecordLogoutUser(admin);
				//�˳�
				powerTag = EXIT;
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
		//����֪ͨ
		case '`':
		{
			//����д����ModifyMessage()����
			MessSys(admin);
			//����
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�ڹ�����
		case '0':
		{
			ManagePay();
			key = ERROR;
			system("cls");
			break;
		}
		//��ѯ����
		case '1':
		{
			system("cls");
			printf("<��ѯ����>\n");
			printf("����[ESC]����\n");
			printf("״̬���ձ�:(״̬��������������)\n");
			printf("[%d]�쳣 [%d]��Ź��� [%d]��ǩ�� [%d]������ [%d]������ [%d]���� [%d]��ǩ��\n",
				STATE_ERROR, STATE_STAY_LONG, STATE_WAIT_PICK, STATE_TRANSPORT, STATE_WAIT_COLLECT, STATE_REJECT, STATE_PICKUPED);
			printf("������");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			printf("\n\n");

			if (search[0] == ESC)//ESC���
			{
				key = ERROR;//����
				system("cls");
				break;//break switch
			}

			pack_search = AdminFindPackage(phead, search);
			if (pack_search != NULL)
			{
				//�ɹ�����
				printf("����[`]   �༭ģʽ\n");
				printf("����[�ո�] ��������\n\n");

				printf("����ѯ�� %d �������������ʾ�������ݣ�����༭ģʽ�鿴����.\n", CountPackage(pack_search));
				PrintNumPackage(pack_search, PAGE_NUM);

				//������
				while (TRUE)
				{
					InputBox(&key, 1, MODE_KEY, ON);
					if (key == ESC)
					{
						//����
						key = ERROR;
						system("cls");
						break;
					}
					if (key == '`')
					{
						EditPackage(pack_search);//����༭ģʽ
						key = '1';//����Ϊ��������
						break;
					}
					if (key == ' ')
					{
						key = '1';//����Ϊ��������
						break;
					}
				}
			}
			else
			{
				//ʧ�ܴ���
				printf("�޽��......\n\n");
				system("pause");//��Ĭ�ȴ�
			}

			system("cls");

			break;//break switch
		}
		//��ѯ����
		case '2':
		{
			system("cls");
			printf("<��ѯ����>\n");
			printf("����[ESC]����\n");
			PrintAllShelf();
			printf("\n");

			printf("���뷶���� A0_1,2  D4_3,4\n");
			printf("�����");
			InputBox(search, MAX_LOCATION, MODE_SHOW, ON);

			if (search[0] == ESC)//ESC���
			{
				//����
				key = ERROR;
				system("cls");
				break;
			}

			shelf* theShelf = StrToShelf(search);

			if (theShelf == NULL)
			{
				printf("����Ļ��ܸ�ʽ����ȷ�������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}

			printf("\n%s ��״̬���£�\n", search);
			char shelf_state[MAX_TF + 1];
			memset(shelf_state, 0, sizeof(shelf_state));
			TFtoStr(shelf_state, theShelf->used);
			printf("�Ƿ�ռ�ã�%s\n", shelf_state);
			printf("ռ�õİ����˵��ţ�%s\n", theShelf->pack_id);

			printf("\n");
			printf("�Ƿ����޸ģ�\n");
			printf("[y/n]\n");
			InputBox(search, 1, MODE_KEY, OFF);
			if (search[0] == 'y')
			{
				ModifyShelf(theShelf);
			}

			system("pause");//��Ĭ�ȴ�
			system("cls");
			break;//break switch
		}
		//��ѯ�û�
		case '3':
		{
			system("cls");
			printf("<��ѯ�û�>\n");
			printf("����[ESC]����\n");
			printf("������");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			printf("\n");

			if (search[0] == ESC)//ESC���
			{
				key = ERROR;//����
				system("cls");
				break;//break switch
			}

			user_search = FindUser(uhead, search);//��ѯ���
			if (user_search != NULL)
			{
				//�ɹ�����
				PrintOneUser(user_search);
			}
			else
			{
				//ʧ�ܴ���
				printf("�޽��......\n");
			}

			system("pause");//��Ĭ�ȴ�
			system("cls");

			break;//break switch
		}
		//��ѯ��ʷ����
		case '4':
		{
			system("cls");
			printf("<��ѯ��ʷ��¼>\n");
			printf("[ESC]�˳�\n");
			printf("��ʽeg��20060105\n");
			printf("�����롪��\n");
			//����1
			printf("��ʼ���ڣ�");
			InputBox(search, MAX_DATA, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (strlen(search) != MAX_DATA
				|| FALSE == isAllDigits(search))
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			//����ת��
			int dataNum = atof(search);			//eg:20060105
			if (dataNum < 0)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			struct tm data1 = { 0 };
			data1.tm_year = dataNum / 10000;	//û����MAX_DATA�����������ע��
			data1.tm_mon = (dataNum % 10000) / 100;
			data1.tm_mday = dataNum % 100;
			if (12 < data1.tm_mon)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			if (DaysInMonth(data1.tm_year, data1.tm_mon) < data1.tm_mday)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			//����2
			printf("��ֹ���ڣ�");
			InputBox(search, MAX_DATA, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (strlen(search) != MAX_DATA
				|| FALSE == isAllDigits(search))
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			//����ת��
			dataNum = atof(search);				//eg:20060105
			if (dataNum < 0)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			struct tm data2 = { 0 };
			data2.tm_year = dataNum / 10000;	//û����MAX_DATA�����������ע��
			data2.tm_mon = (dataNum % 10000) / 100;
			data2.tm_mday = dataNum % 100;
			if (12 < data2.tm_mon)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			if (DaysInMonth(data2.tm_year, data2.tm_mon) < data2.tm_mday)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}

			//��ʽ��ѯ
			ReadPackHis(&data1, &data2);
			system("pause");

			//key = ERROR;
			system("cls");
			break;
		}
		//¼�����
		case '5':
		{
			system("cls");
			printf("<¼�����>\n");
			printf("����[ESC]����\n");
			printf("��������д�������ݣ�\n");

			package* pack = CreatOnePackage();//�����հװ���

			if (EnterPackage(pack) == FALSE)//������Ϣ
			{
				//ʧ�ܴ���
				key = ERROR;//����
				free(pack);
				system("cls");
				continue;
			}
			//�ɹ�����
			AddOnePackage(phead, pack); //��������
			printf("\n¼��ɹ���\n");
			PrintOnePackage(pack); //����ȫ����Ϣ

			system("pause");//��Ĭ�ȴ�
			system("cls");

			break;//break switch
		}
		//�������
		case '6':
		{
			system("cls");
			printf("<�������>\n");
			printf("����[ESC]����\n");
			printf("�˵��ţ�");
			InputBox(search, MAX_ID, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (FALSE == JungePackageInformation(ID, search))
			{
				printf("\n������˵��Ÿ�ʽ����������\n");
				system("pause");
				system("cls");
				break;
			}
			pack_search = AdminFindPackage(phead, search);
			if (NULL == pack_search)
			{
				printf("\n������˵��Ų����ڣ�������\n");
				system("pause");
				system("cls");
				break;
			}
			printf("\n�ҵ����°�������ȷ��.\n");
			PrintOnePackage(pack_search);
			printf("\nȷ����⣿\n");
			printf("[y/n]\n");
			InputBox(search, 1, MODE_KEY, OFF);
			if (search[0] != 'y')
			{
				printf("��ȡ�����...\n");
				printf("���ڷ���...\n");
				system("pause");
				system("cls");
				break;
			}
			if (pack_search->state == STATE_WAIT_PICK)
			{
				printf("�����ظ���⣡\n");
				printf("���ڷ���......\n");
				system("pause");
				system("cls");
				break;
			}
			if (FALSE == AllocateLocation(pack_search, ahead))
			{
				printf("���ʧ��...\n");
				printf("�������������飡\n");
				printf("���ڷ���...\n");
				system("pause");
				system("cls");
				break;
			}
			user* temUser = FindUser(uhead, pack_search->tele_num);
			if (temUser != NULL)
			{
				message* mess = CreatOneMessage("", IMP_NORMAL);
				sprintf(mess->content, "��İ�����%s����ǩ��", pack_search->pack_name);
				AddMessage(temUser->mlist, mess);
			}
			printf("���ɹ���\n");
			printf("�ɹ����������䵽��%s\n", pack_search->location);
			printf("���ڷ���...\n");
			system("pause");
			system("cls");
			break;//break switch
		}
		//�㲥
		case '7': //���û�
		case '8': //������Ա
		{
			const char _group[2][10] = {"�û�","����Ա"};
			user* group = uhead;
			if (key == '8')group = ahead;

			system("cls");
			printf("����[ESC]����\n");
			printf("��Ϣ������ ȫ��%s\n", _group[key - '7']);
			printf("������㲥��Ϣ��");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			if (search[0] == ESC)//ESC���
			{
				//����
				key = ERROR;
				system("cls");
				break;
			}
			//ȷ�ϣ�
			printf("\nȷ���㲥������Ϣ��\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key != 'y')
			{
				key = ERROR;
				system("cls");
				break;
			}
			//��ʽ�㲥
			message* mess = CreatOneMessage(search, IMP_SPECIAL);
			Broadcast(mess, group);//�㲥��ָ��Ⱥ��
			printf("\n�㲥�ɹ���\n");
			printf("���ڷ���...\n");
			key = ERROR;
			system("pause");
			system("cls");
			break;//break switch
		}

		//��������Ա������Ϣ�޸�
		case '9':
		{
			system("cls");
			printf("<�޸ĸ�����Ϣ>\n");
			printf("����[ESC]����\n");
			PrintOneUser(admin);
			printf("\n�Ƿ�Ҫ�޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				ModifyUserInterface(admin);
			}
			else
				//����
				key = ERROR;
			system("cls");

			break;//break switch
		}
		//��ѯ����Ա
		case 'a':
		{
			system("cls");
			printf("<��ѯ�μ�����Ա>\n");
			printf("����[ESC]����\n");

			if (ahead != NULL)
			{
				//�ɹ�����
				printf("����[`]   �༭ģʽ\n");

				printf("����ѯ�� %d �������������ʾ�������ݣ�����༭ģʽ�鿴����.\n", CountUser(ahead));
				PrintNumAdmin(ahead, ADMIN_NUM);

				//������
				while (TRUE)
				{
					InputBox(&key, 1, MODE_KEY, ON);
					if (key == ESC)
					{
						//����
						key = ERROR;
						system("cls");
						break;
					}
					if (key == '`')
					{
						EditAdmin(ahead);//����༭ģʽ
						key = '1';//����Ϊ��������
						break;
					}
				}
			}
			else
			{
				//ʧ�ܴ���
				printf("�޽��......\n\n");
				system("pause");//��Ĭ�ȴ�
			}

			system("cls");

			break;//break switch
		}
		//��������Ա
		case 'b':
		{
			system("cls");
			user* NewAdmin = CreatOneUser();
			char adminName[MAX_USER_NAME + 1];
			user* point = uhead->next;
			while (point != NULL)
			{
				memset(adminName, 0, sizeof(adminName));
				srand((unsigned int)time(NULL));
				int randomNum = rand() % 10000;
				sprintf(adminName, "Admin%04d", randomNum);
				if (strcmp(point->name, adminName) == 0)
				{
					point = uhead;
				}
				point = point->next;
			}
			adminName[MAX_USER_NAME] = '\0';
			strcpy(NewAdmin->name, adminName);
			strcpy(NewAdmin->password, DEFUALT_ADMIN_PASSWORD);
			NewAdmin->level = ADMIN;
			AddUser(ahead, NewAdmin);
			printf("\n�¹���Ա�����ɹ�!\n");
			PrintOneAdmin(NewAdmin);
			system("pause");
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//����ѡ��
		case 's':
		{
			SaveOption();
			key = ERROR;
			system("cls");
			break;
		}
		//�˳���½
		case 'q':
		{
			system("cls");
			printf("�˳���½��\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				//����logoutTime��¼
				ClearLogout();
				//�ط���½
				powerTag = RESTART;
				return;
			}
			else
			{
				//����
				key = ERROR;
				system("cls");
				break;//break switch
			}
		}

		//Sleep(500);//ϵͳ��Ӧʱ�� ��λΪms ���������˸����->��˸�����ѽ��
		}//end switch
	}//end while
}

//����Ա����ϵͳ
void AdminSys(user* admin)
{
	//��ʼ��
	system("cls");
	char key = ERROR;					//���յ�������
	char search[MAX_SEARCH_LENGTH];		//�����ַ�������
	memset(search, 0, sizeof(search));	//����
	package* pack_search = NULL;
	user* user_search = NULL;
	struct tm* nowTime = GetNowTime();
	struct tm* lastTime_S = nowTime;
	struct tm* lastTime_L = nowTime;

	//ÿ���״ε�½����
	if (logoutTime.tm_year != 0
		&& (logoutTime.tm_year != nowTime->tm_year
			|| logoutTime.tm_mon != nowTime->tm_mon
			|| logoutTime.tm_mday != nowTime->tm_mday))
	{
		//����ף��
		festival* fes = isFestival();
		if (fes != NULL)
		{
			message* mess = CreatOneMessage("", IMP_SPECIAL);
			sprintf(mess->content, "%s ���֣�", fes->name);
			AddMessage(admin->mlist, mess);
		}
		//��������
		GoThroughPackage();
	}

	while (TRUE)
	{
		//��ʱ����
		nowTime = GetNowTime();
		if (AutoRegular__TimeSeg_S >= (nowTime->tm_min - lastTime_S->tm_min))
		{
			AdminRegular_S(admin);
			lastTime_S = nowTime;
		}
		if (AutoRegular__TimeSeg_L >= (nowTime->tm_min - lastTime_L->tm_min))
		{
			AdminRegular_L(admin);
			lastTime_L = nowTime;
		}

		//���ó�ʼ��key
		//��Ҫ������дcls
		SetCursorPosition(0, 0);
		memset(search, 0, sizeof(search));
		pack_search = NULL;
		user_search = NULL;

		//������
		//ʱ��
		printf("<����Ա������>\n");
		printf("��ǰʱ�䣺");
		PrintNowTime();

		//�Ʊ�
		printf("\n�ܲƲ���%lf\n", fund);

		//֪ͨ
		printf("\n֪ͨ:\n");
		PrintNumMessage(admin->mlist, MESS_NUM);
		printf("\n");
		//����˵��
		printf("���¶�Ӧ������ѡ����...\n\n");

		printf("[ESC]�˳�\n\n");

		printf("����֪ͨ��\n");
		printf("[`]����֪ͨ\n\n");

		printf("�ڹ�����\n");
		printf("[0]�ڹ�����\n\n");

		printf("��ѯ���ܣ�\n");
		printf("[1]����\n");
		printf("[2]����\n");
		printf("[3]�û�\n");
		printf("[4]��ʷ��¼\n\n");

		printf("¼�빦�ܣ�\n");
		printf("[5]¼�����\n");
		printf("[6]�������\n\n");

		printf("�㲥���ܣ�\n");
		printf("[7]�㲥���û�\n\n");

		printf("������Ϣ�޸�:\n");
		printf("[8]�޸ĸ�����Ϣ\n\n");

		printf("������\n");
		printf("[9]����ѡ��\n");
		printf("[q]�˳���½\n\n");

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//�����ж�->��Ϣѭ��
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
			printf("�˳�����\n [y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				//��¼�˳�ʱ��
				RecordLogoutTime();
				//��¼�˳��˺�
				RecordLogoutUser(admin);
				//�˳�
				powerTag = EXIT;
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
		//����֪ͨ
		case '`':
		{
			//����д����ModifyMessage()����
			MessSys(admin);
			//����
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�ڹ�����
		case '0':
		{
			ManagePay();
			key = ERROR;
			system("cls");
			break;
		}
		//��ѯ����
		case '1':
		{
			system("cls");
			printf("<��ѯ����>\n");
			printf("����[ESC]����\n");
			printf("״̬���ձ�:(״̬��������������)\n");
			printf("[%d]�쳣 [%d]��Ź��� [%d]��ǩ�� [%d]������ [%d]������ [%d]���� [%d]��ǩ��\n",
				STATE_ERROR, STATE_STAY_LONG, STATE_WAIT_PICK, STATE_TRANSPORT, STATE_WAIT_COLLECT, STATE_REJECT, STATE_PICKUPED);
			printf("������");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			printf("\n\n");

			if (search[0] == ESC)//ESC���
			{
				key = ERROR;//����
				system("cls");
				break;//break switch
			}

			pack_search = AdminFindPackage(phead, search);
			if (pack_search != NULL)
			{
				//�ɹ�����
				printf("����[`]   �༭ģʽ\n");
				printf("����[�ո�] ��������\n\n");
				
				printf("����ѯ�� %d �������������ʾ�������ݣ�����༭ģʽ�鿴����.\n", CountPackage(pack_search));
				PrintNumPackage(pack_search, PAGE_NUM);
				printf("\n");
				PrintAllPackage(phead);

				//������
				while (TRUE)
				{
					InputBox(&key, 1, MODE_KEY, ON);
					if (key == ESC)
					{
						//����
						key = ERROR;
						system("cls");
						break;
					}
					if (key == '`')
					{
						EditPackage(pack_search);//����༭ģʽ
						key = '1';//����Ϊ��������
						break;
					}
					if (key == ' ')
					{
						key = '1';//����Ϊ��������
						break;
					}
				}
			}
			else
			{
				//ʧ�ܴ���
				printf("�޽��......\n\n");
				system("pause");//��Ĭ�ȴ�
			}

			system("cls");

			break;//break switch
		}
		//��ѯ����
		case '2':
		{
			system("cls");
			printf("<��ѯ����>\n");
			printf("����[ESC]����\n");
			PrintAllShelf();
			printf("\n");

			printf("���뷶���� A0_1,2  D4_3,4\n");
			printf("�����");
			InputBox(search, MAX_LOCATION, MODE_SHOW, ON);

			if (search[0] == ESC)//ESC���
			{
				//����
				key = ERROR;
				system("cls");
				break;
			}

			shelf* theShelf = StrToShelf(search);

			if (theShelf == NULL)
			{
				printf("����Ļ��ܸ�ʽ����ȷ�������ԣ�\n");
				system("pause");
				//����
				//key = ERROR;
				system("cls");
				break;
			}

			printf("%s ��״̬���£�\n", search);
			char shelf_state[5];
			TFtoStr(shelf_state, theShelf->used);
			printf("�Ƿ�ռ�ã�%s\n", shelf_state);
			printf("ռ�õİ����˵��ţ�%s\n", theShelf->pack_id);
			system("pause");//��Ĭ�ȴ�
			system("cls");
			break;//break switch
		}
		//��ѯ�û�
		case '3':
		{
			system("cls");
			printf("<��ѯ�û�>\n");
			printf("����[ESC]����\n");
			printf("������");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			printf("\n");

			if (search[0] == ESC)//ESC���
			{
				key = ERROR;//����
				system("cls");
				break;//break switch
			}

			user_search = FindUser(uhead, search);//��ѯ���
			if (user_search != NULL)
			{
				//�ɹ�����
				PrintOneUser(user_search);
			}
			else
			{
				//ʧ�ܴ���
				printf("�޽��......\n");
			}

			system("pause");//��Ĭ�ȴ�
			system("cls");

			break;//break switch
		}
		//��ѯ��ʷ����
		case '4':
		{
			system("cls");
			printf("<��ѯ��ʷ��¼>\n");
			printf("[ESC]�˳�\n");
			printf("��ʽeg��20060105\n");
			printf("�����롪��\n");
			//����1
			printf("��ʼ���ڣ�");
			InputBox(search, MAX_DATA, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (strlen(search) != MAX_DATA
				|| FALSE == isAllDigits(search))
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			//����ת��
			int dataNum = atof(search);			//eg:20060105
			if (dataNum < 0)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			struct tm data1 = { 0 };
			data1.tm_year = dataNum / 10000;	//û����MAX_DATA�����������ע��
			data1.tm_mon = (dataNum % 10000) / 100;
			data1.tm_mday = dataNum % 100;
			if (12 < data1.tm_mon)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			if (DaysInMonth(data1.tm_year, data1.tm_mon) < data1.tm_mday)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			//����2
			printf("��ֹ���ڣ�");
			InputBox(search, MAX_DATA, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (strlen(search) != MAX_DATA
				|| FALSE == isAllDigits(search))
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			//����ת��
			dataNum = atof(search);				//eg:20060105
			if (dataNum < 0)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			struct tm data2 = { 0 };
			data2.tm_year = dataNum / 10000;	//û����MAX_DATA�����������ע��
			data2.tm_mon = (dataNum % 10000) / 100;
			data2.tm_mday = dataNum % 100;
			if (12 < data2.tm_mon)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}
			if (DaysInMonth(data2.tm_year, data2.tm_mon) < data2.tm_mday)
			{
				printf("�����ʽ���������ԣ�\n");
				system("pause");
				system("cls");
				break;
			}

			//��ʽ��ѯ
			ReadPackHis(&data1, &data2);
			system("pause");

			//key = ERROR;
			system("cls");
			break;
		}
		//¼�����
		case '5':
		{
			package* pack = CreatOnePackage();//�����հװ���
			//����д����EnterPackage()����
			if (EnterPackage(pack) == FALSE)//������Ϣ
			{
				//ʧ�ܴ���
				key = ERROR;//����
				free(pack);
				system("cls");
				continue;
			}
			//�ɹ�����
			AddOnePackage(phead, pack); //��������
			printf("\n¼��ɹ���\n");
			PrintOnePackage(pack); //����ȫ����Ϣ

			system("pause");//��Ĭ�ȴ�
			system("cls");

			break;//break switch
		}
		//�������
		case '6':
		{
			system("cls");
			printf("<�������>\n");
			printf("����[ESC]����\n");
			printf("�˵��ţ�");
			InputBox(search, MAX_ID, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (FALSE == JungePackageInformation(ID, search))
			{
				printf("\n������˵��Ÿ�ʽ����������\n");
				system("pause");
				system("cls");
				break;
			}
			pack_search = AdminFindPackage(phead, search);
			if (NULL == pack_search)
			{
				printf("\n������˵��Ų����ڣ�������\n");
				system("pause");
				system("cls");
				break;
			}
			printf("\n�ҵ����°�������ȷ��.\n");
			PrintOnePackage(pack_search);
			printf("\nȷ����⣿\n");
			printf("[y/n]\n");
			InputBox(search, 1, MODE_KEY, OFF);
			if (search[0] != 'y')
			{
				printf("��ȡ�����...\n");
				printf("���ڷ���...\n");
				system("pause");
				system("cls");
				break;
			}
			if (pack_search->state == STATE_WAIT_PICK)
			{
				printf("�����ظ���⣡\n");
				printf("���ڷ���......\n");
				system("pause");
				system("cls");
				break;
			}
			if (FALSE == AllocateLocation(pack_search, ahead))
			{
				printf("���ʧ��...\n");
				printf("�������������飡\n");
				printf("���ڷ���...\n");
				system("pause");
				system("cls");
				break;
			}
			user* temUser = FindUser(uhead, pack_search->tele_num);
			if (temUser != NULL)
			{
				message* mess = CreatOneMessage("", IMP_NORMAL);
				sprintf(mess->content, "��İ�����%s����ǩ��", pack_search->pack_name);
				AddMessage(temUser->mlist, mess);
			}
			printf("���ɹ���\n");
			printf("�ɹ����������䵽��%s\n", pack_search->location);
			printf("���ڷ���...\n");
			system("pause");
			system("cls");
			break;//break switch
		}
		//�㲥
		case '7':
		{
			system("cls");
			printf("����[ESC]����\n");
			printf("������㲥��Ϣ��");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			if (search[0] == ESC)//ESC���
			{
				//����
				key = ERROR;
				system("cls");
				break;
			}
			//ȷ�ϣ�
			printf("\nȷ���㲥������Ϣ��\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key != 'y')
			{
				key = '6';
				system("cls");
				break;
			}
			//��ʽ�㲥
			message* mess = CreatOneMessage(search, IMP_SPECIAL);
			Broadcast(mess, uhead);//�㲥���û�
			printf("\n�㲥�ɹ���\n");
			printf("���ڷ���...\n");
			key = '6';
			system("pause");
			system("cls");
			break;//break switch
		}
		//����Ա������Ϣ�޸�
		case '8':
		{
			system("cls");
			printf("<�޸ĸ�����Ϣ>\n");
			printf("����[ESC]����\n");
			PrintOneUser(admin);
			printf("\n�Ƿ�Ҫ�޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				ModifyUserInterface(admin);
			}
			else
				//����
				key = ERROR;
			system("cls");

			break;//break switch
		}
		//����ѡ��
		case '9':
		{
			SaveOption();
			key = ERROR;
			system("cls");
			break;
		}
		//�˳���½
		case 'q':
		{
			system("cls");
			printf("�˳���½��\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				//����logoutTime��¼
				ClearLogout();
				//�ط���½
				powerTag = RESTART;
				return;
			}
			else
			{
				//����
				key = ERROR;
				system("cls");
				break;//break switch
			}

		}
		}//end switch

		//Sleep(500);//ϵͳ��Ӧʱ�� ��λΪms ���������˸����->��˸�����ѽ��
		
	}//end while
}


//�ֶ�¼����� �ɹ�����TRUE ʧ�ܷ���FALSE
int EnterPackage(package* pack)
{
	system("cls");
	if (pack == NULL)
	{
		printf("�Ƿ�������NULLָ�룡(ModifyPackage)\n");
		system("pause");
		return FALSE;
	}

	//׼������
	char key = ERROR;
	//�������ʱ��
	//struct tm* nowTime = GetNowTime();
	//SetPackageInTime(pack, nowTime->tm_year, nowTime->tm_mon, nowTime->tm_mday);

	//��Ϣѭ��
	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);

		//����
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");
		printf("<¼��ģʽ>\n");
		PrintOnePackage(pack);

		printf("\n�������°���ѡ��༭\n");
		printf("[ESC]�˳�\n");
		printf("[%c]ȷ��¼�����\n", ALLRIGHT);
		printf("[%c]��д����\n\n", RULE);

		//¼��ģʽ����
		printf("[%c]�˵���\n", ID);
		printf("[%c]��������\n", PACK_NAME);
		printf("[%c]��ŵص�(ѡ��)\n", LOCATION);
		printf("[%c]ȡ����(ѡ��)\n", PICKCODE);
		//

		printf("[%c]����״̬\n\n", STATE);

		printf("[%c]�ֻ���\n", TELE);
		printf("[%c]�ռ�������\n", USER);
		printf("[%c]�ļ�������\n", SENDER);
		printf("[%c]�ռ��˵�ַ\n", USER_ADDR);
		printf("[%c]�ļ��˵�ַ\n\n", SENDER_ADDR);

		printf("[%c]�˷�\n", BILL);
		printf("[%c]����\n", WEIGHT);
		printf("[%c]���\n", SIZE);
		printf("[%c]ƫԶ����\n", FAR_AREA);
		printf("[%c]����Ʒ\n", FRAG);
		printf("[%c]����Ʒ\n\n", VALU);


		//�����Լ���������Ϣ���ɸ�
		//1.�˵���
		//2.�����ʱ��
		//3.ȡ����
		//4.��������

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//��Ϣ�ж�
		switch (key)
		{
			//����Ӧ
		case ERROR:
		{
			break;//break switch
		}
		//ȷ��¼��
		case ALLRIGHT:
		{
			system("cls");
			printf("ϵͳ���Զ����¼�������Ƿ�Ϲ�\n");
			printf("�Ƿ�¼����ϣ�\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				char bill[20];
				char weight[20];
				char size[20];
				memset(bill, 0, 20);
				memset(weight, 0, 20);
				memset(size, 0, 20);
				sprintf(bill, "%f", pack->Bill);
				sprintf(weight, "%f", pack->weight);
				sprintf(size, "%f", pack->size);
				if (JungePackageInformation(ID, pack->id)
					&& JungePackageInformation(TELE, pack->tele_num)
					&& JungePackageInformation(PACK_NAME, pack->pack_name)
					&& JungePackageInformation(USER, pack->user_name)
					&& JungePackageInformation(SENDER, pack->sender_name)
					&& JungePackageInformation(USER_ADDR, pack->user_address)
					&& JungePackageInformation(SENDER_ADDR, pack->send_address)
					&& JungePackageInformation(BILL, bill)
					&& JungePackageInformation(WEIGHT, weight)
					&& JungePackageInformation(SIZE, size)
					&& JungePackageInformation(FAR_AREA, &(pack->isRemoteArea))
					&& JungePackageInformation(FRAG, &(pack->isFragile))
					&& JungePackageInformation(VALU, &(pack->isValuable))
					)
				{
					return TRUE;
				}
				else
				{
					printf("\n������д��������\n");
					system("pause");
					//����
					key = ERROR;
					system("cls");
					break;//break switch
				}
			}
			else
			{
				key = ERROR;
				system("cls");
				break;//break switch
			}

			break;//break switch
		}
		//�˳�
		case ESC:
		{
			system("cls");
			printf("��������ݽ���ʧ\n");
			printf("�Ƿ����¼�룿\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				return FALSE;
			}
			else
			{
				//����
				key = ERROR;
				system("cls");
				break;//break switch
			}
		}

		//�����д����
		case RULE:
		{
			system("cls");
			PrintInputRule();
			system("pause");//��Ĭ�ȴ�
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}

		//¼��ģʽ����
		//�˵���
		case ID:
		{
			system("cls");
			printf("ԭ�˵��ţ�%s\n", pack->id);
			ModifyPackage(pack, key, "�˵���", MODE_NUM, MAX_ID);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//��������
		case PACK_NAME:
		{
			system("cls");
			printf("ԭ�������ƣ�%s\n", pack->pack_name);
			ModifyPackage(pack, key, "��������", MODE_SHOW, MAX_PACK_NAME);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//��ŵ�ַ
		case LOCATION:
		{
			system("cls");
			printf("ԭ��ŵ�ַ��%s\n", pack->location);
			ModifyPackage(pack, key, "��ŵ�ַ", MODE_SHOW, MAX_LOCATION);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//ȡ����
		case PICKCODE:
		{
			system("cls");
			printf("ԭȡ���룺%s\n", pack->pickupCode);
			ModifyPackage(pack, key, "ȡ����", MODE_SHOW, MAX_PICKUP_CODE);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//��������

		//�޸İ���״̬
		case STATE:
		{
			system("cls");
			ModifyState(pack);
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//�޸��ֻ���
		case TELE:
		{
			system("cls");
			printf("ԭ�ֻ��ţ�%s\n", pack->tele_num);
			ModifyPackage(pack, key, "�ֻ���", MODE_NUM, MAX_TELE_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸��ռ�������
		case USER:
		{
			system("cls");
			printf("ԭ�ռ������ƣ�%s\n", pack->user_name);
			ModifyPackage(pack, key, "�ռ�������", MODE_SHOW, MAX_USER_NAME);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸ļļ�������
		case SENDER:
		{
			system("cls");
			printf("ԭ�ļ������ƣ�%s\n", pack->sender_name);
			ModifyPackage(pack, key, "�ļ�������", MODE_SHOW, MAX_USER_NAME);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸��ռ��˵�ַ
		case USER_ADDR:
		{
			system("cls");
			printf("ԭ�ռ��˵�ַ��%s\n", pack->user_address);
			ModifyPackage(pack, key, "�ռ��˵�ַ", MODE_SHOW, MAX_ADDRESS);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸ļļ��˵�ַ
		case SENDER_ADDR:
		{
			system("cls");
			printf("ԭ�ļ��˵�ַ��%s\n", pack->send_address);
			ModifyPackage(pack, key, "�ļ��˵�ַ", MODE_SHOW, MAX_ADDRESS);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸��˷�
		case BILL:
		{
			system("cls");
			printf("ԭ�˷ѣ�%f Ԫ\n", pack->Bill);
			ModifyPackage(pack, key, "�˷�", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸�����
		case WEIGHT:
		{
			system("cls");
			printf("ԭ������%f kg\n", pack->weight);
			ModifyPackage(pack, key, "����", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸����
		case SIZE:
		{
			system("cls");
			printf("ԭ�����%f cm^3\n", pack->size);
			ModifyPackage(pack, key, "���", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸�ƫԶ����
		case FAR_AREA:
		{
			system("cls");
			printf("ԭƫԶ������%d\n", pack->isRemoteArea);
			ModifyPackage(pack, key, "ƫԶ����(0Ϊ��,1Ϊ��)", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸�����Ʒ
		case FRAG:
		{
			system("cls");
			printf("ԭ����Ʒ��%d\n", pack->isFragile);
			ModifyPackage(pack, key, "����Ʒ(0Ϊ��,1Ϊ��)", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸����Ʒ
		case VALU:
		{
			system("cls");
			printf("ԭ������Ʒ��%d\n", pack->isValuable);
			ModifyPackage(pack, key, "���Ʒ(0Ϊ��,1Ϊ��)", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}

		}//end switch
	}//end while
}

//����Ա�༭��ѯ���İ���
void EditPackage(package* head)
{
	//��������
	system("cls");

	//NULL���
	if (head == NULL)
	{
		return;
	}

	//�Զ������ڱ�head
	if (head->prior == NULL)
		head = head->next;

	//NULL���
	if (head == NULL)
	{
		printf("�ް�����Ϣ\n");
		system("pause");
		return;
	}

	//Ԥ������
	char key = ERROR;		//����
	int i = ERROR;			//�������� ��ʵ��
	package* point = head;  //�α�
	package* tmp = NULL;	//��̽�α�

	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);
		tmp = NULL;
		i = ERROR;

		//����		
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");

		printf("<�༭����ģʽ>\n");
		printf("����[ESC]����\n");
		printf("����[a/d]��ҳ\n");
		printf("����[1 2 3 4 5]ѡ��\n\n");

		//��ӡ
		PrintNumPackage(point, PAGE_NUM);

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
			break;
		}
		//�˳�
		case ESC:
		{
			system("cls");
			printf("�˳��༭��\n [y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				return;
			}
			else
			{
				key = ERROR;
				system("cls");
			}

			break;//break switch
		}
		//��һҳ
		case BUTTON_LEFT: 
		{
			tmp = point;
			for (i = 0; i < PAGE_NUM && tmp->prior != NULL; i++)//��ֹ�ߵ�ͷ
			{
				tmp = tmp->prior;
			}
			if (i == PAGE_NUM)//��֤����PAGE_NUM����
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
			for (i = 0; i < PAGE_NUM && tmp->next != NULL; i++)//��ֹ�ߵ�ͷ
			{
				tmp = tmp->next;
			}
			if (i == PAGE_NUM)//��֤����page_num����
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
				ModifyPackageInterface(tmp);
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		}//end switch

	}//end while
}

//��������Ա�༭��ѯ���Ĵμ�����Ա
void EditAdmin(user* head)
{
	//��������
	system("cls");

	//NULL���
	if (head == NULL)
	{
		return;
	}

	//�Զ������ڱ�head
	if (head->prior == NULL)
		head = head->next;

	//NULL���
	if (head == NULL)
	{
		return;
	}

	//Ԥ������
	char key = ERROR;		//����
	int i = ERROR;			//�������� ��ʵ��
	user* point = head;  //�α�
	user* tmp = NULL;	//��̽�α�

	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);
		tmp = NULL;
		i = ERROR;

		//����		
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");

		printf("<�༭����Ա�û�ģʽ>\n");
		printf("����[ESC]����\n");
		printf("����[a/d]��ҳ\n");
		printf("����[1 2 3 4 5]ѡ��\n\n");

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//��ӡ
		PrintNumAdmin(point, ADMIN_NUM);

		//��Ϣѭ��
		switch (key)
		{
			//����Ӧ
		case ERROR:
		{
			break;
		}
		//�˳�
		case ESC:
		{
			system("cls");
			printf("�˳��༭��\n [y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				return;
			}
			else
			{
				key = ERROR;
				system("cls");
			}

			break;//break switch
		}
		//��һҳ
		case BUTTON_LEFT:
		{
			tmp = point;
			for (i = 0; i < ADMIN_NUM && tmp->prior != NULL; i++)//��ֹ�ߵ�ͷ
			{
				tmp = tmp->prior;
			}
			if (i == ADMIN_NUM)//��֤����PAGE_NUM����
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
			for (i = 0; i < ADMIN_NUM && tmp->next != NULL; i++)//��ֹ�ߵ�ͷ
			{
				tmp = tmp->next;
			}
			if (i == ADMIN_NUM)//��֤����page_num����
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
				ModifyAdminInterface(tmp);
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		}//end switch

	}//end while

}

//ѡ�����޸İ���-����
void ModifyPackageInterface(package* pack)
{
	system("cls");
	if (pack == NULL)
	{
		printf("�Ƿ�������NULLָ�룡(ModifyPackage)\n");
		system("pause");
	}

	//׼������
	char key = ERROR;

	//��Ϣѭ��
	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);

		//����
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");
		printf("<�޸İ���ģʽ>\n");
		PrintOnePackage(pack);

		printf("\n�������°���ѡ��༭\n");
		printf("[ESC]�˳�\n");
		printf("[%c]��д����\n\n",RULE);

		printf("[%c]����״̬\n\n",STATE);

		printf("[%c]�ֻ���\n",TELE);
		printf("[%c]�ռ�������\n",USER);
		printf("[%c]�ļ�������\n",SENDER);
		printf("[%c]�ռ��˵�ַ\n",USER_ADDR);
		printf("[%c]�ļ��˵�ַ\n\n",SENDER_ADDR);

		printf("[%c]�˷�\n",BILL);
		printf("[%c]����\n",WEIGHT);
		printf("[%c]���\n",SIZE);
		printf("[%c]ƫԶ����\n",FAR_AREA);
		printf("[%c]����Ʒ\n",FRAG);
		printf("[%c]����Ʒ\n",VALU);
		printf("[%c]�ͻ�����\n\n",TODOOR);


		//�����Լ���������Ϣ���ɸ�
		//1.�˵���
		//2.�����ʱ��
		//3.ȡ����
		//4.��������

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//��Ϣ�ж�
		switch (key)
		{
		//����Ӧ
		case ERROR:
		{
			break;//break switch
		}
		//�˳�
		case ESC:
		{
			system("cls");
			printf("\n�˳��޸�ģʽ��\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
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

		//�����д����
		case RULE:
		{
			system("cls");
			PrintInputRule();
			system("pause");//��Ĭ�ȴ�
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}

		//�޸İ���״̬
		case STATE:
		{
			system("cls");
			ModifyState(pack);
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//�޸��ֻ���
		case TELE:
		{
			system("cls");
			printf("ԭ�ֻ��ţ�%s\n", pack->tele_num);
			ModifyPackage(pack, key, "�ֻ���", MODE_NUM, MAX_TELE_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸��ռ�������
		case USER:
		{
			system("cls");
			printf("ԭ�ռ������ƣ�%s\n", pack->user_name);
			ModifyPackage(pack, key, "�ռ���", MODE_SHOW, MAX_USER_NAME);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸ļļ�������
		case SENDER:
		{
			system("cls");
			printf("ԭ�ļ������ƣ�%s\n", pack->sender_name);
			ModifyPackage(pack, key, "�ļ�������", MODE_SHOW, MAX_USER_NAME);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸��ռ��˵�ַ
		case USER_ADDR:
		{
			system("cls");
			printf("ԭ�ռ��˵�ַ��%s\n", pack->user_address);
			ModifyPackage(pack, key, "�ռ��˵�ַ", MODE_SHOW, MAX_ADDRESS);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸ļļ��˵�ַ
		case SENDER_ADDR:
		{
			system("cls");
			printf("ԭ�ļ��˵�ַ��%s\n", pack->send_address);
			ModifyPackage(pack, key, "�ļ��˵�ַ", MODE_SHOW, MAX_ADDRESS);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸��˷�
		case BILL:
		{
			system("cls");
			printf("ԭ�˷ѣ�%f Ԫ\n", pack->Bill);
			ModifyPackage(pack, key, "�˷�", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸�����
		case WEIGHT:
		{
			system("cls");
			printf("ԭ������%f kg\n", pack->weight);
			ModifyPackage(pack, key, "����", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸����
		case SIZE:
		{
			system("cls");
			printf("ԭ�����%f cm^3\n", pack->size);
			ModifyPackage(pack, key, "���", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸�ƫԶ����
		case FAR_AREA:
		{
			system("cls");
			printf("ԭƫԶ������%d\n", pack->isRemoteArea);
			ModifyPackage(pack, key, "ƫԶ����(0Ϊ��,1Ϊ��)", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸�����Ʒ
		case FRAG:
		{
			system("cls");
			printf("ԭ����Ʒ��%d\n", pack->isFragile);
			ModifyPackage(pack, key, "����Ʒ(0Ϊ��,1Ϊ��)", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸����Ʒ
		case VALU:
		{
			system("cls");
			printf("ԭ������Ʒ��%d\n", pack->isValuable);
			ModifyPackage(pack, key, "���Ʒ(0Ϊ��,1Ϊ��)", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�޸��ͻ�����
		case TODOOR:
		{
			system("cls");
			printf("ԭ�ͻ����ţ�%d\n", pack->isToDoor);
			ModifyPackage(pack, key, "�ͻ�����(0Ϊ��,1Ϊ��)", MODE_NUM, MAX_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		}//end switch
	}//end while

}

//�ж�����İ�����Ϣ�Ƿ���Ϲ涨-ѡ�����޸İ�����������㺯��
int JungePackageInformation(const char key,const char* input)
{
	switch (key)
	{
	//�˵���
	case ID:
	{
		if (strlen(input) != MAX_ID
			|| isAllDigits(input) == FALSE)
		{
			return FALSE;
		}
		break;//break switch
	}
	//���λ��
	case LOCATION:
	{
		//ע�⣺���ü��հ�
		if (strlen(input) != 0)
		{
			//�ж������ʽ
			if (strlen(input) != 6)
			{
				return FALSE;
			}
			else if (input[2] != '_' || input[4] != ',')
			{
				return FALSE;
			}
			else if (!('A' <= input[0] && input[0] <= SHELF_NUM + 'A'))
			{
				return FALSE;
			}
			else if (!('0' <= input[1] && input[1] <= SHELF_NUM + '0'))
			{
				return FALSE;
			}
			else if (!('0' <= input[3] && input[3] <= LINE + '0'))
			{
				return FALSE;
			}
			else if (!('0' <= input[5] && input[5] <= ROW + '0'))
			{
				return FALSE;
			}
			else
			{
				return TRUE;
			}
			//�ж��Ƿ�ռ��
			//else if (shelfs[input[0] - 'A'][input[1] - '0'][input[3] - '0'][input[5] - '0'].used == TRUE)
			//{
			//	return FALSE;
			//}
		}
		break;//break switch
	}
	//ȡ����
	case PICKCODE:
	{
		if (strlen(input) != MAX_PICKUP_CODE
			|| isAllDigits(input) == FALSE)
		{
			return FALSE;
		}
		break;//break switch
	}
	//�ֻ���
	case TELE:
	{
		if (strcmp(input, DEF_STR) == 0
			|| strlen(input) != MAX_TELE_NUM
			|| isAllDigits(input) == FALSE)
		{
			return FALSE;
		}
		break;//break switch 
	}
	//��������ַ����������
	case USER:
	case SENDER:
	case USER_ADDR:
	case SENDER_ADDR:
	case PACK_NAME:
	{
		if (strcmp(input, DEF_STR) == 0
			|| strlen(input) == 0)
		{
			return FALSE;
		}
		break;//break switch
	}
	//�˷� ����������
	case BILL:
	case WEIGHT:
	case SIZE:
	{
		if (atof(input) <= 0)
		{
			return FALSE;
		}
		break;//break switch
	}
	case FAR_AREA:
	case FRAG:
	case VALU:
	case TODOOR:
	{
		if (*input < 0)
		{
			return FALSE;
		}
		break;//break switch
	}

	}//end switch

	return TRUE;
}

//ѡ�����޸İ���-��㺯��
int ModifyPackage(package* pack, const char _key, const char* information,const int inputMode,const int MaxLen)
{
	//׼������
	char input[MAX_SEARCH_LENGTH];
	char key = ERROR;
	memset(input, 0, MAX_SEARCH_LENGTH);

	//����
	printf("��%s��", information);
	InputBox(input, MaxLen, inputMode, ON);

	//�˳�
	if (input[0] == ESC)
	{
		return FALSE;
	}

	//�жϸ�ʽ
	if (!(JungePackageInformation(_key, input)))
	{
		//����
		printf("\n�޸�ʧ��...\n");//��֪��Ϊɶ��һ���ֲ���ʾ
		system("pause");
		system("cls");

		return FALSE;
	}

	//ȷ���޸�
	printf("\nȷ���޸ģ�\n");
	printf("[y/n]\n");
	InputBox(&key, 1, MODE_KEY, ON);
	if (key != 'y')
	{
		printf("\n��ȡ���޸�\n");
		system("pause");
		system("cls");
		return FALSE;
	}

	//��ʽ�޸�
	switch (_key)
	{
	case ID:
		memcpy(pack->id, input, MaxLen);
		break;
	case LOCATION:
		memcpy(pack->location, input, MaxLen);
		shelfs[pack->location[0] - 'A'][pack->location[1] - '0'][pack->location[3] - '0'][pack->location[5] - '0'].used = TRUE;
		break;
	case PICKCODE:
		memcpy(pack->pickupCode, input, MaxLen);
		break;
	case PACK_NAME:
		memcpy(pack->pack_name, input, MaxLen);
		break;
	case TELE:
		memcpy(pack->tele_num, input, MaxLen);
		break;
	case USER:
		memcpy(pack->user_name, input, MaxLen);
		break;
	case SENDER:
		memcpy(pack->sender_name, input, MaxLen);
		break;
	case USER_ADDR:
		memcpy(pack->user_address, input, MaxLen);
		break;
	case SENDER_ADDR:
		memcpy(pack->send_address, input, MaxLen);
		break;
	case BILL:
		pack->Bill = atof(input);
		break;
	case WEIGHT:
		pack->weight = atof(input);
		break;
	case SIZE:
		pack->size = atof(input);
		break;
	case FAR_AREA:
		pack->isRemoteArea = atof(input);
		break;
	case FRAG:
		pack->isFragile = atof(input);
		break;
	case VALU:
		pack->isValuable = atof(input);
		break;
	case TODOOR:
		pack->isToDoor = atof(input);
		break;
	}
	printf("\n��%s �޸ĳɹ�!\n", information);
	system("pause");
	system("cls");

	return TRUE;
}

//�޸İ���״̬
void ModifyState(package* pack)
{
	//׼������
	system("cls");
	if (pack == NULL)
	{
		printf("�Ƿ�������NULLָ�룡(ModifyState)\n");
		system("pause");
	}
	char key = ERROR;
	char input[MAX_SEARCH_LENGTH];
	char state[MAX_STATE];
	memset(state, 0, MAX_STATE);
	StateToStr(state, pack->state);

	//��Ϣѭ��
	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);
		memset(input, 0, MAX_SEARCH_LENGTH);

		//����
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");
		printf("<�޸İ���״̬>\n");
		printf("����[ESC]����\n\n");

		printf("��״̬��%s\n\n", state);

		printf("����������\n");
		printf("[%d]�쳣������������ʧ�ܵȣ�\n",STATE_ERROR);
		printf("[%d]��������\n\n",STATE_STAY_LONG);
		printf("[%d]��ǩ��\n",STATE_WAIT_PICK);
		printf("[%d]������\n",STATE_TRANSPORT);
		printf("[%d]������\n",STATE_WAIT_COLLECT);
		printf("[%d]����\n",STATE_REJECT);
		printf("[%d]��ǩ��\n",STATE_PICKUPED);

		printf("�°���״̬:");

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		switch (key)
		{
			//����Ӧ
		case ERROR:
		{
			break;
		}
		//�˳�
		case ESC:
		{
			system("cls");
			return;
			//printf("�˳���\n [y/n]\n");
			//InputBox(&key, 1, MODE_KEY, OFF);
			//if (key == 'y')
			//{
			//	return;
			//}
			//else
			//{
			//	key = ERROR;
			//	system("cls");
			//}

			break;//break switch

		}
		//ѡ��״̬��ֵ->���ֱ���һһ��Ӧö������
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		{
			pack->state = key - '0';
			StateToStr(state, pack->state);
			printf("%s\n", state);
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		}//end switch
	}//end while
}



//ѡ�����޸ĸ�����Ϣ-����
int ModifyUserInterface(user* user)
{
	system("cls");
	if (user == NULL)
	{
		printf("�Ƿ�������NULLָ�룡(ModifyUser)\n");
		system("pause");
	}

	//׼������
	char key = ERROR;
	char input[MAX_SEARCH_LENGTH];
	memset(input, 0, MAX_SEARCH_LENGTH);

	//��Ϣѭ��
	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);
		memset(input, 0, MAX_SEARCH_LENGTH);

		//����
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");
		printf("<�޸ĸ�����Ϣģʽ>\n");
		PrintOneUser(user);

		printf("\n�������°���ѡ��༭\n");
		printf("[ESC]�˳�\n");
		printf("[%c]��д����\n\n", RULE);

		printf("[%c]����\n", NAME);
		printf("[%c]�ֻ���\n", TELENUM);
		printf("[%c]����\n\n", PASSWORD);

		printf("[%c]Ĭ�ϵ�ַ\n", DEFUALT_ADDR);
		printf("[%c]��ַ_1\n", ADDR_1);
		printf("[%c]��ַ_2\n", ADDR_2);
		printf("[%c]��ַ_3\n\n", ADDR_3);

		printf("[%c]ע���˺�\n\n", CANCEL);

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

		//�����д����
		case RULE:
		{
			system("cls");
			PrintInputRule();
			system("pause");//��Ĭ�ȴ�
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//�˳�
		case ESC:
		{
			system("cls");
			printf("\n�˳��޸�ģʽ��\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
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

		//����
		case NAME:
		{
			system("cls");
			printf("ԭ���ƣ�%s\n", user->name);
			ModifyUser(user, key, "����", MODE_SHOW, MAX_USER_NAME);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�ֻ���
		case TELENUM:
		{
			system("cls");
			printf("ԭ�ֻ��ţ�%s\n", user->tele_num);
			ModifyUser(user, key, "�ֻ���", MODE_SHOW, MAX_TELE_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//����
		case PASSWORD:
		{
			system("cls");
			printf("ԭ���룺%s\n", user->password);
			ModifyUser(user, key, "����", MODE_SHOW, MAX_PASSWORD_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//Ĭ�ϵ�ַ
		case DEFUALT_ADDR:
		{
			system("cls");
			ModifyDefaulatAddress(user);
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//��ַ_1
		case ADDR_1:
		{
			system("cls");
			printf("ԭ��ַ_1��%s\n", user->address_1);
			ModifyUser(user, key, "��ַ_1", MODE_SHOW, MAX_ADDRESS);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//��ַ_2
		case ADDR_2:
		{
			system("cls");
			printf("ԭ��ַ_2��%s\n", user->address_2);
			ModifyUser(user, key, "��ַ_2", MODE_SHOW, MAX_ADDRESS);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//��ַ_3
		case ADDR_3:
		{
			system("cls");
			printf("ԭ��ַ_3��%s\n", user->address_3);
			ModifyUser(user, key, "��ַ_3", MODE_SHOW, MAX_ADDRESS);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//ע���˺�
		case CANCEL:
		{
			system("cls");
			printf("\n�Ƿ�ע���˺ţ�\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				if (user->level == TOP_ADMIN
					|| user->level == ADMIN)
				{
					printf("\n����Ա��������ע���Լ����˺ţ�\n");
					system("pause");
					//����
					key = ERROR;
					system("cls");
					break;//break switch
				}
				DeleteOneUser(user);
				printf("\nע���ɹ���\n");
				printf("�����˳�ϵͳ\n");
				system("pause");
				ExitSys();
				return RESTART;
			}
			else
			{
				key = ERROR;
				system("cls");
				break;//break switch
			}

			break;//break switch
		}
		}//end switch
	}//end while
}

//ѡ�����޸Ĺ���Ա-����
void ModifyAdminInterface(user* admin)
{
	system("cls");
	if (admin == NULL)
	{
		printf("�Ƿ�������NULLָ�룡(ModifyAdminInterface)\n");
		system("pause");
	}

	//׼������
	char key = ERROR;
	char input[MAX_SEARCH_LENGTH];
	memset(input, 0, MAX_SEARCH_LENGTH);

	//��Ϣѭ��
	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);
		memset(input, 0, MAX_SEARCH_LENGTH);

		//����
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");
		printf("<�޸Ĺ���Ա������Ϣģʽ>\n");
		PrintOneAdmin(admin);

		printf("\n�������°���ѡ��༭\n");
		printf("[ESC]�˳�\n");
		printf("[%c]��д����\n\n", RULE);

		printf("[%c]����\n", NAME);
		printf("[%c]�ֻ���\n", TELENUM);
		printf("[%c]����\n\n", PASSWORD);

		printf("[%c]ע��\n\n", CANCEL);

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

		//�����д����
		case RULE:
		{
			system("cls");
			PrintInputRule();
			system("pause");//��Ĭ�ȴ�
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//�˳�
		case ESC:
		{
			system("cls");
			printf("\n�˳��޸�ģʽ��\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
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

		//����
		case NAME:
		{
			system("cls");
			printf("ԭ���ƣ�%s\n", admin->name);
			ModifyUser(admin, key, "����", MODE_SHOW, MAX_USER_NAME);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�ֻ���
		case TELENUM:
		{
			system("cls");
			printf("ԭ�ֻ��ţ�%s\n", admin->tele_num);
			ModifyUser(admin, key, "�ֻ���", MODE_SHOW, MAX_TELE_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//����
		case PASSWORD:
		{
			system("cls");
			printf("ԭ���룺%s\n", admin->password);
			ModifyUser(admin, key, "����", MODE_SHOW, MAX_PASSWORD_NUM);
			//���� (�ɹ��������ã�
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//ע���˺�
		case CANCEL:
		{
			system("cls");
			printf("\n�Ƿ�ע���˺ţ�\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				DeleteOneUser(admin);
				printf("\nע���ɹ���\n");
				system("pause");
				//���ﲻ��Exit
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

		}//end switch
	}//end while
}

//ѡ��Ĭ�ϵ�ַ
void ModifyDefaulatAddress(user* user)
{
	//׼������
	system("cls");
	if (user == NULL)
	{
		printf("�Ƿ�������NULLָ�룡(ModifyDefaulatAddress)\n");
		system("pause");
	}
	char key = ERROR;
	char input[MAX_SEARCH_LENGTH];

	//��Ϣѭ��
	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);
		memset(input, 0, MAX_SEARCH_LENGTH);
		//����
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");
		printf("<�޸�Ĭ�ϵ�ַ>\n");
		printf("����[ESC]����\n\n");

		printf("�ֵ�ַ��%s\n\n", user->address_default);

		printf("�������ֽ���ѡ��\n");
		printf("[1] %s\n", user->address_1);
		printf("[2] %s\n", user->address_2);
		printf("[3] %s\n\n", user->address_3);

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		switch (key)
		{
			//����Ӧ
		case ERROR:
		{
			break;
		}
		//�˳�
		case ESC:
		{
			system("cls");
			return;
			//printf("�˳���\n [y/n]\n");
			//InputBox(&key, 1, MODE_KEY, OFF);
			//if (key == 'y')
			//{
			//	return;
			//}
			//else
			//{
			//	key = ERROR;
			//	system("cls");
			//}

			break;//break switch

		}
		//ѡ��
		case '1':
		{
			user->address_default = user->address_1;
			system("cls");
			break;//break switch
		}
		case '2':
		{
			user->address_default = user->address_2;
			system("cls");
			break;//break switch
		}
		case '3':
		{
			user->address_default = user->address_3;
			system("cls");
			break;//break switch
		}
		}//end switch
	}//end while
}

//ѡ�����޸��û�-��㺯��
int ModifyUser(user* user, const char _key, const char* information, const int inputMode, const int MaxLen)
{
	//׼������
	char input[MAX_SEARCH_LENGTH];
	char key = ERROR;
	memset(input, 0, MAX_SEARCH_LENGTH);

	//����
	printf("��%s��", information);
	InputBox(input, MaxLen, inputMode, ON);

	//�˳�
	if (input[0] == ESC)
	{
		return FALSE;
	}

	//�жϸ�ʽ
	if (!(JungeUserInformation(_key, input)))
	{
		//����
		printf("\n��ʽ����ȷ���Ѵ��ڣ��޸�ʧ��...\n");//��֪��Ϊɶ��һ���ֲ���ʾ
		system("pause");
		system("cls");

		return FALSE;
	}

	//ȷ���޸�
	printf("\nȷ���޸ģ�\n");
	printf("[y/n]\n");
	InputBox(&key, 1, MODE_KEY, ON);
	if (key != 'y')
	{
		printf("\n��ȡ���޸�\n");
		system("pause");
		system("cls");
		return FALSE;
	}

	//��ʽ�޸�
	switch (_key)
	{
	case NAME:
	{
		memcpy(user->name, input, MaxLen);
		break;
	}
	case PASSWORD:
	{
		memcpy(user->password, input, MaxLen);
		break;
	}
	case TELENUM:
	{
		memcpy(user->tele_num, input, MaxLen);
		break;
	}
	case ADDR_1:
	{
		memcpy(user->address_1, input, MaxLen);
		break;
	}
	case ADDR_2:
	{
		memcpy(user->address_2, input, MaxLen);
		break;
	}
	case ADDR_3:
	{
		memcpy(user->address_3, input, MaxLen);
		break;
	}
	}
	printf("\n��%s �޸ĳɹ�!\n", information);
	system("pause");
	system("cls");

	return TRUE;
}

//�жϸ�����Ϣ����
int JungeUserInformation(const char key, const char* input)
{
	switch (key)
	{
		//���ơ����롢��ַ
	case NAME:
		if (strlen(input) <= 1)
		{
			return FALSE;
		}
		break;
	case PASSWORD:
		if (strlen(input) <= MIN_PASSWORD_NUM)
		{
			return FALSE;
		}
		int digitTag = FALSE;
		int engTag = FALSE;
		int len = strlen(input);
		for (int i = 0; i < len; i++)
		{
			if ('0' <= input[i] && input[i] <= '9')digitTag = TRUE;
			if ('a' <= input[i] && input[i] <= 'z')engTag = TRUE;
			if ('A' <= input[i] && input[i] <= 'Z')engTag = TRUE;
		}
		if (digitTag == FALSE
			|| engTag == FALSE)
		{
			return FALSE;
		}
		break;
	case ADDR_1:
	case ADDR_2:
	case ADDR_3:
	{
		if (strlen(input) == 0)
		{
			return FALSE;
		}
		break;//break switch
	}
	//�ֻ���
	case TELENUM:
	{
		if (strlen(input) != MAX_TELE_NUM
			|| FALSE == isAllDigits(input))
		{
			return FALSE;
		}
		break;//break switch 
	}
	}//end switch

	return TRUE;
}

//�޸Ļ���״̬
void ModifyShelf(shelf* theShelf)
{
	while(TRUE)
	{
		//׼������
		system("cls");
		char key = ERROR;
		char input[MAX_ID + 1];
		char TF[MAX_TF + 1];
		memset(input, 0, sizeof(input));
		memset(TF, 0, sizeof(TF));
		TFtoStr(TF, theShelf->used);

		printf("<�޸Ļ��ܽ���>\n");
		printf("[ESC]����\n");
		printf("��ǰĿ�꣺%s\n", theShelf->location);
		printf("ռ��״̬��%s\n", TF);
		printf("ռ�õİ����˵��ţ�%s\n\n", theShelf->pack_id);

		printf("�����޸ģ�\n");
		printf("[1]״̬\n");
		printf("[2]�˵���\n");

		InputBox(&key, 1, MODE_KEY, ON);
		if (key == ESC)return;

		switch (key)
		{
		case '1':
		{
			system("cls");
			printf("[ESC]����\n");
			printf("�����롪�� 1 �ǣ�0 ��\n");
			printf("ԭ״̬��%s\n", TF);
			printf("��״̬��");
			InputBox(input, 1, MODE_NUM, ON);
			if (input[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (input[0] == '0'
				|| input[0] == '1')
			{
				theShelf->used = input[0] - '0';
				printf("�޸ĳɹ�!\n");
				system("pause");
			}
			else
			{
				printf("�޸�ʧ��...\n");
				system("pause");
			}
			break;
		}
		case '2':
		{
			system("cls");
			printf("[ESC]����\n");
			printf("ԭ�˵��ţ�%s\n", theShelf->pack_id);
			printf("���˵��ţ�");
			InputBox(input, MAX_ID, MODE_NUM, ON);
			if (input[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (!JungePackageInformation(ID, input))
			{
				printf("\n������˵��Ÿ�ʽ���������ԣ�\n");
				system("pause");
				break;
			}

			strcpy(theShelf->pack_id, input);
			printf("\n�������\n");
			system("pause");
			break;
		}
		}//end switch
	}//end while
}

//�ڹ�����
void ManagePay()
{
	system("cls");
	char key = ERROR;

	while(TRUE)
	{
		SetCursorPosition(0, 0);
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n");
		printf("<�ڹ�����>\n");

		printf("[ESC]�˳�\n");
		printf("[1]�����Ż�ȯ\n");
		printf("[2]�����ѷ����Ż�ȯ\n");

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		switch (key)
		{
		case ERROR:break;
		case ESC:
			system("cls");
			return;
		case '1':
		{
			IssueCoupon(NULL);
			key = ERROR;
			system("cls");
			break;
		}
		case '2':
		{
			EditCoupon();
			key = ERROR;
			system("cls");
			break;
		}
		}//end switch
	}//end while
}

//�����Ż�ȯ
void IssueCoupon(coupon* cpyCoupon)
{
	system("cls");
	char key = ERROR;
	char input[100];
	coupon* theCoupon = NULL;

	if(cpyCoupon==NULL)
	{
		theCoupon = CreatOneCoupon();
	}
	else
	{
		theCoupon = cpyCoupon;
	}

	while (TRUE)
	{
		SetCursorPosition(0, 0);
		memset(input, 0, sizeof(input));

		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n");
		printf("<�����Ż�ȯ>\n");

		printf("���Ż�ȯ��Ϣ��\n");
		PrintOneCoupon(theCoupon);
		printf("\n");

		printf("[ESC]�˳�/ɾ��\n");
		printf("[%c]����\n", ALLRIGHT);
		printf("[1]����\n");
		printf("[2]����\n");
		printf("[3]ʱЧ\n");
		printf("[4]�۸�\n");

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		switch (key)
		{
		case ERROR:break;
		case ESC:
		{
			system("cls");
			printf("ȷ���˳�?\n");
			printf("����ʧ������������\n");
			printf("[y/n]");
			InputBox(input, 1, MODE_KEY, ON);
			if (input[0] != 'y')
			{
				key = ERROR;
				system("cls");
				break;
			}
			DeleteOneCoupon(theCoupon);
			return;
		}
		case ALLRIGHT:
		{
			system("cls");
			if (strlen(theCoupon->content) == 0
				|| theCoupon->rate <= 0.0
				|| theCoupon->rate >= 1.0
				|| theCoupon->timeLimit <= 0
				|| theCoupon->cost < 0)
			{
				printf("������������������ԣ�\n");
				key = ERROR;
				system("pause");
				system("cls");
				break;
			}
			PrintOneCoupon(theCoupon);
			printf("ȷ������/���·��У�\n[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key != 'y')
			{
				key = ERROR;
				system("cls");
				break;
			}
			AddCoupon(chead, theCoupon);
			printf("���гɹ���\n��������˳�\n");
			PrintOneCoupon(theCoupon);
			printf("\n");
			system("pause");
			system("cls");
			return;
		}
		case '1':
		{
			system("cls");
			printf("[ESC]����\n");
			printf("�����ݣ�%s", theCoupon->content);
			printf("\n�����ݣ�");
			InputBox(input, MAX_COUPON, MODE_SHOW, ON);
			if (input[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			strcpy(theCoupon->content, input);
			key = ERROR;
			system("cls");
			break;
		}
		case '2':
		{
			system("cls");
			printf("[ESC]����\n");
			printf("�ɱ��ʣ�%f", theCoupon->rate);
			printf("\n�±��ʣ�");
			InputBox(input, 4, MODE_NUM, ON);
			if (input[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			theCoupon->rate = atof(input);
			key = ERROR;
			system("cls");
			break;
		}
		case '3':
		{
			system("cls");
			printf("[ESC]����\n");
			printf("��ʱЧ����λ:��)��%d", theCoupon->timeLimit);
			printf("\n��ʱЧ����λ:��)��");
			InputBox(input, 4, MODE_NUM, ON);
			if (input[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			theCoupon->timeLimit = atof(input);
			key = ERROR;
			system("cls");
			break;
		}
		case '4':
		{
			system("cls");
			printf("[ESC]����\n");
			printf("�ɼ۸�%d", theCoupon->cost);
			printf("\n�¼۸�");
			InputBox(input, 4, MODE_NUM, ON);
			if (input[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			theCoupon->cost = atof(input);
			key = ERROR;
			system("cls");
			break;
		}
		}//end switch
	}//end while
}

//�����Ż�ȯ
void EditCoupon() 
{
	system("cls");
	char key = ERROR;
	int i = ERROR;
	coupon* point = chead->next;
	coupon* tmp = NULL;

	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);
		tmp = NULL;
		i = ERROR;

		//����		
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");

		printf("<�༭�ѷ����Ż�ȯģʽ>\n");
		printf("����[ESC]����\n");
		printf("����[a/d]��ҳ\n");
		printf("����[1 2 3 4 5]ѡ��\n\n");

		//��ȫ���
		if (chead->next == NULL)
		{
			printf("�޷����Ż�ȯ\n");
			system("pause");
			return;
		}

		//��ӡ
		PrintNumCoupon(point, PAGE_NUM);

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
			break;
		}
		//�˳�
		case ESC:return;
		//��һҳ
		case BUTTON_LEFT:
		{
			tmp = point;
			for (i = 0; i < PAGE_NUM && tmp->prior != NULL; i++)//��ֹ�ߵ�ͷ
			{
				tmp = tmp->prior;
			}
			if (i == PAGE_NUM)//��֤����PAGE_NUM����
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
			for (i = 0; i < PAGE_NUM && tmp->next != NULL; i++)//��ֹ�ߵ�ͷ
			{
				tmp = tmp->next;
			}
			if (i == PAGE_NUM)//��֤����page_num����
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
				IssueCoupon(tmp);
				if (tmp == point)
					point = chead->next;
			}
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		}//end switch

	}//end while
}

//����ѡ��
void SaveOption()
{
	system("cls");
	char key = ERROR;

	while (TRUE)
	{
		//���ó�ʼ��key
		//��Ҫ������дcls
		SetCursorPosition(0, 0);

		//������
		//ʱ��
		printf("<�û�������>\n");
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n");

		printf("[ESC]����\n");
		printf("[1]�ֶ�����\n");
		printf("[2]���ݼ����趨\n");
		printf("[3]��ʷ�����趨\n");

		//��ʱ����ʶ��
		if (_kbhit())//��ֹʱ��ͣ��
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		switch (key)
		{
		case ERROR:break;
		case ESC:return;
		case '1':
		{
			system("cls");
			if (!SaveAll())
			{
				printf("\n�������ݳ���\n");
				system("pause");
			}
			key = ERROR;
			system("cls");
			break;
		}
		case '2':
		{
			system("cls");
			char TF[5];
			TFtoStr(TF, cyrTag);
			printf("��ǰ���ݼ���״̬��%s\n", TF);
			printf("����(1Ϊ���ܣ�0Ϊ�Ǽ���)");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (key == '0')cyrTag = DECYR;
			if (key == '1')cyrTag = CYR;

			key = '2';
			break;
		}
		case '3':
		{
			system("cls");
			char TF[5];
			TFtoStr(TF, hisCyrTag);
			printf("��ǰ��ʷ����״̬��%s\n", TF);
			printf("����(1Ϊ���ܣ�0Ϊ�Ǽ���)");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (key == '0')
			{
				DecyrHis();//���̽���
				hisCyrTag = DECYR;
			}
			if (key == '1')
			{
				CyrHis();//���̼���
				hisCyrTag = CYR;
			}

			key = '3';
			break;
		}
		}
	}
}

//��������״̬
void GoThroughPackage()
{
	package* point = phead->next;
	while (point != NULL)
	{
		if (point->state == STATE_ERROR)
		{
			message* mess = CreatOneMessage("", IMP_PACKERRO);
			sprintf(mess->content, "�˵���%s��״̬�쳣��", point->id);
			Broadcast(mess, ahead);
			free(mess);
		}
		if (point->state == STATE_STAY_LONG)
		{
			message* mess = CreatOneMessage("", IMP_STAYLONG);
			sprintf(mess->content, "�˵���%s�������ã�", point->id);
			Broadcast(mess, ahead);
			free(mess);
		}

		point = point->next;
	}
}
