
#ifndef __json_bool_hpp
#define __json_bool_hpp

#include "json_base.hpp"

namespace json_internals
{
    class __json_false__ : public __json__
    {
        public:
            __json_false__ ();
            __json_false__ (const __json_false__ &other);

            virtual ~__json_false__ ();

            __json_false__& operator= (const __json_false__ &other) = delete;

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const override;

            virtual std::string to_string () const override;
    };

    inline std::shared_ptr<      __json_false__> json_as_false (      std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<      __json_false__>(jobj_p); }
    inline std::shared_ptr<const __json_false__> json_as_false (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_false__>(jobj_p); }

    class __json_true__ : public __json__
    {
        public:
            __json_true__ ();
            __json_true__ (const __json_true__ &other);

            virtual ~__json_true__ ();

            __json_true__& operator= (const __json_true__ &other) = delete;

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const override;

            virtual std::string to_string () const override;
    };

    inline std::shared_ptr<      __json_true__> json_as_true (      std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<      __json_true__>(jobj_p); }
    inline std::shared_ptr<const __json_true__> json_as_true (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_true__>(jobj_p); }
}

class json_false : public json
{
    public:
        json_false ();
        json_false (const json_false &other);

        virtual ~json_false ();

        virtual type data_type () const override;
};

inline       json_false& json_as_false (      json &jobj) { return dynamic_cast<      json_false &>(jobj); }
inline const json_false& json_as_false (const json &jobj) { return dynamic_cast<const json_false &>(jobj); }

class json_true : public json
{
    public:
        json_true ();
        json_true (const json_true &other);

        virtual ~json_true ();

        virtual type data_type () const override;
};

inline       json_true& json_as_true (      json &jobj) { return dynamic_cast<      json_true &>(jobj); }
inline const json_true& json_as_true (const json &jobj) { return dynamic_cast<const json_true &>(jobj); }

#endif /* __json_bool_hpp */
