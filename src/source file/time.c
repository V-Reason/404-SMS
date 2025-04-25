#include "Backend.h"

//获取当前时间 ->封装时间函数，用于以后用，eg:纪念日
struct tm* GetNowTime()
{
	time_t timecount = time(NULL);
	struct tm* ptime = localtime(&timecount);
	ptime->tm_year += 1900;
	ptime->tm_mon += 1;
	ptime->tm_mday;
	return ptime;
}

//以 0000.00.00  00:00:00 的24小时的格式打印当前时间
void PrintNowTime()
{
	struct tm* ptime = GetNowTime();
	printf("%d.%d.%d  %02d:%02d:%02d\n",
		ptime->tm_year, ptime->tm_mon, ptime->tm_mday,
		ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
}

//设置入库时间
void SetPackageInTime(package* pack, int year, int mon, int day)
{
	pack->time[IN][YEAR] = year;   //年
	pack->time[IN][MON] = mon;     //月
	pack->time[IN][DAY] = day;     //日
}

//设置出库时间
void SetPackageOutTime(package* pack, int year, int mon, int day)
{
	pack->time[OUT][YEAR] = year;   //年
	pack->time[OUT][MON] = mon;     //月
	pack->time[OUT][DAY] = day;     //日
}

//闰年判断
int IsLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

//获得指定月份的天数
int DaysInMonth(int year, int mon)
{
	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (mon == 2 && IsLeapYear(year)) {
		return 29;
	}
	return days[mon - 1];
}

//计算某月某日相对于本年第一天的天数
int GetDaysFromStartOfYear(int year, int month, int day)
{
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int totalDays = 0;

	//如果是闰年，2月有 29 天
	if (IsLeapYear(year)) {
		daysInMonth[1] = 29;
	}

	//累加前面月份的天数
	for (int i = 0; i < month - 1; i++)
	{
		totalDays += daysInMonth[i];
	}

	//补上当前月份的天数
	totalDays += day;

	return totalDays;
}

//获取包裹滞留天数
int GetPackageStayTime(package* pack)
{
	//是否入库检测
	if (0 == pack->time[IN][YEAR])
	{
		//未入库，返回0
		return 0;
	}

	//已入库，开始计算
	//获得入库时间和现在时间的绝对天数
	struct tm* ptime = GetNowTime();
	struct tm nowTime;
	memset(&nowTime, 0, sizeof(nowTime));
	nowTime.tm_year = pack->time[IN][YEAR];
	nowTime.tm_mon = pack->time[IN][MON];
	nowTime.tm_mday = pack->time[IN][DAY];

	return GetTimeSeg(ptime, &nowTime);
}

//计算时间差 time1<time2 返回正数		time1>time2 返回负数
int GetTimeSeg(struct tm* time1, struct tm* time2)
{
	//获得绝对时间
	const int t1
		= GetDaysFromStartOfYear
		(time1->tm_year, time1->tm_mon, time1->tm_mday);
	const int t2
		= GetDaysFromStartOfYear
		(time2->tm_year, time2->tm_mon, time2->tm_mday);

	//计算相对时间
	int days = 0;
	if (time1->tm_year == time2->tm_year)//相同年份解决法
	{
		//days = abs(t1 - t2);
		days = t2 - t1;
	}
	else//不同年份解决法
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

//时间加法（单位：月）
struct tm TimeAdd(const struct tm* timeBefore, const int mon)
{
	struct tm timeAfter = *timeBefore;
	timeAfter.tm_year += (timeBefore->tm_mon + mon) / 12;
	timeAfter.tm_mon = (timeAfter.tm_mon + mon) % 12;
	int maxDays = DaysInMonth(timeAfter.tm_year, timeAfter.tm_mon);
	timeAfter.tm_mday = min(timeAfter.tm_mday, maxDays);
	return timeAfter;
}

//将时间数据变成字符串2006年01月05日
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