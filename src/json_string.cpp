
#include "json.hpp"

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

    __json_string__::__json_string__ (const char *s)
        : __json__(),
          m_value(s)
    {
    }

    __json_string__::__json_string__ (const char *s, size_t len)
        : __json__(),
          m_value(s, len)
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

    void __json_string__::set (const std::string &s)
    {
        m_value = s;
    }

    void __json_string__::set (const char *s)
    {
        m_value = std::string(s);
    }

    void __json_string__::set (const char *s, size_t len)
    {
        m_value = std::string(s, len);
    }

    bool __json_string__::equals (const std::shared_ptr<__json__> &other_p) const
    {
        return   json_internals::json_as_string(other_p)
               ? m_value == json_internals::json_as_string(other_p)->m_value
               : false;
    }

    size_t __json_string__::length () const
    {
        return m_value.length();
    }

    const std::string& __json_string__::value () const
    {
        return m_value;
    }

    std::string& __json_string__::value ()
    {
        return m_value;
    }

    std::string __json_string__::to_string () const
    {
        return m_value;
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

json_string::json_string (const char *s)
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_string__>(s);
}

json_string::json_string (const char *s, size_t len)
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_string__>(s, len);
}

json_string::json_string (const std::string &s)
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_string__>(s);
}

json_string::~json_string ()
{
}

json_string& json_string::operator= (const std::string &s)
{
    json_internals::json_as_string(m_obj_p)->set(s);
    return *this;
}

json_string& json_string::operator= (const char *s)
{
    json_internals::json_as_string(m_obj_p)->set(s);
    return *this;
}

void json_string::set (const char *s, size_t len)
{
    json_internals::json_as_string(m_obj_p)->set(s, len);
}

size_t json_string::length () const
{
    return json_internals::json_as_string(m_obj_p)->length();
}

const std::string& json_string::value () const
{
    return json_internals::json_as_string(m_obj_p)->value();
}

std::string& json_string::value ()
{
    return json_internals::json_as_string(m_obj_p)->value();
}

json::type json_string::data_type () const
{
    return JSON_STRING;
}
