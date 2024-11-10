#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

// (the bitset defines (1) which components an entity has, and (2) which components a system is interested in)
const unsigned int MAX_COMPONENTS = 32;                                                 // define bitset length = 32 bits
typedef std::bitset<MAX_COMPONENTS> Signature;                                          // define 32-bit bitset type

struct IComponent{                                                                      // (base class containing shared 'counter' variable)
    protected:
        static int nextId;                                                              // (shared 'counter' used to assign ids to components)
};

class Entity{
    private:
        int id;																			// entity id

    public:
        Entity(int id): id(id) {};														// entity constructor
        int GetId() const;																// entity id getter
};

class System{
    private:
        Signature componentSignature;                                                   // signature indicating which components are required by the system
        std::vector<Entity> entities;                                                   // vector of entities associated with the system

    public:
        System() = default;                                                             // System constructor
        ~System() = default;                                                            // System destructor
        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;                                  // get vector of entities
        Signature& GetComponentSignature() const;                                       // get reference to component signature
};

class Registry{

};

#endif
