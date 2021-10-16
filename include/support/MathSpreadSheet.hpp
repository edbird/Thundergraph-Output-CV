
/******************************************************************/
/* COPYRIGHT: E.C. BIRDSALL, MARCH 2016                           */
/******************************************************************/

#ifndef MATHSPREADSHEET_HPP
#define MATHSPREADSHEET_HPP

    /********************************************************
     *
     * CLASS TO REPRESENT MATHEMATICAL DATA
     *
     * THE SUPPORT LIBRARY IS NOT FEATURED IN THE MANUAL
     * IT SHOULD BE CLEAR FROM THE CODE DOCUMENTATION
     * AND EXAMPLE CODE PROVIDED HOW IT CAN BE USED
     *
     ********************************************************/

//#include "algorithm"

#include <iostream>
#include <fstream>
#include <cmath> // user may require this when implementing more complex math operations
#include <vector>

#include "Data.hpp"
#include "SpreadSheet.hpp"

namespace THUNDER
{
    namespace SUPPORT
    {

        // This class works exactly the same as Spreadsheet,
        // but adds new functions which operate on mathematical
        // data types
        template<typename T>
        class MathSpreadSheet : public SpreadSheet<T>
        {

        protected:


        public:

            // Default constructor
            MathSpreadSheet()
                : SpreadSheet<Data<T>>()
            {
            }

            // Capacity initialization constructor
            MathSpreadSheet(const size_t size_x, const size_t size_y)
                : SpreadSheet<Data<T>>(size_x, size_y)
            {
            }

            // Element initialization constructor
            MathSpreadSheet(const size_t size_x, const size_t size_y, const Data<T> val)
                : SpreadSheet<Data<T>>(size_x, size_y, val)
            {

            }

            virtual
            ~MathSpreadSheet()
            {

            }

            // copy column
            // note ranges must be valid and destination must lie to left of source
            void ColCopy(const size_t index_in, const size_t index_out)
            {
                for(size_t y = 0; y < SpreadSheet<T>::SizeY(); ++ y)
                {
                    SpreadSheet<T>::index(index_out, y) = SpreadSheet<T>::index(index_in, y);
                }
            }

            // clear column
            void ColClear(const size_t index)
            {
                for(size_t y = 0; y < SpreadSheet<T>::SizeY(); ++ y)
                {
                    SpreadSheet<T>::index(index, y).Clear();
                }
            }

            // copy row
            // note ranges must be valid and destination must lie to left of source
            void RowCopy(const size_t index_in, const size_t index_out)
            {
                for(size_t x = 0; x < SpreadSheet<T>::SizeX(); ++ x)
                {
                    SpreadSheet<T>::index(x, index_out) = SpreadSheet<T>::index(x, index_in);
                }
            }

            // clear row
            void RowClear(const size_t index)
            {
                for(size_t x = 0; x < SpreadSheet<T>::SizeX(); ++ x)
                {
                    SpreadSheet<T>::index(x, index).Clear();
                }
            }

            // copy block of data
            // note ranges must be valid, and destination must lie to left of source
            void BlockCopy(const size_t index_in_x, const size_t index_in_y, const size_t index_out_x, const size_t index_out_y, const size_t size_x, const size_t size_y)
            {
                size_t out_y = index_out_y;
                size_t y = index_in_y;
                for(; y < index_in_y + size_y; ++ y, ++ out_y)
                {
                    size_t out_x = index_out_x;
                    size_t x = index_in_x;
                    for(; x < index_in_x + size_x; ++ x, ++ out_x)
                    {
                        SpreadSheet<T>::index(out_x, out_y) = SpreadSheet<T>::index(x, y);
                    }
                }
            }

            // clear block of data
            void BlockClear(const size_t index_x, const size_t index_y, const size_t size_x, const size_t size_y)
            {
                for(size_t y = index_y; y < index_y + size_y; ++ y)
                {
                    for(size_t x = index_x; x < index_x + size_x; ++ x)
                    {
                        SpreadSheet<T>::index(x, y).Clear();
                    }
                }
            }

            // add blocks of data
            // note ranges must be valid, and destination must lie to left of source
            void BlockAdd(const size_t index_in_x_1, const size_t index_in_y_1, const size_t index_in_x_2, const size_t index_in_y_2, const size_t index_out_x, const size_t index_out_y, const size_t size_x, const size_t size_y)
            {
                size_t y_1 = index_in_y_1;
                size_t y_2 = index_in_y_2;
                size_t out_y = index_out_y;
                for(; y_1 < index_in_y_1 + size_y; ++ y_1, ++ y_2, ++ out_y)
                {
                    size_t x_1 = index_in_x_1;
                    size_t x_2 = index_in_x_2;
                    size_t out_x = index_out_x;
                    for(; x_1 < index_in_x_1 + size_x; ++ x_1, ++ y_2, ++ out_x)
                    {
                        SpreadSheet<T>::index(out_x, out_y) = SpreadSheet<T>::index(x_1, y_1) + SpreadSheet<T>::index(x_2, y_2);
                    }
                }
            }

            // y=mx+c column rescale
            void ColLinearRescale(const size_t index, const double m, const double c)
            {
                for(size_t y = 0; y < SpreadSheet<T>::SizeY(); ++ y)
                {
                    SpreadSheet<T>::index(index, y).SetValue(m * SpreadSheet<T>::index(index, y).Value() + c);
                }
            }

            // These functions will blow up in your face if you call with an
            // out of range index

