//��ȡ��ʷ��¼
	/*
	struct tm data1;
	struct tm data2;
	struct tm* now = GetNowTime();

	data1.tm_year = 2024;
	data1.tm_mon = 1;
	data1.tm_mday = 1;

	data2.tm_year = 2026;
	data2.tm_mon = 12;
	data2.tm_mday = 31;

	//ReadPackHis(&data1, &data2);
	*/

//д����ʷ��¼
	/*
	package* pack = CreatOnePackage();
	strcpy(pack->id, "9876543210");
	strcpy(pack->tele_num, "18319775041");
	strcpy(pack->pack_name, "��¶ŵfumo");

	WritePackHis(pack);

	free(pack);
	*/

//��ʷ��¼�ӽ���
	/*
	InitKey();
	hisCyrTag = CYR;

	struct tm* nowTime = GetNowTime();
	package* pack = CreatOnePackage();
	strcpy(pack->pack_name, "��¶ŵ");
	strcpy(pack->id, "123456");

	WritePackHis(pack);
	ReadPackHis(nowTime, nowTime);

	free(pack);
	*/


//���ܽ��ܲ���
/*
	_mkdir("TestFile");
	const char fileTxt[] = "./TestFile/File.txt";
	FILE* oriFile = fopen(fileTxt, "w");
	fputs("��¶ŵ����ǿ�ģ�\n����Ҳȷʵ��һ��������...\n", oriFile);
	fclose(oriFile);

	InitKey();
	CyrptFile(fileTxt);
	DecyrptFile(fileTxt);
*/


//�ļ�IO ���
/*
	InitSys();

	PrintAllPackage(phead);
	printf("\n");
	PrintAllUser(uhead);
	printf("\n");
	PrintAllMessage(uhead->next->mlist);
	printf("\n");
	PrintAllMessage(uhead->next->next->mlist);
	printf("\n");
	PrintAllMessage(uhead->next->next->next->mlist);

	ExitSys();
*/

//�ļ�IO
/*
	//��ʼ��
	InitConsole();

	//ģ�����ð���
	phead = CreatPackageList();
	package* pack1 = _CreatOnePackage
		("1111111111", "18319775041", "ħ����ŮСԲ�ְ�", STATE_ERROR);
	package* pack2 = _CreatOnePackage
		("2222222222", "18377620980", "BakaFumo��ż", STATE_ERROR);
	package* pack3 = _CreatOnePackage
		("3333333333", "18520429443", "MikuMiku", STATE_ERROR);
	package* pack4 = _CreatOnePackage
		("4444444444", "18319775041", "��ͯ����˿�ְ�", STATE_ERROR);
	package* pack5 = _CreatOnePackage
		("5555555555", "18377620980", "JustFumoFumo", STATE_ERROR);
	package* pack6 = _CreatOnePackage
		("6666666666", "18520429443", "39Music", STATE_ERROR);
	package* pack7 = _CreatOnePackage
		("7777777777", "18319775041", "�ƽ�����", STATE_ERROR);
	package* pack8 = _CreatOnePackage
		("8888888888", "18377620980", "��ˮʱɰ", STATE_ERROR);
	package* pack9 = _CreatOnePackage
		("9999999999", "18520429443", "��������", STATE_ERROR);
	AddOnePackage(phead, pack1);
	AddOnePackage(phead, pack2);
	AddOnePackage(phead, pack3);
	AddOnePackage(phead, pack4);
	AddOnePackage(phead, pack5);
	AddOnePackage(phead, pack6);
	AddOnePackage(phead, pack7);
	AddOnePackage(phead, pack8);
	AddOnePackage(phead, pack9);

	SavePackage();


	ReadPackage();
	PrintAllPackage(phead);

*/

