#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>
#include "../Logger/Logger.h"
#include <deque>

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Component

// (the bitset defines (1) which components an entity has, and (2) which components a system is interested in)
const unsigned int MAX_COMPONENTS = 32;                                                 // define bitset length = 32 bits
typedef std::bitset<MAX_COMPONENTS> Signature;                                          // define 32-bit bitset type

struct IComponent{                                                                      // (base class containing shared 'counter' variable)
    protected:
        static int nextId;                                                              // (shared 'counter' used to assign ids to components)
};

template <typename T>
class Component: public IComponent{                                                     // (inherit from IComponent to access shared "counter" variable)
    public:
        static int GetId(){
            static auto id = nextId++;                                                  // use "counter" to assign id to component
            return id;                                                                  // (using static ensures that the id is only initialized once and thus never changes)
        }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Entity

class Entity{
    private:
        int id;																			// entity id

    public:
        Entity(int id): id(id) {};														// entity constructor
        Entity(const Entity& entity) = default;                                         // entity copy constructor
        int GetId() const;																// entity id getter
        void KillEntity();                                                              // remove entity from registry
        Entity& operator =(const Entity& other) = default;                              // overload copy assignment operator
        bool operator ==(const Entity& other) const { return id == other.id; }          // overload equality to test entity equality
        bool operator !=(const Entity& other) const { return id != other.id; }          // overload non-equality to test entity non-equality
        bool operator  >(const Entity& other) const { return id > other.id; }           // overload greater-than to test entity greater-than-ness
        bool operator  <(const Entity& other) const { return id < other.id; }           // overload less-than to test entity less-than-ness
        class Registry* registry;                                                       // pointer to registry object (to access registry methods via entity)
                                                                                        // (note that forward declaration is needed since Registry class is defined later)
        template <typename T, typename ...TArgs> void AddComponent(TArgs&& ...args);    // add component of type T and args of types TArgs
        template <typename T> void RemoveComponent();                                   // remove component of type T
        template <typename T> bool HasComponent() const;                                // determine if component of type T is present
        template <typename T> T& GetComponent() const;                                  // get component of type T
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// System

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

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pool

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

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Registry

class Registry{
    private:
        int numEntities = 0;                                                            // how many entities we have in our world
        // (componentPools index = component id, Pool index = entity ID)
        std::vector<std::shared_ptr<IPool>> componentPools;                             // vector containing pointers to all component pools
        // (entityComponentSignature index = entity id)
        std::vector<Signature> entityComponentSignatures;                               // vector containing component signatures per entity
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;           // unordered map containing pointers to systems
        std::set<Entity> entitiesToBeAdded;                                             // set containing entities to be added at end of frame
        std::set<Entity> entitiesToBeKilled;                                            // set containing entities to be killed at end of frame
        std::unordered_map<std::string, Entity> tagToEntity;                            // unordered map mapping tag to entity
        std::unordered_map<int, std::string> entityToTag;                               // unordered map mapping entity (ID) to tag
        std::unordered_map<std::string, std::set<Entity>> groupToEntities;              // unordered map mapping group to (set of) entities
        std::unordered_map<int, std::string> entityToGroup;                             // unordered map mpaping entity (ID) to group
        std::deque<int> freeEntityIds;                                                  // deque of previously-used entity ids that are available for reuse

