
#include <windows.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "cLua.h"
#include "d3dUtils.h"


//#pragma comment(lib,"E:/CnadLuaProject/lib/d3d9.lib")


#define WINDOW_WIDTH	932							//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define WINDOW_HEIGHT	700							//为窗口高度定义的宏，以方便在此处修改窗口高度

HDC g_hdc=NULL;
IDirect3DDevice9 *g_device = 0;

ID3DXMesh* Objects[5] = {0, 0, 0, 0, 0};

// World matrices for each object.  These matrices
// specify the locations of the objects in the world.
D3DXMATRIX ObjWorldMatrices[5];

using namespace std;
using namespace d3dutils;

LuaGlue _Version(lua_State *L)
{
    printf("This is Version 2.0 of the Console Program");
    lua_pushnumber(L,1000);
    return 1;
}

char gpCommandBuffer[254];
const char *GetCommand(void)
{
    printf("\nReady> \n");
    return gets(gpCommandBuffer);
    puts("\n");
}

void print(const char *str)
{
std:
    cout << str << endl;
}

void Cleanup()
{
	for(int i = 0; i < 5; i++)
    {
       // Objects[i]->Release();
    }
		
}

bool Setup()
{
	//
	// Create the objects.
	//

	D3DXCreateTeapot(
		g_device,
		&Objects[0],
		0);

	D3DXCreateBox(
		g_device,
		2.0f, // width
		2.0f, // height
		2.0f, // depth
		&Objects[1],
		0);

	// cylinder is built aligned on z-axis
	D3DXCreateCylinder(
		g_device,
		1.0f, // radius at negative z end
		1.0f, // radius at positive z end
		3.0f, // length of cylinder
		10,   // slices
		10,   // stacks
		&Objects[2],
		0);

	D3DXCreateTorus(
		g_device,
		1.0f, // inner radius
		3.0f, // outer radius
		10,   // sides
		10,   // rings
		&Objects[3],
		0);

	D3DXCreateSphere(
		g_device,
		1.0f, // radius
		10,   // slices
		10,   // stacks
		&Objects[4],
		0);

	//
	// Build world matrices - position the objects in world space.
	// For example, ObjWorldMatrices[1] will position Objects[1] at
	// (-5, 0, 5).  Likewise, ObjWorldMatrices[2] will position
	// Objects[2] at (5, 0, 5).
	//

	D3DXMatrixTranslation(&ObjWorldMatrices[0],  0.0f, 0.0f,  0.0f);
	D3DXMatrixTranslation(&ObjWorldMatrices[1], -5.0f, 0.0f,  5.0f);
	D3DXMatrixTranslation(&ObjWorldMatrices[2],  5.0f, 0.0f,  5.0f);
	D3DXMatrixTranslation(&ObjWorldMatrices[3], -5.0f, 0.0f, -5.0f);
	D3DXMatrixTranslation(&ObjWorldMatrices[4],  5.0f, 0.0f, -5.0f);

	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.5f, // 90 - degree
			(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
			1.0f,
			1000.0f);
	//g_device->SetTransform(D3DTS_PROJECTION, &proj);

	//
	// Switch to wireframe mode.
	//

	//g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return true;
}


bool Display(float timeDelta)
{
	if( g_device )
	{
		// // Animate the camera:
		// // The camera will circle around the center of the scene.  We use the
		// // sin and cos functions to generate points on the circle, then scale them
		// // by 10 to further the radius.  In addition the camera will move up and down
		// // as it circles about the scene.
		// static float angle = (3.0f * D3DX_PI) / 2.0f;
		// static float cameraHeight = 0.0f;
		// static float cameraHeightDirection = 5.0f;
		
		// D3DXVECTOR3 position( cosf(angle) * 10.0f, cameraHeight, sinf(angle) * 10.0f );

		// // the camera is targetted at the origin of the world
		// D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);

		// // the worlds up vector
		// D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

		// D3DXMATRIX V;
		// D3DXMatrixLookAtLH(&V, &position, &target, &up);
		// g_device->SetTransform(D3DTS_VIEW, &V);

		// // compute the position for the next frame
		// angle += timeDelta;
		// if( angle >= 6.28f )
		// 	angle = 0.0f;

		// // compute the height of the camera for the next frame
		// cameraHeight += cameraHeightDirection * timeDelta;
		// if( cameraHeight >= 10.0f )
		// 	cameraHeightDirection = -5.0f;

		// if( cameraHeight <= -10.0f )
		// 	cameraHeightDirection = 5.0f;

		//
		// Draw the Scene:
		//

		g_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
		//g_device->BeginScene();

		// for(int i = 0; i < 5; i++)
		// {
		// 	// Set the world matrix that positions the object.
		// 	g_device->SetTransform(D3DTS_WORLD, &ObjWorldMatrices[i]);

		// 	// Draw the object using the previously set world matrix.
		// 	Objects[i]->DrawSubset(0);
		// }

		//g_device->EndScene();
		g_device->Present(0, 0, 0, 0);
	}
	return true;
}




















