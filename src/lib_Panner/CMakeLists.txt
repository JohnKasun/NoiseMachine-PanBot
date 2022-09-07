set(LIB lib_Panner)
add_library(${LIB} STATIC Panner.cpp include/Panner.h)
target_include_directories(${LIB} PUBLIC include)
target_link_libraries(${LIB} PRIVATE lib_Lfo)