#include <dlib.hpp>
#include <stdexcept>

namespace dl {

library::library(const std::filesystem::path &lib):
    handle_(nullptr)
{
#if _WIN32
    handle_ = LoadLibraryW(lib.wstring().c_str());
#else
    auto path=lib.string();
    handle_ = dlopen(path.c_str(), RTLD_NOW);
#endif
    if (!handle_) {
        throw std::runtime_error("failed to load " + lib.string());
    }
}

library::~library()
{
    if (handle_) {
#if _WIN32
        FreeLibrary(handle_);
#else
        dlclose(handle_);
#endif
    }
}

library::library(library &&other):
    handle_(other.handle_)
{
    other.handle_ = nullptr;
}

library &library::operator=(library &&other)
{
    if (handle_) {
#if _WIN32
        FreeLibrary(handle_);
#else
        dlclose(handle_);
#endif
    }
    handle_ = other.handle_;
    other.handle_ = nullptr;
    return *this;
}

}
