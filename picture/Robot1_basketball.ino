#include <Servo.h>

void avant();
double moteurG_av;
double vitesse;
double moteurG_ar;
double moteurD_av;
double moteurD_ar;
void lire_capteur();
double Val_Cap_D;
double Cap_D;
double Val_Cap_G;
double Cap_G;
double Val_Lum_G;
double Cap_Lum_G;
double Val_Lum_D;
double Cap_Lum_D;
void droite_2();
void droite();
void Arreter();
void gauche();
void Suiveur();
double Val_init;
double Compteur;
double V_init_LDR_G;
double V_init_LDR_D;
Servo servo_9;


void avant()
{
    analogWrite(moteurG_av,vitesse);
    
    analogWrite(moteurG_ar,0);
    
    analogWrite(moteurD_av,vitesse);
    
    analogWrite(moteurD_ar,0);
    
}

void lire_capteur()
{
    Val_Cap_D = analogRead(A0+Cap_D);
    
    Val_Cap_G = analogRead(A0+Cap_G);
    
    Val_Lum_G = analogRead(A0+Cap_Lum_G);
    
    Val_Lum_D = analogRead(A0+Cap_Lum_D);
    
}

void droite_2()
{
    analogWrite(moteurG_av,vitesse);
    
    analogWrite(moteurG_ar,0);
    
    analogWrite(moteurD_av,0);
    
    analogWrite(moteurD_ar,0);
    
}

void droite()
{
    analogWrite(moteurG_av,vitesse);
    
    analogWrite(moteurG_ar,0);
    
    analogWrite(moteurD_av,0);
    
    analogWrite(moteurD_ar,0);
    
}

void Arreter()
{
    analogWrite(moteurG_av,0);
    
    analogWrite(moteurG_ar,0);
    
    analogWrite(moteurD_av,0);
    
    analogWrite(moteurD_ar,0);
    
}

void gauche()
{
    analogWrite(moteurG_av,0);
    
    analogWrite(moteurG_ar,0);
    
    analogWrite(moteurD_av,vitesse);
    
    analogWrite(moteurD_ar,0);
    
}

void Suiveur()
{
    lire_capteur();
    
    if(((Val_Cap_D) < ((Val_init) + (10))) && ((Val_Cap_G) < ((Val_init) + (10)))){
        avant();
    }
    
    if(((Val_Cap_D) > ((Val_init) + (10))) && ((Val_Cap_G) < ((Val_init) + (10)))){
        droite();
    }
    
    if(((Val_Cap_D) < ((Val_init) + (10))) && ((Val_Cap_G) > ((Val_init) + (10)))){
        gauche();
    }
    
}


void setup(){
    vitesse = 130;
    moteurG_av = 3;
    moteurG_ar = 11;
    moteurD_av = 5;
    moteurD_ar = 6;
    Cap_D = 1;
    Cap_G = 0;
    Cap_Lum_G = 2;
    Cap_Lum_D = 3;
    Compteur = 0;
  
    pinMode(moteurG_av,OUTPUT);
    pinMode(moteurG_ar,OUTPUT);
    pinMode(moteurD_av,OUTPUT);
    pinMode(moteurD_ar,OUTPUT);
    pinMode(A0+Cap_D,INPUT);
    pinMode(A0+Cap_G,INPUT);
    pinMode(A0+Cap_Lum_G,INPUT);
    pinMode(A0+Cap_Lum_D,INPUT);
    servo_9.attach(9); // init pin
    servo_9.write(0); // write to servo
    Val_init = analogRead(A0+Cap_G);
    delay(15000);
    lire_capteur();
    while(!(((Val_Cap_D) > ((Val_init) + (10))) && ((Val_Cap_G) > ((Val_init) + (10)))))
    {
       
        Suiveur();
    }
    Arreter();
    for(int i=0;i<10;++i)
    {
        V_init_LDR_G = analogRead(A0+Cap_Lum_G);
        V_init_LDR_D = analogRead(A0+Cap_Lum_D);
    }
    lire_capteur();
    while(!(((Val_Lum_D) > ((V_init_LDR_D) + (50))) || ((Val_Lum_G) > ((V_init_LDR_G) + (50)))))
    {
 
        lire_capteur();
    }
    if((Val_Lum_G) > ((V_init_LDR_G) + (50))){
        gauche();
        delay(1000);
        lire_capteur();
        while(!((Val_Cap_G) > ((Val_init) + (10))))
        {
            lire_capteur();
            gauche();
        }
    }else{
        if((Val_Lum_D) > ((V_init_LDR_D) + (50))){
            droite();
            delay(1000);
            lire_capteur();
            while(!((Val_Cap_D) > ((Val_init) + (10))))
            {
                droite();
                lire_capteur();
            }
        }
    }
    lire_capteur();
    while(!(((Val_Cap_D) > ((Val_init) + (10))) && ((Val_Cap_G) > ((Val_init) + (10)))))
    {

        Suiveur();
    }
    Arreter();
    delay(3000);
    servo_9.write(90); // write to servo
    delay(1000);
    servo_9.write(0); // write to servo
    
}

void loop(){
    
    
  
}
