#include "storage.hpp"
#include "communications.hpp"
#include "rtc.hpp"
#include "tasks.hpp"
#include "screen.hpp"
#include "wifi.hpp"
#include "ota.hpp"


void setup(void)
{
	setup_communications();

  	setup_storage();

	setup_RTC();

	setup_tasks();

	setup_wifi();

	setup_screen();

	setup_OTA();

} 

void loop(void)
{
	loop_communications();

	loop_wifi();

	loop_screen();

	loop_OTA();

	loop_RTC();
}
