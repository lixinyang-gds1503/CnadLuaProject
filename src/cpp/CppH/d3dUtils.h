#ifndef __D3DUTILS_H__
#define __D3DUTILS_H__
#include "E:\CnadLuaProject\include\d3d9.h"
#include "E:\CnadLuaProject\include\d3dx9mesh.h"
//#include <d3d9.h>
#include <string>

#define WINDOW_TITLE TEXT("Direct3D学习") //为窗口标题定义的宏

namespace d3dutils
{
    static D3DCAPS9 g_caps;
    //颜色
    const D3DCOLOR WHITE(D3DCOLOR_XRGB(255, 255, 255));
    const D3DCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));
    const D3DCOLOR RED(D3DCOLOR_XRGB(255, 0, 0));
    const D3DCOLOR GREEN(D3DCOLOR_XRGB(0, 255, 0));
    const D3DCOLOR BLUE(D3DCOLOR_XRGB(0, 0, 255));
    const D3DCOLOR YELLOW(D3DCOLOR_XRGB(255, 255, 0));
    const D3DCOLOR CYAN(D3DCOLOR_XRGB(0, 255, 255));
    const D3DCOLOR MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

    //创建窗口
    HWND CreateWindows(
        HINSTANCE hinstance,
        WNDCLASSEX wndClass,
        int width, int height,
        LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam));

    //创建device
    bool InitDirent3DDevice(
        HWND hwnd,
        bool windowsType,
        D3DDEVTYPE deviceType,
        int width, int height,
        IDirect3DDevice9 **device);

    //设置材质 反光率
    D3DMATERIAL9 InitMtrl(
        D3DXCOLOR a,
        D3DXCOLOR d,
        D3DXCOLOR s,
        D3DXCOLOR e,
        float p);
    
    const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE,WHITE,WHITE,BLACK,8.0f);
    const D3DMATERIAL9 RED_MTRL = InitMtrl(RED,RED,RED,BLACK,8.0f);
    const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN,GREEN,GREEN,BLACK,8.0f);
    const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE,BLUE,BLUE,BLACK,8.0f);
    const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW,YELLOW,YELLOW,BLACK,8.0f);


    //光源
    D3DLIGHT9 InitDirectionallight(D3DXVECTOR3 *direction,D3DXCOLOR *color);// 平行光源
    D3DLIGHT9 InitPointlight(D3DXVECTOR3 *position,D3DXCOLOR *color);// 点光源
    D3DLIGHT9 InitSpotlight(D3DXVECTOR3 *position,D3DXVECTOR3 *direction,D3DXCOLOR *color);// 聚光灯光源


}

#endif