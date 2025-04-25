#include "Frontend.h"

//节日定义
const festival fes[] =
{
	//节日  月 日 倍率
	{"元旦",1,1,0.5},
	{"国庆节",10,1,0.5},
	{"圣诞节",12,25,0.8},
	{"双十一",11,11,0.9},
	{"双十二",12,12,0.9},
	{"劳动节",5,1,0.5},
	{"妇女节",3,8,0.9},
	{"情人节",2,14,0.9}
	//{"VR节",4,25,0.9}
};


//打印填写规则
void PrintInputRule()
{
	printf("\n");
	printf("以下信息全不能为空\n\n");
	printf("包裹录入格式：\n");
	printf("%d位 运单号\n", MAX_ID);
	printf("%d位 手机号\n", MAX_TELE_NUM);
	printf("%d位 包裹名称\n", MAX_PACK_NAME);
	printf("%d位 收件人姓名\n", MAX_USER_NAME);
	printf("%d位 寄件人姓名\n", MAX_USER_NAME);
	printf("%d位 收件人地址\n", MAX_ADDRESS);
	printf("%d位 寄件人地址\n", MAX_ADDRESS);
	printf("存放地点输入示例：A0_0,2\n");

	printf("\n");
	printf("用户信息格式：\n");
	printf("%d位 姓名\n", MAX_USER_NAME);
	printf("%d位 密码\n", MAX_PASSWORD_NUM);
	printf("%d位 手机号\n", MAX_TELE_NUM);
	printf("%d位 地址\n", MAX_ADDRESS);

	printf("\n");
}

//计算包裹总费用
float CalculateBill(user* user, package* pack)
{
	const float baseRate = BASS_RATE;			// 基础费率（元/kg）
	const float volumeRate = VOLUME_RATE;		// 体积费率（元/cm³）
	const float remoteSurcharge = FAR_SUR;		// 偏远地区附加费（元）
	const float fragileSurcharge = FRAG_SUR;    // 易碎品附加费（元）
	const float valuableSurcharge = VALU_SUR;   // 贵重品附加费（元）
	const float todoorSurcharge = TODOOR_SUR;   // 送货上门附加费（元）

	//计算体积重量
	const float volumeWeight = pack->size * volumeRate;

	//计算基础运费（按重量或体积重量中较高的值）
	const float baseCost =
		(pack->weight > volumeWeight) 
		? pack->weight * baseRate 
		: volumeWeight * baseRate;

	//计算附加费用
	pack->isRemoteArea %= 2;
	pack->isFragile %= 2;
	pack->isValuable %= 2;
	pack->isToDoor %= 2;
	float additionalCost = 0;
	additionalCost += pack->isRemoteArea * remoteSurcharge; // 偏远区附加费
	additionalCost += pack->isFragile * fragileSurcharge;   // 易碎品附加费
	additionalCost += pack->isValuable * valuableSurcharge; // 贵重品附加费
	additionalCost += pack->isToDoor * todoorSurcharge;		// 送货上门附加费

	//总费用 = 基础运费 + 附加费用
	float totalCost = baseCost + additionalCost;

	//计算折扣费用
	float levelRate = 1.0;
	levelRate -= (user->level * LEVEL_RATE);

	float fesRate = 1.0;
	festival* theFes = isFestival();
	if (theFes != NULL)
	{
		fesRate = theFes->discount;
	}

	//开始折扣
	totalCost *= levelRate;
	totalCost *= fesRate;

	//优惠券折扣
	RefreshCoupon(user->clist);//首先更新coupon
	coupon* tmp = user->clist->next;
	while (tmp != NULL)
	{
		if (tmp->used == TRUE)
		{
			totalCost *= tmp->cost;
		}
		tmp = tmp->next;
	}

	return totalCost;
}

//费用规则
void PrintBillSchedule()
{
	system("cls");
	printf("<运费计算规则>\n\n");
	printf("以下节日享有相应优惠:\n\n");

	//节日
	printf("节日\t日期\t折扣力度\n");
	const int totalFes = sizeof(fes) / sizeof(festival);
	for (int i = 0; i < totalFes; i++)
	{
		printf("%s\t%d.%d\t%.2f\n",
			fes[i].name, fes[i].month, fes[i].day, fes[i].discount);
	}
	printf("\n");

	//额外收费
	printf("以下是额外收费额度:\n");
	//printf("基础费率: %f", BASS_RATE);
	//printf("体积费率: %f", VOLUME_RATE);
	printf("偏远地区: +%d\n", FAR_SUR);
	printf("易碎物品: +%d\n", FRAG_SUR);
	printf("贵重物品: +%d\n", VALU_SUR);
	printf("\n");

	//优惠政策
	printf("以下是额外优惠政策:\n");
	printf("用户等级从1级的100%倍率开始，\n");
	printf("每升1级获减5%的优惠倍率,\n");
	printf("最高5级.\n");
	printf("\n");

	return;
}

//判断今日是否是节日,是则返回节日，否则返回NULL
festival* isFestival()
{
	festival* theFes = NULL;
	struct tm* nowTime = GetNowTime();
	const int totalFes = sizeof(fes) / sizeof(festival);
	for (int i = 0; i < totalFes; i++)
	{
		if (nowTime->tm_mon == fes[i].month
			&& nowTime->tm_mday == fes[i].day)
		{
			theFes = &fes[i];
			break;
		}
	}

	return theFes;
}

