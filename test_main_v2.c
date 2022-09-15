
#include <stdio.h>
#include <time.h>
#include "relic.h"
#include "relic_test.h"

#include "relic_core.h"
#include "relic_pp.h"
#include "relic_util.h"

#define WITH_PC
#define PP_MAP 3
#undef STRIP
#define EP_ENDOM
#define FP_PRIME 455
#define TEST "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
#define MSG_SIZE 1000001
// #define EP_ADD BASIC

static int Tsm1(void)
{ //测试 G1标量乘法运行时间
    int code = RLC_ERR;
    int k;
    bn_t d;
    bn_t n;
    g1_t h;
    g1_t q;
    g1_t r;

    // test
    g1_r->x

    clock_t start1, stop1, start, stop;
    double duration;

    g1_null(q);
    bn_null(n);
    bn_null(d);
    g1_null(r);
    g1_null(h);
    TRY
    {

        bn_new(d);
        g1_new(q);
        bn_new(n);
        g1_new(r);
        g1_new(h);

        g1_rand(h);

        g1_get_ord(n);
        bn_rand_mod(d, n);
        // printf("%x\n", *d);

        start = clock();
        //for(int i=0; i<1000;i++)
        g1_mul_gen(q, d); // q=g1^d
        stop = clock();
        duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
        printf("Tsm1_g1_mul_gen%lf\n", duration);

        start1 = clock();
        g1_mul(r, h, d); //r=h^d h属于G1
        stop1 = clock();
        duration = ((double)(stop1 - start1)) / CLOCKS_PER_SEC;
        printf("Tsm1_g1_mul:%lf\n", duration);
    }

    CATCH_ANY
    {
        ERROR(end);
    }
    code = RLC_OK;

end:
    bn_free(d);
    g1_free(s);
    g1_free(q);
    return code;
}

static int Tsm2(void)
{ //测试 G2标量乘法运行时间
    int code = RLC_ERR;
    int k;
    bn_t d;
    bn_t n;
    g2_t q, r, h;

    clock_t start, stop, start1, stop1;
    double duration;

    g2_null(q);
    g2_null(r);
    g2_null(h);
    // printf("%x\n", q);

    bn_null(n);
    bn_null(d);

    TRY
    {

        bn_new(d);
        g2_new(q);
        g2_new(r);
        g2_new(h);
        bn_new(n);

        g2_rand(h);
        g2_get_ord(n);
        bn_rand_mod(d, n);

        start = clock();
        g2_mul_gen(q, d); //q=g2^d
        stop = clock();
        // printf("%x\n", q->y);
        duration = ((double)(stop - start)) / CLOCKS_PER_SEC; //计算运行时间
        printf("Tsm2_g2_mul_gen:%lf\n", duration);

        start1 = clock();
        g2_mul(r, h, d); //r=h^d h属于G1
        stop1 = clock();
        duration = ((double)(stop1 - start1)) / CLOCKS_PER_SEC;
        printf("Tsm2_g2_mul:%lf\n", duration);
    }

    CATCH_ANY
    {
        ERROR(end);
    }
    code = RLC_OK;

end:
    bn_free(d);
    g1_free(s);
    g2_free(q);
    return code;
}

static int EPT(void)
{ //测试 GT幂运行时间
    int code = RLC_ERR;
    bn_t d;
    bn_t n;
    gt_t r, h;

    clock_t start, stop;
    double duration;

    bn_null(n);
    bn_null(d);
    gt_null(r);
    gt_null(h);
    TRY
    {

        bn_new(d);
        bn_new(n);
        gt_new(r);
        gt_new(h);

        gt_rand(h);
        g1_get_ord(n);
        bn_rand_mod(d, n);
        // printf("%x\n", *d);

        start = clock();
        gt_exp(r, h, d); // r=e(g1,g2)^d
        stop = clock();
        duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
        printf("EPT:%lf\n", duration);
    }

    CATCH_ANY
    {
        ERROR(end);
    }
    code = RLC_OK;

end:
    bn_free(d);
    g1_free(s);
    return code;
}

// wang version
static int Tpar(void)
{ // 测试 配对运行时间
    int code = RLC_ERR;

    bn_t n;
    g1_t s;
    g2_t a;
    gt_t r;

    clock_t start, stop;
    double duration;

    g1_null(s);
    g2_null(a);
    gt_null(r);
    bn_null(n);
    TRY
    {
        gt_new(r);
        g1_new(s);
        bn_new(n);
        g2_new(a);

        g1_rand(s);
        g2_rand(a);

        start = clock();
        // printf("%d\n",ep_is_infty(s));

        pc_map(r, s, a); //r=e(s,a)

        stop = clock();
        duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
        printf("Tpar:%lf\n", duration);
    }

    CATCH_ANY
    {
        ERROR(end);
    }
    code = RLC_OK;

end:
    g1_free(s);
    bn_free(n);
    g2_free(a);
    gt_free(r);
    return code;
}

static int Tsmt(void)
{ //测试 Gt 乘法运行时间
    gt_t a, b, c;
    bn_t d, e;
    clock_t start, stop; //clock_t是clock()函数返回值的变量类型
    double duration;
    int code = RLC_ERR;

    gt_null(a);
    // printf("%x\n", a);

    gt_null(b);
    gt_null(c);

    gt_new(a);
    gt_new(b);
    gt_new(c);

    gt_rand(a);
    gt_rand(b);
    // printf("%x\n", a);

    start = clock();

    gt_mul(c, a, b); //c=a*b
    //fp12_mul_lazyrs(c, a, b);

    stop = clock();

    duration = ((double)(stop - start)) / CLOCKS_PER_SEC; //计算运行时间
    printf("Tsmt:%lf\n", duration);

    CATCH_ANY
    {
        ERROR(end);
    }
    code = RLC_OK;

end:
    gt_free(a);
    gt_free(b);
    gt_free(c);
    return code;
}

static int hash(void)
{ //测试 hash 操作运行时间
    int code = RLC_ERR;
    int i, j;
    uint8_t message[MSG_SIZE], digest[32];
    clock_t start, stop; //clock_t是clock()函数返回值的变量类型
    double duration;

    memset(message, 0, MSG_SIZE);

    start = clock();
    md_map_sh256(digest, message, strlen((char *)message));

    stop = clock();

    duration = ((double)(stop - start)) / CLOCKS_PER_SEC; //计算运行时间
    printf("Hash:%lf\n", duration);

    code = RLC_OK;

end:
    return code;
}

// int init(void)
// {

