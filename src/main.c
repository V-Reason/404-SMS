#include "Front.h"
#include "Backend.h"
#include "Frontend.h"

int main()
{
	
	//�趨Ĭ��ֵ
	powerTag = EXIT;
	cyrTag = DECYR;
	hisCyrTag = DECYR;

	user* user = NULL;
	while (TRUE)
	{
		powerTag = EXIT;
		user = NULL;
		//��ʼ��ϵͳ
		InitSys();

		//��½/ע��
		while (user == NULL)
		{
			user = LoginRegisterInterface();
		}

		//����ϵͳ
		if (user->level == TOP_ADMIN)
			TopAdminSys(user);
		else if (user->level == ADMIN)
			AdminSys(user);
		else
			UserSys(user);

		//�˳�ϵͳ
		if (powerTag == EXIT)
		{
			//��ע������������ Ȼ���˳�ϵͳ
			ExitSys();
			break;
		}
		else// if (powerTag == RESTART)
		{
			//���ÿ�LogoutTime_File.txt
			SaveAll();
		}
	}
	
	/*
#pragma region Test
	//��ʼ��ϵͳ
	InitSys();

	//ģ�����ð���
	package* pack0 = _CreatOnePackage("0000000000", "12345678901", "����ծ��", STATE_WAIT_PICK);
	strcpy(pack0->pickupCode, "0000");
	PutShelf(pack0, SHELF_A);
	package* pack1 = _CreatOnePackage("1111111111", "12345678901", "ħ����ŮСԲ�ְ�", STATE_ERROR);
	package* pack2 = _CreatOnePackage("2222222222", "12345678901", "BakaFumo��ż", STATE_WAIT_COLLECT);
	package* pack3 = _CreatOnePackage("3333333333", "12345678901", "MikuMiku", STATE_WAIT_PICK);
	strcpy(pack3->pickupCode, "0001");
	PutShelf(pack3, SHELF_D);
	package* pack4 = _CreatOnePackage("4444444444", "12345678901", "��ͯ����˿�ְ�", STATE_TRANSPORT);
	package* pack5 = _CreatOnePackage("5555555555", "98765432101", "JustFumoFumo", STATE_REJECT);
	package* pack6 = _CreatOnePackage("6666666666", "98765432101", "39Music", STATE_ERROR);
	package* pack7 = _CreatOnePackage("7777777777", "98765432101", "�ƽ�����", STATE_ERROR);
	package* pack8 = _CreatOnePackage("8888888888", "98765432101", "��ˮʱɰ", STATE_ERROR);
	package* pack9 = _CreatOnePackage("9999999999", "98765432101", "��������", STATE_ERROR);
	package* pack10 = _CreatOnePackage("1234567890", "98765432101", "��Ƭ", STATE_ERROR);
	package* pack11 = _CreatOnePackage("0987654321", "98765432101", "��ˮ�Ϳ�ʹ", STATE_ERROR);
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

	//�����û�
	user* user1 = _CreatOneUser("V.Reason", "111", "12345678901", 1);
	user* user2 = _CreatOneUser("Vxiaoshan", "222", "9876543210", 2);
	user* user3 = _CreatOneUser("������", "333", "12312332111", 3);
	AddUser(uhead, user1);
	AddUser(uhead, user2);
	AddUser(uhead, user3);

	//���ù���Ա
	user* admin = _CreatOneUser("Admin", "141", "12345678901", ADMIN);
	AddUser(ahead, admin);

	message* mess1 = CreatOneMessage("5����֪ͨ1", 5);
	message* mess2 = CreatOneMessage("5����֪ͨ2", 5);
	message* mess3 = CreatOneMessage("5����֪ͨ3", 5);
	message* mess4 = CreatOneMessage("4����֪ͨ4", 4);
	message* mess5 = CreatOneMessage("4����֪ͨ5", 4);
	message* mess6 = CreatOneMessage("4����֪ͨ6", 4);
	message* mess7 = CreatOneMessage("3����֪ͨ7", 3);
	message* mess8 = CreatOneMessage("3����֪ͨ8", 3);
	message* mess9 = CreatOneMessage("3����֪ͨ9", 3);
	message* mess10 = CreatOneMessage("2����֪ͨ10", 2);
	message* mess11 = CreatOneMessage("1����֪ͨ11", 1);

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

