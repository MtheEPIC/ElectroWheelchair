#include <Wire.h>
#include <MPU6050.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); 
MPU6050 mpu;
RH_ASK driver;
int count=0;
char tmp[] = "t";
char* msg = "S";

void setup()
{
  Serial.begin(9600);   // Debugging only
  lcd.begin();//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  if (!driver.init())
  {
     Serial.println("init failed");
     lcd.print("init failed");     
  }
  Serial.println("Initialize MPU6050...");
  lcd.print("Initialize MPU6050..."); 
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
    lcd.clear(); 
    lcd.print("Could not find MPU6050");
    lcd.print("check wiring!");  
  }
  Serial.println("Initialized MPU6050!");
  lcd.clear(); 
  lcd.print("Initialized MPU"); 
  count=0;
  mpu.calibrateGyro();
  mpu.setThreshold(3);
}

void loop()
{
  Vector normAccel = mpu.readNormalizeAccel();
//  Serial.print("Y");
//  Serial.println(normAccel.YAxis);
//  Serial.print("X");
//  Serial.println(normAccel.XAxis);
  msg = "S";
  if(normAccel.YAxis < -7)
    msg = "B";
  else if(normAccel.YAxis > 3)
    msg = "F";
  else if(normAccel.XAxis > 7)
    msg = "R";
  else if(normAccel.XAxis < -6)
    msg = "L";
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.print("sent msg - ");
  Serial.println(msg);   
  lcd.clear(); 
  lcd.print("sent msg - "); 
  lcd.print(msg); 
  delay(200);
}
void gyroShow()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro(); 
  Serial.print(" Xraw = ");
  Serial.print(rawGyro.XAxis);
  Serial.print(" Xnorm = ");
  Serial.println(normGyro.XAxis);
  Serial.print(" Yraw = ");
  Serial.print(rawGyro.YAxis);
  Serial.print(" Ynorm = ");
  Serial.println(normGyro.YAxis);
  Serial.print(" Zraw = ");
  Serial.print(rawGyro.ZAxis);
  Serial.print(" Znorm = ");
  Serial.println(normGyro.ZAxis);
//  delay(200);
}

void accelShow()
{
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  Serial.print(" Xraw = ");
  Serial.print(rawAccel.XAxis);
  Serial.print(" Xnorm = ");
  Serial.println(normAccel.XAxis);
  Serial.print(" Yraw = ");
  Serial.print(rawAccel.YAxis);
  Serial.print(" Ynorm = ");
  Serial.println(normAccel.YAxis);
  Serial.print(" Zraw = ");
  Serial.print(rawAccel.ZAxis);
  Serial.print(" Znorm = ");
  Serial.println(normAccel.ZAxis);
//  delay(200);
}
