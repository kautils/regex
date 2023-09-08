set(kautil_regex_definition_evacu_m ${m})
set(m kautil_regex_definition)

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/wregex_definition.cc")
    file(COPY_FILE 
            "${CMAKE_CURRENT_LIST_DIR}/regex_definition.cc" 
            "${CMAKE_CURRENT_LIST_DIR}/wregex_definition.cc")
endif()

list(APPEND ${m}_unsetter __srcs)
set(__t kautil_wstd_regex_definition_${PROJECT_VERSION}_shared)
add_library(${__t} SHARED)
file(GLOB __srcs ${CMAKE_CURRENT_LIST_DIR}/*.cc)
set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/wregex_definition.cc PROPERTIES COMPILE_DEFINITIONS KAUTIL_REGEX_WSINGLE_STRING)
target_sources(${__t} PRIVATE ${__srcs})


foreach(__var ${${m}_unsetter})
    unset(${__var})
endforeach()


set(m ${kautil_regex_definition_evacu_m})
unset(kautil_regex_definition_evacu_m)
