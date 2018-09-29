#include <String.h>
int ledpin = 2;
int spin = 3;
int rf = 12;
int rb = 10;
int lf = 9;
int lb = 11;
String path;
int re=5;
int le=6;
int rt=8;
int lt=7;
bool drun= LOW,lastbutoon = LOW;
int a[5], e, v=100, lae=0, j=0, de=80, turnde=275, ts=200, reliefde=75;
void setup()
{ Serial.begin(9600);
  pinMode(rf,OUTPUT);
  pinMode(rb,OUTPUT);
  pinMode(re, OUTPUT);
  pinMode(le, OUTPUT);
  pinMode(lf, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(spin,INPUT);
  pinMode(ledpin,OUTPUT);
  digitalWrite(4, HIGH);
}

void straight(int dv1){    //arguments are for dv(error)
 
  
  analogWrite(re,v-dv1);
  analogWrite(le,v+dv1);
    digitalWrite(rf,HIGH);
  digitalWrite(lf,HIGH); 
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW); 
}
void rev(){
  digitalWrite(rb,HIGH);
  digitalWrite(lb,HIGH);
  digitalWrite(rf,LOW);
  digitalWrite(lf,LOW); 
}
void stp()
{  
  digitalWrite(re,LOW);
  digitalWrite(le,LOW);
   digitalWrite(rf,LOW);
   digitalWrite(rb,LOW);
   digitalWrite(lf,LOW);
   digitalWrite(lb,LOW);
   delay(50);
}
void hardRight()                          //90 degree right active at turns only
{
  analogWrite(re,ts);
  analogWrite(le,ts);
  digitalWrite(rb,HIGH);
  digitalWrite(lf,HIGH);
  digitalWrite(lb,LOW);
  digitalWrite(rf,LOW);
  delay(turnde);
  stp();
}
void hardLeft()                          //90 degree left active at turns only
{ 
  analogWrite(re,ts);
  analogWrite(le,ts);
  digitalWrite(lb,HIGH);
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lf,LOW);
  delay(turnde);
  stp();
  
}
void uturn()
{
  analogWrite(re,ts);
  analogWrite(le,ts);
  digitalWrite(lb,HIGH);
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lf,LOW);
  delay(2*turnde);
  stp();  
}
int reading()                          // takes reading from sensors and converts it into a single value and returns to the main function
{int ledNo=0;
int val = 0;
a[0]=!digitalRead(A0);
a[1]=!digitalRead(A1);
a[2]=!digitalRead(A2);
a[3]=!digitalRead(A3);
a[4]=!digitalRead(A4);
  for(int i=0;i<5;i++)
  { 
    if(a[i]==1)
    {
      ledNo++;
    }
    val=val+((i+1)*10*a[i]);
   }
 // if(ledNo<4 && ledNo>0)                          //conditions to differentiate between hard right and hard left and caliberation
  //{ 
  if(val==0)
    {
      return val;
    }else
 {   val =(val/ledNo);
 return val;
 }
  //}else{
    /*if(a[4]==1)
    { 
      hardRight();
      return 51;   
    }else if(a[0]==1)
    { 
      hardLeft();
      return -1;
    }else*/ 
}
int correction(int x)                 // damps dv and returns to main function
{int y;
e=30-x;
y=2*e+0.9*(e-lae);
lae=e;
return y;
 }
void ledglow()
{
  while(digitalRead(rt) == HIGH && digitalRead(lt) == HIGH)
  {
    drun = HIGH;
    digitalWrite(ledpin, HIGH);
    delay(50);
    digitalWrite(ledpin, LOW);
    delay(50);
  }
  drun = LOW;
}
unsigned long tpassed;

void loop()
{
  int val=reading();
  Serial.print(path);
  if(val>9 && val<51){                                    // bot is deviated 
    int dv3 = correction(val);
    straight(dv3);
  }  else if(val==0 ){
    stp();
    /*uturn;
    tpassed = millis();
    while((millis()-tpassed)<reliefde){ straight(correction(reading())); delay(5);}
    */
  }
  
  if(digitalRead(rt)==HIGH && digitalRead(lt)==HIGH)
  {
    delay(de);
    if(digitalRead(rt)==HIGH && digitalRead(lt)==HIGH)
    {
      stp();
     ledglow();
    }else{
      hardLeft();
    tpassed = millis();
    while((millis()-tpassed)<reliefde){ straight(correction(reading())); delay(5);}
   }
  }
  else if(digitalRead(rt)==HIGH && digitalRead(lt)==LOW){                             //check reading function to understand this condition
      delay(de);
    if(digitalRead(A2)==LOW)
    {
      path[j] = 's';
      j++;
    }else if(digitalRead(A2) == HIGH)
    {
    hardRight(); 
    tpassed = millis();
    while((millis()-tpassed)<reliefde){ straight(correction(reading())); delay(5);}
    } 
  }
  else if(digitalRead(lt)==HIGH && digitalRead(rt)==LOW){
    delay(de);
    if(digitalRead(A0)==LOW)
    {
      path[j] = 'l';
      j++;
    }
    hardLeft();
    tpassed = millis();
    while((millis()-tpassed)<reliefde){ straight(correction(reading())); delay(5);}
  }
  delay(10);


}
  
