add_subdirectory(lib_SelectorPanel)

add_library(lib_PanBotLookAndFeel STATIC include/PanBotLookAndFeel.h PanBotLookAndFeel.cpp)
target_include_directories(lib_PanBotLookAndFeel PUBLIC include)
target_link_libraries(lib_PanBotLookAndFeel 
    PRIVATE 
        juce::juce_gui_extra
    PUBLIC
        lib_SelectorPanel
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)