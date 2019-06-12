#include "Component.hpp"

ECS::Component::Component(std::string name){
	this->name = name;
}

std::string ECS::Component::getComponentName(){
	return this->name;
}