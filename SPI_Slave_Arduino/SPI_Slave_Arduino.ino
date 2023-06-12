#include <SPI.h>
#include<stdint.h>  
#define SPI_SCK 13
//#define SPI_MISO 12
#define SPI_MOSI 11
#define SPI_SS 10
//char dataBuff[500];
int dataBuff;
//Initialize SPI slave.
void SPI_SlaveInit(void) 
{ 
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  //pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);
  //make SPI as slave
  
  // Enable SPI as slave.
  SPCR = (1 << SPE);
}
//This function returns SPDR Contents 
uint8_t SPI_SlaveReceive(void)
{
  /* Wait for reception complete */
  while(!(SPSR & (1<<SPIF)));
  /* Return Data Register */
  return SPDR;
}

// The setup() function runs right after reset.
void setup() 
{
  // Initialize serial communication 
  Serial.begin(115200);
  SPI.beginTransaction (SPISettings (21000000, MSBFIRST, SPI_MODE0));
  // Initialize SPI Slave.
  SPI_SlaveInit();
  Serial.println("Slave Initialized");
}

// The loop function runs continuously after setup().
void loop() 
{
  uint32_t i;
  uint16_t dataLen = 0;
  //Serial.println("Slave waiting for ss ");
 // while(digitalRead(SS));

  i = 0;
  dataBuff =SPI_SlaveReceive();
  //for(i = 0 ; i < dataLen ; i++ )
  //{
   // dataBuff[i] =  SPI_SlaveReceive();
  //}
  //  Serial.println(String(i,HEX));
 // dataBuff[i] = '\0';
  
  Serial.println("Rcvd:");
  delay(1000);
  Serial.println(dataBuff);
  delay(1);
  //Serial.print("Length:");
  //Serial.println(dataLen);
}