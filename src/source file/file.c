#include "Backend.h"

//���ַ������\nת����\0
void Replace_nto0(char* str)
{
	if (str == NULL)return;
	const int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
		}
	}
}

//��ȡȫ���ļ�
int ReadAll()
{
	if (!ReadInit())return FALSE;						//��ȡ������

	if (cyrTag == CYR)
	{
		DecyrAll();
	}
	if (!ReadUser(User_File_txt, uhead))return FALSE;	//��ȡ�û�
	if (!ReadUser(Admin_File_txt, ahead))return FALSE;	//��ȡ����Ա
	if (!ReadPackage())return FALSE;					//��ȡ����
	if (!ReadTotalId())return FALSE;					//��ȡTotalId
	if (!ReadFund())return FALSE;						//��ȡfund
	if (!ReadCoupon())return FALSE;						//��ȡCoupon
	if (!ReadLogoutTime())return FALSE;					//��ȡLoginTime
	if (cyrTag == CYR)
	{
		CyrAll();
	}
	return TRUE;
}

//����ȫ���ļ�
int SaveAll()
{
	if (!SaveInit())return FALSE;						//����������

	if (!SaveUser(User_File_txt, uhead))return FALSE;	//�����û�
	if (!SaveUser(Admin_File_txt, ahead))return FALSE;	//�������Ա
	if (!SavePackage())return FALSE;					//�������
	if (!SaveTotalId())return FALSE;					//����TotalId
	if (!SaveFund())return FALSE;						//����fund
	if (!SaveCoupon())return FALSE;						//����Coupon
	if (!SaveLogoutTime())return FALSE;					//����LoginTime
	if (cyrTag == CYR)
	{
		CyrAll();
	}
	return TRUE;
}

//���������ļ�
void DecyrAll()
{
	//DecyrptFile(Init_File_txt);��Ҫ�������
	DecyrptFile(User_File_txt);
	DecyrptFile(Admin_File_txt);
	DecyrptFile(Package_File_txt);
	DecyrptFile(TotalId_File_txt);
	DecyrptFile(Fund_File_txt);
	DecyrptFile(Coupon_File_txt);
	DecyrptFile(LogoutTime_File_txt);
}

//���������ļ�
void CyrAll()
{
	//CyrptFile(Init_File_txt);��Ҫ�������
	CyrptFile(User_File_txt);
	CyrptFile(Admin_File_txt);
	CyrptFile(Package_File_txt);
	CyrptFile(TotalId_File_txt);
	CyrptFile(Fund_File_txt);
	CyrptFile(Coupon_File_txt);
	CyrptFile(LogoutTime_File_txt);
}

//����������ʷ��¼�ļ�
void DecyrHis()
{
	struct tm* nowTime = GetNowTime();
	//׼������
	FILE* file = NULL;
	char FILENAME[sizeof(PACK_HIS) + sizeof(_CRY) + MAX_DATA + sizeof(_TXT) + 1];
	const int initYear = 2000;
	const int endYear = nowTime->tm_year;
	//������START��END
	for (int year = initYear; year <= endYear; year++) {
		for (int mon = 1; mon <= 12; mon++) {
			for (int day = 1; day <= 31; day++) {
				//�༭�ļ���ʽ
				memset(FILENAME, 0, sizeof(FILENAME));//���FILENAME
				sprintf(FILENAME, "%s%04d%02d%02d%s",
					PACK_HIS,
					year, mon, day,
					_TXT);

				//�����ļ�
				file = fopen(FILENAME, "r");
				if (file != NULL)
				{
					//�ҵ��ļ�
					fclose(file);
					//���ܲ���
					DecyrptFile(FILENAME);
				}
				//û�ҵ��ļ��ͼ�������
			}
		}
	}
}

