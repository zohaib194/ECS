#include "Entity.hpp"
#include <string>

ECS::Entity::Entity(){
	this->id = 0;
}

void ECS::Entity::addComponent(Component component){
	this->components.push_back(component);
}

/*
template <typename T>
T ECS::Entity::getComponent(std::string name){
	for(T c : this->components){
		if(c.getComponentName() == name){
			return c;
		}
	}
}
*/