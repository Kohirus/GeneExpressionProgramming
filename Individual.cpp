#include "Individual.h"
#include "paramsettings.h"

int Individual::len = 45;
vector<double> Individual::dependentVar = {};

Individual::Individual()
	: gene(nullptr)
	, error(0.0)
{
	gene = new Gene[GENE_NUM];
	// 计算染色体长度
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
	// 计算表达式数值
	calculate();
	// 计算拟合误差
	fitError();
}

void Individual::mutation()
{
	// 随机选择基因
	int index = index_rand();
	gene[index].mutation();
}

void Individual::transposition_is()
{
	// 随机选取转座长度
	int len_array = sizeof(IS_LEN) / sizeof(int);
	int index = rand() % len_array;
	int len_is = IS_LEN[index];
	// 从整段染色体中随机选取len_is个长度的片段
	index = rand() % (len - len_is);	// 随机起始索引
	string str = content_without_space().substr(index, len_is);	// 截取字符串
	// 随机选择基因
	index = index_rand();
	gene[index].transposition(str);
}

void Individual::transposition_ris()
{
	// 随机选择基因
	int index = index_rand();
	// 在头中随机选取一点
	int pos = rand() % HEAD_LEN;
	// 沿该点向后查找直到发现一个函数 该点即为RIS转座的起始点
	int a;
	if ((a = gene[index].find_func(pos)) == -1)
		return;
	pos = a + Gene::length() * index;
	// 随机选取RIS转座长度
	int len_array = sizeof(RIS_LEN) / sizeof(int);
	index = rand() % len_array;
	int len_ris = RIS_LEN[index];
	// 从起始点向后取len_ris个长度的片段
	string str = content_without_space().substr(pos, len_ris);
	index = index_rand();
	gene[index].transposition(str);
}

void Individual::transposition_gene()
{
	// 随机选取两个不同位置的基因
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
	str = str + " — [" + std::to_string(error) + "]";
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
	// 计算表达式数值
	calculate();
	// 计算拟合误差
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
			// 采用绝对误差：选择范围 - |适应度值 - 目标值|
			temp = RANGE - abs(result[i] - dependentVar[i]);
		}
		else
		{
			// 采用相对误差：选择范围 - |（适应度值 - 目标值）/ 目标值 * 100|
			temp = RANGE - abs(100 * (result[i] - dependentVar[i]) / dependentVar[i]);
		}
		if (temp <= 0)
			temp = 0.1;	// 方便轮盘赌计算
		error += temp;
	}
}
