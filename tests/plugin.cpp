#include <plugin_export.h>

#if __cplusplus
extern "C" {
#endif

PLUGIN_EXPORT int add_five(int x) {
    return x + 5;
}

#if __cplusplus
}
#endif
