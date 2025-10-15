#include "ECS\ECS.h"

class CombatManager{
public:
  CombatManager(Manager* man);
  ~CombatManager();

  void Damage(Entity* targetEnt, Entity* sourceEnt);

private:

  Manager* manager;
}
