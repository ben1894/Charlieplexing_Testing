//Charlieplexing Test by zzman1895

const unsigned char controlPins[4] = {3,4,5,6};
long timer = 1000;
unsigned char changeNumber = 0;

//Not set by a loop to allow custom led arranging
//High Pin, Ground Pin, State
unsigned char leds[12][3]
{
  {controlPins[0],controlPins[1],false},
  {controlPins[0],controlPins[2],false},
  {controlPins[0],controlPins[3],false},
  
  {controlPins[1],controlPins[0],false},
  {controlPins[1],controlPins[2],false},
  {controlPins[1],controlPins[3],false},
  
  {controlPins[2],controlPins[0],false},
  {controlPins[2],controlPins[1],false},
  {controlPins[2],controlPins[3],false},
  
  {controlPins[3],controlPins[0],false},
  {controlPins[3],controlPins[1],false},
  {controlPins[3],controlPins[2],false},
};

void setup() 
{
}

void loop() 
{
  //for four control pins, there will be four main groups
  for(int group = 0; group <= 4; group++)
  {
    //set the grouping to HIGH
    pinMode(controlPins[group], OUTPUT); 
    digitalWrite(controlPins[group], HIGH);

    //for each group, there will be 3 leds
    for(int pin = 0; pin <= 3; pin++)
    {
      //scroll through the individual leds, checking if they should be lit
      if(leds[(group*3)+pin][2] == true)
      {
        //set the corresponding pin to low to light the led...
        pinMode(leds[(group*3)+pin][1], OUTPUT);
        digitalWrite(leds[(group*3)+pin][1], LOW);
      }
      else 
      {
        //...or dont turn it on 
        pinMode(leds[(group*3)+pin][1], INPUT);
      }
    }
    //quickly flash through this group. this number is untested at the moment, probably will need to be increased.
    delayMicroseconds(8);
  }
  if(millis() > timer)
  {
    leds[changeNumber][2] = true;

    timer += 1000;
    changeNumber++;
    if(changeNumber == 12)
    {
      changeNumber = 0;
    }
  }
}
