#ifndef __FILE_SYSTEM_FILE_SYSTEM_HPP__
#define __FILE_SYSTEM_FILE_SYSTEM_HPP__

#include <string>
#include <vector>

#include "file_system/common_exception.hpp"

struct DirectoryNotExist : virtual exception_common_base {};

#define EXCEPTION_DIR_NOT_EXIST(d) \
    {\
        std::stringstream d##_ss; \
        d##_ss << "Directory " << d << " does not exist. "; \
        BOOST_THROW_EXCEPTION( DirectoryNotExist() << ExceptionInfoString(d##_ss.str()) ); \
    }

std::vector<std::string> get_file_parts(const std::string& path);

void test_directory(const std::string& dir);

void test_directory_by_filename( const std::string& fn );

bool test_file( const std::string &fn );

std::vector<std::string> read_file_list(const std::string& fn);

std::vector<std::string> find_files_recursively( 
    const std::string &pathStr, 
    const std::string &pattern );

#endif // __FILE_SYSTEM_FILE_SYSTEM_HPP__