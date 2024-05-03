#include <dlib.hpp>

#include <iostream>

int test() {
#if _WIN32
    std::string plugin_name="plugin.dll";
#else
    std::string plugin_name="libplugin.so";
#endif

    dl::library lib(plugin_name);

    auto add_five = lib.load<int(int)>("add_five");
    if (!add_five) {
        throw std::runtime_error("failed to load function");
    }
    if (add_five(4) != 9) {
        throw std::runtime_error("wrong result");
    }

    {
        dl::library lib2(plugin_name);
        auto add_five2 = lib2.load<int(int)>("add_five");
        if (!add_five2) {
            throw std::runtime_error("failed to obtain second handle");
        }
        if (add_five2(6) != 11) {
            throw std::runtime_error("wrong result (2nd handle)");
        }
        add_five = add_five2;
    }

    if (add_five(4) != 9) {
        throw std::runtime_error("first handle invalidated");
    }
    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    try {
        return test();
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << "\n";
    }
    return EXIT_FAILURE;
}
