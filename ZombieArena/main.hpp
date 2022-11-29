
#ifndef main_hpp
#define main_hpp
#include "zombie.hpp"

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena);
Zombie* createHorde(int numZombies, IntRect arena);

#endif
