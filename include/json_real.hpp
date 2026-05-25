
#ifndef __json_real_hpp
#define __json_real_hpp

#include "json_base.hpp"

namespace json_internals
{
    class __json_real__ : public __json__
    {
        public:
            __json_real__ ();
            __json_real__ (const __json_real__ &other);

            __json_real__ (const double value);

            virtual ~__json_real__ ();

            __json_real__& operator= (const __json_real__ &other) = delete;

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const override;

            void set (const double value);

            double value () const;

            virtual std::string to_string () const override;

            virtual type data_type () const override;

            virtual __json__* clone () const override;

        private:
            double  m_value;
    };

    inline std::shared_ptr<      __json_real__> json_as_real (      std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<      __json_real__>(jobj_p); }
    inline std::shared_ptr<const __json_real__> json_as_real (const std::shared_ptr<__json__> &jobj_p) { return std::dynamic_pointer_cast<const __json_real__>(jobj_p); }
}

class json_real : public json
{
    public:
        json_real ();
        json_real (const json_real &other);

        json_real (const double value);

        virtual ~json_real ();

        json_real& operator= (const double value);

        double value () const;

        friend json_real json_as_real (json jobj);

    private:
        explicit json_real (const std::shared_ptr<json_internals::__json__> &obj_p);
};

#endif /* __json_real_hpp */
