print("luaMian.lua")

FromC = Version();--C++

print("\n")
print("Lua: FromC is ",FromC)
print("\n")

EVENT_SAMPLE = 1000

--RegisterEvent("EventHandler")

function Eventhandler(id,...)
    print(string.format("id = %d \n",id))
    local arg = {...}
    for index,value in ipairs(arg)  do
        print(string.format("arg[%d] = ",index))
        print(arg[index])
        print("\n")
    end
    if id == EVENT_SAMPLE then
        print("Sample event!")
    end
end





