#pragma once

#include "util/noncopyable.h"

namespace Engine {

	class iRenderCommand private NonCopyable{
	public:
		
		void execute = 0;



	};



}