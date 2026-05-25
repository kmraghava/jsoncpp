
#include "json_string.hpp"
#include <stdexcept>
#include "utf8.hpp"

namespace json_internals
{
    __json_string__::__json_string__ ()
        : __json__(),
          m_value()
    {
    }

    __json_string__::__json_string__ (const __json_string__ &other)
        : __json__(other),
          m_value(other.m_value)
    {
    }

    __json_string__::__json_string__ (const std::string &s)
        : __json__(),
          m_value(s)
    {
    }

    __json_string__::~__json_string__ ()
    {
    }

    bool __json_string__::equals (const std::shared_ptr<__json__> &other_p) const
    {
        return m_value == json_internals::json_as_string(other_p)->m_value;
    }

    size_t __json_string__::length () const
    {
        return m_value.length();
    }

    void __json_string__::set (const std::string &s)
    {
        m_value = s;
    }

    std::string __json_string__::value () const
    {
        return m_value;
    }

    std::string __json_string__::to_string () const
    {
        std::string  str;
        
        str.reserve(3 + m_value.length());

        str = '"';
        str += m_value;
        str += '"';

        return str;
    }

    __json__::type __json_string__::data_type () const
    {
        return type_string;
    }

    __json__* __json_string__::clone () const
    {
        return new __json_string__(m_value);
    }
}

json_string::json_string ()
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_string__>();
}

json_string::json_string (const json_string &other)
    : json(other)
{
}

json_string::json_string (const std::shared_ptr<json_internals::__json__> &obj_p)
    : json(obj_p)
{
}

json_string::json_string (const std::string &s)
    : json()
{
    if (!utf8::check_string(s))
        throw std::runtime_error("utf8 check failed");

    m_obj_p = std::make_shared<json_internals::__json_string__>(s);
}

json_string::json_string (const char *s)
    : json()
{
    if (!s)
        throw std::runtime_error("s is null");

    if (!utf8::check_string(s))
        throw std::runtime_error("utf8 check failed");

    m_obj_p = std::make_shared<json_internals::__json_string__>(std::string(s));
}

json_string::json_string (const char *s, size_t len)
    : json()
{
    if (!s)
        throw std::runtime_error("s is null");

    if (!utf8::check_string(s, len))
        throw std::runtime_error("utf8 check failed");

    m_obj_p = std::make_shared<json_internals::__json_string__>(std::string(s, len));
}

json_string::~json_string ()
{
}

size_t json_string::length () const
{
    return json_internals::json_as_string(m_obj_p)->length();
}

json_string& json_string::operator= (const std::string &s)
{
    set(s);
    return *this;
}

json_string& json_string::operator= (const char *s)
{
    set(s);
    return *this;
}

void json_string::set (const std::string &s)
{
    if (!utf8::check_string(s))
        throw std::runtime_error("utf8 check failed");

    json_internals::json_as_string(m_obj_p)->set(s);
}

void json_string::set (const char *s)
{
    if (!s)
        throw std::runtime_error("s is null");

    set(std::string(s));
}

void json_string::set (const char *s, size_t len)
{
    if (!s)
        throw std::runtime_error("s is null");

    set(std::string(s, len));
}

std::string json_string::value () const
{
    return json_internals::json_as_string(m_obj_p)->value();
}

json_string json_as_string (json jobj)
{
    if (jobj.m_obj_p->data_type() != json_internals::__json__::type_string)
        throw std::bad_cast();

    return json_string(jobj.m_obj_p);
}
