#include "FreqCountESP.h"

int inputPin = 4;
int timerMs = 1000;
int gpio_pin = 16;  // should not assign GPIO #36 throough #39

void setup()
{
  Serial.begin(115200);
  FreqCountESP.begin(inputPin, timerMs);
  pulse_test(gpio_pin, 32000000);
}

void loop()
{
  if (FreqCountESP.available())
  {
    uint32_t frequency = FreqCountESP.read();
    Serial.println(frequency);
  }
}

#define LEDC_BIT_MAX 16

void pulse_test(uint8_t gpio_pin, uint32_t freq) {
  freq = constrain(freq, 1, 40000000);
  byte p_range = constrain(int(log(80e6/freq)/log(2)), 1, LEDC_BIT_MAX);
  pinMode(gpio_pin, OUTPUT);
  ledcSetClockSource((ledc_clk_cfg_t) LEDC_APB_CLK);
  ledcAttach(gpio_pin, freq, p_range);
  ledcWrite(gpio_pin, 1 << (p_range - 1));  // duty 50%
}
