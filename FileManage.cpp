#include "FileManage.h"

void FileManage::open()
{
	infile.open(file.data());
	assert(isOpen());
}

void FileManage::close()
{
	infile.close();
}

bool FileManage::isOpen()
{
	return infile.is_open();
}

void FileManage::readLine()
{
	text.clear();
	string s;
	while (getline(infile, s))
	{
		text.push_back(s);
	}
}
