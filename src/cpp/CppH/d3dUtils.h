#ifndef __D3DUTILS_H__
#define __D3DUTILS_H__
#include "E:\CnadLuaProject\include\d3d9.h"  
#include "E:\CnadLuaProject\include\d3dx9mesh.h"   
//#include <d3d9.h>
#include <string>


#define WINDOW_TITLE	TEXT("Direct3D学习")	//为窗口标题定义的宏

namespace d3dutils
{
    //创建窗口
    HWND CreateWindows(
        HINSTANCE hinstance,
        WNDCLASSEX wndClass,
        int width, int height,
        LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
    );

    //创建device
    bool InitDirent3DDevice(
        HWND hwnd,
        bool windowsType,
        D3DDEVTYPE deviceType,
        int width, int height,
        IDirect3DDevice9** device
    );

}


#endif