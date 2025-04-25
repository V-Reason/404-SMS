#pragma once
#ifndef Backend
#define Backend
#include "Front.h"

//�ļ���ȡ-��ǰ����
//���º�����ִ��ʧ���������FALSE
void Replace_nto0(char* str);//���ַ������\nת����\0
int ReadAll();//��ȡȫ���ļ�
int SaveAll();//����ȫ���ļ�
void CyrAll();//���������ļ�
void DecyrAll();//���������ļ�
void CyrHis();//����������ʷ��¼�ļ�
void DecyrHis();//����������ʷ��¼�ļ�
void InitFile();//��ʼ��txt�ļ�
int ReadLogoutTime();//��ȡLoginTime
int SaveLogoutTime();//����LoginTime
void ClearLogout();//���Logout��¼
void RecordLogoutTime();//��¼�˳�ʱ��
void RecordLogoutUser(user* user);//��¼�˺�

int ReadInit();
int SaveInit();
int ReadHisInit();
int SaveHisInit();
int ReadFund();//��ȡFund
int SaveFund();//����Fund
int ReadCoupon();//��ȡCoupon
int SaveCoupon();//����Coupon
int ReadTotalId();//��ȡTotalId
int SaveTotalId();//����TotalId
int ReadPackage();//��ȡ����
int SavePackage();//�������
int ReadUser(const char* txt, user* head);//��ȡ�û� ���������������uhead��ahead
int SaveUser(const char* txt, user* head);//�����û�
void WritePackHis(package* pack);//������ʷ��¼-д��;
void ReadPackHis(const struct tm* START, const struct tm* END);//������ʷ��¼-��ȡ
void InitSys();//��ʼ������
void ExitSys();//���˳����� ������������ �������������

//��������-��ǰ����
//int JudgePackage(package* pack);//�жϵ������������Ƿ�Ϸ�
void TFtoStr(char* buffer, int tf);//��TRUE/FALSEת���� ��/��
void StateToStr(char* buffer, packageState state);//��stateת�����ַ���
void PrintAllPackage(package* head);//ֻ���ɶ�������Ա���� ��ӡhead֮������а������Զ��ж��Ƿ�Ϊhead,������ӡhead
void PrintNumPackage(package* head, int num);//��ӡָ�������İ������Զ��ж��Ƿ�Ϊhead,������ӡhead
void PrintOnePackage(package* pack);//��ӡ����pack����
int CountPackage(package* head);//����head����֮�����Ч�����������Զ��ж��Ƿ�Ϊhead,��������head
void AssignId(package* pack);//����head����֮�����Ч�����������Զ��ж��Ƿ�Ϊhead,��������head
package* CreatPackageList();//������������
package* CreatOnePackage();//����һ��package,���ش�����package��ָ��,����ֵΪ-1��DEFAULTʱ��ʾ���޸�
package* _CreatOnePackage(char* id, char* tele_num, char* pack_name, packageState state);
//void ModifyPackage(package* pack);//�ú����Ѿ�ת����ǰ�� //�޸�pack����ֵ //������prior��nextָ��,����ֵΪ-1��DEFAULTʱ��ʾ���޸�
void AddOnePackage(package* head, package* pack);//������ĩβ���һ��package
void AddMultiplePackage(package* head, package* packs);//������ĩβ��Ӷ��package �Զ��ж�head�Ƿ���ڣ������Ժ��ͷ�head
void InsertOnePackage(package* head, package* pack);//��head��߲���һ��package �Զ����head������
void InsertMultiplePackage(package* head, package* packs);//��head���������package �Զ����head�������Ժ��ͷ�head
void TakeOutOnePackage(package* nhead, package* pack);//��headȡ����������pack��������һ������nheadβ��
void DeleteOnePackage(package* pack);//�ͷŵ���pack ������İ����Ļ���״̬��FALSE ���������ͷ�head �Զ����head������
void DeleteAllPackage(package* head);//�ͷ�head��֮�������pack
package* AdminFindPackage(package* head, char* str);//����Ա���Ҷ�������������ҵ��İ�������������õ�headĩβ�����ص�һ���ҵ��İ����ĵ�ַ
package* UserFindPackage(package* head, user* _user);//�û������Լ��İ���
void PackageCheck(package* head, message* messhead);//����ȫ����
void PackageSort(package* head);//��������-����״̬,���봫���ڱ�

//�û�����-��ǰ����
void PrintOneUser(user* head);//��ӡ�����û���Ϣ
void PrintAllUser(user* head);//��ӡ�����û���Ϣ
void PrintOneAdmin(user* head);//��ӡָ���������û�,�Զ��ж�head
void PrintNumAdmin(user* head, int num);//��ӡָ���������û�,�Զ��ж�head
int CountUser(user* head);//�����û�����
//int JudgeUser(user* puser);//�ú����Ѿ����� �ж��û������Ƿ�Ϸ�  ûд��
user* CreatUserList();//�����û�����
user* CreatOneUser();//�����û����� ����DEFAULT��ʾĬ��ֵ0
user* _CreatOneUser(char* name, char* password, char* tele_num, int level);//������ʹ�ú���  �����û����� ����DEFAULT��ʾĬ��ֵ0
void AddUser(user* head, user* _user);//���û���Ϣ���������ĩβ
void DeleteOneUser(user* _user);//ɾ�������û���Ϣ
void DeleteAllUser(user* head); //ɾ������head���ڵ������û���Ϣ
user* FindUser(user* head, char* str);//�������ֺ͵绰 �����û���Ϣ �����ҵ����û�ָ�� ���򷵻�NULL
int isRepeatName(const char* name);//�����Ƿ��ظ�
int isRepeatTele(const char* teleNum);//�ֻ��Ų��ظ�

