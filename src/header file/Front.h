#pragma once
#ifndef Front
#define Front

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <direct.h>
//#include <pthread.h>
#include <Windows.h>

//系统凌晨
#define SYS_MIDNIGHT_HOUR	0
#define SYS_MIDNIGHT_MIN	0

//其它
#define TITLE L"404驿站系统"
#define _TITLE "404驿站系统"
#define GBK  936
#define DEFUALT_TOPADMIN_NAME	"TopAdmin"
#define DEFUALT_ADMIN_NAME	    "Admin"
#define DEFUALT_ADMIN_PASSWORD	"12345"

//普遍宏
#define ERROR	 -1
#define NO_ERROR  0
#define DEFAULT   0
#define DEF_STR	  "NULL"
#define DEF_NUM	  0

#define TRUE    1
#define FALSE   0

#define ON		1
#define OFF		0

#define IN  0
#define OUT 1

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

//时间
#define YEAR 0
#define MON  1
#define DAY  2

//按键宏
#define REGISTER	'0'
#define LOGIN		'1'
#define RETRY		'r'
#define _RETRY		"r"

#define ESC			 27
#define BUTTON_LEFT  'a'
#define BUTTON_RIGHT 'd'


//InputBox模式
#define MODE_SHOW		0
#define MODE_HIDE		1
#define MODE_PASSWORD	2
#define MODE_KEY		3
#define MODE_NUM		4

//搜索函数用
#define _ID			0
#define _TELE		1
#define _STATE		2
#define _PACK_NAME	3

//消息循环用
//ModifyPackageInterface：
#define RULE		'0'
#define PAY_RULE	'1'
#define STATE		'2'

#define TELE		'3'
#define USER		'4'
#define SENDER		'5'
#define USER_ADDR	'6'
#define SENDER_ADDR	'7'

#define BILL		'8'
#define WEIGHT		'9'
#define SIZE		'a'
#define FAR_AREA	'b'
#define FRAG		'c'
#define VALU		'd'
#define TODOOR		'e'

//EnterPackage:
#define ID			 'I'
#define PACK_NAME    'A'
#define LOCATION	 'B'
#define PICKCODE	 'C'
#define COUPON		 'D'
#define ALLRIGHT	 '`'

//ModifyUserInterface:
#define NAME		 '1'
#define TELENUM		 '2'
#define PASSWORD	 '3'
#define DEFUALT_ADDR '4'
#define ADDR_1		 '5'
#define ADDR_2		 '6'
#define ADDR_3	 	 '7'
#define CANCEL		 '`'


//翻页函数用
#define PAGE_NUM   5
#define ADMIN_NUM  5
#define MESS_NUM   5

//字符限制
#define MAX_ID		      10
#define MAX_TELE_NUM      11
#define MAX_PACK_NAME     20
#define MAX_USER_NAME     20	//注意，不要太小，因为默认名称很长
#define MAX_PASSWORD_NUM  20
#define MIN_PASSWORD_NUM  10
#define MAX_SEARCH_LENGTH 100
#define MAX_LOCATION      6
#define MAX_ADDRESS		  40
#define MAX_MESSAGE		  250
#define MAX_STAY_DAYS     7
#define MAX_PICKUP_CODE   4
#define MAX_NUM			  10
#define MAX_STATE		  10
#define MAX_TF			  3
#define MAX_DATA		  8

//货架从A0开始计数
#define ROW  10		//货架行数 不可超过10
#define LINE 10		//货架列数 不可超过10
#define SHELF_NUM	  4
#define SUB_SHELF_NUM 4
#define SHELF_A 0
#define SHELF_B 1
#define SHELF_C 2
#define SHELF_D 3
#define WARNING_LINE 10 //货架空位警戒线
#define WARNING_DAY  5  //包裹滞留时间警戒线

