#include <ncpp/window.h>

#include <curses.h>


namespace ncpp {

Window::Window(Window *parent, WINDOW *win) :
    _win{win}, _parent{parent}, _children{}, _cursor{new Cursor(this)}
{
    if (parent)
        getparyx(_win, _y, _x);
    else
        _x = _y = 0;

    getmaxyx(_win, _height, _width);
}

WINDOW* Window::curs_data()
{
    return _win;
}

void Window::refresh()
{
    wnoutrefresh(_win);

    if (_parent)
        _parent->refresh();
    else
        doupdate();
}

} /* namespace ncpp */
