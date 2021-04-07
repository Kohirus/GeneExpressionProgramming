#ifndef _FILECONTRILLER_H_
#define _FILECONTRILLER_H_

#include "paramsettings.h"
#include "FileManage.h"

class FileController : public FileManage
{
public:
	FileController();

	/** 获取自变量数据 */
	vector<vector<double>>& independent() { return independentVar; }

	/** 获取因变量数据 */
	vector<double>& dependent() { return dependentVar; }

private:
	/**
	 * 分割字符串
	 * @param input_str: 输入字符串
	 * @param output: 输出字符串
	 * @param delim: 分割标志
	 */
	void split(const std::string& input_str, std::vector<std::string>& output, const char* delim);

	vector<double> toDouble(vector<string>& data);

private:
	/** 自变量数据 */
	vector<vector<double>> independentVar;
	/** 因变量数据 */
	vector<double> dependentVar;
};

#endif // _FILECONTRILLER_H_


