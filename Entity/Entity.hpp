#pragma once 

#include "../Component/Component.hpp"
#include <vector>

namespace ECS{
	class Entity{
		public:
			int id;

			Entity();
			//~Entity();
			
			
			void setId(int id){
				this->id = id;
			}

			int getId(){
				return this->id;
			}



			virtual void addComponent(Component component);


			template <typename T>
			T getComponent(std::string name){
				for(auto c : this->components){
					if(c.getComponentName() == name){
						return c;
					}
				}
			}



		private:
			std::vector<Component> components;

	};
}