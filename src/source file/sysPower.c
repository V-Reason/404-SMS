#include "Frontend.h"

//��ʼ������
void InitSys()
{
	//��ʼ���ļ���
	InitFile();//��һ�����л��ʼ����������Ա
	//���ÿ���̨
	InitConsole();
	//�����ܳ�
	InitKey();

	//�����û�������Ա����������
	uhead = CreatUserList();	//�û���ͷ
	ahead = CreatUserList();	//����Ա��ͷ
	phead = CreatPackageList();	//������ͷ
	chead = CreatCouponList();	//�Ż�ȯ��ͷ
	if (!ReadAll())
	{
		printf("��ȡ�ļ�����\n");
		exit(1);
	}

	//���û�������
	InitShelf();
}

//���˳����� ������������ �������������
void ExitSys()
{
	//��������
	if (!SaveAll())
	{
		printf("\n�������ݳ���\n");
		system("pause");
		return;
	}
	//�����������
	DeleteAllPackage(phead);
	DeleteAllUser(uhead);
	DeleteAllUser(ahead);

	//exit(0);
}

//��ʼ��txt�ļ�
void InitFile()
{
	FILE* init_file = fopen(Init_File_txt, "r");
	if (init_file != NULL)
	{
		fclose(init_file);
		return;
	}
	printf("��⵽��һ�δ�ϵͳ�����ڳ�ʼ������...\n");

	//�����ļ���
	_mkdir(HIS_FOLDER);
	_mkdir(RES_FOLDER);

	//�����ļ�
	FILE* tem = NULL;
	tem = fopen(Init_File_txt, "w"); 
	fprintf(tem, "%d", cyrTag);
	fclose(tem);
	tem = fopen(His_Init_File_txt, "w"); 
	fprintf(tem, "%d", hisCyrTag);
	fclose(tem);
	tem = fopen(User_File_txt, "w");  fclose(tem);
	tem = fopen(Admin_File_txt, "w");  fclose(tem);
	tem = fopen(Package_File_txt, "w");  fclose(tem);
	//tem = fopen(Shelfs_File_txt, "w"); fclose(tem);
	tem = fopen(TotalId_File_txt, "w"); fclose(tem);
	tem = fopen(Fund_File_txt, "w"); fclose(tem);
	tem = fopen(Coupon_File_txt, "w"); fclose(tem);
	tem = fopen(LogoutTime_File_txt, "w"); fputs("0\n0\n0\n0\n0", tem); fclose(tem);

	//��ʼ����������Ա
	ahead = CreatUserList();
	user* topAdmin = CreatOneUser();
	topAdmin->level = TOP_ADMIN;
	strcpy(topAdmin->name, DEFUALT_TOPADMIN_NAME);
	strcpy(topAdmin->password, DEFUALT_ADMIN_PASSWORD);
	AddUser(ahead, topAdmin);
	SaveUser(Admin_File_txt, ahead);
	DeleteAllUser(ahead);

	printf("��ʼ���ɹ�\n");
	system("pause");
	return;
}

//��ʼ������ �����ڶ�ȡ�����ļ�֮��ִ��
void InitShelf()
{
	//����
	memset(shelfs, 0, sizeof(shelfs));

	//����shelf.location
	for(int num =0;num<SHELF_NUM;num++)
		for(int sub =0;sub<SUB_SHELF_NUM;sub++)
			for(int r=0;r<ROW;r++)
				for (int l = 0; l < LINE; l++)
				{
					char location[MAX_LOCATION + 1];
					sprintf(location, "%c%d_%d,%d", num + 'A', sub, r, l);
					strcpy(shelfs[num][sub][r][l].location, location);
				}

	//����phead
	package* point = phead->next;
	while (point != NULL)
	{
		//����Ƿ����
		shelf* theShelf = StrToShelf(point->location);
		if (theShelf != NULL)
		{
			theShelf->used = TRUE;
			strcpy(theShelf->pack_id, point->id);
		}
		//����
		point = point->next;
	}
}

//��ʼ������̨
void InitConsole()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	//����fontInfo
	fontInfo.cbSize = sizeof(fontInfo); // �ṹ��Ĵ�С
	fontInfo.nFont = 0; // ϵͳ����̨����������������
	fontInfo.dwFontSize.X = 0;  // �ָ�
	fontInfo.dwFontSize.Y = 20; // �ֿ�
	fontInfo.FontFamily = FF_DONTCARE; // �������ϵ��
	fontInfo.FontWeight = FW_NORMAL; // ��ϸ
	wcscpy_s(fontInfo.FaceName, sizeof(L"Consolas"), L"Consolas"); // ����������

	SetCurrentConsoleFontEx(ConsoleHandle, FALSE, &fontInfo); //��������
	SetConsoleTitle(TITLE);  //���ô��ڱ���
	SetConsoleOutputCP(GBK); //���ת��GBK
	SetConsoleCP(GBK);		 //����ת��GBK ->������Ӧ��������
	system("color 07");      //�ڵװ���

	//�ı䴰�ڴ�С����Ҫ����ԱȨ�ޣ�������
	//char cmd[255];
	//for (int i = 0; i < 255; i++)
	//	cmd[i] = 0;
	//sprintf(cmd, "mode con cols=%d lines=%d",
	//	50, 50);
	//system(cmd);

	//���ô��ڴ�С �� ��������С (û�ɹ����о��У�
	//ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SMALL_RECT wrt = { 0,0,50,50};
	//int junge = SetConsoleWindowInfo(ConsoleHandle, FALSE, &wrt);
	//COORD coord = { WIDTH + 50,HEIGHT + 50 };
	//SetConsoleScreenBufferSize(ConsoleHandle, coord);

	//���ع��	
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	//ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(ConsoleHandle, &cursor);
}