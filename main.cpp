#include "Entity/EntityManager.hpp"
#include "Component/TriangleComponent.cpp"
#include <iostream>

class testEntity : public ECS::Entity{
	public:
		testEntity(){

		}

};

int main(){
	ECS::EntityManager *entityManager;
	entityManager = new ECS::EntityManager();

	int i = entityManager->createEntity<testEntity>();
	if(i != -1){
		std::cout << "Entity created\n";
	}

	TriangleComponent triangleComponent("Box");

	triangleComponent.fillMesh(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));

	//entity.addComponent(triangleComponent);


	//TriangleComponent tc;
	//entity.getComponent<TriangleComponent>(std::string("Box"));
	//std::cout << tc.getComponentName();

	return 0;
}