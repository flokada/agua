// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void mostraHora();
void relogio();
void timer();
void seriall();

//Variaveis para a base de tempo:
float lastMillis;
unsigned long currentMilliss = millis();
float currentMillis = currentMilliss;
float milliDiff = currentMillis - lastMillis;
float milli;

int segundo = 55, minuto = 59, hora = 22, dia = 3; //Hora inicial

int setsegundo1 = 0, setminuto1 = 1, sethora1 = 23; //hora do alarme on
int duracao1 = 1; //duracao da ativacao 
int setoffsegundo1 = 0; //segundo do alarme off
int setoffminuto1 = (setminuto1 + duracao1); //minuto do alarme off
int setoffhora1 = 23; //hora do alarme off

int setsegundo2 = 0, setminuto2 = 2, sethora2 = 23; //hora do alarme on
int duracao2 = 1; //duracao da ativacao 
int setoffsegundo2 = 0; //segundo do alarme off
int setoffminuto2 = (setminuto2 + duracao2); //minuto do alarme off
int setoffhora2 = 23; //hora do alarme off

int setsegundo3 = 0, setminuto3 = 4, sethora3 = 23; //hora do alarme on
int duracao3 = 1; //duracao da ativacao 
int setoffsegundo3 = 0; //segundo do alarme off
int setoffminuto3 = (setminuto3 + duracao3); //minuto do alarme off
int setoffhora3 = 23; //hora do alarme off

int segnov, segvel; //Verificacao do segundo para imprimir somente quando a variavel segundo mudar
int fase = 0; //Contador da fase


void setup() {
  pinMode(13, OUTPUT); //Saida do LED 13
  pinMode(12, OUTPUT); //Saida do rele 1
  pinMode(11, OUTPUT); //Saida do rele 2
  pinMode(3, OUTPUT);  //Saida do rele 3
  lcd.begin(16, 2);
  analogWrite (10, 25); //Brilho do LCD de 0 a 255
  lcd.setCursor(0,0);
  lcd.print("Jardim Aut V1.00");
  delay(5000);
}

void loop() {
  
  mostraHora();
  relogio();
  timer();
}
  
void relogio()
{
  currentMillis = millis();
  milliDiff = currentMillis - lastMillis;

  if(milliDiff<0)
  {
    milliDiff = 500;
  }
  
  lastMillis = currentMillis;
  milli += (milliDiff*1.000261660673); //Fator de correcao do tempo
  Serial.println(milli);

    while (milli >= 1000)
  {
    milli -= 1000;
    segundo++;
    digitalWrite(13, !digitalRead(13)); //Inverte o estado do LED 13 a cada segundo
  }
  
  while (segundo >= 60)
  {
     segundo-=60;
     minuto++;
  }
  
  while (minuto >= 60)
  {
    minuto -= 60;
    hora++;
  }
  
  while (hora >= 24)
  {
     hora -= 24;
     dia++;
  }
  while (dia >= 6)
  {
     dia -= 6;
  }
}

  
  void mostraHora()
  {
    segnov = segundo;
    if(segnov != segvel)
    {
    if(fase == 0){
  
    lcd.clear();
    
    lcd.setCursor(2,0);
    if(dia==0)
    {
      lcd.print("Segunda-feira");
    }
    if(dia==1)
    {
      lcd.print("Terca-feira");
    }
    if(dia==2)
    {
      lcd.print("Quarta-feira");
    }
    if(dia==3)
    {
      lcd.print("Quinta-feira");
    }
    if(dia==4)
    {
      lcd.print("Sexta-feira");
    }
    if(dia==5)
    {
      lcd.setCursor(5,0);
      lcd.print("Sabado");
    }
    if(dia==6)
    {
      lcd.setCursor(4,0);
      lcd.print("Domingo");
    }
    }

    if(fase != 0){
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Fase ");
      lcd.print(fase);
      lcd.print(" Ligada");
    }
    
    lcd.setCursor(4,1);  
    if(hora<10){
      lcd.print("0");
      lcd.print(hora);}
      else
      {
        lcd.print(hora);
    }
    lcd.print(":");
    if(minuto<10){
      lcd.print("0");
      lcd.print(minuto);}
      else
      {
        lcd.print(minuto);
    }
    lcd.print(":");
    if(segundo<10){
      lcd.print("0");
      lcd.print(segundo);}
      else
      {
        lcd.print(segundo);
      }
      segvel = segnov;
  }
  }

  void timer()
  {
    if(segundo == setsegundo1)
    {if(minuto == setminuto1)
    {if(hora == sethora1)
    {fase = 1;
    digitalWrite(12, HIGH);
    }
    }
    }
    if(segundo == setoffsegundo1)
    {if(minuto == setoffminuto1)
    {if(hora == setoffhora1)
    {fase = 0;
    digitalWrite(12, LOW);
    }
    }
    }
    if(segundo == setsegundo2)
    {if(minuto == setminuto2)
    {if(hora == sethora2)
    {fase = 2;
    digitalWrite(11, HIGH);
    }
    }
    }
    if(segundo == setoffsegundo2)
    {if(minuto == setoffminuto2)
    {if(hora == setoffhora2)
    {fase = 0;
    digitalWrite(11, LOW);
    }
    }
    }
    if(segundo == setsegundo3)
    {if(minuto == setminuto3)
    {if(hora == sethora3)
    {fase = 3;
    digitalWrite(3, HIGH);
    }
    }
    }
    if(segundo == setoffsegundo3)
    {if(minuto == setoffminuto3)
    {if(hora == setoffhora3)
    {fase = 0;
    digitalWrite(3, LOW);
    }
    }
    }
  }
 
