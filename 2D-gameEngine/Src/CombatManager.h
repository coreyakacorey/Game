#include "ECS\ECS.h"
#include "ECS\Components.h"

class CombatManager {

	struct Health: public Component { 
		int cur;
		explicit Health(int hp) : cur(hp) {}
	};

public:
	CombatManager(Manager* man);
	~CombatManager();

	void queueHit(Entity* targetEnt, Entity* sourceEnt, Entity* attackEnt, int damage);
	void endOfFrameResolve();

private:
	struct Hit { Entity* target; Entity* source; Entity* attackEnt; int amount; };
	Manager* manager;
	std::vector<Hit> hits;
};
