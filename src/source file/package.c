#include "Backend.h"

//将state转换成字符串 注意buffer的空间为MAX_STATE
void StateToStr(char* buffer, packageState state)
{
	switch (state)
	{
	case STATE_ERROR:
		sprintf(buffer, "异常");
		break;
	case STATE_WAIT_COLLECT:
		sprintf(buffer, "待揽收");
		break;
	case STATE_TRANSPORT:
		sprintf(buffer, "运输中");
		break;
	case STATE_WAIT_PICK:
		sprintf(buffer, "待签收");
		break;
	case STATE_PICKUPED:
		sprintf(buffer, "已签收");
		break;
	case STATE_REJECT:
		sprintf(buffer, "拒收");
		break;
	case STATE_STAY_LONG:
		sprintf(buffer, "滞留过久");
		break;
	}
}

//只能由顶级管理员调用 打印head之后的所有包裹，自动判断是否为head,而不打印head  -简略
void PrintAllPackage(package* head)
{
	if (head == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintAllPackage）\n");
		system("pause");
		return;
	}

	//自动判断head
	package* tmp = NULL;
	if (head->prior == NULL)
		tmp = head->next;
	else
		tmp = head;

	int cnt = 1;
	printf("     运单号\t电话\t\t包裹名称\t\t存放地点  取件码  收件人名  寄件人名\t状态\n");
	while (tmp != NULL)
	{
		char state[MAX_STATE];
		memset(state, 0, MAX_STATE);
		StateToStr(state, tmp->state);

		printf("[%d].%s\t%s\t%-10s\t\t  %s\t   %s\t     %s\t%s\t%s\n",
			cnt, tmp->id, tmp->tele_num, tmp->pack_name, tmp->location, tmp->pickupCode, tmp->user_name, tmp->sender_name, state);
		tmp = tmp->next;
		cnt++;
	}
}

//打印指定数量的包裹，自动判断是否为head,而不打印head  -简略
void PrintNumPackage(package* head, int num)
{
	if (head == NULL)
	{
		printf("非法传入了NULL指针!!!（PrintAllPackage）\n");
		system("pause");
		return;
	}

	//自动判断head
	package* tmp = NULL;
	if (head->prior == NULL)
		tmp = head->next;
	else
		tmp = head;

	int cnt = 1;
	printf("     运单号\t电话\t\t包裹名称\t\t存放地点  取件码  收件人名  寄件人名\t状态\n");
	while (tmp != NULL && cnt<=num)
	{
		char state[MAX_STATE];
		memset(state, 0, MAX_STATE);
		StateToStr(state, tmp->state);

		printf("[%d].%s\t%s\t%-10s\t\t  %s\t   %s\t     %s\t%s\t%s\n",
			cnt, tmp->id, tmp->tele_num, tmp->pack_name, tmp->location, tmp->pickupCode, tmp->user_name, tmp->sender_name, state);
		tmp = tmp->next;
		cnt++;
	}
	printf("\n");
}

