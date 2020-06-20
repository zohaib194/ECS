#include "ModelSystem.hpp"
#include <stdio.h>

/*ECS::ModelSystem::ModelSystem(){
	std::vector<unsigned int> entitiesID = entityManager->getAllEntitiesIDByComponent<ECS::ModelComponent>();

	for(auto ID: entitiesID) {
		if(!std::find(this->registeredEntities.begin(), this->registeredEntities.end(), ID) != this->registeredEntities.end()) {
			loadModel();
			this->registeredEntities.push_back(ID);
		}
		// TODO: Reassign the loaded model.
	}

}

modeler::Model::Model(std::string const &path, bool gamma)
{
	gammaCorrection = gamma;
    loadModel(path);
}*/

void ECS::ModelSystem::Draw(Shader shader)
{
}

void ECS::ModelSystem::loadModel(ModelComponent *model)
{
	const std::string path = model->getDirectory();
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        printf("From assimp with errorcode %d and description \"%s\n\"", 0, importer.GetErrorString());
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene, model);
}

ECS::MeshComponent ECS::ModelSystem::processMesh(aiMesh *mesh, const aiScene *scene, ModelComponent *model)
{
	// data to fill
	std::vector<ECS::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<ECS::TextureA> textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 tempVertex; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

		// positions
		if (mesh->HasPositions())
		{
			tempVertex.x = mesh->mVertices[i].x;
			tempVertex.y = mesh->mVertices[i].y;
			tempVertex.z = mesh->mVertices[i].z;
		}
		else{
			printf("Found no Vertex\n");
			tempVertex = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		vertex.position = tempVertex;

		// normals
		if (mesh->HasNormals())
		{
			tempVertex.x = mesh->mNormals[i].x;
			tempVertex.y = mesh->mNormals[i].y;
			tempVertex.z = mesh->mNormals[i].z;
		}
		else{
			printf("Found no Normals\n");
			tempVertex = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		vertex.normal = tempVertex;
		// texture coordinates
		if (mesh->HasTextureCoords(0)) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else{

			printf("Found no textureCoords\n");
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}
		// tangent and bitangent
		if (mesh->HasTangentsAndBitangents())
		{
			tempVertex.x = mesh->mTangents[i].x;
			tempVertex.y = mesh->mTangents[i].y;
			tempVertex.z = mesh->mTangents[i].z;
			vertex.tangent = tempVertex;

			// bitangent
			tempVertex.x = mesh->mBitangents[i].x;
			tempVertex.y = mesh->mBitangents[i].y;
			tempVertex.z = mesh->mBitangents[i].z;
			vertex.bitangent = tempVertex;

		}
		else{
			printf("Found no tangent or bitangent\n");

			vertex.tangent = glm::vec3(0.0f, 0.0f, 0.0f);
			vertex.bitangent = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	std::vector<ECS::TextureA> diffuseMaps = loadMaterialTextures(material, model, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<ECS::TextureA> specularMaps = loadMaterialTextures(material, model, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<ECS::TextureA> normalMaps = loadMaterialTextures(material, model, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<ECS::TextureA> heightMaps = loadMaterialTextures(material, model, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return ECS::MeshComponent("ChildComponent", vertices, indices, textures);
}


void ECS::ModelSystem::processNode(aiNode *node, const aiScene *scene, ModelComponent *model)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        model->addMesh(processMesh(mesh, scene, model));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, model);
    }
}

std::vector<ECS::TextureA> ECS::ModelSystem::loadMaterialTextures(aiMaterial *mat, ModelComponent *model, aiTextureType type, std::string typeName)
{	
	std::vector<ECS::TextureA> textures_loaded = model->getLoadedTextures();
    std::vector<ECS::TextureA> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            TextureA texture;
			std::string myfile = directory + "/" + str.C_Str();
			GLuint texID = genTexture(myfile.c_str());

			texture.id = texID;
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

GLuint ECS::ModelSystem::genTexture(const char* filename) {
	GLuint TextureID;

	/*-----------------------------------------------------------------------------
	*  Generate Texture and Bind it
	*-----------------------------------------------------------------------------*/
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID); 

	/*-----------------------------------------------------------------------------
	*  Allocate Memory on the GPU
	*-----------------------------------------------------------------------------*/
   
    int twidth, theight, nrComponents;
	unsigned char* image = SOIL_load_image(filename, &twidth, &theight, &nrComponents, SOIL_LOAD_AUTO);
	if (image)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		// target | lod | internal_format | width | height | border | format | type | data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D); // Generate MipMaps to use
		SOIL_free_image_data(image); // Free the data read from file after creating opengl texture 

	  /*-----------------------------------------------------------------------------
	   *  Set Texture Parameters
	   *-----------------------------------------------------------------------------*/
	   // Set these parameters to avoid a black screen caused by improperly mipmapped textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glActiveTexture(GL_TEXTURE0);
		/*-----------------------------------------------------------------------------
		 *  Unbind texture
		 *-----------------------------------------------------------------------------*/
		 // glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {

		printf("SOIL cannot load image \n%s\n", filename);

	}

	return TextureID;
}