
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

            __json_string__ (const std::string &s);

            virtual ~__json_string__ ();

            __json_string__& operator= (const __json_string__ &other) = delete;

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const override;

            size_t length () const;

            void set (const std::string &s);

            std::string value () const;

            virtual std::string to_string () const override;

            virtual type data_type () const override;

            virtual __json__* clone () const override;

        private:
            std::string  m_value;
    };

    inline std::shared_ptr<      __json_string__> json_as_string  (      std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<      __json_string__>(jobj_p); }
    inline std::shared_ptr<const __json_string__> json_as_string  (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_string__>(jobj_p); }
}

class json_string : public json
{
    public:
        json_string ();
        json_string (const json_string &other);

        json_string (const std::string &s);
        json_string (const char *s);
        json_string (const char *s, size_t len);

        virtual ~json_string ();

        size_t length () const;

        json_string& operator= (const std::string &s);
        json_string& operator= (const char *s);

        void set (const std::string &s);
        void set (const char *s);
        void set (const char *s, size_t len);

        std::string value () const;

        friend json_string json_as_string (json jobj);

    private:
        explicit json_string (const std::shared_ptr<json_internals::__json__> &obj_p);
};

#endif /* __json_string_hpp */
