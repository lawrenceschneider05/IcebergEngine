// IcebergEngine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.
namespace Engine
{
	void PrintEngineVersion();

	class IcebergEngine
	{
	public:
		IcebergEngine();
		~IcebergEngine();

		bool init();
		
		void start();
	private:
	};
}