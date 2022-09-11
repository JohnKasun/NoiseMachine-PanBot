set(LIB lib_PanBot)
add_library(${LIB} STATIC PanBot.cpp include/PanBot.h)
target_include_directories(${LIB} PUBLIC include)
target_link_libraries(${LIB} PRIVATE lib_Lfo)