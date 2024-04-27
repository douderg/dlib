
include (GenerateExportHeader)

add_library (plugin MODULE plugin.cpp)
target_include_directories (plugin PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
generate_export_header (plugin)

add_executable (add_five add_five.cpp)
target_link_libraries (add_five PRIVATE dlib)
set_target_properties (add_five PROPERTIES CXX_STANDARD 17)

add_test (NAME add_five COMMAND add_five)
