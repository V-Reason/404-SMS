#include "Frontend.h"

//消息操作系统
void MessSys(user* user)
{
	//预备工作
	system("cls");

	//初始化
	char key = ERROR;					//键入
	int i = ERROR;						//辅助变量 无实意
	message* point = user->mlist->next;	//游标
	message* tmp = NULL;				//试探游标

	while (TRUE)
	{

		//不用初始化key
		//不要在这里写cls
		SetCursorPosition(0, 0);
		tmp = NULL;
		i = ERROR;

		//检测今日无事
		if (user->mlist->next == NULL)
		{
			system("cls");
			printf("今日无事...\n");
			printf("正在返回...\n");
			system("pause");
			return;
		}

		//主界面
		//时间
		printf("当前时间：");
		PrintNowTime();
		printf("\n");
		//操作说明
		printf("<通知操作系统>\n");
		printf("按下[ESC]返回\n");
		printf("按下[a/d]换页\n");
		printf("按下[1 2 3 4 5]选择\n\n");

		//打印
		printf("\n通知:\n");
		PrintNumMessage(point,MESS_NUM);

		//即时键入识别
		if (_kbhit())//防止时间停滞
		{
			InputBox(&key, 1, MODE_KEY, ON);
		}

		//消息循环
		switch (key)
		{
		//无响应
		case ERROR:
		{
			break;//break switch
		}
		//退出系统
		case ESC:
		{
			system("cls");
			printf("退出通知管理操作？\n [y/n]\n");
			InputBox(&key, 1, MODE_KEY, ON);

			if (key == 'y')
			{
				return;
			}
			else
			{
				key = ERROR;
				system("cls");
				break;//break switch
			}

			break;//break switch
		}
		//左一页
		case BUTTON_LEFT:
		{
			tmp = point;
			for (i = 0; i < MESS_NUM && tmp->prior != NULL; i++)//防止走到头
			{
				tmp = tmp->prior;
			}
			if (i == MESS_NUM)//保证走满PAGE_NUM次数
			{
				point = tmp;
			}

			//重置
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//右一页
		case BUTTON_RIGHT:
		{
			tmp = point;
			for (i = 0; i < MESS_NUM && tmp->next != NULL; i++)//防止走到头
			{
				tmp = tmp->next;
			}
			if (i == MESS_NUM)//保证走满page_num次数
			{
				point = tmp;
			}

			//重置
			key = ERROR;
			system("cls");

			break; //break switch
		}
		//选择
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		{
			tmp = point;
			for (i = 0; i < key - '1' && tmp != NULL; i++)
			{
				tmp = tmp->next;
			}
			//进入界面
			if (tmp != NULL)
			{
				if (TRUE == ModifyMessage(tmp))
				{
					point = user->mlist->next;
				}
			}
			//重置
			key = ERROR;
			system("cls");

			break;//break switch
		}

		}//end switch
	}//end while
}

//目前只作为前端删除/办结通知的函数  若删除成功则返回TRUE 否则返回FALSE
int ModifyMessage(message* mess)
{
	//准备工作
	char key = ERROR;
	system("cls");

	//确认删除
	printf("通知内容：%s\n", mess->content);
	printf("是否删除/办结？\n");
	printf("[y/n]\n");
	InputBox(&key, 1, MODE_KEY, OFF);
	if (key != 'y')
	{
		return FALSE;
	}
	//用户申述反馈 通知格式“用户[V.Reason]投诉:..."
	if (mess->important == IMP_USER)
	{
		char* l, * r;
		l = strchr(mess->content, '[');
		r = strchr(mess->content, ']');
		char userName[MAX_USER_NAME + 1];
		memset(userName, 0, sizeof(userName));
		strncpy(userName, l + 1, abs(l - r) - 1);
		char* content = strchr(mess->content, ':');
		content++;
		user* theUser = FindUser(uhead, userName);
		if (theUser != NULL)
		{
			message* newMess = CreatOneMessage("", IMP_SPECIAL);
			sprintf(newMess->content, "投诉处理完成(%s)", content);
			AddMessage(theUser->mlist, newMess);
		}
	}
	//正式删除
	DeleteOneMessage(mess);
	printf("删除/办结成功！\n");
	printf("正在返回...\n");
	system("pause");
	return TRUE;
}