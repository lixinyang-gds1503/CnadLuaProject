// 文本

#include <windows.h>
#include <string>
#include <iostream>
#include <cstring>
//#include "d3dUtils.h"
#include "cube.h"



#define WINDOW_WIDTH	800							//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define WINDOW_HEIGHT	600							//为窗口高度定义的宏，以方便在此处修改窗口高度

HDC g_hdc=NULL;
IDirect3DDevice9 *g_device = 0;

using namespace d3dutils;
using namespace cube;
using namespace std;

DWORD FrameCnt;
FLOAT TimeElapsed;
FLOAT FPS;

ID3DXMesh *text= 0;
ID3DXFont *mFont = 0;

RECT rect;


//计算FPS
void CalcFps(float timeDelta)
{
    FrameCnt++;
    TimeElapsed += timeDelta;
    if (TimeElapsed >= 1.0f)
    {
        FPS = (float) FrameCnt / TimeElapsed;
        TimeElapsed = 0.0f;
        FrameCnt = 0;
    }
    
}


void Cleanup()
{
    text->Release();
    mFont->Release();
}

void getFilePath(char *filepath)
{
     //获取应用路径
    char exe_buff[MAX_PATH];
    GetModuleFileName(NULL,exe_buff,MAX_PATH);
    char *p = strtok(exe_buff,"\\");
    string s ="";
    while (p != 0)
    {
        string m(p);
        if (m != "mian.exe")
        {
            s += m;
            s += "/";
        }

        p = strtok(NULL, "\\");
    }
    delete[] p;
    s += "src/img/crate.jpg";
    const char *strp = s.c_str();
    strcpy(filepath,strp);
    delete[] strp;
}

bool Setup()
{
    g_device->SetRenderState(D3DRS_LIGHTING,false);//光源

    //设置光源
    D3DXVECTOR3 dir(0.0f, -1.0f, 0.0f);
    D3DXCOLOR c = WHITE;
    D3DLIGHT9 dirlight = InitDirectionallight(&dir, &c);
    dirlight.Diffuse = c;
    dirlight.Specular = c * 0.3f;
    dirlight.Ambient = c * 0.6f;
    g_device->SetLight(0, &dirlight);
    g_device->LightEnable(0, true);


    g_device->SetRenderState(D3DRS_NORMALIZENORMALS, true); //从新计算法线
    g_device->SetRenderState(D3DRS_SPECULARENABLE, true);   //打开镜面光

    char filepath[MAX_PATH] = {}; 
    getFilePath(filepath);

    HDC hdc = CreateCompatibleDC(NULL);
    HFONT hFont;
    HFONT hFontOld;

    LOGFONT logf;
    ZeroMemory(&logf,sizeof(LOGFONT));
    logf.lfHeight = 25;
    logf.lfWidth = 12;
    logf.lfEscapement = 0;
    logf.lfWeight = FW_MEDIUM;
    logf.lfItalic = false;//字体是否是斜体
    logf.lfUnderline = false;// 下划线
    logf.lfStrikeOut = false;// 字体是否有删除线
    logf.lfCharSet = DEFAULT_CHARSET;
    logf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    logf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    logf.lfQuality = PROOF_QUALITY;
    logf.lfPitchAndFamily = DEFAULT_PITCH;
    strcpy(logf.lfFaceName,"Times New Roman");

    hFont =  CreateFontIndirect(&logf);
    hFontOld = (HFONT) SelectObject(hdc,hFont);

    D3DXCreateText(g_device,hdc,"Hello,world!",0.001f,0.4f,&text,0,0);

    D3DXCreateFont(g_device,25,12,0,0,false,0,0,2,0,"Times New Roman",&mFont);

    rect.left = 0;
    rect.top = 0;
    rect.right = 100;
    rect.bottom = 100;

    //
	// Restore the old font and free the acquired HDC.
	//
    SelectObject(hdc, hFontOld);
    DeleteObject( hFont );
    DeleteDC( hdc );


    D3DXVECTOR3 position(0.0f,0.0f,-5.0f);

    D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);

    D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

    D3DXMATRIX V;
    D3DXMatrixLookAtLH(&V, &position, &target, &up);

    g_device->SetTransform(D3DTS_VIEW,&V);

    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(
        &proj,
        D3DX_PI * 0.5f,
        (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT,
        1.0f,
        1000.0f
    );
    g_device->SetTransform(D3DTS_PROJECTION,&proj);
    
    return true;
}


bool Display(float timeDelta)
{
	if( g_device )
	{		

        
        //                        后背               //深度             //模板
		g_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xff0000ff, 1.0f, 0);
		g_device->BeginScene();

        CalcFps(timeDelta);

        g_device->SetMaterial(&WHITE_MTRL);
        text->DrawSubset(0);
        char cfps[20];
        sprintf(cfps,"%.2f",FPS);
        mFont->DrawText(0,TEXT(cfps),-1,&rect,DT_LEFT|DT_TOP,0xff000000);


		g_device->EndScene();
		g_device->Present(0, 0, 0, 0);
        
	}
	return true;
}

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

    Cleanup();


    g_device->Release();
	//【6】窗口类的注销
	UnregisterClass(TEXT("ForTheDreamOfGameDevelop"), wndClass.hInstance);  //程序准备结束，注销窗口类
    
    return 0 ;
}