//文件IO
#define DataSeg		'\n'
#define StructSeg	'\n'
//#define Shelfs_File_txt		"./Shelfs_File.txt"
#define Init_File_txt		"./Init_File.txt"
#define His_Init_File_txt		"./History/Init_His.txt"
#define User_File_txt		"./Resource/User_File.txt"
#define Admin_File_txt		"./Resource/Admin_File.txt"
#define Package_File_txt	"./Resource/Package_File.txt"
#define TotalId_File_txt	"./Resource/TotalId_File.txt"
#define Fund_File_txt		"./Resource/Fund_File.txt"
#define Coupon_File_txt		"./Resource/Coupon_File.txt"
#define LogoutTime_File_txt	"./Resource/LogoutTime_File.txt"
#define PACK_HIS			"./History/Package_His"
#define _TXT				".txt"
#define RES_FOLDER			"Resource"
#define HIS_FOLDER			"History"
#define _CRY				"/Cry_"

//收费标准
#define BASS_RATE	1.25
#define VOLUME_RATE	0.005
#define FAR_SUR		3
#define FRAG_SUR	2
#define VALU_SUR	3
#define TODOOR_SUR	2
#define LEVEL_RATE  0.05

//货架分配标准
#define MEDIUM	8000	//20^3
#define LARGE	1000000 //100^3

//退出系统判断用
#define EXIT	0   //不可设置成1
#define RESTART 1   //不可设置成0

#define DECYR	0   //不可设置成1
#define CYR		1   //不可设置成0

//自动登陆间隔（单位：天）
#define AutoLogin_TimeSeg		3

//定时操作间隔（单位：分钟）
#define AutoRegular__TimeSeg_S	10
#define AutoRegular__TimeSeg_L	30

//包裹排序权重阈值
#define SORT_THRESHOLD	5

//内购相关
#define MIN_TOPUP	10
#define MAX_COUPON	30
//#define COUPON_NUM	3
#define VALID	0
#define INVALID	1

//Exp规则
// 最大Exp：4001
// 一级：0~500
// 二级：501~1000
// 三级：1001~1500
// 四级：1501~2000
// 五级：2001~2500
// 每日签到+10
// 寄包裹+100
// 充值+1000/10元
// ect.
//tip:MAX_INT==21,4748,3647
#define MAX_EXP	2500
#define MIN_PAY	MIN_TOPUP
#define LEVEL_STEP		500
#define EVENT_SignIn	1
#define EXP_SignIn		10
#define EVENT_SendPack	2
#define EXP_SendPack	100
#define EVENT_TopUp		3
#define EXP_TopUp		1000

//自定义变量类型->向前声明
typedef unsigned long long ull;
typedef long long ll;

//包裹状态
typedef enum packageState
{
	STATE_ERROR	= 0,	//异常、滞留、等等
	STATE_STAY_LONG,	//存放过久
	STATE_WAIT_PICK,	//待签收
	STATE_TRANSPORT,	//运输中
	STATE_WAIT_COLLECT,	//待揽收
	STATE_REJECT,		//拒收
	STATE_PICKUPED		//已签收
}packageState;

//通知重要性->调整重要性就调整这里
typedef enum messageImportant
{
	IMP_NORMAL = 0,		//普通
	IMP_STAYLONG,		//滞留过久
	IMP_REJECT,			//拒收包裹
	IMP_SHELF,			//货架不足
	IMP_PACKERRO,		//包裹异常
	IMP_SPECIAL,		//特别的  eg:节日折扣通知
	IMP_USER			//用户申诉
}messageImportant;

//用户等级
typedef enum userLevel {
	TOP_ADMIN = -1,
	ADMIN = 0,
	NORMAL_USER = 1,
	POWER_USER,
	SUPER_USER,
	PRO_USER,
	Ultra_USER
}userLevel;

