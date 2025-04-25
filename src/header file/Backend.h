#pragma once
#ifndef Backend
#define Backend
#include "Front.h"

//文件读取-向前声明
//以下函数若执行失败则均返回FALSE
void Replace_nto0(char* str);//将字符串里的\n转换成\0
int ReadAll();//读取全部文件
int SaveAll();//保存全部文件
void CyrAll();//加密所有文件
void DecyrAll();//解密所有文件
void CyrHis();//加密所有历史记录文件
void DecyrHis();//解密所有历史记录文件
void InitFile();//初始化txt文件
int ReadLogoutTime();//读取LoginTime
int SaveLogoutTime();//保存LoginTime
void ClearLogout();//清空Logout记录
void RecordLogoutTime();//记录退出时间
void RecordLogoutUser(user* user);//记录账号

int ReadInit();
int SaveInit();
int ReadHisInit();
int SaveHisInit();
int ReadFund();//读取Fund
int SaveFund();//保存Fund
int ReadCoupon();//读取Coupon
int SaveCoupon();//保存Coupon
int ReadTotalId();//读取TotalId
int SaveTotalId();//保存TotalId
int ReadPackage();//读取包裹
int SavePackage();//保存包裹
int ReadUser(const char* txt, user* head);//读取用户 传入参数用于区分uhead和ahead
int SaveUser(const char* txt, user* head);//保存用户
void WritePackHis(package* pack);//包裹历史记录-写入;
void ReadPackHis(const struct tm* START, const struct tm* END);//包裹历史记录-读取
void InitSys();//初始化程序
void ExitSys();//不退出程序 保存所有数据 并清除所有链表

//包裹操作-向前声明
//int JudgePackage(package* pack);//判断单个包裹数据是否合法
void TFtoStr(char* buffer, int tf);//将TRUE/FALSE转换成 是/否
void StateToStr(char* buffer, packageState state);//将state转换成字符串
void PrintAllPackage(package* head);//只能由顶级管理员调用 打印head之后的所有包裹，自动判断是否为head,而不打印head
void PrintNumPackage(package* head, int num);//打印指定数量的包裹，自动判断是否为head,而不打印head
void PrintOnePackage(package* pack);//打印单个pack包裹
int CountPackage(package* head);//计算head及其之后的有效包裹数量，自动判断是否为head,而不计入head
void AssignId(package* pack);//计算head及其之后的有效包裹数量，自动判断是否为head,而不计入head
package* CreatPackageList();//创建包裹链表
package* CreatOnePackage();//创建一个package,返回创建的package的指针,传入值为-1或DEFAULT时表示不修改
package* _CreatOnePackage(char* id, char* tele_num, char* pack_name, packageState state);
//void ModifyPackage(package* pack);//该函数已经转移至前端 //修改pack的数值 //不包括prior和next指针,传入值为-1或DEFAULT时表示不修改
void AddOnePackage(package* head, package* pack);//在链表末尾添加一个package
void AddMultiplePackage(package* head, package* packs);//在链表末尾添加多个package 自动判断head是否存在，并忽略和释放head
void InsertOnePackage(package* head, package* pack);//在head后边插入一个package 自动检测head并报错
void InsertMultiplePackage(package* head, package* packs);//在head后面插入多个package 自动检测head，并忽略和释放head
void TakeOutOnePackage(package* nhead, package* pack);//从head取出单个包裹pack，放入另一个链表nhead尾部
void DeleteOnePackage(package* pack);//释放单个pack 会把入库的包裹的货架状态变FALSE 不可用于释放head 自动检测head并报错
void DeleteAllPackage(package* head);//释放head及之后的所有pack
package* AdminFindPackage(package* head, char* str);//管理员查找多个包裹，将查找到的包裹组成链表后放置到head末尾，返回第一个找到的包裹的地址
package* UserFindPackage(package* head, user* _user);//用户查找自己的包裹
void PackageCheck(package* head, message* messhead);//包裹全面检查
void PackageSort(package* head);//包裹排序-基于状态,必须传入哨兵

//用户操作-向前声明
void PrintOneUser(user* head);//打印单个用户信息
void PrintAllUser(user* head);//打印所有用户信息
void PrintOneAdmin(user* head);//打印指定数量的用户,自动判断head
void PrintNumAdmin(user* head, int num);//打印指定数量的用户,自动判断head
int CountUser(user* head);//计算用户数量
//int JudgeUser(user* puser);//该函数已经作废 判断用户数据是否合法  没写完
user* CreatUserList();//创建用户链表
user* CreatOneUser();//创建用户对象 传入DEFAULT表示默认值0
user* _CreatOneUser(char* name, char* password, char* tele_num, int level);//仅测试使用函数  创建用户对象 传入DEFAULT表示默认值0
void AddUser(user* head, user* _user);//将用户信息添加至链表末尾
void DeleteOneUser(user* _user);//删除单个用户信息
void DeleteAllUser(user* head); //删除包括head在内的所有用户信息
user* FindUser(user* head, char* str);//基于名字和电话 查找用户信息 返回找到的用户指针 否则返回NULL
int isRepeatName(const char* name);//名字是否重复
int isRepeatTele(const char* teleNum);//手机号查重复

