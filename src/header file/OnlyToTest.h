//读取历史记录
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

//写入历史记录
	/*
	package* pack = CreatOnePackage();
	strcpy(pack->id, "9876543210");
	strcpy(pack->tele_num, "18319775041");
	strcpy(pack->pack_name, "琪露诺fumo");

	WritePackHis(pack);

	free(pack);
	*/

//历史记录加解密
	/*
	InitKey();
	hisCyrTag = CYR;

	struct tm* nowTime = GetNowTime();
	package* pack = CreatOnePackage();
	strcpy(pack->pack_name, "琪露诺");
	strcpy(pack->id, "123456");

	WritePackHis(pack);
	ReadPackHis(nowTime, nowTime);

	free(pack);
	*/


//加密解密测试
/*
	_mkdir("TestFile");
	const char fileTxt[] = "./TestFile/File.txt";
	FILE* oriFile = fopen(fileTxt, "w");
	fputs("琪露诺是最强的！\n但是也确实是一个笨蛋呢...\n", oriFile);
	fclose(oriFile);

	InitKey();
	CyrptFile(fileTxt);
	DecyrptFile(fileTxt);
*/


//文件IO 检查
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

//文件IO
/*
	//初始化
	InitConsole();

	//模拟配置包裹
	phead = CreatPackageList();
	package* pack1 = _CreatOnePackage
		("1111111111", "18319775041", "魔法少女小圆手办", STATE_ERROR);
	package* pack2 = _CreatOnePackage
		("2222222222", "18377620980", "BakaFumo玩偶", STATE_ERROR);
	package* pack3 = _CreatOnePackage
		("3333333333", "18520429443", "MikuMiku", STATE_ERROR);
	package* pack4 = _CreatOnePackage
		("4444444444", "18319775041", "天童爱丽丝手办", STATE_ERROR);
	package* pack5 = _CreatOnePackage
		("5555555555", "18377620980", "JustFumoFumo", STATE_ERROR);
	package* pack6 = _CreatOnePackage
		("6666666666", "18520429443", "39Music", STATE_ERROR);
	package* pack7 = _CreatOnePackage
		("7777777777", "18319775041", "黄金万两", STATE_ERROR);
	package* pack8 = _CreatOnePackage
		("8888888888", "18377620980", "弱水时砂", STATE_ERROR);
	package* pack9 = _CreatOnePackage
		("9999999999", "18520429443", "茉莉奶绿", STATE_ERROR);
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

//模拟配置
	/*
	//初始化
	InitConsole();

	//模拟配置包裹
	phead = CreatPackageList();
	package* pack1 = _CreatOnePackage("1111111111", "18319775041", "魔法少女小圆手办", STATE_ERROR);
	package* pack2 = _CreatOnePackage("2222222222", "18377620980", "BakaFumo玩偶", STATE_ERROR);
	package* pack3 = _CreatOnePackage("3333333333", "18520429443", "MikuMiku", STATE_ERROR);
	package* pack4 = _CreatOnePackage("4444444444", "18319775041", "天童爱丽丝手办", STATE_ERROR);
	package* pack5 = _CreatOnePackage("5555555555", "18377620980", "JustFumoFumo", STATE_ERROR);
	package* pack6 = _CreatOnePackage("6666666666", "18520429443", "39Music", STATE_ERROR);
	package* pack7 = _CreatOnePackage("7777777777", "18319775041", "黄金万两", STATE_ERROR);
	package* pack8 = _CreatOnePackage("8888888888", "18377620980", "弱水时砂", STATE_ERROR);
	package* pack9 = _CreatOnePackage("9999999999", "18520429443", "茉莉奶绿", STATE_ERROR);
	AddOnePackage(phead, pack1);
	AddOnePackage(phead, pack2);
	AddOnePackage(phead, pack3);
	AddOnePackage(phead, pack4);
	AddOnePackage(phead, pack5);
	AddOnePackage(phead, pack6);
	AddOnePackage(phead, pack7);
	AddOnePackage(phead, pack8);
	AddOnePackage(phead, pack9);

	//配置用户
	uhead = CreatUserList();
	user* user1 = _CreatOneUser("V.Reason", "111", "18319775041", NORMAL_USER);
	user* user2 = _CreatOneUser("Vxiaoshan", "222", "18377620980", NORMAL_USER);
	user* user3 = _CreatOneUser("愚人舟", "333", "18520429443", NORMAL_USER);
	AddUser(uhead, user1);
	AddUser(uhead, user2);
	AddUser(uhead, user3);

	ahead = CreatUserList();
	user* topAdmin = _CreatOneUser("admin", "141", "141", TOP_ADMIN);
	user* admin = _CreatOneUser("admin", "141", "141", ADMIN);
	AddUser(ahead, topAdmin);
	AddUser(ahead, admin);

	message* mess1 = CreatOneMessage("我是通知1", 5);
	message* mess2 = CreatOneMessage("我是通知2", 5);
	message* mess3 = CreatOneMessage("我是通知3", 5);
	//message* mess4 = CreatOneMessage("我是通知4", 4);
	//message* mess5 = CreatOneMessage("我是通知5", 4);
	//message* mess6 = CreatOneMessage("我是通知6", 4);
	//message* mess7 = CreatOneMessage("我是通知7", 3);
	//message* mess8 = CreatOneMessage("我是通知8", 3);
	//message* mess9 = CreatOneMessage("我是通知9", 3);
	//message* mess10 = CreatOneMessage("我是通知10", 2);
	//message* mess11 = CreatOneMessage("我是通知11", 1);

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


//MessageSort测试代码
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

	printf("排序前:\n");
	PrintAllMessage(head);
	printf("\n");

	MessageSort(head);

	printf("排序后:\n");
	PrintAllMessage(head);
	printf("\n");
*/


