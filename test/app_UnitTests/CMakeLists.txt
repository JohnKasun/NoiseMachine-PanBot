set(TEST_FILES
        lib_PanBotEngine/test/testPanBotEngine.cpp
        lib_PanBotEngine/lib_Lfo/test/testLfo.cpp 
        lib_PanBotEngine/lib_Wavetable/test/testWavetable.cpp)
list(TRANSFORM TEST_FILES PREPEND "${CMAKE_SOURCE_DIR}/src/")

set(APP app_UnitTests)
add_executable(${APP} ${TEST_FILES})
target_include_directories(${APP} PRIVATE include)
target_link_libraries(${APP}
    PRIVATE
        lib_PanBotEngine
        lib_Lfo
        gtest_main
)

add_subdirectory(googletest)
include(GoogleTest)
gtest_discover_tests(${APP})