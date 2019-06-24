#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "VertexBuffer.h"
#include<vector>
#include "glad/glad.h"
#include<cassert>

struct Layout
{
	unsigned int size;
	unsigned int type;
	unsigned int normal;

	Layout() = delete;

	Layout(unsigned int size_, unsigned int type_, unsigned int normal_): size(size_), type(type_), normal(normal_){}
};

class VertexArray
{
private:
	unsigned int array_id;
	VertexBuffer v_buffer;
	std::vector<Layout> layout;
public:
	VertexArray()
	{
		glGenVertexArrays(1, &array_id);
		glBindVertexArray(array_id);
	}

	~VertexArray()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &array_id);
	}

	void bindBuffer(const VertexBuffer& vb, const std::vector<Layout>& layout_);
	

	inline void bind() const
	{
		glBindVertexArray(array_id);
	}

	inline void unbind() const
	{
		glBindVertexArray(0);
	}

private:

	unsigned int getTypeSize(unsigned int type) const;
	

	unsigned int getStride() const;

};

#endif