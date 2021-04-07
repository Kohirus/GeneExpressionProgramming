#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include "Gene.h"

/* ������(Ⱦɫ����) */
class Individual
{
public:
	Individual();
	Individual(const Individual& obj);
	Individual& operator= (const Individual& obj);
	~Individual();

	/** ��ʼ��Ⱦɫ�� */
	void initialize();

	/** ����ͻ�� */
	void mutation();

	/** ISת�� */
	void transposition_is();

	/** RISת�� */
	void transposition_ris();

	/** ����ת�� */
	void transposition_gene();

	/** ��ȡ��������(���ո�) */
	string content() const;

	/**
	 * ����Ⱦɫ��Ƭ�Ρ��ı�����ʼλ�����len�����ȵ��ַ���Ϊstr
	 * @param pos: ��ʼλ��
	 * @param len: ����
	 * @param str: �µ��ַ���
	 */
	void recombination(const int pos, const int length, const string& str);

	static int length() { return len; }

	/** ��ȡ��������(�����ո�) */
	string content_without_space() const;

	/** ��������� */
	static void setDependentVar(vector<double>& dependent) { dependentVar = dependent; }

	/** ��ȡģ�������� */
	double getFitnessError() const { return error; }

	/** ���¼���ģ�͵������� */
	void recalculate();

	/** �޸Ļ������� */
	void modifyContent(string content);

	/** �����׺���ʽ */
	string infixExpression() const;

	/** ��ȡ����Dc�����׺���ʽ */
	string infixExpressionWithDc();

private:
	/** ���ѡ��һ������ */
	inline int index_rand();

	/** ���������ֵ */
	void calculate();

	/** ������Ӧ����� */
	void fitError();

private:
	// ����ָ��
	Gene* gene;
	// Ⱦɫ�峤��
	static int len;
	// ������ֵ
	vector<double> result;
	// �����
	static vector<double> dependentVar;
	// ������
	double error;
};

#endif

