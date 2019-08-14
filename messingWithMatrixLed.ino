 
 #include "LedControl.h" 
 static const short joystickX = A2;   // joystick X axis pin

  static const short joystickY = A3;   // joystick Y axis pin

  static const short joystickVCC = 15; // virtual VCC for the joystick (Analog 1) (to make the joystick connectable right next to the arduino nano)

  static const short joystickGND = 14; // virtual GND for the joystick (Analog 0) (to make the joystick connectable right next to the arduino nano)



  static const short potentiometer = A5; // potentiometer for snake speed control



  static const short CLK = 10;   // clock for LED matrix

  static const short CS  = 11;  // chip-select for LED matrix

  static const short DIN = 12; // data-in for LED matrix
  const short intensity = 1;



// lower = faster message scrolling

const short messageSpeed = 5;



// initial snake length (1...63, recommended 3)

const short initialSnakeLength = 3;
LedControl matrix(DIN, CLK, CS, 1);

const bool copterMap[8][56] = {

  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},

  {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},

  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},

  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

};
int x;
int y;
int xPin ;
int yPin ; 
int d;

void setup() {
  // put your setup code here, to run once:
  matrix.shutdown(0, false);

  matrix.setIntensity(0, 1);

  matrix.clearDisplay(0);
  x=0;
  y = 3; 
   d = 0;
   printByte();

}

void loop() {
  
 d++;//increases map visibility
 
 yPin = analogRead(2);//A2
 xPin = analogRead(3);//A3
 //process input
if(d>49){
  d = 0;
}
 if(yPin <300){
  x++;//decrease altitude
 
  if(x>7){
  x = 7;
  }
  delay(40);
   printByte();
 }
 else if(yPin >700){
  x--; //increase altitude
  if(x <1){
    x = 0;
    
  }
  delay(40);
  printByte();
 }
 //---------
 printByte();
 tone(9,400);
 delay(80);
//-------------
}
void printByte(){
 
 
  for(int col = 0; col<8; col++){
  
    for(int row = 0; row<8; row++){
     
      if(row == x && col == y){
         
         if(copterMap[row][col+d] == 1){
           x--;
          matrix.setLed(0, x, y, 1);
          tone(9,20);
          delay(40);
         }else{
          matrix.setLed(0, x, y, 1);
         }
      }
      else{
        matrix.setLed(0, row, col, copterMap[row][col +d]);
      }
    
       
    }
  
  
  }
  delay(20);
 
 
  }
