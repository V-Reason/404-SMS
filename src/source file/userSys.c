#include "Frontend.h"

//用户操作系统
//1.取件 -> 取件码 -> 条形码？？？（计算机视觉）
//2.查询 -> KEY操作模式 翻页 选中
//3.寄件 -> 细节待定
//4.申报异常 -> 拒收...
//5.用户信息修改 -> ...
void UserSys(user* user)
{
	//初始化
	system("cls");
	char key = ERROR;					//接收单键输入
	char search[MAX_SEARCH_LENGTH + 1];	//接收字符串输入
	char complain[MAX_MESSAGE + 1];		//接受投诉内容
	memset(search, 0, sizeof(search));	//置零
	package* pack_search = NULL;
	struct tm* lastTime = GetNowTime();	//用于定时
	struct tm* nowTime = GetNowTime();	//用于定时

	//每日登陆
	if (logoutTime.tm_year != 0
		&& (logoutTime.tm_year != nowTime->tm_year
			|| logoutTime.tm_mon != nowTime->tm_mon
			|| logoutTime.tm_mday != nowTime->tm_mday))
	{
		//登陆奖励
		GainExp(EVENT_SignIn, user);
		//节日祝福
		festival* fes = isFestival();
		if (fes != NULL)
		{
			message* mess = CreatOneMessage("", IMP_SPECIAL);
			sprintf(mess->content, "%s 快乐！", fes->name);
			AddMessage(user->mlist, mess);
		}
	}

	while (TRUE)
	{
		//定时进行-保存+刷新优惠券
		nowTime = GetNowTime();
		if (AutoRegular__TimeSeg_S <= GetTimeSeg_Min(lastTime, nowTime))
		{
			UserRegular(user);
			lastTime = nowTime;
		}

		//不用初始化key
		//不要在这里写cls
		SetCursorPosition(0, 0);
		memset(search, 0, sizeof(search));
		pack_search = NULL;

		//主界面
		//时间
		printf("<用户主界面>\n");
		printf("当前时间：");
		PrintNowTime();
		//用户等级 经验
		printf("\n");
		int nextExp = (user->level + 1) * LEVEL_STEP;
		nextExp = nextExp > MAX_EXP ? nextExp : MAX_EXP;
		printf("用户等级：%d 级	用户经验：%d / %d",
			user->level, user->exp, nextExp);
		//通知
		printf("\n通知:\n");
		PrintNumMessage(user->mlist, MESS_NUM);
		printf("\n");
		//操作说明
		printf("按下对应按键以选择功能...\n\n");

		printf("[ESC]退出\n\n");

		printf("关于通知：\n");
		printf("[`]管理通知\n\n");

		printf("[0]内购\n");
		printf("[1]优惠券\n\n");

		printf("[2]查件\n");
		printf("[3]取件\n");
		printf("[4]寄件\n");
		printf("[5]查询历史包裹\n\n");

		printf("[6]投诉\n");
		printf("[7]修改个人信息\n");
		printf("[8]保存选项\n");
		printf("[9]退出登陆\n\n");

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
				RecordLogoutUser(user);
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
			MessSys(user);
			//重置
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//内购
		case '0':
		{
			//界面写在UserPay里面了
			UserPay(user);
			key = ERROR;
			system("cls");
			break;
		}
		//查看优惠券
		case '1':
		{
			CheckCoupon(user);
			key = ERROR;
			system("pause");
			system("cls");
			break;
		}
		//查件
		case '2':
		{
			system("cls");
			printf("<查件>\n");
			printf("按下[ESC]返回\n");

			pack_search = UserFindPackage(phead, user);
			if (pack_search != NULL)
			{
				//成功处理
				printf("键入[`] 拒收包裹界面\n\n");
				printf("键入[空格] 刷新\n\n");

				printf("共查询到 %d 个结果\n", CountPackage(pack_search));
				PrintAllPackage(pack_search);

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
					if (key == ' ')
					{
						key = '1';//重置为重新搜索
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
				//失败处理
				printf("无结果......\n\n");
				system("pause");//静默等待
			}

			system("cls");

			break;//break switch
		}
		//取件
		case '3':
		{
			system("cls");
			printf("<取件>\n");
			printf("按下[ESC]返回\n");

			//输入运单号
			printf("请输入运单号:");
			InputBox(search, MAX_ID, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				//重置
				key = ERROR;
				system("cls");
				break;
			}
			//判断格式
			if (FALSE == JungePackageInformation(ID, search))
			{
				printf("\n输入的运单号格式有误，请重试\n");
				system("pause");
				break;
			}
			//判断存在
			package* pack = AdminFindPackage(phead, search);
			if (FALSE == pack)
			{
				printf("\n输入的运单号不存在，请重试\n");
				system("pause");
				break;
			}
			//判断入库
			if (pack->state != STATE_WAIT_PICK)
			{
				printf("\n包裹尚未入库，请耐心等待！\n");
				system("pause");
				system("cls");
				break;
			}
			//输入取件码
			memset(search, 0, sizeof(search));
			printf("请输入取件码:");
			InputBox(search, MAX_PICKUP_CODE, MODE_NUM, ON);
			if (search[0] == ESC)
			{
				//重置
				key = ERROR;
				system("cls");
				break;
			}
			//判断取件码
			if (0 != strcmp(search, pack->pickupCode))
			{
				printf("\n取件码输入错误,请重试\n");
				system("pause");
				system("cls");
				break;
			}
			//取件手机号设置
			strcpy(pack->pick_tele_num, user->tele_num);
			//核对取件手机号-仅通知原主人
			if (strcmp(pack->tele_num, user->tele_num) != 0)
			{
				_User* oriUser = FindUser(uhead, pack->tele_num);
				if (oriUser != NULL)
				{
					message* mess = CreatOneMessage("", IMP_SPECIAL);
					sprintf(mess->content, "你的包裹(%s)被手机号尾号%s的用户代取了",
						pack->pack_name, &(user->tele_num[MAX_TELE_NUM - 4]));
					AddMessage(oriUser->mlist, mess);
				}
			}
			//取件成功
			GetShelf(pack);
			DeleteOnePackage(pack);
			printf("\n取件成功!\n");
			system("pause");
			//重置
			key = ERROR;
			system("cls");
			break;//break switch
		}
		//寄件
		case '4':
		{
			system("cls");
			printf("<寄件>\n");
			printf("按下[ESC]返回\n");
			printf("请依次填写以下内容：\n");

			package* pack = CreatOnePackage();//创建空白包裹

			if (SendPackage(user, pack) == FALSE)//输入信息
			{
				//失败处理
				key = ERROR;//重置
				free(pack);//删除空白包裹
				system("cls");
				break;
			}
			//成功处理
			AddOnePackage(phead, pack); //加入链表
			GainExp(EVENT_SendPack, user);//获得经验
			printf("\n寄件成功！\n");
			PrintOnePackage(pack); //回显全部信息

			system("pause");//静默等待
			system("cls");

			break;//break switch
		}
		//查询历史包裹
		case '5':
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
		//投诉
		case '6':
		{
			system("cls");
			printf("[ESC]返回\n");
			printf("请输入投诉内容(%d字以内)：", MAX_MESSAGE - 50);
			InputBox(complain, MAX_MESSAGE - 50, MODE_SHOW, ON);
			if (complain[0] == ESC)
			{
				key = ERROR;
				system("cls");
				break;
			}
			printf("\n确定投诉吗？\n[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key == 'y')
			{
				message* mess = CreatOneMessage("", IMP_USER);
				sprintf(mess->content, "用户[%s]投诉:%s", user->name, complain);
				Broadcast(mess, ahead);
				free(mess);
				printf("投诉成功！\n");
				key = ERROR;
				system("pause");
				system("cls");
				break;
			}
			printf("已取消投诉！\n");
			key = ERROR;
			system("pause");
			system("cls");
			break;
		}
		//用户个人信息修改
		case '7':
		{
			system("cls");
			printf("<修改个人信息>\n");
			printf("按下[ESC]返回\n");
			PrintOneUser(user);
			printf("\n是否要修改？\n");
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
				//重置
				key = ERROR;
			system("cls");

			break;//break switch
		}
		//保存选项
		case '8':
		{
			SaveOption();
			key = ERROR;
			system("cls");
			break;
		}
		//退出登陆
		case '9':
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

//用户邮寄包裹
int SendPackage(user* user, package* pack)
{
	system("cls");
	if (user == NULL || pack == NULL)
	{
		printf("非法传入了NULL指针！(ModifyPackage)\n");
		system("pause");
	}

	//准备工作
	char key = ERROR;
	//提前配置
	AssignId(pack);//运单号
	pack->state = STATE_WAIT_COLLECT;//状态->待揽收
	strcpy(pack->tele_num, user->tele_num);//手机号
	strcpy(pack->sender_name, user->name);//寄件人名称
	strcpy(pack->send_address, user->address_default);//寄件人地址


	//消息循环
	while (TRUE)
	{
		//不用重置key
		SetCursorPosition(0, 0);

		//界面
		printf("当前时间：");
		PrintNowTime();
		printf("\n\n");
		printf("<寄件>\n");
		PrintOnePackage(pack);

		printf("\n按下如下按键选择编辑\n");
		printf("[ESC]退出\n");
		printf("[%c]确认录入完毕(运费将自动计算)\n", ALLRIGHT);
		printf("[%c]填写规则\n", RULE);
		printf("[%c]运费计算规则\n\n", PAY_RULE);

		//录入模式新增
		//printf("[%c]运单号\n", ID);
		printf("[%c]包裹名称\n", PACK_NAME);
		//printf("[%c]存放地点(选填)\n", LOCATION);
		//printf("[%c]取件码(选填)\n", PICKCODE);
		//

		//printf("[%c]包裹状态\n\n", STATE);

		printf("[%c]手机号\n", TELE);
		printf("[%c]收件人名称\n", USER);
		printf("[%c]寄件人名称\n", SENDER);
		printf("[%c]收件人地址\n", USER_ADDR);
		printf("[%c]寄件人地址\n\n", SENDER_ADDR);

		//printf("[%c]运费\n", BILL);
		printf("[%c]重量\n", WEIGHT);
		printf("[%c]体积\n", SIZE);
		printf("[%c]偏远地区\n", FAR_AREA);
		printf("[%c]易碎品\n", FRAG);
		printf("[%c]贵重品\n", VALU);
		printf("[%c]送货上门\n\n", TODOOR);

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
					//&& JungePackageInformation(BILL, bill) 运费后面算
					&& JungePackageInformation(WEIGHT, weight)
					&& JungePackageInformation(SIZE, size)
					&& JungePackageInformation(FAR_AREA, &(pack->isRemoteArea))
					&& JungePackageInformation(FRAG, &(pack->isFragile))
					&& JungePackageInformation(VALU, &(pack->isValuable))
					)
				{
					//计算运费
					pack->Bill = CalculateBill(user, pack);
					system("cls");
					printf("您需要支付 %f 元运费\n", pack->Bill);
					printf("是否支付？\n");
					printf("[y/n]\n");
					InputBox(&key, 1, MODE_KEY, OFF);
					if (key != 'y')
					{
						printf("取消支付了...\n");
						printf("正在返回...\n");
						//重置
						key = ERROR;
						break;//break switch
						system("pause");
					}
					fund += pack->Bill;
					printf("成功支付!\n");
					printf("正在返回...\n");
					system("pause");
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
				totalId--;
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
		//输出运费计算规则
		case PAY_RULE:
		{
			system("cls");
			PrintBillSchedule();
			system("pause");//静默等待
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}
		//录入模式新增
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
		//新增结束

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
		//送货上门
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

//用户管理优惠券
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
		printf("没有任何优惠券......\n");
		system("pause");
		return;
	}

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

		printf("<查看优惠券模式>\n");
		printf("按下[ESC]返回\n");
		printf("按下[a/d]换页\n");
		printf("按下[1 2 3 4 5]选择\n\n");

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
			//{
			//	system("cls");
			//	printf("退出编辑？\n [y/n]\n");
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
				system("cls");
				PrintOneCoupon(tmp);
				printf("\n确定使用吗？\n");
				printf("[y/n]\n");
				InputBox(&key, 1, MODE_KEY, ON);
				if (key != 'y')
				{
					//重置
					key = ERROR;
					system("cls");
					break;//break switch
				}
				if (TRUE == UseCoupon(tmp))
				{
					printf("成功启用！\n");
					system("pause");
				}
				else//FALSE
				{
					printf("无法重复启用！\n");
					system("pause");
				}
			}
			//重置
			key = ERROR;
			system("cls");
			break;//break switch
		}
		}//end switch

	}//end while
} 

