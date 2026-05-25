#ifndef __json_base_hpp
#define __json_base_hpp

#include <memory>
#include <string>

class json;

namespace json_internals
{
    class __json__
    {
        public:
            enum type
            {
                type_string,
                type_integer,
                type_real,
                type_false,
                type_true,
                type_array,
                type_object,

                type_unknown
            };

        public:
            __json__ () = default;
            __json__ (const __json__ &other) = default;

            __json__& operator= (const __json__ &other) = delete;

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const = 0;

            virtual std::string to_string () const = 0;

            virtual type data_type () const = 0;

            virtual __json__* clone () const = 0;
    };
}

class json_string;
class json_integer;
class json_real;
class json_false;
class json_true;
class json_array;
class json_object;

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
        json ();
        json (const json &other);

        json& operator= (const json &other);

        std::string to_string () const;

        bool is_string  () const;
        bool is_integer () const;
        bool is_real    () const;
        bool is_false   () const;
        bool is_true    () const;
        bool is_array   () const;
        bool is_object  () const;
        bool is_unknown () const;

        bool is_bool    () const;

        bool operator== (const json &other) const;
        bool operator!= (const json &other) const;

        bool equals (const json &other) const;

        json clone () const;

    protected:
        explicit json (const std::shared_ptr<json_internals::__json__> &obj_p);

        std::shared_ptr<json_internals::__json__>  m_obj_p;

    private:
        friend json_string  json_as_string  (json jobj);
        friend json_integer json_as_integer (json jobj);
        friend json_real    json_as_real    (json jobj);
        friend json_false   json_as_false   (json jobj);
        friend json_true    json_as_true    (json jobj);
        friend json_array   json_as_array   (json jobj);
        friend json_object  json_as_object  (json jobj);
};

#endif /* __json_base_hpp */