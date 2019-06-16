#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string> 

namespace ECS{
	class Component{
		public:
			Component(){
				
			}
			Component(std::string name);
			std::string getComponentName();
			virtual ~Component() = default;
		private:
			std::string name;

	};	
}

#endif