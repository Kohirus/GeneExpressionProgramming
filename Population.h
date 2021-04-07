#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "Individual.h"
#include "paramsettings.h"

/* 种群类 */
class Population
{
public:
	Population(const int num = INDIV_NUM);
	Population(const Population& obj);
	Population& operator= (const Population& obj);
	Population operator+ (const Population& obj);
	~Population();

	/** 初始化种群 */
	void initialize();

	/** 输出种群基因内容 */
	void context() const;

	/** 种群进化 */
	void evolution();

	/** 修改基因内容 */
	void modifyGeneContent(vector<string>& text);

	/*
	 * @brief: 保存最优秀个体
	 * @param maxValue: 迭代过程中适应度最大值
	 * @param index: 当前代中适应度最大的个体索引
	 * @param content: 当前代中适应度最大的个体基因
	 * @param contentWithDc: 当前代中适应度最大的个体中缀表达式
	 * @return: 是否存在比传入的maxValue更大的个体
	 **/
	bool excellentIndiv(double& maxValue, int& index, string& content,string& contentWithDc);

private:
	/** 基因突变 */
	void mutation();

	/** IS转座 */
	void transposition_is();

	/** RIS转座 */
	void transposition_ris();

	/** 基因转座 */
	void transposition_gene();

	/** 单点重组 */
	void recombination_one();

	/** 两点重组 */
	void recombination_two();

	/** 基因重组 */
	void recombination_gene();

private:
	/** 个体 */
	Individual* individual;
	/** 个体数量 */
	int count;
};

#endif