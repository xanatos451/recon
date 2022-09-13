# Latest version available on Release page - console updater by mhils
https://github.com/qba667/FlySkyI6/releases

![alt text](https://github.com/qba667/FlySkyI6/blob/master/update.png)
#
RCgroups Discussion here: https://www.rcgroups.com/forums/showthread.php?2486545-FlySky-FS-i6-8-channels-firmware-patch%21/page122
#
# FlySky-i6-Mod-10ch
![](https://github.com/benb0jangles/FlySky-i6-Mod-/blob/master/Images%20for%20readme/mod-i6-snap.jpg)
#
# Fsi6 Telemetry/Mavlink Firmware: *Special Version*
*Update: After discussion, it is decided that experimental unique mavlink/telemetry versions of the fsi6 mod firmware is better suited to use Basei6_updater from now on as it will allow faster testing, without the need for .exe packaging. This means it is a little bit more complicated for the average user to learn to do, but it means that also the user will be able to customise telemetry menu as required before flashing to i6 transmitter (only some telemetry parameters can fit onto screen at one time, so selection of those is necessary before flashing). Users who are uncertain using this version should either learn to use it, or stick to simple Windows .exe (Executable) version which is what everyone seems to use (but new experimental .exe version releases are less frequent than .bin file releases).
#
Basei6_updater is here: https://github.com/ThomHPL/BaseI6_updater
#
mhils updater is here: 
https://github.com/mhils/flysky-updater
#
Nice Youtube Video Guide: how to flash using .bin files + Basei6 Updater: https://www.youtube.com/watch?v=sCdORlxw8xY&ab_channel=MKmeLab
#
Depreciated from 07/05/2017:
(https://github.com/benb0jangles/FlySky-i6-Mod-/tree/master/10ch%20Mavlink%20Mod%20i6%20Updater)
##
# Description:
A collection of software modifications for the FlySky i6, some useful, some experiment. All use of this repository is experimental and you use at your own risk. But, progress is being made. Please also note that this project is now contributed by many developers/engineers who deserve lots of recognition for their (free) time, knowledge & effort, so please say thanks to all contributors and not me as a single entity. Open/Free Devs need hugs too. Thanks :)

Project goals:
- Increase number of channels (using PPM or ibus)
- Enable Mavlink/APM Telemetry (using ia6b receiver)
- Ability to edit TX Voltage reading & alarm (allowing lithium battery power)
- Edit duration of 1 minute 'inactive' alarm
- Functional Flight Timer
- RSSI

Notable thanks to contributors (alphabetical order):
Benbojangles, DBorthwick, mhils, Povlhp, qba667,ThomHpl

/-----------------------------------------------------------------------------------------------------/

At present we have the following achievements using the FlySky i6:
- We are able to flash different official firmware to the i6 and explore each new firmware
- there are hidden menus to change things like: e.g: tx voltage measurement, stick centering etc
![](http://3.bp.blogspot.com/-Nj7mgAIT7MA/Vh5VKxS7OHI/AAAAAAAAEws/Srsql8ZaRrE/s1600/i6-tx.jpg)
![](http://4.bp.blogspot.com/-2-VoNcjyxok/Vh5ZktnN3WI/AAAAAAAAEw8/HZ8-ryeElaA/s1600/1menu-i6.jpg)
- there is secret way to enter firmware update mode ![](http://4.bp.blogspot.com/-L71EbAD5BOw/VjwdEn_-eOI/AAAAAAAAEys/0qlKbKI8ZUk/s1600/i6-firmware-mode-pic.jpg)
- flashing the i6 using trainer port - to - FTDI/UART does not affect the bootloader code (as is understood 17/11/2015)
![](http://4.bp.blogspot.com/-8cAZaMrxo7E/VOfhg4rcxlI/AAAAAAAADd4/MQmE-XY-Oo0/s1600/flysky-diy-cable.jpg)
- flashing the i6 using it's internal DEBUG PORT/JTAG is possible to change the bootloader, collect eeprom data, and change firmware
- There is a guide to FTDI flashing i6 with different official firmware: (http://dalybulge.blogspot.co.uk/2015/10/turnigyflysky-i6-secret-menu.html?view=classic)
- There is a guide to flashing i6 for 8ch mod using Jtag(https://github.com/ThomHPL/FSi6_updater) Also guide (https://basejunction.wordpress.com/2015/09/13/en-flysky-i6-part-3-firmware-patching/) Also easy explanation here (https://github.com/benb0jangles/FlySky-i6-Mod-/tree/master/Developer%20Files/SWD%20port%20Flashing%20Guide)
- Experiments using Arduino IDE v1.6.6 are ongoing (https://www.arduino.cc/en/Main/Software), with Teensyduino Add-on (https://www.pjrc.com/teensy/teensyduino.html) (Settings > Board > Teensy LC > 48mhz) (LCD example: ST7565)
- Flashing under Linux (wine) is possible, but you may need to map wine's COM1 to the actual com port (e.g. /dev/ttyUSB0)
(https://www.winehq.org/docs/wineusr-guide/misc-things-to-configure#AEN901)
- There is also a native uploader for Linux, see https://github.com/mhils/flysky-updater
- If you have interested in learning about the process involved in accessing, reading then reversing firmware I will add links here:
(http://jcjc-dev.com/2016/12/14/reversing-huawei-5-reversing-firmware/)

More will be added/edited as progress is made. Please send me PM me if you have changes/updates: 
email:i6mods@gmail.com
RCgroups.com:Benbojangles
Diydrones.com:Benbojangles
http://dalybulge.blogspot.co.uk/2015/10/turnigyflysky-i6-secret-menu.html?view=classic

<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">Creative Commons Attribution-NonCommercial 4.0 International License</a>.
