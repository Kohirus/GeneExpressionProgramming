#ifndef _FILEMANAGE_H_
#define _FILEMANAGE_H_

#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

/* 文件管理类 */
class FileManage
{
public:
	FileManage(string name = "") : file(name) {}
	~FileManage() { close(); }

	/** 打开文件 */
	void open();

	/** 关闭文件 */
	void close();

	/** 是否打开文件 */
	bool isOpen();

	/** 设定文件路径 */
	inline void setFileInfo(string name) { file = name; }

	/** 获取文件路径 */
	inline string getFileInfo() const { return file; }

	/** 获取文件内容 */
	vector<string>& fileText() { return text; }

protected:
	/** 按行读取 */
	void readLine();

private:
	/** 输入文件流 */
	ifstream infile;
	/** 文件内容 */
	vector<string> text;
	/** 文件路径 */
	string file;
};

#endif
