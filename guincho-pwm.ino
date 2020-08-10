 
int porta_rele1 = 5;
int porta_rx = 6;
int inc =0;
int valor_pwm;
char buz = 9;
char* musica[] = {"La","Re","Fa","Sol","La","Re", "Fa", "Sol", "Mi", "Pausa", "Sol", "Do", "Fa", "Mi", "Sol", "Do", "Fa", "Mi", "Re", "Fim"}; //Game of Thrones
int duracao[] = {700, 500, 300, 250, 250, 300, 200, 200, 700, 200, 500, 500, 200, 200, 200, 500, 200, 200, 500};


void setup()
{
  //Define pinos para o rele como saida
pinMode(porta_rele1, OUTPUT);  
pinMode(buz, OUTPUT); 
digitalWrite(porta_rele1, HIGH);
tocar(musica,duracao);
}
   
void loop()
{
  valor_pwm = pulseIn(porta_rx,HIGH);

  if (valor_pwm > 1500){

  if (inc == 0){
    

    digitalWrite(porta_rele1, LOW);  //Liga rele 1
    inc =1;
  }
  }else{
    inc =0;
   digitalWrite(porta_rele1, HIGH); //Desliga rele 1
    }
//
//  delay(2000);
//  digitalWrite(porta_rele1, HIGH); //Desliga rele 1
//  delay(2000);
}
void tocar(char* mus[], int tempo[]){
  int tom = 0;
  for(int i = 0; mus[i]!="Fim";i++){
    if(mus[i] == "Do") tom = 262;
    if(mus[i] == "Re") tom = 294;
    if(mus[i] == "Mi") tom = 330;
    if(mus[i] == "Fa") tom = 349;
    if(mus[i] == "Sol") tom = 392;
    if(mus[i] == "La") tom = 440;
    if(mus[i] == "Si") tom = 494;
    if(mus[i] == "Do#") tom = 528;
    if(mus[i] == "Re#") tom = 622;
    if(mus[i] == "Fa#") tom = 370;
    if(mus[i] == "Sol#") tom = 415;
    if(mus[i] == "La#") tom = 466;
    if(mus[i] == "Pausa") tom = 0;
    tone(buz, tom, tempo[i]);
    delay(tempo[i]);
  }
}
