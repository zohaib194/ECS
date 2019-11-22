#include "RenderMeshSystem.hpp"
#include "../Component/MeshComponent.hpp"
#include "../Component/ModelComponent.hpp"
//#include "../Component/structs.hpp"
#ifdef __unix__
#include <GL/glew.h>
#elif defined(_WIN32) || defined(WIN32)
#include "GL/glew.h"
#endif
void ECS::RenderMeshSystem::createVAOVBO() {
	std::vector<unsigned int> entitiesID = entityManager->getAllEntitiesIDByComponent<ECS::MeshComponent>();
	unsigned int VAO, VBO, EBO;
	for(auto ID : entitiesID){

		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		this->VAOS.push_back(VAO);
		MeshComponent* mesh = entityManager->getComponentByEntityID<ECS::MeshComponent*>(ID);


		glGenBuffers(1, &VBO);
		this->VBOS.push_back(VBO);
		glGenBuffers(1, &EBO);
		this->EBOS.push_back(EBO);

		// Register the enetity.
		registeredEntities.push_back(std::make_pair(std::make_tuple(VAO, VBO, EBO), ID));
		glBindVertexArray(VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(ECS::Vertex), &mesh->getVertices()[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(unsigned int), &mesh->getIndices()[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ECS::Vertex), (void*)0);
	//	// vertex normals
	//	glEnableVertexAttribArray(1);
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	//	// vertex texture coords
	//	glEnableVertexAttribArray(2);
	//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	//	// vertex tangent
	//	glEnableVertexAttribArray(3);
	//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	//	// vertex bitangent
	//	glEnableVertexAttribArray(4);
	//	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

		glBindVertexArray(0);
	}

	entitiesID = entityManager->getAllEntitiesIDByComponent<ECS::ModelComponent>();
	VAO= 0;
	VBO = 0;
	EBO = 0;
	for(auto ID : entitiesID){

		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		this->VAOS.push_back(VAO);
		ModelComponent* model = entityManager->getComponentByEntityID<ECS::ModelComponent*>(ID);

		std::vector<ECS::MeshComponent> meshes = model->getMeshes();

		for (auto mesh : meshes) {
			glGenBuffers(1, &VBO);
			this->VBOS.push_back(VBO);
			glGenBuffers(1, &EBO);
			this->EBOS.push_back(EBO);

			// Register the enetity.
			registeredEntities.push_back(std::make_pair(std::make_tuple(VAO, VBO, EBO), ID));
			glBindVertexArray(VAO);
			// load data into vertex buffers
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			// A great thing about structs is that their memory layout is sequential for all its items.
			// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
			// again translates to 3/2 floats which translates to a byte array.
			glBufferData(GL_ARRAY_BUFFER, mesh.getVertices().size() * sizeof(ECS::Vertex), &mesh.getVertices()[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndices().size() * sizeof(unsigned int), &mesh.getIndices()[0], GL_STATIC_DRAW);

			// set the vertex attribute pointers
			// vertex Positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ECS::Vertex), (void*)0);
		//	// vertex normals
		//	glEnableVertexAttribArray(1);
		//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		//	// vertex texture coords
		//	glEnableVertexAttribArray(2);
		//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		//	// vertex tangent
		//	glEnableVertexAttribArray(3);
		//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		//	// vertex bitangent
		//	glEnableVertexAttribArray(4);
		//	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

			glBindVertexArray(0);
		}
	}
}

void ECS::RenderMeshSystem::update(float dt) {
	//  Draws every entity registed in RengerMeshSystem.
	this->draw();
};

void ECS::RenderMeshSystem::draw(){
	//std::vector<unsigned int> entitiesID = entityManager->getAllEntitiesIDByComponent<ECS::MeshComponent>();

	for(auto entityData : this->registeredEntities){
		MeshComponent* mesh = entityManager->getComponentByEntityID<ECS::MeshComponent*>(entityData.second);

		glBindVertexArray(std::get<0>(entityData.first));
		glBindBuffer(GL_ARRAY_BUFFER, std::get<1>(entityData.first));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, std::get<2>(entityData.first));

		//printf("%i, %i, %i, %i \n", std::get<0>(entityData.first), std::get<1>(entityData.first), std::get<2>(entityData.first), entityData.second);
		glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, 0);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}