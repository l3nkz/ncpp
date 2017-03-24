#ifndef __NCPP_ATTRIBUTES_H__
#define __NCPP_ATTRIBUTES_H__

#pragma once

#include <curses.h>


namespace ncpp {

enum class Attribute : attr_t {
    DEFAULT = A_NORMAL,
    NORMAL = A_NORMAL,
    STANDOUT = A_STANDOUT,
    UNDERLINE = A_UNDERLINE,
    REVERSE = A_REVERSE,
    BLINK = A_BLINK,
    BOLD = A_BOLD,
    ITALIC = A_ITALIC,
    DIM = A_DIM,
    PROTECT = A_PROTECT,
    INVISIBLE = A_INVIS,
    ALTCHARSET = A_ALTCHARSET,
    CHARTEXT = A_CHARTEXT
};

class AttributeSet {
   private:
    attr_t _attrs;

   private:
    friend class Cursor;

    attr_t curs_data() const;

   public:
    AttributeSet() = default;
    AttributeSet(const Attribute &attr);

    AttributeSet& operator=(const Attribute &attr);
    AttributeSet& operator=(const AttributeSet& attrs) = default;

    AttributeSet& set(const Attribute &attr);
    AttributeSet& set(const AttributeSet &attrs);
    AttributeSet& unset(const Attribute &attr);
    AttributeSet& unset(const AttributeSet &attrs);

    AttributeSet operator~() const;
    AttributeSet operator+(const Attribute &attr) const;
    AttributeSet operator+(const AttributeSet &attrs) const;
    AttributeSet operator-(const Attribute &attr) const;
    AttributeSet operator-(const AttributeSet &attrs) const;
    AttributeSet& operator+=(const Attribute &attr);
    AttributeSet& operator+=(const AttributeSet &attrs);
    AttributeSet& operator-=(const Attribute &attr);
    AttributeSet& operator-=(const AttributeSet &attrs);
};

} /* namespace ncpp */

#endif /* __NCPP_ATTRIBUTES_H__ */
