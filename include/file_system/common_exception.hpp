#ifndef __FILE_SYSTEM_COMMON_EXCEPTION_HPP__
#define __FILE_SYSTEM_COMMON_EXCEPTION_HPP__

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/exception/all.hpp>

struct exception_common_base    : virtual std::exception, virtual boost::exception { };
struct not_implemented          : virtual exception_common_base {};
struct file_not_good            : virtual exception_common_base {};
struct eigen_row_major          : virtual exception_common_base {};
struct FileExists               : virtual exception_common_base {};

typedef boost::error_info<struct tag_info_string, std::string> ExceptionInfoString;

#define EXCEPTION_NOT_IMPLEMENTED(name) \
    {\
        std::stringstream name##_ss; \
        name##_ss << #name << " is not implemented. "; \
        BOOST_THROW_EXCEPTION( not_implemented() << ExceptionInfoString(name##_ss.str()) ); \
    }

#define EXCEPTION_FILE_NOT_GOOD(fn) \
    {\
        std::stringstream fn##_ss; \
        fn##_ss << "File " << fn << " is not good. "; \
        BOOST_THROW_EXCEPTION( file_not_good() << ExceptionInfoString(fn##_ss.str()) ); \
    }

#define EXCEPTION_FILE_EXISTS(fn) \
    {\
        std::stringstream fn##_ss; \
        fn##_ss << "File " << fn << " exists. "; \
        BOOST_THROW_EXCEPTION( FileExists() << ExceptionInfoString(fn##_ss.str()) ); \
    }

#define EXCEPTION_EIGEN_ROW_MAJOR(m) \
    {\
        std::stringstream m##_ss; \
        m##_ss << #m << " is row major. "; \
        BOOST_THROW_EXCEPTION( eigen_row_major() << ExceptionInfoString( m##_ss.str() ) ); \
    }

#define EXCEPTION_DIAG_INFO(ex) \
    boost::diagnostic_information(ex)

#endif // __FILE_SYSTEM_COMMON_EXCEPTION_HPP__