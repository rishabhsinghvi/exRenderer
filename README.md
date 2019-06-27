# exRenderer
A 3D Renderer written in C++ and OpenGL/glad. 


Currently the only 3D file format that I've tested and confirmed works is .obj. However since I'm using Assimp to load 3D models, it should work on most of file formats.

When I started building this project, my aim was to abstract a lot of OpenGL calls. Each OpenGL object is self-contained within its own class and creating new objects is pretty simple.

TODO: Add textures to models.

Pictures coming as soon as I fix the fragment shader.