//����������ʷ��¼�ļ�
void CyrHis()
{
	struct tm* nowTime = GetNowTime();
	//׼������
	FILE* file = NULL;
	char FILENAME[sizeof(PACK_HIS) + sizeof(_CRY) + MAX_DATA + sizeof(_TXT) + 1];
	const int initYear = 2000;
	const int endYear = nowTime->tm_year;
	//������START��END
	for (int year = initYear; year <= endYear; year++) {
		for (int mon = 1; mon <= 12; mon++) {
			for (int day = 1; day <= 31; day++) {
				//�༭�ļ���ʽ
				memset(FILENAME, 0, sizeof(FILENAME));//���FILENAME
				sprintf(FILENAME, "%s%04d%02d%02d%s",
					PACK_HIS,
					year, mon, day,
					_TXT);

				//�����ļ�
				file = fopen(FILENAME, "r");
				if (file != NULL)
				{
					//�ҵ��ļ�
					fclose(file);
					//���ܲ���
					CyrptFile(FILENAME);
				}
				//û�ҵ��ļ��ͼ�������
			}
		}
	}
}

//��ȡ������
int ReadInit()
{
	FILE* init_file = fopen(Init_File_txt, "r");
	if (init_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", Init_File_txt);
		system("pause");
		return FALSE;
	}
	fscanf(init_file, "%d", &cyrTag);
	fclose(init_file);
	return TRUE;
}

//����������
int SaveInit()
{
	FILE* init_file = fopen(Init_File_txt, "w");
	if (init_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", Init_File_txt);
		system("pause");
		return FALSE;
	}
	fprintf(init_file, "%d", cyrTag);
	fclose(init_file);
	return TRUE;
}

//��ȡ������
int ReadHisInit()
{
	FILE* init_file = fopen(His_Init_File_txt, "r");
	if (init_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", His_Init_File_txt);
		system("pause");
		return FALSE;
	}
	fscanf(init_file, "%d", &hisCyrTag);
	fclose(init_file);
	return TRUE;
}

//����������
int SaveHisInit()
{
	FILE* init_file = fopen(His_Init_File_txt, "w");
	if (init_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", His_Init_File_txt);
		system("pause");
		return FALSE;
	}
	fprintf(init_file, "%d", hisCyrTag);
	fclose(init_file);
	return TRUE;
}

//��ȡ����
int ReadPackage()
{
	//���ļ�
	FILE* pack_file = fopen(Package_File_txt, "r");
	if (pack_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", Package_File_txt);
		system("pause");
		return FALSE;
	}
	//����
	//����
	// 1.��ͬ������DataSeg�ָ�
	// 2.��ͬ�ṹ��StructSeg�ָ�
	package* point = NULL;
	while (!feof(pack_file))
	{
		point = CreatOnePackage();
		//�ַ���
		fscanf(pack_file, "%s", &(point->id)); //Replace_nto0(point->id);
		fscanf(pack_file, "%s", &(point->tele_num)); //Replace_nto0(point->tele_num);
		fscanf(pack_file, "%s", &(point->pick_tele_num)); //Replace_nto0(point->tele_num);
		fscanf(pack_file, "%s", &(point->pack_name)); //Replace_nto0(point->pack_name);
		fscanf(pack_file, "%s", &(point->location)); //Replace_nto0(point->location);
		fscanf(pack_file, "%s", &(point->pickupCode)); //Replace_nto0(point->pickupCode);
		fscanf(pack_file, "%s", &(point->user_name)); //Replace_nto0(point->user_address);
		fscanf(pack_file, "%s", &(point->sender_name)); //Replace_nto0(point->sender_name);
		fscanf(pack_file, "%s", &(point->user_address)); //Replace_nto0(point->user_address);
		fscanf(pack_file, "%s", &(point->send_address)); //Replace_nto0(point->send_address);
		//������
		fscanf(pack_file, "%f", &(point->Bill)); 
		fscanf(pack_file, "%f", &(point->weight));
		fscanf(pack_file, "%f", &(point->size));
		fscanf(pack_file, "%d", &(point->isRemoteArea));
		fscanf(pack_file, "%d", &(point->isFragile));
		fscanf(pack_file, "%d", &(point->isValuable));
		fscanf(pack_file, "%d", &(point->isToDoor));
		fscanf(pack_file, "%d", &(point->time[IN][YEAR]));
		fscanf(pack_file, "%d", &(point->time[IN][MON]));
		fscanf(pack_file, "%d", &(point->time[IN][DAY]));
		fscanf(pack_file, "%d", &(point->time[OUT][YEAR]));
		fscanf(pack_file, "%d", &(point->time[OUT][MON]));
		fscanf(pack_file, "%d", &(point->time[OUT][DAY]));
		fscanf(pack_file, "%d", &(point->state));
		//����
		//fgetc(pack_file);
		AddOnePackage(phead, point);
	}
	if (point != NULL)
		DeleteOnePackage(point);//ɾ��������
	//�ر��ļ�
	pack_file = fclose(pack_file);
	if (pack_file != NULL)
	{
		printf("%s �ļ��ر�ʧ��\n", Package_File_txt);
		system("pause");
		return FALSE;
	}
	return TRUE;
}

