#include "Population.h"
#include "paramsettings.h"
#include "Gene.h"
#include <fstream>
#include <utility>
#include <algorithm>

Population::Population(const int num)
	: count(num)
{
	individual = new Individual[count];
}

Population::Population(const Population& obj)
	: count(obj.count)
{
	individual = new Individual[count];
	for (int i = 0; i < count; i++)
	{
		*(individual + i) = *(obj.individual + i);
	}
}

Population& Population::operator=(const Population& obj)
{
	if (this != &obj)
	{
		if (individual != NULL)
			delete[] individual;
		count = obj.count;
		individual = new Individual[count];
		for (int i = 0; i < count; i++)
		{
			*(individual + i) = *(obj.individual + i);
		}
	}
	return *this;
}

Population Population::operator+(const Population& obj)
{
	Population temp(this->count + obj.count);
	for (int i = 0; i < this->count; i++)
	{
		*(temp.individual + i) = *(this->individual + i);
	}
	for (int i = this->count; i < this->count + obj.count; i++)
	{
		*(temp.individual + i) = *(obj.individual + i - this->count);
	}
	return temp;
}

Population::~Population()
{
	if (!individual)
		delete[] individual;
}

void Population::initialize()
{
	for (int i = 0; i < count; i++)
	{
		individual[i].initialize();
	}
}

void Population::context() const
{
	for (int i = 0; i < count; ++i)
	{
		cout << "[" << i + 1 << "] " << individual[i].content() << endl;
	}
}

void Population::mutation()
{
	for (int i = 0; i < count; i++)
	{
		double prob = rand() / double(RAND_MAX);
		if (prob < PROB_MUTATION)
		{
			individual[i].mutation();
		}
	}
}

void Population::transposition_is()
{
	for (int i = 0; i < count; i++)
	{
		double prob = rand() / double(RAND_MAX);
		if (prob < PROB_IS_TRANS)
		{
			individual[i].transposition_is();
		}
	}
}

void Population::transposition_ris()
{
	for (int i = 0; i < count; i++)
	{
		double prob = rand() / double(RAND_MAX);
		if (prob < PROB_IS_TRANS)
		{
			individual[i].transposition_ris();
		}
	}
}

void Population::transposition_gene()
{
	for (int i = 0; i < count; i++)
	{
		double prob = rand() / double(RAND_MAX);
		if (prob < PROB_GENE_TRANS)
		{
			individual[i].transposition_gene();
		}
	}
}

void Population::recombination_one()
{
	double prob = rand() / double(RAND_MAX);
	if (prob < PROB_RECOMBE_ONE)
	{
		// 随机选取两个不同个体
		int index1 = 0;
		int index2 = 0;
		while (index1 == index2)
		{
			index1 = rand() % count;
			index2 = rand() % count;
		}
		// 随机选取重组点
		int pos = rand() % Individual::length();
		string subStr1 = individual[index1].content_without_space().substr(0, pos);
		string subStr2 = individual[index2].content_without_space().substr(0, pos);
		// 交换两个染色体的片段
		individual[index1].recombination(0, pos, subStr2);
		individual[index2].recombination(0, pos, subStr1);
	}
}

void Population::recombination_two()
{
	double prob = rand() / double(RAND_MAX);
	if (prob < PROB_RECOMBE_TWO)
	{
		// 随机选取两个不同个体
		int index1 = 0;
		int index2 = 0;
		while (index1 == index2)
		{
			index1 = rand() % count;
			index2 = rand() % count;
		}
		// 随机选取左、右重组点 
		int pos_left = rand() % Individual::length();
		int pos_right = (rand() % (Individual::length() - pos_left)) + pos_left;
		int len = pos_right - pos_left + 1;	// 重组点之间的距离
		// 重组点之间的字符串，包括左、右重组点
		string subStr1 = individual[index1].content_without_space().substr(pos_left, len);
		string subStr2 = individual[index2].content_without_space().substr(pos_left, len);
		// 交换两个染色体的片段
		individual[index1].recombination(pos_left, len, subStr2);
		individual[index2].recombination(pos_left, len, subStr1);
	}
}

