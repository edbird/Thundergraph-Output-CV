
/******************************************************************/
/* COPYRIGHT: E.C. BIRDSALL, MARCH 2016                           */
/******************************************************************/

#ifndef DATA_HPP
#define DATA_HPP


    /********************************************************
     *
     * CLASS TO REPRESENT DATA WITH AN INITILIZATION FLAG
     *
     * THE SUPPORT LIBRARY IS NOT FEATURED IN THE MANUAL
     * IT SHOULD BE CLEAR FROM THE CODE DOCUMENTATION
     * AND EXAMPLE CODE PROVIDED HOW IT CAN BE USED
     *
     ********************************************************/

#include <iostream>
#include <string>

namespace THUNDER
{
    namespace SUPPORT
    {

        // template class, represent any template type of data
        template <typename T>
        class Data
        {

            template <typename U>
            friend
            std::ostream& operator<<(std::ostream& os, const Data& data);

        protected:

            // initilzation flag
            bool _initialized;
            // value
            T _value;

        public:

            // default constructor
            Data()
                // NOTE: A COMPILER WARNING APPEARS HERE BECAUSE
                // _value IS NOT INITIALIZED - THIS IS CORRECT
                // AND THE COMPILER WARNING SHOULD BE IGNORED
                // BECAUSE WE DO NOT KNOW WHAT VALUE TO INITIALIZE
                // _value TO YET, IT SHOULD REMAIN UNINITIALIZED
                : _initialized{false}
            {
            }

            // constructor to initialize _value
            Data(const T& value)
                : _initialized{true}
                , _value{value}
            {
            }

            virtual
            ~Data()
            {
            }

            // use default move, copy assignment/constructor

            // set value of _value (data)
            void SetValue(const T& value) const
            {
                _value = value;
                _initialized = true;
            }

            // get value as const reference
            const T& Value() const
            {
                if(_initialized)
                {
                    return _value;
                }
                else
                {
                    // return value, but also print warning for uninitialized data
                    std::string error_string("[WARN] value not initialized in Data::Value()");
                    std::clog << error_string << std::endl;
                    return _value;

                    // disabled the error throwing
                    //std::cerr << error_string << std::endl;
                    //throw error_string;
                }
            }

            // get initialization flag
            bool Initialized() const
            {
                return _initialized;
            }

            // clear initialization flag
            void Clear() const
            {
                _initialized = false;
            }

        };

        template <typename U>
        std::ostream& operator<<(std::ostream& os, const Data<U>& data)
        {
            os << data.Value();

            return os;
        }

    }
}

#endif
