#include "Entity/Entity.hpp"
#include "Component/TriangleComponent.cpp"
#include <iostream>
int main(){
	ECS::Entity entity(1);
	TriangleComponent triangleComponent("Box");

	triangleComponent.fillMesh(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));

	entity.addComponent(triangleComponent);

	TriangleComponent tc = entity.getComponent<TriangleComponent>("Box");
	std::cout << tc.getComponentName();

	return 0;
}