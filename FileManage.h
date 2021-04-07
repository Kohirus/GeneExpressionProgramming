#ifndef _FILEMANAGE_H_
#define _FILEMANAGE_H_

#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

/* �ļ������� */
class FileManage
{
public:
	FileManage(string name = "") : file(name) {}
	~FileManage() { close(); }

	/** ���ļ� */
	void open();

	/** �ر��ļ� */
	void close();

	/** �Ƿ���ļ� */
	bool isOpen();

	/** �趨�ļ�·�� */
	inline void setFileInfo(string name) { file = name; }

	/** ��ȡ�ļ�·�� */
	inline string getFileInfo() const { return file; }

	/** ��ȡ�ļ����� */
	vector<string>& fileText() { return text; }

protected:
	/** ���ж�ȡ */
	void readLine();

private:
	/** �����ļ��� */
	ifstream infile;
	/** �ļ����� */
	vector<string> text;
	/** �ļ�·�� */
	string file;
};

#endif
