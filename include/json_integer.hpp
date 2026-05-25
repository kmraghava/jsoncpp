
#ifndef __json_integer_hpp
#define __json_integer_hpp

#include "json_base.hpp"

namespace json_internals
{
    class __json_integer__ : public __json__
    {
        public:
            __json_integer__ ();
            __json_integer__ (const __json_integer__ &other);

            __json_integer__ (const long value);

            virtual ~__json_integer__ ();

            __json_integer__& operator= (const __json_integer__ &other) = delete;

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const override;

            void set (const long value);

            long value () const;

            virtual std::string to_string () const override;

            virtual type data_type () const override;

            virtual __json__* clone () const override;

        private:
            long  m_value;
    };

    inline std::shared_ptr<      __json_integer__> json_as_integer (      std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<      __json_integer__>(jobj_p); }
    inline std::shared_ptr<const __json_integer__> json_as_integer (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_integer__>(jobj_p); }
}

class json_integer : public json
{
    public:
        json_integer ();
        json_integer (const json_integer &other);

        json_integer (const long value);

        virtual ~json_integer ();

        json_integer& operator= (const long value);

        long value () const;

        friend json_integer json_as_integer (json jobj);

    private:
        explicit json_integer (const std::shared_ptr<json_internals::__json__> &obj_p);
};

#endif /* __json_integer_hpp */