//�������
int SavePackage()
{
	//���ļ�
	FILE* pack_file = fopen(Package_File_txt, "w");
	if (pack_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", Package_File_txt);
		system("pause");
		return FALSE;
	}
	//����
	//����
	// 1.��ͬ������DataSeg�ָ�
	// 2.��ͬ�ṹ��StructSeg�ָ�
	package* point = phead->next;
	while (point != NULL)
	{
		//�ַ���
		fputs(point->id, pack_file); fputc(DataSeg, pack_file);
		fputs(point->tele_num, pack_file); fputc(DataSeg, pack_file);
		fputs(point->pick_tele_num, pack_file); fputc(DataSeg, pack_file);
		fputs(point->pack_name, pack_file); fputc(DataSeg, pack_file);
		fputs(point->location, pack_file); fputc(DataSeg, pack_file);
		fputs(point->pickupCode, pack_file); fputc(DataSeg, pack_file);
		fputs(point->user_name, pack_file); fputc(DataSeg, pack_file);
		fputs(point->sender_name, pack_file); fputc(DataSeg, pack_file);
		fputs(point->user_address, pack_file); fputc(DataSeg, pack_file);
		fputs(point->send_address, pack_file); fputc(DataSeg, pack_file);
		//������
		fprintf(pack_file, "%f%c", point->Bill, DataSeg);
		fprintf(pack_file, "%f%c", point->weight, DataSeg);
		fprintf(pack_file, "%f%c", point->size, DataSeg);
		fprintf(pack_file, "%d%c", point->isRemoteArea, DataSeg);
		fprintf(pack_file, "%d%c", point->isFragile, DataSeg);
		fprintf(pack_file, "%d%c", point->isValuable, DataSeg);
		fprintf(pack_file, "%d%c", point->isToDoor, DataSeg);
		fprintf(pack_file, "%d%c", point->time[IN][YEAR], DataSeg);
		fprintf(pack_file, "%d%c", point->time[IN][MON], DataSeg);
		fprintf(pack_file, "%d%c", point->time[IN][DAY], DataSeg);
		fprintf(pack_file, "%d%c", point->time[OUT][YEAR], DataSeg);
		fprintf(pack_file, "%d%c", point->time[OUT][MON], DataSeg);
		fprintf(pack_file, "%d%c", point->time[OUT][DAY], DataSeg);
		fprintf(pack_file, "%d%c", point->state, DataSeg);
		//����
		//fputc(StructSeg, pack_file);
		point = point->next;
	}
	//�ر��ļ�
	pack_file = fclose(pack_file);
	if (pack_file != NULL)
	{
		printf("%s �ļ��ر�ʧ��\n", Package_File_txt);
		system("pause");
		return FALSE;
	}
	return TRUE;
}

