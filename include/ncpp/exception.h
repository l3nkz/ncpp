#ifndef __NCPP_EXCEPTION_H__
#define __NCPP_EXCEPTION_H__

#pragma once

#include <exception>
#include <stdexcept>

namespace ncpp {

class NoSpaceLeft : public std::exception {
   private:
    const char *_str;

   public:
    NoSpaceLeft() = default;
    NoSpaceLeft(const std::string &str) noexcept;

    const char *what() const noexcept;
};

} /* namespace ncpp */

#endif /* __NCPP_EXCEPTION_H__ */
