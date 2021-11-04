
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include "file_system/file_system.hpp"

std::vector<std::string> get_file_parts(const std::string& path) {
    std::filesystem::path p(path);

    std::vector<std::string> parts;

    parts.push_back( p.parent_path().string() );
    parts.push_back( p.stem().string() );
    parts.push_back( p.extension().string() );

    if ( 0 == parts[0].length() ) {
        parts[0] = "./";
    }

    return parts;
}

void test_directory(const std::string& dir) {
    std::filesystem::path p(dir);

    if ( !std::filesystem::is_directory(p) ) {
        // Create the directory.
        try {
            std::filesystem::create_directories(p);
        } catch ( std::filesystem::filesystem_error& err ) {
            std::stringstream ss;
            ss << "Create directory " << dir << " failed. ";
            throw(std::runtime_error(ss.str()));
        }
    }
}

void test_directory_by_filename( const std::string& fn ) {
    // Get the file parts.
    auto parts = get_file_parts(fn);

    // Test the output directory.
    test_directory( parts[0] );
}

bool test_file( const std::string &fn ) {
    std::filesystem::path p(fn);

    return std::filesystem::is_regular_file(p);
}

std::vector<std::string> read_file_list(const std::string& fn)
{
    std::vector<std::string> fList;
    std::string line;

    std::ifstream ifs(fn);

    if ( ifs.is_open() ) {
        std::size_t count = 0;

        while( std::getline(ifs, line) ) {
            count++;

            boost::algorithm::trim(line);

            if ( !line.empty() ) {
                fList.push_back(line);
            } else {
                std::cout << "Empty line at Line " << count << std::endl;
            }
        }
    } else {
        std::stringstream ss;
        ss << "File " << fn << " not opened.";
        throw(std::runtime_error(ss.str()));
    }

    ifs.close();

    return fList;
}

std::vector<std::string> find_files_recursively( const std::string &pathStr, const std::string &pattern ) {
    namespace fs = std::filesystem;

    fs::path path(pathStr);

    if ( !fs::exists(path) || !fs::is_directory(path) ) {
        EXCEPTION_DIR_NOT_EXIST(pathStr)
    }

    fs::recursive_directory_iterator iter(path);
    fs::recursive_directory_iterator end;

    std::regex re(pattern);

    std::vector<std::string> files;
    while ( iter != end ) {
        if ( fs::is_regular_file(*iter) ) {
            if ( std::regex_search( iter->path().string(), re ) ) {
                files.push_back( iter->path().string() );
            }
        }
        ++iter;
    }

    // Sort.
    if ( !files.empty() ) std::sort( files.begin(), files.end() );

    return files;
}

