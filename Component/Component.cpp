#include "Component.hpp"

ECS::Component::Component(std::string name){
	this->name = name;
}

void ECS::Component::execute(){

}

std::string ECS::Component::getComponentName(){
	return this->name;
}