#pragma once
#include <iostream>
#include <unordered_map> 
#include <type_traits>
#include "Entity.hpp"
#include "../helpers/globals.hpp"

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
			int createEntity(){
				if(!std::is_base_of<ECS::Entity, T>::value){
					printf("[ERROR] Entity is not devired from class Entity.\n");
					return ENTITY_INIT_ERROR;
				} 
				this->entities[EntityId] = new T(EntityId);
				//this->entities[EntityId]->setId(EntityId);

				return this->entities[EntityId++]->getId();
			}

			
			ECS::Entity* removeEntity(int ID){
				std::unordered_map<int, ECS::Entity*>::const_iterator got = this->entities.find(ID);

				if ( got == this->entities.end() ) {
					printf("[ERROR] Entity not found.\n");
				}

				return got->second;
			}


		private:
			std::unordered_map<int, ECS::Entity*> entities; 
	};
}