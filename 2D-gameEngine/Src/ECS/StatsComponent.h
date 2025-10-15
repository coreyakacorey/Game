#include "Components.h"

class HealthComponent : public Component {

public:
  int maxHealth;
  int curHealth;
  bool isAlive = true;

  HealthComponent(int maxH) {
    curHealth = maxHealth = maxH;
  }
  ~HealthComponent() {}

  void init() override {
    //Check for inital health changes based on onther stats
  }

  void update() override {
    //Change health based on game events

    if(curHealth <= 0){
      isAlive = false;
      entity->destory();
      //delete entity

    }
  }

private:
}
