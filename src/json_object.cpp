
#include "json_object.hpp"
#include <sstream>
#include <stdexcept>
#include "utf8.hpp"

namespace json_internals
{
    __json_object__::__json_object__ ()
        : __json__(),
          m_values()
    {}

    __json_object__::__json_object__ (const __json_object__ &other)
        : __json__(other),
          m_values(other.m_values)
    {}

    bool __json_object__::equals (const std::shared_ptr<__json__> &other_p) const
    {
        const std::shared_ptr<const __json_object__> other_object_p = json_internals::json_as_object(other_p);

        if (other_object_p)
            return m_values == other_object_p->m_values;

        return false;
    }

    size_t __json_object__::size () const
    {
        return m_values.size();
    }

    json& __json_object__::operator[] (const std::string &key)
    {
        return m_values[key];
    }

    json __json_object__::get (const std::string &key) const
    {
        return m_values.at(key);
    }

    void __json_object__::set (const std::string &key, const json &value)
    {
        m_values.insert_or_assign(key, value);
    }

    bool __json_object__::exists (const std::string &key) const
    {
        return m_values.find(key) != m_values.end();
    }

    void __json_object__::del (const std::string &key)
    {
        m_values.erase(key);
    }

    void __json_object__::clear ()
    {
        m_values.clear();
    }

    void __json_object__::update (const std::shared_ptr<const __json_object__> &other_p)
    {
        for (const auto &[key, value] : other_p->m_values)
            m_values.insert_or_assign(key, value);
    }

    void __json_object__::update_existing (const std::shared_ptr<const __json_object__> &other_p)
    {
        for (const auto &[key, value] : other_p->m_values)
        {
            auto itr = m_values.find(key);

            if (itr != m_values.end())
                itr->second = value;
        }
    }

    void __json_object__::update_missing (const std::shared_ptr<const __json_object__> &other_p)
    {
        for (const auto &[key, value] : other_p->m_values)
            m_values.emplace(key, value);
    }

    void __json_object__::update_recursive (const std::shared_ptr<const __json_object__> &other_p)
    {
        for (const auto &[key, value] : other_p->m_values)
        {
            auto itr = m_values.find(key);

            if (itr != m_values.end())
            {
                if (itr->second.is_object() && value.is_object())
                    json_as_object(itr->second).update_recursive(json_as_object(value));
                else
                    itr->second = value;
            }
            else
                m_values.emplace(key, value);
        }
    }

    std::string __json_object__::to_string () const
    {
        std::stringstream ss;

        ss << "{";

        bool first = true;

        for (const auto &[key, value] : m_values)
        {
            if (!first)
                ss << ',';

            ss << '"' << key << '"'
               << ":"
               << value.to_string();

            first = false;
        }

        ss << "}";

        return ss.str();
    }
}

json_object::json_object ()
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_object__>();
}

json_object::json_object (const json_object &other)
    : json(other)
{
}

json_object::~json_object ()
{
}

size_t json_object::size () const
{
    return json_internals::json_as_object(m_obj_p)->size();
}

json& json_object::operator[] (const std::string &key)
{
    if (!utf8::check_string(key))
        throw std::runtime_error("utf8 check failed");

    return (*json_internals::json_as_object(m_obj_p))[key];
}

json& json_object::operator[] (const char *key_p)
{
    if (!key_p)
        throw std::runtime_error("key is null");

    return (*this)[std::string(key_p)];
}

json json_object::get (const std::string &key) const
{
    if (!utf8::check_string(key))
        throw std::runtime_error("utf8 check failed");

    return json_internals::json_as_object(m_obj_p)->get(key);
}

json json_object::get (const char *key_p) const
{
    if (!key_p)
        throw std::runtime_error("key is null");

    return get(std::string(key_p));
}

void json_object::set (const std::string &key, const json &value)
{
    if (!utf8::check_string(key))
        throw std::runtime_error("utf8 check failed");

    if (*this == value)
        throw std::runtime_error("invalid value object");

    json_internals::json_as_object(m_obj_p)->set(key, value);
}

void json_object::set (const char *key_p, const json &value)
{
    if (!key_p)
        throw std::runtime_error("key is null");

    set(std::string(key_p), value);
}

bool json_object::exists (const std::string &key) const
{
    if (!utf8::check_string(key))
        throw std::runtime_error("utf8 check failed");

    return json_internals::json_as_object(m_obj_p)->exists(key);
}

bool json_object::exists (const char *key_p) const
{
    if (!key_p)
        throw std::runtime_error("key is null");

    return exists(std::string(key_p));
}

void json_object::del (const std::string &key)
{
    if (!utf8::check_string(key))
        throw std::runtime_error("utf8 check failed");

    json_internals::json_as_object(m_obj_p)->del(key);
}

void json_object::del (const char *key_p)
{
    if (!key_p)
        throw std::runtime_error("key is null");

    del(std::string(key_p));
}

void json_object::clear ()
{
    json_internals::json_as_object(m_obj_p)->clear();
}

void json_object::update (const json_object &other)
{
    json_internals::json_as_object(m_obj_p)->update(json_internals::json_as_object(other.m_obj_p));
}

void json_object::update_existing (const json_object &other)
{
    json_internals::json_as_object(m_obj_p)->update_existing(json_internals::json_as_object(other.m_obj_p));
}

void json_object::update_missing (const json_object &other)
{
    json_internals::json_as_object(m_obj_p)->update_missing(json_internals::json_as_object(other.m_obj_p));
}

void json_object::update_recursive (const json_object &other)
{
    json_internals::json_as_object(m_obj_p)->update_recursive(json_internals::json_as_object(other.m_obj_p));
}

json::type json_object::data_type () const
{
    return JSON_OBJECT;
}
