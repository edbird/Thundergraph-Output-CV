
/******************************************************************/
/* COPYRIGHT: E.C. BIRDSALL, MARCH 2016                           */
/******************************************************************/

#ifndef SPREADSHEET_HPP
#define SPREADSHEET_HPP

    /********************************************************
     *
     * CLASS TO REPRESENT SPREADSHEET OBJECT WHICH IS
     * ESSENTIALLY A MATRIX (2D) CONTAINER
     *
     * THE SUPPORT LIBRARY IS NOT FEATURED IN THE MANUAL
     * IT SHOULD BE CLEAR FROM THE CODE DOCUMENTATION
     * AND EXAMPLE CODE PROVIDED HOW IT CAN BE USED
     *
     ********************************************************/

#include <iostream>
#include <memory>

#ifdef _WIN32
    #include "non_std_copy.hpp"
#endif

namespace THUNDER
{
    namespace SUPPORT
    {
        // base class for base class pointers (polymorphism)
        class SpreadSheetBase
        {

        protected:

            virtual
            ~SpreadSheetBase() = 0; // abstract base class

        };

        // Required for complation
        SpreadSheetBase::~SpreadSheetBase() { }

        // spreadsheet implementation
        template <typename T>
        class SpreadSheet : public SpreadSheetBase
        {

            template <typename U>
            friend
            std::ostream& operator<<(std::ostream& os, const SpreadSheet<U>& spreadsheet);

            // copy and swap ideom
            template <typename U>
            friend
            void swap(SpreadSheet<U>& l, SpreadSheet<U>& r);

        protected:

            //std::unique_ptr<T[]> _data;
            size_t _capacity_x; // x and y capacity (allocation size)
            size_t _capacity_y;
            size_t _size_x; // x and y size (number of elements used)
            size_t _size_y;
            T *_data; // allocation (linear, 1D)

        protected:

            // index lookup, returns 1D index from 2D index input
            inline
            size_t index(const size_t x, const size_t y) const
            {
                return (x + y * _capacity_x);
            }

            // Algorithm code
            // Returns the minimum capacity required to store size_x elements
            // Return value is always a power of 2
            // Integer arithmatic for speed
            // This is a highly optimized function, consequently written in an
            // assembly style of code
            inline
            size_t capacity_query(size_t size) const
            {
                if(size == 0) 		    // unsigned integer, cannot call --, return if 0
                    return 0;			//
                -- size;				// decrement input parameter to prevent exact powers of 2 triggering reallocation
                                        // without this: example; 8 -> return 16 (should be 8)
                size_t c = 0;			// counter init
                START:					// loop structure, entry point
                if(size != 0)			// test size_x == 0, if not 0, continue
                {						//
                    size >>= 1;		    // size_x = size_x >> 1, shift bits left by 1, LSB fall off
                    ++ c;				// count number of times SBL required to obtain 0 result
                    goto START;			// jump
                }						//
                                        // shifted size_x >> (SBL) by c bits to get zero result
                                        // hence, 1 << c will be the MSB of size_x if exact power of 2,
                                        // or MSB << 1 if not exact power of 2
                                        // this is equal to the nearest power of 2 required to store
                                        // size_x elements, with contraint that storage allocated
                                        // with size which is a power of 2
                return (1 << c);
            }


        public:

            // Default constructor
            SpreadSheet()
                : _capacity_x{0}
                , _capacity_y{0}
                , _size_x{0}
                , _size_y{0}
                , _data{nullptr}
            {
            }

            // Capacity initialization constructor
            SpreadSheet(const size_t size_x, const size_t size_y)
                : _capacity_x{capacity_query(size_x)}
                , _capacity_y{capacity_query(size_y)}
                , _size_x{0}
                , _size_y{0}
                , _data{_capacity_x * _capacity_y > 0 ? new T[_capacity_x * _capacity_y] : nullptr}
            {
            }

            // Element initialization constructor
            SpreadSheet(const size_t size_x, const size_t size_y, const T val)
                : _capacity_x{capacity_query(size_x)}
                , _capacity_y{capacity_query(size_y)}
                , _size_x{size_x}
                , _size_y{size_y}
                , _data{size_x * size_y > 0 ? new T[_capacity_x * _capacity_y] : nullptr}
            {
                for(size_t j = 0; j < size_y; ++ j)
                {
                    T* const ptr_0{&(_data[index(0, j)])};
                    T* const ptr_1{&(_data[index(_size_x, j)])};

                    // fill all values with val
                    std::fill(ptr_0, ptr_1, val);
                }
            }

            // destructor implementation
            virtual
            ~SpreadSheet()
            {
                delete [] _data;
                _data = nullptr;
                _size_x = 0;
                _size_y = 0;
                _capacity_x = 0;
                _capacity_y = 0;
            }

