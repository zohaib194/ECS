#include "Component.hpp"
#include <glm/glm.hpp>

class TriangleComponent : public zECS::Component {
	private :
		struct Mesh {
			glm::vec3 vertices;
			glm::vec4 color;
		};

		Mesh meshes[3];
	public :
		TriangleComponent(std::string name) : ECS::Component(name){

		}

		void fillMesh(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, glm::vec4 color){		
			meshes[0].vertices = pointA;
			meshes[0].color = color;

			meshes[1].vertices = pointB;
			meshes[1].color = color;

			meshes[2].vertices = pointC;
			meshes[2].color = color;
		}

		//void execute();
};