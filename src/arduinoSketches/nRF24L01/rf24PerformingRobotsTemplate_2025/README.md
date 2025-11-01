Quick test:

1. Select the Arduino Mega.
1. Upload the receiver code. This is the default code, so you only have to
   change your CUSTOM_CHANNEL_NUMBER and your CUSTOM_ADDRESS_BYTE. 
1. Open the
   serial monitor, and you should see: 
```
VS1053 found 
radio successfully initialized 
I am a receiver on channel 90 and at address 0x33
```
1. Set up the code for the transmitter. This requires uncommenting the
   NRF_CE_PIN and NRF_CSN_PIN for the transmitter, and commenting out those
   same pins for the receiver, and then uncommenting the transmitter code and
   commenting out the receiver code. These places are marked with "CHANGEHERE"
   to make them easier to find. 
1. Select the Arduino Uno, and upload the code.
1. Open the serial monitor, and you should see:
```
Setting up LCD 
Setting up radio 
radio successfully initialized 
I am a transmitter 
```
1. Now if you press the transmit button on the transmitter,
   the LCD should say 
```transmitting 0, success
```
1. Connect your laptop to the receiver (change board back to Mega), open the serial
   monitor, and when you press the transmit button on the transmitter you
   should see the following message on the serial monitor: 
```
message received Data = 0
```
and if you press the scroll up button and then the transmit button
   you should see: 
```message received Data = 1 moving nose to 180 and drawing rectanglePlaying track 002
```
