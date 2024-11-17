#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

// (the bitset defines (1) which components an entity has, and (2) which components a system is interested in)
const unsigned int MAX_COMPONENTS = 32;                                                 // define bitset length = 32 bits
typedef std::bitset<MAX_COMPONENTS> Signature;                                          // define 32-bit bitset type

struct IComponent{                                                                      // (base class containing shared 'counter' variable)
    protected:
        static int nextId;                                                              // (shared 'counter' used to assign ids to components)
};

template <typename T>
class Component: public IComponent{                                                     // (inherit from IComponent to access shared "counter" variable)
    static int GetId(){
        static auto id = nextId++;                                                      // use "counter" to assign id to component
        return id;                                                                      // (using static ensures that the id is only initialized once and thus never changes)
    }
};

class Entity{
    private:
        int id;																			// entity id

    public:
        Entity(int id): id(id) {};														// entity constructor
        Entity(const Entity& entity) = default;                                         // entity copy constructor
        int GetId() const;																// entity id getter
        Entity& operator =(const Entity& other) = default;                              // overload copy assignment operator
        bool operator ==(const Entity& other) const { return id == other.id; }          // overload equality to test entity equality
        bool operator !=(const Entity& other) const { return id == other.id; }          // overload non-equality to test entity non-equality
        bool operator  >(const Entity& other) const { return id == other.id; }          // overload greater-than to test entity greater-than-ness
        bool operator  <(const Entity& other) const { return id == other.id; }          // overload less-than to test entity less-than-ness
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
        const Signature& GetComponentSignature() const;                                 // get reference to component signature
        template <typename T> void RequireComponent();                                  // defines component required by the system
};

class IPool{                                                                            // (base class used to allow creation of componentPool w/o specifying T)
    public:
        virtual ~IPool() {}
};

template <typename T>
class Pool: public IPool{
    private:
        std::vector<T> data;                                                            // vector that is "wrapped" by the Pool class

    public:
        Pool(int size = 100){                                                           // default pool size = 100
            data.resize(size);
        }

        virtual ~Pool() = default;                                                      // (virtual is probably unnecessary here)

        bool IsEmpty() const {
            return data.empty();                                                        // return pool "emptiness" value
        }

        int GetSize() const {
            return data.size();                                                         // return size of pool
        }

        void Resize(int n) {
            data.resize(n);                                                             // resize pool
        }

        void Clear(){
            data.clear();                                                               // clear data from pool
        }

        void Add(T object){
            data.push_back(object);                                                     // add object to pool
        }

        void Set(int index, T object){
            data[index] = object;                                                       // set object at specified pool index
        }

        T& Get(int index){
            return static_cast<T&>(data[index]);                                        // return object at specified pool index
        }                                                                               // (static cast is probably unnecessary here)

        T& operator [](unsigned int index){
            return data[index];                                                         // return object at specified pool index
        }
};

class Registry{
    private:
        int numEntities = 0;                                                            // how many entities we have in our world
        // (componentPools index = component id, Pool index = entity ID)
        std::vector<IPool*> componentPools;                                             // vector containing pointers to all component pools
        // (entityComponentSignature index = entity id)
        std::vector<Signature> entityComponentSignatures;                               // vector containing component signatures per entity
        std::unordered_map<std::type_index, System*> systems;                           // unordered map containing pointers to systems
        std::set<Entity> entitiesToBeAdded;                                             // set containing entities to be added at end of frame
        std::set<Entity> entitiesToBeKilled;                                            // set containing entities to be killed at end of frame

    public:
        Registry() = default;
};

// (templates are implemented in the header file)
template <typename T>
void System::RequireComponent(){
    const auto componentId = Component<T>::GetId();                                     // get id associated with component to require
    componentSignature.set(componentId);                                                // toggle bit corresponding to component id
}

#endif
