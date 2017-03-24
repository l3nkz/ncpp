#include <ncpp/colors.h>
#include <ncpp/exception.h>

#include <string>
#include <tuple>
#include <utility>

#include <curses.h>


namespace ncpp {

ColorMap::ColorMap() : detail::DataMap<Color>(COLORS)
{}

void ColorMap::add(const std::string &name, short r, short g, short b)
{
    int id = this->next_id();
    if (id == -1)
        throw NoSpaceLeft();

    this->add(name, ColorPtr{new  Color(id, r, g, b)});
}

void ColorMap::del(const std::string &name)
{
    auto color = this->operator[](name);

    this->del(name, color->curs_data());
}


Color::Color(short id, short r, short g, short b) : _id{id}, _r{r}, _g{g}, _b{b}
{
    ::init_color(_id, _r, _g, _b);
}

short Color::curs_data() const
{
    return _id;
}

Color::~Color()
{
}

short Color::r() const
{
    return _r;
}

void Color::r(short new_r)
{
    _r = new_r;

    ::init_color(_id, _r, _g, _b);
}

short Color::g() const
{
    return _g;
}

void Color::g(short new_g)
{
    _g = new_g;

    ::init_color(_id, _r, _g, _b);
}

short Color::b() const
{
    return _b;
}

void Color::b(short new_b)
{
    _b = new_b;

    ::init_color(_id, _r, _g, _b);
}

std::tuple<short, short, short> Color::rgb() const
{
    return std::make_tuple(_r, _g, _b);
}

void Color::rgb(short new_r, short new_g, short new_b)
{
    _r = new_r;
    _g = new_g;
    _b = new_b;

    ::init_color(_id, _r, _g, _b);
}


ColorPairMap::ColorPairMap() : detail::DataMap<ColorPair>(COLOR_PAIRS)
{}

void ColorPairMap::add(const std::string &name, const ColorPtr &fg, const ColorPtr &bg)
{
    int id = this->next_id();
    if (id == -1)
        throw NoSpaceLeft();

    this->add(name, ColorPairPtr{new ColorPair(id, fg, bg)});
}

void ColorPairMap::del(const std::string &name)
{
    auto color_pair = this->operator[](name);

    this->del(name, color_pair->curs_data());
}


ColorPair::ColorPair(short id, const ColorPtr &fg, const ColorPtr &bg) : _id{id}, _fg{fg}, _bg{bg}
{
    ::init_pair(id, _fg->curs_data(), _bg->curs_data());
}

short ColorPair::curs_data() const
{
    return _id;
}

ColorPtr ColorPair::fg() const
{
    return _fg;
}

void ColorPair::fg(const ColorPtr &new_fg)
{
    _fg = new_fg;

    ::init_pair(_id, _fg->curs_data(), _bg->curs_data());
}

ColorPtr ColorPair::bg() const
{
    return _bg;
}

void ColorPair::bg(const ColorPtr &new_bg)
{
    _bg = new_bg;

    ::init_pair(_id, _fg->curs_data(), _bg->curs_data());
}

std::pair<ColorPtr, ColorPtr> ColorPair::colors() const
{
    return std::make_pair(_fg, _bg);
}

void ColorPair::colors(const ColorPtr &new_fg, const ColorPtr &new_bg)
{
    _fg = new_fg;
    _bg = new_bg;

    ::init_pair(_id, _fg->curs_data(), _bg->curs_data());
}

} /* namespace ncpp */
