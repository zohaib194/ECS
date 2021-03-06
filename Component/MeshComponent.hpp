#pragma once 
#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "Component.hpp"
#include "structs.hpp"
#include "libs/glm/glm/glm.hpp"

#include <vector>


namespace ECS {

	class MeshComponent : public ECS::Component {
		private :
			/*  Mesh Data  */
	        std::vector<ECS::Vertex> vertices;
	        std::vector<unsigned int> indices;
	        std::vector<ECS::TextureA> textures;
	        /*  Functions  */
	        // void Draw(Shader shader);
		public :
			MeshComponent(std::string name, 
				std::vector<ECS::Vertex> vertices, 
				std::vector<unsigned int> indices, 
				std::vector<ECS::TextureA> textures = std::vector<ECS::TextureA>()) : ECS::Component(name){
				this->vertices = vertices;
				this->indices = indices;
				this->textures = textures;
			}

			//void execute();

			std::vector<ECS::Vertex> getVertices(){
				return this->vertices;
			}

			std::vector<unsigned int> getIndices(){
				return this->indices;
			}

			std::vector<ECS::TextureA> getTextures(){
				return this->textures;
			}
	};

}
#endif