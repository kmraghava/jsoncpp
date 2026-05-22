
#include <charconv>
#include <cstring>
#include <iostream>
#include "json.hpp"
#include <stdexcept>

json json::parse (std::istream &stream)
{
    json  jobj;

    // Slurp up leading white spaces
    stream >> std::ws;

    char ch = stream.peek();
    if (ch == EOF)
        throw std::runtime_error("unexpected end of stream");

    if (ch == '{')
        jobj = parse_object(stream);

    else if (ch == '[')
        jobj = parse_array(stream);

    else if (ch == '"')
        jobj = parse_string(stream);

    else if (ch == 'f')
        jobj = parse_false(stream);

    else if (ch == 't')
        jobj = parse_true(stream);

    else if (ch == '-' || ch == '+' || (ch >= '0' && ch <= '9'))
        jobj = parse_number(stream);

    else
        throw std::runtime_error("unexpected token");

    return jobj;
}

json json::parse_object (std::istream &stream)
{
    json_object  jobj;
    std::string  key;
    char         ch;

    // Consume the leading '{'
    ch = stream.get();

    while (true)
    {
        // Slurp up any white spaces
        stream >> std::ws;

        // Empty object
        if (ch == '{' && stream.peek() == '}')
        {
            stream.get();
            break;
        }

        if (stream.peek() != '"')
            throw std::runtime_error("unexpected token when parsing object key");

        key = parse_cstring(stream);

        // Slurp up any white spaces
        stream >> std::ws;

        if (stream.get() != ':')
            throw std::runtime_error("unexpected token when parsing object separator");

        // Slurp up any white spaces
        stream >> std::ws;

        jobj.set(key, parse(stream));

        // Slurp up any white spaces
        stream >> std::ws;

        ch = stream.get();
        
        if (ch == ',')
            continue;
        
        if (ch == '}')
            break;

        throw std::runtime_error("unexpected token when parsing object");
    }

    return jobj;
}

json json::parse_array (std::istream &stream)
{
    json_array  jarray;
    char        ch;

    // Consume the leading '['
    ch = stream.get();

    while (true)
    {
        // Slurp up any white spaces
        stream >> std::ws;

        // Empty object
        if (ch == '[' && stream.peek() == ']')
        {
            stream.get();
            break;
        }

        jarray.append(parse(stream));

        // Slurp up any white spaces
        stream >> std::ws;

        ch = stream.get();
        
        if (ch == ',')
            continue;
        
        if (ch == ']')
            break;

        throw std::runtime_error("unexpected token when parsing array");
    }

    return jarray;
}

json json::parse_string (std::istream &stream)
{
    return json_string(parse_cstring(stream));
}

json json::parse_false (std::istream &stream)
{
    char  buf[5];

    stream.read(buf, 5);

    if (stream.gcount() != 5)
        throw std::runtime_error("unexpected end of stream when parsing false");

    if (std::memcmp(buf, "false", 5) != 0)
        throw std::runtime_error("unexpected token when parsing false");

    return json_false();
}

json json::parse_true (std::istream &stream)
{
    char  buf[4];

    stream.read(buf, 4);

    if (stream.gcount() != 4)
        throw std::runtime_error("unexpected end of stream when parsing true");

    if (std::memcmp(buf, "true", 4) != 0)
        throw std::runtime_error("unexpected token when parsing true");

    return json_true();
}

json json::parse_number (std::istream &stream)
{
    json         num;
    std::string  num_str;
    char         ch;

    /* No JSON integer / real number is > 64 bytes in size.
     * So, reserve 64 bytes to avoid reallocs.
     */
    num_str.reserve(64);

    ch = stream.peek();
    while (   ch == '-'
           || ch == '+'
           || (ch >= '0' && ch <='9')
           || ch == 'e'
           || ch == 'E'
           || ch == '.'
          )
    {
        num_str += stream.get();
        ch = stream.peek();
    }

    // 1. Is it a floating-point number? 
    // JSON numbers with a decimal point '.' or scientific notation 'e'/'E' are floats.
    if (   num_str.find('.') != std::string::npos
        || num_str.find('e') != std::string::npos
        || num_str.find('E') != std::string::npos
       )
    {
        double value;

        // Pass the start pointer and end pointer of our text view
        auto [ptr, ec] = std::from_chars(num_str.data(), 
                                         num_str.data() + num_str.size(), 
                                         value);
        
        // std::errc{} means no error occurred
        if (ec != std::errc{} || ptr != num_str.data() + num_str.size())
            throw std::runtime_error("invalid floating-point number");

        num = json_real(value);
    } 
    
    // 2. Otherwise, treat it as an integer
    else
    {
        long value;

        auto [ptr, ec] = std::from_chars(num_str.data(), 
                                         num_str.data() + num_str.size(), 
                                         value);
        
        if (ec != std::errc{} || ptr != num_str.data() + num_str.size())
            throw std::runtime_error("invalid integer");

        num = json_integer(value);
    }

    return num;
}

std::string json::parse_cstring (std::istream& stream)
{
    std::string str;

    // Consume the leading '"'
    stream.get();

    // Read until trailing '"'
    if (!std::getline(stream, str, '"'))
        throw std::runtime_error("unterminated string");

    return str;
}
