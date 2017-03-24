#ifndef __NCPP_HELPERS_H__
#define __NCPP_HELPERS_H__

#include <cstdio>
#include <memory>
#include <string>


namespace ncpp {
namespace helper {

template <typename... Args>
std::string sprintf(const std::string &fmt, Args... args)
{
    size_t sz = std::snprintf(nullptr, 0, fmt.c_str(), args...) + 1;

    auto buf = std::make_unique<char>(sz);
    std::snprintf(buf.get(), sz, fmt.c_str(), fmt);

    return std::string(buf.get(), sz);
}

} /* namespace helper */
} /* namespace ncpp */

#endif /* __NCPP_HELPERS_H__ */