//-----------------------------------【WndProc( )函数】--------------------------------------
//	描述：窗口过程函数WndProc,对窗口消息进行处理
//------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )      
{
	PAINTSTRUCT paintStruct;			//定义一个PAINTSTRUCT结构体来记录一些绘制信息

	switch( message )						//switch语句开始
	{
	case WM_PAINT:						// 若是客户区重绘消息
		g_hdc = BeginPaint( hwnd, &paintStruct );  //指定窗口进行绘图工作的准备，并用将和绘图有关的信息填充到paintStruct结构体中。
		//Game_Paint( hwnd);
		EndPaint( hwnd, &paintStruct );			//EndPaint函数标记指定窗口的绘画过程结束
		ValidateRect(hwnd, NULL);		// 更新客户区的显示
		break;									//跳出该switch语句

	case WM_KEYDOWN:					// 若是键盘按下消息
		if (wParam == VK_ESCAPE)    // 如果被按下的键是ESC
			DestroyWindow(hwnd);		// 销毁窗口, 并发送一条WM_DESTROY消息
		break;									//跳出该switch语句

	case WM_DESTROY:					//若是窗口销毁消息
		//Game_CleanUp(hwnd);			//调用自定义的资源清理函数Game_CleanUp（）进行退出前的资源清理
		PostQuitMessage( 0 );			//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		break;									//跳出该switch语句

	default:										//若上述case条件都不符合，则执行该default语句
		return DefWindowProc( hwnd, message, wParam, lParam );		//调用缺省的窗口过程
	}

	return 0;									//正常退出
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

    /*-------------------------------创建窗口----------------------------------*/
    WNDCLASSEX wndClass = { 0 }; 
    HWND hwnd = CreateWindows(hInstance,wndClass,WINDOW_WIDTH,WINDOW_HEIGHT,
                    WndProc);

    /* ------------------------------如何初始化Direct3D----------------------------------- */
    if(!InitDirent3DDevice(hwnd,true,D3DDEVTYPE_HAL,WINDOW_WIDTH,WINDOW_HEIGHT,&g_device))
    {
        MessageBox(0,TEXT("InitD3D failed!"),0,0);
        return 0;
    }

    if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}


    //【5】消息循环过程
	MSG msg = { 0 };				//定义并初始化msg
    static float lastTime = (float)timeGetTime(); 
	while( msg.message != WM_QUIT )		//使用while循环，如果消息不是WM_QUIT消息，就继续循环
	{
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage( &msg );		//将虚拟键消息转换为字符消息
			DispatchMessage( &msg );			//分发一个消息给窗口程序。
		}
        else
        {
            float currTime  = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;
            Display(timeDelta);
            lastTime = currTime;
        }
	}

   // Cleanup();


    g_device->Release();
	//【6】窗口类的注销
	UnregisterClass(TEXT("ForTheDreamOfGameDevelop"), wndClass.hInstance);  //程序准备结束，注销窗口类


    //send();

    
    return 0 ;
}


// Lua

void send()
{
    std::cout << _pgmptr << endl;
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath(_pgmptr,drive,dir,fname,ext);
    printf("a:%s,b:%s,c:%s,d:%s\n", drive, dir,fname, ext);

    print("Lua Console (c) 2004 Charles River Media");
    print("Enter Lua commands at the prompt");
    print("\"QUIT\" to exit\n");

    cLua *pLua = new cLua();
    pLua->AddFunction("Version", _Version);
    pLua->RunScript("lua/luaMain.lua"); //必须在执行文件一级 运行脚本
    const char *FromC = pLua->RunString("FromC");
    pLua->RunLuaFuction("Eventhandler");
    const char *pCommand = GetCommand();
    while (strcmp(pCommand, "QUIT") != 0)
    {
        if (!pLua->RunString(pCommand))
        {
            const char *str = pLua->GetErrorString();
            char error[254] = "ERROR:";
            try
            {
                strncat(error, str, strlen(str) + 1);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            cout << error << endl;
        }
        pCommand = GetCommand();
    }

    delete pLua;
    //system("pause");
}
