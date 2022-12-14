#include "cube.h"

const DWORD cube::cubeVertex::FVF = D3DFVF_XYZ /*| D3DFVF_DIFFUSE*/ | D3DFVF_NORMAL | D3DFVF_TEX1;
                                    // 坐标           颜色                 法线           纹理
bool cube::CreateVertexBuffer(
        IDirect3DDevice9 *devict,
        UINT Length, 
        DWORD Usage,  
        D3DPOOL Pool,
        IDirect3DVertexBuffer9 **ppVertexBuffer
    )
{
    devict->CreateVertexBuffer(
        Length,
        Usage,
        cubeVertex::FVF,
        Pool,
        ppVertexBuffer,
        0);

    return true;
}

bool cube::CreateIndexBuffer(
        IDirect3DDevice9 *devict,
        UINT Length, 
        DWORD Usage, 
        D3DFORMAT Format, 
        D3DPOOL Pool,
        IDirect3DIndexBuffer9 **ppIndexBuffer
    )
{
    devict->CreateIndexBuffer(
        Length,
        Usage,
        Format,
        Pool,
        ppIndexBuffer,
        0
    );
    return true;
}
