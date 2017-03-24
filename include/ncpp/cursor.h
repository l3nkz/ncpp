#ifndef __NCPP_CURSOR_H__
#define __NCPP_CURSOR_H__

#pragma once

#include <ncpp/attributes.h>
#include <ncpp/colors.h>
#include <ncpp/helpers.h>

#include <memory>
#include <string>
#include <utility>


namespace ncpp {

class Window;

class Cursor {
   private:
    Window *_window;

    int _x;
    int _y;

    ColorPairPtr _colors;
    AttributeSet _attrs;

   private:
    friend class Window;

    Cursor(Window *window);

    void update_window();

   public:
    /* Get/Move the cursor */
    int x() const;
    void x(int new_x);
    int y() const;
    void y(int new_y);
    std::pair<int, int> xy() const;
    void xy(int new_x, int new_y);

    /* Set/Clear text attributes */
    AttributeSet attributes() const;
    void on(const Attribute &attr);
    void off(const Attribute &attr);
    void on(const AttributeSet &attrs);
    void off(const AttributeSet &attrs);
    void reset_attributes();

    /* Set/Clear text colors */
    ColorPtr fg() const;
    void fg(const ColorPtr &fg);
    void reset_fg();
    ColorPtr bg() const;
    void bg(const ColorPtr &bg);
    void reset_bg();
    ColorPairPtr colors() const;
    void colors(const ColorPairPtr &colors);
    void reset_colors();

    /* Display text */
    void print(const char c);
    void print(const std::string &str);

    template <typename... Args>
    void print(const std::string &fmt, Args... args)
    {
        print(helper::sprintf(fmt, std::forward(args)...));
    }

    /* Wrapper functions to ease various tasks */
    void print(int x, int y, const char c);
    void print(const AttributeSet &attrs, const char c);
    void print(int x, int y, const AttributeSet &attrs, const char c);
    void print(const ColorPairPtr &col, const char c);
    void print(int x, int y, const ColorPairPtr &col, const char c);
    void print(const ColorPairPtr &col, const AttributeSet &attrs, const char c);
    void print(int x, int y, const ColorPairPtr &col, const AttributeSet &attrs, const char c);

    template <typename... Args>
    void print(int x, int y, const std::string &fmt, Args... args)
    {
        move(x, y);
        print(fmt, args...);
    }

    template <typename... Args>
    void print(const AttributeSet &attrs, const std::string &fmt, Args... args)
    {
        on(attrs);
        print(fmt, args...);
        off(attrs);
    }

    template <typename... Args>
    void print(int x, int y, const AttributeSet &attrs, const std::string &fmt, Args... args)
    {
        move(x, y);
        print(attrs, fmt, args...);
    }

    template <typename... Args>
    void print(const ColorPairPtr &col, const std::string &fmt, Args... args)
    {
        colors(col);
        print(fmt, args...);
        reset_colors();
    }

    template <typename... Args>
    void print(int x, int y, const ColorPairPtr &col, const std::string &fmt, Args... args)
    {
        move(x, y);
        print(col, fmt, args...);
    }

    template <typename... Args>
    void print(const ColorPairPtr &col, const AttributeSet &attrs, const std::string &fmt, Args... args)
    {
        colors(col);
        print(attrs, fmt, args...);
        reset_colors();
    }

    template <typename... Args>
    void print(int x, int y, const ColorPairPtr &col, const AttributeSet &attrs,
               const std::string &fmt, Args... args)
    {
        move(x, y);
        print(col, attrs, fmt, args...);
    }

    /* Erase text */
    void erase();
    void erase(int count);
    void erase(int begin, int end);
    void erase(int begin_x, int begin_y, int end_x, int end_y);

    /* Clear text */
    void clear();
    void clear(int count);
};

using CursorPtr = std::shared_ptr<Cursor>;

} /* namespace ncpp */

#endif /* __NCPP_CURSOR_H__ */
