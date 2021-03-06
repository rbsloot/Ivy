#include <string>
#include <fstream>
#include "WriteToFile.h"
#include "BaseException.h"
void WriteToFile::Execute(std::vector<boost::any> arglist)
{
	std::string lineToWrite;
	try{
		std::string path = Cast::cast<std::string>(arglist[0]);
		try{
			lineToWrite = Cast::cast<std::string>(arglist[1]);
		}
		catch (std::exception& e) {
			lineToWrite = std::to_string(boost::any_cast<double>(arglist[1]));
		}

		std::ofstream out;
		out.open(path, std::ios::app);
		out << lineToWrite << std::endl;
		out.close();
	}
	catch (std::exception& e){
		throw BaseException("WriteToFile kan geen booleans wegschrijven");
	}
}

boost::any WriteToFile::GetResult()
{
	return Result;
}

WriteToFile::~WriteToFile()
{
}
