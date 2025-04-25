#include "Backend.h"

//��ȡ��ǰʱ�� ->��װʱ�亯���������Ժ��ã�eg:������
struct tm* GetNowTime()
{
	time_t timecount = time(NULL);
	struct tm* ptime = localtime(&timecount);
	ptime->tm_year += 1900;
	ptime->tm_mon += 1;
	ptime->tm_mday;
	return ptime;
}

//�� 0000.00.00  00:00:00 ��24Сʱ�ĸ�ʽ��ӡ��ǰʱ��
void PrintNowTime()
{
	struct tm* ptime = GetNowTime();
	printf("%d.%d.%d  %02d:%02d:%02d\n",
		ptime->tm_year, ptime->tm_mon, ptime->tm_mday,
		ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
}

//�������ʱ��
void SetPackageInTime(package* pack, int year, int mon, int day)
{
	pack->time[IN][YEAR] = year;   //��
	pack->time[IN][MON] = mon;     //��
	pack->time[IN][DAY] = day;     //��
}

//���ó���ʱ��
void SetPackageOutTime(package* pack, int year, int mon, int day)
{
	pack->time[OUT][YEAR] = year;   //��
	pack->time[OUT][MON] = mon;     //��
	pack->time[OUT][DAY] = day;     //��
}

//�����ж�
int IsLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

//���ָ���·ݵ�����
int DaysInMonth(int year, int mon)
{
	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (mon == 2 && IsLeapYear(year)) {
		return 29;
	}
	return days[mon - 1];
}

//����ĳ��ĳ������ڱ����һ�������
int GetDaysFromStartOfYear(int year, int month, int day)
{
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int totalDays = 0;

	//��������꣬2���� 29 ��
	if (IsLeapYear(year)) {
		daysInMonth[1] = 29;
	}

	//�ۼ�ǰ���·ݵ�����
	for (int i = 0; i < month - 1; i++)
	{
		totalDays += daysInMonth[i];
	}

	//���ϵ�ǰ�·ݵ�����
	totalDays += day;

	return totalDays;
}

//��ȡ������������
int GetPackageStayTime(package* pack)
{
	//�Ƿ������
	if (0 == pack->time[IN][YEAR])
	{
		//δ��⣬����0
		return 0;
	}

	//����⣬��ʼ����
	//������ʱ�������ʱ��ľ�������
	struct tm* ptime = GetNowTime();
	struct tm nowTime;
	memset(&nowTime, 0, sizeof(nowTime));
	nowTime.tm_year = pack->time[IN][YEAR];
	nowTime.tm_mon = pack->time[IN][MON];
	nowTime.tm_mday = pack->time[IN][DAY];

	return GetTimeSeg(ptime, &nowTime);
}

//����ʱ��� time1<time2 ��������		time1>time2 ���ظ���
int GetTimeSeg(struct tm* time1, struct tm* time2)
{
	//��þ���ʱ��
	const int t1
		= GetDaysFromStartOfYear
		(time1->tm_year, time1->tm_mon, time1->tm_mday);
	const int t2
		= GetDaysFromStartOfYear
		(time2->tm_year, time2->tm_mon, time2->tm_mday);

	//�������ʱ��
	int days = 0;
	if (time1->tm_year == time2->tm_year)//��ͬ��ݽ����
	{
		//days = abs(t1 - t2);
		days = t2 - t1;
	}
	else//��ͬ��ݽ����
	{
		for (int y = 0; y < abs(time1->tm_year - time2->tm_year); y++)
		{
			days += IsLeapYear(y) ? 366 : 365;
		}
		//days += abs(t1 - t2);
		days += (t2 - t1);
	}
	return days;
}

int GetTimeSeg_Min(struct tm* time1, struct tm* time2)
{
	if (time1 == NULL || time2 == NULL)return 0;
	return	(time2->tm_hour * 60 + time2->tm_min)
		- (time1->tm_hour * 60 + time1->tm_min);
}

//ʱ��ӷ�����λ���£�
struct tm TimeAdd(const struct tm* timeBefore, const int mon)
{
	struct tm timeAfter = *timeBefore;
	timeAfter.tm_year += (timeBefore->tm_mon + mon) / 12;
	timeAfter.tm_mon = (timeAfter.tm_mon + mon) % 12;
	int maxDays = DaysInMonth(timeAfter.tm_year, timeAfter.tm_mon);
	timeAfter.tm_mday = min(timeAfter.tm_mday, maxDays);
	return timeAfter;
}

//��ʱ�����ݱ���ַ���2006��01��05��
void TimeToStr(char* buffer, struct tm* time)
{
	if (time->tm_year == 0)
	{
		sprintf(buffer, "NULL");
		return;
	}

	sprintf(buffer, "%04d%02d%02d",
		time->tm_year, time->tm_mon, time->tm_mday);
	return;
}