//打印单个pack包裹  -详细
void PrintOnePackage(const package* pack)
{
	if (pack == NULL)
	{
		printf("传入了NULL指针!!!(PrintOnePackage)\n");
		system("pause");
		return;
	}

	char state[MAX_STATE + 1];
	memset(state, 0, sizeof(state));
	StateToStr(state, pack->state);

	char far_area[MAX_TF + 1];
	char fragile[MAX_TF + 1];
	char valuable[MAX_TF + 1];
	char toDoor[MAX_TF + 1];
	char TimeIn[256];
	char TimeOut[256];
	memset(far_area, 0, MAX_TF + 1);
	memset(fragile, 0, MAX_TF + 1);
	memset(valuable, 0, MAX_TF + 1);
	memset(TimeIn, 0, sizeof(TimeIn));
	memset(TimeOut, 0, sizeof(TimeOut));
	TFtoStr(far_area, pack->isRemoteArea);
	TFtoStr(fragile, pack->isFragile);
	TFtoStr(valuable, pack->isValuable);
	TFtoStr(toDoor, pack->isToDoor);
	if (pack->time[IN][YEAR] != 0)
		sprintf(TimeIn, "%04d年%02d月%02d日", 
			pack->time[IN][YEAR], pack->time[IN][MON], pack->time[IN][DAY]);
	else
		strcpy(TimeIn, DEF_STR);
	if (pack->time[OUT][YEAR] != 0)
		sprintf(TimeOut, "%04d年%02d月%02d日", 
			pack->time[OUT][YEAR],pack->time[OUT][MON],pack->time[OUT][DAY]);
	else
		strcpy(TimeOut, DEF_STR);

	printf("包裹状态:\t%s\n", state);
	printf("运单号:\t\t%s\n", pack->id);
	printf("手机号:\t\t%s\n", pack->tele_num);
	printf("取件手机号:\t%s\n", pack->pick_tele_num);
	printf("包裹名称:\t%s\n", pack->pack_name);
	printf("存放地点:\t%s\n", pack->location);
	printf("取件码:\t\t%s\n", pack->pickupCode);
	printf("入库时间:\t%s\n", TimeIn);
	printf("出库时间:\t%s\n", TimeOut);
	printf("收件人名:\t%s\n", pack->user_name);
	printf("寄件人名:\t%s\n", pack->sender_name);
	printf("收件人地址:\t%s\n", pack->user_address);
	printf("寄件人地址:\t%s\n", pack->send_address);
	printf("运费(元):\t%.2f 元\n", pack->Bill);
	printf("重量(kg):\t%.2f kg\n", pack->weight);
	printf("体积(cm^3):\t%.2f cm^3\n", pack->size);
	printf("偏远地区:\t%s\n", far_area);
	printf("易碎品:\t\t%s\n", fragile);
	printf("贵重品:\t\t%s\n", valuable);
	printf("送货上门:\t%s\n", toDoor);
	printf("滞留天数:\t%d 天\n", GetPackageStayTime(pack));

	printf("\n");
}

//计算head及其之后的有效包裹数量，自动判断是否为head,而不计入head
int CountPackage(package* head)
{
	int cnt;
	if (head->prior == NULL)
		cnt = 0;
	else
		cnt = 1;

	head = head->next;

	while (head != NULL)
	{
		cnt++;
		head = head->next;
	}

	return cnt;
}

//分配运单号 -> 基于totalID自增序列生成
void AssignId(package* pack)
{
	sprintf(pack->id, "%010u", totalId);
	totalId++;
}

//创建包裹链表
package* CreatPackageList()
{
	package* head = (package*)malloc(sizeof(package));
	memset(head, 0, sizeof(package));
	return head;
}

//创建一个package,返回创建的package的指针,传入值为-1或DEFAULT时表示不修改
package* CreatOnePackage()
{
	package* pack = (package*)malloc(sizeof(package));
	memset(pack, 0, sizeof(package));
	//字符类
	strcpy(pack->id, DEF_STR);
	strcpy(pack->tele_num, DEF_STR);
	strcpy(pack->pick_tele_num, DEF_STR);
	strcpy(pack->pack_name, DEF_STR);
	strcpy(pack->location, DEF_STR);
	strcpy(pack->pickupCode, DEF_STR);
	strcpy(pack->user_name, DEF_STR);
	strcpy(pack->sender_name, DEF_STR);
	strcpy(pack->user_address, DEF_STR);
	strcpy(pack->send_address, DEF_STR);
	//数值类
	pack->Bill = DEF_NUM;
	pack->weight = DEF_NUM;
	pack->size = DEF_NUM;
	pack->isRemoteArea = DEF_NUM;
	pack->isFragile = DEF_NUM;
	pack->isValuable = DEF_NUM;
	pack->time[IN][YEAR] = DEF_NUM;
	pack->time[IN][MON] = DEF_NUM;
	pack->time[IN][DAY] = DEF_NUM;
	pack->time[OUT][YEAR] = DEF_NUM;
	pack->time[OUT][MON] = DEF_NUM;
	pack->time[OUT][DAY] = DEF_NUM;
	pack->state = DEF_NUM;
	return pack;
}

