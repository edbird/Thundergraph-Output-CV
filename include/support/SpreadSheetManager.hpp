
/******************************************************************/
/* COPYRIGHT: E.C. BIRDSALL, MARCH 2016                           */
/******************************************************************/

#ifndef SPREADSHEETMANAGER_HPP
#define SPREADSHEETMANAGER_HPP

    /********************************************************
     *
     * CLASS TO MANAGE SET OF SPREADSHEETS USING STRING
     * LOOKUP WITH std::map
     *
     * THE SUPPORT LIBRARY IS NOT FEATURED IN THE MANUAL
     * IT SHOULD BE CLEAR FROM THE CODE DOCUMENTATION
     * AND EXAMPLE CODE PROVIDED HOW IT CAN BE USED
     *
     ********************************************************/

#include <map>
#include <functional>
#include <typeinfo>
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "SpreadSheet.hpp"

namespace THUNDER
{
    namespace SUPPORT
    {

		typedef std::map<std::string, SpreadSheetBase*, std::function<bool(const std::string&, const std::string&)>> spreadsheetmanager_map;

        // Manage a map of spreadsheets using using string keys
        // NOTE: THIS CLASS MANAGES BASECLASS POINTERS TO SPREADSHEET OBJECTS
        // THEREFORE THOSE OBJECTS MUST EXIST FOR THE LIFETIME OF THE EXISTANCE
        // OF BASECLASS POINTERS IN THIS CLASS
        class SpreadSheetManager
        {

        protected:

            //std::vector<SpreadSheetBase*> _sheet;
			//std::map<std::string, SpreadSheetBase*> _sheetmap;
			spreadsheetmanager_map _sheetmap;

        public:

            // default constructor, do nothing, memory managed with std::map
			SpreadSheetManager()
				: _sheetmap([](const std::string& a, const std::string& b) { return a < b; })
            {
            }

            // do not expect the user to inherit from this class,
            // but allow for possibility
            // not technically required since no memory manually allocated
            // in this class
            virtual
            ~SpreadSheetManager()
            {

            }

            // insert sheet with std::string key
            //template <typename T>
            void InsertSheet(const std::string unique_text_key, const SpreadSheetBase* const sheet)
            {
                if(_sheetmap.find(unique_text_key) == _sheetmap.end())
                {
                    /*const*/ //SpreadSheetBase* sheet_copy = new SpreadSheet<T>;//(sheet);
                    //*sheet_copy = sheet;
                    //_sheetmap.insert(std::pair<std::string, SpreadSheetBase*>(unique_text_key, const_cast<SpreadSheetBase*>(sheet_copy)));
                    _sheetmap.insert(std::pair<std::string, SpreadSheetBase*>(unique_text_key, const_cast<SpreadSheetBase*>(sheet)));
                }
                else
                {
                    std::string error_string("Error in SpreadSheetManager::InsertSheet(), unique_text_key is not unique in std::map");
                    std::cerr << error_string << std::endl;
                    throw error_string;
                }
            }

            // remove sheet pointed at by unique_text_key
            void EraseSheet(const std::string unique_text_key)
            {
                std::map<std::string, SpreadSheetBase*>::const_iterator it = _sheetmap.find(unique_text_key);
                if(it != _sheetmap.end())
                {
                    #if DEBUG
                    std::cout << "Found sheet at index" << std::distance<std::map<std::string, SpreadSheetBase*>::const_iterator>(_sheetmap.begin(), it) << std::endl;
                    #endif
                    _sheetmap.erase(it);
                }
                else
                {
                    std::string error_string("Error in SpreadSheetManager::EraseSheet(), unique_text_key is not a key in std::map");
                    std::cerr << error_string << std::endl;
                    throw error_string;
                }
            }

            // get pointer to spreadsheet
            // must cast before using
            SpreadSheetBase* GetSheet(const std::string unique_text_key) const
            {
                std::map<std::string, SpreadSheetBase*>::const_iterator it = _sheetmap.find(unique_text_key);
                if(it != _sheetmap.end())
                {
                    return it->second;
                }
                else
                {
                    std::string error_string("Error in SpreadSheetManager::GetSheet(), unique_text_key is not a key in std::map");
                    std::cerr << error_string << std::endl;
                    throw error_string;
                }
            }

            // clear entries in _sheetmap
            void Clear()
            {
                _sheetmap.clear();
            }

        };

    }
}

#endif
