
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

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const;

            void set (const long value);

            const long& value () const;
            long& value ();

            virtual std::string to_string () const;

        private:
            long  m_value;
    };
}

class json_integer : public json
{
    public:
        json_integer ();
        json_integer (const json_integer &other);

        json_integer (const long value);

        virtual ~json_integer ();

        json_integer& operator= (const long value);

        const long& value () const;
        long& value ();

        virtual type data_type () const;
};

#endif /* __json_integer_hpp */
