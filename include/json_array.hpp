
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

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const override;

            size_t size () const;

            json& operator[] (size_t index);

            json get (size_t index) const;
            void set (size_t index, const json &value);

            void append (const json &value);
            void insert (size_t index, const json &value);
            void remove (size_t index);
            void clear ();
            void extend (const std::shared_ptr<const __json_array__> &other_p);

            virtual std::string to_string () const override;

        private:
            std::vector<json>  m_values;
    };

    inline std::shared_ptr<      __json_array__> json_as_array (      std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<      __json_array__>(jobj_p); }
    inline std::shared_ptr<const __json_array__> json_as_array (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_array__>(jobj_p); }
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

        json get (size_t index) const;
        void set (size_t index, const json &value);

        void append (const json &value);
        void insert (size_t index, const json &value);
        void remove (size_t index);
        void clear ();
        void extend (const json_array &other);

        virtual type data_type () const override;
};

inline       json_array& json_as_array (      json &jobj) { return dynamic_cast<      json_array &>(jobj); }
inline const json_array& json_as_array (const json &jobj) { return dynamic_cast<const json_array &>(jobj); }

#endif /* __json_array_hpp */
