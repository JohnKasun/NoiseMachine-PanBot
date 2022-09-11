add_library(lib_SelectorPanel STATIC SelectorPanel.cpp)
target_include_directories(lib_SelectorPanel PUBLIC include)
target_link_libraries(lib_SelectorPanel 
    PRIVATE 
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)