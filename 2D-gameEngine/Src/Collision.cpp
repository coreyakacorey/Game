#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w >= recB.x &&      // A’s right edge is to the right of (or touching) B’s left
		recB.x + recB.w >= recA.x &&      // B’s right edge is to the right of A’s left
		recA.y + recA.h >= recB.y &&      // A’s bottom is below (or touching) B’s top
		recB.y + (recB.h) >= recA.y         // B’s bottom is below A’s top
		) {

		//if (recA.y + recA.h > recB.y) { std::cout << "Rec A: " << recA.y + recA.h << " " << "Rec B: " << recB.y << " " << recA.h << std::endl; }
		//std::cout << "Rec A:" << recA.x << " " << recA.y << "Rec B:" << recB.x << " " << recB.y << std::endl;
		return true;
	}
	return false;
}

int Collision::AABBint(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w >= recB.x &&      // A’s right edge is to the right of (or touching) B’s left
		recB.x + recB.w >= recA.x &&      // B’s right edge is to the right of A’s left
		recA.y + recA.h >= recB.y &&      // A’s bottom is below (or touching) B’s top
		recB.y + (recB.h) >= recA.y         // B’s bottom is below A’s top
		) {

		int overlapLeft = (recA.x + recA.w) - recB.x;          // A's right past B's left
		int overlapRight = (recB.x + recB.w) - recA.x;          // B's right past A's left
		int overlapTop = (recA.y + recA.h) - recB.y;          // A's bottom past B's top
		int overlapBottom = (recB.y + recB.h) - recA.y;          // B's bottom past A's top

		// Pick the smallest positive overlap; that’s the contact side.
		// (Use <= to make ties stable.)
		int minX = (overlapLeft <= overlapRight) ? overlapLeft : overlapRight;
		int minY = (overlapTop <= overlapBottom) ? overlapTop : overlapBottom;

		if (minX < minY) {
			if (overlapLeft < overlapRight) return 4; // A hit B’s left side
			else return 2;                             // A hit B’s right side
		}
		else {
			if (overlapTop < overlapBottom) return 1; // A hit B’s top
			else return 3;                               // A hit B’s bottom
		}

		//if (recA.y + recA.h > recB.y) { std::cout << "Rec A: " << recA.y + recA.h << " " << "Rec B: " << recB.y << " " << recA.h << std::endl; }
		//std::cout << "Rec A:" << recA.x << " " << recA.y << "Rec B:" << recB.x << " " << recB.y << std::endl;
		return true;
	}
	return 0;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
	if (AABB(colA.collider, colB.collider)) {
		std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else {
		return false;
	}
}
