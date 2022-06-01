#pragma once
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

template <class T>
class Allocator
{
public:

    T* allocate(size_t size)
    {
        return new T[size];
    }

    void deallocate(T* pointer)
    {
        delete[] pointer;
    }

    void destroy(T* pointer) 
    {
        pointer->~T();
    }

    void construct(T* pointer, size_t n) 
    {
        for (size_t i = 0; i < n; i++) 
        {
            new (pointer + i) T();
        }
    }

    size_t max_size() const noexcept 
    {
        return numeric_limits<size_t>::max();
    }
};



template <class T>
class Iterator
{
private:
    T* my_pointer;
    bool reverse_flag;
public:
    Iterator(T* pointer): my_pointer(pointer) {}

    Iterator(T* pointer, bool flag): my_pointer(pointer), reverse_flag(flag) {}

    T& operator*()
    {
        return *my_pointer;
    }

    const T& operator*() const
    {
        return *my_pointer;
    }

    T& operator[](const size_t n)
    {
    	if (reverse_flag)
        	return my_pointer[syzeof(my_pointer) - n - 1];
        else
        	return my_pointer[n];
    }

    const T& operator[](const size_t n) const
    {
        if (reverse_flag)
        	return my_pointer[syzeof(my_pointer) - n - 1];
        else
        	return my_pointer[n];
    }

    Iterator<T>& operator++()
    {
    	if (reverse_flag)
        	my_pointer++;
        else
        	my_pointer--;
        return *this;
    }

    Iterator<T>& operator--()
    {
        if (reverse_flag)
        	my_pointer++;
        else
        	my_pointer--;
        return *this;
    }

    Iterator<T> operator++(int)
    {
    	Iterator<T> tmp = *this;
    	if (reverse_flag)
    		my_pointer--;
    	else
    		my_pointer++;
        return tmp;
    }

    Iterator<T> operator--(int)
    {
    	Iterator<T> tmp = *this;
    	if (reverse_flag)
    		my_pointer++;
    	else
    		my_pointer--;
        return tmp;
    }

    Iterator<T>& operator+=(int value)
    {
    	if (!(reverse_flag))
        	my_pointer += value;
        else
        	my_pointer -= value;
        return *this;
    }

    Iterator<T>& operator-=(int value)
    {
        if (!(reverse_flag))
        	my_pointer -= value;
        else
        	my_pointer += value;
        return *this;
    }

    Iterator<T> operator+(int value)
    {
        Iterator<T> save = * this;
        if (!(reverse_flag))
        	return save + value;
        else
        	return save - value;
    }

    Iterator<T> operator-(int value)
    {
        Iterator<T> save = * this;
        if (!(reverse_flag))
        	return save - value;
        else
        	return save + value;
    }

    bool operator==(const Iterator<T>& second_vec) const
    {
        return my_pointer == second_vec.my_pointer;
    }

    bool operator>(const Iterator<T>& second_vec) const
    {
    	if (!(reverse_flag))
        	return my_pointer > second_vec.my_pointer;
        else
        	return my_pointer < second_vec.my_pointer;
    }

    bool operator<(const Iterator<T>& second_vec) const
    {
        if (!(reverse_flag))
        	return !(*this >= second_vec);
        else
        	return !(*this <= second_vec);
    }

    bool operator>=(const Iterator<T>& second_vec) const
    {
        if (!(reverse_flag))
        	return my_pointer >= second_vec.my_pointer;
        else
        	return my_pointer <= second_vec.my_pointer;
    }

    bool operator<=(const Iterator<T>& second_vec) const
    {
        if (!(reverse_flag))
        	return !(*this > second_vec);
        else
        	return !(*this < second_vec);
    }

    bool operator!=(const Iterator<T>& second_vec) const
    {
        return (!(*this == second_vec));
    }

};

template <class T, class Allocator = Allocator<T>>
class Vector
{
private:
    size_t max_size;
    size_t vec_size;
    T* my_pointer;
    Allocator alloc;
public:
	Vector(): max_size(0), vec_size(0), my_pointer(nullptr), alloc() {}

    Vector(const size_t new_size): max_size(new_size), vec_size(new_size), alloc()
    {
        if (new_size < 0)
            throw runtime_error("non-positive size");
        my_pointer = alloc.allocate(max_size);
    }

