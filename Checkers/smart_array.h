#include"pch.h"

#ifndef SMART_ARRAY_H

#define SMART_ARRAY_H

template <typename T>
struct smart_array
{
#pragma region Ctor

	smart_array() : smart_array(1) { }

	smart_array(size_t count) : m_count(count), m_index(0) { m_ptr = new T[m_count * 2]; }

	smart_array(const smart_array<T>& other)
	{
		this->m_count = other.m_count;

		this->m_index = other.m_index;

		m_ptr = new T[m_count];

		for (size_t i = 0; i < m_count; i++)
		{
			*(m_ptr + i) = *(other.m_ptr + i);
		}
	}

	~smart_array() { delete[] m_ptr; }

#pragma endregion

#pragma region Functions

	const size_t& GetCount() const
	{
		return m_count;
	}

	void Add(T elem)
	{
		if (m_index >= m_count)
			Resize();

		*(m_ptr + m_index) = elem;

		++m_index;
	}

	void Clear()
	{
		delete[] m_ptr;

		m_count = 0;

		m_index = 0;
	}

#pragma endregion

#pragma region Operators

	smart_array<T>& operator = (const smart_array<T>& other)
	{
		this->m_count = other.m_count;

		this->m_index = other.m_index;

		this->m_ptr = new T[m_count];

		for (size_t i = 0; i < m_count; i++)
		{
			*(m_ptr + i) = *(other.m_ptr + i);
		}

		return *this;
	}

	T& operator[](size_t index)
	{
		if (index < m_count)
			return *(m_ptr + index);
	}

	const T& operator[](size_t index) const
	{
		if (index < m_count)
			return *(m_ptr + index);
	}
#pragma endregion


private:

	void Resize()
	{
		T* ptrTemp = new T[m_count * 2];

		for (size_t i = 0; i < m_count; i++)
		{
			*(ptrTemp + i) = *(m_ptr + i);
		}

		delete[]m_ptr;

		m_ptr = ptrTemp;
	}

	T* m_ptr;

	size_t m_index;//Current index of the element must be lower then the m_count

	size_t m_count;//Amount of elements allocated in array
};

#endif // !SMART_ARRAY_H