//对InputBox的测试
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


//登陆/注册函数调用演示
/*
user* head = CreatUserList();
user* user0 = CreatOneUser(DEFAULT, DEFAULT, DEFAULT, DEFAULT);
AddUser(head, user0);

user* user1 = NULL;
do
{
	user1 = Login_Register(head);
} while (user1 == NULL);

//进入系统
if (user1->level == ADMIN)
{
	AdminSys(head, user1);
}
else
{
	UserSys(head, user1, user1->level);
}
*/


//初始化
/*
	
	InitConsole();

	//配置包裹
	package* phead = CreatPackageList();
	package* pack1 = CreatOnePackage("1111111111", "18319775041", "魔法少女小圆手办", STATUS_WAITING);
	package* pack2 = CreatOnePackage("2222222222", "18377620980", "BakaFumo玩偶", STATUS_WAITING);
	package* pack3 = CreatOnePackage("3333333333", "18520429443", "MikuMiku", STATUS_WAITING);
	AddOnePackage(phead, pack1);
	AddOnePackage(phead, pack2);
	AddOnePackage(phead, pack3);

	//配置用户
	user* uhead = CreatUserList();
	user* user1 = CreatOneUser("V.Reason", "111", "18319775041", NORMAL_USER);
	user* user2 = CreatOneUser("Vxiaoshan", "222", "18377620980", NORMAL_USER);
	user* user3 = CreatOneUser("愚人舟", "333", "18520429443", NORMAL_USER);
	AddUser(uhead, user1);
	AddUser(uhead, user2);
	AddUser(uhead, user3);

	user* ahead = CreatUserList();
	user* admin = CreatOneUser("admin", "141", "141", ADMIN);
	AddUser(ahead, admin);

	AdminSys(admin,phead,uhead);

	ExitSys(phead, uhead, ahead);


*/


//取件码随机数示范
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

//功能存疑
/*
			//功能存疑
			//case '4'://检查所有包裹
			//{
			//	system("cls");
			//	printf("<检查包裹>\n");
			//	printf("按下[ESC]返回\n");

			//	//Judge没写完，没法写

			//	break;//break switch
			//}

			//case '7'://录入用户 没写完整
			//	system("pause");
			//	printf("<录入用户>\n");
			//	printf("按下[ESC]返回\n");
			//	printf("请依次填写以下内容：\n");

			//	user* user = CreatOneUser(DEFAULT, DEFAULT, DEFAULT, DEFAULT);//创建空白用户

			//	if (EnterUser(user) == FALSE)
			//	{
			//		//失败处理
			//		key = ERROR;//重置
			//		free(pack);
			//		system("cls");
			//		continue;
			//	}
			//	//成功处理

			//	break;//break switch
*/


