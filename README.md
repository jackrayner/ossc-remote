# ossc-remote
Use an Arduino to send OSSC remote codes. Useful if you don't have a remote, you purchased a "blank" L336 remote or accidentally overwrote some buttons on your L336 remote!

This Arduino sketch supports two modes:
* Mode `1` will send your selected remote code once, so you can use your Arduino as a (slow) remote control for the OSSC. 
* Mode `2` will send the same code for 15 seconds at half-second intervals, for use when programming an L336 remote.

To change modes, reset the Arduino.

The hex codes sent to the OSSC are the defaults included in the firmware and can be found [here](http://junkerhq.net/xrgb/index.php?title=OSSC_LIRC_Script). They are already included in the Arduino sketch so you just need to the number from the list at the bottom of this README.

## Pre-requisites

* Arduino board
* IR L.E.D
* Suitable resistor for the L.E.D
* Computer
* (Optional) L336 learning remote

## Setup

### Board

* Attach the resistor to one of the L.E.D legs
* Connect the positive leg of the L.E.D/resistor to pin 3 of the Arduino
* Connect negative leg of the L.E.D/resistor to ground
* Connect your Arduino to your computer

### Code

* Clone this repo
* Open `remote.ino` with the (Arduino IDE)[https://www.arduino.cc/en/Main/Software]
* Install the [IR Remote library](https://github.com/z3t0/Arduino-IRremote) using [this](https://www.arduino.cc/en/guide/libraries#toc3) guide
* Open the serial monitor window (Tools > Serial monitor)
* Upload the sketch to the board

## Usage

### Mode `1`: Remote mode

* After uploading the sketch to the Arduino, you should see the following printed to the serial monitor:

```
START /Users/jack/code/ossc-remote/remote.ino from Oct 10 2020
Ready to send IR signals at pin 3
Choose 1 for remote mode, 2 for L336 programming.
```

* To use the Arduino as a remote, type `1` into the box and press `send`. You will then see the following prompt.

```
Please enter button number.
```

* Position the L.E.D so it's facing the IR receiver on the OSSC, then type in a number that corresponds with the list at the bottom of this README (e.g. `14` for `MENU`) and you'll see the following

```
Sending code for button 0 (3EC129D6) 
Please enter button number.
```

* Your OSSC should respond to the code entered and you can send another number to the Arduino to continue controlling the OSSC.

### Mode `2`: Programming mode

* To program an L336 remote, turn on the Arduino and instead type `2` into the prompt. This will make the Arduino send the same code you select for 15 seconds (every half second).

```
START /Users/jack/code/ossc-remote/remote.ino from Oct 10 2020
Ready to send IR signals at pin 3
Choose 1 for remote mode, 2 for L336 programming.
```

* Get your L336 remote and position the L.E.D of the Arduino so it's facing the IR LED of the L336 remote. They to be very close - if not touching - to work.

* Enter the code for the button you want to program into the serial monitor **but do not press `send` yet**.

* On the remote, press once the device button (TV or DVR or HIFI) you want to assign for use with your OSSC, then press and hold the same button until the red light's brightness increases and stays lit when you release the button. Move on to the next step within ~10 seconds, otherwise you will need to repeat this.

* Press `send` to make the Arduino start sending the code and immediately move to the next step.

```
Please enter button number.
Sending code for button 0 (3EC129D6) for 15 seconds.............................
```

* Press and hold the button on the remote corresponding to the number you've entered. The red light will go out. Then release it after about 3 seconds and the red light should blink rapidly 3 times and then go back to a steady red. If it just blinks red then you need to retry.

* Press the same device button once (TV or DVR or HIFI) to exit learning mode. The red light should go off on the remote.

* Test out the button on the remote to see if it controls your OSSC! Repeat this section for all of the buttons you want to program.

## Remote codes

Enter the list number into the serial console for the button you want. 

e.g. `1` for the button `1` or `14` for `MENU`.

1. "1"            
2. "2"            
3. "3"            
4. "4"            
5. "5"            
6. "6"            
7. "7"            
8. "8"            
9. "9"            
10. "0"            
11. "10+"          
12. "TOGGLE/RETURN"
13. "PIC/CANCEL"   
14. "MENU"         
15. "EXIT"         
16. "INFO"         
17. "CLOCK/EJECT"  
18. "REWIND"       
19. "FORWARD"      
20. "L/R"          
21. "PAUSE/ZOOM"   
22. "CHAPTER-"     
23. "CHAPTER+"     
24. "STOP"         
25. "PLAY"         
26. "LEFT"         
27. "RIGHT"        
28. "UP"           
29. "DOWN"         
30. "OK"           
31. "POWER"        
32. "VOL-"         
33. "VOL+"         
34. "MUTE"         
35. "CH+"          
36. "CH-"          
37. "TV/AV"        
38. "PNS"          
39. "TONE-"        
40. "TONE+"        