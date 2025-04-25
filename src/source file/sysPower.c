#include "Frontend.h"

//初始化程序
void InitSys()
{
	//初始化文件夹
	InitFile();//第一次运行会初始化顶级管理员
	//配置控制台
	InitConsole();
	//配置密匙
	InitKey();

	//配置用户、管理员、包裹数据
	uhead = CreatUserList();	//用户链头
	ahead = CreatUserList();	//管理员链头
	phead = CreatPackageList();	//包裹链头
	chead = CreatCouponList();	//优惠券链头
	if (!ReadAll())
	{
		printf("读取文件出错！\n");
		exit(1);
	}

	//配置货架数据
	InitShelf();
}

//不退出程序 保存所有数据 并清除所有链表
void ExitSys()
{
	//保存数据
	if (!SaveAll())
	{
		printf("\n保存数据出错！\n");
		system("pause");
		return;
	}
	//清除所有链表
	DeleteAllPackage(phead);
	DeleteAllUser(uhead);
	DeleteAllUser(ahead);

	//exit(0);
}

//初始化txt文件
void InitFile()
{
	FILE* init_file = fopen(Init_File_txt, "r");
	if (init_file != NULL)
	{
		fclose(init_file);
		return;
	}
	printf("检测到第一次打开系统，正在初始化环境...\n");

	//创建文件夹
	_mkdir(HIS_FOLDER);
	_mkdir(RES_FOLDER);

	//创建文件
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

	//初始化顶级管理员
	ahead = CreatUserList();
	user* topAdmin = CreatOneUser();
	topAdmin->level = TOP_ADMIN;
	strcpy(topAdmin->name, DEFUALT_TOPADMIN_NAME);
	strcpy(topAdmin->password, DEFUALT_ADMIN_PASSWORD);
	AddUser(ahead, topAdmin);
	SaveUser(Admin_File_txt, ahead);
	DeleteAllUser(ahead);

	printf("初始化成功\n");
	system("pause");
	return;
}

//初始化货架 必须在读取包裹文件之后执行
void InitShelf()
{
	//置零
	memset(shelfs, 0, sizeof(shelfs));

	//配置shelf.location
	for(int num =0;num<SHELF_NUM;num++)
		for(int sub =0;sub<SUB_SHELF_NUM;sub++)
			for(int r=0;r<ROW;r++)
				for (int l = 0; l < LINE; l++)
				{
					char location[MAX_LOCATION + 1];
					sprintf(location, "%c%d_%d,%d", num + 'A', sub, r, l);
					strcpy(shelfs[num][sub][r][l].location, location);
				}

	//遍历phead
	package* point = phead->next;
	while (point != NULL)
	{
		//检测是否入库
		shelf* theShelf = StrToShelf(point->location);
		if (theShelf != NULL)
		{
			theShelf->used = TRUE;
			strcpy(theShelf->pack_id, point->id);
		}
		//遍历
		point = point->next;
	}
}

//初始化控制台
void InitConsole()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	//配置fontInfo
	fontInfo.cbSize = sizeof(fontInfo); // 结构体的大小
	fontInfo.nFont = 0; // 系统控制台字体表中字体的索引
	fontInfo.dwFontSize.X = 0;  // 字高
	fontInfo.dwFontSize.Y = 20; // 字宽
	fontInfo.FontFamily = FF_DONTCARE; // 字体间距和系列
	fontInfo.FontWeight = FW_NORMAL; // 粗细
	wcscpy_s(fontInfo.FaceName, sizeof(L"Consolas"), L"Consolas"); // 字样的名称

	SetCurrentConsoleFontEx(ConsoleHandle, FALSE, &fontInfo); //设置字体
	SetConsoleTitle(TITLE);  //设置窗口标题
	SetConsoleOutputCP(GBK); //输出转成GBK
	SetConsoleCP(GBK);		 //输入转成GBK ->用来适应中文输入
	system("color 07");      //黑底白字

	//改变窗口大小（需要管理员权限！！！）
	//char cmd[255];
	//for (int i = 0; i < 255; i++)
	//	cmd[i] = 0;
	//sprintf(cmd, "mode con cols=%d lines=%d",
	//	50, 50);
	//system(cmd);

	//设置窗口大小 和 缓冲区大小 (没成功，研究中）
	//ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SMALL_RECT wrt = { 0,0,50,50};
	//int junge = SetConsoleWindowInfo(ConsoleHandle, FALSE, &wrt);
	//COORD coord = { WIDTH + 50,HEIGHT + 50 };
	//SetConsoleScreenBufferSize(ConsoleHandle, coord);

	//隐藏光标	
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	//ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(ConsoleHandle, &cursor);
}