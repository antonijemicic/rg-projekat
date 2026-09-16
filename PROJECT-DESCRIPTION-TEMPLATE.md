# RG PROJECT - Isometric Room

mi23276 - Antonije Mićić

Interactive 3D isometric room with configurable lighting, timed lighting events,
framebuffer post-processing effects and point shadows.

## Controls

W -> Move camera forward  
S -> Move camera backward  
A -> Move camera left  
D -> Move camera right  
Arrow Keys -> Rotate camera  
Mouse Movement -> Rotate camera  
Mouse Scroll -> Zoom  
F2 -> Toggle GUI  
E -> Start timed lighting event  
ESC -> Exit application

## Features

### Fundamental:

[x] Model with lighting
[x] Two types of lighting with customizable colors and movement through GUI or ACTIONS
[x] E --- AFTER 2 SECONDS ---Triggers---> Point Light becomes red ---> AFTER 3 SECONDS ---Triggers---> Point Light moves
and Spot Light becomes blue

### Group A:

[x] Frame-buffers with post-processing   
[ ] Off-screen Anti-Aliasing  
[ ] Parallax Mapping
[ ] Bloom with the use of HDR

### Group B:

[ ] Deferred Shading  
[x] Point Shadows  
[ ] SSAO

### Engine improvement:

[x] Reusable framebuffer post-processing controller
[x] Reusable point shadow controller

## Models:

[Isometric Room - Poly Pizza](https://poly.pizza/m/epElsuhDoKg)

## Textures

No external textures are used.

## Other resources

[LearnOpenGL - Framebuffers](https://learnopengl.com/Advanced-OpenGL/Framebuffers)  
[LearnOpenGL - Point Shadows](https://learnopengl.com/Advanced-Lighting/Shadows/Point-Shadows)
