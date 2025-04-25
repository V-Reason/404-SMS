#include "Frontend.h"

//登陆/注册主界面
user* LoginRegisterInterface()
{
	//自动登录-最高优先级
	struct tm* nowTime = GetNowTime();
	if (GetTimeSeg(nowTime, &logoutTime) <= AutoLogin_TimeSeg && logoutTime.tm_year != 0)
	{
		//自动登录
		user* temUser = FindUser(uhead, logoutName);				//先在uhead里找
		if (temUser == NULL)temUser = FindUser(ahead, logoutName);	//后在ahead里找
		if (temUser != NULL)
		{
			return temUser;
		}
		//若仍然temUser==NULL则不走自动登陆路线
	}

	//无法自动登录
	//准备工作
	system("cls");
	char key = ERROR;
	char LRmode = ERROR;
	int level = ERROR;
	user* temUser = NULL;

	while (TRUE)
	{
		system("cls");
		key = ERROR;
		LRmode = ERROR;
		level = ERROR;
		temUser = NULL;
		//开始界面
		SetCursorPosition(0, 0);
		printf("欢迎使用 %s ！！！\n", _TITLE);
		printf("使用前，请确保窗口大小恰当！！！\n");
		printf("按任意键继续！\n");
		printf("[ESC]退出\n");
		InputBox(&key, 1, MODE_KEY, ON);
		if (key == ESC)
		{
			printf("\n确定退出？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				//退出程序
				ExitSys();
				exit(0);
			}
			else
			{
				//重置
				continue;
			}
		}

		//子界面
		//分支-身份
		level = UserOrAdmin();
		if (level == ERROR)
		{
			continue;
		}

		//分支-登陆/注册
		if (level != ADMIN)
		{
			//非管理员可选择LR
			LRmode = LoginOrRegister();
			if (LRmode == ERROR)
			{
				continue;
			}
		}
		else
		{
			//管理员只能Login
			LRmode = LOGIN;
		}

		//分支-正式LR
		if (LRmode == LOGIN)
		{
			if (level == ADMIN)
				temUser = Login("管理员", ahead);
			else
				temUser = Login("用户", uhead);
			//登陆成功判定
			//失败
			if (temUser == NULL)
			{
				//重置
				continue;
			}
			//成功
			return temUser;
		}
		if (LRmode == REGISTER)
		{
			temUser = Register(uhead);
			//注册成功判定
			//失败
			if (temUser == NULL)
			{
				//重置
				continue;
			}
			//成功
			return temUser;
		}
	}
}

//登陆/注册选择函数 返回LOGIN/REGISTER 失败退出系统
char LoginOrRegister()
{
	//准备工作
	system("cls");
	char key = ERROR;
	int temLevel = ERROR;
	

	user* head = NULL;		//用于区分身份
	user* temUser = NULL;	//用作返回值
	char account[MAX_USER_NAME];
	char password1[MAX_PASSWORD_NUM];
	char password2[MAX_PASSWORD_NUM];
	memset(account, 0, sizeof(account)); //置零操作
	memset(password1, 0, sizeof(password1));
	memset(password2, 0, sizeof(password2));

	//分支-登陆/注册
	while (TRUE)
	{
		SetCursorPosition(0, 0);
		printf("当前时间：");
		PrintNowTime();
		printf("\n");

		printf("登陆/注册系统:\n");
		printf("请选择您要登陆或注册:\n");
		printf("[ESC]退出系统\n");
		printf("[%c]登陆\n", LOGIN);
		printf("[%c]注册\n", REGISTER);

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
			system("cls");
			printf("是否退出系统？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				ExitSys();//退出系统
			}
			else
			{
				key = ERROR;
				system("cls");
				break;//break switch
			}
		}
		case LOGIN:
		case REGISTER:
		{
			return key;//break switch
		}
		}//end switch
	}//end while
}

//用户/管理员选择函数 返回level 失败返回ERROR
int UserOrAdmin()
{
	//准备工作
	system("cls");
	char key = ERROR;

	while (TRUE)
	{
		SetCursorPosition(0, 0);
		printf("当前时间：");
		PrintNowTime();
		printf("\n");

		printf("身份选择:\n");
		printf("请选择:\n");
		printf("[ESC]返回\n");
		printf("[0]管理员\n");
		printf("[1]用户\n");

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
			break;
		}
		//返回
		case ESC:
		{
			system("cls");
			return ERROR;
		}
		//选择
		case '0':
		case '1':
		{
			system("cls");
			return key - '0';
		}
		}//end switch
	}//end while
}

