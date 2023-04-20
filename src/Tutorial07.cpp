//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
// University: UCQ
// Subject:     Clase Arquitectura de Motores Gráficos
// Professor:    Ing. Roberto Charretón Kaplun
// 
// Student:  Ali Mateo Campos Martínez
// Grade:       8° Cuatrimestre
//--------------------------------------------------------------------------------------

// Tidier project and call order
#include "Prerequisities.h"

// All structures
#include "Commons.h"

// Our bookstores
#include "CTime.h"
#include "UserInterface.h"

// Abstraction
#include "Window.h"
#include "DeviceContext.h"
#include "Device.h"
#include "DepthStencilView.h"
#include "Texture.h"
#include "InputLayout.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "Transform.h"
#include "SamplerState.h"
#include "Viewport.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ModelLoader.h"
#include "ShaderProgram.h"
#include "ConstantBuffer.h"
#include "CCamera.h"


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
Window                              g_window;
DeviceContext                       g_deviceContext;
Device                              g_device;
DepthStencilView                    g_depthStencilView;
Texture                             g_ModelTexture;
Texture                             g_depthStencil;
Texture                             g_backBuffer;
SwapChain                           g_swapChain;
RenderTargetView                    g_renderTargetView;
SamplerState                        g_samplerState;
Viewport                            g_viewport;
Transform                           g_transform;
CTime                               g_Time;
Camera                              cam;  // Stores view and projection transposed matrix           
VertexBuffer                        g_vertexBuffer;
LoadData                            LD;
IndexBuffer                         g_indexBuffer;
ModelLoader                         g_modelLoader;
ShaderProgram                       g_shaderProgram;
UserInterface                       UI;
ConstantBuffer                      g_constantBuffer;
CCamera                             g_camera;
XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );

// Render Model in ImGui
ID3D11Texture2D* imguiTexture;
ID3D11RenderTargetView* imguiRTV;
ID3D11ShaderResourceView* imguiSRV = nullptr;


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT 
InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT 
InitDevice();
LRESULT 
CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
void 
Render();
void 
update();
void 
destroy();

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int 
WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    // Inicializamos la ventana
    if (FAILED(g_window.init(hInstance, nCmdShow, WndProc, "ENGINE: Let me do it for you")))
        return 0;

    if( FAILED( InitDevice() ) ){
        destroy();
        return 0;
    }

    // Initialize time
    g_Time.init();

    // Initialize transform
    g_transform.init();

    // Main message loop
    MSG msg = {0};
    while (WM_QUIT != msg.message){

      if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
            TranslateMessage( &msg );
            DispatchMessage( &msg );
      }
      else{
          g_Time.update();
          update();
          Render();
      }
    }

    destroy();

    return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT 
CompileShaderFromFile( char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut ){
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, nullptr, ppBlobOut, &pErrorBlob, nullptr );

    if( FAILED(hr) ){
        if( pErrorBlob != nullptr )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }

    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT 
InitDevice(){
    HRESULT hr = S_OK;
  
    //Create swap chain
    g_swapChain.init(g_device, g_deviceContext, g_backBuffer, g_window);

    // Create a render target view
    g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);

    g_backBuffer.destroy();
    if (FAILED(hr)) {
        return hr;
    }

    // Create depth stencil texture
    g_depthStencil.init(g_device,
                        g_window.m_width,
                        g_window.m_height,
                        DXGI_FORMAT_D24_UNORM_S8_UINT,
                        D3D11_BIND_DEPTH_STENCIL);

    // Create the depth stencil view
    g_depthStencilView.init(g_device, g_depthStencil.m_texture, DXGI_FORMAT_D24_UNORM_S8_UINT);

    // Setup the viewport
    g_viewport.init(g_window);


    //Define the input layout
    std::vector <D3D11_INPUT_ELEMENT_DESC> Layout;

    D3D11_INPUT_ELEMENT_DESC position;
    position.SemanticName = "POSITION";
    position.SemanticIndex = 0;
    position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    position.InputSlot = 0;
    position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    position.InstanceDataStepRate = 0;
    Layout.push_back(position);

    D3D11_INPUT_ELEMENT_DESC texcoord;
    texcoord.SemanticName = "TEXCOORD";
    texcoord.SemanticIndex = 0;
    texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
    texcoord.InputSlot = 0;
    texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    texcoord.InstanceDataStepRate = 0;
    Layout.push_back(texcoord);


    // Create the input layout
    g_shaderProgram.init(g_device, "Tutorial07.fx", Layout);

    //Upload model information
    LD = g_modelLoader.load("Pistol.obj");
    
    //Set VertexBuffer
    g_vertexBuffer.init(g_device, LD);

    //INDEX BUFFER
    g_indexBuffer.init(g_device, LD);


    //Create the constant buffers camera
    g_camera.init(g_device);

    //Buffer modelo
    g_constantBuffer.init(g_device, sizeof(CBChangesEveryFrame));

    // Load the Texture
    g_ModelTexture.init(g_device, "GunAlbedo.dds");

    //Create the sample state
    g_samplerState.init(g_device);

    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(textureDesc));
    textureDesc.Width = g_window.m_width;
    textureDesc.Height = g_window.m_height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    g_device.m_device->CreateTexture2D(&textureDesc, NULL, &imguiTexture);

    // Crear una vista de render target para la textura de IMGUI
    g_device.m_device->CreateRenderTargetView(imguiTexture, NULL, &imguiRTV);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Texture2D.MostDetailedMip = 0;
    g_device.m_device->CreateShaderResourceView(imguiTexture, &srvDesc, &imguiSRV);

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = XMMatrixLookAtLH( Eye, At, Up );

    // Initialize the projection matrix (global)
    g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f );

    cam.mView = XMMatrixTranspose(g_View);
    cam.mProjection = XMMatrixTranspose(g_Projection);

    // Initialize Classes
    UI.init(g_window.m_hWnd, g_device.m_device, g_deviceContext.m_deviceContext);

    return S_OK;
}


