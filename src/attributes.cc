#include <ncpp/attributes.h>

namespace ncpp {

attr_t AttributeSet::curs_data() const
{
    return _attrs;
}

AttributeSet::AttributeSet(const Attribute &attr) : _attrs{static_cast<attr_t>(attr)}
{}

AttributeSet& AttributeSet::operator=(const Attribute &attr)
{
    _attrs = static_cast<attr_t>(attr);

    return *this;
}

AttributeSet& AttributeSet::set(const Attribute &attr)
{
    _attrs |= static_cast<attr_t>(attr);

    return *this;
}

AttributeSet& AttributeSet::set(const AttributeSet &attrs)
{
    _attrs |= attrs._attrs;

    return *this;
}

AttributeSet& AttributeSet::unset(const Attribute &attr)
{
    _attrs &= ~(static_cast<attr_t>(attr));

    return *this;
}

AttributeSet& AttributeSet::unset(const AttributeSet &attrs)
{
    _attrs &= ~(attrs._attrs);

    return *this;
}

AttributeSet AttributeSet::operator~() const
{
    AttributeSet tmp{*this};

    tmp._attrs = ~tmp._attrs;
    return tmp;
}

AttributeSet AttributeSet::operator+(const Attribute &attr) const
{
    AttributeSet tmp{*this};

    tmp.set(attr);
    return tmp;
}

AttributeSet AttributeSet::operator+(const AttributeSet &attrs) const
{
    AttributeSet tmp{*this};

    tmp.set(attrs);
    return tmp;
}

AttributeSet AttributeSet::operator-(const Attribute &attr) const
{
    AttributeSet tmp{*this};

    tmp.unset(attr);
    return tmp;
}

AttributeSet AttributeSet::operator-(const AttributeSet &attrs) const
{
    AttributeSet tmp{*this};

    tmp.unset(attrs);
    return tmp;
}

AttributeSet& AttributeSet::operator+=(const Attribute &attr)
{
    set(attr);

    return *this;
}

AttributeSet& AttributeSet::operator+=(const AttributeSet &attrs)
{
    set(attrs);

    return *this;
}

AttributeSet& AttributeSet::operator-=(const Attribute &attr)
{
    unset(attr);

    return *this;
}

AttributeSet& AttributeSet::operator-=(const AttributeSet &attrs)
{
    unset(attrs);

    return *this;
}

} /* namespace ncpp */
