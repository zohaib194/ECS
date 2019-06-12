#pragma once 

#include "../Component/Component.hpp"
#include <vector>

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



			inline void addComponent(Component component){
				this->components.push_back(component);
			}


			template <typename T>
			T getComponent(std::string name){
				for(auto c : this->components){
					if(c.getComponentName() == name){
						return c;
					}
				}
			}


			inline const int getNrOfComponents() const {
				return this->components.size(); 
			}

			 virtual ~Entity() = default;


		private:
			std::vector<Component> components;

	};
}