//ģ������
	/*
	//��ʼ��
	InitConsole();

	//ģ�����ð���
	phead = CreatPackageList();
	package* pack1 = _CreatOnePackage("1111111111", "18319775041", "ħ����ŮСԲ�ְ�", STATE_ERROR);
	package* pack2 = _CreatOnePackage("2222222222", "18377620980", "BakaFumo��ż", STATE_ERROR);
	package* pack3 = _CreatOnePackage("3333333333", "18520429443", "MikuMiku", STATE_ERROR);
	package* pack4 = _CreatOnePackage("4444444444", "18319775041", "��ͯ����˿�ְ�", STATE_ERROR);
	package* pack5 = _CreatOnePackage("5555555555", "18377620980", "JustFumoFumo", STATE_ERROR);
	package* pack6 = _CreatOnePackage("6666666666", "18520429443", "39Music", STATE_ERROR);
	package* pack7 = _CreatOnePackage("7777777777", "18319775041", "�ƽ�����", STATE_ERROR);
	package* pack8 = _CreatOnePackage("8888888888", "18377620980", "��ˮʱɰ", STATE_ERROR);
	package* pack9 = _CreatOnePackage("9999999999", "18520429443", "��������", STATE_ERROR);
	AddOnePackage(phead, pack1);
	AddOnePackage(phead, pack2);
	AddOnePackage(phead, pack3);
	AddOnePackage(phead, pack4);
	AddOnePackage(phead, pack5);
	AddOnePackage(phead, pack6);
	AddOnePackage(phead, pack7);
	AddOnePackage(phead, pack8);
	AddOnePackage(phead, pack9);

	//�����û�
	uhead = CreatUserList();
	user* user1 = _CreatOneUser("V.Reason", "111", "18319775041", NORMAL_USER);
	user* user2 = _CreatOneUser("Vxiaoshan", "222", "18377620980", NORMAL_USER);
	user* user3 = _CreatOneUser("������", "333", "18520429443", NORMAL_USER);
	AddUser(uhead, user1);
	AddUser(uhead, user2);
	AddUser(uhead, user3);

	ahead = CreatUserList();
	user* topAdmin = _CreatOneUser("admin", "141", "141", TOP_ADMIN);
	user* admin = _CreatOneUser("admin", "141", "141", ADMIN);
	AddUser(ahead, topAdmin);
	AddUser(ahead, admin);

	message* mess1 = CreatOneMessage("����֪ͨ1", 5);
	message* mess2 = CreatOneMessage("����֪ͨ2", 5);
	message* mess3 = CreatOneMessage("����֪ͨ3", 5);
	//message* mess4 = CreatOneMessage("����֪ͨ4", 4);
	//message* mess5 = CreatOneMessage("����֪ͨ5", 4);
	//message* mess6 = CreatOneMessage("����֪ͨ6", 4);
	//message* mess7 = CreatOneMessage("����֪ͨ7", 3);
	//message* mess8 = CreatOneMessage("����֪ͨ8", 3);
	//message* mess9 = CreatOneMessage("����֪ͨ9", 3);
	//message* mess10 = CreatOneMessage("����֪ͨ10", 2);
	//message* mess11 = CreatOneMessage("����֪ͨ11", 1);

	AddMessage(admin->mlist, mess1);
	AddMessage(admin->mlist, mess2);
	AddMessage(admin->mlist, mess3);
	//AddMessage(admin->mlist, mess4);
	//AddMessage(admin->mlist, mess5);
	//AddMessage(admin->mlist, mess6);
	//AddMessage(admin->mlist, mess7);
	//AddMessage(admin->mlist, mess8);
	//AddMessage(admin->mlist, mess9);
	//AddMessage(admin->mlist, mess10);
	//AddMessage(admin->mlist, mess11);

	AdminSys(admin, phead, uhead, ahead);

	ExitSys(phead, uhead, ahead);
	*/


//MessageSort���Դ���
/*
	
	message* head = CreatMessageList();
	message* m1 = CreatOneMessage("1", 1);
	message* m2 = CreatOneMessage("2", 2);
	message* m3 = CreatOneMessage("3", 3);
	message* m4 = CreatOneMessage("4", 4);
	message* m5 = CreatOneMessage("5", 5);
	message* m6 = CreatOneMessage("6", 6);
	AddMessage(head, m2);
	AddMessage(head, m6);
	AddMessage(head, m1);
	AddMessage(head, m4);
	AddMessage(head, m3);
	AddMessage(head, m5);

	printf("����ǰ:\n");
	PrintAllMessage(head);
	printf("\n");

	MessageSort(head);

	printf("�����:\n");
	PrintAllMessage(head);
	printf("\n");
*/


//��InputBox�Ĳ���
/*
	
	//char str[50] = { 0 };
	//InputBox(str, 50, SHOW, OFF);

	//while (TRUE)
	//{
	//	char key = ERROR;
	//	InputBox(&key, 1, KEY, ON);
	//	printf("%c\n", key);
	//}

*/


//��½/ע�ắ��������ʾ
/*
user* head = CreatUserList();
user* user0 = CreatOneUser(DEFAULT, DEFAULT, DEFAULT, DEFAULT);
AddUser(head, user0);

user* user1 = NULL;
do
{
	user1 = Login_Register(head);
} while (user1 == NULL);

//����ϵͳ
if (user1->level == ADMIN)
{
	AdminSys(head, user1);
}
else
{
	UserSys(head, user1, user1->level);
}
*/