// 	bn_t x, y, z, tmp_bn, r, n, ai;
// 	g1_t A, g1, B, Y, Z, pk, tmp1, tmp2;
// 	g2_t g2, _X, _Y;
// 	gt_t xita;

// 	TRY
// 	{

// 		bn_null(r);
// 		bn_null(x);
// 		bn_null(y);
// 		bn_null(z);
// 		bn_null(tmp_bn);
// 		bn_null(n);
// 		bn_null(ai);

// 		g1_null(A);
// 		g1_null(g1);
// 		g1_null(B);
// 		g1_null(Y);
// 		g1_null(Z);
// 		g1_null(pk);
// 		g1_null(tmp1);
// 		g1_null(tmp2);

// 		g2_null(g2);
// 		g2_null(_X);
// 		g2_null(_Y);

// 		gt_null(xita);
// 	}

// 	TRY
// 	{

// 		bn_new(r);
// 		bn_new(x);
// 		bn_new(y);
// 		bn_new(z);
// 		bn_new(tmp_bn);
// 		bn_new(n);
// 		bn_new(ai);

// 		g1_new(A);
// 		g1_new(g1);
// 		g1_new(B);
// 		g1_new(Y);
// 		g1_new(Z);
// 		g1_new(pk);
// 		g1_new(tmp1);
// 		g1_new(tmp2);

// 		g2_new(g2);
// 		g2_new(_X);
// 		g2_new(_Y);

// 		gt_new(xita);
// 	}

// 	TRY
// 	{

// 		g1_get_gen(g1); // init g1 生成元

// 		g1_get_ord(n);
// 		bn_rand_mod(r, n); //init r

// 		g1_mul(A, g1, r);  // Ai=g1^r
// 		bn_rand_mod(x, n); // rand init x
// 		bn_rand_mod(y, n); // rand init x
// 		bn_rand_mod(z, n); // rand init x

// 		g2_get_gen(g2);

// 		g1_mul(Y, g1, y);

// 		g1_mul(pk, g1, ai);

// 		bn_mul(tmp_bn, y, r);
// 		g1_mul(tmp1, x, r);
// 		g1_mul(tmp2, pk, tmp_bn);

// 		g1_add(B, tmp1, tmp2);

// 		g1_mul(Z, g1, y);

// 		g2_mul(_X, g2, x);
// 		g2_mul(_Y, g2, y);

// 		gt_null(xita);
// 		gt_new(xita);
// 		pc_map(xita, g1, _X); //r=e(s,a)
// 	}

// 	TRY
// 	{
// 		bn_print(r);
// 		bn_print(x);
// 		bn_print(y);
// 		bn_print(z);
// 		bn_print(tmp_bn);
// 		bn_print(n);
// 		bn_print(ai);

// 		g1_print(A);
// 		g1_print(g1);
// 		g1_print(B);
// 		g1_print(Y);
// 		g1_print(Z);
// 		g1_print(pk);
// 		g1_print(tmp1);
// 		g1_print(tmp2);

// 		g2_print(g2);
// 		g2_print(_X);
// 		g2_print(_Y);

// 		gt_print(xita);
// 	}
// }

// static int algorithm1(void)
// {

// 	bn_t STM,k;
// 	bn_t x, y, z, tmp_bn, r, n, ai,rk,ra,rseta;
// 	g1_t A, g1, B, Y, Z, pk, tmp1, tmp2,T0,T1,T2;
// 	g2_t g2, _X, _Y;
// 	gt_t xita;

// 	TRY
// 	{

// // init all
// 		bn_null(r);
// 		bn_null(x);
// 		bn_null(y);
// 		bn_null(z);
// 		bn_null(tmp_bn);
// 		bn_null(n);
// 		bn_null(ai);

// // init algorithm1
// 		bn_null(STM);
// 		bn_null(k);

// 		bn_null(rk);
// 		bn_null(ra);
// 		bn_null(rseta);

// //_________________________________________________
// 		g1_null(A);
// 		g1_null(g1);
// 		g1_null(B);
// 		g1_null(Y);
// 		g1_null(Z);
// 		g1_null(pk);
// 		g1_null(tmp1);
// 		g1_null(tmp2);
// 		g1_null(T0);
// 		g1_null(T1);
// 		g1_null(T2);

// 		g2_null(g2);
// 		g2_null(_X);
// 		g2_null(_Y);
// //_________________________________________________
// 		gt_null(xita);
// 	}

// 	TRY
// 	{

// 		bn_new(r);
// 		bn_new(x);
// 		bn_new(y);
// 		bn_new(z);
// 		bn_new(tmp_bn);
// 		bn_new(n);
// 		bn_new(ai);

// 		bn_new(STM);
// 		bn_new(k);

// 		bn_new(rk);
// 		bn_new(ra);
// 		bn_new(rseta);

// 		g1_new(A);
// 		g1_new(g1);
// 		g1_new(B);
// 		g1_new(Y);
// 		g1_new(Z);
// 		g1_new(pk);
// 		g1_new(tmp1);
// 		g1_new(tmp2);

// 		g1_new(T0);
// 		g1_new(T1);
// 		g1_new(T2);

// 		g2_new(g2);
// 		g2_new(_X);
// 		g2_new(_Y);

// 		gt_new(xita);
// 	}

// 	TRY
// 	{

// 		g1_get_gen(g1); // init g1 生成元

// 		g1_get_ord(n);
// 		bn_rand_mod(r, n); //init r

// 		g1_mul(A, g1, r);  // Ai=g1^r
// 		bn_rand_mod(x, n); // rand init x
// 		bn_rand_mod(y, n); // rand init x
// 		bn_rand_mod(z, n); // rand init x

// 		g2_get_gen(g2);

// 		g1_mul(Y, g1, y);

// 		g1_mul(pk, g1, ai);

// 		bn_mul(tmp_bn, y, r);
// 		g1_mul(tmp1, x, r);
// 		g1_mul(tmp2, pk, tmp_bn);

// 		g1_add(B, tmp1, tmp2);

// 		g1_mul(Z, g1, y);

// 		g2_mul(_X, g2, x);
// 		g2_mul(_Y, g2, y);

// 		gt_null(xita);
// 		gt_new(xita);
// 		pc_map(xita, g1, _X); //r=e(s,a)

// 		g1_mul(T0,Z,k)；
// 		g1_

// 		hash();  // 待替换

// 	}

// 	TRY
// 	{
// 		bn_print(r);
// 		bn_print(x);
// 		bn_print(y);
// 		bn_print(z);
// 		bn_print(tmp_bn);
// 		bn_print(n);
// 		bn_print(ai);

