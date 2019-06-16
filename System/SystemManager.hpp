#pragma once
#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include "System.hpp"

#include <iostream>
#include <unordered_map> 
#include <type_traits>

extern unsigned int SystemId;


namespace ECS {

	class SystemManager {
		public:

			SystemManager(){

			}

			template <class T>
			void activateSystem(){
				if(!std::is_base_of<ECS::System, T>::value){
					printf("[ERROR] Given system is not derived from class System\n");
					return;
				}

				this->systems[SystemId] = new T();
				SystemId++;
			}

			void update(float dt){
				for(auto& system : this->systems) {
					system.second->update(dt);
				}
			}
		private:
			std::unordered_map<int, ECS::System*> systems;
	};
}

#endif