// This function is in charge of updating the
// program LOGIC
// Mathematics, physics, buffers, etc...
void 
update(){

  UI.update();

  //ImGui Demo
  bool show_demo_window = true;
  ImGui::ShowDemoWindow(&show_demo_window);



  // ImGui Base
  ImGui::Begin("ENGINE vol. 1");
  ImGui::End();



  // EASY TRANSFORM
  ImGui::Begin("EASY TRANSFORM");

  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
  ImGui::Text("POSITION");
  ImGui::PopStyleColor();
  ImGui::SliderFloat("Position X", &g_transform.m_v3Position.x, -4.0f, 1.0f);
  ImGui::SliderFloat("Position Y", &g_transform.m_v3Position.y, -2.0f, 2.0f);
  ImGui::SliderFloat("Position Z", &g_transform.m_v3Position.z, -2.0f, 2.0f);

  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
  ImGui::Text("ROTATION");
  ImGui::PopStyleColor();
  ImGui::SliderFloat("Rotation X", &g_transform.m_v3Rotate.x, -6.0f, 6.0f);
  ImGui::SliderFloat("Rotation Y", &g_transform.m_v3Rotate.y, -6.0f, 6.0f);
  ImGui::SliderFloat("Rotation Z", &g_transform.m_v3Rotate.z, -6.0f, 6.0f);

  ImGui::End();



  // EASY SCALE
  ImGui::Begin("EASY SCALE");

  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
  ImGui::Text("SCALE");
  ImGui::PopStyleColor();
  ImGui::SliderFloat("Rotation X", &g_transform.m_v3Scale.x, 0.4f, 1.0f);
  ImGui::SliderFloat("Rotation Y", &g_transform.m_v3Scale.y, 0.4f, 1.0f);
  ImGui::SliderFloat("Rotation Z", &g_transform.m_v3Scale.z, 0.4f, 1.0f);

  ImGui::End();



  // DATA TRANSFORM
  ImGui::Begin("DATA TRANSFORM");

  UI.vec3Control("Position", &g_transform.m_v3Position.x);
  UI.vec3Control("Rotation", &g_transform.m_v3Rotate.x);
  UI.vec3Control("Scale", &g_transform.m_v3Scale.x, 0.5f);

  ImGui::End();



  // COLOR BACKGROUND
  ImGui::Begin("COLOR BACKGROUND");
  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
  ImGui::Text("Color widget with Float Display:");
  ImGui::PopStyleColor();
  ImGui::ColorEdit4("MyColor##2f", (float*)&g_renderTargetView.m_cleanColor, ImGuiColorEditFlags_Float);
  ImGui::End();



  // COLOR MODEL TEXTURE
  ImGui::Begin("COLOR MODEL TEXTURE");

  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
  ImGui::Text("White is better:");
  ImGui::PopStyleColor();
  ImGui::ColorEdit4("MyColor##2f", (float*)&g_vMeshColor, ImGuiColorEditFlags_Float);

  ImGui::End();



  // RENDERER
  bool Stage = true;
  // ImGui::Begin("RENDERER", &Stage, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
  ImGui::Begin("RENDERER");
  ImTextureID texId = (ImTextureID)imguiSRV;
  ImGui::Image(texId, ImVec2(g_window.m_width / 2, g_window.m_height / 2));
  ImGui::End();


  g_transform.m_fRotateNum += 0.0002f;

  g_World = XMMatrixScaling    (g_transform.m_v3Scale.x, 
                                g_transform.m_v3Scale.y,
                                g_transform.m_v3Scale.z) *

            XMMatrixRotationX  (g_transform.m_v3Rotate.x) *
            XMMatrixRotationY  (g_transform.m_v3Rotate.y) *
            XMMatrixRotationZ  (g_transform.m_v3Rotate.z) *

            XMMatrixTranslation(g_transform.m_v3Position.x, 
                                g_transform.m_v3Position.y, 
                                g_transform.m_v3Position.z);

  // Update variables that change once per frame
  CBChangesEveryFrame cb;
  cb.mWorld = XMMatrixTranspose(g_World);
  cb.vMeshColor = g_vMeshColor;

  // Update Mesh Buffers
  g_constantBuffer.update(g_deviceContext, 0, nullptr, &cb, 0, 0);

  // UpdateCamera Buffers
  g_camera.update(g_deviceContext, cam);
}


