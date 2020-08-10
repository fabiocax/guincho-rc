#define channumber 8
#define filter 10
int channel[channumber];
int lastReadChannel[channumber];
int conta = 0;
int portReceiver = 6;

int porta_rele1 = 5;
int inc = 0;
char buz = 9;
char* musica[] = {"La", "Re", "Fa", "Sol", "La", "Re", "Fa", "Sol", "Mi", "Pausa", "Sol", "Do", "Fa", "Mi", "Sol", "Do", "Fa", "Mi", "Re", "Fim"}; //Game of Thrones
int duracao[] = {700, 500, 300, 250, 250, 300, 200, 200, 700, 200, 500, 500, 200, 200, 200, 500, 200, 200, 500};



void setup() {
  Serial.begin(9600);
  pinMode(portReceiver, INPUT);
  pinMode(porta_rele1, OUTPUT);
  pinMode(buz, OUTPUT);
  digitalWrite(porta_rele1, HIGH);
  tocar(musica, duracao);
}

void loop() {

  if (pulseIn(portReceiver, HIGH) > 3000) {
    for (int i = 0; i <= channumber - 1; i++) {
      channel[i] = pulseIn(portReceiver, HIGH);
    }
    for (int i = 0; i <= channumber - 1; i++) {
      if ((channel[i] > 2000) || (channel[i] < 100)) {
        channel[i] = lastReadChannel[i];
      } else {
        channel[i] = (lastReadChannel[i] + channel[i]) / 2;
        conta++;
      }
    }

  }
  if (conta > filter) {
    for (int i = 0; i <= channumber - 1; i++) {
      if (i + 1 == 6){
        Serial.print("CH");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(channel[i]);
        lastReadChannel[i] = channel[i];
      }
    }
    if (channel[5] > 1000){
      //digitalWrite(13, HIGH);
      digitalWrite(porta_rele1, LOW);  //Liga rele 1
      
    }else{
      //digitalWrite(13, LOW);
      digitalWrite(porta_rele1, HIGH); //Desliga rele 1
    }
    delay(400);
    conta = 0;
  }
}


void tocar(char* mus[], int tempo[]) {
  int tom = 0;
  for (int i = 0; mus[i] != "Fim"; i++) {
    if (mus[i] == "Do") tom = 262;
    if (mus[i] == "Re") tom = 294;
    if (mus[i] == "Mi") tom = 330;
    if (mus[i] == "Fa") tom = 349;
    if (mus[i] == "Sol") tom = 392;
    if (mus[i] == "La") tom = 440;
    if (mus[i] == "Si") tom = 494;
    if (mus[i] == "Do#") tom = 528;
    if (mus[i] == "Re#") tom = 622;
    if (mus[i] == "Fa#") tom = 370;
    if (mus[i] == "Sol#") tom = 415;
    if (mus[i] == "La#") tom = 466;
    if (mus[i] == "Pausa") tom = 0;
    tone(buz, tom, tempo[i]);
    delay(tempo[i]);
  }
}