//��ȡ�û� ���������������uhead��ahead
int ReadUser(const char* txt, user* head)
{
	//���ļ�
	FILE* user_file = fopen(txt, "r");
	if (user_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", txt);
		system("pause");
		return FALSE;
	}
	//��ȡ
	user* point = NULL;
	while (!feof(user_file))
	{
		point = CreatOneUser();
		//��ֵ��
		fscanf(user_file, "%d", &(point->level));
		fscanf(user_file, "%d", &(point->exp));
		//�ַ���
		fscanf(user_file, "%s", &(point->name));
		fscanf(user_file, "%s", &(point->password));
		fscanf(user_file, "%s", &(point->tele_num));
		fscanf(user_file, "%s", &(point->address_1));
		fscanf(user_file, "%s", &(point->address_2));
		fscanf(user_file, "%s", &(point->address_3));
		char defAddr[MAX_ADDRESS];
		fscanf(user_file, "%s", defAddr);
		if (strcmp(defAddr, point->address_1) == 0)
			point->address_default = point->address_1;
		else if(strcmp(defAddr, point->address_2) == 0)
			point->address_default = point->address_2;
		else //if(strcmp(defAddr, point->address_3) == 0)
			point->address_default = point->address_3;
		//֪ͨ
		int cnt = 0;
		message* theMess = NULL;
		fscanf(user_file, "%d", &cnt);
		for (int i = 0; i < cnt; i++)
		{
			theMess = CreatOneMessage(DEFAULT, DEFAULT);
			fscanf(user_file, "%s", &(theMess->content));
			fscanf(user_file, "%d", &(theMess->important));
			AddMessage(point->mlist, theMess);
		}
		//�Ż�ȯ
		cnt = 0;
		coupon* theCoupon = NULL;
		fscanf(user_file, "%d", &cnt);
		for (int i = 0; i < cnt; i++)
		{
			theCoupon = CreatOneCoupon();
			fscanf(user_file, "%s", &(theCoupon->content));
			fscanf(user_file, "%f", &(theCoupon->rate));
			fscanf(user_file, "%d", &(theCoupon->timeLimit));
			fscanf(user_file, "%d", &(theCoupon->cost));
			fscanf(user_file, "%d", &(theCoupon->used));
			fscanf(user_file, "%d", &(theCoupon->time[VALID].tm_year));
			fscanf(user_file, "%d", &(theCoupon->time[VALID].tm_mon));
			fscanf(user_file, "%d", &(theCoupon->time[VALID].tm_mday));
			fscanf(user_file, "%d", &(theCoupon->time[INVALID].tm_year));
			fscanf(user_file, "%d", &(theCoupon->time[INVALID].tm_mon));
			fscanf(user_file, "%d", &(theCoupon->time[INVALID].tm_mday));
			theCoupon = theCoupon->next;
			AddCoupon(point->clist, theCoupon);
		}
		//����
		AddUser(head, point);
	}
	if (point != NULL)
		DeleteOneUser(point);//ɾ��������Ŀ
	//�ر��ļ�
	user_file = fclose(user_file);
	if (user_file != NULL)
	{
		printf("%s �ļ��ر�ʧ��\n", txt);
		system("pause");
		return FALSE;
	}
	return TRUE;
}