//仅测试使用函数 创建一个package,返回创建的package的指针,传入值为-1或DEFAULT时表示不修改
package* _CreatOnePackage(char* id, char* tele_num, char* pack_name, packageState state)
{
	package* pack = (package*)malloc(sizeof(package));
	memset(pack, 0, sizeof(package));
	//字符类
	strcpy(pack->id, DEF_STR);
	strcpy(pack->tele_num, DEF_STR);
	strcpy(pack->pick_tele_num, DEF_STR);
	strcpy(pack->pack_name, DEF_STR);
	strcpy(pack->location, DEF_STR);
	strcpy(pack->pickupCode, DEF_STR);
	strcpy(pack->user_name, DEF_STR);
	strcpy(pack->sender_name, DEF_STR);
	strcpy(pack->user_address, DEF_STR);
	strcpy(pack->send_address, DEF_STR);
	//数值类
	pack->Bill = DEF_NUM;
	pack->weight = DEF_NUM;
	pack->size = DEF_NUM;
	pack->isRemoteArea = DEF_NUM;
	pack->isFragile = DEF_NUM;
	pack->isValuable = DEF_NUM;
	pack->time[IN][YEAR] = DEF_NUM;
	pack->time[IN][MON] = DEF_NUM;
	pack->time[IN][DAY] = DEF_NUM;
	pack->time[OUT][YEAR] = DEF_NUM;
	pack->time[OUT][MON] = DEF_NUM;
	pack->time[OUT][DAY] = DEF_NUM;
	pack->state = DEF_NUM;
	if (id != (char*)DEFAULT)
	{
		strcpy(pack->id, id);
	}
	if (tele_num != (char*)DEFAULT)
	{
		strcpy(pack->tele_num, tele_num);
	}
	if (pack_name != (char*)DEFAULT)
	{
		strcpy(pack->pack_name, pack_name);
	}
	if (state != DEFAULT)
	{
		pack->state = state;
	}
	return pack;
}


//在链表末尾添加一个package
void AddOnePackage(package* head, package* pack)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = pack;
	pack->prior = head;
	pack->next = NULL;
}

//在链表末尾添加多个package 自动判断head是否存在，并忽略和释放head
void AddMultiplePackage(package* head, package* packs)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	if (packs->prior == NULL)
	{
		packs = packs->next;
		free(packs->prior);
	}
	head->next = packs;
	packs->prior = head;
}

//在head后边插入一个package 自动检测head并报错
void InsertOnePackage(package* head, package* pack)
{
	if (pack->prior == NULL)
	{
		printf("非法传入了head!!!（InsertOnePackage）\n");
		system("pause");
		return;
	}
	if (head->next == NULL)
	{
		AddOnePackage(head, pack);
		return;
	}
	pack->prior = head;
	pack->next = head->next;
	head->next->prior = pack;
	head->next = pack;
}

//在head后面插入多个package 自动检测head，并忽略和释放head
void InsertMultiplePackage(package* head, package* packs)
{
	if (packs->prior == NULL)
	{
		packs = packs->next;
		free(packs->prior);
	}
	if (head->next == NULL)
	{
		AddMultiplePackage(head, packs);
		return;
	}
	package* tmp = head->next;
	head->next = packs;
	packs->prior = head;
	while (packs->next != NULL)
	{
		packs = packs->next;
	}
	packs->next = tmp;
	tmp->prior = packs;
}

//从head取出单个包裹pack，放入另一个链表nhead尾部
void TakeOutOnePackage(package* nhead, package* pack)
{
	if (pack->next == NULL)
	{
		pack->prior->next = NULL;
		AddOnePackage(nhead, pack);
		return;
	}
	pack->prior->next = pack->next;
	pack->next->prior = pack->prior;
	AddOnePackage(nhead, pack);
}

//释放单个pack 会把入库的包裹的货架状态变FALSE 不可用于释放head 自动检测head并报错
void DeleteOnePackage(package* pack)
{
	if (pack == NULL)return;
	if (pack->prior == NULL)
	{
		printf("非法传入了head!!!（FreeOnePackage）\n");
		system("pause");
		return;
	}

	//货架位置状态变FALSE
	GetShelf(pack);

	if (pack->next == NULL)
	{
		if (pack->prior == NULL)
		{
			free(pack);
			return;
		}
		pack->prior->next = NULL;
		free(pack);
		return;
	}
	pack->prior->next = pack->next;
	pack->next->prior = pack->prior;
	free(pack);
}

