#include "Component/MeshComponent.hpp"
#include "Component/ModelComponent.hpp"
#include "Entity/EntityManager.hpp"
#include "System/RenderMeshSystem.hpp"
#include "System/System.hpp"
#include "System/SystemManager.hpp"
#include "helpers/globals.hpp"
#include <iostream>
#ifdef __unix__
	#include <GL/glew.h>
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
	#include "GL/glew.h"
    #include <direct.h>
    #define getcwd _getcwd
#endif
#include "GLFW/glfw3.h"

#include <stdio.h>


ECS::EntityManager* entityManager;
ECS::SystemManager* systemManager;
ECS::ShaderManager* shaderManager;
const int MAX_PATH = 200;

GLFWwindow* glfw_setup() {

	//tries to initialize glfw. NOTE: should be changed to cause fatal error.
	if (!glfwInit())
	{
		return nullptr;
	}

	//glfwSetErrorCallback(glfw_errorCallback);

	//Multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Set requiered version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// create window
//	glm::vec2 wSize = environment::Camera::windowSize();
	GLFWwindow* window = glfwCreateWindow(1024, 720, "Exam", nullptr, nullptr);
	// set window as active
	glfwMakeContextCurrent(window);

	// Number of screen updates before swapping when calling glfwSwapBuffer();
	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		// Disable cursor when inside the window.

	glewExperimental = GL_TRUE;
    // Initialize GLEW QUESTION: should this be moved to other file?
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
    }

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glLineWidth(3);

	// Error handeling
	glEnable( GL_DEBUG_OUTPUT );
	//glDebugMessageCallback( (GLDEBUGPROC) gl_errorCallback, 0 );

    return window;
}


std::string getProjectPath(){
	char buffer[MAX_PATH];
	char *answer = getcwd(buffer, sizeof(buffer));
	std::string s_cwd;
	if (answer) {
	    s_cwd = answer;
	}
	return s_cwd.substr(0, s_cwd.find("ECS/", 0) + 4);
}




class PlayerEntity : public ECS::Entity{
	public:
		PlayerEntity(int ID) : ECS::Entity(ID){

		}

		void printPlayerEntity(){
			std::cout << "call from PlayerEntity\n";
		}
};

class EnemyEntity : public ECS::Entity{
	public:
		EnemyEntity(int ID) : ECS::Entity(ID){

		}

		void printPlayerEntity(){
			std::cout << "call from PlayerEntity\n";
		}
};


#include <vector>

int main(){
	GLFWwindow* window = glfw_setup();


	entityManager = new ECS::EntityManager();
	systemManager = new ECS::SystemManager();
	shaderManager = new ECS::ShaderManager();

	int i = entityManager->createEntity<PlayerEntity>();
	int j = entityManager->createEntity<EnemyEntity>();
	if(i != -1){
		std::cout << "Entity created: " << i << "\n";
	}

	PlayerEntity* player = dynamic_cast<PlayerEntity*>(entityManager->removeEntity(i));
	EnemyEntity* enemy = dynamic_cast<EnemyEntity*>(entityManager->removeEntity(j));

	//player->printTestEntity();
	std::vector<ECS::Vertex> vertices;
	ECS::Vertex vertex;
	vertex.position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertices.push_back(vertex);
	vertex.position = glm::vec3(0.5f, 0.0f, 0.0f);
	vertices.push_back(vertex);
	vertex.position = glm::vec3(1.0f,  -0.5f, 0.0f);
	vertices.push_back(vertex);

	std::vector<unsigned int> indices = {
		0, 1, 2
	};

	ECS::MeshComponent* mesh = new ECS::MeshComponent("Triangle", vertices, indices);
	player->addComponent(mesh);
	vertices.clear();
	indices.clear();

	vertex.position = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices.push_back(vertex);
	vertex.position = glm::vec3(-1.0f, 1.0f, 0.0f);
	vertices.push_back(vertex);
	vertex.position = glm::vec3(0.0f,  0.0f, 0.0f);
	vertices.push_back(vertex);
	vertex.position = glm::vec3(-1.0f,  0.0f, 0.0f);
	vertices.push_back(vertex);

	indices = {
		0, 1, 2,
		2, 1, 3
	};


	ECS::MeshComponent* mesh1 = new ECS::MeshComponent("Triangle", vertices, indices);

	enemy->addComponent(mesh1);

	// Get the project path.
	std::string projectPath = getProjectPath();

	//enemy->addComponent(new ECS::ModelComponent("PLAYER_MODEL", "./Game/Assets/modell_chessBoard.obj"));

	//ECS::ModelComponent* model = entityManager->getComponentByEntityID<ECS::ModelComponent*>(j);

	// Activate render system once all the mesh components are added on entities.
	systemManager->activateSystem<ECS::RenderMeshSystem>(projectPath + "shader/vertex.vert", projectPath + "shader/fragment.frag");

	//printf("Nr of components in player entity: %i\n", entityManager->getNrOfComponentForPlayer(i));
	while(!glfwWindowShouldClose(window))
	{
		// Clearing screen for next draw
		glClearColor(0.4, 0.8, 0.8, 1);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		systemManager->update(1.0f);

		glfwSwapBuffers(window);    // SWAP BUFFERS
        glfwPollEvents();           // LISTEN FOR WINDOW EVENTS

	}


	//TriangleComponent tc;
	//entity.getComponent<TriangleComponent>(std::string("Box"));
	//std::cout << tc.getComponentName();

	return 0;
}