//�����û�
int SaveUser(const char* txt, user* head)
{
	//���ļ�
	FILE* user_file = fopen(txt, "w");
	if (user_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", txt);
		system("pause");
		return FALSE;
	}
	//����
	//����
	// 1.��ͬ������DataSeg�ָ�
	// 2.��ͬ�ṹ��StructSeg�ָ�
	// 3.����֪ͨ��������ͳ��֪ͨ��������д��һ����Ϊ����
	user* point = head->next;
	while (point != NULL)
	{
		//��ֵ��
		fprintf(user_file, "%d%c", point->level, DataSeg);
		fprintf(user_file, "%d%c", point->exp, DataSeg);
		//�ַ���
		fputs(point->name, user_file); fputc(DataSeg, user_file);
		fputs(point->password, user_file); fputc(DataSeg, user_file);
		fputs(point->tele_num, user_file); fputc(DataSeg, user_file);
		fputs(point->address_1, user_file); fputc(DataSeg, user_file);
		fputs(point->address_2, user_file); fputc(DataSeg, user_file);
		fputs(point->address_3, user_file); fputc(DataSeg, user_file);
		fputs(point->address_default, user_file); fputc(DataSeg, user_file);
		//֪ͨ
		int cnt = CountMessage(point->mlist);
		fprintf(user_file, "%d%c", cnt, DataSeg);
		message* mess = point->mlist->next;
		while (mess != NULL)
		{
			fprintf(user_file, "%s%c", mess->content, DataSeg);
			fprintf(user_file, "%d%c", mess->important, DataSeg);
			mess = mess->next;
		}
		//�Ż�ȯ
		cnt = CountCoupon(point->clist);
		fprintf(user_file, "%d%c", cnt, DataSeg);
		coupon* theCoupon = point->clist->next;
		while (theCoupon != NULL)
		{
			fprintf(user_file, "%s%c", theCoupon->content, DataSeg);
			fprintf(user_file, "%f%c", theCoupon->rate, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->timeLimit, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->cost, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->used, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->time[VALID].tm_year, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->time[VALID].tm_mon, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->time[VALID].tm_mday, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->time[INVALID].tm_year, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->time[INVALID].tm_mon, DataSeg);
			fprintf(user_file, "%d%c", theCoupon->time[INVALID].tm_mday, DataSeg);
			theCoupon = theCoupon->next;
		}
		//����
		point = point->next;
	}
	//�ر��ļ�
	user_file = fclose(user_file);
	if (user_file != NULL)
	{
		printf("%s �ļ��ر�ʧ��\n", txt);
		system("pause");
		return FALSE;
	}
	return TRUE;

}

//��ȡTotalId
int ReadTotalId()
{
	FILE* totalId_file = fopen(TotalId_File_txt, "r");
	if (totalId_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", TotalId_File_txt);
		system("pause");
		return FALSE;

	}
	fscanf(totalId_file, "%u", &totalId);

	fclose(totalId_file);
	return TRUE;
}

//����TotalId
int SaveTotalId()
{
	FILE* totalId_file = fopen(TotalId_File_txt, "w");
	if (totalId_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", TotalId_File_txt);
		system("pause");
		return FALSE;

	}
	fprintf(totalId_file, "%u", totalId);
	fclose(totalId_file);
	return TRUE;
}

//��ȡFund
int ReadFund()
{
	FILE* fund_file = fopen(Fund_File_txt, "r");
	if (fund_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", Fund_File_txt);
		system("pause");
		return FALSE;
	}
	fscanf(fund_file, "%lf", &fund);

	fclose(fund_file);
	return TRUE;
}

//����Fund
int SaveFund()
{
	FILE* fund_file = fopen(Fund_File_txt, "w");
	if (fund_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", Fund_File_txt);
		system("pause");
		return FALSE;

	}
	fprintf(fund_file, "%lf", fund);
	fclose(fund_file);
	return TRUE;
}