//作废代码1
/*

	//初始化SDL    视频子系统        事件子系统
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)<0)
	{
		//失败检测
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return -1;
	}
	if (IMG_Init(IMG_INIT_JPG) == FALSE)
	{
		//失败检测
		SDL_Log("IMG_Init failed: %s", IMG_GetError());
		return -1;
	}

	//创建主窗口->居中显示，可调大小
	SDL_Window* mainWindow = SDL_CreateWindow(
		WINDOWS_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOWS_WIDTH, WINDOWS_LENTH,
		SDL_WINDOW_RESIZABLE);
	if (mainWindow == NULL)
	{
		//失败检测
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
		return -1;
	}

	//铺色


	//事件监听/消息循环 event_loop
	SDL_Event event;
	int flag = TRUE;//控制消息循环进行与否
	while (flag)
	{
		if (SDL_PollEvent(&event)) //Poll无阻塞  wait阻塞
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

	//清理
	SDL_DestroyWindow(mainWindow);
	//退出SDL
	IMG_Quit();
	SDL_Quit();

*/


//作废代码2
/*
//包裹异常类型
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
////用户异常类型
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
////通知异常类型
//typedef enum messageError
//{
//	m_content_ERROR		= 0x00000001u,
//	m_important_ERROR	= 0x00000010u,
//
//	m_point_ERROR		= 0x00000020u,
//	//m_next_ERROR		= 0x00000200u,
//}messageError;
*/


//作废代码3
/*
////SDL2  注意是2！！！ 是2！！！
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
*/


//作废代码4
/*
////窗口宏
//#define WINDOWS_TITLE "404 Staion System"
//#define WINDOWS_WIDTH 1920
//#define WINDOWS_LENTH 1080
*/


//作废代码5
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


//作废代码6
/*
//判断单个包裹数据是否合法
void JudgePackage(package* pack) {
	//int error = NO_ERROR;
	////运单号
	//if (strlen(pack->id) != MAX_ID || isdigit(pack->id) != FALSE)
	//{
	//	error |= p_id_ERROR;
	//}
	////手机号
	//if (strlen(pack->tele_num) != MAX_TELE_NUM || isdigit(pack->tele_num) != FALSE)
	//{
	//	error |= p_tele_ERROR;
	//}

	////包裹名称->无限制

	////包裹状态
	//if (pack->state == STATE_EXCEPTION || pack->state == STATE_STAY_LONG)
	//{
	//	error |= p_state_ERROR;
	//}


	////存放地点
	//if (strlen(pack->location) != MAX_LOCATION)
	//{
	//	error |= p_location_ERROR;
	//}

	////指针
	//if (!(pack->owner && pack->sender && pack->prior && pack->next))
	//{
	//	error |= p_point_ERROR;
	//}

	////收件人/地址->无限制
	////寄件人/地址->无限制
	//
	////运费
	//if (pack->Bill < 0)
	//{
	//	error |= p_bill_ERROR;
	//}

	////重量
	//if (pack->weight < 0)
	//{
	//	error |= p_weight_ERROR;
	//}

	////体积
	//if (pack->size < 0)
	//{
	//	error |= p_size_ERROR;
	//}



	//功能存疑
	////偏远地区
	//if (pack->isRemoteArea > 1)
	//{
	//	error |= p_area_ERROR;
	//}

	////易碎品
	//if (pack->isFragile > 1)
	//{
	//	error |= p_fragile_ERROR;
	//}

	////贵重物品
	//if (pack->isValuable > 1)
	//{
	//	error |= p_valuable_ERROR;
	//}

}
*/

//作废代码7
/*
//包裹状态
typedef enum packageState
{
	STATE_EXCEPTION		= 0,   // 异常
	STATE_WAITING			= 1,   // 待取
	STATE_WAITING_PROCESS	= 2,   // 待处理
	STATE_RECEIVED			= 3,   // 已取
	STATE_IN_TRANSIT		= 4,   // 在途
	STATE_STAY_LONG		= 5    // 滞留时间过长
}packageState;

*/

//作废代码8
/*
		//修改运单号
		case 'w':
		{
			printf("新运单号:");
			InputBox(input, MAX_ID, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0
				|| strlen(input) != MAX_ID
				|| (!isAllDigits(input)))
			{
				//重置
				printf("\n修改失败...\n");//不知道为啥第一个字不显示
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\n确认修改？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n已取消修改\n");
				system("pause");
				key = ERROR;
				system("cls");
			}
			memcpy(pack->id, input, MAX_ID);
			//junge()
			printf("\n新运单号修改成功!\n");
			system("pause");
			key = ERROR;
			system("cls");

			break;//break switch
		}

*/

