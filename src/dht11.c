#include <dht11.h>
#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>

const int MAXTIMINGS = 85;
int dht11_dat[5] = { 0, 0, 0, 0, 0};

int GetTempAndHumidity(float* data, int pin){
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
  int i = 0;
  uint8_t laststate	= HIGH;
  uint8_t counter		= 0;
  uint8_t j		= 0;

  pinMode( pin, OUTPUT );
  digitalWrite( pin, LOW );
  delay( 18 );

  digitalWrite( pin, HIGH );
  delayMicroseconds( 40 );

  pinMode( pin, INPUT );

  for ( i = 0; i < MAXTIMINGS ; i++ ){
    counter = 0;
    while ( digitalRead( pin ) == laststate ){
      counter++;
      delayMicroseconds( 1 );
      if ( counter == 255 ){
        break;
      }
    }
  }
  laststate = digitalRead( pin );

  if ( counter == 255 ){
    return 1;
  }

  /* ignore first 3 transitions */
  if ( (i >= 4) && (i % 2 == 0) ){
    /* shove each bit into the storage bytes */
    dht11_dat[j / 8] <<= 1;
    if ( counter > 16 ) {
      dht11_dat[j / 8] |= 1;
      j++;
    }
  }

  /*
   * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
   * print it out if data is good
   */
  int checksum = (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]);
  if ( (j >= 40) && (dht11_dat[4] == ( checksum & 0xFF) ) ){
    data[0] = dht11_dat[2] + (dht11_dat[3]/100);
    data[1] = dht11_dat[0] + (dht11_dat[1]/100);
    return 0;
  } else {
    return 1;
  }
}
