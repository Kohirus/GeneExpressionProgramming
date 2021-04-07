#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include "Gene.h"

/* 个体类(染色体类) */
class Individual
{
public:
	Individual();
	Individual(const Individual& obj);
	Individual& operator= (const Individual& obj);
	~Individual();

	/** 初始化染色体 */
	void initialize();

	/** 基因突变 */
	void mutation();

	/** IS转座 */
	void transposition_is();

	/** RIS转座 */
	void transposition_ris();

	/** 基因转座 */
	void transposition_gene();

	/** 获取基因内容(含空格) */
	string content() const;

	/**
	 * 重组染色体片段。改变以起始位置向后len个长度的字符串为str
	 * @param pos: 起始位置
	 * @param len: 长度
	 * @param str: 新的字符串
	 */
	void recombination(const int pos, const int length, const string& str);

	static int length() { return len; }

	/** 获取基因内容(不含空格) */
	string content_without_space() const;

	/** 设置因变量 */
	static void setDependentVar(vector<double>& dependent) { dependentVar = dependent; }

	/** 获取模型拟合误差 */
	double getFitnessError() const { return error; }

	/** 重新计算模型的拟合误差 */
	void recalculate();

	/** 修改基因内容 */
	void modifyContent(string content);

	/** 获得中缀表达式 */
	string infixExpression() const;

	/** 获取代入Dc域的中缀表达式 */
	string infixExpressionWithDc();

private:
	/** 随机选择一个基因 */
	inline int index_rand();

	/** 计算个体数值 */
	void calculate();

	/** 计算适应度误差 */
	void fitError();

private:
	// 基因指针
	Gene* gene;
	// 染色体长度
	static int len;
	// 个体数值
	vector<double> result;
	// 因变量
	static vector<double> dependentVar;
	// 拟合误差
	double error;
};

#endif