// 		g1_print(A);
// 		g1_print(g1);
// 		g1_print(B);
// 		g1_print(Y);
// 		g1_print(Z);
// 		g1_print(pk);
// 		g1_print(tmp1);
// 		g1_print(tmp2);

// 		g2_print(g2);
// 		g2_print(_X);
// 		g2_print(_Y);

// 		gt_print(xita);
// 	}
// 	return 0;
// }

// static int algorithm2(void)
// {
// 	return 0;
// }

// static int algorithm3(void)
// {
// 	return 0;
// }

// #define _DEBUG

#ifdef _DEBUG
#define SetNull if (1)
#define SetNew if (1)
#define PrintAll if (1)
#define setInit if (1)
#define CHECK if (1)
#else
#define SetNull if (1)
#define SetNew if (1)
#define PrintAll if (0)
#define setInit if (1)
#define CHECK if (0)
#endif

struct Msg
{
    /* data */
    uint8_t STM[128];
    g1_t T0;
    g1_t T1;
    g1_t T2;
    g1_t T3; // add v2.0
    gt_t R0; // add v2.0
    g1_t R1;
    g1_t R2;
    uint8_t c[32]; // digest
    bn_t bn_c;
    bn_t Sk;
    bn_t Sa;
    bn_t Sdelta;
};

struct Car
{
    bn_t a;
    g1_t A;
    g1_t B;
    bn_t r;
    g1_t pk;
    struct Msg msg;
};

struct TA
{
    /* data */
    g1_t g1;
    g2_t g2;
    g1_t X;
    g1_t Y;
    g1_t Z;

    bn_t x; //random
    bn_t y; //random
    bn_t z; //random
    bn_t n;

    g2_t _X;
    g2_t _Y;
    g2_t _Z;

    gt_t thetax;
};

int setMsgNull(struct Msg *msg)
{
    /* data */
    memset(msg->STM, 0, 128);
    memset(msg->c, 0, 32);
    SetNull
    {
        g1_null(msg->T0);
        g1_null(msg->T1);
        g1_null(msg->T2);
        g1_null(msg->T3); // add v2.0
        g1_null(msg->R0);
        g1_null(msg->R1);
        gt_null(msg->R2);

        bn_null(msg->bn_c);
        bn_null(msg->Sk);
        bn_null(msg->Sa);
        bn_null(msg->Sdelta);
    }
}

int setMsgNew(struct Msg *msg)
{
    SetNew
    {
        g1_new(msg->T0);
        g1_new(msg->T1);
        g1_new(msg->T2);
        g1_new(msg->T3);
        g1_new(msg->R0);
        g1_new(msg->R1);
        gt_new(msg->R2);

        bn_new(msg->bn_c);
        bn_new(msg->Sk);
        bn_new(msg->Sa);
        bn_new(msg->Sdelta);
    }
}

int tmp_hash_print(const ep_t p)
{
    fp_print(p->y);
}

uint8_t *func(uint8_t a[], uint8_t b[], int len1, int len2)
{
    uint8_t *s;
    s = malloc(sizeof(uint8_t) * (len1 + len2));
    for (int i = 0; i < len1; i++)
        s[i] = a[i];
    for (int i = 0; i < len2; i++)
        s[len1 + i] = b[i];
    return s;
}

int setMsgInit(struct Msg *msg, const struct Car *car, const struct TA *ta)
{
    setInit
    {
        memset(msg->STM, 0, 128);

        bn_t mu, k, rk, ra, rdelta; //add  v2.0

        bn_null(mu); // add v2.0
        bn_null(k);
        bn_null(rk);
        bn_null(ra);
        bn_null(rdelta);
        bn_new(mu); // add v2.0
        bn_new(k);
        bn_new(rk);
        bn_new(ra);
        bn_new(rdelta);

        bn_rand_mod(mu, ta->n); // add v2.0
        bn_rand_mod(k, ta->n);
        bn_rand_mod(rk, ta->n);
        bn_rand_mod(ra, ta->n);
        bn_rand_mod(rdelta, ta->n);

        g1_mul(msg->T0, car->A, mu); //T0 v2.0
        g1_mul(msg->T1, car->B, mu); //T1 v2.0
        g1_mul(msg->T2, ta->Z, k);   //T1 v2.0

        g1_mul(msg->T3, ta->g1, k);
        g1_add(msg->T3, car->pk, msg->T3);
        g1_norm(msg->T3, msg->T3); // T3 v2.0

        g1_t g1_tmp_T0Ra;
        g1_null(g1_tmp_T0Ra);
        g1_new(g1_tmp_T0Ra);

        g1_mul(g1_tmp_T0Ra, msg->T0, ra);
        pc_map(msg->R0, g1_tmp_T0Ra, ta->_Y); //R0 v2.0

        g1_mul(msg->R1, ta->Z, rk); //R1 v2.0

        g1_t g1_tmp_g1ra, g1_tmp_g1rk;
        g1_null(g1_tmp_g1ra);
        g1_new(g1_tmp_g1ra);
        g1_null(g1_tmp_g1rk);
        g1_new(g1_tmp_g1rk);

        g1_mul(g1_tmp_g1ra, ta->g1, ra);
        g1_mul(g1_tmp_g1rk, ta->g1, rk);
        g1_add(msg->R2, g1_tmp_g1ra, g1_tmp_g1rk);
        g1_norm(msg->R2, msg->R2); //R2 v2.0

        uint8_t T0_bin[2 * RLC_PC_BYTES + 1];
        int l;
        l = g1_size_bin(msg->T0, 0);
        g1_write_bin(T0_bin, l, msg->T0, 0);

        uint8_t *s = func(msg->STM, T0_bin, sizeof(msg->STM), sizeof(T0_bin));
        int len_s = sizeof(msg->STM) + sizeof(T0_bin);

        // printf("%d\n",sizeof(msg->STM)+sizeof(T0_bin));
        // for(int i =0;i<sizeof(msg->STM)+sizeof(T0_bin);i++){
        // 	printf("%d",s[i]);

        // }
        // printf("\n");

        md_map_sh256(msg->c, s, len_s);
        // for(int i =0;i<sizeof(msg->c);i++){
        // 	printf("%d",msg->c[i]);
        // }
        // printf("\n");

        bn_read_bin(msg->bn_c, msg->c, sizeof(msg->c));
        // bn_print(msg->bn_c);

        bn_t bn_tmp_kc;
        bn_null(bn_tmp_kc);
        bn_new(bn_tmp_kc);
        bn_mul(bn_tmp_kc, k, msg->bn_c);
        bn_mod(bn_tmp_kc, bn_tmp_kc, ta->n);
        bn_sub(msg->Sk, bn_tmp_kc, rk); //Sk
        bn_mod(msg->Sk, msg->Sk, ta->n);

        bn_t bn_tmp_ac;
        bn_null(bn_tmp_ac);
        bn_new(bn_tmp_ac);
        bn_mul(bn_tmp_ac, car->a, msg->bn_c);
        bn_mod(bn_tmp_ac, bn_tmp_ac, ta->n);
        bn_sub(msg->Sa, bn_tmp_ac, ra); //Sa
        bn_mod(msg->Sa, msg->Sa, ta->n);
    }
    return 1;
}

