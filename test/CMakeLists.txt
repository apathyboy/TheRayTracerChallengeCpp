
add_executable(rtc-tests)

target_sources(rtc-tests
    PRIVATE "main.cpp"

            "features/camera.cpp"
            "features/canvas.cpp"
            "features/intersections.cpp"
            "features/lights.cpp"
            "features/materials.cpp"
            "features/math.cpp"
            "features/matrices.cpp"
            "features/rays.cpp"
            "features/spheres.cpp"
            "features/shapes.cpp"
            "features/transformations.cpp"
            "features/tuples.cpp"
            "features/world.cpp")

target_link_libraries(rtc-tests PRIVATE Catch2::Catch2 rtc::rtc)

if(WIN32)
    target_compile_options(rtc-tests PRIVATE
        "-W4"            # set a high warning level
        "-WX"            # treat warnings as errors
        "-wd4201"        # disable warning for nameless struct/union
        "-permissive-")  # enable iso c++ conformance mode
endif()

include(CTest)
include(Catch)

catch_discover_tests(rtc-tests)
