#include "Entity.hpp"
#include <string>

ECS::Entity::Entity(int id){
	this->id = id;
}

void ECS::Entity::addComponent(Component component){
	this->components.push_back(component);
}

template <class T>
T ECS::Entity::getComponent(std::string name){
	for(T c : this->components){
		if(c.getComponentName() == name){
			return c;
		}
	}
}