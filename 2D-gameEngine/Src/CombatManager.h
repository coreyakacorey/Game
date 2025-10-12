#include "ECS\ECS.h"

class CombatManager{
public:
  CombatManager(Manager* man);
  ~CombatManager();

  void Damage();

private:

  Manager* manager;
}
