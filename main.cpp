#include "paramsettings.h"
#include <ctime>
#include "Population.h"
#include "FileController.h"
#include "Gene.h"

using namespace std;

/* 迭代过程中最优秀个体 */
int num_generaton = 0;	// 代数
int num_index = 0;		// 个体索引
string excellGene = "";	// 基因
string excellInfix = "";	// 中缀表达式
double maxFitness = 0.0;	// 最大适宜度

void clearOutputFile();

int main()
{
	/* =======================设置训练样本====================== */
	clearOutputFile();
	srand((int)time(0));
	// 读取训练样本以及预测样本
	FileController file;
	// 设置自变量
	Gene::setData(file.independent());
	// 设置因变量
	Individual::setDependentVar(file.dependent());

	/* =======================设置Dc域====================== */
	Gene::initDc();
	
	/* =======================迭代开始====================== */
	Population parent;
	// 初始化种群
	parent.initialize();

	for (int i = 0; i < GENERATION - 1; i++)
	{
		if (parent.excellentIndiv(maxFitness, num_index, excellGene, excellInfix))
			num_generaton = i + 1;
		
		cout << "------------------------第" << i+1 << "代------------------------" << endl;
		cout << endl;
		parent.context();
		cout << endl;
		parent.evolution();
	}
	cout << "------------------------第" << GENERATION << "代------------------------" << endl;
	parent.context();
	if (parent.excellentIndiv(maxFitness, num_index, excellGene, excellInfix))
		num_generaton = 1000;
	cout << endl;
	cout << endl << "迭代完成..." << endl;
	cout << "当前代最优秀个体基因如下: " << endl;
	cout << "第" << num_generaton << "代的第" << num_index << "个个体：" << endl;
	cout << "基因：" << excellGene << endl;
	cout << "中缀表达式: " << excellInfix << endl;

	Gene::destroyDc();

	return 0;
}

void clearOutputFile()
{
	fstream result_child("output/result_child.txt", ios::out);
	result_child.close();
	fstream result_parent("output/result_parent.txt", ios::out);
	result_parent.close();
	fstream gene_child("output/gene_child.txt", ios::out);
	gene_child.close();
}
