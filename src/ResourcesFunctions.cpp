#include "ResourcesFunctions.h"


std::string getFileData(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if(in)
	{
		std::string data;

		//Set cursor at end of file to get its size
		in.seekg(0, std::ios::end);
		data.resize(in.tellg());
		//Set cursor at beginning to read file
		in.seekg(0, std::ios::beg);
		in.read(&data[0], data.size());
		in.close();

		return(data);
	}
	throw(errno);
}