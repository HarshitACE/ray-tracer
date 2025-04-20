# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(ray-tracing-one-weekendTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(ray-tracing-one-weekend_test source/ray-tracing-one-weekend_test.cpp)
target_link_libraries(
    ray-tracing-one-weekend_test PRIVATE
    ray-tracing-one-weekend_lib
    Catch2::Catch2WithMain
)
target_compile_features(ray-tracing-one-weekend_test PRIVATE cxx_std_20)

catch_discover_tests(ray-tracing-one-weekend_test)

# ---- End-of-file commands ----

add_folders(Test)
