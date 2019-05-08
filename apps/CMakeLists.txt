
# Chapter 1

add_executable(chapter1)

target_sources(chapter1
    PRIVATE "chapter1.cpp")

target_link_libraries(chapter1 PRIVATE rtc::rtc)

if(WIN32)
    target_compile_options(chapter1 PRIVATE
        "-W4"            # set a high warning level
        "-WX"            # treat warnings as errors
        "-wd4201"        # disable warning for nameless struct/union
        "-permissive-")  # enable iso c++ conformance mode
endif()

# Chapter 2

add_executable(chapter2)

target_sources(chapter2
    PRIVATE "chapter2.cpp")

target_link_libraries(chapter2 PRIVATE rtc::rtc)

if(WIN32)
    target_compile_options(chapter2 PRIVATE
        "-W4"            # set a high warning level
        "-WX"            # treat warnings as errors
        "-wd4201"        # disable warning for nameless struct/union
        "-permissive-")  # enable iso c++ conformance mode
endif()

# Chapter 4

add_executable(chapter4)

target_sources(chapter4
    PRIVATE "chapter4.cpp")

target_link_libraries(chapter4 PRIVATE rtc::rtc)

if(WIN32)
    target_compile_options(chapter4 PRIVATE
        "-W4"            # set a high warning level
        "-WX"            # treat warnings as errors
        "-wd4201"        # disable warning for nameless struct/union
        "-permissive-")  # enable iso c++ conformance mode
endif()

# Chapter 5

add_executable(chapter5)

target_sources(chapter5
    PRIVATE "chapter5.cpp")

target_link_libraries(chapter5 PRIVATE rtc::rtc)

if(WIN32)
    target_compile_options(chapter5 PRIVATE
        "-W4"            # set a high warning level
        "-WX"            # treat warnings as errors
        "-wd4201"        # disable warning for nameless struct/union
        "-permissive-")  # enable iso c++ conformance mode
endif()

# Chapter 6

add_executable(chapter6)

target_sources(chapter6
    PRIVATE "chapter6.cpp")

target_link_libraries(chapter6 PRIVATE rtc::rtc)

if(WIN32)
    target_compile_options(chapter6 PRIVATE
        "-W4"            # set a high warning level
        "-WX"            # treat warnings as errors
        "-wd4201"        # disable warning for nameless struct/union
        "-permissive-")  # enable iso c++ conformance mode
endif()
