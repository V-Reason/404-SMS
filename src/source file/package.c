#include "Backend.h"

//��stateת�����ַ��� ע��buffer�Ŀռ�ΪMAX_STATE
void StateToStr(char* buffer, packageState state)
{
	switch (state)
	{
	case STATE_ERROR:
		sprintf(buffer, "�쳣");
		break;
	case STATE_WAIT_COLLECT:
		sprintf(buffer, "������");
		break;
	case STATE_TRANSPORT:
		sprintf(buffer, "������");
		break;
	case STATE_WAIT_PICK:
		sprintf(buffer, "��ǩ��");
		break;
	case STATE_PICKUPED:
		sprintf(buffer, "��ǩ��");
		break;
	case STATE_REJECT:
		sprintf(buffer, "����");
		break;
	case STATE_STAY_LONG:
		sprintf(buffer, "��������");
		break;
	}
}

//ֻ���ɶ�������Ա���� ��ӡhead֮������а������Զ��ж��Ƿ�Ϊhead,������ӡhead  -����
void PrintAllPackage(package* head)
{
	if (head == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintAllPackage��\n");
		system("pause");
		return;
	}

	//�Զ��ж�head
	package* tmp = NULL;
	if (head->prior == NULL)
		tmp = head->next;
	else
		tmp = head;

	int cnt = 1;
	printf("     �˵���\t�绰\t\t��������\t\t��ŵص�  ȡ����  �ռ�����  �ļ�����\t״̬\n");
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

//��ӡָ�������İ������Զ��ж��Ƿ�Ϊhead,������ӡhead  -����
void PrintNumPackage(package* head, int num)
{
	if (head == NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PrintAllPackage��\n");
		system("pause");
		return;
	}

	//�Զ��ж�head
	package* tmp = NULL;
	if (head->prior == NULL)
		tmp = head->next;
	else
		tmp = head;

	int cnt = 1;
	printf("     �˵���\t�绰\t\t��������\t\t��ŵص�  ȡ����  �ռ�����  �ļ�����\t״̬\n");
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

//��ӡ����pack����  -��ϸ
void PrintOnePackage(const package* pack)
{
	if (pack == NULL)
	{
		printf("������NULLָ��!!!(PrintOnePackage)\n");
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
		sprintf(TimeIn, "%04d��%02d��%02d��", 
			pack->time[IN][YEAR], pack->time[IN][MON], pack->time[IN][DAY]);
	else
		strcpy(TimeIn, DEF_STR);
	if (pack->time[OUT][YEAR] != 0)
		sprintf(TimeOut, "%04d��%02d��%02d��", 
			pack->time[OUT][YEAR],pack->time[OUT][MON],pack->time[OUT][DAY]);
	else
		strcpy(TimeOut, DEF_STR);

	printf("����״̬:\t%s\n", state);
	printf("�˵���:\t\t%s\n", pack->id);
	printf("�ֻ���:\t\t%s\n", pack->tele_num);
	printf("ȡ���ֻ���:\t%s\n", pack->pick_tele_num);
	printf("��������:\t%s\n", pack->pack_name);
	printf("��ŵص�:\t%s\n", pack->location);
	printf("ȡ����:\t\t%s\n", pack->pickupCode);
	printf("���ʱ��:\t%s\n", TimeIn);
	printf("����ʱ��:\t%s\n", TimeOut);
	printf("�ռ�����:\t%s\n", pack->user_name);
	printf("�ļ�����:\t%s\n", pack->sender_name);
	printf("�ռ��˵�ַ:\t%s\n", pack->user_address);
	printf("�ļ��˵�ַ:\t%s\n", pack->send_address);
	printf("�˷�(Ԫ):\t%.2f Ԫ\n", pack->Bill);
	printf("����(kg):\t%.2f kg\n", pack->weight);
	printf("���(cm^3):\t%.2f cm^3\n", pack->size);
	printf("ƫԶ����:\t%s\n", far_area);
	printf("����Ʒ:\t\t%s\n", fragile);
	printf("����Ʒ:\t\t%s\n", valuable);
	printf("�ͻ�����:\t%s\n", toDoor);
	printf("��������:\t%d ��\n", GetPackageStayTime(pack));

	printf("\n");
}

//����head����֮�����Ч�����������Զ��ж��Ƿ�Ϊhead,��������head
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

//�����˵��� -> ����totalID������������
void AssignId(package* pack)
{
	sprintf(pack->id, "%010u", totalId);
	totalId++;
}

//������������
package* CreatPackageList()
{
	package* head = (package*)malloc(sizeof(package));
	memset(head, 0, sizeof(package));
	return head;
}

//����һ��package,���ش�����package��ָ��,����ֵΪ-1��DEFAULTʱ��ʾ���޸�
package* CreatOnePackage()
{
	package* pack = (package*)malloc(sizeof(package));
	memset(pack, 0, sizeof(package));
	//�ַ���
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
	//��ֵ��
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

//������ʹ�ú��� ����һ��package,���ش�����package��ָ��,����ֵΪ-1��DEFAULTʱ��ʾ���޸�
package* _CreatOnePackage(char* id, char* tele_num, char* pack_name, packageState state)
{
	package* pack = (package*)malloc(sizeof(package));
	memset(pack, 0, sizeof(package));
	//�ַ���
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
	//��ֵ��
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


//������ĩβ���һ��package
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

//������ĩβ��Ӷ��package �Զ��ж�head�Ƿ���ڣ������Ժ��ͷ�head
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

//��head��߲���һ��package �Զ����head������
void InsertOnePackage(package* head, package* pack)
{
	if (pack->prior == NULL)
	{
		printf("�Ƿ�������head!!!��InsertOnePackage��\n");
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

//��head���������package �Զ����head�������Ժ��ͷ�head
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

//��headȡ����������pack��������һ������nheadβ��
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

//�ͷŵ���pack ������İ����Ļ���״̬��FALSE ���������ͷ�head �Զ����head������
void DeleteOnePackage(package* pack)
{
	if (pack == NULL)return;
	if (pack->prior == NULL)
	{
		printf("�Ƿ�������head!!!��FreeOnePackage��\n");
		system("pause");
		return;
	}

	//����λ��״̬��FALSE
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

//�ͷ�head��֮�������pack
void DeleteAllPackage(package* head)
{
	while (head->next != NULL)
	{
		head = head->next;
		free(head->prior);
	}
	free(head);
}

//����Ա���Ҷ�������������ҵ��İ�������������õ�headĩβ�����ص�һ���ҵ��İ����ĵ�ַ
package* AdminFindPackage(package* head, char* str)
{
	package* nhead = CreatPackageList();

	//����
	while (head->next != NULL)//����
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

		if (relevance == TRUE)//��ѯ����ж�
		{
			head = head->prior;
			TakeOutOnePackage(nhead, head->next);//ץ������nheadĩβ
		}
	}

	//���հ���״̬����
	PackageSort(nhead);

	//����head��nhead
	if (nhead->next != NULL)
	{
		AddMultiplePackage(head, nhead);//��pack�䵱head��β��
		//free(nhead); nhead�Ѿ���AddMultiplePackage���ͷ�
		return head->next;
	}
	else//û�в�ѯ������ͷſռ�
	{
		free(nhead);
		return NULL;
	}
}

//�û������Լ��İ��� //���ڵ绰���������
package* UserFindPackage(package* head, user* _user)
{
	//package* head1 = AdminFindPackage(head, _user->tele_num);
	//package* head2 = AdminFindPackage(head, _user->name);
	return AdminFindPackage(head, _user->name);
}

//��������-����״̬,���봫���ڱ�
void PackageSort(package* head)
{
	if (head == NULL || head->prior != NULL)
	{
		printf("�Ƿ�������NULLָ��!!!��PackageSort)\n");
		system("pause");
		return;
	}

	//���������ڱ�������
	//������ֱ�ӷ���
	if (head->next == NULL)
		return;
	//��Ԫ����ֱ�ӷ���
	if (head->next->next == NULL)
		return;

	//��ʼ����
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

//����ȫ����
void PackageCheck(package* head, message* messhead)
{
	if (head->prior == NULL)
		head = head->next;
	while (head != NULL)
	{
		char cnt = '0';
		char content[MAX_MESSAGE];
		memset(content, 0, sizeof(content));
		sprintf("����Ϊ %s �İ���������������:\n", head->id);
		//strcat(content, "����Ϊ ");
		//strcat(content, head->id);
		//strcat(content, " �İ���������������:\n");
		//�����쳣���
		if (head->state == STATE_ERROR)
		{
			cnt++;
			strcat(content, &cnt);
			strcat(content, ".�����쳣��\n");
			message* mess = CreatOneMessage(content, STATE_ERROR);
			AddMessage(messhead, mess);
		}
		//������Ź���
		if (GetPackageStayTime(head) >= MAX_STAY_DAYS)
		{
			char tem = MAX_STAY_DAYS + '0';
			cnt++;
			strcat(content, &cnt);
			strcat(content, ".����ʱ�䳬�� ");
			strcat(content, &tem);
			strcat(content, " �죡\n");
			message* mess = CreatOneMessage(content, STATE_STAY_LONG);
			AddMessage(messhead, mess);
		}

		head = head->next;
	}
}
