#include "Backend.h"

coupon* CreatCouponList()
{
	coupon* head = (coupon*)malloc(sizeof(coupon));
	memset(head, 0, sizeof(coupon));
	return head;
}

coupon* CreatOneCoupon()
{
	coupon* theCoupon = (coupon*)malloc(sizeof(coupon));
	memset(theCoupon, 0, sizeof(coupon));
	return theCoupon;
}

coupon* CpyCoupon(coupon* theCoupon)
{
	coupon* newCoupon = CreatOneCoupon();
	strcpy(newCoupon->content, theCoupon->content);
	newCoupon->rate = theCoupon->rate;
	newCoupon->timeLimit = theCoupon->timeLimit;
	newCoupon->cost = theCoupon->cost;
	newCoupon->time[VALID] = theCoupon->time[VALID];
	newCoupon->time[INVALID] = theCoupon->time[INVALID];
	return newCoupon;
}

void AddCoupon(coupon* chead,coupon* theCoupon)
{
	while (chead->next != NULL)
	{
		chead = chead->next;
	}
	chead->next = theCoupon;
	theCoupon->prior = chead;
}

void DeleteOneCoupon(coupon* theCoupon)
{	
	if (theCoupon->next == NULL)
	{
		if (theCoupon->prior == NULL)
		{
			free(theCoupon);
			return;
		}
		theCoupon->prior->next = NULL;
		free(theCoupon);
		return;
	}
	theCoupon->prior->next = theCoupon->next;
	theCoupon->next->prior = theCoupon->prior;
	free(theCoupon);
}

void DeleteAllCoupon(coupon* head)
{
	while (head->next != NULL)
	{
		head = head->next;
		free(head->prior);
	}
	free(head);
}

int CountCoupon(coupon* head)
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

void PrintAllCoupon(coupon* head)
{
	if (head == NULL)return;

	if (head->prior == NULL)head = head->next;

	int cnt = 1;
	printf("  内容\t是否使用\t生效日期\t截止日期\n");
	while (head != NULL)
	{
		char TF[5];
		TFtoStr(TF, head->used);
		printf("%d.%s\t%s\t%04d%02d%02d\t%04d%02d%02d\n",
			cnt, head->content,TF,
			head->time[VALID].tm_year, head->time[VALID].tm_mon, head->time[VALID].tm_mday,
			head->time[INVALID].tm_year, head->time[INVALID].tm_mon, head->time[INVALID].tm_mday);
		cnt++;
		head = head->next;
	}
}

void PrintNumCoupon(coupon* head,const int num)
{
	if (head == NULL)return;

	if (head->prior == NULL)head = head->next;

	int cnt = 1;
	printf("  内容\t是否使用\t生效日期\t截止日期\n");
	while (head != NULL && cnt <= num)
	{
		char TF[5];
		TFtoStr(TF, head->used);
		printf("%d.%s\t%s\t%04d%02d%02d\t%04d%02d%02d\n",
			cnt, head->content, TF,
			head->time[VALID].tm_year, head->time[VALID].tm_mon, head->time[VALID].tm_mday,
			head->time[INVALID].tm_year, head->time[INVALID].tm_mon, head->time[INVALID].tm_mday);
		cnt++;
		head = head->next;
	}
}

void PrintOneCoupon(coupon* theCoupon)
{
	if (theCoupon == NULL)return;

	char TF[5];
	TFtoStr(TF, theCoupon->used);

	printf("内容：%s\n", theCoupon->content);
	printf("倍率：%f\n", theCoupon->rate);
	printf("时效：%d 个月\n", theCoupon->timeLimit);
	printf("价格：%d\n", theCoupon->cost);
	printf("是否使用：%s\n", TF);
}

int UseCoupon(coupon* theCoupon)
{
	if (theCoupon->used = TRUE)
		return FALSE;
	//允许同时使用多个券

	theCoupon->used = TRUE;
	struct tm* nowTime = GetNowTime();
	theCoupon->time[VALID].tm_year = nowTime->tm_year;
	theCoupon->time[VALID].tm_mon = nowTime->tm_mon;
	theCoupon->time[VALID].tm_mday = nowTime->tm_mday;
	theCoupon->time[INVALID] = TimeAdd(&(theCoupon->time[VALID]), theCoupon->timeLimit);

	return TRUE;
}

void RefreshCoupon(coupon* chead)
{
	coupon* point = chead->next;
	while (point != NULL)
	{
		struct tm* nowTime = GetNowTime();
		if (GetTimeSeg(nowTime, &(point->time[INVALID])) < 0)
		{
			if (point->next == NULL)
			{
				DeleteOneCoupon(point);
			}
			else
			{
				point = point->next;
				DeleteOneCoupon(point->prior);
			}
		}
		else
		{
			point = point->next;
		}
	}
}