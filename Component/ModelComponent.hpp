#pragma once
#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#include "Component.hpp"
#include "MeshComponent.hpp"
#include "libs/glm/glm/glm.hpp"

#include <vector>


namespace ECS {

	class ModelComponent : public ECS::Component {
		private :
			/*  Mesh Data  */
	        std::vector<TextureA> textures_loaded;	//!< Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
            std::vector<MeshComponent> meshes;      //!< The meshes the Model compose of.
            std::string directory;                  //!< Directory path containing the loaded model.
            bool gammaCorrection;                   //!< Indicates that gamma has been corrected for computer monitors. NOTE: not used yet.

	        /*  Functions  */
	        // void Draw(Shader shader);
		public :

			/**
			 * @brief      Constructs a new instance.
			 *
			 * @param[in]  name   The name
			 * @param      path   The path
			 * @param[in]  gamma  The gamma
			 */
			ModelComponent(std::string name, std::string const &path, bool gamma = true) : ECS::Component(name){
				this->directory = path;
				this->gammaCorrection = gamma;
			}

			//void execute();

			std::vector<MeshComponent> getMeshes(){
				return this->meshes;
			}

			/**
			 * @brief      Gets the loaded textures.
			 *
			 * @return     The loaded textures.
			 */
			std::vector<TextureA> getLoadedTextures(){
				return this->textures_loaded;
			}
			/**
			 * @brief      Gets the directory.
			 *
			 * @return     The directory.
			 */

			std::string getDirectory(){
				return this->directory;
			}

			bool isGammaCorrection(){
				return this->gammaCorrection;
			}
	};

}
#endif