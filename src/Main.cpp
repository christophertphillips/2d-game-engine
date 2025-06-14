#include "./Game/Game.h"
// #include <sol/sol.hpp>
// #include <iostream>

// int nativeCppCubeFunction(int n){
//     return (n * n * n);
// }

// void LuaDemo() {
//     // This is how to create a Lua "virtual machine"
//     sol::state lua;

//     // This is how to make Lua libraries avilable to the Lua "virtual machine"
//     lua.open_libraries(sol::lib::base);

//     // This is how to expose and bind a native C++ function to be used by the Lua script
//     lua["cube"] = &nativeCppCubeFunction;

//     // This is how to run a Lua script using the Lua "virtual machine"
//     lua.script_file("./assets/scripts/LuaDemoScript.lua");

//     // This is how to get the value of a global variable from the Lua script
//     int someVariableInsideCpp = lua["some_variable"];
//     std::cout << "[C++] The value of the Lua variable some_variable in C++ is " << someVariableInsideCpp << std::endl;

//     // This is how to get the values from inside a Lua table
//     int isFullscreen = lua["config"]["fullscreen"];

//     // This is how to bring an entire Lua table into C++
//     sol::table config = lua["config"];
//     int width = config["resolution"]["width"];
//     int height = config["resolution"]["height"];
//     std::cout << "[C++] From a Lua table, we read the following values... fullscreen: " << isFullscreen << ", width: " << width << ", height: " << height << std::endl;

//     // This is how to invoke a Lua function from inside C++
//     sol::function functionFactorial = lua["factorial"];
//     int functionResult = functionFactorial(5);
//     std::cout << "[C++] The factorial of the numer 5 (via Lua) is calculated as " << functionResult << std::endl;
// }

int main(int argc, char* argv[]) {
    Game game;

    game.Initialize();
    game.Run();
    game.Destroy();

    // LuaDemo();

    return 0;
}
