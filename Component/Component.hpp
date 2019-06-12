#pragma once
#include <string> 

namespace ECS{
	class Component{
		public:
			Component(){
				
			}
			Component(std::string name);
			std::string getComponentName();
		private:
			std::string name;

	};	
}