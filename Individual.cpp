#include "Individual.h"
#include "paramsettings.h"

int Individual::len = 45;
vector<double> Individual::dependentVar = {};

Individual::Individual()
	: gene(nullptr)
	, error(0.0)
{
	gene = new Gene[GENE_NUM];
	// ����Ⱦɫ�峤��
	len = GENE_NUM * Gene::length();
}

Individual::Individual(const Individual& obj)
	: gene(new Gene[GENE_NUM])
	, result(obj.result)
	, error(obj.error)
{
	for (int i = 0; i < GENE_NUM; i++)
	{
		*(gene + i) = *(obj.gene + i);
	}
}

Individual& Individual::operator=(const Individual& obj)
{
	if (this != &obj)
	{
		if (gene != NULL)
			delete[] gene;
		this->gene = new Gene[GENE_NUM];
		for (int i = 0; i < GENE_NUM; i++)
		{
			*(gene + i) = *(obj.gene + i);
		}
		result = obj.result;
		error = obj.error;
	}
	return *this;
}

Individual::~Individual()
{
	if (!gene)
	{
		delete[] gene;
	}
}

void Individual::initialize()
{
	for (int i = 0; i < GENE_NUM; i++)
	{
		gene[i].initialize();
	}
	// ������ʽ��ֵ
	calculate();
	// ����������
	fitError();
}

void Individual::mutation()
{
	// ���ѡ�����
	int index = index_rand();
	gene[index].mutation();
}

void Individual::transposition_is()
{
	// ���ѡȡת������
	int len_array = sizeof(IS_LEN) / sizeof(int);
	int index = rand() % len_array;
	int len_is = IS_LEN[index];
	// ������Ⱦɫ�������ѡȡlen_is�����ȵ�Ƭ��
	index = rand() % (len - len_is);	// �����ʼ����
	string str = content_without_space().substr(index, len_is);	// ��ȡ�ַ���
	// ���ѡ�����
	index = index_rand();
	gene[index].transposition(str);
}

void Individual::transposition_ris()
{
	// ���ѡ�����
	int index = index_rand();
	// ��ͷ�����ѡȡһ��
	int pos = rand() % HEAD_LEN;
	// �ظõ�������ֱ������һ������ �õ㼴ΪRISת������ʼ��
	int a;
	if ((a = gene[index].find_func(pos)) == -1)
		return;
	pos = a + Gene::length() * index;
	// ���ѡȡRISת������
	int len_array = sizeof(RIS_LEN) / sizeof(int);
	index = rand() % len_array;
	int len_ris = RIS_LEN[index];
	// ����ʼ�����ȡlen_ris�����ȵ�Ƭ��
	string str = content_without_space().substr(pos, len_ris);
	index = index_rand();
	gene[index].transposition(str);
}

void Individual::transposition_gene()
{
	// ���ѡȡ������ͬλ�õĻ���
	if (GENE_NUM > 1)
	{
		int index1 = 0;
		int index2 = 0;
		while (index1 == index2)
		{
			index1 = index_rand();
			index2 = index_rand();
		}
		Gene temp(gene[index1]);
		gene[index1] = gene[index2];
		gene[index2] = temp;
	}
}

std::string Individual::content() const
{
	string str;
	for (int i = 0; i < GENE_NUM; i++)
	{
		str = str + gene[i].content() + " ";
	}
	str = str + " �� [" + std::to_string(error) + "]";
	return str;
}

void Individual::recombination(const int pos, const int length, const string& str)
{
	string text = content_without_space();
	text.replace(pos, length, str);
	for (int i = 0; i < GENE_NUM; i++)
	{
		Gene temp(text.substr(i * Gene::length(), Gene::length()));
		gene[i] = temp;
	}
}

string Individual::content_without_space() const
{
	string str;
	for (int i = 0; i < GENE_NUM; i++)
	{
		str = str + gene[i].content();
	}
	return str;
}

void Individual::recalculate()
{
	for (int i = 0; i < GENE_NUM; i++)
	{
		gene[i].update();
	}
	
	result.clear();
	error = 0.0;
	// ������ʽ��ֵ
	calculate();
	// ����������
	fitError();
}

void Individual::modifyContent(string content)
{
	string text[GENE_NUM];
	for (int i = 0; i < GENE_NUM; i++)
	{
		text[i] = content.substr(i * Gene::length(), Gene::length());
		gene[i].setContent(text[i]);
	}
}

std::string Individual::infixExpression() const
{
	string expression = "";
	for (int i = 0; i < GENE_NUM; i++)
	{
		if (i < GENE_NUM - 1)
			expression = expression + gene[i].decode() + "+";
		else
			expression = expression + gene[i].decode();
	}
	return expression;
}

std::string Individual::infixExpressionWithDc()
{
	string expression = "";
	for (int i = 0; i < GENE_NUM; i++)
	{
		if (i < GENE_NUM - 1)
			expression = expression + gene[i].decodeWithDc() + "+";
		else
			expression = expression + gene[i].decodeWithDc();
	}
	return expression;
}

int Individual::index_rand()
{
	return rand() % GENE_NUM;
}

void Individual::calculate()
{
	vector<vector<double>> param = {};
	for (int i = 0; i < GENE_NUM; i++)
	{
		param.push_back(gene[i].expressionValue());
	}

	int len = Gene::sampleCount();
	for (int i = 0; i < len; ++i)
	{
		double value = 0.0;
		double a = 0.0;
		for (int j = 0; j < GENE_NUM; j++)
		{
			switch (CONN)
			{
			case '+':
				value += param[j].at(i);
				break;
			case '-':
				value -= param[j].at(i);
				break;
			case '*':
				value *= param[j].at(i);
				break;
			case '/':
				value /= param[j].at(i);
				if (isnan(value) || isinf(value))
					value = 0.0;
				break;
			default:
				break;
			}
		}
		result.push_back(value);
	}
}

void Individual::fitError()
{
	int num = Gene::sampleCount();
	for (int i = 0; i < num; i++)
	{
		double temp = 0.0;
		if (AbsoluteError)
		{
			// ���þ�����ѡ��Χ - |��Ӧ��ֵ - Ŀ��ֵ|
			temp = RANGE - abs(result[i] - dependentVar[i]);
		}
		else
		{
			// ���������ѡ��Χ - |����Ӧ��ֵ - Ŀ��ֵ��/ Ŀ��ֵ * 100|
			temp = RANGE - abs(100 * (result[i] - dependentVar[i]) / dependentVar[i]);
		}
		if (temp <= 0)
			temp = 0.1;	// �������̶ļ���
		error += temp;
	}
}
