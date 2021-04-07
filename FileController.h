#ifndef _FILECONTRILLER_H_
#define _FILECONTRILLER_H_

#include "paramsettings.h"
#include "FileManage.h"

class FileController : public FileManage
{
public:
	FileController();

	/** ��ȡ�Ա������� */
	vector<vector<double>>& independent() { return independentVar; }

	/** ��ȡ��������� */
	vector<double>& dependent() { return dependentVar; }

private:
	/**
	 * �ָ��ַ���
	 * @param input_str: �����ַ���
	 * @param output: ����ַ���
	 * @param delim: �ָ��־
	 */
	void split(const std::string& input_str, std::vector<std::string>& output, const char* delim);

	vector<double> toDouble(vector<string>& data);

private:
	/** �Ա������� */
	vector<vector<double>> independentVar;
	/** ��������� */
	vector<double> dependentVar;
};

#endif // _FILECONTRILLER_H_