//��ʼ��
/*
	
	InitConsole();

	//���ð���
	package* phead = CreatPackageList();
	package* pack1 = CreatOnePackage("1111111111", "18319775041", "ħ����ŮСԲ�ְ�", STATUS_WAITING);
	package* pack2 = CreatOnePackage("2222222222", "18377620980", "BakaFumo��ż", STATUS_WAITING);
	package* pack3 = CreatOnePackage("3333333333", "18520429443", "MikuMiku", STATUS_WAITING);
	AddOnePackage(phead, pack1);
	AddOnePackage(phead, pack2);
	AddOnePackage(phead, pack3);

	//�����û�
	user* uhead = CreatUserList();
	user* user1 = CreatOneUser("V.Reason", "111", "18319775041", NORMAL_USER);
	user* user2 = CreatOneUser("Vxiaoshan", "222", "18377620980", NORMAL_USER);
	user* user3 = CreatOneUser("������", "333", "18520429443", NORMAL_USER);
	AddUser(uhead, user1);
	AddUser(uhead, user2);
	AddUser(uhead, user3);

	user* ahead = CreatUserList();
	user* admin = CreatOneUser("admin", "141", "141", ADMIN);
	AddUser(ahead, admin);

	AdminSys(admin,phead,uhead);

	ExitSys(phead, uhead, ahead);


*/


//ȡ���������ʾ��
/*
	while(TRUE)
	{
		char str[20];
		srand(time(NULL));
		const int randomNum = rand() % 10000;
		sprintf(str, "%4d", randomNum);
		printf("%s\n", str);
		Sleep(1000);
	}
*/

//���ܴ���
/*
			//���ܴ���
			//case '4'://������а���
			//{
			//	system("cls");
			//	printf("<������>\n");
			//	printf("����[ESC]����\n");

			//	//Judgeûд�꣬û��д

			//	break;//break switch
			//}

			//case '7'://¼���û� ûд����
			//	system("pause");
			//	printf("<¼���û�>\n");
			//	printf("����[ESC]����\n");
			//	printf("��������д�������ݣ�\n");

			//	user* user = CreatOneUser(DEFAULT, DEFAULT, DEFAULT, DEFAULT);//�����հ��û�

			//	if (EnterUser(user) == FALSE)
			//	{
			//		//ʧ�ܴ���
			//		key = ERROR;//����
			//		free(pack);
			//		system("cls");
			//		continue;
			//	}
			//	//�ɹ�����

			//	break;//break switch
*/


//���ϴ���1
/*

	//��ʼ��SDL    ��Ƶ��ϵͳ        �¼���ϵͳ
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)<0)
	{
		//ʧ�ܼ��
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return -1;
	}
	if (IMG_Init(IMG_INIT_JPG) == FALSE)
	{
		//ʧ�ܼ��
		SDL_Log("IMG_Init failed: %s", IMG_GetError());
		return -1;
	}

	//����������->������ʾ���ɵ���С
	SDL_Window* mainWindow = SDL_CreateWindow(
		WINDOWS_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOWS_WIDTH, WINDOWS_LENTH,
		SDL_WINDOW_RESIZABLE);
	if (mainWindow == NULL)
	{
		//ʧ�ܼ��
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
		return -1;
	}

	//��ɫ


	//�¼�����/��Ϣѭ�� event_loop
	SDL_Event event;
	int flag = TRUE;//������Ϣѭ���������
	while (flag)
	{
		if (SDL_PollEvent(&event)) //Poll������  wait����
		{
			switch (event.type)
			{
			case SDL_QUIT:
				flag = FALSE;
				break;
			default:
				break;
			}
		}
	}

	//����
	SDL_DestroyWindow(mainWindow);
	//�˳�SDL
	IMG_Quit();
	SDL_Quit();

*/


