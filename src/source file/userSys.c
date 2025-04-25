#include "Frontend.h"

//�û�����ϵͳ
//1.ȡ�� -> ȡ���� -> �����룿������������Ӿ���
//2.��ѯ -> KEY����ģʽ ��ҳ ѡ��
//3.�ļ� -> ϸ�ڴ���
//4.�걨�쳣 -> ����...
//5.�û���Ϣ�޸� -> ...
void UserSys(user* user)
{
	//��ʼ��
	system("cls");
	char key = ERROR;					//���յ�������
	char search[MAX_SEARCH_LENGTH + 1];	//�����ַ�������
	char complain[MAX_MESSAGE + 1];		//����Ͷ������
	memset(search, 0, sizeof(search));	//����
	package* pack_search = NULL;
	struct tm* lastTime = GetNowTime();	//���ڶ�ʱ
	struct tm* nowTime = GetNowTime();	//���ڶ�ʱ

	//ÿ�յ�½
	if (logoutTime.tm_year != 0
		&& (logoutTime.tm_year != nowTime->tm_year
			|| logoutTime.tm_mon != nowTime->tm_mon
			|| logoutTime.tm_mday != nowTime->tm_mday))
	{
		//��½����
		GainExp(EVENT_SignIn, user);
		//����ף��
		festival* fes = isFestival();
		if (fes != NULL)
		{
			message* mess = CreatOneMessage("", IMP_SPECIAL);
			sprintf(mess->content, "%s ���֣�", fes->name);
			AddMessage(user->mlist, mess);
		}
	}

	while (TRUE)
	{
		//��ʱ����-����+ˢ���Ż�ȯ
		nowTime = GetNowTime();
		if (AutoRegular__TimeSeg_S <= GetTimeSeg_Min(lastTime, nowTime))
		{
			UserRegular(user);
			lastTime = nowTime;
		}

		//���ó�ʼ��key
		//��Ҫ������дcls
		SetCursorPosition(0, 0);
		memset(search, 0, sizeof(search));
		pack_search = NULL;

		//������
		//ʱ��
		printf("<�û�������>\n");
		printf("��ǰʱ�䣺");
		PrintNowTime();
		//�û��ȼ� ����
		printf("\n");
		int nextExp = (user->level + 1) * LEVEL_STEP;
		nextExp = nextExp > MAX_EXP ? nextExp : MAX_EXP;
		printf("�û��ȼ���%d ��	�û����飺%d / %d",
			user->level, user->exp, nextExp);
		//֪ͨ
		printf("\n֪ͨ:\n");
		PrintNumMessage(user->mlist, MESS_NUM);
		printf("\n");
		//����˵��
		printf("���¶�Ӧ������ѡ����...\n\n");

		printf("[ESC]�˳�\n\n");

		printf("����֪ͨ��\n");
		printf("[`]����֪ͨ\n\n");

		printf("[0]�ڹ�\n");
		printf("[1]�Ż�ȯ\n\n");

		printf("[2]���\n");
		printf("[3]ȡ��\n");
		printf("[4]�ļ�\n");
		printf("[5]��ѯ��ʷ����\n\n");

		printf("[6]Ͷ��\n");
		printf("[7]�޸ĸ�����Ϣ\n");
		printf("[8]����ѡ��\n");
		printf("[9]�˳���½\n\n");

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
				RecordLogoutUser(user);
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
			MessSys(user);
			//����
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�ڹ�
		case '0':
		{
			//����д��UserPay������
			UserPay(user);
			key = ERROR;
			system("cls");
			break;
		}
		//�鿴�Ż�ȯ
		case '1':
		{
			CheckCoupon(user);
			key = ERROR;
			system("pause");
			system("cls");
			break;
		}
		//���
		case '2':
		{
			system("cls");
			printf("<���>\n");
			printf("����[ESC]����\n");

			pack_search = UserFindPackage(phead, user);
			if (pack_search != NULL)
			{
				//�ɹ�����
				printf("����[`] ���հ�������\n\n");
				printf("����[�ո�] ˢ��\n\n");

				printf("����ѯ�� %d �����\n", CountPackage(pack_search));
				PrintAllPackage(pack_search);

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
					if (key == ' ')
					{
						key = '1';//����Ϊ��������
						break;
					}
					if (key == '`')
					{
						RejectPackageInterface(pack_search);
						key = ERROR;
						system("cls");
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
		//ȡ��
		case '3':
		{
			system("cls");
			printf("<ȡ��>\n");
			printf("����[ESC]����\n");

			//�����˵���
			printf("�������˵���:");
			InputBox(search, MAX_ID, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				//����
				key = ERROR;
				system("cls");
				break;
			}
			//�жϸ�ʽ
			if (FALSE == JungePackageInformation(ID, search))
			{
				printf("\n������˵��Ÿ�ʽ����������\n");
				system("pause");
				break;
			}
			//�жϴ���
			package* pack = AdminFindPackage(phead, search);
			if (FALSE == pack)
			{
				printf("\n������˵��Ų����ڣ�������\n");
				system("pause");
				break;
			}
			//�ж����
			if (pack->state != STATE_WAIT_PICK)
			{
				printf("\n������δ��⣬�����ĵȴ���\n");
				system("pause");
				system("cls");
				break;
			}
			//����ȡ����
			memset(search, 0, sizeof(search));
			printf("������ȡ����:");
			InputBox(search, MAX_PICKUP_CODE, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				//����
				key = ERROR;
				system("cls");
				break;
			}
			//�ж�ȡ����
			if (0 != strcmp(search, pack->pickupCode))
			{
				printf("\nȡ�����������,������\n");
				system("pause");
				system("cls");
				break;
			}
			//ȡ���ֻ�������
			strcpy(pack->pick_tele_num, user->tele_num);
			//�˶�ȡ���ֻ���-��֪ͨԭ����
			if (strcmp(pack->tele_num, user->tele_num) != 0)
			{
				_User* oriUser = FindUser(uhead, pack->tele_num);
				if (oriUser != NULL)
				{
					message* mess = CreatOneMessage("", IMP_SPECIAL);
					sprintf(mess->content, "��İ���(%s)���ֻ���β��%s���û���ȡ��",
						pack->pack_name, &(user->tele_num[MAX_TELE_NUM - 4]));
					AddMessage(oriUser->mlist, mess);
				}
			}
			//ȡ���ɹ�
			GetShelf(pack);
			DeleteOnePackage(pack);
			printf("\nȡ���ɹ�!\n");
			system("pause");
			//����
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//�ļ�
		case '4':
		{
			system("cls");
			printf("<�ļ�>\n");
			printf("����[ESC]����\n");
			printf("��������д�������ݣ�\n");

			package* pack = CreatOnePackage();//�����հװ���

			if (SendPackage(user, pack) == FALSE)//������Ϣ
			{
				//ʧ�ܴ���
				key = ERROR;//����
				free(pack);//ɾ���հװ���
				system("cls");
				break;
			}
			//�ɹ�����
			AddOnePackage(phead, pack); //��������
			GainExp(EVENT_SendPack, user);//��þ���
			printf("\n�ļ��ɹ���\n");
			PrintOnePackage(pack); //����ȫ����Ϣ

			system("pause");//��Ĭ�ȴ�
			system("cls");

			break;//break switch
		}
		//��ѯ��ʷ����
		case '5':
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
		//Ͷ��
		case '6':
		{
			system("cls");
			printf("[ESC]����\n");
			printf("������Ͷ������(%d������)��", MAX_MESSAGE - 50);
			InputBox(complain, MAX_MESSAGE - 50, MODE_SHOW, ON);
			if (complain[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			printf("\nȷ��Ͷ����\n[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key == 'y')
			{
				message* mess = CreatOneMessage("", IMP_USER);
				sprintf(mess->content, "�û�[%s]Ͷ��:%s", user->name, complain);
				Broadcast(mess, ahead);
				free(mess);
				printf("Ͷ�߳ɹ���\n");
				key = ERROR;
				system("pause");
				system("cls");
				break;
			}
			printf("��ȡ��Ͷ�ߣ�\n");
			key = ERROR;
			system("pause");
			system("cls");
			break;
		}
		//�û�������Ϣ�޸�
		case '7':
		{
			system("cls");
			printf("<�޸ĸ�����Ϣ>\n");
			printf("����[ESC]����\n");
			PrintOneUser(user);
			printf("\n�Ƿ�Ҫ�޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				if (RESTART == ModifyUserInterface(user))
				{
					return RESTART;
				}
			}
			else
				//����
				key = ERROR;
			system("cls");

			break;//break switch
		}
		//����ѡ��
		case '8':
		{
			SaveOption();
			key = ERROR;
			system("cls");
			break;
		}
		//�˳���½
		case '9':
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

//�û��ʼİ���
int SendPackage(user* user, package* pack)
{
	system("cls");
	if (user == NULL || pack == NULL)
	{
		printf("�Ƿ�������NULLָ�룡(ModifyPackage)\n");
		system("pause");
	}

	//׼������
	char key = ERROR;
	//��ǰ����
	AssignId(pack);//�˵���
	pack->state = STATE_WAIT_COLLECT;//״̬->������
	strcpy(pack->tele_num, user->tele_num);//�ֻ���
	strcpy(pack->sender_name, user->name);//�ļ�������
	strcpy(pack->send_address, user->address_default);//�ļ��˵�ַ


	//��Ϣѭ��
	while (TRUE)
	{
		//��������key
		SetCursorPosition(0, 0);

		//����
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n\n");
		printf("<�ļ�>\n");
		PrintOnePackage(pack);

		printf("\n�������°���ѡ��༭\n");
		printf("[ESC]�˳�\n");
		printf("[%c]ȷ��¼�����(�˷ѽ��Զ�����)\n", ALLRIGHT);
		printf("[%c]��д����\n", RULE);
		printf("[%c]�˷Ѽ������\n\n", PAY_RULE);

		//¼��ģʽ����
		//printf("[%c]�˵���\n", ID);
		printf("[%c]��������\n", PACK_NAME);
		//printf("[%c]��ŵص�(ѡ��)\n", LOCATION);
		//printf("[%c]ȡ����(ѡ��)\n", PICKCODE);
		//

		//printf("[%c]����״̬\n\n", STATE);

		printf("[%c]�ֻ���\n", TELE);
		printf("[%c]�ռ�������\n", USER);
		printf("[%c]�ļ�������\n", SENDER);
		printf("[%c]�ռ��˵�ַ\n", USER_ADDR);
		printf("[%c]�ļ��˵�ַ\n\n", SENDER_ADDR);

		//printf("[%c]�˷�\n", BILL);
		printf("[%c]����\n", WEIGHT);
		printf("[%c]���\n", SIZE);
		printf("[%c]ƫԶ����\n", FAR_AREA);
		printf("[%c]����Ʒ\n", FRAG);
		printf("[%c]����Ʒ\n", VALU);
		printf("[%c]�ͻ�����\n\n", TODOOR);

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
				char weight[20];
				char size[20];
				memset(weight, 0, 20);
				memset(size, 0, 20);
				sprintf(weight, "%f", pack->weight);
				sprintf(size, "%f", pack->size);
				if (JungePackageInformation(ID, pack->id)
					&& JungePackageInformation(TELE, pack->tele_num)
					&& JungePackageInformation(PACK_NAME, pack->pack_name)
					&& JungePackageInformation(USER, pack->user_name)
					&& JungePackageInformation(SENDER, pack->sender_name)
					&& JungePackageInformation(USER_ADDR, pack->user_address)
					&& JungePackageInformation(SENDER_ADDR, pack->send_address)
					//&& JungePackageInformation(BILL, bill) �˷Ѻ�����
					&& JungePackageInformation(WEIGHT, weight)
					&& JungePackageInformation(SIZE, size)
					&& JungePackageInformation(FAR_AREA, &(pack->isRemoteArea))
					&& JungePackageInformation(FRAG, &(pack->isFragile))
					&& JungePackageInformation(VALU, &(pack->isValuable))
					)
				{
					//�����˷�
					pack->Bill = CalculateBill(user, pack);
					system("cls");
					printf("����Ҫ֧�� %f Ԫ�˷�\n", pack->Bill);
					printf("�Ƿ�֧����\n");
					printf("[y/n]\n");
					InputBox(&key, 1, MODE_KEY, OFF);
					if (key != 'y')
					{
						printf("ȡ��֧����...\n");
						printf("���ڷ���...\n");
						//����
						key = ERROR;
						break;//break switch
						system("pause");
					}
					fund += pack->Bill;
					printf("�ɹ�֧��!\n");
					printf("���ڷ���...\n");
					system("pause");
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
				totalId--;
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
		//����˷Ѽ������
		case PAY_RULE:
		{
			system("cls");
			PrintBillSchedule();
			system("pause");//��Ĭ�ȴ�
			//����
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//¼��ģʽ����
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
		//��������

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
		//�ͻ�����
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

//�û������Ż�ȯ
void CheckCoupon(user* user)
{
	RefreshCoupon(user->clist);

	system("cls");
	char key = ERROR;
	int i = ERROR;
	coupon* point = user->clist->next;
	coupon* tmp = NULL;

	if (user->clist->next == NULL)
	{
		printf("û���κ��Ż�ȯ......\n");
		system("pause");
		return;
	}

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

		printf("<�鿴�Ż�ȯģʽ>\n");
		printf("����[ESC]����\n");
		printf("����[a/d]��ҳ\n");
		printf("����[1 2 3 4 5]ѡ��\n\n");

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
			//{
			//	system("cls");
			//	printf("�˳��༭��\n [y/n]\n");
			//	InputBox(&key, 1, MODE_KEY, OFF);
			//	if (key == 'y')
			//	{
			//		return;
			//	}
			//	else
			//	{
			//		key = ERROR;
			//		system("cls");
			//	}

			//	break;//break switch
			//}
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
				system("cls");
				PrintOneCoupon(tmp);
				printf("\nȷ��ʹ����\n");
				printf("[y/n]\n");
				InputBox(&key, 1, MODE_KEY, ON);
				if (key != 'y')
				{
					//����
					key = ERROR;
					system("cls");
					break;//break switch
				}
				if (TRUE == UseCoupon(tmp))
				{
					printf("�ɹ����ã�\n");
					system("pause");
				}
				else//FALSE
				{
					printf("�޷��ظ����ã�\n");
					system("pause");
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

//��ʱ��ɺ�Ĳ�������
void UserRegular(user* user)
{
	//��ʱˢ���Ż�ȯ
	RefreshCoupon(user->clist);
	//��ʱ����
	SaveAll();
}

//����Ա�̶�ʱ��ɺ�Ĳ�������
void AdminRegular_S(user* user)
{
	//��ʱ����
	SaveAll();
}

//����Ա����ʱ��ɺ�Ĳ�������
void AdminRegular_L(user* user)
{
	//��������״̬
	GoThroughPackage();
}

//���հ�������
void RejectPackageInterface(package* head)
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

		printf("<���հ���ģʽ>\n");
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
			{
				if (tmp->state != STATE_WAIT_PICK
					&& tmp->state != STATE_STAY_LONG)
				{
					printf("�޷��Ըð������в���\n");
					key = ERROR;
					system("pause");
					system("cls");
					break;//break switch
				}
				printf("\n�Ƿ���հ�����\n[y/n]");
				InputBox(&key, 1, MODE_KEY, ON);
				if (key == 'y')
				{
					tmp->state = STATE_REJECT;
					message* mess = CreatOneMessage("", IMP_REJECT);
					sprintf(mess->content, "�ֻ���%s�����˰���%s",
						tmp->tele_num, tmp->id);
					Broadcast(mess, ahead);
					free(mess);
					printf("�ɹ����հ���\n");
					system("pause");
				}
				else
				{
					printf("��ȡ�����ղ���\n");
					system("pause");
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