#ifndef ECS_H
#define ECS_H

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
