#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include "glad/glad.h"

class IndexBuffer
{
private:
	unsigned int index_id;
	void* index_data;
	unsigned int index_count;

public:
	IndexBuffer() {}

	IndexBuffer(void* data, unsigned int count) : index_data(data), index_count(count)
	{
		glGenBuffers(1, &index_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*index_count, index_data, GL_STATIC_DRAW);
	}

	~IndexBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &index_id);
	}

	inline void bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
	}

	inline void unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	inline unsigned int getCount() const
	{
		return index_count;
	}

	inline void setIndexData(void* data)
	{
		index_data = data;
	}

	inline void setCount(unsigned int count)
	{
		index_count = count;
	}
};


#endif