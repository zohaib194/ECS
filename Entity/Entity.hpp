#pragma once 

#include "../Component/Component.hpp"
#include <vector>

namespace ECS{
	class Entity{
		public:
			int id;

			Entity(int id);
			//~Entity();
			virtual void addComponent(Component component);
			template <class T> T
			getComponent(std::string name);

		private:
			std::vector<Component> components;

	};
}