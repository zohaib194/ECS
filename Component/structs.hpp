#include "libs/glm/glm/glm.hpp"

namespace ECS {

	struct Vertex {
		glm::vec3 position;
	    glm::vec3 normal;
	    glm::vec2 texCoords;
	    glm::vec3 tangent;		//!< Information usefull for lighting.	
		glm::vec3 bitangent;	//!< Information usefull for defining curves.
	};


	struct Texture {
	    unsigned int id;
	    std::string type;
	};

	/**
	 * @brief texture loaded from file.
	 */
	struct TextureA {
		unsigned int id;		//!< Identifier for the texture.
		std::string type;		//!< The type of data given by the texure. (color, hight, etc)
		std::string path;		//!< File path to the texture.
	};
}