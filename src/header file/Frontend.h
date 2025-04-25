#pragma once
#ifndef Frontend
#define Frontend
#include "Backend.h"

//前端操作-向前声明
user* LoginRegisterInterface();//注册账号 只允许用户注册 返回注册的用户
char LoginOrRegister();//登陆/注册选择函数 返回LOGIN/REGISTER 失败退出系统
int UserOrAdmin();//用户/管理员选择函数 返回level 失败返回ERROR
user* Login(const char* inf, user* head);//输入账号密码 传入参数head作为区分uhead和ahead 返回登陆的用户
user* Register(user* head);//注册账号 只允许用户注册 返回注册的用户
void TopAdminSys(user* admin);//进入顶级管理员系统 详见定义
void AdminSys(user* admin);//进入管理员操作系统 详见定义
void UserSys(user* user);//进入用户操作系统 详见定义
void MessSys(user* user);//消息操作系统
int EnterPackage(package* pack);//手动录入包裹 成功返回TRUE 失败返回FALSE
int SendPackage(user* user, package* pack);//用户邮寄包裹
void CheckCoupon(user* user);//用户使用优惠券界面
void RejectPackageInterface(package* head);//拒收包裹界面
void EditPackage(package* head);//管理员编辑查询到的包裹
void EditAdmin(user* head);//管理员编辑查询到的用户
void ModifyPackageInterface(package* pack);//选择性修改包裹-界面
int ModifyPackage(package* pack, const char _key, const char* information, const int inputMode, const int MaxLen);//选择性修改包裹-深层函数
int ModifyUserInterface(user* user);//选择性修改用户-界面
void ModifyAdminInterface(user* admin);//选择性修改管理员-界面
int ModifyUser(user* user, const char _key, const char* information, const int inputMode, const int MaxLen);//选择性修改用户-深层函数
void ModifyState(package* pack);//修改包裹状态
void ModifyDefaulatAddress(user* user);//修改默认地址
int ModifyMessage(message* mess);//目前只作为前端删除通知的函数  若删除成功则返回TRUE 否则返回FALSE
int JungePackageInformation(const char key, const char* information);//判断输入的包裹信息是否符合规定
int JungeUserInformation(const char key, const char* input);//判断个人信息函数
void SaveOption();//保存选项
void UserRegular(user* user);//用户定时完成后的操作函数
void AdminRegular_S(user* user);//管理员短定时完成后的操作函数
void AdminRegular_L(user* user);//管理员长定时完成后的操作函数
void GoThroughPackage();//遍历包裹状态

//增值-向前声明
//等级计算公式
float CalculateBill(user* user, package* pack);//返回运费
void PrintBillSchedule();//打印收费标准
void PrintInputRule();//打印填写规则
festival* isFestival();//判断今日是否是节日,是则返回节日，否则返回NULL
void GainExp(const int event, user* user);//获得经验值

//内购
void ManagePay();//内购管理
void GainExp(const int event, user* user);//获得经验值
void UserPay(user* user);//用户内购
void BuyExp(user* user);//购买exp
void BuyCoupon(user* user);//购买优惠券
void PrintExpRule();//打印等级规则

//优惠券
void IssueCoupon(coupon* cpyCoupon);//发行优惠券
void EditCoupon();//管理优惠券

#endif