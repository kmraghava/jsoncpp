
#include "json.hpp"

namespace json_internals
{
    __json_real__::__json_real__ ()
        : __json__(),
          m_value(0)
    {
    }

    __json_real__::__json_real__ (const __json_real__ &other)
        : __json__(other),
          m_value(other.m_value)
    {
    }

    __json_real__::__json_real__ (const double value)
        : __json__(),
          m_value(value)
    {
    }

    __json_real__::~__json_real__ ()
    {
    }

    bool __json_real__::equals (const std::shared_ptr<__json__> &other_p) const
    {
        return   json_internals::json_as_real(other_p)
               ? m_value == json_internals::json_as_real(other_p)->m_value
               : false;
    }

    void __json_real__::set (const double value)
    {
        m_value = value;
    }

    const double& __json_real__::value () const
    {
        return m_value;
    }

    double& __json_real__::value ()
    {
        return m_value;
    }

    std::string __json_real__::to_string () const
    {
        return std::to_string(m_value);
    }
}

json_real::json_real ()
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_real__>();
}

json_real::json_real (const json_real &other)
    : json(other)
{
}

json_real::json_real (const double value)
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_real__>(value);
}

json_real::~json_real ()
{
}

json_real& json_real::operator= (const double value)
{
    json_internals::json_as_real(m_obj_p)->set(value);
    return *this;
}

const double& json_real::value () const
{
    return json_internals::json_as_real(m_obj_p)->value();
}

double& json_real::value ()
{
    return json_internals::json_as_real(m_obj_p)->value();
}

json::type json_real::data_type () const
{
    return JSON_REAL;
}
