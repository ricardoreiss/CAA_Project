
// Keypad 4x4 Inputting data
#include <LiquidCrystal.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
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

char ids[48]= {'1', '2', '3', 'A', 'q', 'w', 'e', 'r', 'Q', 'W', 'E', 'R', '4', '5', '6', 'B', 's', 'd', 'f', 'g', 'S', 'Y', 'F', 'G', '7', '8', '9', 'C', 'z', 'x', 'c', 'v', 'Z', 'X', 'P', 'V', '*', '0', '#', 'D', 'j', 'k', 'l', 'o', 'J', 'K', 'L', 'O'};
String words[48] = {"Ola", "Meu", "Aqui", "Familia", "Estou", "Gosto", "Tenho", "Dormir", "Casa", "Dificuldade", "Banheiro", "Triste",
"Voce", "Com", "Feliz", "Sonho", "Sentindo", "Comer", "Sou", "Tirar", "Escola", "Socorro", "Hospital", "Nivel de Intensidade", 
"Eu", "De", "Bem", "Amigos", "Preciso", "Comida", "Quero", "Fala", "Nao", "Medo", "Policia", "Reproduzir", 
"Me", "Isso", "Autista", "Identificar", "Onde", "Tem", "Ir", "Esta", "Fome", "Dor", "Mal", "Delete"};

int key = 0;

String fraseid = "";
int theLast = 0;

int intensidade = 1;

#define pinTx 9
#define pinRx 8
#define volume 30

SoftwareSerial playerMP3Serial(pinRx, pinTx);
DFRobotDFPlayerMini playerMP3;

void setup()
{
lcd.begin(16, 2);
Serial.begin(9600);
playerMP3Serial.begin(9600);
playerMP3.volume(volume);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY)
  {
    for(int id = 0; id < 48; id++ ){
      if (ids[id] == keypressed){
        key = id;};
    };

    switch (key) {
    case 23: //Nível de Intensidade
      if (intensidade == 3){
        intensidade = 0;
      };
      
      intensidade++;
      break;

    case 35: //Reproduzir
      playerMP3.playFolder(1,1); 
      break;

    case 47: //Delete
      theLast = fraseid.lastIndexOf('>'); 
      fraseid = fraseid.substring(0, theLast);
      fraseid = fraseid.substring(0, fraseid.lastIndexOf('>')+1);
      break;
        
    default:
        fraseid +=String(key) + ">";    
    }

    String fid = fraseid;
    
    String strs[20];
    int StringCount = 0;
    while (fid.length() > 0){
      int index = fid.indexOf('>');
      if (index == -1){
        strs[StringCount++] = fid;
        break;
      }else{
        strs[StringCount++] = fid.substring(0, index);
        fid = fid.substring(index+1);
      }
    }

    String frase = "";

    for (int o = 0; o < StringCount; o++){
      String idw = strs[o];
      String word = words[idw.toInt()];
      frase += word + " ";
    };


    Serial.println(intensidade);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(frase.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(frase.substring(16));

    


 }
}