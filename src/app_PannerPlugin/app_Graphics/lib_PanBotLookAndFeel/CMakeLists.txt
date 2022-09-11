add_library(lib_PanBotLookAndFeel 
    STATIC 
        include/NoMachLookAndFeel.h 
        NoMachLookAndFeel.cpp
        include/lib_PanBotLookAndFeel/PanBotLookAndFeel.h
        PanBotLookAndFeel.cpp)
target_include_directories(lib_PanBotLookAndFeel PUBLIC include/lib_PanBotLookAndFeel PRIVATE include)
target_link_libraries(lib_PanBotLookAndFeel 
    PRIVATE 
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)