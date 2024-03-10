boolean Running = false;
unsigned long StartTime = 0;
unsigned long StopTime = 0;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  unsigned long currentTime = millis();// set current time to millis

  if (! Running)
  {
    StartTime = currentTime;// when start event occurs set start time to current time
    Running = true;//and move to (Running)
  }

  if (Running)
  {
    Serial.println(currentTime - StartTime);//This is where i get confused. aren't these the same? Both were made equal in first IF and are current Millis?
  }
  else
  {
    Serial.println(StopTime);
  }
}
