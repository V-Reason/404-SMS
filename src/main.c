#include "Front.h"
#include "Backend.h"
#include "Frontend.h"

int main()
{
	
	//设定默认值
	powerTag = EXIT;
	cyrTag = DECYR;
	hisCyrTag = DECYR;

	user* user = NULL;
	while (TRUE)
	{
		powerTag = EXIT;
		user = NULL;
		//初始化系统
		InitSys();

		//登陆/注册
		while (user == NULL)
		{
			user = LoginRegisterInterface();
		}

		//进入系统
		if (user->level == TOP_ADMIN)
			TopAdminSys(user);
		else if (user->level == ADMIN)
			AdminSys(user);
		else
			UserSys(user);

		//退出系统
		if (powerTag == EXIT)
		{
			//非注销则清理数据 然后退出系统
			ExitSys();
			break;
		}
		else// if (powerTag == RESTART)
		{
			//会置空LogoutTime_File.txt
			SaveAll();
		}
	}
	
	/*
#pragma region Test
	//初始化系统
	InitSys();

	//模拟配置包裹
	package* pack0 = _CreatOnePackage("0000000000", "12345678901", "美国债卷", STATE_WAIT_PICK);
	strcpy(pack0->pickupCode, "0000");
	PutShelf(pack0, SHELF_A);
	package* pack1 = _CreatOnePackage("1111111111", "12345678901", "魔法少女小圆手办", STATE_ERROR);
	package* pack2 = _CreatOnePackage("2222222222", "12345678901", "BakaFumo玩偶", STATE_WAIT_COLLECT);
	package* pack3 = _CreatOnePackage("3333333333", "12345678901", "MikuMiku", STATE_WAIT_PICK);
	strcpy(pack3->pickupCode, "0001");
	PutShelf(pack3, SHELF_D);
	package* pack4 = _CreatOnePackage("4444444444", "12345678901", "天童爱丽丝手办", STATE_TRANSPORT);
	package* pack5 = _CreatOnePackage("5555555555", "98765432101", "JustFumoFumo", STATE_REJECT);
	package* pack6 = _CreatOnePackage("6666666666", "98765432101", "39Music", STATE_ERROR);
	package* pack7 = _CreatOnePackage("7777777777", "98765432101", "黄金万两", STATE_ERROR);
	package* pack8 = _CreatOnePackage("8888888888", "98765432101", "弱水时砂", STATE_ERROR);
	package* pack9 = _CreatOnePackage("9999999999", "98765432101", "茉莉奶绿", STATE_ERROR);
	package* pack10 = _CreatOnePackage("1234567890", "98765432101", "刀片", STATE_ERROR);
	package* pack11 = _CreatOnePackage("0987654321", "98765432101", "泪水和苦痛", STATE_ERROR);
	AddOnePackage(phead, pack0);
	AddOnePackage(phead, pack1);
	AddOnePackage(phead, pack2);
	AddOnePackage(phead, pack3);
	AddOnePackage(phead, pack4);
	AddOnePackage(phead, pack5);
	AddOnePackage(phead, pack6);
	AddOnePackage(phead, pack7);
	AddOnePackage(phead, pack8);
	AddOnePackage(phead, pack9);
	AddOnePackage(phead, pack10);
	AddOnePackage(phead, pack11);

	//配置用户
	user* user1 = _CreatOneUser("V.Reason", "111", "12345678901", 1);
	user* user2 = _CreatOneUser("Vxiaoshan", "222", "9876543210", 2);
	user* user3 = _CreatOneUser("愚人舟", "333", "12312332111", 3);
	AddUser(uhead, user1);
	AddUser(uhead, user2);
	AddUser(uhead, user3);

	//配置管理员
	user* admin = _CreatOneUser("Admin", "141", "12345678901", ADMIN);
	AddUser(ahead, admin);

	message* mess1 = CreatOneMessage("5我是通知1", 5);
	message* mess2 = CreatOneMessage("5我是通知2", 5);
	message* mess3 = CreatOneMessage("5我是通知3", 5);
	message* mess4 = CreatOneMessage("4我是通知4", 4);
	message* mess5 = CreatOneMessage("4我是通知5", 4);
	message* mess6 = CreatOneMessage("4我是通知6", 4);
	message* mess7 = CreatOneMessage("3我是通知7", 3);
	message* mess8 = CreatOneMessage("3我是通知8", 3);
	message* mess9 = CreatOneMessage("3我是通知9", 3);
	message* mess10 = CreatOneMessage("2我是通知10", 2);
	message* mess11 = CreatOneMessage("1我是通知11", 1);

	Broadcast(mess1, ahead); Broadcast(mess1, uhead);
	Broadcast(mess2, ahead); Broadcast(mess2, uhead);
	Broadcast(mess3, ahead); Broadcast(mess3, uhead);
	Broadcast(mess4, ahead); Broadcast(mess4, uhead);
	Broadcast(mess5, ahead); Broadcast(mess5, uhead);
	Broadcast(mess6, ahead); Broadcast(mess6, uhead);
	Broadcast(mess7, ahead); Broadcast(mess7, uhead);
	Broadcast(mess8, ahead); Broadcast(mess8, uhead);
	Broadcast(mess9, ahead); Broadcast(mess9, uhead);
	Broadcast(mess10, ahead); Broadcast(mess10, uhead);
	Broadcast(mess11, ahead); Broadcast(mess11, uhead);
	
	ExitSys();
		
#pragma endregion
*/
	return 0;
}

