
add_library(rtc)

target_sources(rtc
    PRIVATE "src/canvas.cpp")

target_include_directories(rtc
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(rtc PUBLIC cxx_std_20)

add_library(rtc::rtc ALIAS rtc)
