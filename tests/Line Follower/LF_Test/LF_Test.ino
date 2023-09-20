
int IRS_1 = 2;
int IRS_2 = 3;
int IRS_3 = 4;
int IRS_4 = 5;
int IRS_5 = 6;
int SWITCH = 7;
int IRS_Front = 8;
bool S1, S2, S3, S4, S5, S6, S7;
char strBuf[70];

void setup(){ 
  Serial.begin(9600);

  pinMode(IRS_1, INPUT);
  pinMode(IRS_4, INPUT);
  pinMode(IRS_5, INPUT);
  pinMode(SWITCH, INPUT);
  pinMode(IRS_Front, INPUT);
 }
 
void loop() {
  S1 = digitalRead(IRS_1);
  S2 = digitalRead(IRS_2);
  S3 = digitalRead(IRS_3);
  S4 = digitalRead(IRS_4);
  S5 = digitalRead(IRS_5);
  S6 = digitalRead(SWITCH);
  S7 = digitalRead(IRS_Front);


  Serial.println("S1\tS2\tS3\tS4\tS5\tS6\tS7");
  sprintf(strBuf, "%d\t%d\t%d\t%d\t%d\t%d\t%d", S1, S2, S3, S4, S5, S6, S7);
  Serial.println(strBuf);

  
  delay(50);

}