//���ϴ���2
/*
//�����쳣����
//typedef enum packageError
//{
//	p_id_ERROR			= 0x00000001u,
//	p_tele_ERROR		= 0x00000010u,
//	p_pack_name_ERROR	= 0x00000020u,
//	p_location_ERROR	= 0x00000200u,
//	p_user_name_ERROR	= 0x00001000u,
//	p_sender_name_ERROR	= 0x00002000u,
//	p_user_addr_ERROR	= 0x00004000u,
//	p_sender_addr_ERROR	= 0x00008000u,
//	p_bill_ERROR		= 0x00100000u,
//	p_weight_ERROR		= 0x00200000u,
//	p_size_ERROR		= 0x00400000u,
//	p_area_ERROR		= 0x00800000u,
//	p_fragile_ERROR		= 0x01000000u,
//	p_valuable_ERROR	= 0x02000000u,
//	p_time_ERROR		= 0x04000000u,
//	p_state_ERROR		= 0x08000000u,
//
//	p_point_ERROR		= 0x10000000u,
//	//p_sender_ERROR		= 0x20000000u,
//	//p_prior_ERROR		= 0x40000000u,
//	//p_next_ERROR		= 0x80000000u
//}packageError;
//
////�û��쳣����
//typedef enum userError
//{
//	u_level_ERROR			= 0x00000001u,
//	u_name_ERROR			= 0x00000010u,
//	u_password_ERROR		= 0x00000020u,
//	u_tele_ERROR			= 0x00000200u,
//	u_addr_default_ERROR	= 0x00001000u,
//	u_addr_1_ERROR			= 0x00002000u,
//	u_addr_2_ERROR			= 0x00004000u,
//	u_addr_3_ERROR			= 0x00008000u,
//
//	u_point_ERROR			= 0x00100000u,
//	//u_prior_ERROR			= 0x00200000u,
//	//u_next_ERROR			= 0x00400000u,
//}userError;
//
////֪ͨ�쳣����
//typedef enum messageError
//{
//	m_content_ERROR		= 0x00000001u,
//	m_important_ERROR	= 0x00000010u,
//
//	m_point_ERROR		= 0x00000020u,
//	//m_next_ERROR		= 0x00000200u,
//}messageError;
*/


//���ϴ���3
/*
////SDL2  ע����2������ ��2������
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
*/


//���ϴ���4
/*
////���ں�
//#define WINDOWS_TITLE "404 Staion System"
//#define WINDOWS_WIDTH 1920
//#define WINDOWS_LENTH 1080
*/


//���ϴ���5
/*
	//if (id != (char*)DEFAULT)
	//{
	//	strcpy(pack->id, id);
	//}
	//if (tele_num != (char*)DEFAULT)
	//{
	//	strcpy(pack->tele_num, tele_num);
	//}
	//if (pack_name != (char*)DEFAULT)
	//{
	//	strcpy(pack->pack_name, pack_name);
	//}
	//if (state != DEFAULT)
	//{
	//	pack->state = state;
	//}
*/


//���ϴ���6
/*
//�жϵ������������Ƿ�Ϸ�
void JudgePackage(package* pack) {
	//int error = NO_ERROR;
	////�˵���
	//if (strlen(pack->id) != MAX_ID || isdigit(pack->id) != FALSE)
	//{
	//	error |= p_id_ERROR;
	//}
	////�ֻ���
	//if (strlen(pack->tele_num) != MAX_TELE_NUM || isdigit(pack->tele_num) != FALSE)
	//{
	//	error |= p_tele_ERROR;
	//}

	////��������->������

	////����״̬
	//if (pack->state == STATE_EXCEPTION || pack->state == STATE_STAY_LONG)
	//{
	//	error |= p_state_ERROR;
	//}


	////��ŵص�
	//if (strlen(pack->location) != MAX_LOCATION)
	//{
	//	error |= p_location_ERROR;
	//}

	////ָ��
	//if (!(pack->owner && pack->sender && pack->prior && pack->next))
	//{
	//	error |= p_point_ERROR;
	//}

	////�ռ���/��ַ->������
	////�ļ���/��ַ->������
	//
	////�˷�
	//if (pack->Bill < 0)
	//{
	//	error |= p_bill_ERROR;
	//}

	////����
	//if (pack->weight < 0)
	//{
	//	error |= p_weight_ERROR;
	//}

	////���
	//if (pack->size < 0)
	//{
	//	error |= p_size_ERROR;
	//}



	//���ܴ���
	////ƫԶ����
	//if (pack->isRemoteArea > 1)
	//{
	//	error |= p_area_ERROR;
	//}

	////����Ʒ
	//if (pack->isFragile > 1)
	//{
	//	error |= p_fragile_ERROR;
	//}

	////������Ʒ
	//if (pack->isValuable > 1)
	//{
	//	error |= p_valuable_ERROR;
	//}

}
*/