//���ܲ���-��ǰ����
void InitShelf();//��ʼ������ �����ڶ�ȡ�����ļ���ִ��
int PutShelf(package* pack, int num);//�������������
int GetShelf(package* pack);//�ӻ���ȡ������
int CountUsedShelf(int n);//����ʹ�û������� ������ܺ� ABCD �ڲ�������CountEmptyShelf
int CountEmptyShelf(int n);//����ջ������� ������ܺ� ABCD
void PrintAllShelf();//��ӡ����״̬ Ŀǰ��ӡ�ջ�������
//int JudgeLocation(package* pack);//�����ϣ�Ϊ����������λ�� ���ش�ű�� ��û��λ���򷵻�ERROR
int AllocateLocation(package* pack, user* ahead);//Ϊ���������ܡ�����λ�ã��ڲ����ö����������û��λ�򷵻�FALSE,����ͬʱ�Զ�����Ƿ�ﵽ�����ߣ���������ȫ�����Ա��֪ͨ
void SetPickupCode(package* pack);//����ȡ����  0000~9999
shelf* StrToShelf(const char* str);//���ַ���ת��Ϊshelf
void ModifyShelf(shelf* theShelf);//�޸Ļ���״̬

//֪ͨ����-��ǰ����
message* CreatMessageList();//����ͷ���
message* CreatOneMessage(char* content, int important);//��������message ����DEFAULT ���趨ΪĬ��ֵ
void MessageSort(message* head);//֪ͨ�����㷨��ð�����򣩴���ֵ�������ڱ�
void PrintOneMessage(message* mess);//��ӡ����֪ͨ
void PrintNumMessage(message* head, int num);//��ӡָ������֪ͨ
void PrintAllMessage(message* head);//��ӡ����֪ͨ
void AddMessage(message* head, message* mes);//���Message�ڵ� ��������������
void DeleteOneMessage(message* mess);//ɾ������֪ͨ
void DeleteAllMessage(message* head);//ɾ��head���ڵ�����֪ͨ
int CountMessage(message* mhead);//����֪ͨ����
message* CpyMessage(message* mess);//����֪ͨ ������mess

//�Żݾ�
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

//ʱ�����-��ǰ����
struct tm* GetNowTime();//��ȡ��ǰʱ��
void PrintNowTime();//�� 0000.00.00  00:00:00 ��24Сʱ�ĸ�ʽ��ӡ��ǰʱ��
int IsLeapYear(int year);//�����ж�
int DaysInMonth(int year, int mon);//���ָ���·ݵ�����
int GetDaysFromStartOfYear(int year, int month, int day);//����ĳ��ĳ������ڱ����һ�������
int GetPackageStayTime(package* pack);//��ȡ������������
void SetPackageInTime(package* pack, int year, int mon, int day);//�������ʱ��
void SetPackageOutTime(package* pack, int year, int mon, int day);//���ó���ʱ��
int GetTimeSeg(struct tm* time1, struct tm* time2);//����ʱ��� time1<time2 ��������		time1>time2 ���ظ���
int GetTimeSeg_Min(struct tm* time1, struct tm* time2);
struct tm TimeAdd(const struct tm* timeBefore, const int mon);//ʱ��ӷ�����λ���£�

//���ܽ���-��ǰ����
ll gcd(ll a, ll b);//���㲢�������Լ��
ll mod_exp(ll base, ll exp, ll mod);//���㲢���� a^b mod m
ll mod_inverse(ll a, ll b);//����ģ��Ԫ��
void generate_keys(ll p, ll q, PublicKey* pubKey, PrivateKey* priKet);//���� RSA ��Կ��
ll encrypt(ll message, PublicKey pubKey);//���� ��������
ll decrypt(ll message, PrivateKey privKey);//���� ��������
void CyrptFile(const char* oriTxt);//�������ļ�����,ֱ�ӵ��þ���
void DecyrptFile(const char* oriTxt);//�������ļ�����,ֱ�ӵ��þ���
void InitKey();//��ʼ��˽Կ�͹�Կ ���ǵõ���


//�����չ->��ǰ����
int isAllDigits(const char* str);//�ж��ַ����Ƿ�ȫ������ �ڲ�����isdigit()
void InputBox(char* str, int maxLen, int mode, int esc);//���������룬���뼴д�룬���Զ���������������ַ���maxLen,���ݱ���Ϊstr  �������������룬����������Ϊ SHOW��Ϊ�����룬HIDE��Ϊ����,PASSWORD��Ϊ��*����
void SetCursorPosition(int x, int y);//���ù��λ��
void InitConsole();//��ʼ������̨����
void CursorShow();//�����ʾ
void CursorHide();//�������
void CheckAll(package* phead, user* adminHead);//ȫ���� ���������� ���㲥��Ϣ
void CheckShelfs(user* adminHead);//������ ���㲥��Ϣ
void CheckPackage(package* phead, user* adminHead);//������ ���㲥��Ϣ
void Broadcast(message* mess, user* head);//��ȫ��ָ��Ⱥ��㲥��Ϣ,���û�����uhead,�����Ա����ahead
void TimeToStr(char* buffer, struct tm* time);//��ʱ�����ݱ���ַ���2006��01��05��

#endif