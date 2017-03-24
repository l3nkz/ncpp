#ifndef __NCPP_COLORS_H__
#define __NCPP_COLORS_H__

#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <utility>


namespace ncpp {
namespace detail {

template <typename T>
class DataMap {
   private:
    std::map<std::string, std::shared_ptr<T>> _data;
    std::vector<bool> _ids;

   protected:
    int next_id()
    {
        for (size_t i = 0; i < _ids.size(); ++i) {
            if (_ids[i]) {
                _ids[i] = false;
                return i;
            }
        }

        return -1;
    }

    void add(const std::string &name, const std::shared_ptr<T>& data)
    {
        _data.insert(std::make_pair(name, data));
    }

    void del(const std::string &name, int num)
    {
        _data.erase(name);
        _ids[num] = true;
    }

    DataMap(int max_elements) : _data{}, _ids(max_elements, false)
    {}

   public:
    std::shared_ptr<T>& operator[](const std::string &str)
    {
        return _data[str];
    }

    const std::shared_ptr<T>& operator[](const std::string &str) const
    {
        return _data[str];
    }
};

} /* namespace detail */

class Color;
class ColorPair;

class ColorMap : public detail::DataMap<Color> {
   public:
    ColorMap();
    ColorMap(const ColorMap&) = delete;

    ColorMap& operator=(const ColorMap&) = delete;

    void add(const std::string &name, short r, short g, short b);
    void del(const std::string &name);
};

class Color {
   private:
    short _id;

    short _r;
    short _g;
    short _b;

   private:
    friend class Cursor;
    friend class ColorPair;
    friend class ColorMap;

    Color(short id, short r, short g, short b);

    short curs_data() const;

   public:
    Color(const Color&) = delete;

    ~Color();

    Color& operator=(const Color&) = delete;

    short r() const;
    void r(short new_r);
    short g() const;
    void g(short new_g);
    short b() const;
    void b(short new_b);
    std::tuple<short,short,short> rgb() const;
    void rgb(short new_r, short new_g, short new_b);
};

using ColorPtr = std::shared_ptr<Color>;


class ColorPairMap : public detail::DataMap<ColorPair> {
   public:
    ColorPairMap();
    ColorPairMap(const ColorPairMap&) = delete;

    ColorPairMap& operator=(const ColorPairMap&) = delete;

    void add(const std::string &name, const ColorPtr &fg, const ColorPtr &bg);
    void del(const std::string &name);
};

class ColorPair {
   private:
    short _id;

    ColorPtr _fg;
    ColorPtr _bg;

   private:
    friend class Cursor;
    friend class ColorPairMap;

    ColorPair(short id, const ColorPtr &fg, const ColorPtr &bg);

    short curs_data() const;

   public:
    ColorPair(const ColorPair&) = delete;

    ~ColorPair();

    ColorPair& operator=(const ColorPair&) = delete;

    ColorPtr fg() const;
    void fg(const ColorPtr &new_fg);
    ColorPtr bg() const;
    void bg(const ColorPtr &new_bg);
    std::pair<ColorPtr,ColorPtr> colors() const;
    void colors(const ColorPtr &new_fg, const ColorPtr &new_bg);
};

using ColorPairPtr = std::shared_ptr<ColorPair>;

} /* namespace ncpp */

#endif /* __NCPP_COLORS_H__ */
