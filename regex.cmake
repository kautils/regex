if(NOT DEFINED KAUTIL_THIRD_PARTY_DIR)
    set(KAUTIL_THIRD_PARTY_DIR ${CMAKE_BINARY_DIR})
    file(MAKE_DIRECTORY "${KAUTIL_THIRD_PARTY_DIR}")
endif()

macro(git_clone url)
    get_filename_component(file_name ${url} NAME)
    if(NOT EXISTS ${KAUTIL_THIRD_PARTY_DIR}/kautil_cmake/${file_name})
        file(DOWNLOAD ${url} "${KAUTIL_THIRD_PARTY_DIR}/kautil_cmake/${file_name}")
    endif()
    include("${KAUTIL_THIRD_PARTY_DIR}/kautil_cmake/${file_name}")
    unset(file_name)
endmacro()

git_clone(https://raw.githubusercontent.com/kautils/CMakeLibrarytemplate/v0.0.1/CMakeLibrarytemplate.cmake)
git_clone(https://raw.githubusercontent.com/kautils/CMakeFetchKautilModule/v0.0.1/CMakeFetchKautilModule.cmake)


CMakeFetchKautilModule(sharedlib GIT https://github.com/kautils/sharedlib.git REMOTE origin TAG v0.0.1 )
find_package(KautilSharedlib.0.0.1.static REQUIRED)


include(regex_definition/regex_definition.cmake)
set(__definition_target kautil_wstd_regex_definition_${PROJECT_VERSION}_shared)
set(__definition_file_name ${CMAKE_SHARED_LIBRARY_PREFIX}${__definition_target}${CMAKE_SHARED_LIBRARY_SUFFIX})
install(TARGETS ${__definition_target} EXPORT ${__definition_target} DESTINATION lib)



set(module_name regex)
get_filename_component(__include_dir "${CMAKE_CURRENT_LIST_DIR}" DIRECTORY)
unset(srcs)
file(GLOB srcs ${CMAKE_CURRENT_LIST_DIR}/*.cc)
set(${module_name}_common_pref
    #DEBUG_VERBOSE
    MODULE_PREFIX kautil wstd
    MODULE_NAME ${module_name}
    INCLUDES $<BUILD_INTERFACE:${__include_dir}> $<INSTALL_INTERFACE:include>
    SOURCES ${srcs}
    LINK_LIBS kautil::sharedlib::0.0.1::static 
    EXPORT_NAME_PREFIX ${PROJECT_NAME}
    EXPORT_VERSION ${PROJECT_VERSION}
    EXPORT_VERSION_COMPATIBILITY AnyNewerVersion

    DESTINATION_INCLUDE_DIR include/kautil/wstd
    DESTINATION_CMAKE_DIR cmake
    DESTINATION_LIB_DIR lib
)


CMakeLibraryTemplate(${module_name} EXPORT_LIB_TYPE static ${${module_name}_common_pref} )
#CMakeLibraryTemplate(${module_name} EXPORT_LIB_TYPE shared ${${module_name}_common_pref} )
add_dependencies(${${module_name}_static} ${__definition_target})

target_compile_definitions(
        ${${module_name}_static} PRIVATE
        KAUTIL_WSTD_REEGX_SO="${CMAKE_CURRENT_BINARY_DIR}/${__definition_file_name}"
)
target_compile_definitions(
        ${${module_name}_static} INTERFACE
        KAUTIL_WSTD_REEGX_SO=$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/lib/${__definition_file_name}>
)



set(__t ${${module_name}_static_tmain})
add_executable(${__t})
target_sources(${__t} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/unit_test.cc)
target_link_libraries(${__t} PRIVATE ${${module_name}_static})
target_compile_definitions(${__t} PRIVATE ${${module_name}_static_tmain_ppcs})



