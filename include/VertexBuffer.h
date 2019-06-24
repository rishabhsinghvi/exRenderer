#ifndef V_BUFFER_H
#define V_BUFFER_H

#include "glad/glad.h"

class VertexBuffer
{
private:
	unsigned int buffer_id;
	void* buffer_data;
	unsigned int buffer_size;
public:
	
	VertexBuffer() { /* element */ };

	VertexBuffer(void* data, unsigned int b_size): buffer_data(data),buffer_size(b_size)
	{
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER,  buffer_size, buffer_data, GL_STATIC_DRAW);
	}

	~VertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &buffer_id);
	}

	inline void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	}

	inline void unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	inline unsigned int getSize()
	{
		return buffer_size;
	}

	inline void setBufferData(void* data)
	{
		buffer_data = data;
	}

	inline void setSize(unsigned int size)
	{
		buffer_size = size;
	}
};


#endif