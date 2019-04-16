
if (MSVC)
    # don't link any libraries by default
    set(CMAKE_CXX_STANDARD_LIBRARIES_INIT "" CACHE STRING "" FORCE)
    set(CMAKE_C_STANDARD_LIBRARIES_INIT "" CACHE STRING "" FORCE)

    # don't enable RTTI or set a warning level by default
    string(REGEX REPLACE "/GR " "" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
    string(REGEX REPLACE "/W[0-4] " "" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
    string(REGEX REPLACE "/W[0-4] " "" CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT}")
endif()