//货架操作-向前声明
void InitShelf();//初始化货架 必须在读取包裹文件后执行
int PutShelf(package* pack, int num);//将包裹放入货架
int GetShelf(package* pack);//从货架取出包裹
int CountUsedShelf(int n);//计算使用货架数量 传入货架号 ABCD 内部调用了CountEmptyShelf
int CountEmptyShelf(int n);//计算空货架数量 传入货架号 ABCD
void PrintAllShelf();//打印货架状态 目前打印空货架数量
//int JudgeLocation(package* pack);//已作废，为包裹分配存放位置 返回存放编号 若没空位了则返回ERROR
int AllocateLocation(package* pack, user* ahead);//为包裹“智能”分配位置，内部调用多个函数，若没空位则返回FALSE,发配同时自动检测是否达到警戒线，若有则向全体管理员发通知
void SetPickupCode(package* pack);//发配取件码  0000~9999
shelf* StrToShelf(const char* str);//将字符串转化为shelf
void ModifyShelf(shelf* theShelf);//修改货架状态

//通知操作-向前声明
message* CreatMessageList();//创建头结点
message* CreatOneMessage(char* content, int important);//创建单个message 传入DEFAULT 可设定为默认值
void MessageSort(message* head);//通知排序算法（冒泡排序）传入值必须是哨兵
void PrintOneMessage(message* mess);//打印单个通知
void PrintNumMessage(message* head, int num);//打印指定数量通知
void PrintAllMessage(message* head);//打印所有通知
void AddMessage(message* head, message* mes);//添加Message节点 添加完后立刻排序
void DeleteOneMessage(message* mess);//删除单个通知
void DeleteAllMessage(message* head);//删除head在内的所有通知
int CountMessage(message* mhead);//计算通知数量
message* CpyMessage(message* mess);//复制通知 返回新mess

//优惠卷
coupon* CreatCouponList();
coupon* CreatOneCoupon();
coupon* CpyCoupon(coupon* theCoupon);
void AddCoupon(coupon* chead, coupon* theCoupon);
void DeleteOneCoupon(coupon* theCoupon);
void DeleteAllCoupon(coupon* head);
int CountCoupon(coupon* head);
int UseCoupon(coupon* theCoupon);
void PrintAllCoupon(coupon* head);
void PrintNumCoupon(coupon* head, const int num);
void PrintOneCoupon(coupon* theCoupon);
void RefreshCoupon(coupon* chead);

//时间操作-向前声明
struct tm* GetNowTime();//获取当前时间
void PrintNowTime();//以 0000.00.00  00:00:00 的24小时的格式打印当前时间
int IsLeapYear(int year);//闰年判断
int DaysInMonth(int year, int mon);//获得指定月份的天数
int GetDaysFromStartOfYear(int year, int month, int day);//计算某月某日相对于本年第一天的天数
int GetPackageStayTime(package* pack);//获取包裹滞留天数
void SetPackageInTime(package* pack, int year, int mon, int day);//设置入库时间
void SetPackageOutTime(package* pack, int year, int mon, int day);//设置出库时间
int GetTimeSeg(struct tm* time1, struct tm* time2);//计算时间差 time1<time2 返回正数		time1>time2 返回负数
int GetTimeSeg_Min(struct tm* time1, struct tm* time2);
struct tm TimeAdd(const struct tm* timeBefore, const int mon);//时间加法（单位：月）

//加密解密-向前声明
ll gcd(ll a, ll b);//计算并返回最大公约数
ll mod_exp(ll base, ll exp, ll mod);//计算并返回 a^b mod m
ll mod_inverse(ll a, ll b);//计算模反元素
void generate_keys(ll p, ll q, PublicKey* pubKey, PrivateKey* priKet);//生成 RSA 密钥对
ll encrypt(ll message, PublicKey pubKey);//加密 返回密文
ll decrypt(ll message, PrivateKey privKey);//解密 返回明文
void CyrptFile(const char* oriTxt);//将所有文件加密,直接调用就行
void DecyrptFile(const char* oriTxt);//将所有文件解密,直接调用就行
void InitKey();//初始化私钥和公钥 ，记得调用


//后端扩展->向前声明
int isAllDigits(const char* str);//判断字符串是否全是数字 内部调用isdigit()
void InputBox(char* str, int maxLen, int mode, int esc);//无阻塞输入，键入即写入，可自定义设置最大输入字符数maxLen,内容保存为str  可设置掩码输入，第三传参若为 SHOW则为非掩码，HIDE则为掩码,PASSWORD则为用*覆盖
void SetCursorPosition(int x, int y);//设置光标位置
void InitConsole();//初始化控制台设置
void CursorShow();//光标显示
void CursorHide();//光标隐藏
void CheckAll(package* phead, user* adminHead);//全面检查 包裹、货架 并广播消息
void CheckShelfs(user* adminHead);//检查货架 并广播消息
void CheckPackage(package* phead, user* adminHead);//检查包裹 并广播消息
void Broadcast(message* mess, user* head);//向全体指定群体广播消息,向用户则传入uhead,向管理员则传入ahead
void TimeToStr(char* buffer, struct tm* time);//将时间数据变成字符串2006年01月05日

#endif