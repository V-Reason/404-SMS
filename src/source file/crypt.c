#include "Backend.h"

// �������Լ��
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// ���� a^b mod m
ll mod_exp(ll base, ll exp, ll mod) {
    ll result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// ����ģ��Ԫ��
ll mod_inverse(ll a, ll m) {
    a = a % m;
    for (ll x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // ���û��ģ��Ԫ��
}

// ���� RSA ��Կ��
void generate_keys(ll p, ll q, PublicKey* pubKey, PrivateKey* privKey) {
    ll n = p * q;
    ll phi = (p - 1) * (q - 1);

    // ѡ�� e
    ll e = 3;
    while (gcd(e, phi) != 1) {
        e += 2; // ѡ��һ������
    }

    // ���� d
    ll d = mod_inverse(e, phi);

    pubKey->e = e;
    pubKey->n = n;
    privKey->d = d;
    privKey->n = n;
}

// ����
ll encrypt(ll message, PublicKey pubKey) {
    return   mod_exp(message, pubKey.e, pubKey.n);
}

// ����
ll decrypt(ll message, PrivateKey privKey) {
    return   mod_exp(message, privKey.d, privKey.n);
}

//�������ļ�����,ֱ�ӵ��þ���
void CyrptFile(const char* oriTxt) {

    //�༭�ļ���
    char cryTxt[256];
    memset(cryTxt, 0, sizeof(cryTxt));
    char* tmp = strrchr(oriTxt, '/');
    strncpy(cryTxt, oriTxt, abs(oriTxt - tmp));
    strncat(cryTxt, _CRY, sizeof(_CRY));
    strcat(cryTxt, tmp + 1);

    FILE* oriFile = fopen(oriTxt, "r");
    FILE* cryFile = fopen(cryTxt, "w");

    if (oriFile == NULL) {
        //perror("oriFile not found");
        return;
    }
    if (cryFile == NULL) {
        //perror("cryFile not found");
        return;
    }

    char c;	//������ַ�
    long long cyr;

    while ((c = fgetc(oriFile)) != EOF) {
        if (feof(oriFile)) {
            break;
        }
        else {				//���������ַ�����ܺ���ַ�
            long long tmp = c;
            cyr = encrypt(tmp, pubKey);
            fprintf(cryFile, "%lld", cyr); //д���ļ�
            fputc(' ', cryFile); //д��ո�

        }
    }
    fclose(oriFile);
    fclose(cryFile);

    oriFile = fopen(oriTxt, "w");//����ը��ָ�Ӳ�
    fclose(oriFile);
}

//�������ļ�����,ֱ�ӵ��þ���
void DecyrptFile(const char* oriTxt) {
    //�༭�ļ���
    char cryTxt[256];
    memset(cryTxt, 0, sizeof(cryTxt));
    char* tmp = strrchr(oriTxt, '/');
    strncpy(cryTxt, oriTxt, abs(oriTxt - tmp));
    strncat(cryTxt, _CRY, sizeof(_CRY));
    strcat(cryTxt, tmp + 1);

    FILE* oriFile = fopen(oriTxt, "w");
    FILE* cryFile = fopen(cryTxt, "r");

    if (oriFile == NULL) {
        //perror("oriFile not found");
        return;
    }
    if (cryFile == NULL) {
        //perror("cryFile not found");
        return;
    }

    char c;     //���ڽ���longlong��ķ��ţ����ţ��ո���з���
    long long cyr;

    while (TRUE) {
        fscanf(cryFile, "%lld", &cyr);	//��ȡһ��long long������һ������
        if (feof(cryFile)) {
            break;
        }
        else {
            long long tmp = decrypt(cyr, privKey);
            c = (char)tmp;
            fputc(c, oriFile);
        }
    }

    fclose(oriFile);
    fclose(cryFile);

    cryFile = fopen(cryTxt, "w");//����ը��ָ�Ӳ�
    fclose(cryFile);
}

//��ʼ��˽Կ�͹�Կ
void InitKey() {

    long long p = 61; // ���� p
    long long q = 53; // ���� q
    generate_keys(p, q, &pubKey, &privKey);
}