#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

namespace ECS {
	class System {
		public:
			System();
			virtual void update(float dt) = 0;
			~System();
		

	};
}
#endif