#include <Wire.h>
#include <LSM6.h>

LSM6 imu;

#define XPin 13
#define YPin 12
#define ZPin 11

#define GlobalThreshold 310

#define ThreshX GlobalThreshold
#define ThreshY GlobalThreshold
#define ThreshZ GlobalThreshold

bool Xon = false;
bool Yon = false;
bool Zon = false;
int Zblock = false;
int Yblock = false;
int Xblock = false;

void setup()
{
  Wire.begin();
  if (!imu.init())
  {
    while (1);
  }
  imu.enableDefault();
}

void loop()
{
  imu.read();
  float Xax = ((float)imu.g.x)/100;
  float Zax = ((float)imu.g.z)/100;
  float Yax = ((float)imu.g.y)/100;
  Xax = abs(Xax);
  Zax = abs(Zax);
  Yax = abs(Yax);
  if(Zax > ThreshZ)
  {
    if(!Zblock)
    {
      Xon = !Xon;
    }
  }else{
    if(Zblock > 0)
    {
      Zblock--;
    }
  }
  if(Yax > ThreshY)
  {
    if(!Yblock)
    {
      Yon = !Yon;
    }
  }else{
    if(Yblock > 0)
    {
      Yblock--;
    }
  }
  if(Xax > ThreshX)
  {
    if(!Xblock)
    {
      Xon = !Xon;
    }
    Xblock = 10;
    
  }else{
    if(Xblock > 0){
    Xblock--;
    }
  }
  delay(10);
  digitalWrite(XPin,Xon ? HIGH : LOW);
  digitalWrite(YPin,Yon ? HIGH : LOW);
  digitalWrite(ZPin,Zon ? HIGH : LOW);
}
