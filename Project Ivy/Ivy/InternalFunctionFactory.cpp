#include "InternalFunctionFactory.h"

InternalFunctionFactory::InternalFunctionFactory()
{
	//Date
	//I/O
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("readFile", new ReadFile(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("saveFile", new SaveFile(), 2);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("writeToFile", new WriteToFile(), 2);
	//Math
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("cos", new Cos(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("invert", new Invert(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("log", new Log(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("pow", new Pow(), 2);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("random", new Random(), 0);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("random_t", new RandomWithPara(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("random_b", new RandomWithRange(), 2);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("sin", new Sin(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("sqrt", new SquareRoot(), 1);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("tan", new Tan(), 1);
	//System
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("consoleInput", new ConsoleInput(), 0);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("print", new Print(), 1);
	//Easteregg
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("summonSupremeLord", new SummonSupremeLord(), 0);
	InternalFunctionFactory::Instance()->RegisterFactoryFunction("summonSupremeCommander", new SummonSupremeCommander(), 0);
}

InternalFunctionFactory::~InternalFunctionFactory() 
{
	for each(auto it in factoryFunctionRegistry)
		delete it.second;
}

InternalFunctionFactory* InternalFunctionFactory::Instance()
{
	static InternalFunctionFactory instance;
	return &instance;
}


void InternalFunctionFactory::RegisterFactoryFunction(std::string name, IInternalFunction* classFactoryFunction, int argNr)
{
	factoryFunctionRegistry[name] = classFactoryFunction;
	factoryFunctionArgNrRegistry[name] = argNr;
}


IInternalFunction* InternalFunctionFactory::Create(std::string name)
{
	IInternalFunction * instance = nullptr;
	auto it = factoryFunctionRegistry.find(name);
	if (it != factoryFunctionRegistry.end()){
		instance = it->second;
	}
	if (instance != nullptr){
		return instance;
	}
	else{
		return nullptr;
	}
}

const std::map<std::string, IInternalFunction*> InternalFunctionFactory::GetMap()
{
	return factoryFunctionRegistry;
}

const std::map<std::string, int> InternalFunctionFactory::GetArgNrMap()
{
	return factoryFunctionArgNrRegistry;
}