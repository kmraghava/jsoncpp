
#include "json_real.hpp"

namespace json_internals
{
    __json_real__::__json_real__ ()
        : __json__(),
          m_value(0.0)
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
        return m_value == json_internals::json_as_real(other_p)->m_value;
    }

    void __json_real__::set (const double value)
    {
        m_value = value;
    }

    double __json_real__::value () const
    {
        return m_value;
    }

    std::string __json_real__::to_string () const
    {
        return std::to_string(m_value);
    }

    __json__::type __json_real__::data_type () const
    {
        return type_real;
    }

    __json__* __json_real__::clone () const
    {
        return new __json_real__(m_value);
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

json_real::json_real (const std::shared_ptr<json_internals::__json__> &obj_p)
    : json(obj_p)
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

double json_real::value () const
{
    return json_internals::json_as_real(m_obj_p)->value();
}

json_real json_as_real (json jobj)
{
    if (jobj.m_obj_p->data_type() != json_internals::__json__::type_real)
        throw std::bad_cast();

    return json_real(jobj.m_obj_p);
}
