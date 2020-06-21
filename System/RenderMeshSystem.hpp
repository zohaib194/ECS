#pragma once 
#ifndef RENDERMESHSYSTEM_H
#define RENDERMESHSYSTEM_H

#include "System.hpp"
#include <iostream>
#include <tuple>
#include <utility>      // std::pair, std::make_pair

#include "../Entity/EntityManager.hpp"
#include "../System/ShaderManager.hpp"

extern ECS::EntityManager *entityManager;
extern ECS::ShaderManager* shaderManager;

namespace ECS {
	class RenderMeshSystem : public ECS::System {

		public:
			RenderMeshSystem() {
				
			}
			RenderMeshSystem(std::string vertPath, std::string fragPath){
				shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
					{GL_VERTEX_SHADER, vertPath},
					{GL_FRAGMENT_SHADER, fragPath},
				});
				this->createVAOVBO();
			};

			void update(float dt);

			void draw();
			std::vector<unsigned int> VAOS;

		private:
			std::vector<unsigned int> VBOS;
			std::vector<unsigned int> EBOS;
			// VAO, VBO, EBO, EntityID
			std::vector<std::pair<std::tuple<unsigned int, unsigned int, unsigned int>, unsigned int>> registeredEntities;
			ECS::Shader* shaderProgram;

			void createVAOVBO();
	};
}
#endif