//--------------------------------------------------------------------------------------
// Clean the objects we have created
// 
// This function is in charge of releasing
// the resources used in the program
//--------------------------------------------------------------------------------------
void 
destroy(){
    g_deviceContext.destroy();
    g_samplerState.destroy();
    g_ModelTexture.destroy();
    g_camera.destroy();
    g_constantBuffer.destroy();
    g_vertexBuffer.destroy();
    g_indexBuffer.destroy();
    g_shaderProgram.destroy();
    g_depthStencil.destroy();
    g_depthStencilView.destroy();
    g_renderTargetView.destroy();
    g_swapChain.destroy();
    UI.destroy();
    g_device.destroy();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT
ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
// Procesa los mensajes enviados a una ventana
// 
// HWND: A handle to the window
// 
// UINT: It uses these messages to control the operations of applications and to provide 
//       input and other information for applications to process.
// 
// WPARAM: Additional message information.
//         ali
//         The contents of the wParam parameter depend on the value of the uMsg parameter.
//         
// 
// LPARAM: = Up
//--------------------------------------------------------------------------------------
LRESULT 
CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ){
    
  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return true;
  
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message ){

        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        case WM_KEYDOWN:

            switch (wParam){

                case 'A':
                  g_transform.m_v3Position.x -= g_transform.m_fSpeed * g_Time.m_fDeltaTime;
                  break;

                case 'D':
                  g_transform.m_v3Position.x += g_transform.m_fSpeed * g_Time.m_fDeltaTime;
                  break;

                case 'W':
                  g_transform.m_v3Position.y += g_transform.m_fSpeed * g_Time.m_fDeltaTime;
                  break;

                case 'S':
                  g_transform.m_v3Position.y -= g_transform.m_fSpeed * g_Time.m_fDeltaTime;
                  break;

                case 'Q':
                  g_transform.m_v3Position.z += g_transform.m_fSpeed * g_Time.m_fDeltaTime;
                  break;

                case 'E':
                  g_transform.m_v3Position.z -= g_transform.m_fSpeed * g_Time.m_fDeltaTime;
                  break;

                case 'Z':
                  g_transform.m_fScaleNum += g_transform.m_fSpeed * g_Time.m_fDeltaTime;
                  break;

                case 'X':
                  g_transform.m_fScaleNum -= g_transform.m_fSpeed * g_Time.m_fDeltaTime;
                  break;

                case '0':
                  g_vMeshColor = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
                  break;

                case '1':
                  g_vMeshColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
                  break;

                case '2':
                  g_vMeshColor = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
                  break;

                case '3':
                  g_vMeshColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
                  break;
            }

            break;
        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
// This function is responsible for updating exclusively
// the data displayed on the screen
//--------------------------------------------------------------------------------------
void 
Render(){

    // Set the IMGUI texture as the rendering view
    g_deviceContext.m_deviceContext->OMSetRenderTargets(1, &imguiRTV, NULL);

    // Clear the back buffer
    g_depthStencilView.render(g_deviceContext);

    // Class render target view
    g_renderTargetView.render(g_deviceContext, g_depthStencilView);

    // Class viewport
    g_viewport.render(g_deviceContext);

    // Set the input layout
    g_shaderProgram.render(g_deviceContext);
    
    //Set constants buffers (camera)
    g_camera.render(g_deviceContext);
    
    //Set sampler
    g_samplerState.render(g_deviceContext);
    
    //Set vertex e indexbuffer
    g_vertexBuffer.render(g_deviceContext, 0);
    g_indexBuffer.render(g_deviceContext, DXGI_FORMAT_R32_UINT);
    
    //Set constant buffers
    g_constantBuffer.VSSetConstantBuffer(g_deviceContext, 1, 1);
    g_constantBuffer.PSSetConstantBuffers(g_deviceContext, 1, 1);
    
    // Set primitive topology
    g_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Set shader resources
    ID3D11ShaderResourceView* srvs[] = { imguiSRV };
    g_deviceContext.m_deviceContext->PSSetShaderResources(0, 1, srvs);

    // Set shader resources (texture)
    g_ModelTexture.render(g_deviceContext);

    // Set index buffer
    g_deviceContext.DrawIndexed( LD.index.size(), 0, 0);

    // Copy the back buffer to the texture IMGUI
    g_swapChain.m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&g_backBuffer.m_texture);
    g_deviceContext.m_deviceContext->CopyResource(imguiTexture, g_backBuffer.m_texture);
    g_backBuffer.m_texture->Release();
    
    //Render ImGui
    UI.render();

    // Present our back buffer to our front buffer
    g_swapChain.present();
}
