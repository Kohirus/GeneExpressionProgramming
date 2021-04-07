#include "paramsettings.h"
#include <ctime>
#include "Population.h"
#include "FileController.h"
#include "Gene.h"

using namespace std;

/* ������������������� */
int num_generaton = 0;	// ����
int num_index = 0;		// ��������
string excellGene = "";	// ����
string excellInfix = "";	// ��׺���ʽ
double maxFitness = 0.0;	// ������˶�

void clearOutputFile();

int main()
{
	/* =======================����ѵ������====================== */
	clearOutputFile();
	srand((int)time(0));
	// ��ȡѵ�������Լ�Ԥ������
	FileController file;
	// �����Ա���
	Gene::setData(file.independent());
	// ���������
	Individual::setDependentVar(file.dependent());

	/* =======================����Dc��====================== */
	Gene::initDc();
	
	/* =======================������ʼ====================== */
	Population parent;
	// ��ʼ����Ⱥ
	parent.initialize();

	for (int i = 0; i < GENERATION - 1; i++)
	{
		if (parent.excellentIndiv(maxFitness, num_index, excellGene, excellInfix))
			num_generaton = i + 1;
		
		cout << "------------------------��" << i+1 << "��------------------------" << endl;
		cout << endl;
		parent.context();
		cout << endl;
		parent.evolution();
	}
	cout << "------------------------��" << GENERATION << "��------------------------" << endl;
	parent.context();
	if (parent.excellentIndiv(maxFitness, num_index, excellGene, excellInfix))
		num_generaton = 1000;
	cout << endl;
	cout << endl << "�������..." << endl;
	cout << "��ǰ������������������: " << endl;
	cout << "��" << num_generaton << "���ĵ�" << num_index << "�����壺" << endl;
	cout << "����" << excellGene << endl;
	cout << "��׺���ʽ: " << excellInfix << endl;

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
