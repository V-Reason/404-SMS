#include "Front.h"

//������
int powerTag;
int cyrTag;
int hisCyrTag;

//����������ڸ�head
package* phead;		//���������ڸ�
user* uhead;		//�û������ڸ�
user* ahead;		//����Ա�����ڸ�
coupon* chead;		//�Ż�ȯ�����ڸ�

//���ܶ���
shelf shelfs[SHELF_NUM][SUB_SHELF_NUM][ROW][LINE];

//���������˵��ű���
unsigned int totalId = 0;

//�Ʊ�
double fund = 0.0;

//�����ϴε�½��ʱ��
struct tm logoutTime;
char logoutName[MAX_USER_NAME + 1];
char logoutPassword[MAX_PASSWORD_NUM + 1];

//�ӽ���
PublicKey pubKey;
PrivateKey privKey;

////���ն���->������Pay.c��
//const festival fes[] =
//{
//	{"Ԫ��",1,1,0.5},
//	{"�����",10,1,0.5},
//	{"ʥ����",12,25,0.8},
//	{"˫ʮһ",11,11,0.9},
//	{"˫ʮ��",12,12,0.9},
//	{"�Ͷ���",5,1,0.5},
//	{"��Ů��",3,8,0.9},
//	{"���˽�",2,14,0.9}
//};