    Vector(const Vector& second_vector): max_size(second_vector.max_size), vec_size(second_vector.vec_size), alloc()
    {
        my_pointer = alloc.allocate(max_size);
        for (size_t i = 0; i < vec_size; i++)
        {
            my_pointer[i] = second_vector[i];
        }
    }

    Vector& operator=(const Vector& second_vector)
    {
    	alloc.deallocate(my_pointer);
    	vec_size = second_vector.size();
    	max_size = second_vector.capacity();
    	my_pointer = alloc.allocate(max_size);
    	for (size_t i = 0; i < vec_size; i++)
    	{
    		my_pointer[i] = second_vector[i];
    	}
    	return *this;
    }

    Vector& operator=(Vector&& second_vector)
    {
    	alloc.deallocate(my_pointer);
    	max_size = second_vector.capacity();
    	vec_size = second_vector.size();
    	my_pointer = alloc.allocate(max_size);
    	for (size_t i = 0; i < vec_size; i++)
    	{
    		my_pointer[i] = move(second_vector[i]);
    	}
    	second_vector.my_pointer = nullptr;
    	second_vector.vec_size = 0;
    	second_vector.max_size = 0;
    	return *this;
    }


    Vector(Vector&& second_vector): max_size(second_vector.max_size), vec_size(second_vector.vec_size), alloc()
    {
    	my_pointer = second_vector.my_pointer;
        second_vector.my_pointer = nullptr;
        second_vector.max_size = 0;
    	second_vector.vec_size = 0;
    }

    Iterator<T> begin()
    {
        return Iterator<T>(my_pointer, false);
    }

    Iterator<T> rbegin()
    {
        return Iterator<T>(my_pointer + vec_size, true);
    }

    Iterator<T> end()
    {
        return Iterator<T>(my_pointer + vec_size, false);
    }

    Iterator<T> rend()
    {
        return Iterator<T>(my_pointer, true);
    }

    T& operator[](size_t n)
    {
        if ( (n < 0) || (n > vec_size) )
        {
            throw runtime_error("index out of range");
        }
        return my_pointer[n];
    }

    const T& operator[](size_t n) const
    {
        if ( (n < 0) || (n > vec_size) )
        {
            throw runtime_error("index out of range");
        }
        return my_pointer[n];
    }

    void push_back(const T& elem)
    {
        if (vec_size + 2 >= max_size)
        {
            max_size = max_size * 2 + 1;
            reallocate();
        }
        my_pointer[vec_size] = elem;
        vec_size++;;
    }

    void push_back(T&& elem)
    {
        if (vec_size + 2 >= max_size)
        {
            max_size = max_size * 2 + 1;
            reallocate();
        }
        my_pointer[vec_size] = move(elem);
        vec_size++;
    }

    void reallocate()
    {
        T* new_pointer = alloc.allocate(max_size);
        for (size_t i = 0; i < vec_size; i++)
        {
            new_pointer[i] = move(my_pointer[i]);
        }
        alloc.deallocate(my_pointer);
        my_pointer = new_pointer;
    }

    void pop_back()
    {
        if (vec_size == 0)
        {
            throw runtime_error("empty vector");
        }
        vec_size--;
        alloc.destroy(my_pointer + vec_size);
    }

    template <class... Args>
    void emplace_back(Args&& ... args)
    {
        this->push_back(T(forward<Args>(args)...));
    }

    void clear()
    {
        deleter();
        vec_size = 0;
        max_size = 0;
    }

    void deleter(size_t offset=0)
    {
        for (T* tmp = my_pointer + offset; tmp < my_pointer + vec_size; tmp++)
        {
            alloc.destroy(tmp);
        }
    }

    void resize(size_t new_size)
    {
    	if (new_size > max_size)
        {
			max_size = new_size * 2 + 1;
            reallocate();
        }
        else if (new_size < vec_size)
        {
        	deleter(new_size);
            vec_size = new_size;
        }
    }

    void reserve(size_t new_size)
    {
        if (new_size > max_size)
        {
            max_size = new_size;
            reallocate();
        }
    }

    size_t capacity() const
    {
        return max_size;
    }

    bool empty() const
    {
        return vec_size == 0;
    }

    size_t size() const
    {
        return vec_size;
    }

	~Vector()
    {
        vec_size = 0;
        max_size = 0;
        if (my_pointer != nullptr)
        {
            alloc.deallocate(my_pointer);
        }
    }

};