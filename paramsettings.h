#ifndef _PARAMSETTINGS_H_
#define _PARAMSETTINGS_H_

#include <iostream>
using namespace std;

/* 参数配置头文件 */

/* --------------------适应度配置--------------------- */
/* 默认采用绝对误差，flase即为相对误差 */
const bool AbsoluteError = true;
/* 选择范围 */
const double RANGE = 100.0;

/* --------------------基因配置----------------------- */
/* 函数集 */
// 可选函数集: +、-、*、/、S(sin)、C(cos)、T(tan)、E(exp)、L(log10)、Q(sqrt)
const char FUNC[] = { '+','-','*','/' };
/* 终点集 */
const char TERM[] = { 'a' };
/* 头部长度 */
const int HEAD_LEN = 7;
/* 是否开启Dc域 */
const bool IS_OPEN_DC = true;
/* Dc域最大值 */
const double DC_MAX_VALUE = 10.0;
/* Dc域最小值 */
const double DC_MIN_VALUE = 0.0;
/* Dc域元素个数 */
const int DC_LEN = 10;

/* -------------------染色体配置---------------------- */
/* 基因数目 */
const int GENE_NUM = 3;
/* 基因连接符 */
// 可选基因连接符: +、-、*、/
const char CONN = '+';

/* --------------------种群配置----------------------- */
/* 种群大小(应为偶数) */
const int INDIV_NUM = 20;
/* 繁衍代数 */
const int GENERATION = 1000;

/* --------------------概率设定----------------------- */
/* 变异概率 */
const double PROB_MUTATION = 1;
/* IS转座率 */
const double PROB_IS_TRANS = 1;
/* IS元素长度 */
const int IS_LEN[] = { 1,2,3 };
/* RIS转座率 */
const double PROB_RIS_TRANS = 1;
/* RIS元素长度 */
const int RIS_LEN[] = { 1,2,3 };
/* 基因转座率 */
const double PROB_GENE_TRANS = 1;
/* 单点重组 */
const double PROB_RECOMBE_ONE = 1;
/* 两点重组 */
const double PROB_RECOMBE_TWO = 1;
/* 基因重组 */
const double PROB_RECOMBE_GENE = 1;

/* --------------------文件路径----------------------- */
/* 自变量存储文件 */
const string PATH_INPUT = "data/input.txt";
/* 因变量存储文件 */
const string PATH_OUTPUT = "data/output.txt";
#endif // _PARAMSETTINGS_H_
