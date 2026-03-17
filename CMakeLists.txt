cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE STRING "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(Editor VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Общие include директории
set(COMMON_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/document/include
    ${CMAKE_CURRENT_SOURCE_DIR}/primitives/include
)

# Библиотека primitives
add_library(primitives STATIC
    primitives/src/shape.cpp
    primitives/src/circle.cpp
    primitives/src/line.cpp
    primitives/src/rectangle.cpp
)

target_include_directories(primitives 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/primitives/include
)

# Библиотека document
add_library(document STATIC
    document/src/document.cpp
    document/src/document_manager.cpp
)

target_include_directories(document 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/document/include
)

target_link_libraries(document
    PRIVATE
        primitives
)

# Библиотека core
add_library(core STATIC
    core/src/canvas.cpp
    core/src/editor.cpp
    core/src/model.cpp
)

target_include_directories(core 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/core/include
)

target_link_libraries(core
    PRIVATE
        primitives
        document
)

# Основное приложение
add_executable(editor src/main.cpp)

target_include_directories(editor
    PRIVATE 
        ${COMMON_INCLUDES}
)

target_link_libraries(editor
    PRIVATE
        core
        document
        primitives
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    
    add_executable(editor_tests tests/tests.cpp)
    
    target_include_directories(editor_tests
        PRIVATE 
            ${COMMON_INCLUDES}
    )
    
    target_compile_definitions(editor_tests 
        PRIVATE 
            BOOST_TEST_DYN_LINK
    )
    
    target_link_libraries(editor_tests
        PRIVATE
            ${Boost_LIBRARIES}
            core
            document
            primitives
    )
endif()

function(set_compiler_flags target_name)
    if (MSVC)
        target_compile_options(${target_name} PRIVATE /W4)
    else ()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endfunction()

set_compiler_flags(editor)
set_compiler_flags(primitives)
set_compiler_flags(document)
set_compiler_flags(core)

if(WITH_BOOST_TEST)
    set_compiler_flags(editor_tests)
endif()

install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME "editor")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "example@example.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-test-dev")
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(NAME editor_tests COMMAND editor_tests)
endif()