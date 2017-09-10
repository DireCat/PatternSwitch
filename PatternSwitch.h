
#ifndef PATTERNSWITCH_H
#define PATTERNSWITCH_H

#define PATTERN_RESOLUTION_MS 	10  // 255 * 10 = 2,55 sec. max delay
#define PATTERN_SIZE 32

#include <Arduino.h>
#include <EEPROM.h>
//#include <Streaming.h> 
class PatternSwitch
{
	public:
		PatternSwitch (uint16_t timeout_ms = 2000, uint8_t tollerance = 20);

		void loop ();		// insert this inside main loop
		void trigger();		// 

		// callback events
		void onSuccess (void (*func)());
		void onFail (void (*func)());
		void onRecordComplete (void (*func)());


		uint8_t getProgress();  // returns trigger counter value

		void reset ();		// optional - reset occurs automatically after timeout

		// Record a pattern
		void startRecord (); 
		void stopRecord ();	// optional as well (timeout)

		// EEPROM 
		void saveToEEPROM (uint8_t base_addr = 0);
		void loadFromEEPROM (uint8_t base_addr = 0);

		enum event_t {
			SUCCESS,
			FAIL,
			RECORDED,
			TIMEOUT
		};

		// Generic event assignment
		void setEvent (void (*func)(event_t ev));

	private:
		uint8_t timetable [PATTERN_SIZE]; 
		uint8_t len;
		uint8_t pos;
		uint8_t counter;

		void (*event_success)();
		void (*event_fail)();
		void (*event_record_complete)();
		void (*event_handler)(event_t);

		void dispatchEvent (event_t ev);

		uint8_t tollerance;

		uint32_t ck_last;
		uint32_t ck_timeout;
		uint8_t ck_toll;

		float k_speed;
		boolean recording;
};

#endif