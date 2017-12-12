#define palavra(b13, b12, b11, b10, b9, b8, b7, b6, b5, b4, b3, b2, b1)\
digitalWrite(13, b13);\
digitalWrite(12, b12);\
digitalWrite(11, b11);\
digitalWrite(10, b10);\
digitalWrite(9, b9);\
digitalWrite(8, b8);\
digitalWrite(7, b7);\
digitalWrite(6, b6);\
digitalWrite(5, b5);\
digitalWrite(4, b4);\
digitalWrite(3, b3);\
digitalWrite(2, b2);\
digitalWrite(A5, b1)

void setup()
{
	Serial.begin(9600);
	pinMode(A5, OUTPUT), digitalWrite(A5, 0); pinMode(A0, INPUT);
	for(int i = 2; i <= 13; ++i) pinMode(i, OUTPUT), digitalWrite(i, 0);

	palavra(0,0,0,0,0,0,1,0,1,0,1,0,1);
	while(digitalRead(A0) == 1){ Serial.print("Instrução 1 \n"); }
	delay(1500);

	palavra(0,0,0,0,0,0,1,1,0,1,0,0,1);
	while(digitalRead(A0) == 1){ Serial.print("Instrução 2 \n"); }
	delay(1500);

	palavra(0,1,1,0,0,1,0,1,1,0,1,1,0);
	while(digitalRead(A0) == 1){ Serial.print("Instrução 3 \n"); }
	delay(1500);

	palavra(0,0,0,0,0,0,1,0,0,0,1,0,0);
	while(digitalRead(A0) == 1){ Serial.print("Instrução 4 \n"); }
	delay(1500);

	palavra(0,0,0,0,0,0,1,1,0,0,0,0,1);
	while(digitalRead(A0) == 1){ Serial.print("Instrução 5 \n"); }
	delay(1500);

	palavra(0,0,0,1,1,0,0,0,1,0,0,1,0);
	while(digitalRead(A0) == 1){ Serial.print("Instrução 6 \n"); }
	delay(1500);

	palavra(0,0,1,0,1,1,0,0,0,1,1,0,1);
	while(digitalRead(A0) == 1){ Serial.print("Instrução 7 \n"); }
	delay(1500);

	Serial.print("Fim");
}
void loop(){}
