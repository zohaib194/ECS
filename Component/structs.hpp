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

	/**
	 * @brief texture loaded from file.
	 */
	struct TextureA {
		unsigned int id;		//!< Identifier for the texture.
		std::string type;		//!< The type of data given by the texure. (color, hight, etc)
		std::string path;		//!< File path to the texture.
	};
}