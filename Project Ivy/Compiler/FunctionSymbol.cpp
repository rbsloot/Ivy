#include "FunctionSymbol.h"


FunctionSymbol::FunctionSymbol(std::string name, int argNr, Action* startAction, Action* endAction, bool internal)
{
	this->name = name;
	this->argNr = argNr;
	this->startAction = startAction;
	this->endAction = endAction;
	this->internal = internal;
}

FunctionSymbol::~FunctionSymbol()
{
}

Action* FunctionSymbol::getStartAction() { return startAction; }
Action* FunctionSymbol::getEndAction() { return endAction; }
std::string FunctionSymbol::getName() { return name; }
int FunctionSymbol::getArgumentNr() { return argNr; }
bool FunctionSymbol::isInternal() { return internal; }