//��ȡCoupon
int ReadCoupon()
{
	FILE* coupon_file = fopen(Coupon_File_txt, "r");
	if (coupon_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", Coupon_File_txt);
		system("pause");
		return FALSE;
	}
	coupon* point = NULL;
	while (!feof(coupon_file))
	{
		point = CreatOneCoupon();
		fscanf(coupon_file, "%s", point->content);
		fscanf(coupon_file, "%f", point->rate);
		fscanf(coupon_file, "%d", point->timeLimit);
		fscanf(coupon_file, "%d", point->cost);
		fscanf(coupon_file, "%d", point->used);
		fscanf(coupon_file, "%d", point->time[VALID].tm_year);
		fscanf(coupon_file, "%d", point->time[VALID].tm_mon);
		fscanf(coupon_file, "%d", point->time[VALID].tm_mday);
		fscanf(coupon_file, "%d", point->time[INVALID].tm_year);
		fscanf(coupon_file, "%d", point->time[INVALID].tm_mon);
		fscanf(coupon_file, "%d", point->time[INVALID].tm_mday);
		AddCoupon(chead, point);
	}
	if (point != NULL)
		DeleteOneCoupon(point);

	coupon_file = fclose(coupon_file);
	if (coupon_file != NULL)
	{
		printf("%s �ļ��ر�ʧ��\n", Coupon_File_txt);
		system("pause");
		return FALSE;
	}
	return TRUE;
}

//����Coupon
int SaveCoupon()
{
	FILE* coupon_file = fopen(Coupon_File_txt, "w");
	if (coupon_file == NULL)
	{
		printf("%s �ļ���ʧ��\n", Coupon_File_txt);
		system("pause");
		return FALSE;
	}
	coupon* point = chead->next;
	while (point != NULL)
	{
		fprintf(coupon_file, "%s%c", point->content, DataSeg);
		fprintf(coupon_file, "%f%c", point->rate, DataSeg);
		fprintf(coupon_file, "%d%c", point->timeLimit, DataSeg);
		fprintf(coupon_file, "%d%c", point->cost, DataSeg);
		fprintf(coupon_file, "%d%c", point->used, DataSeg);
		fprintf(coupon_file, "%d%c", point->time[VALID].tm_year, DataSeg);
		fprintf(coupon_file, "%d%c", point->time[VALID].tm_mon, DataSeg);
		fprintf(coupon_file, "%d%c", point->time[VALID].tm_mday, DataSeg);
		fprintf(coupon_file, "%d%c", point->time[INVALID].tm_year, DataSeg);
		fprintf(coupon_file, "%d%c", point->time[INVALID].tm_mon, DataSeg);
		fprintf(coupon_file, "%d%c", point->time[INVALID].tm_mday, DataSeg);
		point = point->next;
	}

	coupon_file = fclose(coupon_file);
	if (coupon_file != NULL)
	{
		printf("%s �ļ��ر�ʧ��\n", Coupon_File_txt);
		system("pause");
		return FALSE;
	}
	return TRUE;
}

//��ȡLogoutTime
int ReadLogoutTime()
{
	FILE* loginTime = fopen(LogoutTime_File_txt, "r");
	if (loginTime == NULL)
	{
		printf("%s �ļ���ʧ��\n", LogoutTime_File_txt);
		system("pause");
		return FALSE;
	}
	fscanf(loginTime, "%d", &(logoutTime.tm_year));
	fscanf(loginTime, "%d", &(logoutTime.tm_mon));
	fscanf(loginTime, "%d", &(logoutTime.tm_mday));
	fscanf(loginTime, "%s", logoutName);
	fscanf(loginTime, "%s", logoutPassword);

	fclose(loginTime);
	return TRUE;
}

//����LogoutTime
int SaveLogoutTime()
{
	FILE* loginTime = fopen(LogoutTime_File_txt, "w");
	if (loginTime == NULL)
	{
		printf("%s �ļ���ʧ��\n", LogoutTime_File_txt);
		system("pause");
		return FALSE;
	}
	fprintf(loginTime, "%d\n", logoutTime.tm_year);
	fprintf(loginTime, "%d\n", logoutTime.tm_mon);
	fprintf(loginTime, "%d\n", logoutTime.tm_mday);
	fprintf(loginTime, "%s\n", logoutName);
	fprintf(loginTime, "%s", logoutPassword);

	fclose(loginTime);
	return TRUE;
}

