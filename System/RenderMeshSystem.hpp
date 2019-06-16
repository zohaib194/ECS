#pragma once 
#ifndef RENDERMESHSYSTEM_H
#define RENDERMESHSYSTEM_H

#include "System.hpp"
#include <iostream>
#include "../Entity/EntityManager.hpp"

extern ECS::EntityManager *entityManager;

namespace ECS {
	class RenderMeshSystem : public ECS::System {

		public:
			RenderMeshSystem(){
				this->createVAOVBO();
			};

			void update(float dt) override;
			unsigned int VAO;

		private:
			unsigned int VBO;
			unsigned int EBO;

			void createVAOVBO();
	};
}
#endif