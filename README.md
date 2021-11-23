# Motospeed-K24-RE
Reverse engineering the motospeed K24 to be able to control the leds using openrgb.

Openrgb issue: https://gitlab.com/CalcProgrammer1/OpenRGB/-/issues/1921

The txt file contains all the data that I have managed to collect using wireshark.

Captures:
- Static
- Neon
- Wave
- Twinkle
- Radar
- Auto Ripple
- Snake
- Aurora
- Ripple
- Reactive
- Cross
- Fireworks
- Speed Respond
- Musical Rhythm
- Custom



Led layout:
- These layouts represent the way the physical leds are placed on the board

keys:

	/	led_1		led_2		led_3		led_4		/
		led_5		led_6		led_7		led_8
		led_9		led_10		led_11		led_12
		led_13		led_14		led_15		led_15,5
		led_16		led_17		led_18		led_19
	/	led_20		led_20,5	led_21		led_21,5	/

Note: the led_xx,5 don't exist however in the packets they do, so to keep things clear I added them as half leds.

Underglow:

	/	null		und_1		und_2		  und_3		und_4		  null		/
		und_23		null		null		  null		null		  und_5
		und_22		null		null		  null		null		  und_6
		und_21		null		null		  null		null		  und_7
		und_20		null		null		  null		null		  und_8
		und_19		null		null		  null		null		  und_9
		null		null		null		  null		null		  und_10
		und_18		null		null		  null		null		  und_11
		und_17		null		null		  null		null		  und_12
	/	und_16		null	        und_15	          null		und_14	          und_13        /


Data_layout:

- These layouts represent the way the data that is sent to the leds is placed in the code

see txt





To do: 
- figure out what certain packets (when in direct mode) do, see test section in txt.
