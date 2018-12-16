# include "neopixel/neopixel.h" // Required library

#define PIXEL_PIN D0    // define the Pin the data line is connected to on the Photon
#define PIXEL_COUNT 8   // the total number of individual NeoPixels
#define PIXEL_TYPE WS2812   // the type of NeoPixels in use
#define BRIGHTNESS 255  // set the brightness limit (value between 0-255)

int vibPin = D3;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int light = 0; // variable that tells the fob which function to run

int vibStart = 0; // a variable that is used to initialize the vibration pattern
int vibRounds = 4 ; // how many rounds of vibration do we want
int vibDelay = 300; // how long should the vibration last

// specify the maximum and minimum range of brightness values that should be taken by the fob
int MinBrightness = 10;       //value 0-255 
int MaxBrightness = 200;      //value 0-255

// how many loops should each cycle of the breathing lights take
int numLoops1 = 1;       

// steps to be taken by the lights when going up and down in brightness
int fadeInWait = 8;          // lighting up speed, steps.
int fadeOutWait = 8;         // dimming speed, steps.

//---------------------------------------------------------------------------------------------------//

void setup() {
  strip.begin(); 
  strip.show();
  
  Particle.function("fobToggle", fobToggle);
  
  pinMode(vibPin, OUTPUT);
}

/*
rgbBreathe(strip.Color(insert r,g,b color code),numLoops(refer to integer above), (duration for lights to hold before dimming. insert 0 to skip hold)
*/

int fobToggle (String color) {
/*
this custom variable name is input into the particle consol using the syntax: particle call DEVICE_NAME APP_NAME COLOR_VARIABLE
to signal the fob to glow in the required color pattern
*/
    if (color == "green") {
        light = 1;
        return 1;
    }
    
    else if (color == "yellow") {
        light = 2;
        vibStart = 0;
        return 2;
    }
    
    else if (color == "red") {
        light = 3;
        vibStart = 0;
        return 3;
    }
    
    else if (color == "blue") {
        light = 4;
        return 4;
    }
    
    else {
        light = 0;
        return 0;
    }
    
    
}

/*
rgbBreathe(strip.Color(insert r,g,b color code),numLoops(refer to integer above), (duration for lights to hold before dimming. insert 0 to skip hold)
*/

void loop() {
  
  if (light == 1) {
      
      rgbBreathe(strip.Color(0, 128, 0), numLoops1, 150); //green
  }
  
  else if (light == 2) {
      while (vibStart < vibRounds) {
          digitalWrite(vibPin, HIGH);
          delay(vibDelay);
          
          digitalWrite(vibPin, LOW);
          delay(vibDelay);
          vibStart = vibStart + 1;
      }
      
      rgbBreathe(strip.Color(255, 100, 0), numLoops1, 150); //yellow
  }
  
  else if (light == 3) {
      
      while (vibStart < vibRounds) {
          digitalWrite(vibPin, HIGH);
          delay(vibDelay);
          
          digitalWrite(vibPin, LOW);
          delay(vibDelay);
          vibStart = vibStart + 1;
      }
      
      rgbBreathe(strip.Color(255, 0, 0), numLoops1, 150); //red
  }
  
  else if (light == 4) {
      
      rgbBreathe(strip.Color(0,  0, 250), numLoops1, 150); //red
  }
  
  else {
      rgbBreathe(strip.Color(0, 0 , 0), numLoops1, 0);
  }
  
}


//code modified from: https://github.com/kit-ho/NeoPixel-WS2812b-Strip-Breathing-Code-with-Arduino/blob/master/Breather_v1.1.ino
void rgbBreathe(uint32_t c, uint8_t x, uint8_t y) {
  for (int j = 0; j < x; j++) {
    for (uint8_t b = MinBrightness; b < MaxBrightness; b++) {
      strip.setBrightness(b * 255 / 255);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
      }
      strip.show();
      delay(fadeInWait);
    }
    strip.setBrightness(MaxBrightness * 255 / 255);
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(y);
    }
    for (uint8_t b = MaxBrightness; b > MinBrightness; b--) {
      strip.setBrightness(b * 255 / 255);
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
      }
      strip.show();
      delay(fadeOutWait);
    }
  }
}
