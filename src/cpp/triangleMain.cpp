
// #include <windows.h>
// #include <string>
// #include <iostream>
// //#include "d3dUtils.h"
// #include "cube.h"



// #define WINDOW_WIDTH	800							//为窗口宽度定义的宏，以方便在此处修改窗口宽度
// #define WINDOW_HEIGHT	600							//为窗口高度定义的宏，以方便在此处修改窗口高度

// HDC g_hdc=NULL;
// IDirect3DDevice9 *g_device = 0;

// IDirect3DVertexBuffer9 *triangle = 0;

// D3DXMATRIX World;//变换矩阵


// using namespace d3dutils;
// using namespace cube;


// void Cleanup()
// {
//     triangle->Release();
//     triangle = 0;
// }

// bool Setup()
// {
//     D3DXVECTOR3 dir(1.0f,0.0f,0.0f);
//     D3DCOLOR c = d3dutils::WHITE;
//     D3DLIGHT9 dirlight = InitDirectionallight(&dir,&c);

//     g_device->SetLight(0,&dirlight);
//     g_device->LightEnable(0,true);


//     CreateVertexBuffer(
//         g_device,
//         3 * sizeof(Vertex),
//         D3DUSAGE_WRITEONLY,
//         D3DPOOL_MANAGED,
//         &triangle
//     );

//     cube::Vertex *cvs;

//     triangle->Lock(0,0,(void**)&cvs,0);

//     cvs[0] = Vertex(-1.0f,0.0f,2.0f,D3DCOLOR_XRGB(255,0,0));
//     cvs[1] = Vertex(0.0f,1.0f,2.0f,D3DCOLOR_XRGB(0,255,0));
//     cvs[2] = Vertex(1.0f,0.0f,2.0f,D3DCOLOR_XRGB(0,0,255));

//     triangle->Unlock();

//     D3DXVECTOR3 position(0.0f,0.0f,-5.0f);

//     D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);

//     D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

//     D3DXMATRIX V;
//     D3DXMatrixLookAtLH(&V, &position, &target, &up);

//     g_device->SetTransform(D3DTS_VIEW,&V);

//     D3DXMATRIX proj;
//     D3DXMatrixPerspectiveFovLH(
//         &proj,
//         D3DX_PI * 0.5f,
//         (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT,
//         1.0f,
//         1000.0f
//     );
//     g_device->SetTransform(D3DTS_PROJECTION,&proj);
//     g_device->SetRenderState(D3DRS_LIGHTING,false);
//     return true;
// }


// bool Display(float timeDelta)
// {
// 	if( g_device )
// 	{		

//         // D3DXMATRIX rx,ry;
//         // D3DXMatrixRotationX(&rx,D3DX_PI/4.0f);
//         // static float y = 0.0f;
//         // D3DXMatrixRotationY(&ry,y);
//         // y+=timeDelta;
//         // if (y >= 6.28f)
//         // {   
//         //     y = 0.0f;
//         // }

//         // D3DXMATRIX p = rx * ry;
//         // g_device->SetTransform(D3DTS_WORLD,&p);

        
// 		g_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
// 		g_device->BeginScene();

//         g_device->SetFVF(cube::Vertex::FVF);
//         g_device->SetStreamSource(0,triangle,0,sizeof(Vertex));
//         //
//         D3DXMatrixTranslation(&World,-1.25f,0.0f,0.0f);
//         g_device->SetTransform(D3DTS_WORLD,&World);
//         g_device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT);//平面模式
//         g_device->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);

//         //
//         D3DXMatrixTranslation(&World,1.25f,0.0f,0.0f);
//         g_device->SetTransform(D3DTS_WORLD,&World);
//         g_device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);//gouraud模式
//         g_device->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);

// 		g_device->EndScene();
// 		g_device->Present(0, 0, 0, 0);
        
// 	}
// 	return true;
// }

// LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )      
// {
// 	PAINTSTRUCT paintStruct;			//定义一个PAINTSTRUCT结构体来记录一些绘制信息

// 	switch( message )						//switch语句开始
// 	{
// 	case WM_PAINT:						// 若是客户区重绘消息
// 		g_hdc = BeginPaint( hwnd, &paintStruct );  //指定窗口进行绘图工作的准备，并用将和绘图有关的信息填充到paintStruct结构体中。
// 		//Game_Paint( hwnd);
// 		EndPaint( hwnd, &paintStruct );			//EndPaint函数标记指定窗口的绘画过程结束
// 		ValidateRect(hwnd, NULL);		// 更新客户区的显示
// 		break;									//跳出该switch语句

// 	case WM_KEYDOWN:					// 若是键盘按下消息
// 		if (wParam == VK_ESCAPE)    // 如果被按下的键是ESC
// 			DestroyWindow(hwnd);		// 销毁窗口, 并发送一条WM_DESTROY消息
// 		break;									//跳出该switch语句

// 	case WM_DESTROY:					//若是窗口销毁消息
// 		//Game_CleanUp(hwnd);			//调用自定义的资源清理函数Game_CleanUp（）进行退出前的资源清理
// 		PostQuitMessage( 0 );			//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
// 		break;									//跳出该switch语句

// 	default:										//若上述case条件都不符合，则执行该default语句
// 		return DefWindowProc( hwnd, message, wParam, lParam );		//调用缺省的窗口过程
// 	}

// 	return 0;									//正常退出
// }


// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
// {

//     /*-------------------------------创建窗口----------------------------------*/
//     WNDCLASSEX wndClass = { 0 }; 
//     HWND hwnd = CreateWindows(hInstance,wndClass,WINDOW_WIDTH,WINDOW_HEIGHT,
//                     WndProc);

//     /* ------------------------------如何初始化Direct3D----------------------------------- */
//     if(!InitDirent3DDevice(hwnd,true,D3DDEVTYPE_HAL,WINDOW_WIDTH,WINDOW_HEIGHT,&g_device))
//     {
//         MessageBox(0,TEXT("InitD3D failed!"),0,0);
//         return 0;
//     }

//     if(!Setup())
// 	{
// 		::MessageBox(0, "Setup() - FAILED", 0, 0);
// 		return 0;
// 	}


//     //【5】消息循环过程
// 	MSG msg = { 0 };				//定义并初始化msg
//     static float lastTime = (float)timeGetTime(); 
// 	while( msg.message != WM_QUIT )		//使用while循环，如果消息不是WM_QUIT消息，就继续循环
// 	{
// 		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
// 		{
// 			TranslateMessage( &msg );		//将虚拟键消息转换为字符消息
// 			DispatchMessage( &msg );			//分发一个消息给窗口程序。
// 		}
//         else
//         {
//             float currTime  = (float)timeGetTime();
// 			float timeDelta = (currTime - lastTime)*0.001f;
//             Display(timeDelta);
//             lastTime = currTime;
//         }
// 	}

//     Cleanup();


//     g_device->Release();
// 	//【6】窗口类的注销
// 	UnregisterClass(TEXT("ForTheDreamOfGameDevelop"), wndClass.hInstance);  //程序准备结束，注销窗口类


//     //send();

    
//     return 0 ;
// }