    public:
        Registry(){                                                                     // registry constructor
            Logger::Log("Registry constructor called!");
        };
        ~Registry(){                                                                    // registry destructor
            Logger::Log("Registry destructor called!");
        };
        Entity CreateEntity();                                                          // create entity, add to entitiesToBeAdded, and return copy
        void KillEntity(Entity entity);                                                 // remove entity from registry
        template <typename T, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args); // add component of type T and args of types TArgs to specified entity
        template <typename T> void RemoveComponent(Entity entity);                      // remove component of type T from specified entity
        template <typename T> bool HasComponent(Entity entity) const;                   // determine if specified entity has component of type T
        template <typename T> T& GetComponent(Entity entity) const;                     // get component of type T from specified entity
        template <typename T, typename ...TArgs> void AddSystem(TArgs&& ...args);       // add system of type T and args of type TArgs to systems unordered map
        template <typename T> void RemoveSystem();                                      // remove system of type T from systems undordered map
        template <typename T> bool HasSystem() const;                                   // determine if systems unordered map has system of type T
        template <typename T> T& GetSystem() const;                                     // get system of type T from systems unordered map
        void AddEntityToSystems(Entity entity);                                         // add entity to *all* systems that are interested in that entity
        void RemoveEntityFromSystems(Entity entity);                                    // remove entity from all systems
        void Update();                                                                  // add/remove entities waiting to be added/removed
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Method templates

// ------------------------------------------------------------------------------------------------
// Entity method templates

// (templates are implemented in the header file)
template <typename T, typename ...TArgs>
void Entity::AddComponent(TArgs&& ...args){                                             // add component of type T and args of types TArgs
    registry->AddComponent<T>(*this, std::forward<TArgs>(args)...);                     // call Registry::AddComponent()
}

template <typename T>
void Entity::RemoveComponent(){                                                         // remove component of type T
    registry->RemoveComponent<T>(*this);                                                // call Registry::RemoveComponent()
}

template <typename T>
bool Entity::HasComponent() const{                                                      // determine if component of type T is present
    return registry->HasComponent<T>(*this);                                            // call Registry::HasComponent()
}

template <typename T>
T& Entity::GetComponent() const{                                                        // get component of type T
    return registry->GetComponent<T>(*this);                                            // call Registry::GetComponent()
}

// ------------------------------------------------------------------------------------------------
// System method templates

template <typename T>
void System::RequireComponent(){
    const auto componentId = Component<T>::GetId();                                     // get id associated with component to require
    componentSignature.set(componentId);                                                // toggle bit corresponding to component id
}

// ------------------------------------------------------------------------------------------------
// Registry method templates

template <typename T, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args){                            // add component of type T and args of types TArgs to specified entity
    const auto componentId = Component<T>::GetId();                                     // get id associated with component type T
    const auto entityId = entity.GetId();                                               // get entity id

    if(componentId >= componentPools.size()){                                           // if component type can't fit in componentPools...
        componentPools.resize(componentId + 1, nullptr);                                // ... increase componentPool size by 1
    }

    if(!componentPools[componentId]){                                                   // if componentPools doesn't have a pointer to a pool for the specified component...
        std::shared_ptr<Pool<T>> newComponentPool = std::make_shared<Pool<T>>();        // ... create a new pool...
        componentPools[componentId] = newComponentPool;                                 // ... and assign its pointer to the relevant componentPools vector index
    }

    std::shared_ptr<Pool<T>> componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);    // get component pool associated with component id

    if(entityId >= componentPool->GetSize()){                                           // if component pool isn't big enough to accomodate entity...
        componentPool->Resize(numEntities);                                             // ... increase size of component pool to match # of entities
    }

    T newComponent(std::forward<TArgs>(args)...);                                       // create new component of type T on stack, forwarding component args
    componentPool->Set(entityId, newComponent);                                         // set component at specified entity index in componentPool
    entityComponentSignatures[entityId].set(componentId);                               // set component bit to 1 in entity's component signature bitset

    Logger::Log("Component id = " + std::to_string(componentId) + " was added to entity id = " + std::to_string(entityId));
}

template <typename T>
void Registry::RemoveComponent(Entity entity){                                          // remove component of type T from specified entity
    const auto componentId = Component<T>::GetId();                                     // get id associated with component type T
    const auto entityId = entity.GetId();                                               // get entity id

    entityComponentSignatures[entityId].set(componentId, false);                        // set component bit to 0 in entity's component signature bitset
}

template <typename T>
bool Registry::HasComponent(Entity entity) const{
    const auto componentId = Component<T>::GetId();                                     // get id associated with component type T
    const auto entityId = entity.GetId();                                               // get entity id

    return entityComponentSignatures[entityId].test(componentId);                       // return bool result of testing component's bit in entity's component signature bitset
}

template <typename T>
T& Registry::GetComponent(Entity entity) const{
    const auto componentId = Component<T>::GetId();                                     // get id associated with component type T
    const auto entityId = entity.GetId();                                               // get entity id

    auto componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);    // get component pool associated with component id
    return componentPool->Get(entityId);                                                // return component (associated with specified entity)
}

template <typename T, typename ...TArgs>
void Registry::AddSystem(TArgs&& ...args){                                              // add system of type T and args of type TArgs to systems unordered map
    std::shared_ptr<T> newSystem = std::make_shared<T>(std::forward<TArgs>(args)...);   // create new system of type T on heap, forwarding component args
    systems.insert(std::make_pair(std::type_index(typeid(T)), newSystem));              // insert pointer to new system in systems unordered map at (type_index(T), newSystem*)
}

template <typename T>
void Registry::RemoveSystem(){                                                          // remove system of type T from systems undordered map
    auto systemsIterator = systems.find(std::type_index(typeid(T)));                    // get iterator pointing to system of type T in the systems unordered map
    systems.erase(systemsIterator);                                                     // remove system of type T from the systems unordered map
}

template <typename T>
bool Registry::HasSystem() const{                                                       // determine if systems unordered map has system of type T
    return systems.find(std::type_index(typeid(T))) != systems.end();                   // return bool result of comparing find iterator to iterator pointing to end of systems unordered map 
}

template <typename T>
T& Registry::GetSystem() const{                                                         // get system of type T from systems unordered map
    auto systemsIterator = systems.find(std::type_index(typeid(T)));                    // get iterator pointing to system of type T in the systems unordered map
    return *(std::static_pointer_cast<T>(systemsIterator->second));                     // return system of type T from unordered map (via value of iterator and dereference operation)
}

#endif