int msgPrint(struct Msg *msg)
{
    for (int i = 0; i < 32; i++)
    {
        printf("%d", msg->c[i]);
    }
    printf("\n");
    PrintAll
    {
        g1_print(msg->T0);
        g1_print(msg->T1);
        g1_print(msg->T2);
        g1_print(msg->R0);
        g1_print(msg->R1);
        gt_print(msg->R2);

        bn_print(msg->bn_c);
        bn_print(msg->Sk);
        bn_print(msg->Sa);
        bn_print(msg->Sdelta);
    }
    return 1;
}

int initCar(struct Car *car, const struct TA *ta)
{
    SetNull
    {
        bn_null(car->a);
        g1_null(car->A);
        g1_null(car->B);
        bn_null(car->r);
        g1_null(car->pk);
        setMsgNull(&(car->msg));
    }

    SetNew
    {
        bn_new(car->a);
        g1_new(car->A);
        g1_new(car->B);
        bn_new(car->r);
        g1_new(car->pk);
        setMsgNew(&(car->msg));
    }

    setInit
    {
        bn_rand_mod(car->a, ta->n); //a
        bn_rand_mod(car->r, ta->n); //r

        g1_mul(car->A, ta->g1, car->r);  //A
        g1_mul(car->pk, ta->g1, car->a); //Pk

        bn_t bn_tmp;
        bn_null(bn_tmp);
        bn_new(bn_tmp);
        bn_mul(bn_tmp, ta->y, car->r);
        g1_t g1_tmp;
        g1_null(g1_tmp);
        g1_new(g1_tmp);
        g1_mul(g1_tmp, car->pk, bn_tmp);

        g1_t g1_tmp_2;
        g1_null(g1_tmp_2);
        g1_new(g1_tmp_2);
        g1_mul(g1_tmp_2, ta->X, car->r);

        g1_add(car->B, g1_tmp, g1_tmp_2); //B
    }

    PrintAll
    {
        bn_print(car->a);
        g1_print(car->A);
        g1_print(car->B);
        bn_print(car->r);
        g1_print(car->pk);
        msgPrint(&(car->msg));
    }
    return 1;
}

int initTA(struct TA *ta)
{
    SetNull
    {
        g1_null(ta->g1);
        g2_null(ta->g2);
        g1_null(ta->X);
        g1_null(ta->Y);
        g1_null(ta->Z);

        bn_null(ta->x); //random
        bn_null(ta->y); //random
        bn_null(ta->z); //random
        bn_null(ta->n); //random

        g2_null(ta->_X);
        g2_null(ta->_Y);
        g2_null(ta->_Z);

        gt_null(ta->thetax);
    }
    SetNew
    {
        g1_new(ta->g1);
        g2_new(ta->g2);
        g1_new(ta->X);
        g1_new(ta->Y);
        g1_new(ta->Z);

        bn_new(ta->x); //random
        bn_new(ta->y); //random
        bn_new(ta->z); //random
        bn_new(ta->n);

        g2_new(ta->_X);
        g2_new(ta->_Y);
        g2_new(ta->_Z);

        gt_new(ta->thetax);
    }
    // PrintAll
    // {
    // 	g1_print(ta->g1);
    // 	g2_print(ta->g2);
    // 	g1_print(ta->X);
    // 	g1_print(ta->Y);
    // 	g1_print(ta->Z);

    // 	bn_print(ta->x); //random
    // 	bn_print(ta->y); //random
    // 	bn_print(ta->z); //random

    // 	g2_print(ta->_X);
    // 	g2_print(ta->_Y);
    // 	g2_print(ta->_Z);

    // 	gt_print(ta->thetax);
    // }
    printf("init \n");
    setInit
    {

        g1_get_gen(ta->g1);
        g2_get_gen(ta->g2);

        g1_get_ord(ta->n);
        bn_rand_mod(ta->x, ta->n);
        bn_rand_mod(ta->y, ta->n);
        bn_rand_mod(ta->z, ta->n);

        g1_mul(ta->X, ta->g1, ta->x);
        g1_mul(ta->Y, ta->g1, ta->y);
        g1_mul(ta->Z, ta->g1, ta->z);

        g2_mul(ta->_X, ta->g2, ta->x);
        g2_mul(ta->_Y, ta->g2, ta->y);

        pc_map(ta->thetax, ta->g1, ta->_X); //r=e(s,a)
    }
    PrintAll
    {
        g1_print(ta->g1);
        g2_print(ta->g2);
        g1_print(ta->X);
        g1_print(ta->Y);
        g1_print(ta->Z);

        bn_print(ta->x); //random
        bn_print(ta->y); //random
        bn_print(ta->z); //random

        g2_print(ta->_X);
        g2_print(ta->_Y);
        g2_print(ta->_Z);

        gt_print(ta->thetax);
    }
}

