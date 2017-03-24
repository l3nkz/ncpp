#include <ncpp/attributes.h>
#include <ncpp/colors.h>
#include <ncpp/cursor.h>
#include <ncpp/window.h>

#include <stdexcept>
#include <utility>

#include <curses.h>


namespace ncpp {

Cursor::Cursor(Window *window) : _window(window)
{
    refresh();
}

void Cursor::update_window()
{
    wattr_set(_window->curs_data(), _attrs.curs_data(),
              _colors->curs_data(), nullptr);
}

int Cursor::x() const
{
    return _x;
}

void Cursor::x(int new_x)
{
    wmove(_window->curs_data(), _y, new_x);
    getyx(_window->curs_data(), _y, _x);
}

int Cursor::y() const
{
    return _y;
}

void Cursor::y(int new_y)
{
    wmove(_window->curs_data(), new_y, _x);
    getyx(_window->curs_data(), _y, _x);
}

std::pair<int, int> Cursor::xy() const
{
    return std::make_pair(_x, _y);
}

void Cursor::xy(int new_x, int new_y)
{
    wmove(_window->curs_data(), new_y, new_x);
    getyx(_window->curs_data(), _y, _x);
}

AttributeSet Cursor::attributes() const
{
    return _attrs;
}

void Cursor::on(const Attribute &attr)
{
    _attrs += attr;

    update_window();
}

void Cursor::off(const Attribute &attr)
{
    _attrs -= attr;

    update_window();
}

void Cursor::on(const AttributeSet &attrs)
{
    _attrs += attrs;

    update_window();
}

void Cursor::off(const AttributeSet &attrs)
{
    _attrs -= attrs;

    update_window();
}

void Cursor::reset_attributes()
{
    _attrs = Attribute::NORMAL;

    update_window();
}

ColorPtr Cursor::fg() const
{
    return _colors->fg();
}

void Cursor::fg(const ColorPtr &fg)
{
    _colors->fg(fg);

    update_window();
}

void Cursor::reset_fg()
{
    _colors->fg(_window->fg());

    update_window();
}

ColorPtr Cursor::bg() const
{
    return _colors->bg();
}

void Cursor::bg(const ColorPtr &bg)
{
    _colors->bg(bg);

    update_window();
}

void Cursor::reset_bg()
{
    _colors->bg(_window->bg());

    update_window();
}

ColorPairPtr Cursor::colors() const
{
    return _colors;
}

void Cursor::colors(const ColorPairPtr &colors)
{
    _colors->colors(colors->fg(), colors->bg());

    update_window();
}

void Cursor::reset_colors()
{
    ColorPtr fg, bg;
    std::tie(fg, bg) = _window->colors()->colors();

    _colors->colors(fg, bg);

    update_window();
}

void Cursor::print(const char c)
{
    waddch(_window->curs_data(), c);
    getyx(_window->curs_data(), _y, _x);
    _window->refresh();
}

void Cursor::print(const std::string &str)
{
    waddstr(_window->curs_data(), str.c_str());
    getyx(_window->curs_data(), _y, _x);
    _window->refresh();
}

void Cursor::print(int x, int y, const char c)
{
    move(x, y);
    print(c);
}

void Cursor::print(const AttributeSet &attrs, const char c)
{
    on(attrs);
    print(c);
    off(attrs);
}

void Cursor::print(int x, int y, const AttributeSet &attrs, const char c)
{
    move(x, y);
    print(attrs, c);
}

void Cursor::print(const ColorPairPtr &col, const char c)
{
    colors(col);
    print(c);
    reset_colors();
}

void Cursor::print(int x, int y, const ColorPairPtr &col, const char c)
{
    move(x, y);
    print(col, c);
}

void Cursor::print(const ColorPairPtr &col, const AttributeSet &attrs, const char c)
{
    colors(col);
    print(attrs, c);
    reset_colors();
}

void Cursor::print(int x, int y, const ColorPairPtr &col, const AttributeSet &attrs, const char c)
{
    move(x, y);
    print(col, attrs, c);
}

void Cursor::erase()
{
    erase(1);
}

void Cursor::erase(int count)
{
    if (count > (_window->width() - _x))
        throw std::invalid_argument("'count' is out of window");

    if (count == -1) {
        wclrtoeol(_window->curs_data());
        _window->refresh();
        return;
    }

    while(count--)
        wdelch(_window->curs_data());

    _window->refresh();
}

void Cursor::erase(int begin, int end)
{
    if (begin < 0)
        throw std::invalid_argument("'begin' must be >0");

    x(begin);
    erase(end == -1 ? -1 : end-begin);
}

void Cursor::erase(int begin_x, int begin_y, int end_x, int end_y)
{
    if (begin_x < 0 || begin_y < 0)
        throw std::invalid_argument("'begin_x' and 'begin_y' must be >0");

    xy(begin_x, begin_y);

    if (end_y == -1 && end_x == -1) {
        wclrtobot(_window->curs_data());
        _window->refresh();
        return;
    }

    if (end_y < begin_y || end_y > _window->height())
        throw std::invalid_argument("'end_y' must be >= 'begin_y' but inside the window");
    if (end_x < begin_x || end_x > _window->width())
        throw std::invalid_argument("'end_x' must be >= 'begin_x' but inside the window");

    int lines;

    if (end_y == -1) {
        lines = _window->height() - begin_y;
    } else {
        lines = end_y - begin_y;
    }

    if (lines > 2) {
        y(begin_y + 1);

        winsdelln(_window->curs_data(), 1-lines);
        lines = 1;

        y(begin_y);
    }

    if (lines == 1)
        wclrtoeol(_window->curs_data());

    erase(end_x == -1 ? -1 : end_x-begin_x);
}

} /* namespace ncpp */
