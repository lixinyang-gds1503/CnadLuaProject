#ifndef _CUBE_H_
#define _CUBE_H_

#if !defined(__D3DUTILS_H__)
#include "d3dUtils.h"
#endif

namespace cube
{
    
    struct cubeVertex
    {
        float _x,_y,_z;
        cubeVertex(){}
        cubeVertex(float x,float y,float z)
        {
            _x = x,_y = y,_z=z;
        }
        static const DWORD FVF;
    };

    /*创建顶点缓冲区*/
    bool CreateVertexBuffer(
        IDirect3DDevice9 *devict,
        UINT Length, 
        DWORD Usage,  
        D3DPOOL Pool,
        IDirect3DVertexBuffer9 **ppVertexBuffer
    );

    /*创建索引缓冲区*/
    bool CreateIndexBuffer(
        IDirect3DDevice9 *devict,
        UINT Length, 
        DWORD Usage, 
        D3DFORMAT Format, 
        D3DPOOL Pool,
        IDirect3DIndexBuffer9 **ppIndexBuffer
    );
    

}


#endif