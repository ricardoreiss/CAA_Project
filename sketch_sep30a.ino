#include <LiquidCrystal.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Keypad.h>
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

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

byte rowPins[numRows] = {52, 50, 48,46}; //Rows 0 to 3
byte colPins[numCols]= {44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22}; //Columns 0 to 3
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

char ids[48]= {'1', '2', '3', 'A', 'q', 'w', 'e', 'r', 'Q', 'W', 'E', 'R', '4', '5', '6', 'B', 's', 'd', 'f', 'g', 'S', 'Y', 'F', 'G', '7', '8', '9', 'C', 'z', 'x', 'c', 'v', 'Z', 'X', 'P', 'V', '*', '0', '#', 'D', 'j', 'k', 'l', 'o', 'J', 'K', 'L', 'O'};
String words[48] = {"Ola", "Meu", "Aqui", "Familia", "Estou", "Gosto", "Ter", "Dormir", "Casa", "Difícil", "Banheiro", "Triste",
"Voce", "Com", "Feliz", "Obrigado", "Sentindo", "Comer", "Sou", "Tirar", "Escola", "Socorro", "Hospital", "Nivel de Intensidade", 
"Eu", "De", "Bem", "Amigos", "Preciso", "Comida", "Quero", "Fala", "Nao", "Medo", "Policia", "Reproduzir", 
"Me", "Isso", "Autista", "Identificar", "Onde", "Quem", "Quando", "Ir", "Fome", "Dor", "Mal", "Delete"};

int key = 0;
String fraseid = "";
int theLast = 0;
int intensidade = 1;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

String strs[20];
int StringCount = 0;
int rd;

void song(){
  myDFPlayer.playFolder(1, 1);
  delay(1000);
  myDFPlayer.stop();
  myDFPlayer.playFolder(1,2);
}

void setup()
{
lcd.begin(16, 2);
mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

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
    if (intensidade == 10){
      intensidade = 0;
    };
    
    intensidade++;
    break;

  case 35: //Reproduzir
    Serial.println("Reproduzir...");
    break;


  case 47: //Delete
    theLast = fraseid.lastIndexOf('>'); 
    fraseid = fraseid.substring(0, theLast);
    fraseid = fraseid.substring(0, fraseid.lastIndexOf('>')+1);
    break;
      
  default:
      Serial.println("Key:" + String(key));
      myDFPlayer.playFolder(1, key + 1);
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
