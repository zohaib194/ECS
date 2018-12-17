#pragma once
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
				this->entities[EntityId] = new T();
				this->entities[EntityId]->setId(EntityId);

				return this->entities[EntityId++]->getId();
			}

			template <class T>
			void removeEntity(T identity){
				if(std::is_class<T>::value){
					
				}
			}


		private:
			std::unordered_map<int, ECS::Entity*> entities; 
	};
}