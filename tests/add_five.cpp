#include <dlib.hpp>

int main(int argc, char** argv) {
#if _WIN32
    dl::library lib("plugin.dll");
#elif __APPLE__
    dl::library lib("plugin.dylib");
#else
    dl::library lib("plugin.so");
#endif
    
    auto add_five = lib.load<int(int)>("add_five");
    if (!add_five) {
        return EXIT_FAILURE;
    }
    if (add_five(4) != 9) {
        return EXIT_FAILURE;
    }

    {
        dl::library lib2("plugin");
        auto add_five2 = lib2.load<int(int)>("add_five");
        if (!add_five2) {
            return EXIT_FAILURE;
        }
        if (add_five2(6) != 11) {
            return EXIT_FAILURE;
        }
        add_five = add_five2;
    }

    if (add_five(4) != 9) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
