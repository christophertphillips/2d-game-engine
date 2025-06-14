--This is a Lua global variable
some_variable = 3 ^ (5 * 2)

--This is a Lua table that contains values for the initialization of our game engine
config = {
    title = "My Game Engine",
    fullscreen = false,
    resolution = {
        width = 800,
        height = 600
    }
}

-- This is a Lua function that calculates the factorial of a given number
function factorial(n)
    if (n == 1) then
        return 1
    else
        return n * factorial(n - 1)
    end
end

-- This is how to invoke a native C++ function inside Lua
print("[Lua] The cube of the number 3 (via native C++) is calculated as " .. cube(3))
