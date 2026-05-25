
#include "json_array.hpp"
#include <stdexcept>
#include <sstream>

namespace json_internals
{
    __json_array__::__json_array__ ()
        : __json__(),
          m_values()
    {
    }

    __json_array__::__json_array__ (const __json_array__ &other)
        : __json__(other),
          m_values(other.m_values)
    {

    }
    __json_array__::__json_array__ (const std::vector<json> &values)
        : __json__(),
          m_values(values)
    {
    }

    void __json_array__::set (const std::vector<json> &values)
    {
        m_values = values;
    }

    bool __json_array__::equals (const std::shared_ptr<__json__> &other_p) const
    {
        return m_values == json_internals::json_as_array(other_p)->m_values;
    }

    size_t __json_array__::size () const
    {
        return m_values.size();
    }

    json& __json_array__::operator[] (size_t index)
    {
        if (index >= m_values.size())
            throw std::out_of_range("index out of range");

        return m_values[index];
    }

    json __json_array__::get (size_t index) const
    {
        if (index >= m_values.size())
            throw std::out_of_range("index out of range");

        return m_values[index];
    }

    void __json_array__::set (size_t index, const json &value)
    {
        if (index >= m_values.size())
            throw std::out_of_range("index out of range");

        m_values[index] = value;
    }

    void __json_array__::append (const json &value)
    {
        m_values.push_back(value);
    }

    void __json_array__::insert (size_t index, const json &value)
    {
        if (index >= m_values.size())
            throw std::out_of_range("index out of range");

        m_values.insert(m_values.begin() + index, value);
    }

    void __json_array__::remove (size_t index)
    {
        if (index >= m_values.size())
            throw std::out_of_range("index out of range");

        m_values.erase(m_values.begin() + index);
    }

    void __json_array__::clear ()
    {
        m_values.clear();
    }

    void __json_array__::extend (const std::shared_ptr<const __json_array__> &other_p)
    {
        m_values.insert(m_values.end(), other_p->m_values.begin(), other_p->m_values.end());
    }

    std::string __json_array__::to_string () const
    {
        std::stringstream  ss;

        ss << "[";

        if (size() > 0)
            ss << m_values[0].to_string();

        for (size_t ii = 1; ii < size(); ii++)
            ss << ", " << m_values[ii].to_string();

        ss << "]";

        return ss.str();
    }

    __json__::type __json_array__::data_type () const
    {
        return type_array;
    }

    __json__* __json_array__::clone () const
    {
        __json_array__  *clone_array_p = new __json_array__();

        for (size_t ii = 0; ii < size(); ii++)
            clone_array_p->append(m_values[ii].clone());

        return clone_array_p;
    }
}


json_array::json_array ()
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_array__>();
}

json_array::json_array (const json_array &other)
    : json(other)
{
}

json_array::json_array (const std::shared_ptr<json_internals::__json__> &obj_p)
    : json(obj_p)
{
}

json_array::json_array (const std::vector<json> &values)
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_array__>(values);
}

json_array::~json_array ()
{
}

json_array& json_array::operator= (const std::vector<json> &values)
{
    json_internals::json_as_array(m_obj_p)->set(values);
    return *this;
}

size_t json_array::size () const
{
    return json_internals::json_as_array(m_obj_p)->size();
}

json& json_array::operator[] (size_t index)
{
    return (*json_internals::json_as_array(m_obj_p))[index];
}

json json_array::get (size_t index) const
{
    return json_internals::json_as_array(m_obj_p)->get(index);
}

void json_array::set (size_t index, const json &value)
{
    if (*this == value)
        throw std::runtime_error("invalid value array");

    json_internals::json_as_array(m_obj_p)->set(index, value);
}

void json_array::append (const json &value)
{
    if (*this == value)
        throw std::runtime_error("invalid value array");

    json_internals::json_as_array(m_obj_p)->append(value);
}

void json_array::insert (size_t index, const json &value)
{
    if (*this == value)
        throw std::runtime_error("invalid value array");

    json_internals::json_as_array(m_obj_p)->insert(index, value);
}

void json_array::remove (size_t index)
{
    json_internals::json_as_array(m_obj_p)->remove(index);
}

void json_array::clear ()
{
    json_internals::json_as_array(m_obj_p)->clear();
}

void json_array::extend (const json_array &other)
{
    json_internals::json_as_array(m_obj_p)->extend(json_internals::json_as_array(other.m_obj_p));
}

json_array json_as_array (json jobj)
{
    if (jobj.m_obj_p->data_type() != json_internals::__json__::type_array)
        throw std::bad_cast();

    return json_array(jobj.m_obj_p);
}