int MessageVerify(struct Msg *msg, struct TA *ta)
{
    gt_t R0_;
    g1_t R1_, R2_;
    gt_null(R0_);
    g1_null(R1_);
    g1_null(R2_);

    gt_new(R0_);
    g1_new(R1_);
    g1_new(R2_);

    g1_t g1_tmp_Tc;
    g2_t g2_tmp_XC, g2_tmp_YSa, g2_tmp_addXY;
    gt_t gt_tmp_tcg2, gt_tmp_TXY;
    g1_null(g1_tmp_Tc);
    g2_null(g2_tmp_XC);
    g2_null(g2_tmp_YSa);
    g2_null(g2_tmp_addXY);
    gt_null(gt_tmp_tcg2);
    gt_null(gt_tmp_TXY);

    g1_new(g1_tmp_Tc);
    g2_new(g2_tmp_XC);
    g2_new(g2_tmp_YSa);
    g2_new(g2_tmp_addXY);
    gt_new(gt_tmp_tcg2);
    gt_new(gt_tmp_TXY);

    g1_mul(g1_tmp_Tc, msg->T1, msg->bn_c);
    pc_map(gt_tmp_tcg2, g1_tmp_Tc, ta->g2);

    g2_mul(g2_tmp_XC, ta->_X, msg->bn_c);
    g2_mul(g2_tmp_YSa, ta->_Y, msg->Sa);
    g2_add(g2_tmp_addXY, g2_tmp_XC, g2_tmp_YSa);
    g2_norm(g2_tmp_addXY, g2_tmp_addXY);

    pc_map(gt_tmp_TXY, msg->T0, g2_tmp_addXY);
    gt_inv(gt_tmp_TXY, gt_tmp_TXY);

    gt_mul(R0_, gt_tmp_tcg2, gt_tmp_TXY);

    CHECK
    {
        if (gt_cmp(R0_, msg->R0) == RLC_EQ)
        {
            printf("R0 Success\n");
        }
        else
        {
            printf("R0 Failed\n");
            printf("R0\n");
            gt_print(msg->R0);
            printf("R0_\n");
            gt_print(R0_);
        }
    }

    g1_t g1_tmp_T2c, g1_tmp_Zsk;
    g1_null(g1_tmp_T2c);
    g1_null(g1_tmp_Zsk);
    g1_new(g1_tmp_T2c);
    g1_new(g1_tmp_Zsk);

    g1_mul(g1_tmp_T2c, msg->T2, msg->bn_c);
    g1_mul(g1_tmp_Zsk, ta->Z, msg->Sk);

    g1_sub(R1_, g1_tmp_T2c, g1_tmp_Zsk);
    g1_norm(R1_, R1_);

    CHECK
    {
        if (g1_cmp(R1_, msg->R1) == RLC_EQ)
        {
            printf("R1 Success\n");
        }
        else
        {
            printf("R1 Failed\n");
        }
    }

    g1_t g1_tmp_T3c, g1_tmp_g1sask;
    bn_t bn_tmp_sask;
    g1_null(g1_tmp_T3c);
    g1_null(g1_tmp_g1sask);
    bn_null(bn_tmp_sask);
    g1_new(g1_tmp_T3c);
    g1_new(g1_tmp_g1sask);
    bn_new(bn_tmp_sask);

    g1_mul(g1_tmp_T3c, msg->T3, msg->bn_c);
    bn_add(bn_tmp_sask, msg->Sa, msg->Sk);
    bn_mod(bn_tmp_sask, bn_tmp_sask, ta->n);
    g1_mul(g1_tmp_g1sask, ta->g1, bn_tmp_sask);
    g1_sub(R2_, g1_tmp_T3c, g1_tmp_g1sask);
    g1_norm(R2_, R2_);

    CHECK
    {
        if (g1_cmp(R2_, msg->R2) == RLC_EQ)
        {
            printf("R2 Success\n");
        }
        else
        {
            printf("R2 Failed\n");
        }
    }

    gt_free(R0_);
    g1_free(R1_);
    g1_free(R2_);
    g1_free(g1_tmp_Tc);
    g2_free(g2_tmp_XC);
    g2_free(g2_tmp_YSa);
    g2_free(g2_tmp_addXY);
    gt_free(gt_tmp_tcg2);
    gt_free(gt_tmp_TXY); // ....
    // return 0;
}

