# check than command don't exist not override priviosus
if(COMMAND __find_sources)
    message(FATAL_ERROR "function/macro __find_check_and_link_lib_to_target already exist")
endif()

function(__find_sources EXTRA_DIRECTORIES)
    set(__directory ${CMAKE_CURRENT_LIST_DIR})

    message("__find_sources __directory = ${__directory}")
    file(GLOB PUB_HEADER "${__directory}/*.h")
    file(GLOB PRIV_HEADERS "${__directory}/src/*.h")
    file(GLOB PRIV_SOURCES "${__directory}/src/*.cpp")
    file(GLOB MAIN_SOURCES "${__directory}/*.cpp")

    foreach(_dir ${EXTRA_DIRECTORIES})
        file(GLOB _tmp_opt_sources "${__directory}/src/${_dir}/*.cpp")
        file(GLOB _tmp_opt_headers "${__directory}/src/${_dir}/*.h")
        set(PRIV_SOURCES ${PRIV_SOURCES} ${_tmp_opt_sources})
        set(PRIV_HEADERS ${PRIV_HEADERS} ${_tmp_opt_headers})
    endforeach()

    set(SOURCES ${MAIN_SOURCES} ${PRIV_SOURCES} ${PRIV_HEADERS} PARENT_SCOPE)
    set(HEADERS ${PRIV_HEADERS} ${PUB_HEADER} PARENT_SCOPE)
endfunction()

macro(create_lib LIB_NAME TYPE)

    set(options )
    set(oneValueArgs FOLDER_NAME)
    set(multiValueArgs DIRECTORIES)
    cmake_parse_arguments(CREATE_LIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    project(${LIB_NAME} VERSION 1.0 LANGUAGES CXX)
    __find_sources("${CREATE_LIB_DIRECTORIES}")

    message("Headers for lib ${LIB_NAME} are : ${HEADERS}")
    message("Sources for lib ${LIB_NAME} are : ${SOURCES}")

    add_library(${LIB_NAME}
        ${TYPE}

        ${SOURCES}
        ${HEADERS}
    )

    message("CMAKE_CURRENT_LIST_DIR for lib ${LIB_NAME} is ${CMAKE_CURRENT_LIST_DIR}")
    target_include_directories(${LIB_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")
    target_include_directories(${LIB_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

    set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

    target_compile_options(${LIB_NAME}
        PUBLIC

        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )


    if(USE_LIBCXX)
        target_link_libraries(
            ${LIB_NAME}
            libc++
            libc++abi
        )
    endif()
endmacro(create_lib)

macro(create_app APP_NAME STANDART_NUM)

    set(options)
    set(oneValueArgs FOLDER_NAME)
    set(multiValueArgs DIRECTORIES)
    cmake_parse_arguments(CREATE_APP "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    __find_sources("${CREATE_APP_DIRECTORIES}")

    add_executable(${APP_NAME}

        ${SOURCES}
        ${HEADERS}
    )

    target_include_directories(${APP_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src")

    set_target_properties(${APP_NAME} PROPERTIES LINKER_LANGUAGE CXX)
    __17_and_warnings(${APP_NAME} ${STANDART_NUM})

    target_compile_options(${APP_NAME} PUBLIC -no-pie -rdynamic)

    if(USE_LIBCXX)
        target_link_libraries(${APP_NAME} libc++ libc++abi -lgcc -lgcc_s -lc)
    endif()
endmacro(create_app)
