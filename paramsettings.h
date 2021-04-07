#ifndef _PARAMSETTINGS_H_
#define _PARAMSETTINGS_H_

#include <iostream>
using namespace std;

/* ��������ͷ�ļ� */

/* --------------------��Ӧ������--------------------- */
/* Ĭ�ϲ��þ�����flase��Ϊ������ */
const bool AbsoluteError = true;
/* ѡ��Χ */
const double RANGE = 100.0;

/* --------------------��������----------------------- */
/* ������ */
// ��ѡ������: +��-��*��/��S(sin)��C(cos)��T(tan)��E(exp)��L(log10)��Q(sqrt)
const char FUNC[] = { '+','-','*','/' };
/* �յ㼯 */
const char TERM[] = { 'a' };
/* ͷ������ */
const int HEAD_LEN = 7;
/* �Ƿ���Dc�� */
const bool IS_OPEN_DC = true;
/* Dc�����ֵ */
const double DC_MAX_VALUE = 10.0;
/* Dc����Сֵ */
const double DC_MIN_VALUE = 0.0;
/* Dc��Ԫ�ظ��� */
const int DC_LEN = 10;

/* -------------------Ⱦɫ������---------------------- */
/* ������Ŀ */
const int GENE_NUM = 3;
/* �������ӷ� */
// ��ѡ�������ӷ�: +��-��*��/
const char CONN = '+';

/* --------------------��Ⱥ����----------------------- */
/* ��Ⱥ��С(ӦΪż��) */
const int INDIV_NUM = 20;
/* ���ܴ��� */
const int GENERATION = 1000;

/* --------------------�����趨----------------------- */
/* ������� */
const double PROB_MUTATION = 1;
/* ISת���� */
const double PROB_IS_TRANS = 1;
/* ISԪ�س��� */
const int IS_LEN[] = { 1,2,3 };
/* RISת���� */
const double PROB_RIS_TRANS = 1;
/* RISԪ�س��� */
const int RIS_LEN[] = { 1,2,3 };
/* ����ת���� */
const double PROB_GENE_TRANS = 1;
/* �������� */
const double PROB_RECOMBE_ONE = 1;
/* �������� */
const double PROB_RECOMBE_TWO = 1;
/* �������� */
const double PROB_RECOMBE_GENE = 1;

/* --------------------�ļ�·��----------------------- */
/* �Ա����洢�ļ� */
const string PATH_INPUT = "data/input.txt";
/* ������洢�ļ� */
const string PATH_OUTPUT = "data/output.txt";
#endif // _PARAMSETTINGS_H_
