#include "libs/glm/glm/glm.hpp"

namespace ECS {

	struct Vertex {
		glm::vec3 position;
	    //glm::vec3 Normal;
	    //glm::vec2 TexCoords;
	};


	struct Texture {
	    unsigned int id;
	    std::string type;
	};  
}