//输入账号密码 传入参数head作为区分uhead和ahead 返回登陆的用户
user* Login(const char* inf, user* head)
{
	//准备工作
	system("cls");
	char key = ERROR;

	user* temUser = NULL;
	char account[MAX_USER_NAME + 1];
	char password[MAX_PASSWORD_NUM + 1];

	while (TRUE)
	{
		memset(account, 0, sizeof(account));
		memset(password, 0, sizeof(password));
		system("cls");

		printf("%s登陆\n", inf);
		printf("[ESC]返回\n");
		//输入
		printf("账号/手机号:");
		InputBox(account, MAX_USER_NAME, MODE_SHOW, ON);
		if (account[0] == ESC)//ESC检测
		{
			return NULL;
		}
		printf("\n");
		printf("密码:");
		InputBox(password, MAX_PASSWORD_NUM, MODE_PASSWORD, ON);
		if (password[0] == ESC)//ESC检测
		{
			continue;
		}

		temUser = FindUser(head, account);
		if (temUser == NULL
			||strcmp(password, temUser->password) != 0)
		{
			//失败处理
			printf("\n用户不存在或密码错误！\n");
			system("pause");
			continue;
		}
		//成功处理
		printf("\n登陆成功！\n");
		system("pause");
		return temUser;
	}
}

//注册账号 只允许用户注册 返回注册的用户
user* Register(user* head)
{
	//准备工作
	system("cls");
	char key = ERROR;

	user* temUser = NULL;
	char account[MAX_USER_NAME + 1];
	char teleNum[MAX_TELE_NUM + 1];
	char password1[MAX_PASSWORD_NUM + 1];
	char password2[MAX_PASSWORD_NUM + 1];

	while (TRUE)
	{
		memset(account, 0, sizeof(account));
		memset(password1, 0, sizeof(password1));
		memset(password2, 0, sizeof(password2));
		system("cls");

		printf("用户注册\n");
		printf("[ESC]返回\n");
		//输入账号
		printf("账号:");
		InputBox(account, MAX_USER_NAME, MODE_SHOW, ON);
		if (account[0] == ESC)//ESC检测
		{
			return NULL;
		}
		if (FALSE == JungeUserInformation(NAME, account)
			|| TRUE == isRepeatName(account))
		{
			printf("\n输入的账号不合规或已存在，请重试!\n");
			system("pause");
			continue;
		}
		//输入手机号
		printf("\n");
		printf("手机号:");
		InputBox(teleNum, MAX_TELE_NUM, MODE_SHOW, ON);
		if (teleNum[0] == ESC)//ESC检测
		{
			return NULL;
		}
		if (FALSE == JungeUserInformation(TELENUM, teleNum)
			|| TRUE == isRepeatTele(teleNum))
		{
			printf("\n输入的手机号不合规或已存在，请重试!\n");
			system("pause");
			continue;
		}
		//输入密码
		printf("\n");
		printf("密码:");
		InputBox(password1, MAX_PASSWORD_NUM, MODE_PASSWORD, ON);
		if (password1[0] == ESC)//ESC检测
		{
			continue;
		}
		if (!JungeUserInformation(PASSWORD, password1))
		{
			printf("\n输入的密码不合规，请重试!\n");
			system("pause");
			continue;
		}
		printf("\n");
		printf("请再次输入密码:");
		InputBox(password2, MAX_PASSWORD_NUM, MODE_PASSWORD, ON);
		if (password2[0] == ESC)//ESC检测
		{
			continue;
		}
		if (strcmp(password1, password2) != 0)
		{
			printf("\n两次输入的密码不一致，请重试！\n");
			system("pause");
			continue;
		}

		//成功处理
		temUser = CreatOneUser();
		strcpy(temUser->name, account);
		strcpy(temUser->tele_num, teleNum);
		strcpy(temUser->password, password1);
		AddUser(uhead, temUser);
		printf("注册成功！\n");
		system("pause");
		return temUser;
	}
}