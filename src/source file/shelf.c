#include "Backend.h"

//��StrToShelf��
extern int JungePackageInformation(const char key, const char* information);

//����ȡ���� 0000~9999
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

		//��ֹ�ظ�
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

//�������������->��Ҫ�ƶ�ABCD
int PutShelf(package* pack, int num)
{
	//�����ҿ�λ
	for (int sub = 0; sub < SUB_SHELF_NUM; sub++)
		for (int r = 0; r < ROW; r++)
			for (int l = 0; l < LINE; l++)
			{
				if (shelfs[num][sub][r][l].used == FALSE)
				{
					//��ʽ���
					shelfs[num][sub][r][l].used = TRUE;
					strcpy(shelfs[num][sub][r][l].pack_id, pack->id);
					sprintf(pack->location, "%c%d_%d,%d", num + 'A', sub, r, l);
					//����ȡ����
					SetPickupCode(pack);
					//�������ʱ��
					struct tm* nowTime = GetNowTime();
					SetPackageInTime(pack, nowTime->tm_year, nowTime->tm_mon, nowTime->tm_mday);
					//���ð���״̬
					pack->state = STATE_WAIT_PICK;
					return TRUE;
				}
			}
	return FALSE;
}

//Ϊ���������ܡ�����λ�ã��ڲ����ö����������û��λ�򷵻�FALSE,����ͬʱ�Զ�����Ƿ�ﵽ�����ߣ���������ȫ�����Ա��֪ͨ
int AllocateLocation(package* pack, user* adminHead)
{
	//�����߼��
	CheckShelfs(adminHead);

	//���Ʒ��D��		���ȼ����
	if (pack->isValuable)
	{
		return PutShelf(pack, SHELF_D);
	}
	//С����A��
	if (pack->size <= MEDIUM)
	{
		return PutShelf(pack, SHELF_A);
	}
	//�м���B��
	if (pack->size <= LARGE)
	{
		return PutShelf(pack, SHELF_B);
	}
	//�����C��
	return PutShelf(pack, SHELF_C);
}

//�ӻ���ȡ������
int GetShelf(package* pack)
{
	//��ȫ���
	if (pack == NULL)
	{
		printf("�Ƿ�������NULLָ��(GetShelf)\n");
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

	//�ÿջ���
	theShelf->used = FALSE;
	memset(theShelf->pack_id,0, MAX_ID);
	//д������������
	struct tm* nowTime = GetNowTime();
	SetPackageOutTime(pack, nowTime->tm_year, nowTime->tm_mon, nowTime->tm_mday);
	pack->state = STATE_PICKUPED;
	//д����ʷ��¼
	WritePackHis(pack);

	return TRUE;
}

//���ַ���ת��Ϊshelf
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

//����ʹ�û������� ������ܺ� ABCD
int CountUsedShelf(int n)
{
	return (SUB_SHELF_NUM * ROW * LINE) - CountEmptyShelf(n);
}

//����ջ������� ������ܺ� ABCD
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

//��ӡ����״̬ Ŀǰ��ӡ�ջ�������
void PrintAllShelf()
{
	for (int num = SHELF_A; num < SHELF_NUM; num++)
	{
		printf("%c�������û�������:%d\n", num + 'A', CountUsedShelf(num));
	}
	printf("\n");
	for (int num = SHELF_A; num < SHELF_NUM; num++)
	{
		printf("%c���Ŀջ�������:%d\n", num + 'A', CountEmptyShelf(num));
	}
	printf("\n");
}