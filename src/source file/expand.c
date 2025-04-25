#include "Backend.h"

//��ȫ��ָ��Ⱥ��㲥��Ϣ,���û�����uhead,�����Ա����ahead
void Broadcast(message* mess, user* head)
{
	//�����ڸ�
	if (head->prior == NULL)
		head = head->next;
	while (head != NULL)//�㲥��Ϣ
	{
		message* theMess = CpyMessage(mess);
		AddMessage(head->mlist, theMess);
		head = head->next;
	}
}

//ȫ���� ���������� ���㲥��Ϣ
void CheckAll(package* phead, user* ahead)
{
	CheckShelfs(ahead);
	CheckPackage(phead, ahead);
}

//������ ���㲥��Ϣ
void CheckShelfs(user* ahead)
{
	for (int i = 0; i <= SHELF_NUM; i++)
	{
		if (WARNING_LINE >= CountEmptyShelf(i))
		{
			message* mess = CreatOneMessage("", IMP_SHELF);
			sprintf(mess->content, "����%c �Ŀջ����������������ߣ�", i + 'A');
			Broadcast(mess, ahead);
		}
	}
}

//������ ���㲥��Ϣ
void CheckPackage(package* phead, user* ahead)
{
	//�����ڸ�
	if (phead->prior == NULL)
		phead = phead->next;
	//����
	while (phead != NULL)
	{
		//״̬���
		//�쳣
		if (phead->state == STATE_ERROR)
		{
			//�㲥
			message* mess = CreatOneMessage("", IMP_PACKERRO);
			sprintf(mess, "�˵���%s �İ���״̬Ϊ�쳣��", phead->id);
			Broadcast(mess, ahead);
		}
		//����
		if (phead->state == STATE_REJECT)
		{
			//�㲥
			message* mess = CreatOneMessage("", IMP_REJECT);
			sprintf(mess, "�˵���%s �İ������û����գ�", phead->id);
			Broadcast(mess, ahead);
		}
		//�����������ʱ��
		if (GetPackageStayTime(phead) >= WARNING_DAY)
		{
			//����״̬
			phead->state = STATE_STAY_LONG;
			//�㲥
			message* mess = CreatOneMessage("", IMP_STAYLONG);
			sprintf(mess, "�˵���%s ������ʱ�������", phead->id);
			Broadcast(mess, ahead);
		}
		phead = phead->next;
	}
}

//Tip:����ת�����ַ�����ʹ��sprintf()
//    �ַ���ת����С����atof()
//�ж��ַ����Ƿ�ȫ������ �ڲ�����isdigit()
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


//ʹ��˵����
// ���������룬���뼴д��
// δ���������ַ�����
//str:�Ὣ������ַ�д��str
//maxLen:�����������λ��
//esc:
//	OFFʱ��ʶ��ESC  
//	ONʱʶ��ESC����������������ֹ���룬��str����  
//mode:
//	SHOW	 ��ʱ���ԣ�������
//	HIDE	 ������
//	PASSWORD ��ʱ���ԣ���'*'����
//	KEY		 ������������ʶ�𵥴ʼ��룬�������أ������maxLen=1����ʹ��
//	NUM		 �����������֣�֧��С��
void InputBox(char* str, int maxLen, int mode, int esc)
{
	memset(str, 0, maxLen);
	int cnt = 0; //��¼str����
	char tem = 0;
	//��ȡ
	while (TRUE)
	{
		Sleep(50);//�ӳ���Ӧ����ֹ���л���,��Ҫ������
		//�����ж�
		if (_kbhit() || tem < 0)//��||tem<0�������ĵĵڶ��ֽ� KEYģʽ�¶�ȡ���ĵĵ�һ�ֽ�
		{
			tem = _getch();

			//ģʽ�ж�
			switch (mode)
			{
			case MODE_SHOW:
				//Ϊ���������� û����_getche()
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
				//��������֮����
				CursorShow();
				break;
			}//end switch

			//�����ж�����˳���������
			//if (tem == ESC && esc == ON)//esc���������˳�
			if (tem == ESC)//esc���������˳�
			{
				memset(str, 0, maxLen);
				str[0] = ESC;
				CursorHide();
				return;
			}
			if (mode == MODE_KEY)//KEY�������1ʹ��  KEYģʽ�¶�ȡ���ĵĵڶ��ֽ�
			{
				while (_kbhit())_getch();//��ջ����� ��ֹ����
				str[0] = tem;
				CursorHide();
				return;
			}
			if (tem == '\r' || tem == '\n')//��ֹ����
			{
				str[cnt] = '\0';//����ʹ��'\n',�����ļ�IO��������
				while (_kbhit())_getch();//��ջ�����
				printf("\n");
				CursorHide();
				return;
			}
			if (tem == '\b')//ʵ��ɾ��
			{
				if (cnt > 0)
				{
					printf("\b \b");
					cnt--;
					str[cnt] = '\0';
				}
				continue;
			}
			//�����������
			if (mode == MODE_NUM)
			{
				if (cnt >= maxLen)continue;

				if ('0' <= tem && tem <= '9')
				{
					printf("%c", tem);//��ӡ����
				}
				else if (tem == '.' && cnt != 0)
				{
					printf("%c", tem);//��ӡС����
				}
				else if ((tem == '+' || tem == '-') && cnt == 0)
				{
					printf("%c", tem);//��ӡ������
				}
				else
				{
					continue;//�����롢���������д��
				}
			}
			if (cnt >= maxLen)
			{
				continue;
			}
			//��ʽ��ֵ-δ���������ַ�����
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

//��TRUE/FALSEת���� ��/��
void TFtoStr(char* buffer, int tf)
{
	if (tf != 0)
	{
		sprintf(buffer, "��");
	}
	else
	{
		sprintf(buffer, "��");
	}
}

//�����ʾ
void CursorShow()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = TRUE;
	cursor.dwSize = sizeof(cursor);
	//ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(ConsoleHandle, &cursor);
}

//�������
void CursorHide()
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	//ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(ConsoleHandle, &cursor);
}