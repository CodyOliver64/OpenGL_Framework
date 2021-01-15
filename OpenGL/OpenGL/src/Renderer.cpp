#include "Renderer.h"
#include <iostream>

// Debug Functions
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind(); //describes how the data works to the gpu
    va.Bind(); // the data, containing positions of points/texture coords
    ib.Bind(); //groupings of the data, indexing the vertex buffer

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // New draw call using index buffer, 6 for 4 positons + 2 indicies, nullptr since ibo is bound on line 160
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}