//获得经验值
void GainExp(const int event, user* user)
{
	message* mess = CreatOneMessage("", IMP_NORMAL);
	switch (event)
	{
	case EVENT_SignIn://每日登录
		user->exp += EXP_SignIn;
		sprintf(mess->content, "每日登录 +%d exp",EXP_SignIn);
		AddMessage(user->mlist, mess);
		break;
	case EVENT_SendPack://寄件
		user->exp += EXP_SendPack;
		sprintf(mess->content, "发送包裹 +%d exp", EXP_SendPack);
		AddMessage(user->mlist, mess);
		break;
	case EVENT_TopUp://充值
		user->exp += EXP_TopUp;
		sprintf(mess->content, "充值成功 +%d exp", EXP_TopUp);
		AddMessage(user->mlist, mess);
		break;
	default:
		free(mess);
		break;
	}

	//限定EXP上限
	user->exp = user->exp > MAX_EXP ? MAX_EXP : user->exp;

	//升级检测
	if (user->level < user->exp / LEVEL_STEP + NORMAL_USER)
	{
		//升级
		user->level++;
		//通知
		message* mess = CreatOneMessage("NULL", IMP_NORMAL);
		sprintf(mess->content, "[升级]恭喜升至 %d 级", user->level);
		AddMessage(user->mlist, mess);
	}
}

//用户内购
void UserPay(user* user)
{
	//准备工作
	system("cls");
	char key = ERROR;

	while (TRUE)
	{
		SetCursorPosition(0, 0);
		//主界面
		printf("<内购界面>\n");
		printf("当前时间：");
		PrintNowTime();
		printf("\n");

		//操作说明
		printf("[ESC]退出\n");
		printf("[0]购买exp\n");
		printf("[1]购买优惠券\n");

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
			return;
		}
		//购买exp
		case '0':
		{
			BuyExp(user);
			key = ERROR;
			system("cls");
			break;
		}
		//购买优惠券
		case '1':
		{
			BuyCoupon(user);
			key = ERROR;
			system("cls");
			break;
		}
		}//end switch
	}
}

//购买exp
void BuyExp(user* user)
{
	//准备工作
	system("cls");
	char key = ERROR;

	while (TRUE)
	{
		SetCursorPosition(0, 0);
		//主界面
		printf("<内购界面-购买Exp>\n");
		printf("当前时间：");
		PrintNowTime();
		printf("\n");

		//操作说明
		printf("[ESC]退出\n");
		printf("[0]等级规则\n");
		printf("[1]购买 %d exp\n", EXP_TopUp);
		printf("[2]购买 %d exp\n", EXP_TopUp * 2);
		printf("[3]购买 %d exp\n", EXP_TopUp * 3);
		printf("[4]购买 %d exp\n", EXP_TopUp * 4);

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
			return;
		}
		//等级规则
		case '0':
		{
			system("cls");
			PrintExpRule();
			system("pause");
			key = ERROR;
			system("cls");
			break;
		}
		//购买Exp
		case '1':
		case '2':
		case '3':
		case '4':
		{
			int cnt = key - '0';
			system("cls");
			printf("确定购买 %d 点Exp ?\n", cnt * LEVEL_STEP);
			printf("您需要支付 %d 元\n", cnt * MIN_PAY);
			printf("[y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key == 'y')
			{
				for (int i = 0; i < cnt; i++)
				{
					fund += MIN_PAY;
					GainExp(EVENT_TopUp, user);
				}
				printf("购买成功！\n");
				system("pause");
			}
			key = ERROR;
			system("cls");
			break;
		}
		}//end switch
	}//end while

}

//购买优惠券
void BuyCoupon(user* user)
{
	//准备工作
	system("cls");
	char key = ERROR;
	int cnt = CountCoupon(chead);

	while (TRUE)
	{
		SetCursorPosition(0, 0);
		//主界面
		printf("<内购界面-购买优惠券>\n");
		printf("当前时间：");
		PrintNowTime();
		printf("\n");

		//操作说明
		printf("[ESC]退出\n");
		printf("点击进入详情\n");
		coupon* theCoupon = chead->next;
		for (int i = 0; i < cnt; i++)
		{
			printf("[%c]购买 %s 优惠券\n", i, theCoupon->content);
			theCoupon = theCoupon->next;
		}

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
			return;
		}
		//购买优惠券
		default:
		{
			if (key < '0' || '9' < key)break;
			
			int num = key - '0';

			coupon* theCoupon = chead->next;
			for (int i = 0; i < num; i++)
				theCoupon = theCoupon->next;

			system("cls");
			printf("优惠券详情:\n");
			printf("内容：%s\n", theCoupon->content);
			printf("价格：%d 元\n", theCoupon->cost);
			printf("是否购买？\n");
			printf("[y/n]");
			InputBox(&key, 1, MODE_KEY, ON);
			if (key != 'y')
			{
				key = ERROR;
				system("cls");
				break;
			}
			fund += theCoupon->cost;
			coupon* newCoupon = CpyCoupon(theCoupon);
			AddCoupon(user->clist, newCoupon);
			printf("购买成功！\n");
			key = ERROR;
			system("pause");
			system("cls");
			break;
		}
		}//end switch
	}//end while
}

//打印等级规则
void PrintExpRule()
{
	printf("\n");
	printf("最大Exp：%d\n", MAX_EXP);
	printf("一级：0~%d\n", LEVEL_STEP);
	printf("二级：%d~%d\n", LEVEL_STEP + 1, LEVEL_STEP * 2);
	printf("三级：%d~%d\n", LEVEL_STEP * 2 + 1, LEVEL_STEP * 3);
	printf("四级：%d~%d\n", LEVEL_STEP * 3 + 1, LEVEL_STEP * 4);
	printf("五级：%d~%d\n", LEVEL_STEP * 4 + 1, LEVEL_STEP * 5);
	printf("每日签到 +%d\n", EXP_SignIn);
	printf("寄包裹 +%d\n", EXP_SendPack);
	printf("充值 +%d/%d\n", EXP_TopUp, MIN_PAY);
	printf("超出的Exp将不被返还\n");
}