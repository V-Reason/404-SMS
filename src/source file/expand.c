#include "Backend.h"

//向全体指定群体广播消息,向用户则传入uhead,向管理员则传入ahead
void Broadcast(message* mess, user* head)
{
	//跳过哨岗
	if (head->prior == NULL)
		head = head->next;
	while (head != NULL)//广播消息
	{
		message* theMess = CpyMessage(mess);
		AddMessage(head->mlist, theMess);
		head = head->next;
	}
}

//全面检查 包裹、货架 并广播消息
void CheckAll(package* phead, user* ahead)
{
	CheckShelfs(ahead);
	CheckPackage(phead, ahead);
}

//检查货架 并广播消息
void CheckShelfs(user* ahead)
{
	for (int i = 0; i <= SHELF_NUM; i++)
	{
		if (WARNING_LINE >= CountEmptyShelf(i))
		{
			message* mess = CreatOneMessage("", IMP_SHELF);
			sprintf(mess->content, "货架%c 的空货架数量超过警戒线！", i + 'A');
			Broadcast(mess, ahead);
		}
	}
}

//检查包裹 并广播消息
void CheckPackage(package* phead, user* ahead)
{
	//跳过哨岗
	if (phead->prior == NULL)
		phead = phead->next;
	//遍历
	while (phead != NULL)
	{
		//状态检查
		//异常
		if (phead->state == STATE_ERROR)
		{
			//广播
			message* mess = CreatOneMessage("", IMP_PACKERRO);
			sprintf(mess, "运单号%s 的包裹状态为异常！", phead->id);
			Broadcast(mess, ahead);
		}
		//拒收
		if (phead->state == STATE_REJECT)
		{
			//广播
			message* mess = CreatOneMessage("", IMP_REJECT);
			sprintf(mess, "运单号%s 的包裹被用户拒收！", phead->id);
			Broadcast(mess, ahead);
		}
		//计算包裹滞留时间
		if (GetPackageStayTime(phead) >= WARNING_DAY)
		{
			//设置状态
			phead->state = STATE_STAY_LONG;
			//广播
			message* mess = CreatOneMessage("", IMP_STAYLONG);
			sprintf(mess, "运单号%s 的滞留时间过长！", phead->id);
			Broadcast(mess, ahead);
		}
		phead = phead->next;
	}
}

//Tip:数字转化成字符串请使用sprintf()
//    字符串转换成小数用atof()
//判断字符串是否全是数字 内部调用isdigit()
int isAllDigits(const char* str)
{
	while (*str)
	{
		if (!isdigit(*str))
		{
			return FALSE;
		}
		str++;
	}
	return TRUE;
}


//使用说明：
// 无阻塞输入，键入即写入
// 未限制特殊字符输入
//str:会将输入的字符写入str
//maxLen:限制最大输入位数
//esc:
//	OFF时不识别ESC  
//	ON时识别ESC按键，并且立刻终止输入，将str置零  
//mode:
//	SHOW	 即时回显，非掩码
//	HIDE	 不回显
//	PASSWORD 即时回显，用'*'掩码
//	KEY		 非阻塞，用于识别单词键入，立即返回，必须和maxLen=1搭配使用
//	NUM		 用于输入数字，支持小数
void InputBox(char* str, int maxLen, int mode, int esc)
{
	memset(str, 0, maxLen);
	int cnt = 0; //记录str长度
	char tem = 0;
	//读取
	while (TRUE)
	{
		Sleep(50);//延迟响应，防止队列混乱,必要！！！
		//输入判断
		if (_kbhit() || tem < 0)//用||tem<0勘测中文的第二字节 KEY模式下读取中文的第一字节
		{
			tem = _getch();

			//模式判断
			switch (mode)
			{
			case MODE_SHOW:
				//为了适配中文 没法用_getche()
				CursorShow();
				if (cnt >= maxLen)break;
				if (tem != '\b' )
					printf("%c", tem);
				break;
			case MODE_HIDE:
			case MODE_KEY:
				break;

			case MODE_PASSWORD:
				CursorShow();
				if (cnt >= maxLen)break;
				if (tem != '\b'
					&& tem != '\r'
					&& tem != '\n')
					printf("%c", '*');
				break;

			case MODE_NUM:
				if (cnt >= maxLen)break;
				//输入限制之后处理
				CursorShow();
				break;
			}//end switch

			//以下判断上下顺序不能随意调
			//if (tem == ESC && esc == ON)//esc按键清零退出
			if (tem == ESC)//esc按键清零退出
			{
				memset(str, 0, maxLen);
				str[0] = ESC;
				CursorHide();
				return;
			}
			if (mode == MODE_KEY)//KEY必须配合1使用  KEY模式下读取中文的第二字节
			{
				while (_kbhit())_getch();//清空缓冲区 防止中文
				str[0] = tem;
				CursorHide();
				return;
			}
			if (tem == '\r' || tem == '\n')//终止输入
			{
				str[cnt] = '\0';//不能使用'\n',否则文件IO会有问题
				while (_kbhit())_getch();//清空缓冲区
				printf("\n");
				CursorHide();
				return;
			}
			if (tem == '\b')//实现删除
			{
				if (cnt > 0)
				{
					printf("\b \b");
					cnt--;
					str[cnt] = '\0';
				}
				continue;
			}
			//数字输入规则
			if (mode == MODE_NUM)
			{
				if (cnt >= maxLen)continue;

				if ('0' <= tem && tem <= '9')
				{
					printf("%c", tem);//打印数字
				}
				else if (tem == '.' && cnt != 0)
				{
					printf("%c", tem);//打印小数点
				}
				else if ((tem == '+' || tem == '-') && cnt == 0)
				{
					printf("%c", tem);//打印正负号
				}
				else
				{
					continue;//不输入、不输出、不写入
				}
			}
			if (cnt >= maxLen)
			{
				continue;
			}
			//正式赋值-未限制特殊字符输入
			str[cnt] = tem;
			cnt++;
		}//end if
	}//end while
}

void SetCursorPosition(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//将TRUE/FALSE转换成 是/否
void TFtoStr(char* buffer, int tf)
{
	if (tf != 0)
	{
		sprintf(buffer, "是");
	}
	else
	{
		sprintf(buffer, "否");
	}
}

//光标显示
void CursorShow()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = TRUE;
	cursor.dwSize = sizeof(cursor);
	//ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(ConsoleHandle, &cursor);
}

//光标隐藏
void CursorHide()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	//ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(ConsoleHandle, &cursor);
}