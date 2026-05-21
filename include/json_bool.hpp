
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

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const;

            virtual std::string to_string () const;
    };

    class __json_true__ : public __json__
    {
        public:
            __json_true__ ();
            __json_true__ (const __json_true__ &other);

            virtual ~__json_true__ ();

            __json_true__& operator= (const __json_true__ &other) = delete;

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const;

            virtual std::string to_string () const;
    };
}

class json_false : public json
{
    public:
        json_false ();
        json_false (const json_false &other);

        virtual ~json_false ();

        virtual type data_type () const;
};

class json_true : public json
{
    public:
        json_true ();
        json_true (const json_true &other);

        virtual ~json_true ();

        virtual type data_type () const;
};

#endif /* __json_bool_hpp */
