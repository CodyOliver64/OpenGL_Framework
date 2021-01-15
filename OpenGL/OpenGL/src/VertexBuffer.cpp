#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID)); //pass in an int pointer that will store the ID of this buffer. This ID serves as the "object"
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //binds the buffer, selecting it. Takes in a target (type) and the buffer ID
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));// takes in the type, the size of our data in bytes, the data itself, and a hint of how the data will be accessed (check types on doc.gl)
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
