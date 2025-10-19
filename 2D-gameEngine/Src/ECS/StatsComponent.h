#include "Components.h"

class StatsComponent : public Component {

public:
    int maxHealth;
    int curHealth;
    bool isAlive = true;
    int level;
    int exp;

    StatsComponent(int maxH) {
        curHealth = maxHealth = maxH;
    }
    StatsComponent(int maxH, int lvl) {
        curHealth = maxHealth = maxH;
        level = lvl;
    }
    StatsComponent(int maxH, int lvl, int ex) {
        curHealth = maxHealth = maxH;
        level = lvl;
        exp = ex;
    }
    ~StatsComponent() {}

    void init() override {
        //Check for inital health changes based on onther stats
    }

    void update() override {
        //Change health based on game events

        if (curHealth <= 0) {
            std::cout << "Deleting entity" << std::endl;
            isAlive = false;
            entity->destroy();
            //delete entity
        }
    }

private:
};
