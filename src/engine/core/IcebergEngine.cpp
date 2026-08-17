// IcebergEngine.cpp : Defines the entry point for the application.
//

#include "IcebergEngine.h"
#include "utils/log.h"

namespace Engine
{
	IcebergEngine::IcebergEngine()
	{
		log(LOG_DEBUG, "Constructor");
	}

	IcebergEngine::~IcebergEngine()
	{
		log(LOG_DEBUG, "Destructor");
	}

	bool IcebergEngine::init() 
	{
		log(LOG_SUCCESS, "Init");
		return 1;
	}

	void IcebergEngine::start() 
	{
		log(LOG_DEBUG, "Start");
	}
}