//���LogoutTime��¼
void ClearLogout()
{
	memset(&logoutTime, 0, sizeof(logoutTime));
	memset(&logoutName, 0, sizeof(logoutName));
	memset(&logoutPassword, 0, sizeof(logoutPassword));
	strcpy(logoutName, DEF_STR);
	strcpy(logoutPassword, DEF_STR);
}

//��¼�˳�ʱ��
void RecordLogoutTime()
{
	struct tm* nowTime = GetNowTime();
	logoutTime.tm_year = nowTime->tm_year;
	logoutTime.tm_mon = nowTime->tm_mon;
	logoutTime.tm_mday = nowTime->tm_mday;
}

//��¼�˳��˺�
void RecordLogoutUser(user* user)
{
	strcpy(logoutName, user->name);
	strcpy(logoutPassword, user->password);
}

//������ʷ��¼-д��
void WritePackHis(package* pack)
{
	if (pack == NULL)return;

	char FILENAME[sizeof(PACK_HIS) + MAX_DATA + sizeof(_TXT) + 1]; 
	memset(FILENAME, 0, sizeof(FILENAME));
	struct tm* nowTime = GetNowTime();
	sprintf(FILENAME, "%s%04d%02d%02d%s",
		PACK_HIS,
		nowTime->tm_year, nowTime->tm_mon, nowTime->tm_mday,
		_TXT);

	FILE* packHis = fopen(FILENAME, "a");//׷��ģʽ-���Զ�����txt
	if (packHis == NULL)return;

	//����
	if (hisCyrTag == CYR)
	{
		fclose(packHis);
		DecyrptFile(FILENAME);
		packHis = fopen(FILENAME, "a");//׷��ģʽ-���Զ�����txt
	}

	//�ַ���
	fputs(pack->id, packHis); fputc(DataSeg, packHis);
	fputs(pack->tele_num, packHis); fputc(DataSeg, packHis);
	fputs(pack->pick_tele_num, packHis); fputc(DataSeg, packHis);
	fputs(pack->pack_name, packHis); fputc(DataSeg, packHis);
	fputs(pack->location, packHis); fputc(DataSeg, packHis);
	fputs(pack->pickupCode, packHis); fputc(DataSeg, packHis);
	fputs(pack->user_name, packHis); fputc(DataSeg, packHis);
	fputs(pack->sender_name, packHis); fputc(DataSeg, packHis);
	fputs(pack->user_address, packHis); fputc(DataSeg, packHis);
	fputs(pack->send_address, packHis); fputc(DataSeg, packHis);
	//������
	fprintf(packHis, "%f%c", pack->Bill, DataSeg);
	fprintf(packHis, "%f%c", pack->weight, DataSeg);
	fprintf(packHis, "%f%c", pack->size, DataSeg);
	fprintf(packHis, "%d%c", pack->isRemoteArea, DataSeg);
	fprintf(packHis, "%d%c", pack->isFragile, DataSeg);
	fprintf(packHis, "%d%c", pack->isValuable, DataSeg);
	fprintf(packHis, "%d%c", pack->isToDoor, DataSeg);
	fprintf(packHis, "%d%c", pack->time[IN][YEAR], DataSeg);
	fprintf(packHis, "%d%c", pack->time[IN][MON], DataSeg);
	fprintf(packHis, "%d%c", pack->time[IN][DAY], DataSeg);
	fprintf(packHis, "%d%c", pack->time[OUT][YEAR], DataSeg);
	fprintf(packHis, "%d%c", pack->time[OUT][MON], DataSeg);
	fprintf(packHis, "%d%c", pack->time[OUT][DAY], DataSeg);
	fprintf(packHis, "%d%c", pack->state, DataSeg);

	fclose(packHis);

	//����
	if (hisCyrTag == CYR)
	{
		CyrptFile(FILENAME);
	}
}

