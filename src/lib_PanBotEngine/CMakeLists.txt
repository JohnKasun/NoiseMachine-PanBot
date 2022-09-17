add_subdirectory(lib_Lfo)
add_subdirectory(lib_Wavetable)

set(LIB lib_PanBotEngine)
add_library(${LIB} STATIC PanBotEngine.cpp include/PanBotEngine.h)
target_include_directories(${LIB} PUBLIC include)
target_link_libraries(${LIB} PUBLIC lib_Lfo)