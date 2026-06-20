// Projekt 1: Textbaserat Rollspel (Arena Fighter)

#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Character {
private:
    int health;
    int attackValue;
    std::string name;

public:

    Character(std::string charName, int charAttack, int charHealth) : name(charName), attackValue(charAttack), health(charHealth)  {}

    int getHealth() const { return health; }

    std::string getName() const { return name; }

    int getAttack() const { return attackValue; }

    int setAttack(int newAttack) { return  attackValue = newAttack; }

    virtual void attack() {}

    virtual void specialevent() {}

    void takeDamage(int damage) {
        health -= damage;
    }

    bool isDead() const { 

        if (health <= 0) {
            std::cout << name << " is Dead!" << std::endl;
            return true;
        }

        return false;
     }


};

class Player : public Character {
public:

    Player(std::string playName, int playAttack, int playHealth) : Character(playName, playAttack, playHealth) {}    

    void attack() override { 
        std::cout << "Player attacked for " << getAttack() << " damage." << std::endl;
    }

};

class Enemy : public Character {
public:

    Enemy(std::string enemName, int enemAttack, int enemHealth) : Character(enemName, enemAttack, enemHealth) {}


    void attack() override { 
        std::cout << getName() << " attacked for " << getAttack() << " damage." << std::endl;
    }

};

class Boss : public Character {
public:

    Boss(std::string bossName, int bossAttack, int bossHealth) : Character(bossName, bossAttack, bossHealth) {}


    void attack() override { 
        std::cout << "Bolin attacked for " << getAttack() << " damage." << std::endl;
    }

    void specialevent() override {
        if (getHealth() < 20) {
            setAttack(getAttack() * 2);
            std::cout << getName() << " gets enraged! Attack doubled!" << std::endl;
        }
    }

};

int main() {

    std::unique_ptr<Player> Rillard = std::make_unique<Player>("Rillard", 60, 70);

    std::vector<std::unique_ptr<Character>> enemies;

    enemies.push_back(std::make_unique<Enemy>("Grunt", 10, 50));
    enemies.push_back(std::make_unique<Boss>("Bolin", 30, 72));

    std::cout << std::endl;
    std::cout << Rillard->getName() << " challenges the Arena!" << std::endl;
    std::cout << "Health: " << Rillard->getHealth() << std::endl;
    std::cout << "Attack: " << Rillard->getAttack() << std::endl;

    std::cin.get();
    
    std::cout << std::endl;
    std::cout << enemies.front()->getName() << " has appeared!" << std::endl;
    std::cout << "Health: " << enemies.front()->getHealth() << std::endl;
    std::cout << "Attack: " << enemies.front()->getAttack() << std::endl;
    std::cin.get();

    while (Rillard->getHealth() > 0 && enemies.empty() == 0) {

        
        

        std::cout << std::endl;

        Rillard->attack();
        enemies.front()->takeDamage(Rillard->getAttack());
        std::cout << enemies.front()->getName() << " has " << enemies.front()->getHealth() << " health remaining." << std::endl;
        enemies.front()->specialevent();

        if (enemies.front()->isDead() == true) {
            std::cout << "Congratulations! You slayed " << enemies.front()->getName() << ". Remaining health: " << Rillard->getHealth() << std::endl;
            std::cout << std::endl;
            std::cin.get();
            enemies.erase(enemies.begin());

            if (enemies.empty() == 0) {
                std::cout << enemies.front()->getName() << " has appeared!" << std::endl;
                std::cout << "Health: " << enemies.front()->getHealth() << std::endl;
                std::cout << "Attack: " << enemies.front()->getAttack() << std::endl;
            }

            std::cin.get();

            continue;

        }


        std::cin.get();

        enemies.front()->attack();
        Rillard->takeDamage(enemies.front()->getAttack());
        std::cout << Rillard->getName() << " has " << Rillard->getHealth() << " health remaining." << std::endl;
        std::cin.get();
        if (Rillard->isDead() == true) {
            std::cout << "You have Died!" << std::endl;
            break;
        }


    }
        

}