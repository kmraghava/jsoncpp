
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

            virtual bool equals (const std::shared_ptr<__json__> &other_p) const;

            void set (const double value);

            const double& value () const;
            double& value ();

            virtual std::string to_string () const;

        private:
            double  m_value;
    };
}

class json_real : public json
{
    public:
        json_real ();
        json_real (const json_real &other);

        json_real (const double value);

        virtual ~json_real ();

        json_real& operator= (const double value);

        const double& value () const;
        double& value ();

        virtual type data_type () const;
};

#endif /* __json_real_hpp */
