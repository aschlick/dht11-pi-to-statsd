#ifndef DHT11_H
#define DHT11_H

class Dht11 {
private:
  int pin;

public:
  Dht11(int pin);
  float* getTempAndHumidity();
}

#endif
