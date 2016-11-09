# README #

### BauTek Pinball Chassis Control ###
Written by Adam Bauman (adam@kungfutreachery.net, https://bitbucket.org/adambauman/arduino-pinball_chassis_control)
1.0 (July 2016)

Provides the following chassis control functions for the Bautek Mini Pinball Cabinet:
-	Force feedback kicker solenoid control using Xbox 360 feedback motor as the trigger (see note below)
-	Cabinet RGB LED lighting control (currently running table-specific logo mood lighting)

###Note:### Xbox controller-based solenoid control software and hardware design was created by 
      zed @ http://forum.zenstudios.com/showthread.php?6657-Pinball-FX2-full-force-feedback
      (Hydris HDS on Youtube.) Thanks for sharing your awesome feedback design!

### Parts List ###

-	1x	CD4017 Decade counter
-	1x	CD4053 Analog mux/demux
-	2x	SL5501 6-pin phototransistor
-	2x	BD237 NPN power transistor
-	2x	1N4007 diodes (added from the original design for flyback protection)
-	2x	0.1 OHM resistors
-	1x	Arduino (zed used an Uno in his original design)
-	2x	24v DC contactors
-	1x	24v DC power supply (these contactors are hogs, at least 10amp minimum recommended)
-	1x	Xbox 360 game pad (wired recommended)

### Hardware Design ###

Fritzing of the feedback and RGB circuits coming soon, see zed's original post in the link above for his layout (the only edition is a flyback protection circuit across the contactors.)