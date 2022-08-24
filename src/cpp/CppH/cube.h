#ifndef _CUBE_H_
#define _CUBE_H_

#if !defined(__D3DUTILS_H__)
#include "d3dUtils.h"
#endif

namespace cube
{
    
    typedef struct cubeVertex
    {
        float _x,_y,_z;
        float _nx,_ny,_nz;//顶点法线
        float _u,_v;//纹理坐标
        D3DCOLOR _color;//
        cubeVertex(){}
        cubeVertex(float x,float y,float z)
        {
            _x = x,_y = y,_z=z;
        }

        cubeVertex(float x,float y,float z,D3DCOLOR color)
        {
            _x = x,_y = y,_z=z;
            _color = color;
        }

        cubeVertex(float x,float y,float z,
                    float nx,float ny,float nz,D3DCOLOR color)
        {
            _x = x,_y = y,_z=z;
            _nx = nx,_ny = ny,_nz= nz;
            _color = color;
            
        }

        cubeVertex(float x,float y,float z,
                    float nx,float ny,float nz,float u,float v,D3DCOLOR color)
        {
            _x = x,_y = y,_z=z;
            _nx = nx,_ny = ny,_nz= nz;
            _u = u,_v = v;
            _color = color;
            
        }
        static const DWORD FVF;
    } Vertex;

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