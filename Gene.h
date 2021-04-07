#ifndef _GENE_H_
#define _GENE_H_

#include <string>
#include <vector>
#include <queue>
#include <map>

class BinaryTree;

using namespace std;

/* 基因类 */
class Gene
{
public:
	Gene(const string& str = "");
	Gene(const Gene& obj);
	Gene& operator= (const Gene& obj);
	~Gene();

	/** 生成初始基因片段 */
	void initialize();

	/** 设置数据 */
	static void setData(const vector<vector<double>>& value);

	/** 获取基因内容 */
	inline string content() { return text; }
	
	/** 获取基因长度 */
	static inline int length() { return gene_len; }

	/** 基因突变 */
	void mutation();

	/** 
	 * IS转座、RIS转座
	 * @param str: 转座的基因序列
	 */
	void transposition(const string& str);

	/** 从pos开始向后查找,直到找到一个函数位置,返回该函数的索引 */
	int find_func(const int pos);
	
	/** 获取表达式的值 */
	vector<double> expressionValue() { return result; }

	/** 获取训练样本数目 */
	static int sampleCount() { return indenpentVar.size(); }

	/** 重新计算基因相关数据 */
	void update();

	/** 设置基因内容 */
	void setContent(const string& content) { text = content; }

	/** 解码二叉表达树 */
	string decode();

	/** 解码二叉表达树，并且包含Dc域的具体数值 */
	string decodeWithDc();

	/** 初始化Dc域 */
	static void initDc();

	/** 销毁Dc域 */
	static void destroyDc();

private:	
	/** 判断元素所需参数 */
	int paramCount(char elem);

	/** 获取集合最大参数 */
	int maxParam();
	
	/** 获取随机元素 */
	char getRandomElem();
	
	/** 获取随机函数集元素 */
	char getFuncElem();
	
	/** 获取随机终点集元素 */
	char getTermElem();
	
	/** 是否是终止符 */
	bool isTerm(char elem);
	
	/** 是否是函数符 */
	bool isFunc(char elem);

	/** 生成Dc域随机数值 */
	double randDcValue();

	/** 存储Dc域数据 */
	void saveDcValue();

	/** 
	 * 中缀表达式转后缀表达式
	 * @param expression: 中缀字符串表达式
	 * return: 后缀表达式的队列
	 */
	queue<char> infix2postfix(string expression);

	/** 
	 * 计算后缀表达式 
	 * @param postfix: 后缀表达式
	 * @param value: 自变量的值
	 * return: 后缀表达式的值
	 */
	double calculate(queue<char> postfix, map<char, double> value);

	/** 获取运算符优先级 */
	int priority(char ch);

	/** 计算数学表达式 */
	double mathExpression(double value_l, char symbol, double value_r);
	double mathExpression(char symbol, double value_r);

private:
	static int gene_len;	// 基因总长度
	static int tail_len;	// 尾部长度
	static vector<map<char, double>> indenpentVar;	// 自变量
	string text;			// 基因内容
	BinaryTree* tree;		// 二叉树
	vector<double> result;	// 表达式的值
	vector<double> dc_value;	// 存储Dc域的数据
	static double* dc_array;	// Dc域数组指针
};
#endif

