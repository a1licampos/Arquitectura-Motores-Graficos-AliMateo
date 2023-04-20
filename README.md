# Arquitectura-Motores-Graficos-AliMateo

**Universidad:** *UCQ*  
**Carrera:**     *IDVMI*  
**Profesor:**    *Ing. Roberto Charretón Kaplun*  
  
**Grado:**       *8° Cuatrimestre*  
**Alumno:**      *Ali Mateo Campos Martínez*
  
## Representación gráfica del proyecto
![Cubo](Cube.jpg)
![FINAL](Cube.mp4)

## Objetivos
+ **Movimiento del objeto (cubo) a través del Input del teclado**
  + <sub>El objeto comienza en (0,0,0)</sub>
  + <sub>Eje X</sub>
  + **_Tecla A_**: Movemos el objeto a la *izquierda* 
  + **_Tecla D_**: Movemos el objeto a la *derecha* 
  + <sub>Eje Y</sub>  
  + **_Tecla W_**: Movemos el objeto hacia *arriba*   
  + **_Tecla S_**: Movemos el objeto a la *derecha*
  + <sub>Eje Z (profundidad)</sub>
  + **_Tecla Q_**: Movemos el objeto hacia el *fondo*   
  + **_Tecla S_**: Movemos el objeto hacia *enfrente*
   
+ **Escala del objeto (cubo) a través del Input del teclado**
  + <sub>La escala del objeto comienza con 0.5f</sub>
  + **_Tecla Z_**: *Aumentamos* la escala del objeto
  + **_Tecla X_**: *Disminuimos* la escala del objeto
  
+ **Rotación del objeto (cubo)**
  + <sub>El objeto rota conforme pasa el tiempo, es decir, le vamos sumando 0.0002f en la función *Update* en *Tutorial7.cpp*</sub>
  + `g_transform.m_fRotateNum += 0.0002f;`
  
+ **Cambios de color en la textura del objeto (cubo)**
  + **_Tecla númerica 1_**: Cambiamos el color a *rojo* `#D60000`
  + **_Tecla númerica 2_**: Cambiamos el color a *verde* `#00C600`
  + **_Tecla númerica 3_**: Cambiamos el color a *azul* `#000087`
  + **_Tecla númerica 0_**: Reiniciamos el color de la textura a su original
  
+ **Abstracción de clases**
  + ### Clases abstraídas (13/03/2023)
  + <sub>Cada clase tiene su .h y su .cpp, además de estar comendatadas en el primero mencionado (h).</sub>
    + CTime
    + Window
    + DeviceContext
    + Device
    + DepthStencilView
    + Texture
    + InputLayout
    + SwapChain
    + RenderTargetView
    + Transform
    + SamplerState
    + Viewport
   
+ **Bugs a resolver**
  + Después de cerrar el programa presenta un _triggered a breakpoint_ en la función `ImGui_ImplDX11_InvalidateDeviceObjects()`, según indicaciones del profesor por el     momento está bien, sin embargo, debe prestarse atención en el futuro.