//作废代码9
/*
		//修改包裹名称
		case '3':
		{
			printf("新包裹名称:");
			InputBox(input, MAX_PACK_NAME, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0)
			{
				//重置
				printf("\n修改失败...\n");//不知道为啥第一个字不显示
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\n确认修改？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n已取消修改\n");
				system("pause");
				key = ERROR;
				system("cls");
			}
			memcpy(pack->pack_name, input, MAX_PACK_NAME);
			//junge()
			printf("\n新包裹名称修改成功!\n");
			system("pause");
			key = ERROR;
			system("cls");

			break;//break switch
		}

*/

//作废代码10
/*
		case '2':
		{
			printf("新手机号:");
			InputBox(input, MAX_TELE_NUM, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0
				|| strlen(input) != MAX_TELE_NUM
				|| (!isAllDigits(input)))
			{
				//重置
				printf("\n修改失败...\n");//不知道为啥第一个字不显示
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\n确认修改？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n已取消修改\n");
				system("pause");
				key = ERROR;
				system("cls");
			}
			memcpy(pack->tele_num, input, MAX_TELE_NUM);
			//junge()
			printf("\n新手机号修改成功!\n");
			system("pause");
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//修改收件人名称
		case '3':
		{
			printf("新收件人姓名:");
			InputBox(input, MAX_USER_NAME, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0)
			{
				//重置
				printf("\n修改失败...\n");//不知道为啥第一个字不显示
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\n确认修改？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n已取消修改\n");
				system("pause");
				//重置
				key = ERROR;
				system("cls");
			}
			memcpy(pack->user_name, input, MAX_USER_NAME);
			printf("\n新收件人名称修改成功!\n");
			system("pause");
			//重置
			key = ERROR;
			system("cls");
		}
		//修改寄件人名称
		case '4':
		{
			printf("新寄件人姓名:");
			InputBox(input, MAX_USER_NAME, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0)
			{
				//重置
				printf("\n修改失败...\n");//不知道为啥第一个字不显示
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\n确认修改？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n已取消修改\n");
				system("pause");
				//重置
				key = ERROR;
				system("cls");
			}
			memcpy(pack->sender_name, input, MAX_USER_NAME);
			printf("\n新寄件人名称修改成功!\n");
			system("pause");
			//重置
			key = ERROR;
			system("cls");
		}
		//修改收件人地址
		case '5':
		{
			printf("新收件人地址:");
			InputBox(input, MAX_ADDRESS, SHOW, ON);
			if (input[0] == ESC
				|| strlen(input) == 0)
			{
				//重置
				printf("\n修改失败...\n");//不知道为啥第一个字不显示
				system("pause");
				key = ERROR;
				system("cls");

				break;//break switch
			}
			printf("\n确认修改？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, KEY, ON);
			if (key != 'y')
			{
				printf("\n已取消修改\n");
				system("pause");
				//重置
				key = ERROR;
				system("cls");
			}
			memcpy(pack->user_address, input, MAX_USER_NAME);
			printf("\n新寄件人名称修改成功!\n");
			system("pause");
			//重置
			key = ERROR;
			system("cls");
		}

*/

//作废代码11
/*
//修改用户信息 传入DEFAULT表示不修改
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

//作废代码12
/*
//国家电话代码
typedef struct countryCode {
	char code[4];       // 国家代码（默认为"+86"）
	char country[20];   // 国家名称
}countryCode;
//国家代码表
countryCode countryCodes[] =
{
	{"+86", "China"},			//中国
	{"+1", "United States"},	//美国
	{"+81", "Japan"},			//日本
	{"+82", "South Korea"},		//韩国
	{"+44", "United Kingdom"},  //英国
	{"+33", "France"},			//法国
	{"+49", "Germany"},			//德国
	{"+91", "India"},			//印度
	{"+7", "Russia"},			//俄国
	{"+55", "Brazil"},			//巴西
	{"+61", "Australia"},		//澳大利亚
	{"+65", "Singapore"},		//新加坡
	{"+27", "South Africa"},	//南非
	{"+52", "Mexico"},			//墨西哥
};
//国家代码表的长度
const int numCountryCodes = sizeof(countryCodes) / sizeof(countryCodes[0]);
*/

