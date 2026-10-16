cmake_minimum_required(VERSION 3.24)
project(dota2_fps_unlocker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(unlocker_core STATIC
    src/core/optimizer_core.cpp
    src/core/config_loader.cpp
    src/handlers/overlay_handler.cpp
    src/handlers/hotkey_handler.cpp
    src/services/process_attach.cpp
    src/services/console_tweak.cpp
    src/services/telemetry_client.cpp
    src/utils/log_writer.cpp
    src/utils/memory_patch.cpp
)

target_include_directories(unlocker_core PUBLIC src)
target_link_libraries(unlocker_core PRIVATE user32 psapi)

add_executable(dota2-fps-unlocker src/bootstrap/main.cpp)
target_link_libraries(dota2-fps-unlocker PRIVATE unlocker_core)

enable_testing()
add_executable(test_memory_patch tests/test_memory_patch.cpp)
target_link_libraries(test_memory_patch PRIVATE unlocker_core)
add_test(NAME memory_patch COMMAND test_memory_patch)

add_executable(test_config_loader tests/test_config_loader.cpp)
target_link_libraries(test_config_loader PRIVATE unlocker_core)
add_test(NAME config_loader COMMAND test_config_loader)