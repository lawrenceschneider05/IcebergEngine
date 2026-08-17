// IcebergEngine.cpp : Defines the entry point for the application.
//

#include "IcebergEngine.h"
#include <iostream>

using std::cout;

namespace Engine
{
	IcebergEngine::IcebergEngine()
	{
		cout << "Constructor\n";
	}

	IcebergEngine::~IcebergEngine()
	{
		cout << "Destructor\n";
	}

	bool IcebergEngine::init() 
	{
		cout << "Init\n";
		return 1;
	}

	void IcebergEngine::start() 
	{
		cout << "Start\n";
	}
}