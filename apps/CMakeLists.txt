
# Chapter 1

add_executable(chapter1)

target_sources(chapter1
    PRIVATE "chapter1.cpp")

target_compile_features(chapter1 PRIVATE cxx_std_20)

target_link_libraries(chapter1 PRIVATE rtc::rtc)

if(WIN32)
    target_compile_options(chapter1 PRIVATE
        "-W4"            # set a high warning level
        "-WX"            # treat warnings as errors
        "-wd4201"        # disable warning for nameless struct/union
        "-permissive-")  # enable iso c++ conformance mode
endif()
