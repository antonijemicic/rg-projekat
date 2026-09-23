# Backpack

mi23276 - ANTONIJE MICIC  
Textured backpack model with directional and point lighting. The model uses diffuse and specular textures. Both light
colors and the point light position can be controlled using keyboard actions. The project also contains a timed event
sequence triggered by the E key.

## Controls

J / L -> Move point light left / right  
I / K -> Move point light up / down  
U / O -> Move point light forward / backward

1 -> Set point light color to red  
2 -> Set point light color to green  
3 -> Set point light color to blue

4 -> Set directional light color to red  
5 -> Set directional light color to green  
6 -> Set directional light color to blue

E -> Start timed event sequence

## Features

### Fundamental:

[x] Model with lighting and textures  
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

https://learnopengl.com/Model-Loading/Model

## Textures

Diffuse and specular textures are used by the shader. The backpack model also includes a normal texture.