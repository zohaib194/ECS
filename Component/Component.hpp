#pragma once
#include <string> 

namespace ECS{
	class Component{
		public:
			Component(std::string name);
			virtual void execute();
			std::string getComponentName();
		private:
			std::string name;

	};	
}