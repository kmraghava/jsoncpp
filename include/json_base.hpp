#ifndef __json_base_hpp
#define __json_base_hpp

#include <memory>
#include <string>

namespace json_internals
{
    class __json__
    {
        public:
            __json__ () = default;
            __json__ (const __json__ &other) = default;

            __json__& operator= (const __json__ &other) = delete;

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const = 0;

            virtual std::string to_string () const = 0;
    };
}

class json
{
    public:
        static json parse (std::istream &stream);

    private:
        static json parse_object (std::istream &stream);
        static json parse_array  (std::istream &stream);
        static json parse_string (std::istream &stream);
        static json parse_false  (std::istream &stream);
        static json parse_true   (std::istream &stream);
        static json parse_number (std::istream &stream);

        static std::string parse_cstring (std::istream& stream);
        
    public:
        typedef enum
        {
            JSON_STRING,
            JSON_REAL,
            JSON_INTEGER,
            JSON_FALSE,
            JSON_TRUE,
            JSON_ARRAY,
            JSON_OBJECT,

            JSON_UNKNOWN
        } type;

    public:
        json ();
        json (const json &other);

        json& operator= (const json &other);

        virtual type data_type () const;

        std::string to_string () const;

        bool is_string  () const;
        bool is_real    () const;
        bool is_integer () const;
        bool is_false   () const;
        bool is_true    () const;
        bool is_bool    () const;
        bool is_array   () const;
        bool is_object  () const;

        bool operator== (const json &other) const;
        bool operator!= (const json &other) const;

        bool equals (const json &other) const;

    protected:
        std::shared_ptr<json_internals::__json__>  m_obj_p;
};

#endif /* __json_base_hpp */