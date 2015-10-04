#pragma once

#include <new.h>

#define ARRAY_ALLOCATION_SIZE 16

template<class Element,unsigned long AllocationSize = ARRAY_ALLOCATION_SIZE>
class Array
{
public:
	Array(void);
	~Array(void);

	void Insert(unsigned long at,const Element& element);
	void InsertBack(const Element& element);
	void InsertFront(const Element& element);

	void Erase(unsigned long at,unsigned long count = 1);
	void Erase(void);
	void EraseBack(void);
	void EraseFront(void);

	unsigned long GetBufferSize(void) const;
	unsigned long GetSize(void) const;

	Element& Front(void);
	const Element& Front(void) const;

	Element& Back(void);
	const Element& Back(void) const;

	Element& GetElement(unsigned long element);

	operator Element*(void);
	operator const Element*(void) const;

protected:
	Element*		m_Buffer;
	unsigned long	m_BufferSize;
	unsigned long	m_Size;

protected:
	bool PrepareBuffer(unsigned long newSize,bool preserve);
	bool ResizeBuffer(unsigned long newSize,bool preserve);
};

template<class Element,unsigned long AllocationSize>
Array<Element,AllocationSize>::Array(void) :
m_Buffer(NULL),
m_BufferSize(0),
m_Size(0)
{
}

template<class Element,unsigned long AllocationSize>
Array<Element,AllocationSize>::~Array(void)
{
	ResizeBuffer(0,false);
}

template<class Element,unsigned long AllocationSize>
bool Array<Element,AllocationSize>::PrepareBuffer(unsigned long newSize,bool preserve)
{
	if(m_BufferSize == newSize)
		return true;

	if(newSize < m_BufferSize)
		if(m_BufferSize - newSize < AllocationSize)
			return true;

	newSize = newSize - newSize % AllocationSize + AllocationSize;

	return ResizeBuffer(newSize,preserve);
}

template<class Element,unsigned long AllocationSize>
bool Array<Element,AllocationSize>::ResizeBuffer(unsigned long newSize,bool preserve)
{
	if(m_BufferSize == newSize)
		return true;

	if(!newSize)
	{
		for(unsigned long i = 0; i < m_Size; ++i)
			m_Buffer[i].~Element();

		delete[] m_Buffer;

		m_Buffer = NULL;
		m_BufferSize = 0;
		m_Size = 0;

		return true;
	}

	if(!m_Buffer)
	{
		m_Buffer = new Element[newSize];
		if(!m_Buffer)
			return false;

		m_BufferSize = newSize;
		m_Size = 0;

		return true;
	}

	Element* newBuffer = new Element[newSize];
	if(!newBuffer)
		return false;

	if(preserve)
		CopyMemory(newBuffer,m_Buffer,sizeof(Element) * m_Size);	// TODO What if the new buffer size is smaller that m_Size
	else
	{
		for(unsigned long i = 0; i < m_Size; ++i)
			m_Buffer[i].~Element();

		m_Size = 0;
	}

	delete[] m_Buffer;

	m_Buffer = newBuffer;
	m_BufferSize = newSize;

	return true;
}

template<class Element,unsigned long AllocationSize>
void Array<Element,AllocationSize>::Insert(unsigned long at,const Element& element)
{
	ASSERT(at <= m_Size);

	PrepareBuffer(m_Size + 1,true);

	MoveMemory(m_Buffer + at + 1,m_Buffer + at,sizeof(Element) * (m_Size - at));

	::new(&m_Buffer[at]) Element(element);
	
	m_Size++;
}

template<class Element,unsigned long AllocationSize>
inline void Array<Element,AllocationSize>::InsertBack(const Element& element)
{
	Insert(m_Size,element);
}

template<class Element,unsigned long AllocationSize>
inline void Array<Element,AllocationSize>::InsertFront(const Element& element)
{
	Insert(0,element);
}

template<class Element,unsigned long AllocationSize>
void Array<Element,AllocationSize>::Erase(unsigned long at,unsigned long count)
{
	ASSERT(m_Buffer);
	ASSERT(at + count <= m_Size);

	for(unsigned long i = at; i < at + count; ++i)
		m_Buffer[i].~Element();

	CopyMemory(m_Buffer + at,m_Buffer + at + count,sizeof(Element) * (m_Size - at - count));
	
	m_Size -= count;

	PrepareBuffer(m_Size,true);
}

template<class Element,unsigned long AllocationSize>
inline void Array<Element,AllocationSize>::Erase(void)
{
	Erase(0,m_Size);
}

template<class Element,unsigned long AllocationSize>
inline void Array<Element,AllocationSize>::EraseBack(void)
{
	Erase(m_Size - 1);
}

template<class Element,unsigned long AllocationSize>
inline void Array<Element,AllocationSize>::EraseFront(void)
{
	Erase(0);
}

template<class Element,unsigned long AllocationSize>
inline unsigned long Array<Element,AllocationSize>::GetBufferSize(void) const
{
	return m_BufferSize;
}

template<class Element,unsigned long AllocationSize>
inline unsigned long Array<Element,AllocationSize>::GetSize(void) const
{
	return m_Size;
}

template<class Element,unsigned long AllocationSize>
inline Element& Array<Element,AllocationSize>::Front(void)
{
	ASSERT(m_Buffer);

	return m_Buffer[0];
}

template<class Element,unsigned long AllocationSize>
inline const Element& Array<Element,AllocationSize>::Front(void) const
{
	ASSERT(m_Buffer);

	return m_Buffer[0];
}

template<class Element,unsigned long AllocationSize>
inline Element& Array<Element,AllocationSize>::Back(void)
{
	ASSERT(m_Buffer);

	return m_Buffer[m_Size - 1];
}

template<class Element,unsigned long AllocationSize>
inline const Element& Array<Element,AllocationSize>::Back(void) const
{
	ASSERT(m_Buffer);

	return m_Buffer[m_Size - 1];
}

template<class Element,unsigned long AllocationSize>
inline Element& Array<Element,AllocationSize>::GetElement(unsigned long element)
{
	ASSERT(m_Buffer);
	ASSERT(element < m_Size);

	return m_Buffer[element];
}

template<class Element,unsigned long AllocationSize>
inline Array<Element,AllocationSize>::operator Element*(void)
{
	return m_Buffer;
}

template<class Element,unsigned long AllocationSize>
inline Array<Element,AllocationSize>::operator const Element*(void) const
{
	return m_Buffer;
}