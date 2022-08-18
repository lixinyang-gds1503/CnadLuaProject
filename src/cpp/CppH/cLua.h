
#ifndef CLUA_H
#include <stddef.h>

struct lua_State;
#define LuaGlue extern "C" int
extern "C"{
    typedef int (*LuaFuctionType)(struct lua_State * pLuaState);
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
    #include "lua.hpp"
};

//#ifdef _WIN32
//#pragma comment(lib,"lib/liblua.a")
//#endif


#define CLUA_H


class cLua 
{
private:
    lua_State * m_pScriptContext;
public:
    cLua();
    virtual ~cLua();
    bool RunScript(const char *pFileName);
    const char *RunString(const char *pCommand);
    void RunLuaFuction(const char *pFuctionName);

    const char *GetErrorString(void);
    bool AddFunction(const char *pFunctionName,LuaFuctionType pFunction);
    const char *GetStringArgument(int num,const char *pDefault = NULL);
    double GetNumberArgument(int num,double dDefault = 0.0);
    void PushString(const char *pString);
    void PushNumber(double value);
};

#endif