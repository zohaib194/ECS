#pragma once
#ifndef MODELSYSTEM_H
#define MODELSYSTEM_H


#include "System.hpp"
#include "../Entity/EntityManager.hpp"

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


extern ECS::EntityManager *entityManager;
/**
 * @@brief Container for classes and structures associated with modeling consepts.
 */
namespace ECS{
    /**
     * @brief Consists of texture and mesh for.
     * @details Includes informationon has about filelocation of model
     * and if gamma correction has been applied.
     */
    class ModelSystem : : public ECS::System
    {
        public:

            ModelSystem();

            /**
             * @brief Loads the model from the given path.
             * @param path Path to the model to be loaded.
             * @param gamma Optional to indicate if the gammacorrection has already been applied.
             */
            ModelSystem(std::string const &path, bool gamma = false);

            /**
             * @brief Draws the model to the screen.
             * @param shader Shaderprogram for the GL pipeline
             */
            void Draw(Shader shader);

            void update(float dt);
        private:
            /**
             * @brief Loads the Model from the given path.
             * @details Loads a model with supported ASSIMP extensions
             * from file and stores the resulting meshes in the meshes vector.
             *
             * @param path The filepath to the Model file.
             */
            void loadModel(std::string const &path);

            /**
             * @brief Converts assimp mesh to proprietary mesh
             *
             * @param mesh Assimp mesh to be converted.
             * @param scene Assimp scene containing the given mesh.
             *
             * @return Proprietary mesh.
             */
        	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

            /**
             * @brief Adds each mesh conected with the node to meshes.
             *
             * @param node Assimp Node of the scene to be processed.
             * @param scene Assimp scene containing the node.
             */
            void processNode(aiNode *node, const aiScene *scene);
            // checks all material textures of a given type and loads the textures if they're not loaded yet.
            // the required info is returned as a Texture struct.

            /**
             * @brief Loads textures of a given type associated with the given type if they have not been loaded.
             *
             * @param mat Assimp material the texture is conected to.
             * @param type Name of type as defined by assimp
             * @param typeName Name of type for the return textureA.
             * @return Vector of textures associated with the material.
             */
            std::vector<TextureA> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

            /**
             * <External ID, Entity ID>.
             */
            std::vector<unsigned int> registeredEntities;

    };
}