int batchMessageVerify(struct Car *car, int car_num, struct TA *ta)
{
    // printf("%d number\n", car_num);
    g1_t *R_1 = (struct g1_t *)malloc(sizeof(g1_t) * car_num);
    g1_t *R_2 = (struct g1_t *)malloc(sizeof(g1_t) * car_num);
    // init R_1,R_@
    for (int i = 0; i < car_num; i++)
    {
        g1_null(R_1[i]);
        g1_null(R_2[i]);
        g1_new(R_1[i]);
        g1_new(R_2[i]);
        g1_t g1_tmp_T2c, g1_tmp_Zsk;
        g1_null(g1_tmp_T2c);
        g1_null(g1_tmp_Zsk);
        g1_new(g1_tmp_T2c);
        g1_new(g1_tmp_Zsk);

        g1_mul(g1_tmp_T2c, car->msg.T2, car->msg.bn_c);
        g1_mul(g1_tmp_Zsk, ta->Z, car->msg.Sk);

        g1_sub(R_1[i], g1_tmp_T2c, g1_tmp_Zsk);
        g1_norm(R_1[i], R_1[i]);

        CHECK
        {
            if (g1_cmp(R_1[i], car->msg.R1) == RLC_EQ)
            {
                // printf("R1 Success\n");
                continue;
            }
            else
            {
                printf("R1 Failed\n");
            }
        }

        g1_t g1_tmp_T3c, g1_tmp_g1sask;
        bn_t bn_tmp_sask;
        g1_null(g1_tmp_T3c);
        g1_null(g1_tmp_g1sask);
        bn_null(bn_tmp_sask);
        g1_new(g1_tmp_T3c);
        g1_new(g1_tmp_g1sask);
        bn_new(bn_tmp_sask);

        g1_mul(g1_tmp_T3c, car->msg.T3, car->msg.bn_c);
        bn_add(bn_tmp_sask, car->msg.Sa, car->msg.Sk);
        bn_mod(bn_tmp_sask, bn_tmp_sask, ta->n);
        g1_mul(g1_tmp_g1sask, ta->g1, bn_tmp_sask);
        g1_sub(R_2[i], g1_tmp_T3c, g1_tmp_g1sask);
        g1_norm(R_2[i], R_2[i]);

        CHECK
        {
            if (g1_cmp(R_2[i], car->msg.R2) == RLC_EQ)
            {
                // printf("R2 Success\n");
                continue;
            }
            else
            {
                printf("R2 Failed\n");
            }
        }
    }

    // 第二个验证

    bn_t *eta = (struct bn_t *)malloc(sizeof(bn_t) * car_num);
    for (int i = 0; i < car_num; i++)
    {
        bn_null(eta[i]);
        bn_new(eta[i]);
        bn_rand_mod(eta[i], ta->n);
        // bn_print(eta[i]);
    }

    gt_t gt_tmp_total;
    gt_null(gt_tmp_total);
    gt_new(gt_tmp_total);
    for (int i = 0; i < car_num; i++)
    {
        if (i == 0)
        {
            gt_exp(gt_tmp_total, car[i].msg.R0, eta[i]);
        }
        else
        {
            gt_t gt_tmp_Reta;
            gt_null(gt_tmp_Reta);
            gt_new(gt_tmp_Reta);
            gt_exp(gt_tmp_Reta, car[i].msg.R0, eta[i]);
            gt_mul(gt_tmp_total, gt_tmp_total, gt_tmp_Reta);
        }
    }

    g1_t g1_tmp_Tceta;
    g1_null(g1_tmp_Tceta);
    g1_new(g1_tmp_Tceta);
    for (int i = 0; i < car_num; i++)
    {
        if (i == 0)
        {
            bn_t bn_tmp_ceta;
            bn_null(bn_tmp_ceta);
            bn_new(bn_tmp_ceta);
            bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
            bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
            g1_mul(g1_tmp_Tceta, car[i].msg.T1, bn_tmp_ceta);
        }
        else
        {
            bn_t bn_tmp_ceta;
            bn_null(bn_tmp_ceta);
            bn_new(bn_tmp_ceta);
            bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
            bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
            g1_t g1_tmp_Tceta_;
            g1_null(g1_tmp_Tceta_);
            g1_new(g1_tmp_Tceta_);
            g1_mul(g1_tmp_Tceta_, car[i].msg.T1, bn_tmp_ceta);
            g1_add(g1_tmp_Tceta, g1_tmp_Tceta, g1_tmp_Tceta_);
            g1_norm(g1_tmp_Tceta, g1_tmp_Tceta);
        }
    }

    gt_t gt_tmp_tcetag2;
    gt_null(gt_tmp_tcetag2);
    gt_new(gt_tmp_tcetag2);

    pc_map(gt_tmp_tcetag2, g1_tmp_Tceta, ta->g2); //e1

    g1_t g1_tmp_T0ceta;
    g1_null(g1_tmp_T0ceta);
    g1_new(g1_tmp_T0ceta);
    for (int i = 0; i < car_num; i++)
    {
        if (i == 0)
        {
            bn_t bn_tmp_ceta;
            bn_null(bn_tmp_ceta);
            bn_new(bn_tmp_ceta);
            bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
            bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
            g1_mul(g1_tmp_T0ceta, car[i].msg.T0, bn_tmp_ceta);
        }
        else
        {
            bn_t bn_tmp_ceta;
            bn_null(bn_tmp_ceta);
            bn_new(bn_tmp_ceta);
            bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
            bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
            g1_t g1_tmp_T0ceta_;
            g1_null(g1_tmp_T0ceta_);
            g1_new(g1_tmp_T0ceta_);
            g1_mul(g1_tmp_T0ceta_, car[i].msg.T0, bn_tmp_ceta);
            g1_add(g1_tmp_T0ceta, g1_tmp_T0ceta, g1_tmp_T0ceta_);
            g1_norm(g1_tmp_T0ceta, g1_tmp_T0ceta);
        }
    }

    gt_t gt_tmp_t1ceta_X;
    gt_null(gt_tmp_t1ceta_X);
    gt_new(gt_tmp_t1ceta_X);

    pc_map(gt_tmp_t1ceta_X, g1_tmp_T0ceta, ta->_X); //e2

    g1_t g1_tmp_T0Saeta;
    g1_null(g1_tmp_T0Saeta);
    g1_new(g1_tmp_T0Saeta);
    for (int i = 0; i < car_num; i++)
    {
        if (i == 0)
        {
            bn_t bn_tmp_saeta;
            bn_null(bn_tmp_saeta);
            bn_new(bn_tmp_saeta);
            bn_mul(bn_tmp_saeta, car[i].msg.Sa, eta[i]);
            bn_mod(bn_tmp_saeta, bn_tmp_saeta, ta->n);
            g1_mul(g1_tmp_T0Saeta, car[i].msg.T0, bn_tmp_saeta);
        }
        else
        {
            bn_t bn_tmp_saeta;
            bn_null(bn_tmp_saeta);
            bn_new(bn_tmp_saeta);
            bn_mul(bn_tmp_saeta, car[i].msg.Sa, eta[i]);
            bn_mod(bn_tmp_saeta, bn_tmp_saeta, ta->n);
            g1_t g1_tmp_T0Saeta_;
            g1_null(g1_tmp_T0Saeta_);
            g1_new(g1_tmp_T0Saeta_);
            g1_mul(g1_tmp_T0Saeta_, car[i].msg.T0, bn_tmp_saeta);
            g1_add(g1_tmp_T0Saeta, g1_tmp_T0Saeta, g1_tmp_T0Saeta_);
            g1_norm(g1_tmp_T0Saeta, g1_tmp_T0Saeta);
        }
    }

    gt_t gt_tmp_T0saeta_Y;
    gt_null(gt_tmp_T0saeta_Y);
    gt_new(gt_tmp_T0saeta_Y);

    pc_map(gt_tmp_T0saeta_Y, g1_tmp_T0Saeta, ta->_Y); //e3

    gt_t gt_tmp_e1_e2;
    gt_null(gt_tmp_e1_e2);
    gt_new(gt_tmp_e1_e2);
    gt_mul(gt_tmp_e1_e2, gt_tmp_t1ceta_X, gt_tmp_T0saeta_Y);
    gt_inv(gt_tmp_e1_e2, gt_tmp_e1_e2);

    gt_t gt_tmp_ethetax_inv_ee;
    gt_null(gt_tmp_ethetax_inv_ee);
    gt_new(gt_tmp_ethetax_inv_ee);

    gt_mul(gt_tmp_ethetax_inv_ee, gt_tmp_tcetag2, gt_tmp_e1_e2);

    CHECK
    {
        if (gt_cmp(gt_tmp_total, gt_tmp_ethetax_inv_ee) == RLC_EQ)
        {
            printf("gt success\n");
        }
        else
        {
            printf("gt Failed\n");
        }
    }
}

