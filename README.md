Control
======
These packages are responsible for controlling the motors of the robot. 
## **roboteq**
    Provides a means to communicte with the SDC2130 Roboteq motor controller. Provides closed loop speed control (refer to manual). THIS WILL BE OUR HARDWARE INTERFACE
## **diff_drive_controller**
    Controller package we are using. 



nav stack ---- (Twist Command) ---> controller manager -> diff_drive_controller -> roboteq ---(Left & Right Velocity Commands)---> HW
# Wild-Wild-Wes
