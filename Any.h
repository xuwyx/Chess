//
// Created by QZQ on 01/06/2017.
//
#ifndef STUPIDSQL_ANY_H
#define STUPIDSQL_ANY_H

#include <iostream>
#include <cassert>
#include <vector>

class Any
{
    template <typename T>
    friend T any_cast(const Any& operand);
//    friend std::ostream& operator <<(std::ostream&, Any&);
//    friend std::istream& operator >>(std::istream&, Any&);
public:
    class PlaceHolder
    {
    public:
        virtual ~PlaceHolder(){}
        virtual const std::type_info& type() const = 0;
        virtual PlaceHolder * clone() const = 0;
        virtual bool operator <(PlaceHolder&) = 0;
//        virtual void print(std::ostream&) = 0;
    };

    template <typename T>
    class Holder : public PlaceHolder
    {
    public:
        T data;
        Holder(const T& d): data(d){}
        virtual const std::type_info& type() const override
        {
            return typeid(T);
        }

        virtual PlaceHolder * clone() const override
        {
            return new Holder(data);
        }

        virtual bool operator <(PlaceHolder& h) override
        {
            return this->data < dynamic_cast<Holder<T>&>(h).data;
        }

//        virtual void print(std::ostream& os) override
//        {
////            os << data;
//        }

		virtual ~Holder(){}
    };

//    default constructor
    Any(): content(nullptr){}
//    template constructor
    template <typename T>
    Any(const T& d): content(new Holder<T>(d)){}
//    copy constructor
    Any(const Any& ot): content(ot.content ? ot.content->clone() : nullptr){}
//    copy assignment operator
    Any& operator =(Any ot)
    {
        this->swap(ot);
        return *this;
    }
    bool operator <(Any &ot) {return *(this->content) < *(ot.content);}
    bool operator >(Any &ot) {return ot < *this;}
    bool operator !=(Any &ot) {return *this < ot || ot < *this;}
    bool operator ==(Any &ot) {return !(*this != ot);}
    bool operator >=(Any &ot) {return *this > ot || *this == ot;}
    bool operator <=(Any &ot) {return *this < ot || *this == ot;}

    void swap(Any &ot)
    {
        std::swap(this->content, ot.content);
    }

    ~Any()
    {
        if (content) delete content;
    }

    const std::type_info& type() const
    {
        return content ? content->type() : typeid(void);
    }

//    void print(std::ostream& os)
//    {
//        content->print(os);
//    }

private:
    PlaceHolder * content;
};

template <typename T>
T any_cast(const Any& operand)
{
    if (operand.type() != typeid(T)) std::cout << operand.type().name() << '\n' << typeid(T).name() << std::endl;
//    assert(operand.type() == typeid(T));
    return dynamic_cast<Any::Holder<T>*>(operand.content)->data;
}

#endif //STUPIDSQL_ANY_H