//作废代码13
/*
// 读取用户文件
void FileReadUser(user* head) {
	// 打开文件
	FILE* file = fopen("SAMPLE_FILE_NAME ", "r");
	if (file == NULL) {
		perror("File not found");
		return;
	}
	user* puser = head;

	// 读取数据
	while (1) {

		if (feof(file)) {
			printf("文件读取完毕\n");
			break;
		}

		puser->next = (user*)malloc(sizeof(user));
		puser->next->prior = puser;
		puser->next->next = NULL;
		puser = puser->next;

		int i = fscanf(file, "%s %s %s %d",
			puser->name, puser->password, puser->tele_num, &puser->level);

		if (i != 4) {                             // 数据不完整
			printf("数据不完整或多余，请修改后重新读取\n");
			puser->prior->next = NULL;
			free(puser);    // 多定义一个结构体，释放掉
			break;
		}
		if (JudgeUser(puser) == FALSE) {               // 数据不合法
			printf("数据不合法，请修改后重新读取\n");
			puser->prior->next = NULL;
			free(puser);    // 多定义一个结构体，释放掉
			break;
		}

	}

	fclose(file);
}
*/

//作废代码14
/*
判断数据是否合法  //没写完
int JudgeUser(user* puser)
{
	if (strlen(puser->password) != MAX_PASSWORD_NUM) {
		printf("password长度不合法\n");
		return FALSE;
	}
	if (strlen(puser->name) > MAX_PACK_NAME) {
		printf("name长度不合法\n");
		return FALSE;
	}
	if (strlen(puser->tele_num) != MAX_TELE_NUM) {
		printf("tele_num长度不合法\n");
		return FALSE;
	}
	if (puser->level < 0 || 5 < puser->level) {
		printf("level不合法\n");
		return FALSE;
	}
	return TRUE;
}
*/

//作废代码15
/*
//保存用户信息至txt文件
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
// 保存包裹数据
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
// 读取包裹文件
/*
void FileReadPackage(package* head) {
	// 打开文件
	FILE* file = fopen("./samples.txt", "r");
	if (file == NULL) {
		perror("File not found");
		return;
	}
	package* pack = head;

	// 读取数据
	while (1) {

		if (feof(file)) {
			printf("文件读取完毕\n");
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
					printf("时间数据不完整\n");
					pack->prior->next = NULL;
					free(pack);    // 多定义一个结构体，释放掉
					break;
				}
			}
		}

		if (x != 14) {                             // 数据不完整
			printf("数据不完整或多余，请修改后重新读取\n");
			pack->prior->next = NULL;
			free(pack);    // 多定义一个结构体，释放掉
			break;
		}
		if (JudgePackage(pack) == FALSE) {               // 数据不合法
			printf("数据不合法，请修改后重新读取\n");
			pack->prior->next = NULL;
			free(pack);    // 多定义一个结构体，释放掉
			break;
		}

	}

	fclose(file);
}
// 读取通知信息
void FileReadMessage(message* head) {
	FILE* file = fopen("MESSAGE_FILE_NAME", "r");
	if (file == NULL) {
		perror("File not found");
		return;
	}
	message* pmessage = head;
	// 读取数据
	while (TRUE) {
		if (feof(file)) {
			printf("文件读取完毕\n");
			break;
		}
		pmessage->next = (message*)malloc(sizeof(message));
		pmessage->next->prior = pmessage;
		pmessage->next->next = NULL;
		pmessage = pmessage->next;
		int i = fscanf(file, "%s %d", pmessage->content, &pmessage->important);
		if (i != 2) {                             // 数据不完整
			printf("数据不完整或多余，请修改后重新读取\n");
			pmessage->prior->next = NULL;
			free(pmessage);    // 多定义一个结构体，释放掉
			break;
		}
	}
	fclose(file);
}


*/