            // get mean of row/col
            // row_index flag switches between indexing columns and rows
            double Mean(const size_t index, const bool row_index = false)
            {
                double sum = 0.0;
                size_t count = 0;
                double mean;

                if(row_index == false)
                {
                    for(size_t i = 0; i < SpreadSheet<T>::SizeY(); ++ i)
                    {
                        if(SpreadSheet<T>::Get(index, i).Initialized())
                        {
                            ++ count;
                            sum += static_cast<double>(SpreadSheet<T>::Get(index, i).Value());
                        }
                    }
                }
                else if(row_index == true)
                {
                    for(size_t i = 0; i < SpreadSheet<T>::SizeX(); ++ i)
                    {
                        if(SpreadSheet<T>::Get(i, index).Initialized())
                        {
                            ++ count;
                            sum += static_cast<double>(SpreadSheet<T>::Get(i, index).Value());
                        }
                    }

                }

                // sum and count are now set
                mean = (1.0 / (double)count) * sum;
                return mean;
            }

            // get variance
            // row_index flag switches between indexing columns and rows
            double Var(const size_t index, const bool row_index = false)
            {
                double mean; // compute in this function for memory IO efficicency
                double sum = 0.0;
                double sum_sq = 0.0;
                size_t count = 0;
                double var;

                if(row_index == false)
                {
                    for(size_t i = 0; i < SpreadSheet<T>::SizeY(); ++ i)
                    {
                        if(SpreadSheet<T>::Get(index, i).Initialized())
                        {
                            ++ count;
                            double val = static_cast<double>(SpreadSheet<T>::Get(index, i).Value());
                            sum += val;
                            sum_sq += std::pow(val, 2.0);
                        }
                    }
                }
                else if(row_index == true)
                {
                    for(size_t i = 0; i < SpreadSheet<T>::SizeY(); ++ i)
                    {
                        if(SpreadSheet<T>::Get(index, i).Initialized())
                        {
                            ++ count;
                            double val = static_cast<double>(SpreadSheet<T>::Get(index, i).Value());
                            sum += val;
                            sum_sq += std::pow(val, 2.0);
                        }
                    }
                }

                // sum, sum of squares, and count now set
                //double mean = (1.0 / (double)count) * sum;
                double MEM_A = (1.0 / (double)(count - 1)) * sum_sq;
                double MEM_B = 1.0 / (double)((count - 1) * count);
                var = MEM_A - MEM_B * std::pow(sum, 2.0);
                return var;
            }

            // get standard deviation
            // row_index flag switches between indexing columns and rows
            double StdDev(const size_t index, const bool row_index = false)
            {
                double stddev;
                stddev = sqrt(Var(index, row_index));
                return stddev;
            }

            // return row/col as std::vector
            // row_index flag switches between indexing columns and rows
            std::vector<T> GetSTLVector(const size_t index, const bool row_index = false)
            {
                std::vector<T> ret;

                if(row_index == false)
                {
                    for(size_t i = 0; i < SpreadSheet<T>::SizeY(); ++ i)
                    {
                        if(SpreadSheet<T>::Get(index, i).Initialized())
                        {
                            ret.push_back(SpreadSheet<T>::Get(index, i).Value());
                        }
                    }
                }
                else if(row_index == true)
                {
                    for(size_t i = 0; i < SpreadSheet<T>::SizeY(); ++ i)
                    {
                        if(SpreadSheet<T>::Get(index, i).Initialized())
                        {
                            ret.push_back(SpreadSheet<T>::Get(i, index).Value());
                        }
                    }
                }

                return std::move(ret);
            }

            // Low level read
            void Read(const std::string& filename)
            {
                SpreadSheet<T>::Clear();

                std::ifstream ifile;
                ifile.open(filename.c_str(), std::ios::binary);

                if(ifile.is_open())
                {
                    for(size_t y = 0; y < SpreadSheet<T>::SizeY(); ++ y)
                    {
                        for(size_t x = 0; x < SpreadSheet<T>::SizeX(); ++ x)
                        {
                            char init;
                            ifile.read(&init, sizeof(char));
                            if(init == 'I')
                            {
                                T val;
                                ifile.read((char*)(&val), sizeof(val));
                                Data<T> data(val);
                                SpreadSheet<T>::Put(x, y, data);
                            }
                            else if(init == 'U')
                            {

                            }
                        }
                    }
                }

                ifile.close();
            }

            // Low level write
            void Write(const std::string& filename)
            {
                std::ofstream ofile;
                ofile.open(filename.c_str(), std::ios::binary);

                if(ofile.is_open())
                {
                    for(size_t y = 0; y < SpreadSheet<T>::SizeY(); ++ y)
                    {
                        for(size_t x = 0; x < SpreadSheet<T>::SizeX(); ++ x)
                        {
                            char init;
                            if(SpreadSheet<T>::Get(x, y).Initialized() == true)
                            {
                                init = 'I';
                                ofile.write(&init, sizeof(char));
                                T val{SpreadSheet<T>::Get(x, y).Value()};
                                ofile.write((char*)(&val), sizeof(val));
                            }
                            else
                            {
                                init = 'U';
                                ofile.write(&init, sizeof(char));
                            }
                        }
                    }

                    ofile.flush();
                }
                else
                {
                    std::cerr << "ERROR: Could not open output file " << filename << std::endl;
                }

                ofile.close();
            }

        };

        // typedefs for mathematical types you SHOULD use
        typedef MathSpreadSheet<float> MathSpreadSheetf;
        typedef MathSpreadSheet<double> MathSpreadSheetd;
        typedef MathSpreadSheet<int32_t> MathSpreadSheeti32;
        typedef MathSpreadSheet<uint32_t> MathSpreadSheetui32;
        typedef MathSpreadSheet<int64_t> MathSpreadSheeti64;
        typedef MathSpreadSheet<uint64_t> MathSpreadSheetui64;

    }
}


#endif
