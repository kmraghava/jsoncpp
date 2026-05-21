
#ifndef __json_object_hpp
#define __json_object_hpp

#include "json_base.hpp"
#include <map>

namespace json_internals
{
    class __json_object__ : public __json__
    {
        public:
            __json_object__ ();
            __json_object__ (const __json_object__ &other);
            __json_object__ (const std::map<std::string, json> &values);

            virtual ~__json_object__ () = default;

            __json_object__& operator= (const __json_object__ &other) = delete;

            void set (const std::map<std::string, json> &values);

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const override;

            size_t size () const;

            json& operator[] (const std::string &key);

            json get (const std::string &key) const;
            void set (const std::string &key, const json &value);

            bool exists (const std::string &key) const;

            void del (const std::string &key);

            void clear ();

            void update (const std::shared_ptr<const __json_object__> &other_p);
            void update_existing (const std::shared_ptr<const __json_object__> &other_p);
            void update_missing (const std::shared_ptr<const __json_object__> &other_p);
            void update_recursive (const std::shared_ptr<const __json_object__> &other_p);

            virtual std::string to_string () const override;

        private:
            std::map<std::string, json>  m_values;
    };

    inline std::shared_ptr<      __json_object__> json_as_object (      std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<      __json_object__>(jobj_p); }
    inline std::shared_ptr<const __json_object__> json_as_object (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_object__>(jobj_p); }
}

class json_object : public json
{
    public:
        json_object ();
        json_object (const json_object &other);
        json_object (const std::map<std::string, json> &values);

        virtual ~json_object ();

        json_object& operator= (const std::map<std::string, json> &values);

        size_t size () const;

        json& operator[] (const std::string &key);
        json& operator[] (const char *key_p);

        json get (const std::string &key) const;
        json get (const char *key_p) const;

        void set (const std::string &key, const json &value);
        void set (const char *key_p, const json &value);

        bool exists (const std::string &key) const;
        bool exists (const char *key_p) const;

        void del (const std::string &key);
        void del (const char *key_p);

        void clear ();

        void update (const json_object &other);
        void update_existing (const json_object &other);
        void update_missing (const json_object &other);
        void update_recursive (const json_object &other);

        virtual type data_type () const override;
};

inline       json_object& json_as_object (      json &jobj) { return dynamic_cast<      json_object &>(jobj); }
inline const json_object& json_as_object (const json &jobj) { return dynamic_cast<const json_object &>(jobj); }

#endif /* __json_object_hpp */
