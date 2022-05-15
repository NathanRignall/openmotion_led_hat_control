#include <iostream>
#include <thread>

#include <unistd.h>		   //Needed for I2C port
#include <fcntl.h>		   //Needed for I2C port
#include <sys/ioctl.h>	   //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port

#include <openmotion_led_hat_control.h>

namespace open_motion
{

	led_hat::led_hat(uint8_t address)
	{

		led_hat::address = address;

		char *filename = (char *)"/dev/i2c-1";
		if ((led_hat::i2c_file = open(filename, O_RDWR)) < 0)
		{
			printf("Failed to open the i2c bus.\n");
		}

		if (ioctl(led_hat::i2c_file, I2C_SLAVE, address) < 0)
		{
			printf("Failed to acquire bus access and/or talk to slave.\n");
		}

		led_hat::alive = true;
		led_hat::thread = std::thread(&led_hat::reapeat_state_alive, this);
	}

	int led_hat::state_alive()
	{
		uint8_t local_buffer[2] = {0};

		enum i2c_register command = ALIVE;
		local_buffer[0] = uint8_t(command);

		local_buffer[1] = 0x00;

		if (write(led_hat::i2c_file, local_buffer, 2) != 2)
		{
			return -1;
		}

		return 0;
	}

	void led_hat::reapeat_state_alive()
	{

		while (led_hat::alive)
		{
			led_hat::state_alive();
			usleep(500000);
		}
	}

	int led_hat::set_ir_led_brightness(uint8_t value)
	{
		uint8_t local_buffer[2] = {0};

		enum i2c_register command = IR_BRIGHT;
		local_buffer[0] = uint8_t(command);

		local_buffer[1] = value;

		if (write(led_hat::i2c_file, local_buffer, 2) != 2)
		{
			return -1;
		}

		return 0;
	}

	int led_hat::set_ring_led_brightness(uint8_t value)
	{
		uint8_t local_buffer[2] = {0};

		enum i2c_register command = RING_BRIGHT;
		local_buffer[0] = uint8_t(command);

		local_buffer[1] = value;

		if (write(led_hat::i2c_file, local_buffer, 2) != 2)
		{
			return -1;
		}

		return 0;
	}

	uint8_t led_hat::get_ir_led_brightness()
	{
		uint8_t local_buffer[1] = {0};

		enum i2c_register command = IR_BRIGHT;
		local_buffer[0] = uint8_t(command);

		if (read(led_hat::i2c_file, local_buffer, 1) != 1)
		{
			printf("Failed to read from the i2c bus.\n");
		}
		else
		{
			led_hat::hardware_state.ir_led_brightness = local_buffer[0];
		}

		return led_hat::hardware_state.ir_led_brightness;
	}
}