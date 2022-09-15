
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

static int MapToPoint(void)
{ //测试 hash to G1 运行时间
	g1_t p;
	//uint8_t m = 0;
	uint8_t msg[32];
	// uint8_t *msgs[5] = {m,m,m,m,m};
	// int lens[5] = {sizeof(m), sizeof(m), sizeof(m), sizeof(m), sizeof(m)};
	rand_bytes(msg, 32);
	int result = RLC_OK;
	clock_t start, stop; //clock_t是clock()函数返回值的变量类型
	double duration;
	g1_null(p);

	TRY {
		g1_new(p);
		start = clock();
		g1_map(p, msg, 32);
		stop = clock();

	duration = ((double)(stop - start)) / CLOCKS_PER_SEC; //计算运行时间
	printf("MaptoHash:%lf\n", duration);

	}
	CATCH_ANY {
		result = RLC_ERR;
	}
	FINALLY {
		g1_free(p);
	}
	return result;
}

static int BNmutip(void)
{ //测试 hash to G1 运行时间
	bn_t mu,k, rk, n;  //add  v2.0
    g1_t p;
	clock_t start, stop; //clock_t是clock()函数返回值的变量类型
	double duration;
	int result = RLC_OK;
		bn_null(mu);   // add v2.0
		bn_null(k);
		bn_null(rk);
		g1_null(p);
		bn_new(k);
		bn_new(n);
		bn_new(rk);
		g1_new(p);
		g1_rand(p);
		g1_get_ord(n);
		bn_rand_mod(k, n);	
		bn_rand_mod(rk, n);	
		start = clock();
			g1_print(p);
			for (int i=0;i<6;i++)
			{
			 //bn_print(rk);
	         bn_add(rk,k,rk);
			 bn_mod_2b(rk,rk,n);
			}
		// bn_print(rk);
		stop = clock();
	duration = ((double)(stop - start)) / CLOCKS_PER_SEC; //计算运行时间
	printf("BNmmutiply:%lf\n", duration);
	return result;
}


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
	g1_t T3;   // add v2.0
	g1_t R0;
	g1_t R1;
	gt_t R2;
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

		bn_t mu,k, rk, ra, rdelta;  //add  v2.0

		bn_null(mu);   // add v2.0
		bn_null(k);
		bn_null(rk);
		bn_null(ra);
		bn_null(rdelta);
		bn_new(k);
		bn_new(rk);
		bn_new(ra);
		bn_new(rdelta);

		bn_rand_mod(k, ta->n);
		bn_rand_mod(rk, ta->n);
		bn_rand_mod(ra, ta->n);
		bn_rand_mod(rdelta, ta->n);

		g1_mul(msg->T0, ta->Z, k); //T0

		g1_t g1_tmp_t1;
		g1_null(g1_tmp_t1);
		g1_new(g1_tmp_t1);
		g1_mul(g1_tmp_t1, ta->g1, k);
		g1_add(msg->T1, car->A, g1_tmp_t1); // T1

		g1_t g1_tmp_t2;
		g1_null(g1_tmp_t2);
		g1_new(g1_tmp_t2);
		bn_t bn_tmp_t;
		bn_null(bn_tmp_t);
		bn_new(bn_tmp_t);
		bn_mul(bn_tmp_t, k, car->a);
		g1_mul(g1_tmp_t2, ta->Y, bn_tmp_t);
		g1_add(msg->T2, car->B, g1_tmp_t2); // T2

		g1_mul(msg->R0, ta->Z, rk); //R0

		g1_t g1_tmp_tr, g1_tmp_zr;
		g1_mul(g1_tmp_tr, msg->T0, ra);
		g1_mul(g1_tmp_zr, ta->Z, rdelta);
		g1_sub(msg->R1, g1_tmp_tr, g1_tmp_zr); //R1
		g1_norm(msg->R1, msg->R1);

		gt_t gt_tmp_t;
		gt_null(gt_tmp_t);
		gt_new(gt_tmp_t);
		pc_map(gt_tmp_t, msg->T1, ta->_Y); //r=e(s,a)
		gt_t gt_tmp_t1;
		gt_null(gt_tmp_t1);
		gt_new(gt_tmp_t1);
		gt_exp(gt_tmp_t1, gt_tmp_t, ra);
		gt_t gt_tmp_t2;
		gt_null(gt_tmp_t2);
		gt_new(gt_tmp_t2);
		gt_exp(gt_tmp_t2, ta->thetax, rk);
		gt_t gt_tmp_t3;
		gt_null(gt_tmp_t3);
		gt_new(gt_tmp_t3);
		gt_inv(gt_tmp_t3, gt_tmp_t2);
		gt_mul(msg->R2, gt_tmp_t1, gt_tmp_t3); //R2

		// for(int i=0;i<128;i++){
		// 	printf("%d",msg->STM[i]);
		// 	if((i+1)%16==0) printf(" ");
		// }
		// printf("\n");
		// g1_print(msg->T0);
		// tmp_hash_print(msg->T1);
		// tmp_hash_print(msg->T2);
		// tmp_hash_print(msg->R0);
		// tmp_hash_print(msg->R1);
		// tmp_hash_print(msg->R2);

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

		bn_t bn_tmp_ka, bn_tmp_kac;

		bn_null(bn_tmp_ka);
		bn_new(bn_tmp_ka);
		bn_mul(bn_tmp_ka, k, car->a);
		bn_null(bn_tmp_kac);
		bn_new(bn_tmp_kac);
		bn_mul(bn_tmp_kac, bn_tmp_ka, msg->bn_c);
		bn_sub(msg->Sdelta, bn_tmp_kac, rdelta); //sDelta
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

		g1_mul(car->A, ta->g1, car->r);	 //A
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
	g1_t R0_, R1_, R2_;
	g1_null(R0_);
	g1_null(R1_);
	g1_null(R2_);

	g1_new(R0_);
	g1_new(R1_);
	g1_new(R2_);

	g1_t g1_tmp_T0c, g1_tmp_zsk;

	g1_null(g1_tmp_T0c);
	g1_null(g1_tmp_zsk);

	g1_new(g1_tmp_T0c);
	g1_new(g1_tmp_zsk);

	g1_mul(g1_tmp_T0c, msg->T0, msg->bn_c);
	g1_mul(g1_tmp_zsk, ta->Z, msg->Sk);
	g1_sub(R0_, g1_tmp_T0c, g1_tmp_zsk);
	g1_norm(R0_, R0_);

	//R2
	CHECK
	{
		printf("R0_ \n");
		g1_print(R0_);

		printf("msg->R0 \n");
		g1_print(msg->R0);
	}

	g1_t g1_tmp_ZSdelta, g1_tmp_ZSa;
	g1_null(g1_tmp_ZSdelta);
	g1_null(g1_tmp_ZSa);

	g1_new(g1_tmp_ZSdelta);
	g1_new(g1_tmp_ZSa);

	g1_mul(g1_tmp_ZSdelta, ta->Z, msg->Sdelta);
	g1_mul(g1_tmp_ZSa, ta->Z, msg->Sa);
	g1_sub(R1_, g1_tmp_ZSdelta, g1_tmp_ZSa);
	g1_norm(R1_, R1_);

	//R1
	CHECK
	{
		printf("R1_ \n");
		g1_print(R1_);

		printf("msg->R1 \n");
		g1_print(msg->R1);
	}

	gt_t gt_tmp_eTg, gt_tmp_ec, gt_tmp_thetax_sk, gt_tmp_TXY, gt_tmp_add;
	g2_t g2_tmp_exp_XC, g2_tmp_exp_YSa, g2_tmp_add_XY;
	gt_null(gt_tmp_eTg);
	gt_null(gt_tmp_ec);
	gt_null(gt_tmp_thetax_sk);
	gt_null(gt_tmp_TXY);
	gt_null(gt_tmp_add);

	g2_null(g2_tmp_exp_XC);
	g2_null(g2_tmp_exp_YSa);
	g2_null(g2_tmp_add_XY);
	g2_null(gt_tmp_add);

	gt_new(gt_tmp_eTg);
	gt_new(gt_tmp_ec);
	gt_new(gt_tmp_thetax_sk);
	gt_new(gt_tmp_TXY);

	g2_new(g2_tmp_exp_XC);
	g2_new(g2_tmp_exp_YSa);
	g2_new(g2_tmp_add_XY);

	pc_map(gt_tmp_eTg, msg->T2, ta->g2); //r=e(s,a)
	gt_exp(gt_tmp_ec, gt_tmp_eTg, msg->bn_c);

	gt_exp(gt_tmp_thetax_sk, ta->thetax, msg->Sk);
	gt_mul(gt_tmp_add, gt_tmp_ec, gt_tmp_thetax_sk);

	g2_mul(g2_tmp_exp_XC, ta->_X, msg->bn_c);
	g2_mul(g2_tmp_exp_YSa, ta->_Y, msg->Sa);
	g2_add(g2_tmp_add_XY, g2_tmp_exp_XC, g2_tmp_exp_YSa);
	g2_norm(g2_tmp_add_XY, g2_tmp_add_XY);

	pc_map(gt_tmp_TXY, msg->T1, g2_tmp_add_XY); //r=e(s,a)

	gt_t gt_tmp_inv;

	gt_null(gt_tmp_inv);
	gt_new(gt_tmp_inv);

	gt_inv(gt_tmp_inv, gt_tmp_TXY);
	gt_mul(R2_, gt_tmp_add, gt_tmp_inv);

	//R2
	CHECK
	{
		printf("R2_ \n");
		g1_print(R2_);

		printf("msg->R2 \n");
		g1_print(msg->R2);
	}

	//if  C==C'
	// 后续完成
}

