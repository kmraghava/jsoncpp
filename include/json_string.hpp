
#ifndef __json_string_hpp
#define __json_string_hpp

#include "json_base.hpp"

namespace json_internals
{
    class __json_string__ : public __json__
    {
        public:
            __json_string__ ();
            __json_string__ (const __json_string__ &other);

            __json_string__ (const char *s);
            __json_string__ (const char *s, size_t len);
            __json_string__ (const std::string &s);

            virtual ~__json_string__ ();

            __json_string__& operator= (const __json_string__ &other) = delete;

            void set (const std::string &s);
            void set (const char *s);
            void set (const char *s, size_t len);

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const;

            size_t length () const;

            const std::string& value () const;
            std::string& value ();

            virtual std::string to_string () const;

        private:
            std::string  m_value;
    };
}

class json_string : public json
{
    public:
        json_string ();
        json_string (const json_string &other);

        json_string (const char *s);
        json_string (const char *s, size_t len);
        json_string (const std::string &s);

        virtual ~json_string ();

        json_string& operator= (const std::string &s);
        json_string& operator= (const char *s);

        void set (const char *s, size_t len);

        size_t length () const;

        const std::string& value () const;
        std::string& value ();

        virtual type data_type () const;
};

#endif /* __json_string_hpp */
