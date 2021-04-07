#include "Gene.h"
#include "paramsettings.h"
#include "BinaryTree.h"
#include <queue>
#include <stack>
#include <math.h>
#include <string>

int Gene::gene_len = 15;
int Gene::tail_len = 8;
vector<map<char, double>> Gene::indenpentVar = {};
double* Gene::dc_array = nullptr;

Gene::Gene(const string& str)
	: text(str)
	, result()
	, tree(nullptr)
{
	// ��������ܳ��Ⱥ�β������
	int n = maxParam();
	tail_len = HEAD_LEN * (n - 1) + 1;
	gene_len = tail_len + HEAD_LEN;
}

Gene::Gene(const Gene& obj)
	: tree(NULL)
	, result(obj.result)
	, text(obj.text)
	, dc_value(obj.dc_value)
{
}

Gene& Gene::operator=(const Gene& obj)
{
	if (this != &obj)
	{
		this->tree = NULL;
		this->text = obj.text;
		result = obj.result;
		dc_value = obj.dc_value;
	}
	return *this;
}

Gene::~Gene()
{
	if (!tree)
		delete tree;
}

void Gene::initialize()
{
	// ������ɵ�һ��������Ԫ��
	text += getFuncElem();
	// �������ͷ��Ԫ��
	for (int i = 1; i < HEAD_LEN; ++i)
	{
		text += getRandomElem();
	}
	// �������β��Ԫ��
	for (int i = 0; i < tail_len; ++i)
	{
		text += getTermElem();
	}

	// ���ɲ��洢Dc������
	if(IS_OPEN_DC)
		saveDcValue();
	
	// ������ʽΪ��׺���ʽ
	string expression = decode();
	// ��׺ת��׺
	queue<char> postfix_str = infix2postfix(expression);
	// ��׺���� ����ѵ������
	int len_inden = indenpentVar.size();
	for (int i = 0; i < len_inden; i++)
	{
		double value_practise = calculate(postfix_str, indenpentVar[i]);
		result.push_back(value_practise);
	}
}

void Gene::setData(const vector<vector<double>>& value)
{
	int len = sizeof(TERM) / sizeof(char);
	for (auto line : value)
	{
		map<char, double> temp = {};
		for (int j = 0; j < len; j++)
		{
			temp.insert(std::pair<char, double>(TERM[j], line[j]));
		}
		indenpentVar.push_back(temp);
	}
}

void Gene::mutation()
{
	int index = rand() % gene_len;
	char ch;
	if (index < HEAD_LEN)
		ch = getRandomElem();
	else
		ch = getTermElem();
	text[index] = ch;
}

void Gene::transposition(const string& str)
{
	int len = str.length();
	// ��ɾ��ͷ����β��len�����ȵ��ַ�
	text.erase(HEAD_LEN - len, len);
	// ��ȡĿǰ�����ͷ������
	int curr_head_len = text.length() - tail_len;
	// ��������ͷ����Ԫ�ص����λ��
	int index = (rand() % curr_head_len) + 1;
	text.insert(index, str);
}

int Gene::find_func(const int pos)
{
	for (int i = pos; i < HEAD_LEN; i++)
	{
		if (isFunc(text.at(i)))
			return i;
	}
	return -1;
}

void Gene::update()
{
	result.clear();

	// ���ɲ��洢Dc������
	if (IS_OPEN_DC)
		saveDcValue();

	// ������ʽΪ��׺���ʽ
	string expression = decode();
	// ��׺ת��׺
	queue<char> postfix_str = infix2postfix(expression);
	// ��׺����
	int len_inden = indenpentVar.size();
	for (int i = 0; i < len_inden; i++)
	{
		double value_practise = calculate(postfix_str, indenpentVar[i]);
		result.push_back(value_practise);
	}
}

