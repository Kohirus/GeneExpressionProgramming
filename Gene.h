#ifndef _GENE_H_
#define _GENE_H_

#include <string>
#include <vector>
#include <queue>
#include <map>

class BinaryTree;

using namespace std;

/* ������ */
class Gene
{
public:
	Gene(const string& str = "");
	Gene(const Gene& obj);
	Gene& operator= (const Gene& obj);
	~Gene();

	/** ���ɳ�ʼ����Ƭ�� */
	void initialize();

	/** �������� */
	static void setData(const vector<vector<double>>& value);

	/** ��ȡ�������� */
	inline string content() { return text; }
	
	/** ��ȡ���򳤶� */
	static inline int length() { return gene_len; }

	/** ����ͻ�� */
	void mutation();

	/** 
	 * ISת����RISת��
	 * @param str: ת���Ļ�������
	 */
	void transposition(const string& str);

	/** ��pos��ʼ������,ֱ���ҵ�һ������λ��,���ظú��������� */
	int find_func(const int pos);
	
	/** ��ȡ���ʽ��ֵ */
	vector<double> expressionValue() { return result; }

	/** ��ȡѵ��������Ŀ */
	static int sampleCount() { return indenpentVar.size(); }

	/** ���¼������������� */
	void update();

	/** ���û������� */
	void setContent(const string& content) { text = content; }

	/** ����������� */
	string decode();

	/** ����������������Ұ���Dc��ľ�����ֵ */
	string decodeWithDc();

	/** ��ʼ��Dc�� */
	static void initDc();

	/** ����Dc�� */
	static void destroyDc();

private:	
	/** �ж�Ԫ��������� */
	int paramCount(char elem);

	/** ��ȡ���������� */
	int maxParam();
	
	/** ��ȡ���Ԫ�� */
	char getRandomElem();
	
	/** ��ȡ���������Ԫ�� */
	char getFuncElem();
	
	/** ��ȡ����յ㼯Ԫ�� */
	char getTermElem();
	
	/** �Ƿ�����ֹ�� */
	bool isTerm(char elem);
	
	/** �Ƿ��Ǻ����� */
	bool isFunc(char elem);

	/** ����Dc�������ֵ */
	double randDcValue();

	/** �洢Dc������ */
	void saveDcValue();

	/** 
	 * ��׺���ʽת��׺���ʽ
	 * @param expression: ��׺�ַ������ʽ
	 * return: ��׺���ʽ�Ķ���
	 */
	queue<char> infix2postfix(string expression);

	/** 
	 * �����׺���ʽ 
	 * @param postfix: ��׺���ʽ
	 * @param value: �Ա�����ֵ
	 * return: ��׺���ʽ��ֵ
	 */
	double calculate(queue<char> postfix, map<char, double> value);

	/** ��ȡ��������ȼ� */
	int priority(char ch);

	/** ������ѧ���ʽ */
	double mathExpression(double value_l, char symbol, double value_r);
	double mathExpression(char symbol, double value_r);

private:
	static int gene_len;	// �����ܳ���
	static int tail_len;	// β������
	static vector<map<char, double>> indenpentVar;	// �Ա���
	string text;			// ��������
	BinaryTree* tree;		// ������
	vector<double> result;	// ���ʽ��ֵ
	vector<double> dc_value;	// �洢Dc�������
	static double* dc_array;	// Dc������ָ��
};
#endif

