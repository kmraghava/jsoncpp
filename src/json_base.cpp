
#include "json_base.hpp"

json::json ()
    : m_obj_p(NULL)
{
}

json::json (const json &other)
    : m_obj_p(other.m_obj_p)
{
}

json& json::operator= (const json &other)
{
    m_obj_p = other.m_obj_p;
    return *this;
}

json::type json::data_type () const
{
    return JSON_UNKNOWN;
}

std::string json::to_string () const
{
    return m_obj_p->to_string();
}

bool json::is_string () const
{
    return data_type() == JSON_STRING;
}

bool json::is_real () const
{
    return data_type() == JSON_REAL;
}

bool json::is_integer () const
{
    return data_type() == JSON_INTEGER;
}

bool json::is_false () const
{
    return data_type() == JSON_FALSE;
}

bool json::is_true () const
{
    return data_type() == JSON_TRUE;
}

bool json::is_bool () const
{
    return is_false() || is_true();
}

bool json::is_array () const
{
    return data_type() == JSON_ARRAY;
}

bool json::is_object () const
{
    return data_type() == JSON_OBJECT;
}

bool json::operator== (const json &other) const
{
    return m_obj_p == other.m_obj_p;
}

bool json::operator!= (const json &other) const
{
    return !(*this == other);
}

bool json::equals (const json &other) const
{
    return   m_obj_p
           ? m_obj_p->equals(other.m_obj_p)
           : false;
}