//���ϴ���7
/*
//����״̬
typedef enum packageState
{
	STATE_EXCEPTION		= 0,   // �쳣
	STATE_WAITING			= 1,   // ��ȡ
	STATE_WAITING_PROCESS	= 2,   // ������
	STATE_RECEIVED			= 3,   // ��ȡ
	STATE_IN_TRANSIT		= 4,   // ��;
	STATE_STAY_LONG		= 5    // ����ʱ�����
}packageState;

*/

//���ϴ���8
/*
		//�޸��˵���
		case 'w':
		{
			printf("���˵���:");
			InputBox(input, MAX_ID, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0
				|| strlen(input) != MAX_ID
				|| (!isAllDigits(input)))
			{
				//����
				printf("\n�޸�ʧ��...\n");//��֪��Ϊɶ��һ���ֲ���ʾ
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\nȷ���޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n��ȡ���޸�\n");
				system("pause");
				key = ERROR;
				system("cls");
			}
			memcpy(pack->id, input, MAX_ID);
			//junge()
			printf("\n���˵����޸ĳɹ�!\n");
			system("pause");
			key = ERROR;
			system("cls");

			break;//break switch
		}

*/

//���ϴ���9
/*
		//�޸İ�������
		case '3':
		{
			printf("�°�������:");
			InputBox(input, MAX_PACK_NAME, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0)
			{
				//����
				printf("\n�޸�ʧ��...\n");//��֪��Ϊɶ��һ���ֲ���ʾ
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\nȷ���޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n��ȡ���޸�\n");
				system("pause");
				key = ERROR;
				system("cls");
			}
			memcpy(pack->pack_name, input, MAX_PACK_NAME);
			//junge()
			printf("\n�°��������޸ĳɹ�!\n");
			system("pause");
			key = ERROR;
			system("cls");

			break;//break switch
		}

*/

//���ϴ���10
/*
		case '2':
		{
			printf("���ֻ���:");
			InputBox(input, MAX_TELE_NUM, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0
				|| strlen(input) != MAX_TELE_NUM
				|| (!isAllDigits(input)))
			{
				//����
				printf("\n�޸�ʧ��...\n");//��֪��Ϊɶ��һ���ֲ���ʾ
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\nȷ���޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n��ȡ���޸�\n");
				system("pause");
				key = ERROR;
				system("cls");
			}
			memcpy(pack->tele_num, input, MAX_TELE_NUM);
			//junge()
			printf("\n���ֻ����޸ĳɹ�!\n");
			system("pause");
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//�޸��ռ�������
		case '3':
		{
			printf("���ռ�������:");
			InputBox(input, MAX_USER_NAME, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0)
			{
				//����
				printf("\n�޸�ʧ��...\n");//��֪��Ϊɶ��һ���ֲ���ʾ
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\nȷ���޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n��ȡ���޸�\n");
				system("pause");
				//����
				key = ERROR;
				system("cls");
			}
			memcpy(pack->user_name, input, MAX_USER_NAME);
			printf("\n���ռ��������޸ĳɹ�!\n");
			system("pause");
			//����
			key = ERROR;
			system("cls");
		}
		//�޸ļļ�������
		case '4':
		{
			printf("�¼ļ�������:");
			InputBox(input, MAX_USER_NAME, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0)
			{
				//����
				printf("\n�޸�ʧ��...\n");//��֪��Ϊɶ��һ���ֲ���ʾ
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\nȷ���޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n��ȡ���޸�\n");
				system("pause");
				//����
				key = ERROR;
				system("cls");
			}
			memcpy(pack->sender_name, input, MAX_USER_NAME);
			printf("\n�¼ļ��������޸ĳɹ�!\n");
			system("pause");
			//����
			key = ERROR;
			system("cls");
		}
		//�޸��ռ��˵�ַ
		case '5':
		{
			printf("���ռ��˵�ַ:");
			InputBox(input, MAX_ADDRESS, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0)
			{
				//����
				printf("\n�޸�ʧ��...\n");//��֪��Ϊɶ��һ���ֲ���ʾ
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\nȷ���޸ģ�\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n��ȡ���޸�\n");
				system("pause");
				//����
				key = ERROR;
				system("cls");
			}
			memcpy(pack->user_address, input, MAX_USER_NAME);
			printf("\n�¼ļ��������޸ĳɹ�!\n");
			system("pause");
			//����
			key = ERROR;
			system("cls");
		}

*/

//���ϴ���11
/*
//�޸��û���Ϣ ����DEFAULT��ʾ���޸�
void ModifyUser(user* _user, char* name, char* password, char* tele_num, int level)
{
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
}
*/

