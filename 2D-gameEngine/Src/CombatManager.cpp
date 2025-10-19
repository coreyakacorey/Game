#include "CombatManager.h"

CombatManager::CombatManager(Manager* man) : manager(man){}

//CombatManager::~CombatManager();

void CombatManager::queueHit(Entity* targetEnt, Entity* sourceEnt, Entity* attackEnt ,int damage) {
	if (!targetEnt)return;
	if (!targetEnt->isActive())return;
	hits.push_back({ targetEnt, sourceEnt, attackEnt, damage });
}

void CombatManager::endOfFrameResolve() {
	for (const auto& h : hits) {
		if (!h.target || !h.target->isActive()) continue;
		if (!h.target->hasComponent<StatsComponent>()) {
			h.attackEnt->getComponent<StatsComponent>().exp += h.target->getComponent<StatsComponent>().exp;
			continue;
		}

		auto& hp = h.target->getComponent<StatsComponent>();
		hp.curHealth -= h.amount;

		if (h.source && h.source->isActive()) {
			h.source->destroy();
		}
	}
       
    hits.clear();
}