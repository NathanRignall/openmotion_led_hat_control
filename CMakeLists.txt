add_library(led_hat_control INTERFACE)

target_include_directories(led_hat_control
    INTERFACE
    ./include)

target_sources(led_hat_control
    INTERFACE
    led_hat_control.cpp
)

target_link_libraries(led_hat_control
    INTERFACE
)
