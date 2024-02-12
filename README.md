# Password System 
This is a password system implementation using an LCD display, a keypad, and some buttons. The system allows the user to set a password, enter the password, and provides feedback on whether the password is correct or not.

## Features
##### Set a password: The user can set a password by entering it using the keypad. The entered password is displayed on the LCD as asterisks.

##### Enter a password: The user can enter a password to check if it matches the set password. The entered password is also displayed as asterisks.

##### Password comparison: The system compares the entered password with the set password and provides feedback on whether the password is correct or not.

##### Retry mechanism If the user enters an incorrect password, they are given a certain number of tries before they have to wait for a specific duration. After each attempt, the LCD is cleared, and the remaining tries are displayed.

Restart after successful login: If the user enters the correct password, they are greeted with a message, and the system restarts after a certain duration.

## Hardware Requirements
##### LCD display: The system requires an LCD display to show messages and password input/output.

##### Keypad: A keypad is needed for the user to enter the password.

##### Buttons: Start button and other buttons for navigation and system control.

## Usage
Connect the LCD display, keypad, and buttons to the appropriate pins of your microcontroller or development board.

Compile and upload the code to your microcontroller or development board.

Power on the system and wait for initialization.

Press the start button to begin.

Select the desired option using the keypad:

Option 1: Set a password.
Option 2: Enter a password.
Option 3: Clear the password.
Follow the instructions on the LCD display to set or enter the password.

If the entered password is incorrect, the system will display the remaining tries and provide feedback.

If the entered password is correct, the system will display a greeting message and restart after a certain duration.
