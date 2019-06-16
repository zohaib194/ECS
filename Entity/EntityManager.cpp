#include "EntityManager.hpp"


ECS::Entity* ECS::EntityManager::removeEntity(int ID){
	std::unordered_map<int, ECS::Entity*>::const_iterator got = this->entities.find(ID);

	if ( got == this->entities.end() ) {
		printf("[ERROR] Entity not found.\n");
	}

	return got->second;
}