//���ϴ���12
/*
//���ҵ绰����
typedef struct countryCode {
	char code[4];       // ���Ҵ��루Ĭ��Ϊ"+86"��
	char country[20];   // ��������
}countryCode;
//���Ҵ����
countryCode countryCodes[] =
{
	{"+86", "China"},			//�й�
	{"+1", "United States"},	//����
	{"+81", "Japan"},			//�ձ�
	{"+82", "South Korea"},		//����
	{"+44", "United Kingdom"},  //Ӣ��
	{"+33", "France"},			//����
	{"+49", "Germany"},			//�¹�
	{"+91", "India"},			//ӡ��
	{"+7", "Russia"},			//���
	{"+55", "Brazil"},			//����
	{"+61", "Australia"},		//�Ĵ�����
	{"+65", "Singapore"},		//�¼���
	{"+27", "South Africa"},	//�Ϸ�
	{"+52", "Mexico"},			//ī����
};
//���Ҵ����ĳ���
const int numCountryCodes = sizeof(countryCodes) / sizeof(countryCodes[0]);
*/

//���ϴ���13
/*
// ��ȡ�û��ļ�
void FileReadUser(user* head) {
	// ���ļ�
	FILE* file = fopen("SAMPLE_FILE_NAME ", "r");
	if (file == NULL) {
		perror("File not found");
		return;
	}
	user* puser = head;

	// ��ȡ����
	while (1) {

		if (feof(file)) {
			printf("�ļ���ȡ���\n");
			break;
		}

		puser->next = (user*)malloc(sizeof(user));
		puser->next->prior = puser;
		puser->next->next = NULL;
		puser = puser->next;

		int i = fscanf(file, "%s %s %s %d",
			puser->name, puser->password, puser->tele_num, &puser->level);

		if (i != 4) {                             // ���ݲ�����
			printf("���ݲ���������࣬���޸ĺ����¶�ȡ\n");
			puser->prior->next = NULL;
			free(puser);    // �ඨ��һ���ṹ�壬�ͷŵ�
			break;
		}
		if (JudgeUser(puser) == FALSE) {               // ���ݲ��Ϸ�
			printf("���ݲ��Ϸ������޸ĺ����¶�ȡ\n");
			puser->prior->next = NULL;
			free(puser);    // �ඨ��һ���ṹ�壬�ͷŵ�
			break;
		}

	}

	fclose(file);
}
*/

//���ϴ���14
/*
�ж������Ƿ�Ϸ�  //ûд��
int JudgeUser(user* puser)
{
	if (strlen(puser->password) != MAX_PASSWORD_NUM) {
		printf("password���Ȳ��Ϸ�\n");
		return FALSE;
	}
	if (strlen(puser->name) > MAX_PACK_NAME) {
		printf("name���Ȳ��Ϸ�\n");
		return FALSE;
	}
	if (strlen(puser->tele_num) != MAX_TELE_NUM) {
		printf("tele_num���Ȳ��Ϸ�\n");
		return FALSE;
	}
	if (puser->level < 0 || 5 < puser->level) {
		printf("level���Ϸ�\n");
		return FALSE;
	}
	return TRUE;
}
*/

