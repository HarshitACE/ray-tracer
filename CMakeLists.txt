cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

set(CMAKE_OSX_SYSROOT macosx) # Ignored on other platfroms

project(
    ray-tracing-one-weekend
    VERSION 0.1.0
    DESCRIPTION "Implementation of the popular guide of the same name by Peter S Shirley"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

set(EXPORT_COMPILE_COMMANDS ON)

# ---- Declare library ----

add_library(
    ray-tracing-one-weekend_lib OBJECT
    source/libs/vec3.hpp
    source/libs/color.hpp
    source/libs/ray.hpp
    source/libs/camera.hpp
)

add_library(
    ray-tracing-one-weekend_objects-lib OBJECT
    source/objects/hittable.hpp
    source/objects/hittable_list.hpp
    source/objects/sphere.hpp
    source/objects/sphere.cpp
    source/objects/material.hpp
    source/objects/lambertian.hpp
    source/objects/lambertian.cpp
    source/objects/metal.hpp
    source/objects/dielectric.hpp
    )

target_include_directories(
    ray-tracing-one-weekend_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_include_directories(
    ray-tracing-one-weekend_objects-lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(ray-tracing-one-weekend_lib PUBLIC cxx_std_20)
target_compile_features(ray-tracing-one-weekend_objects-lib PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(ray-tracing-one-weekend_lib PRIVATE fmt::fmt)

# ---- Declare executable ----

add_executable(ray-tracing-one-weekend_exe 
    source/main.cpp
    source/rtweekend.hpp)

add_executable(ray-tracing-one-weekend::exe ALIAS ray-tracing-one-weekend_exe)

set_property(TARGET ray-tracing-one-weekend_exe PROPERTY OUTPUT_NAME ray-tracing-one-weekend)

target_compile_features(ray-tracing-one-weekend_exe PRIVATE cxx_std_20)

target_link_libraries(ray-tracing-one-weekend_exe PRIVATE
    ray-tracing-one-weekend_lib
    ray-tracing-one-weekend_objects-lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT ray-tracing-one-weekend_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of ray-tracing-one-weekend"
  )
endif()

include(cmake/dev-mode.cmake)
