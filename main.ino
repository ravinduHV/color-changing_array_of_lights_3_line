#include "relay.h"

using namespace std;

float time = 1000;
float weight;
int round_count;

int pins[] = {3,4,6};
const int relay_array_size = 3;
relay color_array_RBY [relay_array_size];

unsigned long currentMillis;
unsigned long startMillis;
const unsigned long period = 1000;

void setup()
{
  Serial.begin(9600); 
  for (int i = 0; i < relay_array_size; i++)
  {
    color_array_RBY[i].set_pin(pins[i]);
    if(i > 0)
    {
      color_array_RBY[i-1].set_next_relay(&color_array_RBY[i]);
    }
  } 
  color_array_RBY[relay_array_size-1].set_next_relay(&color_array_RBY[0]);
  startMillis = millis();
}


void loop()
{
  pattern_1();
  pattern_2();
  pattern_3();
  //reverse_pattern_1();
  //reverse_pattern_2();
}


void pattern_1()
{
  currentMillis = millis();
  for (int i = 0; i < relay_array_size; i++)
  {
    color_array_RBY[i].on();
    while(true)
    {
      currentMillis = millis();
      if(currentMillis - startMillis >= period*3)
      {
        startMillis = currentMillis;
        break;
      }
    }
    color_array_RBY[i].off();
  }
}

void pattern_2()
{
  currentMillis = millis();
  for (int i = 0; i < relay_array_size; i++)
  {
    color_array_RBY[i].on();
    color_array_RBY[i].next_relay()->on();
    while(true)
    {
      currentMillis = millis();
      if(currentMillis - startMillis >= period*4)
      {
        startMillis = currentMillis;
        break;
      }
    }
    color_array_RBY[i].off();
  }
}

void pattern_3()
{
  up_all();
  while(true)
  {
    currentMillis = millis();
    if(currentMillis - startMillis >= period*4)
    {
      startMillis = currentMillis;
      break;
    }
  }
  down_all();
}
void reverse_pattern_1();
void reverse_pattern_2();
void down_all()
{
  for (int i = 0; i < relay_array_size; i++)
  {
    color_array_RBY[i].off();
  }
}

void up_all()
{
  for (int i = 0; i < relay_array_size; i++)
  {
    color_array_RBY[i].on();
  }
}

