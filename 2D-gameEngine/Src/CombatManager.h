#include "ECS\ECS.h"

class CombatManager{
public:
  CombatManager(Manager* man);
  ~CombatManager();

  void Damage(Entity* attEnt, Entity* defEnt);

private:

  Manager* manager;
}
