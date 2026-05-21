
#include "json_integer.hpp"

namespace json_internals
{
    __json_integer__::__json_integer__ ()
        : __json__(),
          m_value(0)
    {
    }

    __json_integer__::__json_integer__ (const __json_integer__ &other)
        : __json__(other),
          m_value(other.m_value)
    {

    }
    __json_integer__::__json_integer__ (const long value)
        : __json__(),
          m_value(value)
    {
    }

    __json_integer__::~__json_integer__ ()
    {
    }

    bool __json_integer__::equals (const std::shared_ptr<__json__> &other_p) const
    {
        return   json_internals::json_as_integer(other_p)
               ? m_value == json_internals::json_as_integer(other_p)->m_value
               : false;
    }

    void __json_integer__::set (const long value)
    {
        m_value = value;
    }

    long __json_integer__::value () const
    {
        return m_value;
    }

    std::string __json_integer__::to_string () const
    {
        return std::to_string(m_value);
    }
}

json_integer::json_integer ()
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_integer__>();
}

json_integer::json_integer (const json_integer &other)
    : json(other)
{
}

json_integer::json_integer (const long value)
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_integer__>(value);
}

json_integer::~json_integer ()
{
}

json_integer& json_integer::operator= (const long value)
{
    json_internals::json_as_integer(m_obj_p)->set(value);
    return *this;
}

long json_integer::value () const
{
    return json_internals::json_as_integer(m_obj_p)->value();
}

json::type json_integer::data_type () const
{
    return JSON_INTEGER;
}