std::string Gene::decode()
{
	queue<char> queue = {};
	int index = 0;  // ����Ƭ���ַ������±�����
	tree = new BinaryTree(text.at(index));
	queue.push(text.at(index));
	index++;
	// ���������
	while (!queue.empty())
	{
		char ch = queue.front();
		queue.pop();
		if (isTerm(ch))
			continue;
		else
		{
			int count = paramCount(ch);
			BinaryTreeNode* parent = tree->Find(ch);
			for (int i = 0; i < count; i++)
			{
				char value = text.at(index);
				if (count == 1)
					tree->Insert(parent, value, false);
				else
					tree->Insert(parent, value);
				index++;
				queue.push(value);
			}
		}
	}
	// �������������
	string result = tree->Output();
	delete tree;
	return result;
}

std::string Gene::decodeWithDc()
{
	string expression = decode();
	int flag = 0;
	string::size_type index;
	while ((index = expression.find('?')) != string::npos)
	{
		string temp = std::to_string(dc_value[flag++]);
		expression.replace(expression.find('?'), 1, temp);
	}
	return expression;
}

void Gene::initDc()
{
	if (IS_OPEN_DC)
	{
		// ����Dc���ڴ�
		dc_array = new double[DC_LEN];
		// ��ʼ��Dc��Ԫ����ֵ��С
		int minValue = int(DC_MIN_VALUE * 1000);
		int maxValue = int(DC_MAX_VALUE * 1000);
		for (int i = 0; i < DC_LEN; i++)
		{	
			int value = (rand() % (maxValue - minValue + 1)) + minValue;
			dc_array[i] = value / 1000.0;
		}
	}
}

void Gene::destroyDc()
{
	if (dc_array != nullptr)
		delete[] dc_array;
}

int Gene::paramCount(char elem)
{
	if (elem == '+' || elem == '*' || elem == '-' || elem == '/')
		return 2;
	else
		return 1;
}

int Gene::maxParam()
{
	for (int i = 0; i < HEAD_LEN; i++)
	{
		if (FUNC[i] == '+' || FUNC[i] == '*' || FUNC[i] == '-' || FUNC[i] == '/')
			return 2;
	}
	return 1;
}

char Gene::getRandomElem()
{
	int index = rand() % 2;
	if (index)
		return getFuncElem();
	else
		return getTermElem();
}

char Gene::getFuncElem()
{
	int len = sizeof(FUNC) / sizeof(char);
	int index = rand() % len;
	return FUNC[index];
}

char Gene::getTermElem()
{
	int len = sizeof(TERM) / sizeof(char);
	if (!IS_OPEN_DC)
	{
		// ���û�п���Dc��
		int index = rand() % len;
		return TERM[index];
	}
	else
	{
		// ���������Dc�� ���ȼ�1
		vector<char> dc_term;
		for (int i = 0; i < len; i++)
		{
			dc_term.push_back(TERM[i]);
		}
		dc_term.push_back('?');
		int index = rand() % (len + 1);
		return dc_term[index];
	}
}

bool Gene::isTerm(char elem)
{
	for (int i = 0; i < sizeof(TERM) / sizeof(char); i++)
	{
		if (elem == TERM[i])
			return true;
	}
	if (IS_OPEN_DC && elem == '?')
		return true;

	return false;
}

bool Gene::isFunc(char elem)
{
	for (int i = 0; i < sizeof(FUNC) / sizeof(char); i++)
	{
		if (elem == FUNC[i])
			return true;
	}
	return false;
}

double Gene::randDcValue()
{
	int index = rand() % DC_LEN;
	return dc_array[index];
}

void Gene::saveDcValue()
{
	for (string::iterator it = text.begin(); it != text.end(); ++it)
	{
		if (*it == '?')
		{
			double temp = randDcValue();
			dc_value.push_back(temp);
		}
	}
}

