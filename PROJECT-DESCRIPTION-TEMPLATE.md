# Wooden Crate

mi23276 - ANTONIJE MICIC  
Textured wooden crate model with directional and point lighting. The model uses an image texture, and both lights use
separate ambient, diffuse and specular components. The point light position and the lighting colors can be controlled
using keyboard actions. The project also contains a timed event sequence triggered by the E key.

## Controls

J / L -> Move point light left / right  
I / K -> Move point light up / down  
U / O -> Move point light forward / backward

1 -> Set point light components to red  
2 -> Set point light components to green  
3 -> Set point light components to blue

4 -> Set directional light components to red  
5 -> Set directional light components to green  
6 -> Set directional light components to blue

E -> Start timed light sequence

## Features

### Fundamental:

[x] Model with lighting and texture  
[x] Two types of lighting with customizable colors and movement through ACTIONS  
[x] Press E --- AFTER 2 SECONDS ---Triggers---> Point light becomes red ---> AFTER 3 SECONDS ---Triggers---> Point light
changes position and directional light becomes blue

### Group A:

[ ] Frame-buffers with post-processing  
[ ] Off-screen Anti-Aliasing  
[ ] Parallax Mapping  
[ ] Bloom with the use of HDR

### Group B:

[ ] Deferred Shading  
[ ] Point Shadows  
[ ] SSAO

### Engine improvement:

[ ] None

## Models:

[Wooden Crate model from Sketchfab](https://sketchfab.com/3d-models/game-ready-wooden-crate-low-poly-pbr-921cdec29cc94af48a41045b36cf6270?utm_source=chatgpt.com)

## Textures

Base color texture is used by the shader. The Wooden Crate model also includes a normal texture.