#ifndef V_BUFFER_H
#define V_BUFFER_H

#include "glad/glad.h"

#include<vector>

class VertexBuffer
{
private:
	unsigned int buffer_id;
	std::vector<float> buffer_data;
	unsigned int buffer_size;
	unsigned int buffer_vertices;

public:
	
	VertexBuffer() 
	{

	}

	VertexBuffer(const std::vector<float>& data) : buffer_data(data), buffer_size(data.size() * 4), buffer_vertices(data.size() / 8)
	{
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER,  buffer_size, buffer_data.data(), GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
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

	inline void setBufferData(const std::vector<float>& data)
	{
		buffer_data = data;
		buffer_size = data.size() * 4;
		buffer_vertices = data.size() / 6;   // Each vertex occupies 6 elements: pos_x, pos_y, pos_z, normal_x, normal_y, normal_z, uv_x, uv_y
	}

	inline void setSize(unsigned int size)
	{
		buffer_size = size;
	}

	void draw() const
	{
		glDrawArrays(GL_TRIANGLES, 0, buffer_vertices);
	}
};


#endif