int batchMessageVerify2(struct Car *car, int car_num, struct TA *ta)
{

    g1_t *R_1 = (struct g1_t *)malloc(sizeof(g1_t) * car_num);
    g1_t *R_2 = (struct g1_t *)malloc(sizeof(g1_t) * car_num);
    // init R_1,R_@
    for (int i = 0; i < car_num; i++)
    {
        g1_null(R_1[i]);
        g1_null(R_2[i]);
        g1_new(R_1[i]);
        g1_new(R_2[i]);
        g1_t g1_tmp_T2c, g1_tmp_Zsk;
        g1_null(g1_tmp_T2c);
        g1_null(g1_tmp_Zsk);
        g1_new(g1_tmp_T2c);
        g1_new(g1_tmp_Zsk);

        g1_mul(g1_tmp_T2c, car->msg.T2, car->msg.bn_c);
        g1_mul(g1_tmp_Zsk, ta->Z, car->msg.Sk);

        g1_sub(R_1[i], g1_tmp_T2c, g1_tmp_Zsk);
        g1_norm(R_1[i], R_1[i]);

        CHECK
        {
            if (g1_cmp(R_1[i], car->msg.R1) == RLC_EQ)
            {
                // printf("R1 Success\n");
                continue;
            }
            else
            {
                printf("R1 Failed\n");
            }
        }

        g1_t g1_tmp_T3c, g1_tmp_g1sask;
        bn_t bn_tmp_sask;
        g1_null(g1_tmp_T3c);
        g1_null(g1_tmp_g1sask);
        bn_null(bn_tmp_sask);
        g1_new(g1_tmp_T3c);
        g1_new(g1_tmp_g1sask);
        bn_new(bn_tmp_sask);

        g1_mul(g1_tmp_T3c, car->msg.T3, car->msg.bn_c);
        bn_add(bn_tmp_sask, car->msg.Sa, car->msg.Sk);
        bn_mod(bn_tmp_sask, bn_tmp_sask, ta->n);
        g1_mul(g1_tmp_g1sask, ta->g1, bn_tmp_sask);
        g1_sub(R_2[i], g1_tmp_T3c, g1_tmp_g1sask);
        g1_norm(R_2[i], R_2[i]);

        CHECK
        {
            if (g1_cmp(R_2[i], car->msg.R2) == RLC_EQ)
            {
                // printf("R2 Success\n");
                continue;
            }
            else
            {
                printf("R2 Failed\n");
            }
        }
    }

    // 第二个验证

    bn_t *eta = (struct bn_t *)malloc(sizeof(bn_t) * car_num);
    gt_t gt_tmp_total;
    gt_null(gt_tmp_total);
    gt_new(gt_tmp_total);
    g1_t g1_tmp_Tceta;
    g1_null(g1_tmp_Tceta);
    g1_new(g1_tmp_Tceta);
    g1_t g1_tmp_T0ceta;
    g1_null(g1_tmp_T0ceta);
    g1_new(g1_tmp_T0ceta);
    g1_t g1_tmp_T0Saeta;
    g1_null(g1_tmp_T0Saeta);
    g1_new(g1_tmp_T0Saeta);
    for (int i = 0; i < car_num; i++)
    {
        bn_null(eta[i]);
        bn_new(eta[i]);
        bn_rand_mod(eta[i], ta->n);
        // bn_print(eta[i]);
        if (i == 0)
        {
            gt_exp(gt_tmp_total, car[i].msg.R0, eta[i]);
        }
        else
        {
            gt_t gt_tmp_Reta;
            gt_null(gt_tmp_Reta);
            gt_new(gt_tmp_Reta);
            gt_exp(gt_tmp_Reta, car[i].msg.R0, eta[i]);
            gt_mul(gt_tmp_total, gt_tmp_total, gt_tmp_Reta);
        }
        if (i == 0)
        {
            bn_t bn_tmp_ceta;
            bn_null(bn_tmp_ceta);
            bn_new(bn_tmp_ceta);
            bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
            bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
            g1_mul(g1_tmp_Tceta, car[i].msg.T1, bn_tmp_ceta);
        }
        else
        {
            bn_t bn_tmp_ceta;
            bn_null(bn_tmp_ceta);
            bn_new(bn_tmp_ceta);
            bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
            bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
            g1_t g1_tmp_Tceta_;
            g1_null(g1_tmp_Tceta_);
            g1_new(g1_tmp_Tceta_);
            g1_mul(g1_tmp_Tceta_, car[i].msg.T1, bn_tmp_ceta);
            g1_add(g1_tmp_Tceta, g1_tmp_Tceta, g1_tmp_Tceta_);
            g1_norm(g1_tmp_Tceta, g1_tmp_Tceta);
        }
        if (i == 0)
        {
            bn_t bn_tmp_ceta;
            bn_null(bn_tmp_ceta);
            bn_new(bn_tmp_ceta);
            bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
            bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
            g1_mul(g1_tmp_T0ceta, car[i].msg.T0, bn_tmp_ceta);
        }
        else
        {
            bn_t bn_tmp_ceta;
            bn_null(bn_tmp_ceta);
            bn_new(bn_tmp_ceta);
            bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
            bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
            g1_t g1_tmp_T0ceta_;
            g1_null(g1_tmp_T0ceta_);
            g1_new(g1_tmp_T0ceta_);
            g1_mul(g1_tmp_T0ceta_, car[i].msg.T0, bn_tmp_ceta);
            g1_add(g1_tmp_T0ceta, g1_tmp_T0ceta, g1_tmp_T0ceta_);
            g1_norm(g1_tmp_T0ceta, g1_tmp_T0ceta);
        }
        if (i == 0)
        {
            bn_t bn_tmp_saeta;
            bn_null(bn_tmp_saeta);
            bn_new(bn_tmp_saeta);
            bn_mul(bn_tmp_saeta, car[i].msg.Sa, eta[i]);
            bn_mod(bn_tmp_saeta, bn_tmp_saeta, ta->n);
            g1_mul(g1_tmp_T0Saeta, car[i].msg.T0, bn_tmp_saeta);
        }
        else
        {
            bn_t bn_tmp_saeta;
            bn_null(bn_tmp_saeta);
            bn_new(bn_tmp_saeta);
            bn_mul(bn_tmp_saeta, car[i].msg.Sa, eta[i]);
            bn_mod(bn_tmp_saeta, bn_tmp_saeta, ta->n);
            g1_t g1_tmp_T0Saeta_;
            g1_null(g1_tmp_T0Saeta_);
            g1_new(g1_tmp_T0Saeta_);
            g1_mul(g1_tmp_T0Saeta_, car[i].msg.T0, bn_tmp_saeta);
            g1_add(g1_tmp_T0Saeta, g1_tmp_T0Saeta, g1_tmp_T0Saeta_);
            g1_norm(g1_tmp_T0Saeta, g1_tmp_T0Saeta);
        }
    }

    gt_t gt_tmp_tcetag2;
    gt_null(gt_tmp_tcetag2);
    gt_new(gt_tmp_tcetag2);

    pc_map(gt_tmp_tcetag2, g1_tmp_Tceta, ta->g2); //e1

    gt_t gt_tmp_t1ceta_X;
    gt_null(gt_tmp_t1ceta_X);
    gt_new(gt_tmp_t1ceta_X);

    pc_map(gt_tmp_t1ceta_X, g1_tmp_T0ceta, ta->_X); //e2

    gt_t gt_tmp_T0saeta_Y;
    gt_null(gt_tmp_T0saeta_Y);
    gt_new(gt_tmp_T0saeta_Y);

    pc_map(gt_tmp_T0saeta_Y, g1_tmp_T0Saeta, ta->_Y); //e3

    gt_t gt_tmp_e1_e2;
    gt_null(gt_tmp_e1_e2);
    gt_new(gt_tmp_e1_e2);
    gt_mul(gt_tmp_e1_e2, gt_tmp_t1ceta_X, gt_tmp_T0saeta_Y);
    gt_inv(gt_tmp_e1_e2, gt_tmp_e1_e2);

    gt_t gt_tmp_ethetax_inv_ee;
    gt_null(gt_tmp_ethetax_inv_ee);
    gt_new(gt_tmp_ethetax_inv_ee);

    gt_mul(gt_tmp_ethetax_inv_ee, gt_tmp_tcetag2, gt_tmp_e1_e2);

    CHECK
    {
        if (gt_cmp(gt_tmp_total, gt_tmp_ethetax_inv_ee) == RLC_EQ)
        {
            printf("gt success\n");
        }
        else
        {
            printf("gt Failed\n");
        }
    }
}