int batchMessageVerify(struct Car *car, int car_num, struct TA *ta)
{
	g1_t *R_0 = (struct g1_t *)malloc(sizeof(g1_t) * car_num);
	// init R_0
	for (int i = 0; i < car_num; i++)
	{
		g1_null(R_0[i]);
		g1_new(R_0[i]);
		g1_t g1_tmp_Tc, g1_tmp_Zsk;
		g1_null(g1_tmp_Tc);
		g1_null(g1_tmp_Zsk);

		g1_new(g1_tmp_Tc);
		g1_new(g1_tmp_Zsk);

		g1_mul(g1_tmp_Tc, car[i].msg.T0, car[i].msg.bn_c);
		g1_mul(g1_tmp_Zsk, ta->Z, car[i].msg.Sk);
		g1_sub(R_0[i], g1_tmp_Tc, g1_tmp_Zsk);
		g1_norm(R_0[i], R_0[i]);

		CHECK
		{
			printf("R_0[%d]\n", i);
			g1_print(R_0[i]);
			printf("R_0[%d]\n", i);
			g1_print(car[i].msg.R0);
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
			gt_exp(gt_tmp_total, car[i].msg.R2, eta[i]);
		}
		else
		{
			gt_t gt_tmp_Reta;
			gt_null(gt_tmp_Reta);
			gt_new(gt_tmp_Reta);
			gt_exp(gt_tmp_Reta, car[i].msg.R2, eta[i]);
			gt_mul(gt_tmp_total, gt_tmp_total, gt_tmp_Reta);
		}
	}
	// g1_norm(g1_tmp_total, g1_tmp_total);
	//
	// g1_print(g1_tmp_total);

	//
	g1_t g1_tmp_total_Tceta;
	g1_null(g1_tmp_total_Tceta);
	g1_new(g1_tmp_total_Tceta);
	for (int i = 0; i < car_num; i++)
	{
		if (i == 0)
		{
			bn_t bn_tmp_ceta;
			bn_null(bn_tmp_ceta);
			bn_new(bn_tmp_ceta);
			bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
			bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
			g1_mul(g1_tmp_total_Tceta, car[i].msg.T2, bn_tmp_ceta);
		}
		else
		{
			bn_t bn_tmp_ceta;
			bn_null(bn_tmp_ceta);
			bn_new(bn_tmp_ceta);
			bn_mul(bn_tmp_ceta, car[i].msg.bn_c, eta[i]);
			bn_mod(bn_tmp_ceta, bn_tmp_ceta, ta->n);
			g1_t g1_tmp_total_Tceta_;
			g1_null(g1_tmp_total_Tceta_);
			g1_new(g1_tmp_total_Tceta_);
			g1_mul(g1_tmp_total_Tceta_, car[i].msg.T2, bn_tmp_ceta);
			g1_add(g1_tmp_total_Tceta, g1_tmp_total_Tceta, g1_tmp_total_Tceta_);
		}
	}
	g1_norm(g1_tmp_total_Tceta, g1_tmp_total_Tceta);
	// e()
	gt_t gt_tmp_e_Tg2;
	gt_null(gt_tmp_e_Tg2);
	gt_new(gt_tmp_e_Tg2);
	pc_map(gt_tmp_e_Tg2, g1_tmp_total_Tceta, ta->g2);

	//
	bn_t bn_tmp_total_sketa;
	bn_null(bn_tmp_total_sketa);
	bn_new(bn_tmp_total_sketa);
	for (int i = 0; i < car_num; i++)
	{
		if (i == 0)
		{
			bn_mul(bn_tmp_total_sketa, car[i].msg.Sk, eta[i]);
			bn_mod(bn_tmp_total_sketa, bn_tmp_total_sketa, ta->n);
		}
		else
		{
			bn_t bn_tmp_total_sketa_;
			bn_null(bn_tmp_total_sketa_);
			bn_new(bn_tmp_total_sketa_);
			bn_mul(bn_tmp_total_sketa_, car[i].msg.Sk, eta[i]);
			bn_mod(bn_tmp_total_sketa_, bn_tmp_total_sketa_, ta->n);
			bn_add(bn_tmp_total_sketa, bn_tmp_total_sketa, bn_tmp_total_sketa_);
			bn_mod(bn_tmp_total_sketa, bn_tmp_total_sketa, ta->n);
		}
	}

	//
	gt_t gt_tmp_thetax_total;
	gt_null(gt_tmp_thetax_total);
	gt_new(gt_tmp_thetax_total);
	gt_exp(gt_tmp_thetax_total, ta->thetax, bn_tmp_total_sketa);

	// e(*)*thetax
	gt_t gt_tmp_e_thetax;
	gt_null(gt_tmp_e_thetax);
	gt_new(gt_tmp_e_thetax);
	gt_mul(gt_tmp_e_thetax, gt_tmp_e_Tg2, gt_tmp_thetax_total);

	g1_t g1_tmp_Tceta;
	g1_null(g1_tmp_Tceta);
	g1_new(g1_tmp_Tceta);
	for (int i = 0; i < car_num; i++)
	{
		if (i == 0)
		{
			bn_t bt_tmp_ceta;
			bn_null(bt_tmp_ceta);
			bn_new(bt_tmp_ceta);
			bn_mul(bt_tmp_ceta, car[i].msg.bn_c, eta[i]);
			bn_mod(bt_tmp_ceta, bt_tmp_ceta, ta->n);
			g1_mul(g1_tmp_Tceta, car[i].msg.T1, bt_tmp_ceta);
		}
		else
		{
			bn_t bt_tmp_ceta;
			bn_null(bt_tmp_ceta);
			bn_new(bt_tmp_ceta);
			bn_mul(bt_tmp_ceta, car[i].msg.bn_c, eta[i]);
			bn_mod(bt_tmp_ceta, bt_tmp_ceta, ta->n);
			g1_t g1_tmp_Tceta_;
			g1_null(g1_tmp_Tceta_);
			g1_new(g1_tmp_Tceta_);
			g1_mul(g1_tmp_Tceta_, car[i].msg.T1, bt_tmp_ceta);
			g1_add(g1_tmp_Tceta, g1_tmp_Tceta, g1_tmp_Tceta_);
		}
	}

	g1_norm(g1_tmp_Tceta, g1_tmp_Tceta);

	//e
	gt_t gt_tmp_tcetaX;
	gt_null(gt_tmp_tcetaX);
	gt_new(gt_tmp_tcetaX);
	pc_map(gt_tmp_tcetaX, g1_tmp_Tceta, ta->_X);

	//
	g1_t g1_tmp_T1Saeta;
	g1_null(g1_tmp_T1Saeta);
	g1_new(g1_tmp_T1Saeta);

	for (int i = 0; i < car_num; i++)
	{
		if (i == 0)
		{
			bn_t bn_tmp_seta;
			bn_null(bn_tmp_seta);
			bn_new(bn_tmp_seta);
			bn_mul(bn_tmp_seta, car[i].msg.Sa, eta[i]);
			bn_mod(bn_tmp_seta, bn_tmp_seta, ta->n);
			g1_mul(g1_tmp_T1Saeta, car[i].msg.T1, bn_tmp_seta);
		}
		else
		{
			bn_t bn_tmp_seta;
			bn_null(bn_tmp_seta);
			bn_new(bn_tmp_seta);
			bn_mul(bn_tmp_seta, car[i].msg.Sa, eta[i]);
			bn_mod(bn_tmp_seta, bn_tmp_seta, ta->n);
			g1_t g1_tmp_T1Saeta_;
			g1_null(g1_tmp_T1Saeta_);
			g1_new(g1_tmp_T1Saeta_);
			g1_mul(g1_tmp_T1Saeta_, car[i].msg.T1, bn_tmp_seta);
			g1_add(g1_tmp_T1Saeta, g1_tmp_T1Saeta, g1_tmp_T1Saeta_);
		}
	}
	g1_norm(g1_tmp_T1Saeta, g1_tmp_T1Saeta);

	//
	gt_t gt_tmp_TsaetaY;
	gt_null(gt_tmp_TsaetaY);
	gt_new(gt_tmp_TsaetaY);
	pc_map(gt_tmp_TsaetaY, g1_tmp_T1Saeta, ta->_Y);

	//
	gt_t gt_tmp_e_e;
	gt_null(gt_tmp_e_e);
	gt_new(gt_tmp_e_e);
	gt_mul(gt_tmp_e_e, gt_tmp_tcetaX, gt_tmp_TsaetaY);

	//
	gt_t gt_tmp_inv_ee;
	gt_null(gt_tmp_inv_ee);
	gt_new(gt_tmp_inv_ee);
	gt_inv(gt_tmp_inv_ee, gt_tmp_e_e);

	gt_t gt_tmp_ethetax_inv_ee;
	gt_null(gt_tmp_ethetax_inv_ee);
	gt_new(gt_tmp_ethetax_inv_ee);
	gt_mul(gt_tmp_ethetax_inv_ee, gt_tmp_e_thetax, gt_tmp_inv_ee);

	CHECK
	{
		printf("Left\n");
		gt_print(gt_tmp_total);
		printf("Right\n");
		gt_print(gt_tmp_ethetax_inv_ee);
	}

	// if (gt_cmp(gt_tmp_total, gt_tmp_ethetax_inv_ee) == RLC_EQ)
	// {
	// 	printf("Success\n");
	// }
	// else
	// {
	// 	printf("Failed\n");
	// }
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
		MapToPoint();
		BNmutip();
		// init();

		// struct TA ta;
		// initTA(&ta);

		// struct Car car1;
		// initCar(&car1, &ta);
		// setMsgInit(&car1.msg, &car1, &ta);

		// test(&ta);
		// MessageVerify(&car1.msg,&ta);

		// int car_num[8] = {10, 50, 100, 200, 300, 400, 500, 1000 } ;
		// for (int index = 0; index < 8; index++)
		// {
		// 	struct Car *car = (struct Car *)malloc(sizeof(struct Car) * car_num[index]);
		// 	for (int i = 0; i < car_num[index]; i++)
		// 	{
		// 		initCar(&car[i], &ta);
		// 		setMsgInit(&car[i].msg, &car[i], &ta);
		// 		// bn_print(car[i].msg.bn_c);
		// 	}

		// 	clock_t start, stop;
		// 	double duration;
		// 	start = clock();

		// 	batchMessageVerify(car, car_num[index], &ta);
		// 	stop = clock();
		// 	duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
		// 	printf("%d car batchMessageVerify cost time :%lf, per %f\n", car_num[index], duration,duration/car_num[index]);
		// }
	}

	core_clean();
	return 0;
}
