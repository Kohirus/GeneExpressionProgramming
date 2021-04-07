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
		// ���ѡȡ������ͬ����
		int index1 = 0;
		int index2 = 0;
		while (index1 == index2)
		{
			index1 = rand() % count;
			index2 = rand() % count;
		}
		// ���ѡȡ�����
		int pos = rand() % Individual::length();
		string subStr1 = individual[index1].content_without_space().substr(0, pos);
		string subStr2 = individual[index2].content_without_space().substr(0, pos);
		// ��������Ⱦɫ���Ƭ��
		individual[index1].recombination(0, pos, subStr2);
		individual[index2].recombination(0, pos, subStr1);
	}
}

void Population::recombination_two()
{
	double prob = rand() / double(RAND_MAX);
	if (prob < PROB_RECOMBE_TWO)
	{
		// ���ѡȡ������ͬ����
		int index1 = 0;
		int index2 = 0;
		while (index1 == index2)
		{
			index1 = rand() % count;
			index2 = rand() % count;
		}
		// ���ѡȡ��������� 
		int pos_left = rand() % Individual::length();
		int pos_right = (rand() % (Individual::length() - pos_left)) + pos_left;
		int len = pos_right - pos_left + 1;	// �����֮��ľ���
		// �����֮����ַ������������������
		string subStr1 = individual[index1].content_without_space().substr(pos_left, len);
		string subStr2 = individual[index2].content_without_space().substr(pos_left, len);
		// ��������Ⱦɫ���Ƭ��
		individual[index1].recombination(pos_left, len, subStr2);
		individual[index2].recombination(pos_left, len, subStr1);
	}
}

void Population::recombination_gene()
{
	double prob = rand() / double(RAND_MAX);
	if (prob < PROB_RECOMBE_GENE)
	{
		// ���ѡȡ������ͬ����
		int index1 = 0;
		int index2 = 0;
		while (index1 == index2)
		{
			index1 = rand() % count;
			index2 = rand() % count;
		}
		// ���ѡȡ�������� 
		int index = rand() % GENE_NUM;
		// ��ȡ����������Ӧ�����Ļ���
		string subStr1 = individual[index1].content_without_space().substr(index * Gene::length(), Gene::length());
		string subStr2 = individual[index2].content_without_space().substr(index * Gene::length(), Gene::length());
		// ����
		individual[index1].recombination(index * Gene::length(), Gene::length(), subStr2);
		individual[index2].recombination(index * Gene::length(), Gene::length(), subStr1);
	}
}

void Population::evolution()
{
	// �����̶��㷨ѡ���������
	// ����ÿ��������������ռ���ĸ��ʴ�С
	double allFitness = 0.0;	// �ܵ���Ӧ��
	vector<double> probFitness;
	// ������Ӧ�ȵĺ�
	for (int i = 0; i < INDIV_NUM; i++)
	{
		allFitness += individual[i].getFitnessError();
	}
	// ����ÿ����Ӧ��ռ����Ӧ�ȵĸ���
	for (int i = 0; i < INDIV_NUM; i++)
	{
		probFitness.push_back(individual[i].getFitnessError() / allFitness);
	}
	// ��ֵΪ������ ��ֵΪ������
	vector<pair<double,double> > section;
	// ������չ��Ϊ����Ϊ1���߶� ����ÿ��������ռ����
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
		// ����0~1����������
		double prob = rand() / double(RAND_MAX);
		for (int j = 0; j < INDIV_NUM; j++)
		{
			// ������ڸ������� �����ø���
			if (prob >= section[j].first && prob <= section[j].second)
			{
				context.push_back(individual[j].content_without_space());
				break;
			}
		}
	}	

	// �޸ĵ�ǰ����
	for (int i = 0; i < count; i++)
	{
		individual[i].modifyContent(context[i]);
	}
	this->mutation();			// ����
	this->transposition_is();	// ISת��	
	this->transposition_ris();	// RISת��
	this->transposition_gene();	// ����ת��
	this->recombination_one();	// ��������
	this->recombination_two();	// ��������
	this->recombination_gene();	// ��������
	// ���¼������˶�
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
	// ��Ѱ���˶���ߵĸ���
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
