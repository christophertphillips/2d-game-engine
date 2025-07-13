#ifndef SCRIPTCOMPONENT
#define SCRIPTCOMPONENT

#include <sol/sol.hpp>

struct ScriptComponent {
    sol::function func;

    ScriptComponent(sol::function func = sol::lua_nil){
        this->func = func;
    }
};

#endif
