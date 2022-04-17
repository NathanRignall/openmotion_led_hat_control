add_library(openmotion_led_hat_control INTERFACE)

target_include_directories(openmotion_led_hat_control INTERFACE
    ./include)

target_sources(openmotion_led_hat_control
    INTERFACE
    openmotion_led_hat_control.cpp
)

target_link_libraries(openmotion_led_hat_control
    INTERFACE
)
