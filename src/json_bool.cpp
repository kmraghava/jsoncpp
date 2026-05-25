
#include "json_bool.hpp"

namespace json_internals
{
    __json_false__::__json_false__ ()
        : __json__()
    {
    }

    __json_false__::__json_false__ (const __json_false__ &other)
        : __json__(other)
    {
    }

    __json_false__::~__json_false__ ()
    {
    }

    bool __json_false__::equals (const std::shared_ptr<__json__> &other_p) const
    {
        return other_p->data_type() == type_false;
    }

    std::string __json_false__::to_string () const
    {
        return "false";
    }

    __json__::type __json_false__::data_type () const
    {
        return type_false;
    }

    __json__* __json_false__::clone () const
    {
        return new __json_false__();
    }


    __json_true__::__json_true__ ()
        : __json__()
    {
    }

    __json_true__::__json_true__ (const __json_true__ &other)
        : __json__(other)
    {
    }
    __json_true__::~__json_true__ ()
    {
    }

    bool __json_true__::equals (const std::shared_ptr<__json__> &other_p) const
    {
        return other_p->data_type() == type_true;
    }

    std::string __json_true__::to_string () const
    {
        return "true";
    }
    
    __json__::type __json_true__::data_type () const
    {
        return type_true;
    }

    __json__* __json_true__::clone () const
    {
        return new __json_true__();
    }
}


json_false::json_false ()
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_false__>();
}

json_false::json_false (const json_false &other)
    : json(other)
{
}

json_false::json_false (const std::shared_ptr<json_internals::__json__> &obj_p)
    : json(obj_p)
{
}

json_false::~json_false ()
{
}

json_false json_as_false (json jobj)
{
    if (jobj.m_obj_p->data_type() != json_internals::__json__::type_false)
        throw std::bad_cast();

    return json_false(jobj.m_obj_p);
}


json_true::json_true ()
    : json()
{
    m_obj_p = std::make_shared<json_internals::__json_true__>();
}

json_true::json_true (const json_true &other)
    : json(other)
{
}

json_true::json_true (const std::shared_ptr<json_internals::__json__> &obj_p)
    : json(obj_p)
{
}

json_true::~json_true ()
{
}

json_true json_as_true (json jobj)
{
    if (jobj.m_obj_p->data_type() != json_internals::__json__::type_true)
        throw std::bad_cast();

    return json_true(jobj.m_obj_p);
}
