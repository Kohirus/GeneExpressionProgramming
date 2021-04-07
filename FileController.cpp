#include "FileController.h"
#include <cstdlib>

FileController::FileController()
{
	// 自变量数据读取
	setFileInfo(PATH_INPUT);
	open();
	readLine();
	vector<string> inden = fileText();
	for (auto line : inden)
	{
		vector<string> result;
		split(line, result, " ");
		vector<double> temp = toDouble(result);
		independentVar.push_back(temp);
	}
	close();

	// 因变量数据读取
	setFileInfo(PATH_OUTPUT);
	open();
	readLine();
	vector<string> depen = fileText();
	for (auto line : depen)
	{
		vector<string> result;
		split(line, result, " ");
		dependentVar.push_back(atof(result[0].c_str()));
	}
	close();
}

void FileController::split(const std::string& input_str, std::vector<std::string>& output, const char* delim)
{
	int pos = 0;
	int npos = 0;
	int regexlen = strlen(delim);
	while ((npos = input_str.find(delim, pos)) != -1) {
		std::string tmp = input_str.substr(pos, npos - pos);
		output.push_back(tmp);
		pos = npos + regexlen;
	}
	output.push_back(input_str.substr(pos, input_str.length() - pos));
}

std::vector<double> FileController::toDouble(vector<string>& data)
{
	vector<double> temp;
	for (auto it : data)
	{
		temp.push_back(atof(it.c_str()));
	}
	return temp;
}
