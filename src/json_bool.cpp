
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
        return   json_internals::json_as_false(other_p)
               ? true
               : false;
    }

    std::string __json_false__::to_string () const
    {
        return "false";
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
        return   json_internals::json_as_true(other_p)
               ? true
               : false;
    }

    std::string __json_true__::to_string () const
    {
        return "true";
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

json_false::~json_false ()
{
}

json::type json_false::data_type () const
{
    return JSON_FALSE;
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

json_true::~json_true ()
{
}

json::type json_true::data_type () const
{
    return JSON_TRUE;
}
