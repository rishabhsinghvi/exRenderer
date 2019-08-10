#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "glad/glad.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include<vector>
#include<cassert>
#include<memory>

struct AttributeLayout
{
	unsigned int size; // Number of element per vertex; will most likely be 3. Sets the 'size' parameter in glVertexAttribPointer
	unsigned int type; // Type of each component; will most likely be GL_FLOAT or GL_UNSIGNED_INT. Sets the 'type' parameter in glVertexAttribPointer
	unsigned int normal; // whether data should be normalized or not; either GL_TRUE or GL_FALSE. Sets the 'normalized' parameter in glVertexAttribPointer.

	AttributeLayout() = delete;

	AttributeLayout(unsigned int size_, unsigned int type_, unsigned int normal_): size(size_), type(type_), normal(normal_){}
};

class VertexArray
{
private:
	unsigned int array_id;

	std::shared_ptr<VertexBuffer> v_buffer;
	std::vector<AttributeLayout> layout;
	std::shared_ptr<IndexBuffer> i_buffer;

public:
	VertexArray()
	{
		glGenVertexArrays(1, &array_id);
	}

	~VertexArray()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &array_id);
	}

	// The stride and offset are all calculated by the bindVertexBuffer method. We only need to provide the layout in order in the vector.
	void bindVertexBuffer(const std::shared_ptr<VertexBuffer>& vb, const std::vector<AttributeLayout>& layout_);
	
	void bindIndexBuffer(const std::shared_ptr<IndexBuffer>& ib);

	inline void bind() const
	{
		glBindVertexArray(array_id);
	}

	inline void unbind() const
	{
		glBindVertexArray(0);
	}

	void draw() const;

	inline unsigned int getId() const
	{
		return array_id;
	}
private:

	unsigned int getTypeSize(unsigned int type) const;
	

	unsigned int getStride() const;

};

#endif