//������ʷ��¼-��ȡ
void ReadPackHis(const struct tm* START,const struct tm* END)
{
	//׼������
	FILE* file = NULL;
	char FILENAME[sizeof(PACK_HIS) + MAX_DATA + sizeof(_TXT) + 1];
	//������START��END
	for (int year = START->tm_year; year <= END->tm_year; year++) {
		memset(FILENAME, 0, sizeof(FILENAME));//���FILENAME
		//�趨��ʼ�·�
		int initMon = 1;
		int endMon = 12;
		if (year == START->tm_year)initMon = START->tm_mon;
		if (year == END->tm_year)endMon = END->tm_mon;
		for (int mon = initMon; mon <= endMon; mon++) {
			//�趨ʼ�պ�ĩ��
			int initDay = 1;
			int endDay = DaysInMonth(year, mon);
			if (year == START->tm_year && mon == START->tm_mon)initDay = START->tm_mday;
			if (year == END->tm_year && mon == END->tm_mon)endDay = END->tm_mday;
			for (int day = initDay; day <= endDay; day++) {
				//�༭�ļ���ʽ
				sprintf(FILENAME, "%s%04d%02d%02d%s",
					PACK_HIS,
					year,mon,day,
					_TXT);
				//�����ļ�
				//�Ƚ���
				file = fopen(FILENAME, "r");
				//����
				if (file != NULL && hisCyrTag == CYR)
				{
					fclose(file);
					DecyrptFile(FILENAME);
					file = fopen(FILENAME, "r");
				}
				if (file != NULL)
				{
					//�ҵ��ļ�
					//ȫ����ȡ
					package* hhead = CreatPackageList();
					package* point = NULL;
					while (!feof(file))
					{
						point = CreatOnePackage();
						//�ַ���
						fscanf(file, "%s", &(point->id));
						fscanf(file, "%s", &(point->tele_num));
						fscanf(file, "%s", &(point->pick_tele_num));
						fscanf(file, "%s", &(point->pack_name));
						fscanf(file, "%s", &(point->location));
						fscanf(file, "%s", &(point->pickupCode));
						fscanf(file, "%s", &(point->user_name));
						fscanf(file, "%s", &(point->sender_name));
						fscanf(file, "%s", &(point->user_address));
						fscanf(file, "%s", &(point->send_address));
						//������
						fscanf(file, "%f", &(point->Bill));
						fscanf(file, "%f", &(point->weight));
						fscanf(file, "%f", &(point->size));
						fscanf(file, "%d", &(point->isRemoteArea));
						fscanf(file, "%d", &(point->isFragile));
						fscanf(file, "%d", &(point->isValuable));
						fscanf(file, "%d", &(point->isToDoor));
						fscanf(file, "%d", &(point->time[IN][YEAR]));
						fscanf(file, "%d", &(point->time[IN][MON]));
						fscanf(file, "%d", &(point->time[IN][DAY]));
						fscanf(file, "%d", &(point->time[OUT][YEAR]));
						fscanf(file, "%d", &(point->time[OUT][MON]));
						fscanf(file, "%d", &(point->time[OUT][DAY]));
						fscanf(file, "%d", &(point->state));
						//����
						AddOnePackage(hhead, point);
					}
					if (point != NULL)
						DeleteOnePackage(point);//ɾ��������
					//���
					point = hhead->next;
					printf("\n--------------�ָ���---------------\n");
					printf("\n%04d��%02d��%02d��\n\n", year, mon, day);
					//printf("\n%s:\n\n", FILENAME);
					while (point != NULL)
					{
						PrintOnePackage(point);
						point = point->next;
					}
					//����
					DeleteAllPackage(hhead);
					fclose(file);
					//�ؼ���
					if (hisCyrTag == CYR)
					{
						CyrptFile(FILENAME);
					}
				}
				//û�ҵ��ļ��ͼ�������
			}
		}
	}
}