//定时完成后的操作函数
void UserRegular(user* user)
{
	//定时刷新优惠券
	RefreshCoupon(user->clist);
	//定时保存
	SaveAll();
}

//管理员短定时完成后的操作函数
void AdminRegular_S(user* user)
{
	//定时保存
	SaveAll();
}

//管理员长定时完成后的操作函数
void AdminRegular_L(user* user)
{
	//遍历包裹状态
	GoThroughPackage();
}

//拒收包裹界面
void RejectPackageInterface(package* head)
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

		printf("<拒收包裹模式>\n");
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
			{
				if (tmp->state != STATE_WAIT_PICK
					&& tmp->state != STATE_STAY_LONG)
				{
					printf("无法对该包裹进行操作\n");
					key = ERROR;
					system("pause");
					system("cls");
					break;//break switch
				}
				printf("\n是否拒收包裹？\n[y/n]");
				InputBox(&key, 1, MODE_KEY, ON);
				if (key == 'y')
				{
					tmp->state = STATE_REJECT;
					message* mess = CreatOneMessage("", IMP_REJECT);
					sprintf(mess->content, "手机号%s拒收了包裹%s",
						tmp->tele_num, tmp->id);
					Broadcast(mess, ahead);
					free(mess);
					printf("成功拒收包裹\n");
					system("pause");
				}
				else
				{
					printf("已取消拒收操作\n");
					system("pause");
				}
			}
			//重置
			key = ERROR;
			system("cls");
			break;//break switch
		}
		}//end switch

	}//end while
}