int test(struct TA *ta)
{
    bn_t k, c, kc, rk, Sk;
    bn_null(k);
    bn_null(c);
    bn_null(kc);
    bn_null(rk);
    bn_null(Sk);

    bn_new(k);
    bn_new(c);
    bn_new(kc);
    bn_new(rk);
    bn_new(Sk);

    bn_rand_mod(k, ta->n);
    bn_rand_mod(c, ta->n);
    bn_rand_mod(rk, ta->n);

    bn_mul(kc, k, c);
    bn_mod(kc, kc, ta->n);
    bn_sub(Sk, kc, rk);
    bn_mod(Sk, Sk, ta->n); //Sk

    g1_t R0, R0_, T0;

    g1_null(R0);
    g1_null(T0);
    g1_null(R0_);

    g1_new(R0);
    g1_new(T0);
    g1_new(R0_);

    g1_mul(R0, ta->Z, rk);
    // printf("R0:\n");
    // g1_print(R0);

    g1_mul(T0, ta->Z, k);

    g1_t t0c, zsk;
    g1_null(t0c);
    g1_null(zsk);

    g1_new(t0c);
    g1_new(zsk);

    g1_mul(t0c, T0, c);
    g1_mul(zsk, ta->Z, Sk);
    g1_sub(R0_, t0c, zsk);
    // printf("R0_\n");
    g1_norm(R0_, R0_);
    // g1_print(R0_);

    // g1_t g1_tmp_neg_zsk;
    // g1_null(g1_tmp_neg_zsk);
    // g1_new(g1_tmp_neg_zsk);

    // g1_neg(g1_tmp_neg_zsk,zsk);
    // g1_t tmp_R0_;
    // g1_null(tmp_R0_);
    // g1_new(tmp_R0_);

    // g1_add(tmp_R0_,t0c,g1_tmp_neg_zsk);
    // printf("neg_add:\n");
    // g1_print(tmp_R0_);
}

int test_1(struct TA *ta)
{
    bn_t k, c;

    bn_null(k);
    bn_null(c);

    bn_new(k);
    bn_new(c);

    bn_rand_mod(k, ta->n);
    bn_rand_mod(c, ta->n);

    bn_t tmp_k_c;
    bn_null(tmp_k_c);
    bn_new(tmp_k_c);

    bn_sub(tmp_k_c, k, c);
    bn_mod(tmp_k_c, tmp_k_c, ta->n);

    g1_t tmp_kcz;
    g1_null(tmp_kcz);
    g1_new(tmp_kcz);

    g1_mul(tmp_kcz, ta->Z, tmp_k_c);
    PrintAll
    {
        printf("(k-c)*z\n");
        // g1_norm(tmp_kcz,tmp_kcz);
        g1_print(tmp_kcz);
    }

    g1_t tmp_kz, tmp_cz, tmp_kz_cz;
    g1_null(tmp_kz);
    g1_null(tmp_cz);
    g1_null(tmp_kz_cz);

    g1_new(tmp_kz);
    g1_new(tmp_cz);
    g1_new(tmp_kz_cz);

    g1_mul(tmp_kz, ta->Z, k);
    g1_mul(tmp_cz, ta->Z, c);
    g1_sub(tmp_kz_cz, tmp_kz, tmp_cz);
    g1_norm(tmp_kz_cz, tmp_kz_cz);
    PrintAll
    {
        printf("kz-cz\n");
        g1_print(tmp_kz_cz);
    }
}

int main()
{

    if (core_init() != RLC_OK)
    {
        core_clean();
        return 1;
    }
    //conf_print();
    // if (pc_param_set_any() == RLC_OK)
    // {

    // printf(ep_param_get()
    // if (Tsm1() != RLC_OK)
    // {
    // 	core_clean();
    // 	return 1;
    // }
    // if (Tsm2() != RLC_OK)
    // {
    // 	core_clean();
    // 	return 1;
    // }
    // if (EPT() != RLC_OK)
    // {
    // 	core_clean();
    // 	return 1;
    // }

    // if (Tsmt() != RLC_OK)
    // {
    // 	core_clean();
    // 	return 1;
    // }
    //}

    if (ep_param_set_any_pairf() != RLC_OK)
    {
        THROW(ERR_NO_CURVE);
        core_clean();
        return 0;
    }
    ep_param_print();
    if (ep_param_embed() == 12)
    {
        Tsm1();
        Tsm2();
        Tsmt();
        EPT();
        Tpar();
        hash();
        // init();

        struct TA ta;
        initTA(&ta);

        struct Car car1;
        initCar(&car1, &ta);
        setMsgInit(&car1.msg, &car1, &ta);

        // test(&ta);
        // MessageVerify(&car1.msg, &ta); // ok

        int car_num[8] = {10, 50, 100, 200, 300, 400, 500, 1000};
        // int car_num[1] = {100};
        for (int index = 0; index < 8; index++)
        {
            struct Car *car = (struct Car *)malloc(sizeof(struct Car) * car_num[index]);
            for (int i = 0; i < car_num[index]; i++)
            {
                initCar(&car[i], &ta);
                setMsgInit(&car[i].msg, &car[i], &ta);
                // bn_print(car[i].msg.bn_c);
            }

            if (1)
            {
                clock_t start, stop;
                double duration;
                start = clock();

                batchMessageVerify(car, car_num[index], &ta);
                stop = clock();
                duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
                printf("%d car batchMessageVerify cost time :%lf, per %f\n", car_num[index], duration, duration / car_num[index]);
            }
            if (1)
            {
                clock_t start, stop;
                double duration;
                start = clock();

                batchMessageVerify2(car, car_num[index], &ta);
                stop = clock();
                duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
                printf("%d car batchMessageVerify2 cost time :%lf, per %f\n", car_num[index], duration, duration / car_num[index]);
            }
        }
    }

    core_clean();
    return 0;
}