            // Copy constructor
            SpreadSheet(const SpreadSheet &spreadsheet)
                : _capacity_x{spreadsheet._capacity_x}
                , _capacity_y{spreadsheet._capacity_y}
                , _size_x{spreadsheet._size_x}
                , _size_y{spreadsheet._size_y}
                , _data{_capacity_x * _capacity_y > 0 ? new double[_capacity_x * _capacity_y] : nullptr}
            {
                for(size_t j = 0; j < _size_y; ++ j)
                {
                    T* const ptr_0{&(spreadsheet._data[spreadsheet.index(0, j)])};
                    T* const ptr_1{&(spreadsheet._data[spreadsheet.index(spreadsheet._size_x, j)])};
                    
			        #ifdef _WIN32
					    non_std::copy(ptr_0, ptr_1, &(_data[index(0, j)]));
					#else
					    std::copy(ptr_0, ptr_1, &(_data[index(0, j)]));
					#endif
                }
            }

            // Move constructor
            SpreadSheet(SpreadSheet &&spreadsheet)
                : SpreadSheet()
            {
                // use copy&swap
                swap(*this, spreadsheet);
            }

            // Copy assignment operator
            const SpreadSheet& operator=(const SpreadSheet spreadsheet) // pass by value optimization
            {
                // use copy&swap
                swap(*this, spreadsheet);

                return *this;
            }

        public:

            // return size x
            size_t SizeX() const
            {
                return _size_x;
            }

            size_t SizeY() const
            {
                return _size_y;
            }

            // return capacity x
            size_t CapacityX() const
            {
                return _capacity_x;
            }

            size_t CapacityY() const
            {
                return _capacity_y;
            }

            // clear allocation
            void Clear()
            {
                _capacity_x = 0;
                _capacity_y = 0;
                _size_x = 0;
                _size_y = 0;
                delete [] _data;
                _data = nullptr;
            }


        public:

            // put element val at position x, y
            // auto allocates memory
            void Put(const size_t x, const size_t y, const T& val)
            {
                size_t capacity_x = std::max(_capacity_x, capacity_query(x + 1));
                size_t capacity_y = std::max(_capacity_y, capacity_query(y + 1));
                if(capacity_x != _capacity_x || capacity_y != _capacity_y)
                {
                    //T* data{new T[capacity_x * capacity_y]};
                    try
                    {
                        T* data = new T[capacity_x * capacity_y];

                        for(size_t j = 0; j < _size_y; ++ j)
                        {
                            #ifdef _WIN32
							    non_std::copy(&(_data[index(0, j)]), &(_data[index(_size_x, j)]), &(data[0 + j * capacity_x]));
							#else
							    std::copy(&(_data[index(0, j)]), &(_data[index(_size_x, j)]), &(data[0 + j * capacity_x]));
							#endif    
                        }
                        _capacity_x = capacity_x;
                        _capacity_y = capacity_y;

                        using std::swap;
                        swap(_data, data);

                        delete [] data;
                        data = nullptr;

                        // Split with an else to prevent setting value when memory allocation fails

                        _size_x = std::max(_size_x, x + 1);
                        _size_y = std::max(_size_y, y + 1);

                        _data[index(x, y)] = val;
                    }
                    catch(std::bad_alloc ex)
                    {
                        std::cout << "Memory allocation failure in SpreadSheet::Put()" << std::endl;
                    }
                }

                // Split with an else to prevent setting value when memory allocation fails
                else
                {
                    //std::cout << "Setting value at location " << index(x,y) << " capacity_x is " << _capacity_x << std::endl;
                    _size_x = std::max(_size_x, x + 1);
                    _size_y = std::max(_size_y, y + 1);

                    _data[index(x, y)] = val;
                }
            }

            // get const reference to element
            // can modify element using Put() ONLY!
            const T& Get(const size_t x, const size_t y)
            {
                if(x < _size_x && y < _size_y)
                {
                    return _data[index(x, y)];
                }
                else
                {
                    std::cerr << "Out-of-range error" << std::endl;
                    throw "Out-of-range error";
                }
            }

        };


        template <typename U>
        std::ostream& operator<<(std::ostream& os, const SpreadSheet<U>& spreadsheet)
        {

            // Print matrix content as stream, minimal characters
            // , for element seperated by 1 change in index x
            // ; for element seperated by 1 change in index y

            os << "Matrix content as stream:\n";

            for(size_t j = 0; j < spreadsheet._size_y; ++ j)
            {
                for(size_t i = 0; i < spreadsheet._size_x; ++ i)
                {
                    os << spreadsheet._data[spreadsheet.index(i, j)];
                    if(i == spreadsheet._size_x - 1 && j < spreadsheet._size_y - 1)
                    {
                        os << "; ";
                    }
                    else if(j < spreadsheet._size_y - 1 || i < spreadsheet._size_x - 1)
                    {
                        os << ", ";
                    }
                }
            }

            return os;
        }

        // copy&swap ideom
        template <typename U>
        void swap(SpreadSheet<U>& l, SpreadSheet<U>& r)
        {
            // ENABLE ADL
            using std::swap;

            swap(l._data, r._data);
            swap(l._capacity_x, r._capacity_x);
            swap(l._capacity_y, r._capacity_y);
            swap(l._size_x, r._size_x);
            swap(l._size_y, r._size_y);
        }


    }
}

#endif
