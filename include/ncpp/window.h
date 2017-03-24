#ifndef __NCPP_WINDOW_H__
#define __NCPP_WINDOW_H__

#pragma once

#include <ncpp/cursor.h>

#include <vector>

#include <curses.h>


namespace ncpp {

/* Forward declare 'Cursor' */
class Window {
   private:
    WINDOW *_win;

   private:
    friend class Cursor;

   protected:
    Window *_parent;
    std::vector<Window *> _children;
    CursorPtr _cursor;

    int _x;
    int _y;
    int _width;
    int _height;

    Window(Window *parent, WINDOW *win);

    WINDOW *curs_data();
    virtual void refresh();

   public:
    Window(const Window &win) = delete;
    Window(Window &&win);

    Window& operator=(const Window &win) = delete;
    Window& operator=(Window &&win);

    int width() const;
    int height() const;
    bool resize(int new_width, int new_height);

    int x() const;
    int y() const;
    bool move(int new_x, int new_y);

    CursorPtr cursor();

    ColorPtr fg() const;
    ColorPtr bg() const;
    ColorPairPtr colors() const;
};

} /* namespace ncpp */

#endif /* __NCPP_WINDOW_H__ */