//作废代码16
/*
	//分支-身份
	while (mode == LOGIN)//不允许注册管理员
	{
		SetCursorPosition(0, 0);
		printf("当前时间：");
		PrintNowTime();
		printf("\n");

		printf("请选择您的身份\n");
		printf("[ESC]返回\n");
		printf("[%c]管理员\n", ADMIN);
		printf("[%c]用户\n", USER);
		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		switch (key)
		{
			//无响应
		case ERROR:
		{
			break;//break switch
		}
		//退出系统
		case ESC:
		{
			return NULL;//利用返回值重启函数
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

	//输入账号
	while (TRUE)
	{
		system("cls");
		printf("输入\'r\'重新开始.\n");
		printf("请输入您的账号：\n");
		InputBox(account, MAX_USER_NAME, MODE_SHOW, OFF);

		if (strcmp(_RETRY, account) == 0)
			return NULL;

		if (mode == REGISTER)
			break;

		temUser = FindUser(head, account);
		if (temUser == NULL)
		{
			printf("账号输入错误或不存在，请您重新输入。\n");
			system("pause");
		}
	}

	while (TRUE)
	{
		printf("\n输入\'r\'重新开始.\n");
		printf("请输入您的密码：\n");
		InputBox(password1, MAX_PASSWORD_NUM, MODE_PASSWORD, OFF);

		if (strcmp(_RETRY, account) == 0)
			return NULL;

		if (mode == LOGIN)
		{
			if (strcmp(password1, temUser->password) == 0)
			{
				printf("登录成功！\n");
				system("pause");
				return temUser;
			}
			else
			{
				printf("密码错误，请您重新输入。\n");
				system("pause");
			}
		}
		if (mode == REGISTER)
		{
			printf("\n输入\'r\'重新开始.\n");
			printf("请再次输入您的密码：\n");
			InputBox(password2, MAX_PASSWORD_NUM, MODE_PASSWORD, OFF);

			if (strcmp(_RETRY, account) == 0)
				return NULL;

			if (strcmp(password1, password2) != 0)
			{
				printf("您两次输入的密码不一致，请重新确认：\n");     //当忘记密码时？？？
			}
			else
			{
				printf("\n恭喜您注册成功！\n");
				temUser = CreatOneUser(account, password1, DEFAULT, (int)(temLevel - '0'));
				AddUser(head, temUser);
				system("pause");
				return temUser;
			}
		}
	}
*/

//作废代码17
/*
	const int inTime
		= GetDaysFromStartOfYear
		(pack->time[IN][YEAR], pack->time[IN][MON], pack->time[IN][DAY]);
	const int nowTime
		= GetDaysFromStartOfYear
		(ptime->tm_year, ptime->tm_mon, ptime->tm_mday);
	//计算绝对天数的差值
	int days = 0;
	if (pack->time[IN][YEAR] == pack->time[OUT][YEAR])//相同年份解决法
	{
		days = nowTime - inTime;
	}
	else//不同年份解决法
	{
		for (int y = pack->time[IN][YEAR]; y < pack->time[OUT][YEAR]; y++)
		{
			days += IsLeapYear(y) ? 366 : 365;
		}
		days += (nowTime - inTime);
	}
*/

//作废代码18
/*
//管理员查找多个包裹，将查找到的包裹组成链表后放置到head末尾，返回第一个找到的包裹的地址
package* AdminFindPackage(package* head, char* str)
{
	package* nhead = CreatPackageList();
	int mode = ERROR;

	//匹配类型
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

	//查找
	while (head->next != NULL)//遍历
	{
		head = head->next;

		int relevance = FALSE;
		char temStateStr[2];
		temStateStr[0] = (head->state + '0');
		temStateStr[1] = '\0';

		switch (mode)//类型匹配
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

		if (relevance == TRUE)//查询结果判断
		{
			head = head->prior;
			TakeOutOnePackage(nhead, head->next);//抓出，放nhead末尾
		}
	}

	//整合head和nhead
	if (nhead->next != NULL)
	{
		AddMultiplePackage(head, nhead);//用pack充当head的尾巴
		//free(nhead); nhead已经在AddMultiplePackage中释放
		return head->next;
	}
	else//没有查询结果，释放空间
	{
		free(nhead);
		return NULL;
	}
}
*/

//作废代码19
/*
//初始化coupons[]
void InitCoupons()
{
	memset(coupons, 0, sizeof(coupon) * COUPON_NUM);

	strcpy(coupons[0].content, "九折 三个月");//3元
	coupons[0].rate = 0.9;
	coupons[0].timeLimit = 3;
	coupons[0].cost = 3;
	strcpy(coupons[1].content, "九五折 四个月");//4元
	coupons[1].rate = 0.95;
	coupons[1].timeLimit = 4;
	coupons[1].cost = 4;
	strcpy(coupons[0].content, "八折 五个月");//5元
	coupons[2].rate = 0.8;
	coupons[2].timeLimit = 5;
	coupons[2].cost = 5;
}*/

#pragma endregion