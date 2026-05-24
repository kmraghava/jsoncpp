
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <sstream>

static std::string read_file (std::ifstream &stream)
{
    std::stringstream  ss;

    ss << stream.rdbuf();

    return ss.str();
}

static std::string trim (std::string &s)
{
    std::size_t  begin = 0,
                 end = s.size();

    while (begin < end && std::isspace(s[begin])) begin++;
    while (begin < end && std::isspace(s[end-1])) end--;

    return s.substr(begin, end);
}

int main (int argc, char *argv[])
{
    if (argc != 2)
        return 0;

    std::string    test_name = argv[1];
    std::string    input_file = test_name + "/input";
    std::string    ouput_file = test_name + "/output";

    std::ifstream  input_stream(input_file.c_str());
    std::ifstream  ouput_stream(ouput_file.c_str());

    if (!input_stream)  { std::cout << "failed to open input file: "           << input_file << std::endl; return 0; }
    if (!ouput_stream)  { std::cout << "failed to open expected output file: " << ouput_file << std::endl; return 0; }

    std::string  expected_output,
                 output;

    expected_output = read_file(ouput_stream);
    expected_output = trim(expected_output);

    try
    {
        json  jobj = json::parse(input_stream);
        
        output = jobj.to_string();
    }
    catch (const std::exception &e)
    {
        output = e.what();
    }

    if (output == expected_output)
        std::cout << "PASSED: " << test_name << std::endl;
    else
        std::cout << "FAILED: " << test_name << " | output: " << output << " | expected_output: " << expected_output << std::endl;

    return 0;
}
