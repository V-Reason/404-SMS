#include "Frontend.h"

//顶级管理员操作系统
//除了管理员的所有功能外
//普通用户查改？算了吧
//1.操作管理员信息
//2.增删管理员账号
//3.能看到user密码？算了吧
//注：管理员和用户分治，用两个链表
void TopAdminSys(user* admin)
{
	//初始化
	system("cls");
	char key = ERROR;					//接收单键输入
	char search[MAX_SEARCH_LENGTH];		//接收字符串输入
	memset(search, 0, sizeof(search));	//置零
	package* pack_search = NULL;
	user* user_search = NULL;
	struct tm* nowTime = GetNowTime();
	struct tm* lastTime_S = nowTime;
	struct tm* lastTime_L = nowTime;

	//每次首次登陆操作
	if (logoutTime.tm_year != 0
		&& (logoutTime.tm_year != nowTime->tm_year
			|| logoutTime.tm_mon != nowTime->tm_mon
			|| logoutTime.tm_mday != nowTime->tm_mday))
	{
		//节日祝福
		festival* fes = isFestival();
		if (fes != NULL)
		{
			message* mess = CreatOneMessage("", IMP_SPECIAL);
			sprintf(mess->content, "%s 快乐！", fes->name);
			AddMessage(admin->mlist, mess);
		}
		//遍历包裹
		GoThroughPackage();
	}

	while (TRUE)
	{
		//定时进行
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

		//不用初始化key
		//不要在这里写cls
		SetCursorPosition(0, 0);
		memset(search, 0, sizeof(search));
		pack_search = NULL;
		user_search = NULL;

		//主界面
		//时间
		printf("<顶级管理员主界面>\n");
		printf("当前时间：");
		PrintNowTime();

		//财报
		printf("\n总财产：%lf\n", fund);

		//通知
		printf("\n通知:\n");
		PrintNumMessage(admin->mlist, MESS_NUM);
		printf("\n");
		//操作说明
		printf("按下对应按键以选择功能...\n\n");

		printf("[ESC]退出\n\n");

		printf("关于通知：\n");
		printf("[`]管理通知\n\n");

		printf("内购管理：\n");
		printf("[0]内购管理\n\n");

		printf("查询功能：\n");
		printf("[1]包裹\n");
		printf("[2]货架\n");
		printf("[3]用户\n");
		printf("[4]历史记录\n\n");

		printf("录入功能：\n");
		printf("[5]录入包裹\n\n");
		printf("[6]包裹入库\n\n");

		printf("广播功能：\n");
		printf("[7]广播至用户\n");
		printf("[8]广播至管理员\n\n");

		printf("个人信息修改:\n");
		printf("[9]修改个人信息\n\n");

		printf("管理管理员：\n");
		printf("[a]查询管理员\n");
		printf("[b]创建管理员\n\n");

		printf("其它：\n");
		printf("[s]保存选项\n");
		printf("[q]退出登陆\n\n");

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//功能判断->消息循环
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
			printf("退出程序？\n [y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				//记录退出时间
				RecordLogoutTime();
				//记录退出账号
				RecordLogoutUser(admin);
				//退出
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
		//管理通知
		case '`':
		{
			//界面写在了ModifyMessage()里面
			MessSys(admin);
			//重置
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//内购管理
		case '0':
		{
			ManagePay();
			key = ERROR;
			system("cls");
			break;
		}
		//查询包裹
		case '1':
		{
			system("cls");
			printf("<查询包裹>\n");
			printf("按下[ESC]返回\n");
			printf("状态对照表:(状态搜索请输入数字)\n");
			printf("[%d]异常 [%d]存放过久 [%d]待签收 [%d]运输中 [%d]待揽收 [%d]拒收 [%d]已签收\n",
				STATE_ERROR, STATE_STAY_LONG, STATE_WAIT_PICK, STATE_TRANSPORT, STATE_WAIT_COLLECT, STATE_REJECT, STATE_PICKUPED);
			printf("搜索框：");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			printf("\n\n");

			if (search[0] == ESC)//ESC检测
			{
				key = ERROR;//重置
				system("cls");
				break;//break switch
			}

			pack_search = AdminFindPackage(phead, search);
			if (pack_search != NULL)
			{
				//成功处理
				printf("键入[`]   编辑模式\n");
				printf("键入[空格] 重新搜索\n\n");

				printf("共查询到 %d 个结果，以下显示部分数据，进入编辑模式查看更多.\n", CountPackage(pack_search));
				PrintNumPackage(pack_search, PAGE_NUM);

				//键入检测
				while (TRUE)
				{
					InputBox(&key, 1, MODE_KEY, ON);
					if (key == ESC)
					{
						//重置
						key = ERROR;
						system("cls");
						break;
					}
					if (key == '`')
					{
						EditPackage(pack_search);//进入编辑模式
						key = '1';//重置为重新搜索
						break;
					}
					if (key == ' ')
					{
						key = '1';//重置为重新搜索
						break;
					}
				}
			}
			else
			{
				//失败处理
				printf("无结果......\n\n");
				system("pause");//静默等待
			}

			system("cls");

			break;//break switch
		}
		//查询货架
		case '2':
		{
			system("cls");
			printf("<查询货架>\n");
			printf("按下[ESC]返回\n");
			PrintAllShelf();
			printf("\n");

			printf("输入范例： A0_1,2  D4_3,4\n");
			printf("输入框：");
			InputBox(search, MAX_LOCATION, MODE_SHOW, ON);

			if (search[0] == ESC)//ESC检测
			{
				//重置
				key = ERROR;
				system("cls");
				break;
			}

			shelf* theShelf = StrToShelf(search);

			if (theShelf == NULL)
			{
				printf("输入的货架格式不正确，请重试！\n");
				system("pause");
				system("cls");
				break;
			}

			printf("\n%s 的状态如下：\n", search);
			char shelf_state[MAX_TF + 1];
			memset(shelf_state, 0, sizeof(shelf_state));
			TFtoStr(shelf_state, theShelf->used);
			printf("是否被占用：%s\n", shelf_state);
			printf("占用的包裹运单号：%s\n", theShelf->pack_id);

			printf("\n");
			printf("是否将其修改？\n");
			printf("[y/n]\n");
			InputBox(search, 1, MODE_KEY, OFF);
			if (search[0] == 'y')
			{
				ModifyShelf(theShelf);
			}

			system("pause");//静默等待
			system("cls");
			break;//break switch
		}
		//查询用户
		case '3':
		{
			system("cls");
			printf("<查询用户>\n");
			printf("按下[ESC]返回\n");
			printf("搜索框：");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			printf("\n");

			if (search[0] == ESC)//ESC检测
			{
				key = ERROR;//重置
				system("cls");
				break;//break switch
			}

			user_search = FindUser(uhead, search);//查询结果
			if (user_search != NULL)
			{
				//成功处理
				PrintOneUser(user_search);
			}
			else
			{
				//失败处理
				printf("无结果......\n");
			}

			system("pause");//静默等待
			system("cls");

			break;//break switch
		}
		//查询历史包裹
		case '4':
		{
			system("cls");
			printf("<查询历史记录>\n");
			printf("[ESC]退出\n");
			printf("格式eg：20060105\n");
			printf("请输入——\n");
			//输入1
			printf("起始日期：");
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
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			//数据转换
			int dataNum = atof(search);			//eg:20060105
			if (dataNum < 0)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			struct tm data1 = { 0 };
			data1.tm_year = dataNum / 10000;	//没法用MAX_DATA算出来——请注意
			data1.tm_mon = (dataNum % 10000) / 100;
			data1.tm_mday = dataNum % 100;
			if (12 < data1.tm_mon)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			if (DaysInMonth(data1.tm_year, data1.tm_mon) < data1.tm_mday)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			//输入2
			printf("终止日期：");
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
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			//数据转换
			dataNum = atof(search);				//eg:20060105
			if (dataNum < 0)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			struct tm data2 = { 0 };
			data2.tm_year = dataNum / 10000;	//没法用MAX_DATA算出来——请注意
			data2.tm_mon = (dataNum % 10000) / 100;
			data2.tm_mday = dataNum % 100;
			if (12 < data2.tm_mon)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			if (DaysInMonth(data2.tm_year, data2.tm_mon) < data2.tm_mday)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}

			//正式查询
			ReadPackHis(&data1, &data2);
			system("pause");

			//key = ERROR;
			system("cls");
			break;
		}
		//录入包裹
		case '5':
		{
			system("cls");
			printf("<录入包裹>\n");
			printf("按下[ESC]返回\n");
			printf("请依次填写以下内容：\n");

			package* pack = CreatOnePackage();//创建空白包裹

			if (EnterPackage(pack) == FALSE)//输入信息
			{
				//失败处理
				key = ERROR;//重置
				free(pack);
				system("cls");
				continue;
			}
			//成功处理
			AddOnePackage(phead, pack); //加入链表
			printf("\n录入成功！\n");
			PrintOnePackage(pack); //回显全部信息

			system("pause");//静默等待
			system("cls");

			break;//break switch
		}
		//包裹入库
		case '6':
		{
			system("cls");
			printf("<包裹入库>\n");
			printf("按下[ESC]返回\n");
			printf("运单号：");
			InputBox(search, MAX_ID, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (FALSE == JungePackageInformation(ID, search))
			{
				printf("\n输入的运单号格式错误，请重试\n");
				system("pause");
				system("cls");
				break;
			}
			pack_search = AdminFindPackage(phead, search);
			if (NULL == pack_search)
			{
				printf("\n输入的运单号不存在，请重试\n");
				system("pause");
				system("cls");
				break;
			}
			printf("\n找到如下包裹，请确认.\n");
			PrintOnePackage(pack_search);
			printf("\n确定入库？\n");
			printf("[y/n]\n");
			InputBox(search, 1, MODE_KEY, OFF);
			if (search[0] != 'y')
			{
				printf("已取消入库...\n");
				printf("正在返回...\n");
				system("pause");
				system("cls");
				break;
			}
			if (pack_search->state == STATE_WAIT_PICK)
			{
				printf("请勿重复入库！\n");
				printf("正在返回......\n");
				system("pause");
				system("cls");
				break;
			}
			if (FALSE == AllocateLocation(pack_search, ahead))
			{
				printf("入库失败...\n");
				printf("货架已满，请检查！\n");
				printf("正在返回...\n");
				system("pause");
				system("cls");
				break;
			}
			user* temUser = FindUser(uhead, pack_search->tele_num);
			if (temUser != NULL)
			{
				message* mess = CreatOneMessage("", IMP_NORMAL);
				sprintf(mess->content, "你的包裹（%s）待签收", pack_search->pack_name);
				AddMessage(temUser->mlist, mess);
			}
			printf("入库成功！\n");
			printf("成功将包裹发配到：%s\n", pack_search->location);
			printf("正在返回...\n");
			system("pause");
			system("cls");
			break;//break switch
		}
		//广播
		case '7': //至用户
		case '8': //至管理员
		{
			const char _group[2][10] = {"用户","管理员"};
			user* group = uhead;
			if (key == '8')group = ahead;

			system("cls");
			printf("按下[ESC]返回\n");
			printf("消息将发至 全体%s\n", _group[key - '7']);
			printf("请输入广播消息：");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			if (search[0] == ESC)//ESC检测
			{
				//重置
				key = ERROR;
				system("cls");
				break;
			}
			//确认？
			printf("\n确定广播如上消息？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key != 'y')
			{
				key = ERROR;
				system("cls");
				break;
			}
			//正式广播
			message* mess = CreatOneMessage(search, IMP_SPECIAL);
			Broadcast(mess, group);//广播至指定群体
			printf("\n广播成功！\n");
			printf("正在返回...\n");
			key = ERROR;
			system("pause");
			system("cls");
			break;//break switch
		}

		//顶级管理员个人信息修改
		case '9':
		{
			system("cls");
			printf("<修改个人信息>\n");
			printf("按下[ESC]返回\n");
			PrintOneUser(admin);
			printf("\n是否要修改？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				ModifyUserInterface(admin);
			}
			else
				//重置
				key = ERROR;
			system("cls");

			break;//break switch
		}
		//查询管理员
		case 'a':
		{
			system("cls");
			printf("<查询次级管理员>\n");
			printf("按下[ESC]返回\n");

			if (ahead != NULL)
			{
				//成功处理
				printf("键入[`]   编辑模式\n");

				printf("共查询到 %d 个结果，以下显示部分数据，进入编辑模式查看更多.\n", CountUser(ahead));
				PrintNumAdmin(ahead, ADMIN_NUM);

				//键入检测
				while (TRUE)
				{
					InputBox(&key, 1, MODE_KEY, ON);
					if (key == ESC)
					{
						//重置
						key = ERROR;
						system("cls");
						break;
					}
					if (key == '`')
					{
						EditAdmin(ahead);//进入编辑模式
						key = '1';//重置为重新搜索
						break;
					}
				}
			}
			else
			{
				//失败处理
				printf("无结果......\n\n");
				system("pause");//静默等待
			}

			system("cls");

			break;//break switch
		}
		//创建管理员
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
			printf("\n新管理员创建成功!\n");
			PrintOneAdmin(NewAdmin);
			system("pause");
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//保存选项
		case 's':
		{
			SaveOption();
			key = ERROR;
			system("cls");
			break;
		}
		//退出登陆
		case 'q':
		{
			system("cls");
			printf("退出登陆？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				//空置logoutTime记录
				ClearLogout();
				//重返登陆
				powerTag = RESTART;
				return;
			}
			else
			{
				//重置
				key = ERROR;
				system("cls");
				break;//break switch
			}
		}

		//Sleep(500);//系统响应时间 单位为ms 过快会有闪烁问题->闪烁问题已解决
		}//end switch
	}//end while
}

//管理员操作系统
void AdminSys(user* admin)
{
	//初始化
	system("cls");
	char key = ERROR;					//接收单键输入
	char search[MAX_SEARCH_LENGTH];		//接收字符串输入
	memset(search, 0, sizeof(search));	//置零
	package* pack_search = NULL;
	user* user_search = NULL;
	struct tm* nowTime = GetNowTime();
	struct tm* lastTime_S = nowTime;
	struct tm* lastTime_L = nowTime;

	//每次首次登陆操作
	if (logoutTime.tm_year != 0
		&& (logoutTime.tm_year != nowTime->tm_year
			|| logoutTime.tm_mon != nowTime->tm_mon
			|| logoutTime.tm_mday != nowTime->tm_mday))
	{
		//节日祝福
		festival* fes = isFestival();
		if (fes != NULL)
		{
			message* mess = CreatOneMessage("", IMP_SPECIAL);
			sprintf(mess->content, "%s 快乐！", fes->name);
			AddMessage(admin->mlist, mess);
		}
		//遍历包裹
		GoThroughPackage();
	}

	while (TRUE)
	{
		//定时进行
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

		//不用初始化key
		//不要在这里写cls
		SetCursorPosition(0, 0);
		memset(search, 0, sizeof(search));
		pack_search = NULL;
		user_search = NULL;

		//主界面
		//时间
		printf("<管理员主界面>\n");
		printf("当前时间：");
		PrintNowTime();

		//财报
		printf("\n总财产：%lf\n", fund);

		//通知
		printf("\n通知:\n");
		PrintNumMessage(admin->mlist, MESS_NUM);
		printf("\n");
		//操作说明
		printf("按下对应按键以选择功能...\n\n");

		printf("[ESC]退出\n\n");

		printf("关于通知：\n");
		printf("[`]管理通知\n\n");

		printf("内购管理：\n");
		printf("[0]内购管理\n\n");

		printf("查询功能：\n");
		printf("[1]包裹\n");
		printf("[2]货架\n");
		printf("[3]用户\n");
		printf("[4]历史记录\n\n");

		printf("录入功能：\n");
		printf("[5]录入包裹\n");
		printf("[6]包裹入库\n\n");

		printf("广播功能：\n");
		printf("[7]广播至用户\n\n");

		printf("个人信息修改:\n");
		printf("[8]修改个人信息\n\n");

		printf("其它：\n");
		printf("[9]保存选项\n");
		printf("[q]退出登陆\n\n");

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//功能判断->消息循环
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
			printf("退出程序？\n [y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				//记录退出时间
				RecordLogoutTime();
				//记录退出账号
				RecordLogoutUser(admin);
				//退出
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
		//管理通知
		case '`':
		{
			//界面写在了ModifyMessage()里面
			MessSys(admin);
			//重置
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//内购管理
		case '0':
		{
			ManagePay();
			key = ERROR;
			system("cls");
			break;
		}
		//查询包裹
		case '1':
		{
			system("cls");
			printf("<查询包裹>\n");
			printf("按下[ESC]返回\n");
			printf("状态对照表:(状态搜索请输入数字)\n");
			printf("[%d]异常 [%d]存放过久 [%d]待签收 [%d]运输中 [%d]待揽收 [%d]拒收 [%d]已签收\n",
				STATE_ERROR, STATE_STAY_LONG, STATE_WAIT_PICK, STATE_TRANSPORT, STATE_WAIT_COLLECT, STATE_REJECT, STATE_PICKUPED);
			printf("搜索框：");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			printf("\n\n");

			if (search[0] == ESC)//ESC检测
			{
				key = ERROR;//重置
				system("cls");
				break;//break switch
			}

			pack_search = AdminFindPackage(phead, search);
			if (pack_search != NULL)
			{
				//成功处理
				printf("键入[`]   编辑模式\n");
				printf("键入[空格] 重新搜索\n\n");
				
				printf("共查询到 %d 个结果，以下显示部分数据，进入编辑模式查看更多.\n", CountPackage(pack_search));
				PrintNumPackage(pack_search, PAGE_NUM);
				printf("\n");
				PrintAllPackage(phead);

				//键入检测
				while (TRUE)
				{
					InputBox(&key, 1, MODE_KEY, ON);
					if (key == ESC)
					{
						//重置
						key = ERROR;
						system("cls");
						break;
					}
					if (key == '`')
					{
						EditPackage(pack_search);//进入编辑模式
						key = '1';//重置为重新搜索
						break;
					}
					if (key == ' ')
					{
						key = '1';//重置为重新搜索
						break;
					}
				}
			}
			else
			{
				//失败处理
				printf("无结果......\n\n");
				system("pause");//静默等待
			}

			system("cls");

			break;//break switch
		}
		//查询货架
		case '2':
		{
			system("cls");
			printf("<查询货架>\n");
			printf("按下[ESC]返回\n");
			PrintAllShelf();
			printf("\n");

			printf("输入范例： A0_1,2  D4_3,4\n");
			printf("输入框：");
			InputBox(search, MAX_LOCATION, MODE_SHOW, ON);

			if (search[0] == ESC)//ESC检测
			{
				//重置
				key = ERROR;
				system("cls");
				break;
			}

			shelf* theShelf = StrToShelf(search);

			if (theShelf == NULL)
			{
				printf("输入的货架格式不正确，请重试！\n");
				system("pause");
				//重试
				//key = ERROR;
				system("cls");
				break;
			}

			printf("%s 的状态如下：\n", search);
			char shelf_state[5];
			TFtoStr(shelf_state, theShelf->used);
			printf("是否被占用：%s\n", shelf_state);
			printf("占用的包裹运单号：%s\n", theShelf->pack_id);
			system("pause");//静默等待
			system("cls");
			break;//break switch
		}
		//查询用户
		case '3':
		{
			system("cls");
			printf("<查询用户>\n");
			printf("按下[ESC]返回\n");
			printf("搜索框：");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			printf("\n");

			if (search[0] == ESC)//ESC检测
			{
				key = ERROR;//重置
				system("cls");
				break;//break switch
			}

			user_search = FindUser(uhead, search);//查询结果
			if (user_search != NULL)
			{
				//成功处理
				PrintOneUser(user_search);
			}
			else
			{
				//失败处理
				printf("无结果......\n");
			}

			system("pause");//静默等待
			system("cls");

			break;//break switch
		}
		//查询历史包裹
		case '4':
		{
			system("cls");
			printf("<查询历史记录>\n");
			printf("[ESC]退出\n");
			printf("格式eg：20060105\n");
			printf("请输入——\n");
			//输入1
			printf("起始日期：");
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
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			//数据转换
			int dataNum = atof(search);			//eg:20060105
			if (dataNum < 0)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			struct tm data1 = { 0 };
			data1.tm_year = dataNum / 10000;	//没法用MAX_DATA算出来——请注意
			data1.tm_mon = (dataNum % 10000) / 100;
			data1.tm_mday = dataNum % 100;
			if (12 < data1.tm_mon)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			if (DaysInMonth(data1.tm_year, data1.tm_mon) < data1.tm_mday)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			//输入2
			printf("终止日期：");
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
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			//数据转换
			dataNum = atof(search);				//eg:20060105
			if (dataNum < 0)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			struct tm data2 = { 0 };
			data2.tm_year = dataNum / 10000;	//没法用MAX_DATA算出来——请注意
			data2.tm_mon = (dataNum % 10000) / 100;
			data2.tm_mday = dataNum % 100;
			if (12 < data2.tm_mon)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}
			if (DaysInMonth(data2.tm_year, data2.tm_mon) < data2.tm_mday)
			{
				printf("输入格式有误，请重试！\n");
				system("pause");
				system("cls");
				break;
			}

			//正式查询
			ReadPackHis(&data1, &data2);
			system("pause");

			//key = ERROR;
			system("cls");
			break;
		}
		//录入包裹
		case '5':
		{
			package* pack = CreatOnePackage();//创建空白包裹
			//界面写在了EnterPackage()里面
			if (EnterPackage(pack) == FALSE)//输入信息
			{
				//失败处理
				key = ERROR;//重置
				free(pack);
				system("cls");
				continue;
			}
			//成功处理
			AddOnePackage(phead, pack); //加入链表
			printf("\n录入成功！\n");
			PrintOnePackage(pack); //回显全部信息

			system("pause");//静默等待
			system("cls");

			break;//break switch
		}
		//包裹入库
		case '6':
		{
			system("cls");
			printf("<包裹入库>\n");
			printf("按下[ESC]返回\n");
			printf("运单号：");
			InputBox(search, MAX_ID, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (FALSE == JungePackageInformation(ID, search))
			{
				printf("\n输入的运单号格式错误，请重试\n");
				system("pause");
				system("cls");
				break;
			}
			pack_search = AdminFindPackage(phead, search);
			if (NULL == pack_search)
			{
				printf("\n输入的运单号不存在，请重试\n");
				system("pause");
				system("cls");
				break;
			}
			printf("\n找到如下包裹，请确认.\n");
			PrintOnePackage(pack_search);
			printf("\n确定入库？\n");
			printf("[y/n]\n");
			InputBox(search, 1, MODE_KEY, OFF);
			if (search[0] != 'y')
			{
				printf("已取消入库...\n");
				printf("正在返回...\n");
				system("pause");
				system("cls");
				break;
			}
			if (pack_search->state == STATE_WAIT_PICK)
			{
				printf("请勿重复入库！\n");
				printf("正在返回......\n");
				system("pause");
				system("cls");
				break;
			}
			if (FALSE == AllocateLocation(pack_search, ahead))
			{
				printf("入库失败...\n");
				printf("货架已满，请检查！\n");
				printf("正在返回...\n");
				system("pause");
				system("cls");
				break;
			}
			user* temUser = FindUser(uhead, pack_search->tele_num);
			if (temUser != NULL)
			{
				message* mess = CreatOneMessage("", IMP_NORMAL);
				sprintf(mess->content, "你的包裹（%s）待签收", pack_search->pack_name);
				AddMessage(temUser->mlist, mess);
			}
			printf("入库成功！\n");
			printf("成功将包裹发配到：%s\n", pack_search->location);
			printf("正在返回...\n");
			system("pause");
			system("cls");
			break;//break switch
		}
		//广播
		case '7':
		{
			system("cls");
			printf("按下[ESC]返回\n");
			printf("请输入广播消息：");
			InputBox(search, MAX_SEARCH_LENGTH, MODE_SHOW, ON);
			if (search[0] == ESC)//ESC检测
			{
				//重置
				key = ERROR;
				system("cls");
				break;
			}
			//确认？
			printf("\n确定广播如上消息？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key != 'y')
			{
				key = '6';
				system("cls");
				break;
			}
			//正式广播
			message* mess = CreatOneMessage(search, IMP_SPECIAL);
			Broadcast(mess, uhead);//广播至用户
			printf("\n广播成功！\n");
			printf("正在返回...\n");
			key = '6';
			system("pause");
			system("cls");
			break;//break switch
		}
		//管理员个人信息修改
		case '8':
		{
			system("cls");
			printf("<修改个人信息>\n");
			printf("按下[ESC]返回\n");
			PrintOneUser(admin);
			printf("\n是否要修改？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				ModifyUserInterface(admin);
			}
			else
				//重置
				key = ERROR;
			system("cls");

			break;//break switch
		}
		//保存选项
		case '9':
		{
			SaveOption();
			key = ERROR;
			system("cls");
			break;
		}
		//退出登陆
		case 'q':
		{
			system("cls");
			printf("退出登陆？\n");
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				//空置logoutTime记录
				ClearLogout();
				//重返登陆
				powerTag = RESTART;
				return;
			}
			else
			{
				//重置
				key = ERROR;
				system("cls");
				break;//break switch
			}

		}
		}//end switch

		//Sleep(500);//系统响应时间 单位为ms 过快会有闪烁问题->闪烁问题已解决
		
	}//end while
}


//手动录入包裹 成功返回TRUE 失败返回FALSE
int EnterPackage(package* pack)
{
	system("cls");
	if (pack == NULL)
	{
		printf("非法传入了NULL指针！(ModifyPackage)\n");
		system("pause");
		return FALSE;
	}

	//准备工作
	char key = ERROR;
	//配置入库时间
	//struct tm* nowTime = GetNowTime();
	//SetPackageInTime(pack, nowTime->tm_year, nowTime->tm_mon, nowTime->tm_mday);

	//消息循环
	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);

		//界面
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");
		printf("<录入模式>\n");
		PrintOnePackage(pack);

		printf("\n按下如下按键选择编辑\n");
		printf("[ESC]退出\n");
		printf("[%c]确认录入完毕\n", ALLRIGHT);
		printf("[%c]填写规则\n\n", RULE);

		//录入模式新增
		printf("[%c]运单号\n", ID);
		printf("[%c]包裹名称\n", PACK_NAME);
		printf("[%c]存放地点(选填)\n", LOCATION);
		printf("[%c]取件码(选填)\n", PICKCODE);
		//

		printf("[%c]包裹状态\n\n", STATE);

		printf("[%c]手机号\n", TELE);
		printf("[%c]收件人名称\n", USER);
		printf("[%c]寄件人名称\n", SENDER);
		printf("[%c]收件人地址\n", USER_ADDR);
		printf("[%c]寄件人地址\n\n", SENDER_ADDR);

		printf("[%c]运费\n", BILL);
		printf("[%c]重量\n", WEIGHT);
		printf("[%c]体积\n", SIZE);
		printf("[%c]偏远地区\n", FAR_AREA);
		printf("[%c]易碎品\n", FRAG);
		printf("[%c]贵重品\n\n", VALU);


		//提醒自己：以下信息不可改
		//1.运单号
		//2.出入库时间
		//3.取件码
		//4.包裹名称

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//消息判断
		switch (key)
		{
			//无响应
		case ERROR:
		{
			break;//break switch
		}
		//确认录入
		case ALLRIGHT:
		{
			system("cls");
			printf("系统将自动检测录入数据是否合规\n");
			printf("是否录入完毕？\n");
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
					printf("\n存在填写错误，请检查\n");
					system("pause");
					//重置
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
		//退出
		case ESC:
		{
			system("cls");
			printf("输入的数据将丢失\n");
			printf("是否结束录入？\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				return FALSE;
			}
			else
			{
				//重置
				key = ERROR;
				system("cls");
				break;//break switch
			}
		}

		//输出填写规则
		case RULE:
		{
			system("cls");
			PrintInputRule();
			system("pause");//静默等待
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}

		//录入模式新增
		//运单号
		case ID:
		{
			system("cls");
			printf("原运单号：%s\n", pack->id);
			ModifyPackage(pack, key, "运单号", MODE_NUM, MAX_ID);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//包裹名称
		case PACK_NAME:
		{
			system("cls");
			printf("原包裹名称：%s\n", pack->pack_name);
			ModifyPackage(pack, key, "包裹名称", MODE_SHOW, MAX_PACK_NAME);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//存放地址
		case LOCATION:
		{
			system("cls");
			printf("原存放地址：%s\n", pack->location);
			ModifyPackage(pack, key, "存放地址", MODE_SHOW, MAX_LOCATION);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//取件码
		case PICKCODE:
		{
			system("cls");
			printf("原取件码：%s\n", pack->pickupCode);
			ModifyPackage(pack, key, "取件码", MODE_SHOW, MAX_PICKUP_CODE);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//新增结束

		//修改包裹状态
		case STATE:
		{
			system("cls");
			ModifyState(pack);
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//修改手机号
		case TELE:
		{
			system("cls");
			printf("原手机号：%s\n", pack->tele_num);
			ModifyPackage(pack, key, "手机号", MODE_NUM, MAX_TELE_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改收件人名称
		case USER:
		{
			system("cls");
			printf("原收件人名称：%s\n", pack->user_name);
			ModifyPackage(pack, key, "收件人名称", MODE_SHOW, MAX_USER_NAME);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改寄件人名称
		case SENDER:
		{
			system("cls");
			printf("原寄件人名称：%s\n", pack->sender_name);
			ModifyPackage(pack, key, "寄件人名称", MODE_SHOW, MAX_USER_NAME);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改收件人地址
		case USER_ADDR:
		{
			system("cls");
			printf("原收件人地址：%s\n", pack->user_address);
			ModifyPackage(pack, key, "收件人地址", MODE_SHOW, MAX_ADDRESS);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改寄件人地址
		case SENDER_ADDR:
		{
			system("cls");
			printf("原寄件人地址：%s\n", pack->send_address);
			ModifyPackage(pack, key, "寄件人地址", MODE_SHOW, MAX_ADDRESS);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改运费
		case BILL:
		{
			system("cls");
			printf("原运费：%f 元\n", pack->Bill);
			ModifyPackage(pack, key, "运费", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改重量
		case WEIGHT:
		{
			system("cls");
			printf("原重量：%f kg\n", pack->weight);
			ModifyPackage(pack, key, "重量", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改体积
		case SIZE:
		{
			system("cls");
			printf("原体积：%f cm^3\n", pack->size);
			ModifyPackage(pack, key, "体积", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改偏远地区
		case FAR_AREA:
		{
			system("cls");
			printf("原偏远地区：%d\n", pack->isRemoteArea);
			ModifyPackage(pack, key, "偏远地区(0为否,1为是)", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改易碎品
		case FRAG:
		{
			system("cls");
			printf("原易碎品：%d\n", pack->isFragile);
			ModifyPackage(pack, key, "易碎品(0为否,1为是)", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改珍贵品
		case VALU:
		{
			system("cls");
			printf("原贵重物品：%d\n", pack->isValuable);
			ModifyPackage(pack, key, "珍贵品(0为否,1为是)", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}

		}//end switch
	}//end while
}

//管理员编辑查询到的包裹
void EditPackage(package* head)
{
	//首先清屏
	system("cls");

	//NULL检测
	if (head == NULL)
	{
		return;
	}

	//自动忽略哨兵head
	if (head->prior == NULL)
		head = head->next;

	//NULL检测
	if (head == NULL)
	{
		printf("无包裹信息\n");
		system("pause");
		return;
	}

	//预备工作
	char key = ERROR;		//键入
	int i = ERROR;			//辅助变量 无实意
	package* point = head;  //游标
	package* tmp = NULL;	//试探游标

	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);
		tmp = NULL;
		i = ERROR;

		//界面		
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");

		printf("<编辑包裹模式>\n");
		printf("按下[ESC]返回\n");
		printf("按下[a/d]换页\n");
		printf("按下[1 2 3 4 5]选择\n\n");

		//打印
		PrintNumPackage(point, PAGE_NUM);

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}


		//消息循环
		switch (key)
		{
		//无响应
		case ERROR:
		{
			break;
		}
		//退出
		case ESC:
		{
			system("cls");
			printf("退出编辑？\n [y/n]\n");
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
		//左一页
		case BUTTON_LEFT: 
		{
			tmp = point;
			for (i = 0; i < PAGE_NUM && tmp->prior != NULL; i++)//防止走到头
			{
				tmp = tmp->prior;
			}
			if (i == PAGE_NUM)//保证走满PAGE_NUM次数
			{
				point = tmp;
			}

			//重置
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//右一页
		case BUTTON_RIGHT: 
		{
			tmp = point;
			for (i = 0; i < PAGE_NUM && tmp->next != NULL; i++)//防止走到头
			{
				tmp = tmp->next;
			}
			if (i == PAGE_NUM)//保证走满page_num次数
			{
				point = tmp;
			}

			//重置
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//选择
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
			//进入界面
			if (tmp != NULL)
				ModifyPackageInterface(tmp);
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		}//end switch

	}//end while
}

//顶级管理员编辑查询到的次级管理员
void EditAdmin(user* head)
{
	//首先清屏
	system("cls");

	//NULL检测
	if (head == NULL)
	{
		return;
	}

	//自动忽略哨兵head
	if (head->prior == NULL)
		head = head->next;

	//NULL检测
	if (head == NULL)
	{
		return;
	}

	//预备工作
	char key = ERROR;		//键入
	int i = ERROR;			//辅助变量 无实意
	user* point = head;  //游标
	user* tmp = NULL;	//试探游标

	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);
		tmp = NULL;
		i = ERROR;

		//界面		
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");

		printf("<编辑管理员用户模式>\n");
		printf("按下[ESC]返回\n");
		printf("按下[a/d]换页\n");
		printf("按下[1 2 3 4 5]选择\n\n");

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//打印
		PrintNumAdmin(point, ADMIN_NUM);

		//消息循环
		switch (key)
		{
			//无响应
		case ERROR:
		{
			break;
		}
		//退出
		case ESC:
		{
			system("cls");
			printf("退出编辑？\n [y/n]\n");
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
		//左一页
		case BUTTON_LEFT:
		{
			tmp = point;
			for (i = 0; i < ADMIN_NUM && tmp->prior != NULL; i++)//防止走到头
			{
				tmp = tmp->prior;
			}
			if (i == ADMIN_NUM)//保证走满PAGE_NUM次数
			{
				point = tmp;
			}

			//重置
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//右一页
		case BUTTON_RIGHT:
		{
			tmp = point;
			for (i = 0; i < ADMIN_NUM && tmp->next != NULL; i++)//防止走到头
			{
				tmp = tmp->next;
			}
			if (i == ADMIN_NUM)//保证走满page_num次数
			{
				point = tmp;
			}

			//重置
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//选择
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
			//进入界面
			if (tmp != NULL)
				ModifyAdminInterface(tmp);
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		}//end switch

	}//end while

}

//选择性修改包裹-界面
void ModifyPackageInterface(package* pack)
{
	system("cls");
	if (pack == NULL)
	{
		printf("非法传入了NULL指针！(ModifyPackage)\n");
		system("pause");
	}

	//准备工作
	char key = ERROR;

	//消息循环
	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);

		//界面
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");
		printf("<修改包裹模式>\n");
		PrintOnePackage(pack);

		printf("\n按下如下按键选择编辑\n");
		printf("[ESC]退出\n");
		printf("[%c]填写规则\n\n",RULE);

		printf("[%c]包裹状态\n\n",STATE);

		printf("[%c]手机号\n",TELE);
		printf("[%c]收件人名称\n",USER);
		printf("[%c]寄件人名称\n",SENDER);
		printf("[%c]收件人地址\n",USER_ADDR);
		printf("[%c]寄件人地址\n\n",SENDER_ADDR);

		printf("[%c]运费\n",BILL);
		printf("[%c]重量\n",WEIGHT);
		printf("[%c]体积\n",SIZE);
		printf("[%c]偏远地区\n",FAR_AREA);
		printf("[%c]易碎品\n",FRAG);
		printf("[%c]贵重品\n",VALU);
		printf("[%c]送货上门\n\n",TODOOR);


		//提醒自己：以下信息不可改
		//1.运单号
		//2.出入库时间
		//3.取件码
		//4.包裹名称

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//消息判断
		switch (key)
		{
		//无响应
		case ERROR:
		{
			break;//break switch
		}
		//退出
		case ESC:
		{
			system("cls");
			printf("\n退出修改模式？\n");
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

		//输出填写规则
		case RULE:
		{
			system("cls");
			PrintInputRule();
			system("pause");//静默等待
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}

		//修改包裹状态
		case STATE:
		{
			system("cls");
			ModifyState(pack);
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//修改手机号
		case TELE:
		{
			system("cls");
			printf("原手机号：%s\n", pack->tele_num);
			ModifyPackage(pack, key, "手机号", MODE_NUM, MAX_TELE_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改收件人名称
		case USER:
		{
			system("cls");
			printf("原收件人名称：%s\n", pack->user_name);
			ModifyPackage(pack, key, "收件人", MODE_SHOW, MAX_USER_NAME);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改寄件人名称
		case SENDER:
		{
			system("cls");
			printf("原寄件人名称：%s\n", pack->sender_name);
			ModifyPackage(pack, key, "寄件人名称", MODE_SHOW, MAX_USER_NAME);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改收件人地址
		case USER_ADDR:
		{
			system("cls");
			printf("原收件人地址：%s\n", pack->user_address);
			ModifyPackage(pack, key, "收件人地址", MODE_SHOW, MAX_ADDRESS);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改寄件人地址
		case SENDER_ADDR:
		{
			system("cls");
			printf("原寄件人地址：%s\n", pack->send_address);
			ModifyPackage(pack, key, "寄件人地址", MODE_SHOW, MAX_ADDRESS);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改运费
		case BILL:
		{
			system("cls");
			printf("原运费：%f 元\n", pack->Bill);
			ModifyPackage(pack, key, "运费", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改重量
		case WEIGHT:
		{
			system("cls");
			printf("原重量：%f kg\n", pack->weight);
			ModifyPackage(pack, key, "重量", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改体积
		case SIZE:
		{
			system("cls");
			printf("原体积：%f cm^3\n", pack->size);
			ModifyPackage(pack, key, "体积", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改偏远地区
		case FAR_AREA:
		{
			system("cls");
			printf("原偏远地区：%d\n", pack->isRemoteArea);
			ModifyPackage(pack, key, "偏远地区(0为否,1为是)", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改易碎品
		case FRAG:
		{
			system("cls");
			printf("原易碎品：%d\n", pack->isFragile);
			ModifyPackage(pack, key, "易碎品(0为否,1为是)", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改珍贵品
		case VALU:
		{
			system("cls");
			printf("原贵重物品：%d\n", pack->isValuable);
			ModifyPackage(pack, key, "珍贵品(0为否,1为是)", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//修改送货上门
		case TODOOR:
		{
			system("cls");
			printf("原送货上门：%d\n", pack->isToDoor);
			ModifyPackage(pack, key, "送货上门(0为否,1为是)", MODE_NUM, MAX_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		}//end switch
	}//end while

}

//判断输入的包裹信息是否符合规定-选择性修改包裹函数的深层函数
int JungePackageInformation(const char key,const char* input)
{
	switch (key)
	{
	//运单号
	case ID:
	{
		if (strlen(input) != MAX_ID
			|| isAllDigits(input) == FALSE)
		{
			return FALSE;
		}
		break;//break switch
	}
	//存放位置
	case LOCATION:
	{
		//注意：不用检测空白
		if (strlen(input) != 0)
		{
			//判断输入格式
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
			//判断是否被占用
			//else if (shelfs[input[0] - 'A'][input[1] - '0'][input[3] - '0'][input[5] - '0'].used == TRUE)
			//{
			//	return FALSE;
			//}
		}
		break;//break switch
	}
	//取件码
	case PICKCODE:
	{
		if (strlen(input) != MAX_PICKUP_CODE
			|| isAllDigits(input) == FALSE)
		{
			return FALSE;
		}
		break;//break switch
	}
	//手机号
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
	//人名、地址、包裹名称
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
	//运费 及其计算参数
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

//选择性修改包裹-深层函数
int ModifyPackage(package* pack, const char _key, const char* information,const int inputMode,const int MaxLen)
{
	//准备工作
	char input[MAX_SEARCH_LENGTH];
	char key = ERROR;
	memset(input, 0, MAX_SEARCH_LENGTH);

	//输入
	printf("新%s：", information);
	InputBox(input, MaxLen, inputMode, ON);

	//退出
	if (input[0] == ESC)
	{
		return FALSE;
	}

	//判断格式
	if (!(JungePackageInformation(_key, input)))
	{
		//重置
		printf("\n修改失败...\n");//不知道为啥第一个字不显示
		system("pause");
		system("cls");

		return FALSE;
	}

	//确认修改
	printf("\n确认修改？\n");
	printf("[y/n]\n");
	InputBox(&key, 1, MODE_KEY, ON);
	if (key != 'y')
	{
		printf("\n已取消修改\n");
		system("pause");
		system("cls");
		return FALSE;
	}

	//正式修改
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
	printf("\n新%s 修改成功!\n", information);
	system("pause");
	system("cls");

	return TRUE;
}

//修改包裹状态
void ModifyState(package* pack)
{
	//准备工作
	system("cls");
	if (pack == NULL)
	{
		printf("非法传入了NULL指针！(ModifyState)\n");
		system("pause");
	}
	char key = ERROR;
	char input[MAX_SEARCH_LENGTH];
	char state[MAX_STATE];
	memset(state, 0, MAX_STATE);
	StateToStr(state, pack->state);

	//消息循环
	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);
		memset(input, 0, MAX_SEARCH_LENGTH);

		//界面
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");
		printf("<修改包裹状态>\n");
		printf("按下[ESC]返回\n\n");

		printf("现状态：%s\n\n", state);

		printf("请输入数字\n");
		printf("[%d]异常（滞留、运输失败等）\n",STATE_ERROR);
		printf("[%d]滞留过久\n\n",STATE_STAY_LONG);
		printf("[%d]待签收\n",STATE_WAIT_PICK);
		printf("[%d]运输中\n",STATE_TRANSPORT);
		printf("[%d]待揽收\n",STATE_WAIT_COLLECT);
		printf("[%d]拒收\n",STATE_REJECT);
		printf("[%d]已签收\n",STATE_PICKUPED);

		printf("新包裹状态:");

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
		//退出
		case ESC:
		{
			system("cls");
			return;
			//printf("退出？\n [y/n]\n");
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
		//选择状态数值->数字必须一一对应枚举类型
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
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		}//end switch
	}//end while
}



//选择行修改个人信息-界面
int ModifyUserInterface(user* user)
{
	system("cls");
	if (user == NULL)
	{
		printf("非法传入了NULL指针！(ModifyUser)\n");
		system("pause");
	}

	//准备工作
	char key = ERROR;
	char input[MAX_SEARCH_LENGTH];
	memset(input, 0, MAX_SEARCH_LENGTH);

	//消息循环
	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);
		memset(input, 0, MAX_SEARCH_LENGTH);

		//界面
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");
		printf("<修改个人信息模式>\n");
		PrintOneUser(user);

		printf("\n按下如下按键选择编辑\n");
		printf("[ESC]退出\n");
		printf("[%c]填写规则\n\n", RULE);

		printf("[%c]名称\n", NAME);
		printf("[%c]手机号\n", TELENUM);
		printf("[%c]密码\n\n", PASSWORD);

		printf("[%c]默认地址\n", DEFUALT_ADDR);
		printf("[%c]地址_1\n", ADDR_1);
		printf("[%c]地址_2\n", ADDR_2);
		printf("[%c]地址_3\n\n", ADDR_3);

		printf("[%c]注销账号\n\n", CANCEL);

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//消息循环
		switch (key)
		{
			//无响应
		case ERROR:
		{
			break;//break switch
		}

		//输出填写规则
		case RULE:
		{
			system("cls");
			PrintInputRule();
			system("pause");//静默等待
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//退出
		case ESC:
		{
			system("cls");
			printf("\n退出修改模式？\n");
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

		//名称
		case NAME:
		{
			system("cls");
			printf("原名称：%s\n", user->name);
			ModifyUser(user, key, "名称", MODE_SHOW, MAX_USER_NAME);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//手机号
		case TELENUM:
		{
			system("cls");
			printf("原手机号：%s\n", user->tele_num);
			ModifyUser(user, key, "手机号", MODE_SHOW, MAX_TELE_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//密码
		case PASSWORD:
		{
			system("cls");
			printf("原密码：%s\n", user->password);
			ModifyUser(user, key, "密码", MODE_SHOW, MAX_PASSWORD_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//默认地址
		case DEFUALT_ADDR:
		{
			system("cls");
			ModifyDefaulatAddress(user);
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//地址_1
		case ADDR_1:
		{
			system("cls");
			printf("原地址_1：%s\n", user->address_1);
			ModifyUser(user, key, "地址_1", MODE_SHOW, MAX_ADDRESS);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//地址_2
		case ADDR_2:
		{
			system("cls");
			printf("原地址_2：%s\n", user->address_2);
			ModifyUser(user, key, "地址_2", MODE_SHOW, MAX_ADDRESS);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//地址_3
		case ADDR_3:
		{
			system("cls");
			printf("原地址_3：%s\n", user->address_3);
			ModifyUser(user, key, "地址_3", MODE_SHOW, MAX_ADDRESS);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//注销账号
		case CANCEL:
		{
			system("cls");
			printf("\n是否注销账号？\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				if (user->level == TOP_ADMIN
					|| user->level == ADMIN)
				{
					printf("\n管理员不能主动注销自己的账号！\n");
					system("pause");
					//重置
					key = ERROR;
					system("cls");
					break;//break switch
				}
				DeleteOneUser(user);
				printf("\n注销成功！\n");
				printf("即将退出系统\n");
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

//选择性修改管理员-界面
void ModifyAdminInterface(user* admin)
{
	system("cls");
	if (admin == NULL)
	{
		printf("非法传入了NULL指针！(ModifyAdminInterface)\n");
		system("pause");
	}

	//准备工作
	char key = ERROR;
	char input[MAX_SEARCH_LENGTH];
	memset(input, 0, MAX_SEARCH_LENGTH);

	//消息循环
	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);
		memset(input, 0, MAX_SEARCH_LENGTH);

		//界面
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");
		printf("<修改管理员个人信息模式>\n");
		PrintOneAdmin(admin);

		printf("\n按下如下按键选择编辑\n");
		printf("[ESC]退出\n");
		printf("[%c]填写规则\n\n", RULE);

		printf("[%c]名称\n", NAME);
		printf("[%c]手机号\n", TELENUM);
		printf("[%c]密码\n\n", PASSWORD);

		printf("[%c]注销\n\n", CANCEL);

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//消息循环
		switch (key)
		{
			//无响应
		case ERROR:
		{
			break;//break switch
		}

		//输出填写规则
		case RULE:
		{
			system("cls");
			PrintInputRule();
			system("pause");//静默等待
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//退出
		case ESC:
		{
			system("cls");
			printf("\n退出修改模式？\n");
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

		//名称
		case NAME:
		{
			system("cls");
			printf("原名称：%s\n", admin->name);
			ModifyUser(admin, key, "名称", MODE_SHOW, MAX_USER_NAME);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//手机号
		case TELENUM:
		{
			system("cls");
			printf("原手机号：%s\n", admin->tele_num);
			ModifyUser(admin, key, "手机号", MODE_SHOW, MAX_TELE_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//密码
		case PASSWORD:
		{
			system("cls");
			printf("原密码：%s\n", admin->password);
			ModifyUser(admin, key, "密码", MODE_SHOW, MAX_PASSWORD_NUM);
			//重置 (成功与否均重置）
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//注销账号
		case CANCEL:
		{
			system("cls");
			printf("\n是否注销账号？\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, OFF);
			if (key == 'y')
			{
				DeleteOneUser(admin);
				printf("\n注销成功！\n");
				system("pause");
				//这里不用Exit
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

//选择默认地址
void ModifyDefaulatAddress(user* user)
{
	//准备工作
	system("cls");
	if (user == NULL)
	{
		printf("非法传入了NULL指针！(ModifyDefaulatAddress)\n");
		system("pause");
	}
	char key = ERROR;
	char input[MAX_SEARCH_LENGTH];

	//消息循环
	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);
		memset(input, 0, MAX_SEARCH_LENGTH);
		//界面
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");
		printf("<修改默认地址>\n");
		printf("按下[ESC]返回\n\n");

		printf("现地址：%s\n\n", user->address_default);

		printf("输入数字进行选择\n");
		printf("[1] %s\n", user->address_1);
		printf("[2] %s\n", user->address_2);
		printf("[3] %s\n\n", user->address_3);

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
		//退出
		case ESC:
		{
			system("cls");
			return;
			//printf("退出？\n [y/n]\n");
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
		//选择
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

//选择性修改用户-深层函数
int ModifyUser(user* user, const char _key, const char* information, const int inputMode, const int MaxLen)
{
	//准备工作
	char input[MAX_SEARCH_LENGTH];
	char key = ERROR;
	memset(input, 0, MAX_SEARCH_LENGTH);

	//输入
	printf("新%s：", information);
	InputBox(input, MaxLen, inputMode, ON);

	//退出
	if (input[0] == ESC)
	{
		return FALSE;
	}

	//判断格式
	if (!(JungeUserInformation(_key, input)))
	{
		//重置
		printf("\n格式不正确或已存在，修改失败...\n");//不知道为啥第一个字不显示
		system("pause");
		system("cls");

		return FALSE;
	}

	//确认修改
	printf("\n确认修改？\n");
	printf("[y/n]\n");
	InputBox(&key, 1, MODE_KEY, ON);
	if (key != 'y')
	{
		printf("\n已取消修改\n");
		system("pause");
		system("cls");
		return FALSE;
	}

	//正式修改
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
	printf("\n新%s 修改成功!\n", information);
	system("pause");
	system("cls");

	return TRUE;
}

//判断个人信息函数
int JungeUserInformation(const char key, const char* input)
{
	switch (key)
	{
		//名称、密码、地址
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
	//手机号
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

//修改货架状态
void ModifyShelf(shelf* theShelf)
{
	while(TRUE)
	{
		//准备工作
		system("cls");
		char key = ERROR;
		char input[MAX_ID + 1];
		char TF[MAX_TF + 1];
		memset(input, 0, sizeof(input));
		memset(TF, 0, sizeof(TF));
		TFtoStr(TF, theShelf->used);

		printf("<修改货架界面>\n");
		printf("[ESC]返回\n");
		printf("当前目标：%s\n", theShelf->location);
		printf("占用状态：%s\n", TF);
		printf("占用的包裹运单号：%s\n\n", theShelf->pack_id);

		printf("键入修改：\n");
		printf("[1]状态\n");
		printf("[2]运单号\n");

		InputBox(&key, 1, MODE_KEY, ON);
		if (key == ESC)return;

		switch (key)
		{
		case '1':
		{
			system("cls");
			printf("[ESC]返回\n");
			printf("请输入—— 1 是，0 否\n");
			printf("原状态：%s\n", TF);
			printf("新状态：");
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
				printf("修改成功!\n");
				system("pause");
			}
			else
			{
				printf("修改失败...\n");
				system("pause");
			}
			break;
		}
		case '2':
		{
			system("cls");
			printf("[ESC]返回\n");
			printf("原运单号：%s\n", theShelf->pack_id);
			printf("新运单号：");
			InputBox(input, MAX_ID, MODE_NUM, ON);
			if (input[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (!JungePackageInformation(ID, input))
			{
				printf("\n输入的运单号格式错误，请重试！\n");
				system("pause");
				break;
			}

			strcpy(theShelf->pack_id, input);
			printf("\n设置完毕\n");
			system("pause");
			break;
		}
		}//end switch
	}//end while
}

//内购管理
void ManagePay()
{
	system("cls");
	char key = ERROR;

	while(TRUE)
	{
		SetCursorPosition(0, 0);
		printf("当前时间：");
		PrintNowTime();
		printf("\n");
		printf("<内购管理>\n");

		printf("[ESC]退出\n");
		printf("[1]发行优惠券\n");
		printf("[2]管理已发行优惠券\n");

		//即时键入识别
		if (_kbhit())//防止时间停滞
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

//发行优惠券
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

		printf("当前时间：");
		PrintNowTime();
		printf("\n");
		printf("<发行优惠券>\n");

		printf("新优惠券信息：\n");
		PrintOneCoupon(theCoupon);
		printf("\n");

		printf("[ESC]退出/删除\n");
		printf("[%c]发行\n", ALLRIGHT);
		printf("[1]内容\n");
		printf("[2]倍率\n");
		printf("[3]时效\n");
		printf("[4]价格\n");

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		switch (key)
		{
		case ERROR:break;
		case ESC:
		{
			system("cls");
			printf("确定退出?\n");
			printf("将丢失所有输入数据\n");
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
				printf("输入的内容有误，请重试！\n");
				key = ERROR;
				system("pause");
				system("cls");
				break;
			}
			PrintOneCoupon(theCoupon);
			printf("确定发行/重新发行？\n[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key != 'y')
			{
				key = ERROR;
				system("cls");
				break;
			}
			AddCoupon(chead, theCoupon);
			printf("发行成功！\n按任意键退出\n");
			PrintOneCoupon(theCoupon);
			printf("\n");
			system("pause");
			system("cls");
			return;
		}
		case '1':
		{
			system("cls");
			printf("[ESC]返回\n");
			printf("旧内容：%s", theCoupon->content);
			printf("\n新内容：");
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
			printf("[ESC]返回\n");
			printf("旧倍率：%f", theCoupon->rate);
			printf("\n新倍率：");
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
			printf("[ESC]返回\n");
			printf("旧时效（单位:月)：%d", theCoupon->timeLimit);
			printf("\n新时效（单位:月)：");
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
			printf("[ESC]返回\n");
			printf("旧价格：%d", theCoupon->cost);
			printf("\n新价格：");
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

//管理优惠券
void EditCoupon() 
{
	system("cls");
	char key = ERROR;
	int i = ERROR;
	coupon* point = chead->next;
	coupon* tmp = NULL;

	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);
		tmp = NULL;
		i = ERROR;

		//界面		
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");

		printf("<编辑已发行优惠券模式>\n");
		printf("按下[ESC]返回\n");
		printf("按下[a/d]换页\n");
		printf("按下[1 2 3 4 5]选择\n\n");

		//安全检查
		if (chead->next == NULL)
		{
			printf("无发行优惠券\n");
			system("pause");
			return;
		}

		//打印
		PrintNumCoupon(point, PAGE_NUM);

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}


		//消息循环
		switch (key)
		{
			//无响应
		case ERROR:
		{
			break;
		}
		//退出
		case ESC:return;
		//左一页
		case BUTTON_LEFT:
		{
			tmp = point;
			for (i = 0; i < PAGE_NUM && tmp->prior != NULL; i++)//防止走到头
			{
				tmp = tmp->prior;
			}
			if (i == PAGE_NUM)//保证走满PAGE_NUM次数
			{
				point = tmp;
			}

			//重置
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//右一页
		case BUTTON_RIGHT:
		{
			tmp = point;
			for (i = 0; i < PAGE_NUM && tmp->next != NULL; i++)//防止走到头
			{
				tmp = tmp->next;
			}
			if (i == PAGE_NUM)//保证走满page_num次数
			{
				point = tmp;
			}

			//重置
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//选择
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
			//进入界面
			if (tmp != NULL)
			{
				IssueCoupon(tmp);
				if (tmp == point)
					point = chead->next;
			}
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		}//end switch

	}//end while
}

//保存选项
void SaveOption()
{
	system("cls");
	char key = ERROR;

	while (TRUE)
	{
		//不用初始化key
		//不要在这里写cls
		SetCursorPosition(0, 0);

		//主界面
		//时间
		printf("<用户主界面>\n");
		printf("当前时间：");
		PrintNowTime();
		printf("\n");

		printf("[ESC]返回\n");
		printf("[1]手动保存\n");
		printf("[2]数据加密设定\n");
		printf("[3]历史加密设定\n");

		//即时键入识别
		if (_kbhit())//防止时间停滞
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
				printf("\n保存数据出错！\n");
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
			printf("当前数据加密状态：%s\n", TF);
			printf("输入(1为加密，0为非加密)");
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
			printf("当前历史加密状态：%s\n", TF);
			printf("输入(1为加密，0为非加密)");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			if (key == '0')
			{
				DecyrHis();//即刻解密
				hisCyrTag = DECYR;
			}
			if (key == '1')
			{
				CyrHis();//即刻加密
				hisCyrTag = CYR;
			}

			key = '3';
			break;
		}
		}
	}
}

//遍历包裹状态
void GoThroughPackage()
{
	package* point = phead->next;
	while (point != NULL)
	{
		if (point->state == STATE_ERROR)
		{
			message* mess = CreatOneMessage("", IMP_PACKERRO);
			sprintf(mess->content, "运单号%s的状态异常！", point->id);
			Broadcast(mess, ahead);
			free(mess);
		}
		if (point->state == STATE_STAY_LONG)
		{
			message* mess = CreatOneMessage("", IMP_STAYLONG);
			sprintf(mess->content, "运单号%s滞留过久！", point->id);
			Broadcast(mess, ahead);
			free(mess);
		}

		point = point->next;
	}
}
