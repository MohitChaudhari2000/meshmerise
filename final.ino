int rf = 2;
int rb = 3;
int lf = 5;
int lb = 4;
int e1 =3 ;
int e2 =5 ;
int v = 150;
String path;
int a[5],e,le,j=0,de=10;
void setup()
{

  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  
}
void straight(int dv1){    //arguments are for dv(error)

  analogWrite(e1,v+dv1);
  analogWrite(e2,v-dv1);
  digitalWrite(rf,HIGH);
  digitalWrite(lf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW); 
}
void rev(){
  analogWrite(rb,v);
  analogWrite(lb,v);
  digitalWrite(rf,LOW);
  digitalWrite(lf,LOW); 
}
void stp()
{
   digitalWrite(rf,LOW);
   digitalWrite(rb,LOW);
   digitalWrite(lf,LOW);
   digitalWrite(lb,LOW);
}
void hardRight()                          //90 degree right active at turns only
{
  digitalWrite(rf,HIGH);
  digitalWrite(lb,HIGH);
  digitalWrite(lf,LOW);
  digitalWrite(rb,LOW);
  delay(225);
  stp();
}
void hardLeft()                          //90 degree left active at turns only
{
  digitalWrite(lf,HIGH);
  digitalWrite(rb,HIGH);
  digitalWrite(rf,LOW);
  digitalWrite(lb,LOW);
  delay(225);
  stp();
  
}
int reading()                          // takes reading from sensors and converts it into a single value and returns to the main function
{int ledNo=0;
int val = 0;
  for(int i=1;i<6;i++)
  {
    a[i]=!digitalRead(i+5);
    if(a[i-1]==1)
    {
      ledNo++;
    }
    val=val+(i*10*a[i-1]);
    }
  val =(val/ledNo);
  if(ledNo<4)                          //conditions to differentiate between hard right and hard left and caliberation
  {  
 return val;
  }else{
    if(a[4]==1)
    {
      return 51;   
    }else if(a[0]==1)
    {
      return -1;
    }
  }
}
int correction(int x)                 // damps dv and returns to main function
{int y;
e=30-x;
y=0.5*e+0.1*(e-le);
le=e;
return y;
 }


void loop()
{ 
  int val=reading();
  if(val>=10 && val<51)                    //bot is deviated 
  { int dv3 = correction(val);
    straight(dv3);
  }else if(val>50)                             //check reading function to understand this condition
  { delay(de);
  if(!digitalRead(8)==HIGH)
  {
    path[j] = 'r';
    j++;
  }
    hardRight();
  }else if(val<0)
  { delay(de);
    if(!digitalRead(8)==HIGH)
  {
    path[j] = 'l';
    j++;
  }
    hardLeft();
    
  }
  delay(50);
}