//包裹对象
typedef struct package //一共
{
	char id[MAX_ID + 1];				  //10位运单号
	char tele_num[MAX_TELE_NUM + 1];	  //11电话号码
	char pick_tele_num[MAX_TELE_NUM + 1]; //取件人11电话号码
	char pack_name[MAX_PACK_NAME + 1];	  //20位包裹名称
	char location[MAX_LOCATION + 1];	  //3位存放地点 A0_1,2
	char pickupCode[MAX_PICKUP_CODE + 1]; //4位取件码   2333

	char user_name[MAX_USER_NAME + 1];	//10位用户名（收件人）
	char sender_name[MAX_USER_NAME + 1];//10位寄件人姓名
	char user_address[MAX_ADDRESS + 1];	//40位收件人地址
	char send_address[MAX_ADDRESS + 1];	//40位寄件人地址

	float Bill;			 // 运费
	float weight;        // 重量（kg）
	float size;			 // 体积
	int isRemoteArea;    // 是否偏远地区（1：是，0：否）
	int isFragile;       // 是否易碎品（1：是，0：否）
	int isValuable;		 // 是否为贵重物品，0为非贵重，1为贵重
	int isToDoor;		 // 是否送货上门

	int time[2][3];		 //滞留天数,IN/0为入库时间，OUT/1为出库时间,若时间为空则用-1表示（一定要初始化e）,012分别为年月日
	packageState state;  //包裹状态

	//struct user* owner;		//用于追踪 不用于打印地址 否则
	//struct user* sender;	//用于追踪
	struct package* prior;
	struct package* next;
}package;

//用户对象
typedef struct user 
{					//创建用户结构体
	int level;							//用户等级，0为管理员
	int exp;							//经验值
	char name[MAX_USER_NAME + 1];		//10位以内用户名	
	char password[MAX_PASSWORD_NUM + 1];//20位以内密码
	char tele_num[MAX_TELE_NUM + 1];	//11位电话号码

	char address_1[MAX_ADDRESS + 1];
	char address_2[MAX_ADDRESS + 1];
	char address_3[MAX_ADDRESS + 1];
	char* address_default;

	struct message* mlist; //messageList
	struct coupon* clist;
	struct user* prior;
	struct user* next;
} user;
typedef user _User;

//通知
typedef struct message 
{
	char content[MAX_MESSAGE + 1];	//数组用来存放信息,最高100位
	messageImportant important;					//信息重要程度，越大重要程度越高,0为普通,1为过久未取，2为货架将满，3为包裹异常
	struct message* prior;
	struct message* next;
} message;

//优惠卷
typedef struct coupon
{
	char content[MAX_COUPON + 1];	//内容描述
	float rate;						//倍率
	int timeLimit;					//时效 单位：月
	int cost;						//购买所需价格
	struct tm time[2];				//生效日期和截止日期
	int used;						//标记是否使用

	struct coupon* prior;
	struct coupon* next;
}coupon;

//货架对象
typedef struct shelf {
	char location[MAX_LOCATION + 1];//标记存放位置  eg: A0_1,2
	int used;						//标记是否使用
	char pack_id[MAX_ID + 1];		//存储运单号
}shelf;

//公匙
typedef struct {
	long long e;
	long long n;
} PublicKey;

//私匙
typedef struct {
	long long d;
	long long n;
} PrivateKey;

//节日
typedef struct festival
{
	char name[10];	//节日名称
	int month;		//节日月份
	int day;		//节日日期
	float discount; //折扣小数值
}festival;

//四大链表的哨岗head
extern package* phead;	//包裹链表哨岗
extern user* uhead;		//用户链表哨岗
extern user* ahead;		//管理员链表哨岗
extern coupon* chead;	//优惠券链表哨岗

//货架定义
extern shelf shelfs[SHELF_NUM][SUB_SHELF_NUM][ROW][LINE];

//调用自增运单号变量
extern unsigned int totalId;

//财报
extern double fund;

//节日定义
extern const festival fes[];

//保存上次登陆的时间
extern struct tm logoutTime;
extern char logoutName[MAX_USER_NAME + 1];
extern char logoutPassword[MAX_PASSWORD_NUM + 1];

//加解密
extern PublicKey pubKey;
extern PrivateKey privKey;

//启动项
extern int powerTag;
extern int cyrTag;
extern int hisCyrTag;

#endif