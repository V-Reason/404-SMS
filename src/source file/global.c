#include "Front.h"

//启动项
int powerTag;
int cyrTag;
int hisCyrTag;

//三大链表的哨岗head
package* phead;		//包裹链表哨岗
user* uhead;		//用户链表哨岗
user* ahead;		//管理员链表哨岗
coupon* chead;		//优惠券链表哨岗

//货架定义
shelf shelfs[SHELF_NUM][SUB_SHELF_NUM][ROW][LINE];

//调用自增运单号变量
unsigned int totalId = 0;

//财报
double fund = 0.0;

//保存上次登陆的时间
struct tm logoutTime;
char logoutName[MAX_USER_NAME + 1];
char logoutPassword[MAX_PASSWORD_NUM + 1];

//加解密
PublicKey pubKey;
PrivateKey privKey;

////节日定义->放在了Pay.c里
//const festival fes[] =
//{
//	{"元旦",1,1,0.5},
//	{"国庆节",10,1,0.5},
//	{"圣诞节",12,25,0.8},
//	{"双十一",11,11,0.9},
//	{"双十二",12,12,0.9},
//	{"劳动节",5,1,0.5},
//	{"妇女节",3,8,0.9},
//	{"情人节",2,14,0.9}
//};