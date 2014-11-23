char* replyOK = {
  "OK\n"};

#define MAX_COMMAND_LENGTH 255
char resetByte = '!';
char stopByte = '#';

char* commandLEDOn = {
  "LEDON"};
char* commandLEDOff = {
  "LEDOFF"};

int incomingByte = 0;
int charCount = 0;
char command[MAX_COMMAND_LENGTH + 1]; // leave space for \0
bool locked = false;
int led = 13;
int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    incomingByte = Serial.read();

    if ((char)incomingByte == resetByte) {
      locked = false;
      charCount = 0;
      return;
    }

    if (locked) {
      Serial.println("@");
      return;
    }

    if ((char)incomingByte != stopByte) {
      if (charCount > MAX_COMMAND_LENGTH - 1) {
        Serial.println("@");
        locked = true;
        return;
      }
      else {
        command[charCount] = (char)incomingByte;
        charCount++;
      }
    }
    else {
      command[charCount] = '\0';
      charCount = 0;
      displayLights(command);
      if (strcmp(commandLEDOn, command) == 0) {
        digitalWrite(led, HIGH);
        Serial.println(replyOK);
      }
      else if (strcmp(commandLEDOff, command) == 0) {
        digitalWrite(led, LOW);
        Serial.println(replyOK);
      }
    }
  }
}

void displayLights(String commad){
//  if(command.length() < 2){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);

    if(command[0]== 'r' || command[1] == 'r'){
      digitalWrite(led1, HIGH);
    }
    if(command[0]== 'l' || command[1] == 'l'){
      digitalWrite(led4, HIGH);
    }
    if(command[0]== 'f' || command[1] == 'f'){
      digitalWrite(led2, HIGH);
    }
    if(command[0]== 'b' || command[1] == 'b'){
      digitalWrite(led3, HIGH);
    }


 // }


}

