# ARM_Projects
These are the projects which I worked on, some of it were a university assignments<br/>
Others was made just to improve my self

## For the First Project => Simple Counter Project:
Components:<br/>
1- three 7-segment with decoders<br/>
2- three Push_buttons<br/>
3- TM4C123 (Tiva C Kit)<br/>
4- Power supply <br/>

Functions Required:<br/>
1-when you press on the first pb it will start counting and the results will be displayed on 7-segment<br/>
2- when you press the second one it will decrease the counted value by one,it will do so only when you press it, whatever the duration you kept pressing on it, it will decrease the value by one (on press)<br/>
3- when you press the third puh button it will do nothing but when you release it, it will reset the counter (on release)<br/>

## For the Second Project => Smart Home:
Components:<br/>
1- TM4C123 (Tiva C Kit)<br/>
2- Servo_motor<br/>

Functions Required:<br/>
1- First you keep reading the Temp. from the temp. sensor wich is internally implemented inside the Tiva, and sends the reading via UART to another Tiva, which will display the reading on LCD<br/>
2- You will get a reading from another Tiva (that reading corresponds to a change in a potentiometer value), So you will get the value received and change the brightness of the LED(via PWM) wich is implemented on the Tiva<br/>
3- You will get a reading from another Tiva (which corresponds to the value of the two push_buttons implemented on the Tiva), So you will get the reading and Control the movement of the Servo whether it goes to the right or the left depending on the value received<br/>