//���ϴ���15
/*
//�����û���Ϣ��txt�ļ�
void SaveUser(user* head) {
	FILE* file = fopen("SAMPLE_FILE_NAME ", "w");
	if (file == NULL) {
		perror("File not found");
		return;
	}
	user* puser = head->next;
	while (puser != NULL) {
		fprintf(file, "%s %s %s %d %p %p\n", puser->name, puser->password, puser->tele_num, puser->level, puser->prior, puser->next);
		puser = puser->next;
	}
	fclose(file);
}
// �����������
void SavePackage(package* head) {
	FILE* file = fopen("./samples.txt", "w");
	if (file == NULL) {
		perror("File not found");
		return;
	}
	package* pack = head->next;
	while (pack != NULL) {
		//fprintf(file, "%s %s %s %d %d %d %d %s %s %s %s %d %d %d %p %p %p %p",
		//	pack->id, pack->pack_name, pack->tele_num, (int*)pack->state, pack->Bill, pack->size, pack->weight, pack->user_name, pack->sender, pack->user_address, pack->send_address, pack->isFragile, pack->isRemoteArea, pack->isValuable, pack->owner, pack->sender, pack->prior, pack->next);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				fprintf(file, "%d", pack->time[i][j]);
			}
		}
		pack = pack->next;
	}
	fclose(file);
}
// ��ȡ�����ļ�
/*
void FileReadPackage(package* head) {
	// ���ļ�
	FILE* file = fopen("./samples.txt", "r");
	if (file == NULL) {
		perror("File not found");
		return;
	}
	package* pack = head;

	// ��ȡ����
	while (1) {

		if (feof(file)) {
			printf("�ļ���ȡ���\n");
			break;
		}

		pack->next = (package*)malloc(sizeof(package));
		pack->next->prior = pack;
		pack->next->next = NULL;
		pack = pack->next;

		int x = fscanf(file, "%s %s %s %d %d %d %d %s %s %s %s %d %d% %d %p %p %p %p",
			pack->id, pack->pack_name, pack->tele_num, (int*)&pack->state, &pack->Bill, &pack->size, &pack->weight, pack->user_name, pack->sender, pack->user_address, pack->send_address, &pack->isFragile, &pack->isRemoteArea, &pack->isValuable, pack->owner, pack->sender, pack->prior, pack->next);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				int y = fscanf(file, "%d", pack->time[i][j]);
				if (y != 1) {
					printf("ʱ�����ݲ�����\n");
					pack->prior->next = NULL;
					free(pack);    // �ඨ��һ���ṹ�壬�ͷŵ�
					break;
				}
			}
		}

		if (x != 14) {                             // ���ݲ�����
			printf("���ݲ���������࣬���޸ĺ����¶�ȡ\n");
			pack->prior->next = NULL;
			free(pack);    // �ඨ��һ���ṹ�壬�ͷŵ�
			break;
		}
		if (JudgePackage(pack) == FALSE) {               // ���ݲ��Ϸ�
			printf("���ݲ��Ϸ������޸ĺ����¶�ȡ\n");
			pack->prior->next = NULL;
			free(pack);    // �ඨ��һ���ṹ�壬�ͷŵ�
			break;
		}

	}

	fclose(file);
}
// ��ȡ֪ͨ��Ϣ
void FileReadMessage(message* head) {
	FILE* file = fopen("MESSAGE_FILE_NAME", "r");
	if (file == NULL) {
		perror("File not found");
		return;
	}
	message* pmessage = head;
	// ��ȡ����
	while (TRUE) {
		if (feof(file)) {
			printf("�ļ���ȡ���\n");
			break;
		}
		pmessage->next = (message*)malloc(sizeof(message));
		pmessage->next->prior = pmessage;
		pmessage->next->next = NULL;
		pmessage = pmessage->next;
		int i = fscanf(file, "%s %d", pmessage->content, &pmessage->important);
		if (i != 2) {                             // ���ݲ�����
			printf("���ݲ���������࣬���޸ĺ����¶�ȡ\n");
			pmessage->prior->next = NULL;
			free(pmessage);    // �ඨ��һ���ṹ�壬�ͷŵ�
			break;
		}
	}
	fclose(file);
}


*/

//���ϴ���16
/*
	//��֧-���
	while (mode == LOGIN)//������ע�����Ա
	{
		SetCursorPosition(0, 0);
		printf("��ǰʱ�䣺");
		PrintNowTime();
		printf("\n");

		printf("��ѡ���������\n");
		printf("[ESC]����\n");
		printf("[%c]����Ա\n", ADMIN);
		printf("[%c]�û�\n", USER);
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
			break;//break switch
		}
		//�˳�ϵͳ
		case ESC:
		{
			return NULL;//���÷���ֵ��������
		}
		case ADMIN:
		case USER:
		{
			temLevel = key - '0';
			break;//break switch
		}
		}//end switch
		if (temLevel == ADMIN || temLevel == USER)
			break;//break while
	}//end while

	//�����˺�
	while (TRUE)
	{
		system("cls");
		printf("����\'r\'���¿�ʼ.\n");
		printf("�����������˺ţ�\n");
		InputBox(account, MAX_USER_NAME, MODE_SHOW, OFF);

		if (strcmp(_RETRY, account) == 0)
			return NULL;

		if (mode == REGISTER)
			break;

		temUser = FindUser(head, account);
		if (temUser == NULL)
		{
			printf("�˺��������򲻴��ڣ������������롣\n");
			system("pause");
		}
	}

	while (TRUE)
	{
		printf("\n����\'r\'���¿�ʼ.\n");
		printf("�������������룺\n");
		InputBox(password1, MAX_PASSWORD_NUM, MODE_PASSWORD, OFF);

		if (strcmp(_RETRY, account) == 0)
			return NULL;

		if (mode == LOGIN)
		{
			if (strcmp(password1, temUser->password) == 0)
			{
				printf("��¼�ɹ���\n");
				system("pause");
				return temUser;
			}
			else
			{
				printf("������������������롣\n");
				system("pause");
			}
		}
		if (mode == REGISTER)
		{
			printf("\n����\'r\'���¿�ʼ.\n");
			printf("���ٴ������������룺\n");
			InputBox(password2, MAX_PASSWORD_NUM, MODE_PASSWORD, OFF);

			if (strcmp(_RETRY, account) == 0)
				return NULL;

			if (strcmp(password1, password2) != 0)
			{
				printf("��������������벻һ�£�������ȷ�ϣ�\n");     //����������ʱ������
			}
			else
			{
				printf("\n��ϲ��ע��ɹ���\n");
				temUser = CreatOneUser(account, password1, DEFAULT, (int)(temLevel - '0'));
				AddUser(head, temUser);
				system("pause");
				return temUser;
			}
		}
	}
*/

