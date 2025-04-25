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

//ϵͳ�賿
#define SYS_MIDNIGHT_HOUR	0
#define SYS_MIDNIGHT_MIN	0

//����
#define TITLE L"404��վϵͳ"
#define _TITLE "404��վϵͳ"
#define GBK  936
#define DEFUALT_TOPADMIN_NAME	"TopAdmin"
#define DEFUALT_ADMIN_NAME	    "Admin"
#define DEFUALT_ADMIN_PASSWORD	"12345"

//�ձ��
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

//ʱ��
#define YEAR 0
#define MON  1
#define DAY  2

//������
#define REGISTER	'0'
#define LOGIN		'1'
#define RETRY		'r'
#define _RETRY		"r"

#define ESC			 27
#define BUTTON_LEFT  'a'
#define BUTTON_RIGHT 'd'


//InputBoxģʽ
#define MODE_SHOW		0
#define MODE_HIDE		1
#define MODE_PASSWORD	2
#define MODE_KEY		3
#define MODE_NUM		4

//����������
#define _ID			0
#define _TELE		1
#define _STATE		2
#define _PACK_NAME	3

//��Ϣѭ����
//ModifyPackageInterface��
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


//��ҳ������
#define PAGE_NUM   5
#define ADMIN_NUM  5
#define MESS_NUM   5

//�ַ�����
#define MAX_ID		      10
#define MAX_TELE_NUM      11
#define MAX_PACK_NAME     20
#define MAX_USER_NAME     20	//ע�⣬��Ҫ̫С����ΪĬ�����ƺܳ�
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

//���ܴ�A0��ʼ����
#define ROW  10		//�������� ���ɳ���10
#define LINE 10		//�������� ���ɳ���10
#define SHELF_NUM	  4
#define SUB_SHELF_NUM 4
#define SHELF_A 0
#define SHELF_B 1
#define SHELF_C 2
#define SHELF_D 3
#define WARNING_LINE 10 //���ܿ�λ������
#define WARNING_DAY  5  //��������ʱ�侯����

//�ļ�IO
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

//�շѱ�׼
#define BASS_RATE	1.25
#define VOLUME_RATE	0.005
#define FAR_SUR		3
#define FRAG_SUR	2
#define VALU_SUR	3
#define TODOOR_SUR	2
#define LEVEL_RATE  0.05

//���ܷ����׼
#define MEDIUM	8000	//20^3
#define LARGE	1000000 //100^3

//�˳�ϵͳ�ж���
#define EXIT	0   //�������ó�1
#define RESTART 1   //�������ó�0

#define DECYR	0   //�������ó�1
#define CYR		1   //�������ó�0

//�Զ���½�������λ���죩
#define AutoLogin_TimeSeg		3

//��ʱ�����������λ�����ӣ�
#define AutoRegular__TimeSeg_S	10
#define AutoRegular__TimeSeg_L	30

//��������Ȩ����ֵ
#define SORT_THRESHOLD	5

//�ڹ����
#define MIN_TOPUP	10
#define MAX_COUPON	30
//#define COUPON_NUM	3
#define VALID	0
#define INVALID	1

//Exp����
// ���Exp��4001
// һ����0~500
// ������501~1000
// ������1001~1500
// �ļ���1501~2000
// �弶��2001~2500
// ÿ��ǩ��+10
// �İ���+100
// ��ֵ+1000/10Ԫ
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

//�Զ����������->��ǰ����
typedef unsigned long long ull;
typedef long long ll;

//����״̬
typedef enum packageState
{
	STATE_ERROR	= 0,	//�쳣���������ȵ�
	STATE_STAY_LONG,	//��Ź���
	STATE_WAIT_PICK,	//��ǩ��
	STATE_TRANSPORT,	//������
	STATE_WAIT_COLLECT,	//������
	STATE_REJECT,		//����
	STATE_PICKUPED		//��ǩ��
}packageState;

//֪ͨ��Ҫ��->������Ҫ�Ծ͵�������
typedef enum messageImportant
{
	IMP_NORMAL = 0,		//��ͨ
	IMP_STAYLONG,		//��������
	IMP_REJECT,			//���հ���
	IMP_SHELF,			//���ܲ���
	IMP_PACKERRO,		//�����쳣
	IMP_SPECIAL,		//�ر��  eg:�����ۿ�֪ͨ
	IMP_USER			//�û�����
}messageImportant;

//�û��ȼ�
typedef enum userLevel {
	TOP_ADMIN = -1,
	ADMIN = 0,
	NORMAL_USER = 1,
	POWER_USER,
	SUPER_USER,
	PRO_USER,
	Ultra_USER
}userLevel;