void Population::recombination_gene()
{
	double prob = rand() / double(RAND_MAX);
	if (prob < PROB_RECOMBE_GENE)
	{
		// 随机选取两个不同个体
		int index1 = 0;
		int index2 = 0;
		while (index1 == index2)
		{
			index1 = rand() % count;
			index2 = rand() % count;
		}
		// 随机选取基因索引 
		int index = rand() % GENE_NUM;
		// 获取两个个体相应索引的基因
		string subStr1 = individual[index1].content_without_space().substr(index * Gene::length(), Gene::length());
		string subStr2 = individual[index2].content_without_space().substr(index * Gene::length(), Gene::length());
		// 交换
		individual[index1].recombination(index * Gene::length(), Gene::length(), subStr2);
		individual[index2].recombination(index * Gene::length(), Gene::length(), subStr1);
	}
}

void Population::evolution()
{
	// 用轮盘赌算法选择优秀个体
	// 计算每个个体在轮盘中占到的概率大小
	double allFitness = 0.0;	// 总的适应度
	vector<double> probFitness;
	// 计算适应度的和
	for (int i = 0; i < INDIV_NUM; i++)
	{
		allFitness += individual[i].getFitnessError();
	}
	// 计算每个适应度占总适应度的概率
	for (int i = 0; i < INDIV_NUM; i++)
	{
		probFitness.push_back(individual[i].getFitnessError() / allFitness);
	}
	// 左值为左区间 右值为右区间
	vector<pair<double,double> > section;
	// 将概率展开为长度为1的线段 划分每个个体所占区间
	double temp = 0.0;
	for (int i = 0; i < INDIV_NUM - 1; i++)
	{
		section.push_back(pair<double, double>(temp, temp + probFitness[i]));
		if(i < INDIV_NUM -2)
			temp += probFitness[i];
	}
	section.push_back(pair<double, double>(temp, 1.0)); 
	vector<string> context = {};
	for (int i = 0; i < INDIV_NUM; i++)
	{
		// 生成0~1间的随机算子
		double prob = rand() / double(RAND_MAX);
		for (int j = 0; j < INDIV_NUM; j++)
		{
			// 如果落在该区间内 则加入该个体
			if (prob >= section[j].first && prob <= section[j].second)
			{
				context.push_back(individual[j].content_without_space());
				break;
			}
		}
	}	

	// 修改当前基因
	for (int i = 0; i < count; i++)
	{
		individual[i].modifyContent(context[i]);
	}
	this->mutation();			// 变异
	this->transposition_is();	// IS转座	
	this->transposition_ris();	// RIS转座
	this->transposition_gene();	// 基因转座
	this->recombination_one();	// 单点重组
	this->recombination_two();	// 两点重组
	this->recombination_gene();	// 基因重组
	// 重新计算适宜度
	for (int i = 0; i < count; i++)
	{
		individual[i].recalculate();
	}
}

void Population::modifyGeneContent(vector<string>& text)
{
	for (int i = 0; i < count; i++)
	{
		individual[i].modifyContent(text[i]);
	}
}

bool Population::excellentIndiv(double& maxValue, int& index, string& content, 
	string& contentWithDc)
{
	double temp = individual[0].getFitnessError();
	int idx = 0;
	// 找寻适宜度最高的个体
	for (int i = 1; i < INDIV_NUM; i++)
	{
		if (individual[i].getFitnessError() > temp)
		{
			temp = individual[i].getFitnessError();
			idx = i;
		}
	}

	if (temp > maxValue)
	{
		index = idx + 1;
		content = individual[idx].content();
		contentWithDc = individual[idx].infixExpressionWithDc();
		maxValue = individual[idx].getFitnessError();
		return true;
	}
	return false;
}
