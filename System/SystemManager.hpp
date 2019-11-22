#pragma once
#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include "System.hpp"
#include "RenderMeshSystem.hpp"

#include <iostream>
#include <unordered_map>
#include <type_traits>
#include <typeinfo>   // operator typeid

extern unsigned int SystemId;

namespace ECS {

	class SystemManager {
		public:

			SystemManager(){
			}

			template <class T>
			void activateSystem(std::string vertPath, std::string fragPath){
				if(!std::is_base_of<ECS::System, T>::value){
					printf("[ERROR] Given system is not derived from class System\n");
					return;
				}

				if(typeid(ECS::RenderMeshSystem) == typeid(T) && vertPath != "" && fragPath != ""){
					this->systems[SystemId] = new T(vertPath, fragPath);
					SystemId++;

				}/* else {
					this->systems[SystemId] = new T();
					SystemId++;

				}*/

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