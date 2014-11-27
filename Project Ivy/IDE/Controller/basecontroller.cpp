#include "basecontroller.h"
#include <qdebug.h>
#include <iostream>
#include "mainwindow.h"

#include "..\..\Tokenizer\Tokenizer.h"
#include "..\..\Tokenizer\BadSyntaxException.h"
#include "..\..\Compiler\Compiler.h"
#include "..\..\Virtual Machine\VirtualMachine.h"
#include "..\Jzon.h"

BaseController::BaseController(MainWindow * source)
{
	this->source = source;
}

BaseController::~BaseController()
{
	delete virtualMachine;
	delete compiler;
	delete tokenizer;
}

void BaseController::startBuilding(bool onlyBuild)
{
	source->getBottomBar()->clearErrorList();

	std::vector<std::string> list = source->getCodeEditor()->getEditorContent();

	tokenizer = new Tokenizer();
	try
	{
		tokenizer->tokenize(&list[0], list.size());
	}
	catch (BadSyntaxException& e)
	{
		qDebug() << e.what();
		source->getBottomBar()->addError(e.getLineNumber(), e.getLinePosition(), e.what());
	}

	compiler = new Compiler(tokenizer->getTokenList());
	try
	{
		compiler->compile();
	}
	catch (BadSyntaxException& e)
	{
		qDebug() << e.what();
		source->getBottomBar()->addError(e.getLineNumber(), e.getLinePosition(), e.what());
	}

	if (onlyBuild)
	{
		delete compiler;
		delete tokenizer;
	}
}

void BaseController::startRunning()
{
	startBuilding(false);

	VirtualMachine *virtualMachine = new VirtualMachine();
	try
	{
		virtualMachine->run(compiler->getFirstAction());
	}
	catch (exception e)
	{
		qDebug() << e.what();
	}

	delete virtualMachine;
	delete compiler;
	delete tokenizer;
}
