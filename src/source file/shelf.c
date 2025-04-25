#include "Backend.h"

//给StrToShelf用
extern int JungePackageInformation(const char key, const char* information);

//发配取件码 0000~9999
void SetPickupCode(package* pack)
{
	if (phead->next == NULL)return;

	int tag = TRUE;
	int randomNum = 0;
	char code[MAX_PICKUP_CODE + 1];

	while(tag)
	{
		tag = FALSE;
		memset(code, 0, sizeof(code));
		srand(time(NULL));
		randomNum = rand() % 10000;
		sprintf(code, "%04d", randomNum);

		//防止重复
		package* point = phead->next;
		while (point == NULL)
		{
			if (strcmp(code, point->pickupCode) == 0)
			{
				tag = TRUE;
				break;
			}
			point = point->next;
		}
	}
	strcpy(pack->pickupCode, code);
}

//将包裹放入货架->需要制定ABCD
int PutShelf(package* pack, int num)
{
	//遍历找空位
	for (int sub = 0; sub < SUB_SHELF_NUM; sub++)
		for (int r = 0; r < ROW; r++)
			for (int l = 0; l < LINE; l++)
			{
				if (shelfs[num][sub][r][l].used == FALSE)
				{
					//正式入库
					shelfs[num][sub][r][l].used = TRUE;
					strcpy(shelfs[num][sub][r][l].pack_id, pack->id);
					sprintf(pack->location, "%c%d_%d,%d", num + 'A', sub, r, l);
					//发配取件码
					SetPickupCode(pack);
					//设置入库时间
					struct tm* nowTime = GetNowTime();
					SetPackageInTime(pack, nowTime->tm_year, nowTime->tm_mon, nowTime->tm_mday);
					//设置包裹状态
					pack->state = STATE_WAIT_PICK;
					return TRUE;
				}
			}
	return FALSE;
}

//为包裹“智能”分配位置，内部调用多个函数，若没空位则返回FALSE,发配同时自动检测是否达到警戒线，若有则向全体管理员发通知
int AllocateLocation(package* pack, user* adminHead)
{
	//警戒线检测
	CheckShelfs(adminHead);

	//珍贵品放D区		优先级最高
	if (pack->isValuable)
	{
		return PutShelf(pack, SHELF_D);
	}
	//小件放A区
	if (pack->size <= MEDIUM)
	{
		return PutShelf(pack, SHELF_A);
	}
	//中件放B区
	if (pack->size <= LARGE)
	{
		return PutShelf(pack, SHELF_B);
	}
	//大件放C区
	return PutShelf(pack, SHELF_C);
}

//从货架取出包裹
int GetShelf(package* pack)
{
	//安全检查
	if (pack == NULL)
	{
		printf("非法传入了NULL指针(GetShelf)\n");
		system("pause");
		return FALSE;
	}
	if (pack->state != STATE_WAIT_PICK)
	{
		return;
	}

	shelf* theShelf = StrToShelf(pack->location);
	if (theShelf == NULL)
	{
		return FALSE;
	}

	//置空货架
	theShelf->used = FALSE;
	memset(theShelf->pack_id,0, MAX_ID);
	//写入数据至包裹
	struct tm* nowTime = GetNowTime();
	SetPackageOutTime(pack, nowTime->tm_year, nowTime->tm_mon, nowTime->tm_mday);
	pack->state = STATE_PICKUPED;
	//写入历史记录
	WritePackHis(pack);

	return TRUE;
}

//将字符串转化为shelf
shelf* StrToShelf(const char* str)
{
	if (strlen(str) != MAX_LOCATION)
	{
		return NULL;
	}
	if (!JungePackageInformation(LOCATION, str))
	{
		return NULL;
	}

	int num, sub, r, l;
	num = str[0] - 'A';
	sub = str[1] - '0';
	r = str[3] - '0';
	l = str[5] - '0';

	return &(shelfs[num][sub][r][l]);
}

//计算使用货架数量 传入货架号 ABCD
int CountUsedShelf(int n)
{
	return (SUB_SHELF_NUM * ROW * LINE) - CountEmptyShelf(n);
}

//计算空货架数量 传入货架号 ABCD
int CountEmptyShelf(int n)
{
	int total = 0;
	for (int sub = 0; sub < SUB_SHELF_NUM; sub++)
		for (int r = 0; r < ROW; r++)
			for (int l = 0; l < LINE; l++)
			{
				if (shelfs[n][sub][r][l].used == FALSE)
				{
					total++;
				}
			}
	return total;
}

//打印货架状态 目前打印空货架数量
void PrintAllShelf()
{
	for (int num = SHELF_A; num < SHELF_NUM; num++)
	{
		printf("%c区的已用货架数量:%d\n", num + 'A', CountUsedShelf(num));
	}
	printf("\n");
	for (int num = SHELF_A; num < SHELF_NUM; num++)
	{
		printf("%c区的空货架数量:%d\n", num + 'A', CountEmptyShelf(num));
	}
	printf("\n");
}