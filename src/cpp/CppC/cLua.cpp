#include <cLua.h>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

cLua::cLua()
{
    m_pScriptContext = luaL_newstate();
    luaL_openlibs(m_pScriptContext);
};

cLua ::~cLua()
{
    lua_close(m_pScriptContext);
};
bool cLua ::RunScript(const char *pFileName)
{
    try
    {
        if (luaL_loadfile(m_pScriptContext, pFileName))
        {
            string s = "脚本读取错误";
            printf("lua %s \n", s.c_str());
            return false;
        }
        if (lua_pcall(m_pScriptContext, 0, 0, 0))
        {
            string s = "脚本运行错误";
            printf("lua %s \n", s.c_str());
            return false;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return true;
};

const char *cLua ::RunString(const char *pCommand)
{
    lua_getglobal(m_pScriptContext, pCommand);
    string s = lua_tostring(m_pScriptContext,-1);
    return s.c_str();
};

void cLua::RunLuaFuction(const char *pFuctionName)
{
    lua_getglobal(m_pScriptContext, pFuctionName);
    PushNumber(1000);
    PushString("a");
    PushString("b");
    PushString("c");
    PushString("d");
    if (lua_pcall(m_pScriptContext,5,0,0))
    {
        cout << "RunLuaFuction error!"<< endl;
        cout << lua_tostring(m_pScriptContext,-1) << endl;
    }
    
}

const char *cLua ::GetErrorString(void)
{
    return "error";
};
bool cLua ::AddFunction(const char *pFunctionName, LuaFuctionType pFunction)
{
    lua_register(m_pScriptContext, pFunctionName, pFunction);
    return false;
};
const char *cLua ::GetStringArgument(int num, const char *pDefault)
{
    return "";
};
double cLua ::GetNumberArgument(int num, double dDefault)
{
    return 0.0;
};
void cLua ::PushString(const char *pString){
    lua_pushstring(m_pScriptContext,pString);
};
void cLua ::PushNumber(double value){
    lua_pushnumber(m_pScriptContext,value);
};
