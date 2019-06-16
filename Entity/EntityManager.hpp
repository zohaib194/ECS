#pragma once
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.hpp"
//#include "../helpers/globals.hpp"

#include <iostream>
#include <unordered_map> 

extern unsigned int EntityId;

namespace ECS{
	class EntityManager {
		public:

			EntityManager(){

			}

			/**
			 * @brief      Creates an entity.
			 *
			 * @return     Entity id.
			 */
			template <class T>
			unsigned int createEntity(){
				if(!std::is_base_of<ECS::Entity, T>::value){
					printf("[ERROR] Entity is not devired from class Entity.\n");
					return -1;
				} 
				this->entities[EntityId] = new T(EntityId);
				//this->entities[EntityId]->setId(EntityId);

				return this->entities[EntityId++]->getId();
			}

			template <class T>
			std::vector<unsigned int> getAllEntitiesByComponent(){
				std::vector<unsigned int> entitiesFound;
				int entityID = 0;
				for(auto &entity : this->entities){
					entityID = entity.second->getEntityIDByComponent<T>();
					if(entityID != -1){
						entitiesFound.push_back(entityID);

					}
				}

				return entitiesFound;
			}

			ECS::Entity* removeEntity(int ID);


		private:
			std::unordered_map<int, ECS::Entity*> entities; 
	};
}

#endif