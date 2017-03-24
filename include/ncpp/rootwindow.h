#ifndef __NCPP_ROOTWINDOW_H__
#define __NCPP_ROOTWINDOW_H__

#pragma once

#include <ncpp/window.h>

#include <memory>


namespace ncpp {

class RootWindow : public Window {
   private:
    static std::shared_ptr<RootWindow> instance;

    RootWindow();

   public:
    static std::shared_ptr<RootWindow> get();
};

} /* namespace ncpp */

#endif /* __NCPP_ROOTWINDOW_H__ */
