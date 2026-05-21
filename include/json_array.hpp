
#ifndef __json_array_hpp
#define __json_array_hpp

#include "json_base.hpp"
#include <vector>

namespace json_internals
{
    class __json_array__ : public __json__
    {
        public:
            __json_array__ ();
            __json_array__ (const __json_array__ &other);

            __json_array__ (const std::vector<json> &values);

            __json_array__& operator= (const __json_array__ &other) = delete;

            void set (const std::vector<json> &values);

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const;

            size_t size () const;

            json& get (size_t index);
            const json& get (size_t index) const;

            void set (size_t index, const json &value);

            void append (const json &value);
            void insert (size_t index, const json &value);
            void remove (size_t index);
            void clear ();
            void extend (const std::shared_ptr<const __json_array__> &other_p);

            virtual std::string to_string () const;

        private:
            std::vector<json>  m_values;
    };
}

class json_array : public json
{
    public:
        json_array ();
        json_array (const json_array &other);

        json_array (const std::vector<json> &values);

        virtual ~json_array ();

        json_array& operator= (const std::vector<json> &values);

        size_t size () const;

        json& operator[] (size_t index);
        const json& operator[] (size_t index) const;

        json& get (size_t index);
        const json& get (size_t index) const;

        void set (size_t index, const json &value);

        void append (const json &value);
        void insert (size_t index, const json &value);
        void remove (size_t index);
        void clear ();
        void extend (const json_array &other);

        virtual type data_type () const;
};

#endif /* __json_array_hpp */
