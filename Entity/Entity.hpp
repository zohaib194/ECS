#pragma once 


#ifndef ENTITY_H
#define ENTITY_H

#include "../Component/Component.hpp"

#include <vector>
#include <type_traits>

namespace ECS{
	class Entity{
		public:
			int id;

			Entity(int ID){
				this->id = ID;
			}
			//~Entity();
			
			
			void setId(int id){
				this->id = id;
			}

			inline const int getId() const {
				return this->id;
			}



			inline void addComponent(Component* component){
				this->components.push_back(component);
			}


			template <typename T>
			T getComponent(){
				for(auto &comp : this->components){
					T component = dynamic_cast<T>(comp);
					if(component != nullptr){

						return component;
					}
				}
				return nullptr;
			}

			template <class T>
			int getEntityIDByComponent(){
				for(auto &comp : this->components){
					T* temp = dynamic_cast<T*>(comp);
					if(temp != nullptr){

						return this->id;
					}
				}
				return -1;
			}

			inline const int getNrOfComponents() const {
				return this->components.size(); 
			}

			virtual ~Entity() = default;


		private:
			std::vector<Component*> components;

	};
}
#endif