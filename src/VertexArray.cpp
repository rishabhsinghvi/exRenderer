#include "VertexArray.h"

void VertexArray::bindVertexBuffer(const std::shared_ptr<VertexBuffer>& vb, const std::vector<AttributeLayout>& layout_)
{

	v_buffer = vb;
	layout = layout_;

	glBindVertexArray(array_id);

	v_buffer->bind();

	int pointerOffset = 0;

	auto stride = getStride();

	for (int i = 0; i < layout.size(); i++)
	{
		auto& vertexAttr = layout[i];

		// Enable vertex attributes
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, vertexAttr.size, vertexAttr.type, vertexAttr.normal, stride, (const void*)pointerOffset);

		auto type_size = getTypeSize(vertexAttr.type);
		pointerOffset += vertexAttr.size *  type_size;
	}

	glBindVertexArray(0);
}

void VertexArray::bindIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
{
	i_buffer = ib;
	glBindVertexArray(array_id);
	i_buffer->bind();
	glBindVertexArray(0);
}

// Bit redundant right now, but might be useful if we decide to extend application in the future
unsigned int VertexArray::getTypeSize(unsigned int type) const
{
	switch (type)
	{
	case GL_FLOAT: return 4;
	case GL_UNSIGNED_INT: return 4;
	default: return 4;
	}
	assert(false);
}


unsigned int VertexArray::getStride() const
{
	unsigned int stride = 0;

	// stride = (num of elements in each attribute * size of type of element) for all elements in the attribute layout

	for (const auto& e : layout)
	{
		stride += e.size * getTypeSize(e.type);
	}

	return stride;
}

void VertexArray::draw() const
{
//	bind();
	i_buffer->draw();
}

