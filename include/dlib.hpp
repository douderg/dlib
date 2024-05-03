#pragma once

#if _WIN32
#include <Windows.h>    
#else
#include <dlfcn.h>
#endif

#include <filesystem>

namespace dl {

template <class T>
struct symbol;

template <class T, class...Args>
struct symbol<T(Args...)> {
    using type = T(*)(Args...);
};

class library {
public:
    library(const std::filesystem::path& lib);
    ~library();
    library(library&& other);
    library& operator=(library&& other);

    template <class T>
    typename symbol<T>::type load(const std::string& sym) {
        if (!handle_) {
            return nullptr;
        }
#if _WIN32
        return symbol<T>::type(GetProcAddress(handle_, sym.c_str()));
#else
        return typename symbol<T>::type(dlsym(handle_, sym.c_str()));
#endif
    }
private:

#if _WIN32
    HMODULE handle_;
#else
    void *handle_;
#endif
};

}
