// Keypad 4x4 Inputting data
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <Keypad.h>

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 12; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A', 'q', 'w', 'e', 'r', 'Q', 'W', 'E', 'R'}, 
{'4', '5', '6', 'B', 's', 'd', 'f', 'g', 'S', 'Y', 'F', 'G'}, 
{'7', '8', '9', 'C', 'z', 'x', 'c', 'v', 'Z', 'X', 'P', 'V'},
{'*', '0', '#', 'D', 'j', 'k', 'l', 'o', 'J', 'K', 'L', 'O'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {52, 50, 48,46}; //Rows 0 to 3
byte colPins[numCols]= {44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
lcd.begin(16, 2);
Serial.begin(9600);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
char keypressed = myKeypad.getKey();
if (keypressed != NO_KEY)
{
Serial.println(keypressed);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(keypressed);
}
}
