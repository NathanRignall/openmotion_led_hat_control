
#include <stdint.h>
#include <thread>

#ifndef _LED_HAT_
#define _LED_HAT_

namespace open_motion
{

    class led_hat
    {

        enum ir_led_mode
        {
            SIMPLE,
            ACTIVE
        };

        enum ring_led_effect
        {
            BLANK = 0x00,
            BOOTING = 0x01,
            LOADING = 0x02,
            OKAY = 0x03,
            DISCONNECTED = 0x04,
            ERROR = 0x05,
        };

        enum i2c_register
        {
            HAT_ID_B0 = 0x00,
            HAT_ID_B1 = 0x01,
            HAT_ID_B2 = 0x02,
            HAT_ID_B3 = 0x03,
            HAT_ID_B4 = 0x04,
            HAT_ID_B5 = 0x05,
            HAT_ID_B6 = 0x06,
            HAT_ID_B7 = 0x07,
            HARD_ID_B0 = 0x08,
            HARD_ID_B1 = 0x09,
            SOFT_ID_B0 = 0x0A,
            SOFT_ID_B1 = 0x0B,
            HAT_POWER = 0x10,
            IR_MODE = 0x11,
            RING_MODE = 0x12,
            IR_BRIGHT = 0x20,
            RING_BRIGHT = 0x21,
            ROTATION = 0x30,
            TEMP_B0 = 0x31,
            TEMP_B1 = 0x32,
            P_STATUS = 0x40,
            H_STATUS = 0x41,
            ALIVE = 0xA0,
        };

    private:
        uint8_t address;
        int i2c_file;

        std::thread thread;
        bool alive;

        struct hardware_state
        {
            uint8_t ir_led_brightness;
            uint8_t ring_led_brightness;
            enum ir_led_mode ir_led_mode;
            enum ring_led_effect ring_led_effect;
        };

        hardware_state hardware_state;

        int state_alive();
        void reapeat_state_alive();
        
    public:
        led_hat(uint8_t address);

        int set_alive();
        int get_alive();
        
        int set_ir_led_brightness(uint8_t value);
        int set_ring_led_brightness(uint8_t value);
        int set_ir_led_mode(enum ir_led_mode ir_led_mode);
        int set_ring_led_effect(enum ring_led_effect ring_led_effect);

        uint8_t get_ir_led_brightness();
        uint8_t get_ring_led_brightness();
        enum ir_led_mode get_ir_led_mode();
        enum ring_led_effect get_ring_led_effect();
                
    };

}

#endif