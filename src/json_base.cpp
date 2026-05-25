
#include "json_base.hpp"

namespace json_internals
{
    class __json_bad__ : public __json__
    {
        public:
            __json_bad__ ()
                : __json__()
            {
            }

            __json_bad__ (const __json_bad__ &other)
                : __json__(other)
            {
            }

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const override
            {
                return other_p->data_type() == type_unknown;
            }

            virtual std::string to_string () const override
            {
                return "";
            }

            virtual type data_type () const override
            {
                return type_unknown;
            }

            virtual __json__* clone () const override
            {
                return new __json_bad__();
            }
    };
}

json::json ()
{
    m_obj_p = std::make_shared<json_internals::__json_bad__>();
}

json::json (const json &other)
    : m_obj_p(other.m_obj_p)
{
}

json::json (const std::shared_ptr<json_internals::__json__> &obj_p)
    : m_obj_p(obj_p)
{
}

json& json::operator= (const json &other)
{
    m_obj_p = other.m_obj_p;
    return *this;
}

std::string json::to_string () const
{
    return m_obj_p->to_string();
}

bool json::is_string  () const { return m_obj_p->data_type() == json_internals::__json__::type_string;  }
bool json::is_integer () const { return m_obj_p->data_type() == json_internals::__json__::type_integer; }
bool json::is_real    () const { return m_obj_p->data_type() == json_internals::__json__::type_real;    }
bool json::is_false   () const { return m_obj_p->data_type() == json_internals::__json__::type_false;   }
bool json::is_true    () const { return m_obj_p->data_type() == json_internals::__json__::type_true;    }
bool json::is_array   () const { return m_obj_p->data_type() == json_internals::__json__::type_array;   }
bool json::is_object  () const { return m_obj_p->data_type() == json_internals::__json__::type_object;  }
bool json::is_unknown () const { return m_obj_p->data_type() == json_internals::__json__::type_unknown; }

bool json::is_bool () const
{
    return is_false() || is_true();
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
    if (m_obj_p == other.m_obj_p)
        return true;
    else if (m_obj_p->data_type() == other.m_obj_p->data_type())
        return m_obj_p->equals(other.m_obj_p);
    else
        return false;
}

json json::clone () const
{
    std::shared_ptr<json_internals::__json__>  clone_obj(m_obj_p->clone());

    return json(clone_obj);
}
