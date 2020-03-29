# check than command don't exist not override priviosus
if(COMMAND __17_and_warnings)
    message(FATAL_ERROR "function/macro __17_and_warnings already exist")
endif()

macro(__17_and_warnings TARGET_NAME STANDART_NUM)

if(NOT DEFINED ${STANDART_NUM})
    set(STANDART_NUM 17)
endif()

target_compile_features(${TARGET_NAME}
    PUBLIC cxx_std_${STANDART_NUM}
)

target_compile_options(${TARGET_NAME}
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

endmacro(__17_and_warnings)
