#include "Log.h"

void Log::Execute(std::vector<boost::any> arglist)
{
	double a = Cast::cast<double>(arglist[0]);
	Result = std::log(a);
}

boost::any Log::GetResult()
{
	return Result;
}

Log::~Log()
{
}
