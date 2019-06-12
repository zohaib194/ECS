#include "Entity/EntityManager.hpp"
#include "Component/MeshComponent.cpp"
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>

ECS::EntityManager *entityManager;

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




class PlayerEntity : public ECS::Entity{
	public:
		PlayerEntity(int ID) : ECS::Entity(ID){

		}

		void printPlayerEntity(){
			std::cout << "call from PlayerEntity\n";
		}
};


#include <vector>

int main(){
	GLFWwindow* window = glfw_setup();


	entityManager = new ECS::EntityManager();

	int i = entityManager->createEntity<PlayerEntity>();
	if(i != -1){
		std::cout << "Entity created: " << i << "\n";
	}

	PlayerEntity* player = dynamic_cast<PlayerEntity*>(entityManager->removeEntity(i));

	//player->printTestEntity();
	std::vector<ECS::Vertex> vertices;
	ECS::Vertex vertex;
	vertex.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertices.push_back(vertex);
	vertex.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertices.push_back(vertex);
	vertex.position = glm::vec3(0.0f,  0.5f, 0.0f);
	vertices.push_back(vertex);

	std::vector<unsigned int> indices = {
		0, 1, 2
	};

	ECS::MeshComponent mesh = ECS::MeshComponent("Triangle", vertices, indices);
	//TriangleComponent triangleComponent("Box");
	//	triangleComponent.fillMesh(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));

	player->addComponent(mesh);
	printf("Nr of components in player entity: %i\n", player->getNrOfComponents());
	while(!glfwWindowShouldClose(window))
	{
		// Clearing screen for next draw
		glClearColor(0.4, 0.8, 0.8, 1);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);    // SWAP BUFFERS
        glfwPollEvents();           // LISTEN FOR WINDOW EVENTS

	}


	//TriangleComponent tc;
	//entity.getComponent<TriangleComponent>(std::string("Box"));
	//std::cout << tc.getComponentName();

	return 0;
}



