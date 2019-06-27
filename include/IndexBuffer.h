#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include "glad/glad.h"

#include<vector>

class IndexBuffer
{
private:
	unsigned int index_id;
	std::vector<unsigned int> index_data;
	unsigned int index_count;

public:
	IndexBuffer() 
	{
		glGenBuffers(1, &index_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
	}

	IndexBuffer(const std::vector<unsigned int> data) : index_data(data), index_count(data.size())
	{
		glGenBuffers(1, &index_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(unsigned int), index_data.data(), GL_STATIC_DRAW);
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

	inline unsigned int getId() const
	{
		return index_id;
	}

	inline unsigned int getCount() const
	{
		return index_count;
	}

	inline void setIndexData(const std::vector<unsigned int>& data)
	{
		index_data = data;
		index_count = index_data.size();
	}


	inline void draw() const
	{
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
	}
};


#endif