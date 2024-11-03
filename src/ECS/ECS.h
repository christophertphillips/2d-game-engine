#ifndef ECS_H
#define ECS_H

#include <bitset>

// (the bitset defines (1) which components an entity has, and (2) which components a system is interested in)
const unsigned int MAX_COMPONENTS = 32;                                                 // define bitset length = 32 bits
typedef std::bitset<MAX_COMPONENTS> Signature;                                          // define 32-bit bitset type

class Component{

};

class Entity{
    private:
        int id;																			// entity id

    public:
        Entity(int id): id(id) {};														// entity constructor
        int GetId() const;																// entity id getter
};

class System{

};

class Registry{

};

#endif
