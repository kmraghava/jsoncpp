
#ifndef __json_hpp
#define __json_hpp

#include "json_base.hpp"
#include "json_bool.hpp"
#include "json_integer.hpp"
#include "json_real.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"

namespace json_internals
{
    std::shared_ptr<__json_string__ > json_as_string  (std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<__json_string__ >(jobj_p); }
    std::shared_ptr<__json_real__   > json_as_real    (std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<__json_real__   >(jobj_p); }
    std::shared_ptr<__json_integer__> json_as_integer (std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<__json_integer__>(jobj_p); }
    std::shared_ptr<__json_false__  > json_as_false   (std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<__json_false__  >(jobj_p); }
    std::shared_ptr<__json_true__   > json_as_true    (std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<__json_true__   >(jobj_p); }
    std::shared_ptr<__json_array__  > json_as_array   (std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<__json_array__  >(jobj_p); }
    std::shared_ptr<__json_object__ > json_as_object  (std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<__json_object__ >(jobj_p); }

    std::shared_ptr<const __json_string__ > json_as_string  (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_string__ >(jobj_p); }
    std::shared_ptr<const __json_real__   > json_as_real    (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_real__   >(jobj_p); }
    std::shared_ptr<const __json_integer__> json_as_integer (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_integer__>(jobj_p); }
    std::shared_ptr<const __json_false__  > json_as_false   (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_false__  >(jobj_p); }
    std::shared_ptr<const __json_true__   > json_as_true    (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_true__   >(jobj_p); }
    std::shared_ptr<const __json_array__  > json_as_array   (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_array__  >(jobj_p); }
    std::shared_ptr<const __json_object__ > json_as_object  (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_object__ >(jobj_p); }
}

json_string&  json_as_string  (json &jobj) { return dynamic_cast<json_string  &>(jobj); }
json_real&    json_as_real    (json &jobj) { return dynamic_cast<json_real    &>(jobj); }
json_integer& json_as_integer (json &jobj) { return dynamic_cast<json_integer &>(jobj); }
json_false&   json_as_false   (json &jobj) { return dynamic_cast<json_false   &>(jobj); }
json_true&    json_as_true    (json &jobj) { return dynamic_cast<json_true    &>(jobj); }
json_array&   json_as_array   (json &jobj) { return dynamic_cast<json_array   &>(jobj); }
json_object&  json_as_object  (json &jobj) { return dynamic_cast<json_object  &>(jobj); }

const json_string&  json_as_string  (const json &jobj) { return dynamic_cast<const json_string  &>(jobj); }
const json_real&    json_as_real    (const json &jobj) { return dynamic_cast<const json_real    &>(jobj); }
const json_integer& json_as_integer (const json &jobj) { return dynamic_cast<const json_integer &>(jobj); }
const json_false&   json_as_false   (const json &jobj) { return dynamic_cast<const json_false   &>(jobj); }
const json_true&    json_as_true    (const json &jobj) { return dynamic_cast<const json_true    &>(jobj); }
const json_array&   json_as_array   (const json &jobj) { return dynamic_cast<const json_array   &>(jobj); }
const json_object&  json_as_object  (const json &jobj) { return dynamic_cast<const json_object  &>(jobj); }

#endif /* __json_hpp */