std::queue<char> Gene::infix2postfix(string expression)
{
	// �Ƚ��ַ������ʽ�������
	queue<char> temp;
	for (string::iterator it = expression.begin(); it != expression.end(); ++it)
	{
		temp.push(*it);
	}

	queue<char> postfix;
	stack<char> charStack;
	while (!temp.empty())
	{
		// �����ַ������еĶ�ͷԪ��
		char ch = temp.front();
		temp.pop();
		if (isTerm(ch))
		{
			// ����������� ֱ�����
			postfix.push(ch);
		}
		else if (ch == '(')
		{
			// ����������� ѹ���ջ
			charStack.push(ch);
		}
		else if (ch == ')')
		{
			// ����������� ����ջ������������ ֱ������������(��ջ �����)
			char elem;
			while (!charStack.empty() && (elem = charStack.top()) != '(')
			{
				postfix.push(elem);
				charStack.pop();
			}
			// ����������
			if(!charStack.empty())
				charStack.pop();
		}
		else if (isFunc(ch))
		{
			// ����������
			// �����ջΪ�գ���ջ�������Ϊ�����š�(������ֱ�ӽ����������ջ
			// �����ȼ�����ջ�������ʱ�������ѹջ��
			// �����ȼ�С�ڻ����ջ�������ʱ����ջ������������������
			// �ٱȽ��µ�ջ���������ֱ�������������ջ����������ȼ�Ϊֹ��Ȼ�󽫸������ѹջ
			if (charStack.empty() || charStack.top() == '(')
			{
				charStack.push(ch);
			}
			else
			{
				int curPriority = priority(ch);
				int topPriority = -1;;
				while (!charStack.empty() && curPriority <= (topPriority = priority(charStack.top())))
				{
					char c = charStack.top();
					charStack.pop();
					postfix.push(c);
				}
				charStack.push(ch);
			}
		}
	}
	// ��󵯳�ջ��ʣ��Ԫ��
	while (!charStack.empty())
	{
		postfix.push(charStack.top());
		charStack.pop();
	}
	return postfix;
}

double Gene::calculate(queue<char> postfix, map<char, double> value)
{
	stack<double> temp;
	double result = 0.0;
	int flag = 0;
	while (!postfix.empty())
	{
		char ch = postfix.front();
		if (isTerm(ch))
		{
			// ����ǡ�?����Ӵ洢��Dc��������ѡ����ֵ
			if (IS_OPEN_DC && ch == '?')
			{
				temp.push(dc_value[flag++]);
			}
			else
			{
				// �����������ջ
				temp.push(value.at(ch));
			}
		}
		else if (isFunc(ch))
		{
			// ���������� �򵯳�n������Ҫ������
			int num = paramCount(ch);
			if (num == 1)
			{
				double value = temp.top();
				temp.pop();
				result = mathExpression(ch, value);
			}
			else if (num == 2)
			{
				double value1 = temp.top();
				temp.pop();
				double value2 = temp.top();
				temp.pop();
				result = mathExpression(value1, ch, value2);
			}
			// ��������ջ
			temp.push(result);
		}
		postfix.pop();
	}
	return result;
}

int Gene::priority(char ch)
{
	if (ch == '+' || ch == '-')
		return 0;
	else if (ch == '*' || ch == '/')
		return 1;
	else if (ch == '(')
		return 3;
	else
		return 2;
}

double Gene::mathExpression(double value_l, char symbol, double value_r)
{
	double value = 0.0;
	switch (symbol)
	{
	case '+':
		value = value_l + value_r;
		break;
	case '-':
		value = value_l - value_r;
		break;
	case '*':
		value = value_l * value_r;
		break;
	case '/':
		value = value_r / value_l;
		if (isinf(value) || isnan(value))
			value = 0.0;
		break;
	default:
		break;
	}
	return value;
}

double Gene::mathExpression(char symbol, double value_r)
{
	double value = 0.0;
	switch (symbol)
	{
	case 'S':	// sin
		value = sin(value_r);
		break;
	case 'C':	// cos
		value = cos(value_r);
		break;
	case 'T':	// tan
		value = tan(value_r);
		break;
	case 'Q':	// sqrt
		value = sqrt(fabs(value_r));
		break;
	case 'E':	// exp
		value = exp(value_r);
		break;
	case 'L':	// log10
		value = log10(fabs(value_r));
		break;
	default:
		break;
	}
	if (isfinite(value) || isinf(value) || isnan(value))
		value = 0.0;
	return value;
}
