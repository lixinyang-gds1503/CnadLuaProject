#include "d3dUtils.h"

HWND d3dutils::CreateWindows(
    HINSTANCE hinstance,
    WNDCLASSEX wndClass,
    int width, int height,
    LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam))
{
    //【1】窗口创建四步曲之一：开始设计一个完整的窗口类
    // WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
    wndClass.cbSize = sizeof(WNDCLASSEX);                                                                            //设置结构体的字节数大小
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                                                        //设置窗口的样式
    wndClass.lpfnWndProc = WndProc;                                                                                  //设置指向窗口过程函数的指针
    wndClass.cbClsExtra = 0;                                                                                         //窗口类的附加内存，取0就可以了
    wndClass.cbWndExtra = 0;                                                                                         //窗口的附加内存，依然取0就行了
    wndClass.hInstance = hinstance;                                                                                  //指定包含窗口过程的程序的实例句柄。
    wndClass.hIcon = (HICON)::LoadImage(NULL, TEXT("icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); //本地加载自定义ico图标
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                                                  //指定窗口类的光标句柄。
    wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);                                                    //为hbrBackground成员指定一个白色画刷句柄
    wndClass.lpszMenuName = NULL;                                                                                    //用一个以空终止的字符串，指定菜单资源的名字。
    wndClass.lpszClassName = TEXT("ForTheDreamOfGameDevelop");                                                       //用一个以空终止的字符串，指定窗口类的名字。

    //【2】窗口创建四步曲之二：注册窗口类
    if (!RegisterClassEx(&wndClass)) //设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
        return nullptr;

    //【3】窗口创建四步曲之三：正式创建窗口
    HWND _hwnd = CreateWindow(TEXT("ForTheDreamOfGameDevelop"), WINDOW_TITLE, //喜闻乐见的创建窗口函数CreateWindow //WS_OVERLAPPEDWINDOW //WS_EX_TOPMOST | WS_POPUP
                              WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width,
                              height, NULL, NULL, hinstance, NULL);

    if (_hwnd)
    {
        //【4】窗口创建四步曲之四：窗口的移动、显示与更新
        MoveWindow(_hwnd, 200, 20, width, height, true); //调整窗口显示时的位置，使窗口左上角位于（200,20）处
        ShowWindow(_hwnd, SW_SHOW);                      //调用ShowWindow函数来显示窗口
        UpdateWindow(_hwnd);                             //对窗口进行更新，就像我们买了新房子要装修一样
        return _hwnd;
    }
    else
    {
        return nullptr;
    }
}

bool d3dutils::InitDirent3DDevice(
    HWND hwnd,
    bool windowsType,
    D3DDEVTYPE deviceType,
    int width, int height,
    IDirect3DDevice9 **device)
{
    IDirect3D9 *_d3d9;
    _d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
    if (_d3d9 != nullptr)
    {
        //D3DCAPS9 caps;
        //获取显卡设备信息
        _d3d9->GetDeviceCaps(
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE::D3DDEVTYPE_HAL,
            &g_caps);

        //设置硬件加速
        int vp = 0;
        if (g_caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
        {
            vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
        }
        else
        {
            vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
        }
        //填充D3DPRESENT_PARAMENTERS对象
        D3DPRESENT_PARAMETERS d3dpp;
        d3dpp.BackBufferWidth = width;
        d3dpp.BackBufferHeight = height;

        D3DDISPLAYMODE pMode;
        if (FAILED(_d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &pMode)))
        {
            return FALSE;
        }

        d3dpp.BackBufferFormat = pMode.Format; //像素格式
        d3dpp.BackBufferCount = 1;
        d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; // 多重采样级别
        d3dpp.MultiSampleQuality = 0;
        d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp.hDeviceWindow = hwnd;
        d3dpp.Windowed = windowsType;
        d3dpp.EnableAutoDepthStencil = true;
        d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;//深度 /模板缓冲区
        d3dpp.Flags = 0; // D3DPRESENTFLAG_DEVICECLIP
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

        //创建IDirect3DDevice9接口
        // IDirect3DDevice9 *device = 0;
        HRESULT hr = _d3d9->CreateDevice(
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            hwnd,
            D3DCREATE_HARDWARE_VERTEXPROCESSING,
            &d3dpp,
            device);

        if (FAILED(hr))
        {
            _d3d9->Release();
            MessageBox(NULL, TEXT("crateDevice failed"), TEXT("D3DX"), MB_OKCANCEL);
            return FALSE;
        }

        _d3d9->Release();
        return TRUE;
    }
    return FALSE;
}

D3DMATERIAL9 d3dutils::InitMtrl(
    D3DXCOLOR a,
    D3DXCOLOR d,
    D3DXCOLOR s,
    D3DXCOLOR e,
    float p)
{
    D3DMATERIAL9 mtrl;
    mtrl.Ambient = a;
    mtrl.Diffuse = d;
    mtrl.Specular = s;
    mtrl.Emissive = e;
    mtrl.Power = p;
    return mtrl;
}


D3DLIGHT9 d3dutils::InitDirectionallight(D3DXVECTOR3 *direction,D3DXCOLOR *color)
{
    D3DLIGHT9 light;
    ZeroMemory(&light,sizeof(light));
    light.Type = D3DLIGHT_DIRECTIONAL;
    //light.Ambient = *color * 0.4f;
    //light.Diffuse = *color;
    //light.Specular = *color * 0.6f;
    light.Direction = *direction;
    return light;
}// 平行光源


void d3dutils::ComputeNormal(D3DXVECTOR3 *p0,D3DXVECTOR3 *p1,D3DXVECTOR3 *p2,D3DXVECTOR3 *out)
{
    D3DXVECTOR3 u = *p1 -*p0;
    D3DXVECTOR3 v = *p2 -*p0;
    D3DXVec3Cross(out,&u,&v);
    D3DXVec3Normalize(out,out);
};