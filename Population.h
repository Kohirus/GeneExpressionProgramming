#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "Individual.h"
#include "paramsettings.h"

/* ��Ⱥ�� */
class Population
{
public:
	Population(const int num = INDIV_NUM);
	Population(const Population& obj);
	Population& operator= (const Population& obj);
	Population operator+ (const Population& obj);
	~Population();

	/** ��ʼ����Ⱥ */
	void initialize();

	/** �����Ⱥ�������� */
	void context() const;

	/** ��Ⱥ���� */
	void evolution();

	/** �޸Ļ������� */
	void modifyGeneContent(vector<string>& text);

	/*
	 * @brief: �������������
	 * @param maxValue: ������������Ӧ�����ֵ
	 * @param index: ��ǰ������Ӧ�����ĸ�������
	 * @param content: ��ǰ������Ӧ�����ĸ������
	 * @param contentWithDc: ��ǰ������Ӧ�����ĸ�����׺���ʽ
	 * @return: �Ƿ���ڱȴ����maxValue����ĸ���
	 **/
	bool excellentIndiv(double& maxValue, int& index, string& content,string& contentWithDc);

private:
	/** ����ͻ�� */
	void mutation();

	/** ISת�� */
	void transposition_is();

	/** RISת�� */
	void transposition_ris();

	/** ����ת�� */
	void transposition_gene();

	/** �������� */
	void recombination_one();

	/** �������� */
	void recombination_two();

	/** �������� */
	void recombination_gene();

private:
	/** ���� */
	Individual* individual;
	/** �������� */
	int count;
};

#endif