//释放head及之后的所有pack
void DeleteAllPackage(package* head)
{
	while (head->next != NULL)
	{
		head = head->next;
		free(head->prior);
	}
	free(head);
}

//管理员查找多个包裹，将查找到的包裹组成链表后放置到head末尾，返回第一个找到的包裹的地址
package* AdminFindPackage(package* head, char* str)
{
	package* nhead = CreatPackageList();

	//查找
	while (head->next != NULL)//遍历
	{
		head = head->next;

		int relevance = FALSE;

		if (strlen(str) == 1)
		{
			if (str[0] - '0' == head->state)
				relevance = TRUE;
		}
		else
		{
			if (strstr(head->id, str) != NULL)
				relevance = TRUE;
			if (strstr(head->tele_num, str) != NULL)
				relevance = TRUE;
			if (strstr(head->pack_name, str) != NULL)
				relevance = TRUE;
			if (strstr(head->user_name, str) != NULL)
				relevance = TRUE;
			if (strstr(head->sender_name, str) != NULL)
				relevance = TRUE;
		}

		if (relevance == TRUE)//查询结果判断
		{
			head = head->prior;
			TakeOutOnePackage(nhead, head->next);//抓出，放nhead末尾
		}
	}

	//按照包裹状态排序
	PackageSort(nhead);

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

//用户查找自己的包裹 //基于电话号码和名称
package* UserFindPackage(package* head, user* _user)
{
	//package* head1 = AdminFindPackage(head, _user->tele_num);
	//package* head2 = AdminFindPackage(head, _user->name);
	return AdminFindPackage(head, _user->name);
}

//包裹排序-基于状态,必须传入哨兵
void PackageSort(package* head)
{
	if (head == NULL || head->prior != NULL)
	{
		printf("非法传入了NULL指针!!!（PackageSort)\n");
		system("pause");
		return;
	}

	//不能跳过哨兵！！！
	//空链表，直接返回
	if (head->next == NULL)
		return;
	//单元链表，直接返回
	if (head->next->next == NULL)
		return;

	//开始排序
	int flag = FALSE;
	do
	{
		flag = FALSE;
		flag = FALSE;
		package* a = head->next;
		package* b = head->next->next;

		while (b != NULL)
		{
			if (a->state > b->state)
			{
				package* aPrior = a->prior;
				package* bNext = b->next;

				a->next = bNext;
				a->prior = b;
				b->next = a;
				b->prior = aPrior;


				package* tmp = a;
				a = b;
				b = tmp;

				aPrior->next = a;
				if (bNext != NULL)
					bNext->prior = b;

				flag = TRUE;
			}
			a = a->next;
			b = b->next;
		}

	} while (flag);
}

//包裹全面检查
void PackageCheck(package* head, message* messhead)
{
	if (head->prior == NULL)
		head = head->next;
	while (head != NULL)
	{
		char cnt = '0';
		char content[MAX_MESSAGE];
		memset(content, 0, sizeof(content));
		sprintf("单号为 %s 的包裹存在如下问题:\n", head->id);
		//strcat(content, "单号为 ");
		//strcat(content, head->id);
		//strcat(content, " 的包裹存在如下问题:\n");
		//包裹异常检查
		if (head->state == STATE_ERROR)
		{
			cnt++;
			strcat(content, &cnt);
			strcat(content, ".包裹异常！\n");
			message* mess = CreatOneMessage(content, STATE_ERROR);
			AddMessage(messhead, mess);
		}
		//包裹存放过久
		if (GetPackageStayTime(head) >= MAX_STAY_DAYS)
		{
			char tem = MAX_STAY_DAYS + '0';
			cnt++;
			strcat(content, &cnt);
			strcat(content, ".滞留时间超过 ");
			strcat(content, &tem);
			strcat(content, " 天！\n");
			message* mess = CreatOneMessage(content, STATE_STAY_LONG);
			AddMessage(messhead, mess);
		}

		head = head->next;
	}
}