//���ϴ���17
/*
	const int inTime
		= GetDaysFromStartOfYear
		(pack->time[IN][YEAR], pack->time[IN][MON], pack->time[IN][DAY]);
	const int nowTime
		= GetDaysFromStartOfYear
		(ptime->tm_year, ptime->tm_mon, ptime->tm_mday);
	//������������Ĳ�ֵ
	int days = 0;
	if (pack->time[IN][YEAR] == pack->time[OUT][YEAR])//��ͬ��ݽ����
	{
		days = nowTime - inTime;
	}
	else//��ͬ��ݽ����
	{
		for (int y = pack->time[IN][YEAR]; y < pack->time[OUT][YEAR]; y++)
		{
			days += IsLeapYear(y) ? 366 : 365;
		}
		days += (nowTime - inTime);
	}
*/

//���ϴ���18
/*
//����Ա���Ҷ�������������ҵ��İ�������������õ�headĩβ�����ص�һ���ҵ��İ����ĵ�ַ
package* AdminFindPackage(package* head, char* str)
{
	package* nhead = CreatPackageList();
	int mode = ERROR;

	//ƥ������
	switch (strlen(str))
	{
	case MAX_ID:
		mode = _ID;
		break;
	case MAX_TELE_NUM:
		mode = _TELE;
		break;
	case 1:
		mode = _STATE;
		break;
	default:
		mode = _PACK_NAME;
		break;
	}

	//����
	while (head->next != NULL)//����
	{
		head = head->next;

		int relevance = FALSE;
		char temStateStr[2];
		temStateStr[0] = (head->state + '0');
		temStateStr[1] = '\0';

		switch (mode)//����ƥ��
		{
		case _ID:
			if (strcmp(head->id, str) == 0)
				relevance = TRUE;
			break;
		case _TELE:
			if (strcmp(head->tele_num, str) == 0)
				relevance = TRUE;
			break;
		case _PACK_NAME:
			if (strstr(head->pack_name, str) != NULL)
				relevance = TRUE;
			break;
		case _STATE:
			if (strcmp(temStateStr, str) == 0)
				relevance = TRUE;
			break;
		}

		if (relevance == TRUE)//��ѯ����ж�
		{
			head = head->prior;
			TakeOutOnePackage(nhead, head->next);//ץ������nheadĩβ
		}
	}

	//����head��nhead
	if (nhead->next != NULL)
	{
		AddMultiplePackage(head, nhead);//��pack�䵱head��β��
		//free(nhead); nhead�Ѿ���AddMultiplePackage���ͷ�
		return head->next;
	}
	else//û�в�ѯ������ͷſռ�
	{
		free(nhead);
		return NULL;
	}
}
*/

//���ϴ���19
/*
//��ʼ��coupons[]
void InitCoupons()
{
	memset(coupons, 0, sizeof(coupon) * COUPON_NUM);

	strcpy(coupons[0].content, "���� ������");//3Ԫ
	coupons[0].rate = 0.9;
	coupons[0].timeLimit = 3;
	coupons[0].cost = 3;
	strcpy(coupons[1].content, "������ �ĸ���");//4Ԫ
	coupons[1].rate = 0.95;
	coupons[1].timeLimit = 4;
	coupons[1].cost = 4;
	strcpy(coupons[0].content, "���� �����");//5Ԫ
	coupons[2].rate = 0.8;
	coupons[2].timeLimit = 5;
	coupons[2].cost = 5;
}*/

#pragma endregion