//��������
typedef struct package //һ��
{
	char id[MAX_ID + 1];				  //10λ�˵���
	char tele_num[MAX_TELE_NUM + 1];	  //11�绰����
	char pick_tele_num[MAX_TELE_NUM + 1]; //ȡ����11�绰����
	char pack_name[MAX_PACK_NAME + 1];	  //20λ��������
	char location[MAX_LOCATION + 1];	  //3λ��ŵص� A0_1,2
	char pickupCode[MAX_PICKUP_CODE + 1]; //4λȡ����   2333

	char user_name[MAX_USER_NAME + 1];	//10λ�û������ռ��ˣ�
	char sender_name[MAX_USER_NAME + 1];//10λ�ļ�������
	char user_address[MAX_ADDRESS + 1];	//40λ�ռ��˵�ַ
	char send_address[MAX_ADDRESS + 1];	//40λ�ļ��˵�ַ

	float Bill;			 // �˷�
	float weight;        // ������kg��
	float size;			 // ���
	int isRemoteArea;    // �Ƿ�ƫԶ������1���ǣ�0����
	int isFragile;       // �Ƿ�����Ʒ��1���ǣ�0����
	int isValuable;		 // �Ƿ�Ϊ������Ʒ��0Ϊ�ǹ��أ�1Ϊ����
	int isToDoor;		 // �Ƿ��ͻ�����

	int time[2][3];		 //��������,IN/0Ϊ���ʱ�䣬OUT/1Ϊ����ʱ��,��ʱ��Ϊ������-1��ʾ��һ��Ҫ��ʼ��e��,012�ֱ�Ϊ������
	packageState state;  //����״̬

	//struct user* owner;		//����׷�� �����ڴ�ӡ��ַ ����
	//struct user* sender;	//����׷��
	struct package* prior;
	struct package* next;
}package;

//�û�����
typedef struct user 
{					//�����û��ṹ��
	int level;							//�û��ȼ���0Ϊ����Ա
	int exp;							//����ֵ
	char name[MAX_USER_NAME + 1];		//10λ�����û���	
	char password[MAX_PASSWORD_NUM + 1];//20λ��������
	char tele_num[MAX_TELE_NUM + 1];	//11λ�绰����

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

//֪ͨ
typedef struct message 
{
	char content[MAX_MESSAGE + 1];	//�������������Ϣ,���100λ
	messageImportant important;					//��Ϣ��Ҫ�̶ȣ�Խ����Ҫ�̶�Խ��,0Ϊ��ͨ,1Ϊ����δȡ��2Ϊ���ܽ�����3Ϊ�����쳣
	struct message* prior;
	struct message* next;
} message;

//�Żݾ�
typedef struct coupon
{
	char content[MAX_COUPON + 1];	//��������
	float rate;						//����
	int timeLimit;					//ʱЧ ��λ����
	int cost;						//��������۸�
	struct tm time[2];				//��Ч���ںͽ�ֹ����
	int used;						//����Ƿ�ʹ��

	struct coupon* prior;
	struct coupon* next;
}coupon;

//���ܶ���
typedef struct shelf {
	char location[MAX_LOCATION + 1];//��Ǵ��λ��  eg: A0_1,2
	int used;						//����Ƿ�ʹ��
	char pack_id[MAX_ID + 1];		//�洢�˵���
}shelf;

//����
typedef struct {
	long long e;
	long long n;
} PublicKey;

//˽��
typedef struct {
	long long d;
	long long n;
} PrivateKey;

//����
typedef struct festival
{
	char name[10];	//��������
	int month;		//�����·�
	int day;		//��������
	float discount; //�ۿ�С��ֵ
}festival;

//�Ĵ�������ڸ�head
extern package* phead;	//���������ڸ�
extern user* uhead;		//�û������ڸ�
extern user* ahead;		//����Ա�����ڸ�
extern coupon* chead;	//�Ż�ȯ�����ڸ�

//���ܶ���
extern shelf shelfs[SHELF_NUM][SUB_SHELF_NUM][ROW][LINE];

//���������˵��ű���
extern unsigned int totalId;

//�Ʊ�
extern double fund;

//���ն���
extern const festival fes[];

//�����ϴε�½��ʱ��
extern struct tm logoutTime;
extern char logoutName[MAX_USER_NAME + 1];
extern char logoutPassword[MAX_PASSWORD_NUM + 1];

//�ӽ���
extern PublicKey pubKey;
extern PrivateKey privKey;

//������
extern int powerTag;
extern int cyrTag;
extern int hisCyrTag;

#endif