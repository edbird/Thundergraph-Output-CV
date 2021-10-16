
/******************************************************************/
/* COPYRIGHT: E.C. BIRDSALL, MARCH 2016                           */
/******************************************************************/

#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP


#include <algorithm>
#include <memory>
#include <iostream>

//#ifdef _WIN32
//    #include "non_std_copy.hpp"
//#endif

// put in non_std namespace to
// prevent conflict with future version
// of C++, C++ 14 / C++17
namespace non_std
{

    // dynamic array class
    // size determined at RUN-TIME NOT COMPILE-TIME
    // minimal functionality required to support BMPCanvas class
	template<typename T>
	class dynarray
	{

        template<typename U>
        friend
        void swap(dynarray<U>& l, dynarray<U>& r);

		size_t m_size; //  size, set once, then constant
        //size_t m_index; // put value index, used for sequential insertion

        // allocate memory with smart pointer
        // since array of more than one element, use [] notation
        std::unique_ptr<T[]> m_data;
        //T *m_data;

	public:

        // constructor
        // fixed size must be specified by parameter size
		dynarray(const size_t size)
			: m_size{size}
            //, m_index{0} // insertion index set to zero
            //, m_data{std::unique_ptr<T[]>(new T[size])}
            , m_data{std::make_unique<T[]>(size)}
            //, m_data{new T[size]}
        {
            //std::cout << "PTR: " << (unsigned long long)m_data.get() << std::endl;
		}

        void realloc(const size_t size)
        {
            m_data = std::make_unique<T[]>(size);
            //delete [] m_data;
            //m_data = new T[size];
            m_size = size;
        }

        // remove allocation
		virtual
		~dynarray()
		{
		    // smart pointer will auto-delete
		    //std::cout << "dynarray" << std::endl;
		    
            //std::cout << "PTR: " << (unsigned long long)m_data.get() << std::endl;
		    //m_data.reset(nullptr);
		    //delete [] m_data;
		    
		    //std::cout << "dynarray 2" << std::endl;
		}

        // copy constructor
		dynarray(const dynarray& other)
			: m_size{other.m_size}
            //, m_index{other.m_index}
			, m_data{std::make_unique<T[]>(other.m_size)} // allocate new smart pointer and copy memory
			//, m_data{new T[other.m_size]}
		{
            // copy elements from one object to other
			//#ifdef _WIN32
			//    non_std::copy(&(other.m_data[0]), &(other.m_data[other.m_size]), &(m_data[0]));
			//#else
			    std::copy(other.m_data.get(), other.m_data.get() + other.m_size, m_data.get());
			    //std::copy(&(other.m_data[0]), &(other.m_data[other.m_size]), &(m_data[0]));
			//#endif
		}

		dynarray(dynarray&& other)
            : dynarray(0) // call default constructor
		{
            // call swap (copy-and-swap ideom)
            swap(*this, other);
        }

		dynarray& operator=(dynarray other)
		{
            // copy and swap ideom
            swap(*this, other);

			return *this;
		}

		// modifyable reference - get&set
		T& operator[](const size_t index)
		{
			return m_data[index];
		}

		// const version - stop compiler errors to maintain const correctness
		const T& operator[](const size_t index) const
		{
			return m_data[index];
		}

		// range checked
		T& at(const size_t index) const
		{
			if(index < m_size) // m_index
			{
				return m_data[index];
			}
			else
			{
                std::string error_string(std::string("Out-of-range error in dynarray::at(), index=") + std::to_string(index));
                std::cerr << error_string << std::endl;
				throw error_string;
			}
		}

        // return size
        size_t size() const
        {
            return m_size;
        }

        // return index
        // mainly for debug / checking if insertion is possible
        /*
        size_t index() const
        {
            return m_index;
        }
        */

        // sequential insert
        /*
        void put(const T& val)
        {
            if(m_index < m_size)
            {
                m_data[m_index] = val;
                ++ m_index;
            }
            else
            {
                std::string error_string(std::string("Out-of-range error in dynarray::put(), m_index=") + std::to_string(m_index));
                std::cerr << error_string << std::endl;
				throw error_string;
            }
        }
        */

        // return RAW POINTERS - USE WITH CAUTION
		T* beginrawp() const
		{
			return m_data.get(); //&(m_data[0]);
		}

        // POINTS TO ELEMENT BEYOND ARRAY END
		T* endrawp() const
		{
			return m_data.get() + m_size; //&(m_data[m_size]);
		}

        // POINTS TO ELEMENT BEYOND ARRAY END
        /*
        T* backrawp() const
        {
            return *(m_data[m_index]);
        }
        */

        // copy data into array from raw pointer
        // this function does NOT modift the stream insertion pointer
        void copy_in(const T* const data, const size_t n)
        {
            //#ifdef _WIN32
            //    if(n <= m_size)
            //        non_std::copy(&(data[0]), &(data[n]), &(m_data[0]));
            //    else
			//	    non_std::copy(&(data[0]), &(data[m_size]), &(m_data[0]));
		    //#else
		        if(n <= m_size)
                    std::copy(data.get(), data.get() + n, m_data.get());
                else
				{
				    std::copy(data.get(), data.get() + m_size, m_data.get());
				    std::cerr << "dynarray.copy_in() warning" << std::endl;
				}
			//#endif
        }
        
        // copy data using iterator
        //void copy_in()

	};

    // copy and swap ideom
    // swap function implementation
    template<typename T>
    void swap(dynarray<T>& l, dynarray<T>& r)
    {
        // ENABLE ADL
        using std::swap;

        swap(l.m_size, r.m_size);
        //swap(l.m_index, r.m_index);
        swap(l.m_data, r.m_data);
    }

}

#endif
