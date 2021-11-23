# Motospeed-K24-RE
Reverse engineering the motospeed K24 to be able to control the leds using openrgb.

Openrgb issue: https://gitlab.com/CalcProgrammer1/OpenRGB/-/issues/1921

The txt file contains all the data that I have managed to collect using wireshark.

Key modes:
- Static 
	- (Captures see: Motospeed_K24_Static_RGB_bright-4-3-2-1-0.pcapng)
	![image](https://user-images.githubusercontent.com/79994912/143054558-3b396530-6883-4bbf-882c-8f0fb724dfc9.png)
	
	- Static mode has variables:
		- Color_random
		- Color_1
		- Color_2
		- Brightness
	
	
- Neon
 	- (Captures see: Motospeed_K24_Neon_RrandomB_bright-4-3-2-1-0_speed-4-3-2-1-0.pcapng)
 	![image](https://user-images.githubusercontent.com/79994912/143055721-d490e10f-449c-4260-b216-dc598347fe8b.png)
 
 	- Neon mode has variables:
		- Color_random
		- Color_1
		- Color_2
		- Brightness
		- Speed

- Breath
	- (Captures see: Motospeed_K24_Breath_Rrandom_bright-4-3-2-1-0_speed-4-3-2-1-0.pcapng)
	![image](https://user-images.githubusercontent.com/79994912/143056223-abcb9af5-4558-40b7-98db-fcf1ae3f6855.png)

	- Breath mode has variables:
		- Color_random
		- Color_1
		- Color_2
		- Brightness
		- Speed

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
