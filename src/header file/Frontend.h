#pragma once
#ifndef Frontend
#define Frontend
#include "Backend.h"

//ǰ�˲���-��ǰ����
user* LoginRegisterInterface();//ע���˺� ֻ�����û�ע�� ����ע����û�
char LoginOrRegister();//��½/ע��ѡ���� ����LOGIN/REGISTER ʧ���˳�ϵͳ
int UserOrAdmin();//�û�/����Աѡ���� ����level ʧ�ܷ���ERROR
user* Login(const char* inf, user* head);//�����˺����� �������head��Ϊ����uhead��ahead ���ص�½���û�
user* Register(user* head);//ע���˺� ֻ�����û�ע�� ����ע����û�
void TopAdminSys(user* admin);//���붥������Աϵͳ �������
void AdminSys(user* admin);//�������Ա����ϵͳ �������
void UserSys(user* user);//�����û�����ϵͳ �������
void MessSys(user* user);//��Ϣ����ϵͳ
int EnterPackage(package* pack);//�ֶ�¼����� �ɹ�����TRUE ʧ�ܷ���FALSE
int SendPackage(user* user, package* pack);//�û��ʼİ���
void CheckCoupon(user* user);//�û�ʹ���Ż�ȯ����
void RejectPackageInterface(package* head);//���հ�������
void EditPackage(package* head);//����Ա�༭��ѯ���İ���
void EditAdmin(user* head);//����Ա�༭��ѯ�����û�
void ModifyPackageInterface(package* pack);//ѡ�����޸İ���-����
int ModifyPackage(package* pack, const char _key, const char* information, const int inputMode, const int MaxLen);//ѡ�����޸İ���-��㺯��
int ModifyUserInterface(user* user);//ѡ�����޸��û�-����
void ModifyAdminInterface(user* admin);//ѡ�����޸Ĺ���Ա-����
int ModifyUser(user* user, const char _key, const char* information, const int inputMode, const int MaxLen);//ѡ�����޸��û�-��㺯��
void ModifyState(package* pack);//�޸İ���״̬
void ModifyDefaulatAddress(user* user);//�޸�Ĭ�ϵ�ַ
int ModifyMessage(message* mess);//Ŀǰֻ��Ϊǰ��ɾ��֪ͨ�ĺ���  ��ɾ���ɹ��򷵻�TRUE ���򷵻�FALSE
int JungePackageInformation(const char key, const char* information);//�ж�����İ�����Ϣ�Ƿ���Ϲ涨
int JungeUserInformation(const char key, const char* input);//�жϸ�����Ϣ����
void SaveOption();//����ѡ��
void UserRegular(user* user);//�û���ʱ��ɺ�Ĳ�������
void AdminRegular_S(user* user);//����Ա�̶�ʱ��ɺ�Ĳ�������
void AdminRegular_L(user* user);//����Ա����ʱ��ɺ�Ĳ�������
void GoThroughPackage();//��������״̬

//��ֵ-��ǰ����
//�ȼ����㹫ʽ
float CalculateBill(user* user, package* pack);//�����˷�
void PrintBillSchedule();//��ӡ�շѱ�׼
void PrintInputRule();//��ӡ��д����
festival* isFestival();//�жϽ����Ƿ��ǽ���,���򷵻ؽ��գ����򷵻�NULL
void GainExp(const int event, user* user);//��þ���ֵ

//�ڹ�
void ManagePay();//�ڹ�����
void GainExp(const int event, user* user);//��þ���ֵ
void UserPay(user* user);//�û��ڹ�
void BuyExp(user* user);//����exp
void BuyCoupon(user* user);//�����Ż�ȯ
void PrintExpRule();//��ӡ�ȼ�����

//�Ż�ȯ
void IssueCoupon(coupon* cpyCoupon);//�����Ż�ȯ
void EditCoupon();//�����Ż�ȯ

#endif