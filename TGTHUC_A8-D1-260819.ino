#include <Wire.h> 
 #include <TimerOne.h>
#include <avr/interrupt.h>
#include <Arduino.h>
#include <SoftwareSerial.h> 
//#include "henthutatmo.h"
#include "caigiomotat.h"
//#include "caigiothuc.h"
#include "hamghihai.h"
#include <EEPROM.h>
/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 8;
 //const byte NumberOfFields = 7;
/* khai báo các biến thời gian */
//int second, minute, hour, day, month, year;
//unsigned long second, minute, hour, day, month, year,date;
unsigned long wday=1,thuhen=1;//
//unsigned long wday=0,thuhen=0;
//THEM TU HIEN THI LCD QUA
// include the library code:
//#include <LiquidCrystal.h>
#define m(k) digitalWrite(k,LOW);
#define t(k) digitalWrite(k,HIGH);
#define m(led9) digitalWrite(led9,LOW);
#define t(led9) digitalWrite(led9,HIGH);
//#define t(hour==giomo3&&minute==phutmo3&&second==20) tgian3
//#define t(hour==giomo4&&minute==phutmo4&&second==20) tgian4
// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define den13 11//3//11 // mo tat khi dung ma cai san 4 chan 13 la mode cu chan 11 la mode moi
#define den9 9  // mo tat theo gio phut thu 3
#define den8 8 // mo tat theo gio phut thu 2 
#define den6 6 //  mo tat bluetooth 0
#define den10 10 // den 5
#define den2 2 // bao co wifi a2
#define den3 3 // bao co wifi a1
#define den7 7 // sang man hinh
char state,datad,datae,mang,mangb;
char datab[7];
unsigned char y = 0;//cua da ta l
//char datap[3];
unsigned char l = 0;//cua da ta p
unsigned char i = 0;
int cphtden22=0,cphtden23=0,cphtden24=0,cphtden25=0,cpmoden2=0,cphtden32=0,cphtden33=0,cphtden42=0;
int demxoa=0,cptatden10=0,cptatden103=0,cptatden102=0,cpghingay=0;
unsigned long  gtgoc2=10000001,hienthihen=0,giayghingay=0;//mahienthi=0,
int thu=0,loai=0,dvdm=0,cptatden2=0,cphtthu=0;
int  dvjk=0,hclm=0,dvlm=0,hcnp=0,dvnp=0,dienapa0=1000,dienapa1=1000,dienapa2=1000,dad2=0,dad3=0,dad4=0,dad6=0,dad7=0;
 int b,cm=0,tamp3=0,hcdemghi=0;//,demghidoc=0;
 unsigned long gio=22,phut=55,giay=0,ngay=0,thang=0,nam=0,tgtatden4=0,gmden2=0,gmden3=0,gmden4=0;
 int address = 0,hienthi=0;
int a = 0,cpghi=0,cpdoc=0,chomo2=0,chomo3=0,chomo4=0;//,cphtthu=0;
int value = 0;
int addr = 0;//địa chỉ EEPROM mà ta sẽ lưu đầu tiên
int kieu=1,henden4=1,chomoden2=0,chomoden3=0,chomoden4=0;
//int i=0;
unsigned long giays=0,giaychop=0,xungthemden2=0,xungthemden3=0,xungthemden4=0;
unsigned long biencai=0,giatridoc2=10000002,gthienthi=0,gtgoc=11222222,giatritucthi=10000001;
//unsigned long giaymo2;
int x = 0, k = 0;
unsigned long giayghi=0,ttghen23=0,ttghen33=0,ttghen43=0,tghenden22=0,tghenden32=0,tghenden42=0;//tg sau khi them bot boi hesox
int  n = 1, h = 0,s=1,doclanhai=0;
int bienm=0,chopden=0;
int tamp,m=2;
unsigned long tgbdcbn = 0,tamp2=0,gden2 = 0,gden3 = 0,gden4 = 0,ttghen2=0,ttghen3=0,ttghen4=0,tghenden2=0,tghenden3=0,tghenden4=0,dcghi10=0;
//unsigned  x12 = 1, x13 = 1,dcghi10=0;
void ketnoiwifiavg()
{    if(dienapa1<200)
        {giaya1=0;delay(5);
        }
     if(dienapa2<200)
        {giaya2=0;delay(5);
        }
     if(giaya1==20||giaya1==30||giaya1==40||giaya1==50)
        {chomoden2=1;
        }
      if(giaya1==22||giaya1==32||giaya1==42||giaya1==52)
        {chomoden2=0;
        }
       if(giaya2==20||giaya2==30||giaya2==40||giaya2==50)
        {chomoden2=1;
        }
      if(giaya2==22||giaya2==32||giaya2==42||giaya2==52||giaya1<5&&giaya2<5)
        {chomoden2=0;
        }
      if(chomoden2==1)
        {m(den2);delay(5);
        }
      if(chomoden2==0)
        {t(den2);delay(5);
        }
  }
void setup()
{  pinMode(den13,OUTPUT);// mo tat theo gio trong 24 gio
   pinMode(den9,OUTPUT);//mo tat theo hen gio thu
   pinMode(den8,OUTPUT);//mo tat theo hen gio thu
   pinMode(den6,OUTPUT);//den mo tat bluetooth
   pinMode(den10,OUTPUT);// den cong chinh co mat khau hv2,hv3...
   pinMode(den7,OUTPUT);// mo tat man hinh lcd
    pinMode(den2,OUTPUT);//
   pinMode(den3,OUTPUT);//
   digitalWrite(den13,HIGH);
   digitalWrite(den9,HIGH);
   digitalWrite(den8,HIGH);
   digitalWrite(den6,HIGH);
   digitalWrite(den10,HIGH);
   digitalWrite(den7,HIGH);
 digitalWrite(den2,HIGH);
 digitalWrite(den3,HIGH);
  Wire.begin();
     /* cài đặt thời gian cho module */  
     //setTime(gio, phut, giay, thu, ngay, thang, nam); // 12:30:45 CN 08-02-2015
  Serial.begin(9600); 
     // set up the LCD's number of columns and rows:
  //lcd.begin(16, 2);//khai bao lcd 16 cot(tu 0 den 15) 2 hang(tu 0 den 1)  
    //  lcd.print("T");//in chu nay len man // Print a message to the LCD. 
}
 // CAC HAM DOC LAP

 // HET CAC HAM DOC LAP
void loop()
{ dienapa0 = analogRead(A0);//cai ma bao mat
dienapa1 = analogRead(A1);
dienapa2 = analogRead(A2);
dad2=digitalRead(den8);
dad3=digitalRead(den9);
dad4=digitalRead(den13);
dad6=digitalRead(den6);
dad7=digitalRead(den7);
  tamp2=millis() - tgbdcbn;
 ketnoiwifiavg(); caimo(); caimadoc();docthu();xoagiatridoc();docden22();caihengio();
  /* Đọc dữ liệu của DS1307 */
  readDS1307();
  /* Hiển thị thời gian ra Serial monitor */
  digitalClockDisplay();
  delay(1000);  
  //lcd.print(millis() / 1000);//khoi tao giay chay thoi gian gan bang 1 giay    
  if(giaym==2)
      {
           bienk=1;
      }
    if(giaym==22)//bat dau hien thi thoi gian thuc len lcd
      {
           bienk=2;
      }
    if(giaym==60)
       {bienk=3;   //dvd=0;chucd=0;tramd=0;nghind=0;cnghind=0;tnghind=0;        
       }
    if(bienk==2)//giay m =24
    {  
       dcghidoc=0;
       hcdemghi=0;
       dvl=2;chucl=0;traml=0;nghinl=0;cnghinl=0;tnghinl=0;dcghi=0;ctrieul=0;trieul=0;
         
      }
      
 //HIEN THI LEN LCD THEO GIAY M **************  
  
          if(giaym==42)
         {   
          cphtden22=0,cphtden23=0,cphtden24=0,cphtden25=0,cphtden32=0,cphtden33=0,cphtden42=0;  //hien thi gia tri goc len lcd(ban daula 222222)
         }
 
     if(gio==23&&phut==59)
     {if(thu!=8)
     {thu++;
      }
      else
      {thu=1;
        }
      }
  
  
thuhen=day;
 if(giaym==50||giaym==80)
 {m(den7);m(den6);// tat bltooth
  }
 if(giaym==1||giaym==53||giaym==82)//mo lai blt ngay sau tat
 {t(den7);t(den6);//mo bluetooth
  }
 gio=hour;phut=minute;giay=second;
 if(bthu21==thuhen||bthu22==thuhen||bthu23==thuhen||bthu24==thuhen||bthu25==thuhen||bthu26==thuhen||bthu27==thuhen)
    {
    cpmoden2=1;delay(2);
    }
   if(cpmoden2==1&&chomoden2==0&&second>giaymo2&&second<giaytat2)
      { 
       if(hour==giomo2&&minute==phutmo2||hour==giomo22&&minute==phutmo22||hour==giomo24&&minute==phutmo24||hour==giomo25&&minute==phutmo25)//||bthu28==th
       {   
        m(den8);delay(2);  
       }  
     }
     /*
      * int chuc = temp3/10;
int donvi = temp3%10;
int tram = temp3%100;
      * 
      */
      
  //tinh so xung tang them cho moi den aaaaaaaaaaaaaaaaaa
xungthemden2=xmp*phuthen2/hesox;
xungthemden3=xmp*phuthen3/hesox;
xungthemden4=xmp*phuthen4/hesox;
  //tinh so xung tang them cho moi den bbbbbbbbbbbbbbbbbb
 
  tghenden22=phuthen2*xmp+xungthemden2; 
  tghenden32=phuthen3*xmp+xungthemden3; 
  tghenden42=xmp*phuthen4+xungthemden4;
      if(bientat21==thuhen||bientat22==thuhen||bientat23==thuhen||bientat24==thuhen||bientat25==thuhen||bientat26==thuhen||bientat27==thuhen)
        {cptatden2=1;
        }
        //den 22
     if(tghenden22>5&&gden2==tghenden22&&chomoden2==1)//tu dong tat do mo truc tiep bang lenh m2,m3,m4
       {t(den8);delay(2);gmden2=0;giotat2=hour;phuttat2=minute;//t(den8);delay(2);
       }
     if(tghenden32>5&&gden3==tghenden32&&chomoden3==1)//tu dong tat do mo truc tiep bang lenh m2,m3,m4
       {t(den9);delay(2);gmden3=0;giotat3=hour;phuttat3=minute;//t(den9);delay(2);
       }
     if(tghenden42>5&&gden4==tghenden42&&chomoden4==1)//tu dong tat do mo truc tiep bang lenh m2,m3,m4
       {t(den13);delay(2);gmden4=0;giotat4=hour;phuttat4=minute;//t(den13);
       }
           if(gmden2==3)
           { chomoden2=0;           
           }
           if(gmden3==3)
           { chomoden3=0;           
           }
            if(gmden4==3)
           { chomoden4=0;          
           }
    //
if(chomoden2==0&&cptatden2==1&&second>giaymo2&&second<giaytat2)
 {
   if(hour==giotat2&&minute==phuttat2)
     {       
        t(den8);delay(2);
        if(laplai==1)
       {
           giomo2=25;giotat2=26;
       }
     }
    //het den 22
    if(hour==giotat22&&minute==phuttat22)
       {     
        t(den8);delay(2);
          if(laplai==1)
            {
             giomo22=25;giotat22=26;
            }   
        } 
    if(hour==giotat24&&minute==phuttat24)
           {       
             t(den8);delay(2);
             if(laplai==1)
               {
                giomo24=25;giotat24=26;
               }  
          }  
       if(hour==giotat25&&minute==phuttat25)
            {       
               t(den8);delay(2);
              if(laplai==1)
                {
                 giomo25=25;giotat25=26;
                }  
            } 
       }      
  if(hour==giomo3&&minute==phutmo3&&second>giaymo3&&second<giaytat3&&chomoden3==0||hour==giomo33&&minute==phutmo33&&second>giaymo3&&second<giaytat3&&chomoden3==0)
    {  m(den9);delay(2);
       if(laplai==1)
             {
              giomo3=25;giotat3=25;
              
             }    
    }  
  if(hour==giotat3&&minute==phuttat3&&second>giaymo3&&second<giaytat3&&chomoden3==0||hour==giotat33&&minute==phuttat33&&second>giaymo3&&second<giaytat3&&chomoden3==0)
     {t(den9);delay(2);
          if(laplai==1)
             {
             // giomo3=25;giotat3=25;//phuttat3=61;phutmo3=0;
              giomo33=25;giotat33=26;//phuttat33=63;phutmo33=62; 
             }    
      }        
   if(hour==giomo4&&minute==phutmo4&&second>giaymo3&&chomoden4==0)
    { m(den13);delay(2);
     
    }    
  if(hour==giotat4&&minute==phuttat4&&second>giaymo3&&chomoden4==0)
     {t(den13);delay(2);     
         if(laplai==1)
             {
              giomo4=25;giotat4=25;
             }  
     }   
         
  if(giayghi==3||giayghi==992&&cpdoc==4)
         {dcghidoc=2;delay(5); //lay gia tri trong hv2 lam gia tri goc de so sanh
             if(dcghidoc==2)
               {   doc();delay(5);//giayghi=994;
                   giatridoc2=ctrieul*10000000+trieul*1000000+tnghinl*100000+cnghinl*10000+nghinl*1000+traml*100+chucl*10+dvl;
                   gtgoc2=giatridoc2; 
                   //cpdoc=0;
               }               
         }
                    
         if(giayghi==991||giayghi==996)
          {
            doc();delay(5);           
          }  
       if(dcghidoc==2&&giatrinhap==gtgoc2&&gtgoc2>10000001||dienapa0<500)               
             {biencai=9;
             }                   
        if(giayghi==5||giayghi==992&&cpdoc==1)
          {dcghidoc=160;delay(5); //thu mo den 2
           
            doc();delay(5);
          
          }           
            if(giayghi==7||giayghi==992&&cpdoc==2)
           {dcghidoc=162;delay(5); //thu tat den 2           
              doc();delay(5);           
           }
          if(giayghi==9||giayghi==992&&cpdoc==3)
          {dcghidoc=163;delay(5);          
            doc();delay(5);           
          }            
          if(giayghi==11||giayghi==992&&cpdoc==5)
          {dcghidoc=165;delay(5);           
            doc();delay(5);          
          }
          if(giayghi==13||giayghi==992&&cpdoc==6)//
          {dcghidoc=166;delay(5);            
            doc();delay(5);         
          }
          if(giayghi==15||giayghi==992&&cpdoc==7)//
          {dcghidoc=167;delay(5);          
            doc();delay(5);         
          }
          if(giayghi==17||giayghi==992&&cpdoc==8)//
          { dcghidoc=168;delay(5);           
                doc();delay(5);             
          }
           if(giayghi==19||giayghi==992&&cpdoc==9)//xung mot phut
          { dcghidoc=169;delay(5);             
                doc();delay(5);           
          }
          if(giayghi==21||giayghi==992&&cpdoc==12)//xung mot phut
          { dcghidoc=82;delay(5);             
                doc();delay(5);          
          }
           if(giayghi==23||giayghi==992&&cpdoc==13)//xung mot phut
          { dcghidoc=83;delay(5);             
                doc();delay(5);           
          }
           if(giayghi==25||giayghi==992&&cpdoc==14)//xung mot phut
          { dcghidoc=84;delay(5);             
                doc();delay(5);           
          }
           if(giayghi==27||giayghi==992&&cpdoc==15)//xung mot phut
          { dcghidoc=85;delay(5);             
                doc();delay(5);            
          }
           if(giayghi==29||giayghi==992&&cpdoc==19)//xung mot phut
          { dcghidoc=89;delay(5);             
                doc();delay(5);           
          }
          if(giayghi==993)//xung mot phut
          { dcghidoc=3;delay(5);             
                ghi();delay(5);giayghi=994;            
          }
         if(giaym==20||giaym==55)//thoi gian chuyen sang che do binh thuong
           {biencai=8;vitri=1;
           }
         
         dembit=Serial.available()  ; //dem so bit duoc goi di
         Serial.println(F("A8-D1-260819 DT:0823.822.811")); 
          if(hienthi==0)
          {
       Serial.println(F("*****HEN GIO MO TAT BANG SMARTPHONE*****")); 
       
          }
           Serial.print(F("giaya1+giaya2 :) :"));           
            Serial.println(giaya1);
            Serial.print(giaya2);
            Serial.print(F("Dien apa1+a2 :) :"));           
            Serial.println(dienapa1);
            Serial.println(dienapa2);
     if(hienthi==5)
          {  
            Serial.print(F("X.TANG.D2+XUNGHEN2 :) :"));           
           // Serial.print(2000+xungthemden2); 
           // Serial.print(300+xungthemden3); 
           // Serial.print(400+xungthemden4);  
            //Serial.print(5000+hesox);  
            //Serial.println(90000+tghenden22);         
           // Serial.print(F(" TG TANG-22:"));
             Serial.println(500000000+xungthemden2*100000+tghenden22); 
            // Serial.println(tghenden32);
            // Serial.println(tghenden42);     
           
            Serial.print(F("CPGHI+ XUNG1P(XMP.3.4)+HESOX:"));      
            Serial.println(70000000+chophepghi*10000000+1000*xmp+hesox);//xung mot phut
          }
            if(hienthi==2||hienthi==1||hienthi==0)
            {
            Serial.print(F("P.HEN(HX)2-3-4 :"));   
     Serial.print(phuthen2); 
     Serial.print(F(" : ")); 
     Serial.print(phuthen3); 
     Serial.print(F(": ")); 
     Serial.println(phuthen4);   
      Serial.print(F("THU T.T+S.LAPLAI(TM2-8):"));
             Serial.println(60000+thuhen*100+laplai);           
            }
             if(hienthi==0)
            { 
            Serial.print(F("BAO MO DEN 02-03-04  :")); 
            Serial.println(90000+chomoden2*100+10*chomoden3+chomoden4);          
            Serial.print(F("B D.AP DEN 02-03-04 :"));  
            Serial.println(5000000+dad7*10000+dad6*1000+dad2*100+dad3*10+dad4); 
          }
      if(cphtden22==1||hienthi==2)
          {
             Serial.print(F("DEN_20(D22) :"));    
             Serial.print(800000+1000*giomo2+phutmo2); 
             Serial.print(F(" : "));     
             Serial.println(800000+1000*giotat2+phuttat2);      
         }  
    if(cphtden23==1||hienthi==2)
          {
              Serial.print(F("DEN_23(D23) :"));    
              Serial.print(700000+1000*giomo22+phutmo22);  
              Serial.print(F(" : "));   
              Serial.println(700000+1000*giotat22+phuttat22);   
           }
       if(cphtden24==1||hienthi==2)
           {
              Serial.print(F("DEN_24 (D24):"));    
              Serial.print(400000+1000*giomo24+phutmo24);    
              Serial.print(F(" : "));   
              Serial.println(400000+1000*giotat24+phuttat24);
            }
       if(cphtden25==1||hienthi==2)
            {
              Serial.print(F("DEN_25 (D25):")); 
              Serial.print(500000+1000*giomo25+phutmo25);    
              Serial.print(F(" : "));   
              Serial.println(500000+1000*giotat25+phuttat25);   
    
             }
       if(cphtden32==1||hienthi==2)
            {     
              Serial.print(F("DEN_32(D32) :"));    
              Serial.print(300000+1000*giomo3+phutmo3);
              Serial.print(F(" : ")); 
              Serial.println(300000+1000*giotat3+phuttat3);  
            }
       if(cphtden33==1||hienthi==2)
           {       
             Serial.print(F("DEN_33(D33) :"));    
             Serial.print(300000+1000*giomo33+phutmo33); 
             Serial.print(F(" : "));  
             Serial.println(300000+1000*giotat33+phuttat33); 
          }
       if(cphtden42==1||hienthi==2)
          {   
            Serial.print(F("DEN_42(D42) :"));    
            Serial.print(400000+1000*giomo4+phutmo4);  
            Serial.print(F(" : ")); 
            Serial.println(400000+1000*giotat4+phuttat4);    
          }
          if(cphtthu==1||hienthi==3||hienthi==5)
          { Serial.print(F("CPT-MO-DEN2: "));
            Serial.print(7000+100*cpmoden2+cptatden2);
            Serial.print(F("THU MO 2(TM2): "));    
            Serial.print(thumo2);  
            Serial.print(F("THUTAT2(TT2): "));             
            Serial.println(tatthu2);          
          }     
    
          if(hienthi==5)
          {
             Serial.print(F("MO GIAY2(G23):"));   
             Serial.print(10000+giaymo2*100+giaytat2);
             //Serial.print(F("giay mo 3(G23p):"));    
             //Serial.println(10000+giaymo3*100+giaytat3);
             Serial.print(F("THU T.T+S.LAPLAI(TM2-8):"));
             Serial.println(60000+thuhen*100+laplai); 
          }
         // if(hienthi==5)
         // {   
     
    // }
//if(hienthi==4)
//{ 
      Serial.print(F(" GIAY GHI  : "));
      Serial.print(giayghi); 
      Serial.print(F(" : ")); 
      Serial.print(F(" GIAY_M : "));
      Serial.println(giaym);
      Serial.print(F(" GIO :  "));
      Serial.print(gio);  //chophepghi
      Serial.print(F(" : "));
      Serial.print(phut); 
      Serial.print(F(" : "));     
      Serial.println(giay);     
      //Serial.print(F(" VITRI: ")); 
     // Serial.println(900+vitri);     
//}
if(hienthi==1||hienthi==0)
{    Serial.print(F("C.GHI(XMP12)  :"));
     Serial.print(chophepghi);  //chophepghi
     Serial.print(F("   B.CAI :"));
     Serial.println(biencai);
     Serial.print(F("VI TRI NHAP (9X)  :"));  
     Serial.println(900+vitri);  
    /* switch(vitri) 
 {
  case 1: Serial.println(F(" 10000000:"));
          // hienthihen=phuthen2;
          break;   
 case 2: Serial.println(F(" 02000000:"));
          // hienthihen=phuthen3;
          break; 
 case 3: Serial.println(F(" 00300000:"));
          // hienthihen=phuthen4;
          break;     
 case 4: Serial.println(F(" 00040000:"));
           //hienthihen=thumo2;
          break;  
 case 5: Serial.println(F(" 00005000:"));
          // hienthihen=tatthu2;
          break; 
 case 6: Serial.println(F(" 00000600:"));          
          break;   
 case 7: Serial.println(F(" 00000070:"));          
          break; 
 case 8: Serial.println(F(" 00000008:"));          
          break;                         
         default:vitri=1;
          break; 
 } 
   */ 
     Serial.print(F(" G.TRI.NHAP (0-9):"));    
     Serial.println(500000000+giatrinhap);     
     Serial.print(F("G.TRI DOC(HV2=):"));  
     if(giatrinhap==giatridoc||biencai==9)
     {     
     Serial.println(400000000+giatridoc);     
     }  
     
        
}  
     Serial.print(F("  DCHI:  "));
     Serial.print(dcghidoc);  
     switch(dcghidoc) 
   {
  case 82: Serial.print(F(" HEN TAT DEN 2 :"));           
          break;   
 case 83: Serial.print(F("  HEN TAT DEN 3:"));           
          break; 
 case 84: Serial.print(F("  HEN TAT DEN 4:"));          
          break; 
 case 85: Serial.print(F("CP GHI(XMP12):"));           
          break;   
 //case 86: Serial.print(F("  HEN MT DEN 3:"));           
         // break; 
 case 87: Serial.print(F("  HEN MT DEN 25:"));           
          break; 
          
 case 89: Serial.print(F(" HEN MT DEN 24:"));          
          break;         
 case 160: Serial.print(F(" THU MO DEN 2:"));           
          break;  
 case 162: Serial.print(F("HEN MT DEN 23:"));           
          break; 
 case 163: Serial.print(F("THU TAT DEN 2:"));         
          break; 
 case 165: Serial.print(F(" HEN MT DEN 33:"));           
          break;  
 case 166: Serial.print(F("  HEN MT DEN 22:"));           
          break;  
 case 167: Serial.print(F("  HEN DEN 32:"));           
          break;  
case 168: Serial.print(F("  HEN MT DEN 42:"));           
          break; 
case 169: Serial.print(F("  HEN MT GIAY:"));           
          break; 
case 0: Serial.print(F("  KHONG LAM GI:"));           
          break;  
case 2: Serial.print(F(" BIEN CAI9:"));           
          break;                         
         default:dcghidoc=0;
          break; 
    }
       
//}
       Serial.print(F(" HIENTHI(h+t-) :"));
       Serial.println(hienthi);
     if(giaym==69||hienthi==3)
     {      
      Serial.println(F("gio:c+i-;phut:b+j-;thu:d+:"));
     }
  
    //HET PHAN DIEU KHIEN//HET PHAN DIEU KHIEN*************
   ///NHAN DU LIEU TU BLT AAAAAA
    if(Serial.available() > 6)
  {
    for(y = 0; y < 8; y++)
    {
      datab[y] = Serial.read();
    }
  }
  ///khong dung den nhieu xung nhu vay
if(Serial.available() > 4)//ba xung nhan
  {
    for(y = 0; y < 3; y++)
    {
      datal[y] = Serial.read();
      //giaym=0; 
    }
   }
  //221
  //dl=datap;
  if(Serial.available() > 3)//hai xung nhan
  {
    for(y = 0; y < 2; y++)
    {
      datap[y] = Serial.read();
      //giaym=0; 
    }   
  }
  //222        
     dcghi1=dcghi;dcghi2=dcghi+10;dcghi3=dcghi+20;dcghi4=dcghi+30;dcghi5=dcghi+40;dcghi6=dcghi+50;  
     //PHAN CAI DAT THOI GIAN CHO DONG HO THUC A
if (Serial.available() > 0)//mot xung nhan
  {
    state = Serial.read();  
    //giaym=0;  
  }
  else
  {
    state = 0;
  } 
  ////NHAN DU LIEU TU BLT BBBBB
  if(biencai==9)
  {  
  switch (state)
  {
    case 'a': giays=0;giaym=10;
       if (giay != 59)
        {  giay++;   delay(2);      
          second=giay;
           setTime( hour,minute,second , date,day, month, year);           
        }
      else
        { giay = 0;
        }
        //Serial.println(n);
        delay(3);
      break;
    case 'b':giays=0;giaym=10;
       if (phut != 59)
        {  phut++;       
           delay(2);
           minute=phut;
           setTime( hour,minute,second , day, month, year,date); 
           //setTime( gio,phut,giay, thu, ngay, thang, nam);  delay(2);
        }
      else
        { phut= 0;//minute=0;
        }
        //Serial.println(n);
        delay(3);
         break;
    case 'c': giays=0;giaym=10;
       if (gio != 23)
        {  gio++;           
           delay(2);
           hour=gio;
           setTime( hour,minute,second , day, month, year,date); 
          // setTime( gio,phut,giay, thu, ngay, thang, nam);  delay(2);
        }
      else
        { gio = 0;//hour=0;
        }
        //Serial.println(n);
        delay(1);
         break;
    case 'd': giays=0;giaym=10;
       if (thu != 8)
        {  thu++;  
        //date=thu;  
        day=thu;     
           delay(2);
           setTime( hour,minute,second ,date, day, month, year); 
           //setTime( gio,phut,giay, thu, ngay, thang, nam);  delay(2);
        }
      else
        { thu= 1;
        }
      //day=thu;  
        // setTime( hour,minute,second ,date, day, month, year);    
        //Serial.println(n);
        delay(1);
         break;
         /*
   case 'e':giays=0;giaym=10;
       if (ngay != 31)
        {  ngay++;  
        //day=ngay;     
           delay(2);
           setTime( hour,minute,second ,date, day, month, year); 
           //setTime( gio,phut,giay, thu, ngay, thang, nam);  delay(2);
        }
      else
        { ngay = 1;
        }
        //Serial.println(n);
        delay(1);
         break;
    case 'f':giays=0;
       if (thang != 12)
        {  thang++;        
           delay(2);
           month=thang;
           setTime( hour,minute,second ,date, day, month, year); 
           //setTime( gio,phut,giay, thu, ngay, thang, nam);  delay(2);
        }
      else
        { thang = 0;//month=0;
        }
        //Serial.println(n);
        delay(1);
         break;
    case 'g':giays=0;
       if (nam != 2222)
       //nam>2000;
        {  nam++;      
           delay(2);
          year=nam;
          setTime( hour,minute,second , day, month, year,date); //wday,
           //setTime( gio,phut,giay, thu, ngay, thang, nam); delay(2); 
        }
      else
        { nam = 20;//year=0;
        }
        //Serial.println(n);//dong 500
        delay(1);
         break;
       */
    case 'i':giaym=10;
    giays=0;
       if (gio != 0)
        {  gio--;           
           delay(2);
           hour=gio;
           setTime( hour,minute,second , day, month, year,date); 
          // setTime( gio,phut,giay, thu, ngay, thang, nam);  delay(2);
        }
      else
        { gio = 23;//hour=0;
        }
        //Serial.println(n);
        delay(1);         
        break;        
        case 'j':giays=0;giaym=10;
       if (phut != 0)
        {  phut--;       
           delay(2);
           minute=phut;
           setTime( hour,minute,second ,date, day, month, year); 
           //setTime( gio,phut,giay, thu, ngay, thang, nam);  delay(2);
        }
      else
        { phut= 59;//minute=0;
        }
        //Serial.println(n);
        delay(3);
         break;
        
   default:
        break;
  }
  }
 if(day==8)
 {day=1;delay(2);
 setTime( hour,minute,second ,date, day, month, year); 
  } 
 //thoi gian kien tao  A              
 if(tamp2>50)
 {  
  delay(1);
  tgbdcbn=millis();
  if(tgbdcbn==millis())
 { if(k!=9)
  {
    k++;
  } 
   else
   {k=0;
   } 
   //bat dau THOI GIAN DEN 1
 
 if(giaym!=99)
  { giaym++;
    delay(2);
  }
  else
  {   
    giaym=68;
  delay(1);
   }   
    if(giayghi!=1999)
  { giayghi++;
    delay(2);
  }
  else
  {   
    giayghi=1122;
  delay(1);
   }
   
if(giays!=30)
  { giays++;
    delay(1);
  }
  else
  {giays=7;
    delay(1);
   }
   if(gden2!=22330)//,giaychayden2=0
    { gden2++;
      delay(1);
    }
  else
     {gden2=177;
      delay(1);
     }
   if(gden3!=22330)//,giaychayden3=0
  { gden3++;
    delay(1);
  }
  else
  {gden3=177;
  delay(1);
   }                
   if(gden4!=22330)//,giaychayden4=0
    { gden4++;
     delay(1);
    }
  else
     {gden4=177;
     delay(1);
     }   
      if(gmden2!=330)
         { gmden2++;
            delay(1);
         }
      else
         {gmden2=7;
          delay(1);
         }     
      if(gmden3!=330)
           { gmden3++;
             delay(1);
           }
       else
        {gmden3=7;
          delay(1);
        }   
      if(gmden4!=330)
         { gmden4++;
           delay(1);
         }
        else
         {gmden4=7;
          delay(1);
          }          
          if(giayghingay!=330)
         { giayghingay++;
           delay(1);
         }
        else
         {giayghingay=55;
          delay(1);
          }  
          if(giaya1!=60)
         { giaya1++;
           delay(1);
         }
        else
         {giaya1=23;
          delay(1);
          } 
          if(giaya2!=60)
         { giaya2++;
           delay(1);
         }
        else
         {giaya2=23;
          delay(1);
          }                    
 }  
 } 
}
// HET VOID CLOOP  
void caimo()
    {   //cai dat THU CHO TAT MO                   
              //HET CAI DAT THU CHO TAT MO
              /*if(datal[0] == 'x' && datal[1] == 'o' && datal[2] == 'a')
                      {if(giatrinhap==gtgoc2&&gtgoc2>10000001||dienapa0<500)
                      {                         
                          xoabonho();
                      }
                         giaym=0;datal[0] = 's';
                      } 
                      */                           
                   
                      if(datal[0] == 'h' && datal[1] == 'v' && datal[2] == '2')
                      {
                         dcghidoc=2;delay(1);
                           doc();
                         giaym=0;
                         datal[0] = 's';
                      }  
                      if(datal[0] == 'h' && datal[1] == 'v' && datal[2] == '3')
                      {
                         dcghidoc=3;delay(1);
                           doc();
                         giaym=0;
                         datal[0] = 's';
                      }  
                                           
                      if(datal[0] == 'x' && datal[1] == 'm' && datal[2] == 'p')
                      {
                         dcghidoc=85;delay(1);
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                         
                      if(datal[0] == 'h' && datal[1] == 'd' && datal[2] == '2')
                      {
                         dcghidoc=82;delay(1);
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                      if(datal[0] == 'h' && datal[1] == 'd' && datal[2] == '3')
                      {
                         dcghidoc=83;delay(1);
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                       if(datal[0] == 'h' && datal[1] == 'd' && datal[2] == '4')
                      {
                         dcghidoc=84;delay(1);
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                       
                      //cai thu  mo tat den
                      if(datal[0] == 't' && datal[1] == 'm' && datal[2] == '2')
                      {
                         dcghidoc=160;delay(1);cphtthu=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                       if(datal[0] == 't' && datal[1] == 't' && datal[2] == '2')
                      {
                         dcghidoc=163;delay(1);cphtthu=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                       if(datal[0] == 'd' && datal[1] == '2' && datal[2] == '2')
                      {
                         dcghidoc=166;delay(1);cphtden22=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                      if(datal[0] == 'd' && datal[1] == '2' && datal[2] == '3')// mo den 2 lan 2
                      {
                         dcghidoc=162;delay(1);cphtden23=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                       if(datal[0] == 'd' && datal[1] == '2' && datal[2] == '4')
                      {
                         dcghidoc=89;delay(1);cphtden24=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      }                      
                      if(datal[0] == 'd' && datal[1] == '2' && datal[2] == '5')
                      {
                         dcghidoc=87;delay(1);cphtden25=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      }  
                 /* if(datal[0] == 'x' && datal[1] == 'm' && datal[2] == '1')
                      {
                         dcghidoc=88;delay(1);//cphtden25=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                      */ 
                        if(datal[0] == 'd' && datal[1] == '3' && datal[2] == '2')
                      {
                         dcghidoc=167;delay(1);cphtden32=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      } 
                      if(datal[0] == 'd' && datal[1] == '3' && datal[2] == '3')//mo den 3 la 2
                      {
                         dcghidoc=165;delay(1);cphtden33=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      }                      
                      if(datal[0] == 'd' && datal[1] == '4' && datal[2] == '2')
                      {
                         dcghidoc=168;delay(1);cphtden42=1;
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      }  
                       if(datal[0] == 'g' && datal[1] == '2' && datal[2] == '3')//hen giay mo tat
                      {
                         dcghidoc=169;delay(1);
                         doc();
                         giaym=0;
                         datal[0] = 's';
                      }  
                      if(datal[0] == 'm' && datal[1] == '4' && datal[2] == '8')//hen giay mo tat
                      {
                         
                         giaym=48;delay(10);
                         datal[0] = 's';
                      }  
                             
                  dcghi=dcghidoc;               
                  giatridoc=ctrieul*10000000+trieul*1000000+tnghinl*100000+cnghinl*10000+nghinl*1000+traml*100+chucl*10+dvl;///2222               
 datad=state;
 switch(datad) 
 {
  case 'z': //cho dieu kien de ghi 
           giaym=0;           
             if( kieu!=9)
                 {       
                   kieu++;delay(1);
                 }
                 else
                  {
                 kieu=1;
                  } 
          break;   
        /* case 'v':if(vitri!=8)
            {vitri++;delay(2);giaym=0;
            }
           else
           {vitri=0;
            }
           break; 
            case 'x':if(vitri!=0)
            {vitri--;delay(2);giaym=0;
            }
           else
           {vitri=8;
            }
           break;  
           */          
         case 'h':if(hienthi!=5)
            {hienthi++;delay(1);giaym=0;
            }
           else
           {hienthi=0;
            }
           break;   
           case 't':if(hienthi!=0)
            {hienthi--;delay(1);giaym=0;
            }
           else
           {hienthi=5;delay(1);
            }
           break;                               
         default:datad="0";
          break; 
 }
 
  if(giaym==5||giayghi==994)
 {kieu=1;loai=0;
  }
    }
 //BAT DAU HAM CAI DAT MOI
 void caihengio()//nhap gia tri khi ghi 
 { datad=state;
               giatrinhap= ctrieul3*10000000+trieul3*1000000+tnghinl3*100000+cnghinl3*10000+nghinl3*1000+traml3*100+chucl3*10+dvl3;
                if(vitri==1)
               {ctrieul3=so1;//trieul3=so2;
               }
             if(vitri==2)
               {trieul3=so1;//tnghinl3=so2;
               }  
     if(vitri==3)
               {tnghinl3=so1;//cnghinl3=so2;
               }
               if(vitri==4)
               {cnghinl3=so1;//nghinl3=so2;
               } 
     if(vitri==5)
               {nghinl3=so1;//traml3=so2;
               }
               if(vitri==6)
               {traml3=so1;//chucl3=so2;
               } 
    if(vitri==7)
               {chucl3=so1;//dvl3=so2;
               }  
               if(vitri==8)
               {dvl3=so1;
               } 
               // cach nhap moi theo so 1 aaaaa
                        if(datad == '0' )                                                                                                
                                 {so1=0;giaym=0;datad = 's';// delay(1);//vitri++;                                                         
                                 }   
                         if(datad == '1' )                                                                                                           
                                 {so1=1;giaym=0;datad = 's'; //delay(1);//vitri++;                                                         
                                 }
                         if(datad == '2' )                                                                                                          
                                  {so1=2;giaym=0;datad = 's';// delay(1);//vitri++;                                                         
                                 }
                         if(datad == '3' )                                                                                                           
                                 {so1=3;giaym=0;datad = 's';//delay(1);// vitri++;                                 
                                 } 
                         if(datad == '4' )                                                                                                         
                                 {so1=4;giaym=0;datad = 's'; //vitri++;                                 
                                 }
                         if(datad == '5' )                                                                                                           
                                 {so1=5;giaym=0;datad = 's';// vitri++;                                  
                                 } 
                         if(datad == '6' )                                                                                                           
                                 {so1=6;giaym=0;datad = 's'; //vitri++;                                 
                                 } 
                          if(datad == '7' ) 
                                                                                                          
                                 {so1=7;giaym=0;datad = 's'; //vitri++;                                 
                                 } 
                          if(datad == '8' ) 
                                                                                                         
                                {so1=9;giaym=0;datad = 's'; //vitri++;                                
                                 } 
                          if(datad == '9' ) 
                                                                                                          
                                 {so1=9;giaym=0;datad = 's';//vitri++;                                 
                                 } 
                         // cach nhap moi theo so 1 bbbbbbbbbbbbb             
                     
                      //HEN TAT MO DEN TRUC TIEP  BBBBBBBBB
                                 if(datap[0] == '9' && datap[1] == '1' )                                                                           
                                 {vitri=1;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '9' && datap[1] == '2' )                                                                           
                                 {vitri=2;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '9' && datap[1] == '3' )                                                                           
                                 {vitri=3;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '9' && datap[1] == '4' )                                                                           
                                 {vitri=4;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '9' && datap[1] == '5' )                                                                           
                                 {vitri=5;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '9' && datap[1] == '6' )                                                                           
                                 {vitri=6;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '9' && datap[1] == '7' )                                                                           
                                 {vitri=7;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '9' && datap[1] == '8' )                                                                           
                                 {vitri=8;giaym=0;datap[0] = 's';                                                          
                                 }
                                 
                 /*                //cach nhap thu hai aaaaaaaaaa     
                if(datap[0] == '0' && datap[1] == '0' )                                                                           
                                 {so1=0;so2=0;
                                 datap[0] = 's';                                                          
                                 }              
                                if(datap[0] == '0' && datap[1] == '1' )                                                                           
                                 {so1=0;so2=1;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '0' && datap[1] == '2' )                                                                           
                                 {so1=0;so2=2;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '0' && datap[1] == '3' )                                                                           
                                 {so1=0;so2=3;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '0' && datap[1] == '4' )                                                                           
                                 {so1=0;so2=4;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '0' && datap[1] == '5' )                                                                           
                                 {so1=0;so2=5;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '0' && datap[1] == '6' )                                                                           
                                 {so1=0;so2=6;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '0' && datap[1] == '7' )                                                                           
                                 {so1=0;so2=7;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '0' && datap[1] == '8' )                                                                           
                                 {so1=0;so2=8;                                                         
                                 }
                                 if(datap[0] == '0' && datap[1] == '9' )                                                                           
                                 {so1=0;so2=9;
                                 datap[0] = 's';                                                          
                                 }                        
               
                  if(datap[0] == '1' && datap[1] == '0' )                                                                           
                                 {so1=1;so2=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '1' && datap[1] == '1' )                                                                           
                                 {so1=1;so2=1;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '1' && datap[1] == '2' )                                                                           
                                 {so1=1;so2=2;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '1' && datap[1] == '3' )                                                                           
                                 {so1=1;so2=3;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '1' && datap[1] == '4' )                                                                           
                                 {so1=1;so2=4;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '1' && datap[1] == '5' )                                                                           
                                 {so1=1;so2=5;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '1' && datap[1] == '6' )                                                                           
                                 {so1=1;so2=6;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '1' && datap[1] == '7' )                                                                           
                                 {so1=1;so2=7;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '1' && datap[1] == '8' )                                                                           
                                 {so1=1;so2=8;                                                         
                                 }
                                 if(datap[0] == '1' && datap[1] == '9' )                                                                           
                                 {so1=1;so2=9;
                                 datap[0] = 's';                                                          
                                 }
                   if(datap[0] == '2' && datap[1] == '0' )                                                                           
                                 {so1=2;so2=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '2' && datap[1] == '1' )                                                                           
                                 {so1=2;so2=1;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '2' && datap[1] == '2' )                                                                           
                                 {so1=2;so2=2;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '2' && datap[1] == '3' )                                                                           
                                 {so1=2;so2=3;
                                 datap[0] = 's';                                                          
                                 }
                                   if(datap[0] == '2' && datap[1] == '4' )                                                                           
                                 {so1=2;so2=4;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '2' && datap[1] == '5' )                                                                           
                                 {so1=2;so2=5;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '2' && datap[1] == '6' )                                                                           
                                 {so1=2;so2=6;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '2' && datap[1] == '7' )                                                                           
                                 {so1=2;so2=7;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '2' && datap[1] == '8' )                                                                           
                                 {so1=2;so2=8;                                                         
                                 }
                                 if(datap[0] == '2' && datap[1] == '9' )                                                                           
                                 {so1=2;so2=9;
                                 datap[0] = 's';                                                          
                                 }
                   if(datap[0] == '3' && datap[1] == '0' )                                                                           
                                 {so1=3;so2=0;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '3' && datap[1] == '1' )                                                                           
                                 {so1=3;so2=1;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '3' && datap[1] == '2' )                                                                           
                                 {so1=3;so2=2;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '3' && datap[1] == '3' )                                                                           
                                 {so1=3;so2=3;
                                 datap[0] = 's';                                                          
                                 }
                                   if(datap[0] == '3' && datap[1] == '4' )                                                                           
                                 {so1=3;so2=4;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '3' && datap[1] == '5' )                                                                           
                                 {so1=3;so2=5;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '3' && datap[1] == '6' )                                                                           
                                 {so1=3;so2=6;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '3' && datap[1] == '7' )                                                                           
                                 {so1=3;so2=7;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '3' && datap[1] == '8' )                                                                           
                                 {so1=3;so2=8;   datap[0] = 's';                                                       
                                 }
                                 if(datap[0] == '3' && datap[1] == '9' )                                                                           
                                 {so1=3;so2=9;
                                 datap[0] = 's';                                                          
                                 }
                    if(datap[0] == '4' && datap[1] == '0' )                                                                           
                                 {so1=4;so2=0;giaym=0;
                                 datap[0] = 's';                                                          
                                 }
          
                                 if(datap[0] == '4' && datap[1] == '1' )                                                                           
                                 {so1=4;so2=1;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '4' && datap[1] == '2' )                                                                           
                                 {so1=4;so2=2;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '4' && datap[1] == '3' )                                                                           
                                 {so1=4;so2=3;
                                 datap[0] = 's';                                                          
                                 }
                                   if(datap[0] == '4' && datap[1] == '4' )                                                                           
                                 {so1=4;so2=4;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '4' && datap[1] == '5' )                                                                           
                                 {so1=4;so2=5;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '4' && datap[1] == '6' )                                                                           
                                 {so1=4;so2=6;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '4' && datap[1] == '7' )                                                                           
                                 {so1=4;so2=7;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '4' && datap[1] == '8' )                                                                           
                                 {so1=4;so2=8;                                                         
                                 }
                                 if(datap[0] == '4' && datap[1] == '9' )                                                                           
                                 {so1=4;so2=9;
                                 datap[0] = 's';                                                          
                                 }
                  if(datap[0] == '5' && datap[1] == '0' )                                                                           
                                 {so1=5;so2=0;//giaym=0;
                                 datap[0] = 's';                                                          
                                 }                        
                                 if(datap[0] == '5' && datap[1] == '1' )                                                                           
                                 {so1=5;so2=1;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '5' && datap[1] == '2' )                                                                           
                                 {so1=5;so2=2;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '5' && datap[1] == '3' )                                                                           
                                 {so1=5;so2=3;
                                 datap[0] = 's';                                                          
                                 }
                                   if(datap[0] == '5' && datap[1] == '4' )                                                                           
                                 {so1=5;so2=4;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '5' && datap[1] == '5' )                                                                           
                                 {so1=5;so2=5;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '5' && datap[1] == '6' )                                                                           
                                 {so1=5;so2=6;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '5' && datap[1] == '7' )                                                                           
                                 {so1=5;so2=7;
                                 datap[0] = 's';                                                          
                                 }
                                 if(datap[0] == '5' && datap[1] == '8' )                                                                           
                                 {so1=5;so2=8;                                                         
                                 }
                                 if(datap[0] == '5' && datap[1] == '9' )                                                                           
                                 {so1=5;so2=9;
                                 datap[0] = 's';                                                          
                                 }  
                                 */                             
                 //cach nhap thu hai abbbbbbbbbbbbbbbbbbbb            
 }
 
void caimadoc()
    {       
         if(datap[0] == 't' && datap[1] == '2') 
          {t(den8);delay(2);giomo2=25;phutmo2=61;giotat2=26;phuttat2=62;//t(den8);
          giomo22=25;phutmo22=61;giotat22=26;phuttat22=62;
          giomo25=25;phutmo25=61;giotat25=26;phuttat25=62;
          giomo24=25;phutmo24=61;giotat24=26;phuttat24=62;
                     if(giaym>28)
                         {
                         giaym=12;
                         }
                         gmden2=0;datap[1] = 's'; 
           }
           
         if(datap[0] == 't' && datap[1] == '3' ) 
        {t(den9);delay(2);giomo3=25;phutmo3=61;giotat3=26;phuttat3=26;//t(den9);
        giomo33=25;phutmo33=61;giotat33=26;phuttat33=26;
                   if(giaym>28)//giaym=0;
                         {
                         giaym=12;
                         }
                         gmden3=0;datap[1] = 's'; 
        }
         if(datap[0] == 't' && datap[1] == '4' ) 
           {t(den13);delay(2);giomo4=25;phutmo4=61;giotat4=26;phuttat4=62;//t(den13);
                 if(giaym>28)
                         {
                         giaym=12;
                         }
                         gmden4=0;datap[1] = 's'; 
          } 
        if(datap[0] == 'm' && datap[1] == 'l' ) 
            {
              if(laplai!=3)
               {laplai++;delay(1);datap[1] = 's'; 
               }
              else
                {laplai=1;delay(1);
                }
           } 
           
                        if(datap[0] == 'm' && datap[1] == '2')
                            {m(den8);giomo2=hour;phutmo2=minute;dcghidoc=82;doc();chomoden2=1;
                                if(giaym>28)
                                  {
                                   giaym=12;
                                   } 
                                 if(gden2>9)                         
                                     { gden2=0;
                                     } 
                                     delay(2);
                                    datap[1] = 's';   
                            }
                      
                         if(datap[0] == 'm' && datap[1] == '3' )//dong thoi doc hen gio theo phut
                             {m(den9);giomo3=hour;phutmo3=minute;delay(2);dcghidoc=83;doc();chomoden3=1;
                                if(giaym>28)
                                   {
                                    giaym=12;
                                   }  
                                   if(gden3>9)                         
                                     { gden3=0;
                                     } 
                                     delay(2);
                                    datap[1] = 's';  
                              }
                     
                         if(datap[0] == 'm' && datap[1] == '4')
                         {                                     
                            m(den13); giomo4=hour;phutmo4=minute;dcghidoc=84;doc();chomoden4=1;
                              if(giaym>28)
                                {
                                 giaym=12;
                                } 
                            if(gden4>9)                         
                                     { gden4=0;
                                     }
                                     delay(2);
                                    datap[1] = 's'; 
                          } 
                                                                          
                      //khi nhan z se lam cho kieu nhay tu 2 den 9 va kieu ve khong khi giay m=5//
                      if(biencai==9&&kieu>1&&chophepghi==1||chophepghi>1&&kieu>1||chophepghi==0&&kieu>1)   ///2222                       
                        { 
                           ghi();  delay(500); giayghi=990;//giayghingay=0;
                           //loai=0; cho den 994 thi doc                           
                            switch(dcghidoc) 
 {case 2: cpdoc=4;          
          break;
 case 82:cpdoc=12;
          break;  
 case 83:cpdoc=13;
          break; 
 case 84: cpdoc=14;
          break; 
 case 85: cpdoc=15;           
          break; 
 case 89:cpdoc=19;          
          break; 
 case 160: cpdoc=1;          
          break;
case 162: cpdoc=2;          
          break;
  case 163:cpdoc=3;          
          break;   
  case 165: cpdoc=5;          
          break;
  case 166:cpdoc=6;          
          break;
  case 167:cpdoc=7;          
          break;
  case 168: cpdoc=8;          
          break;
 case 169: cpdoc=9;
          break;
    case 3: cpdoc=22;          
         break;                 
         default:cpdoc=22;
          break; 
       }                     
    }                      
     datad=state;                    
   }  
 //ham chuyen doi
 void chuyendoi(int temp3, char mang[3])
{
int chuc = temp3/10;
int donvi = temp3%10;
int tram = temp3%100;
mang[0] = chuc + 48;
mang[1] = donvi + 48;
mang[2] = tram + 48;
Serial.println(mang);
}
 //PHAN HAM GHI DOC XOA
void ghi()
  {  
  // giá trị được lưu trong EEPROM chỉ từ 0-255 mà thôi  
                dcghi=dcghidoc; 
                dcghi1=dcghi;
                dcghi2=dcghi+10;
                dcghi3=dcghi+20;
                dcghi4=dcghi+30;
                dcghi5=dcghi+40;
                dcghi6=dcghi+50; 
                dcghi7=dcghi+60;
                dcghi8=dcghi+70; 
             
                    gtghi8=ctrieul3 ; //gia tri ghi 8=chuc trieu l3
                    gtghi7=trieul3  ;
                    gtghi6=tnghinl3 ; 
                    gtghi5=cnghinl3 ;
                    gtghi4=nghinl3 ; 
                    gtghi3=traml3 ;
                    gtghi2=chucl3 ;
                    gtghi1=dvl3 ; 
               EEPROM.write(dcghi8,gtghi8);  //gtghi6   tnghind             
               EEPROM.write(dcghi7,gtghi7);  //gtghi5  cnghind   
               EEPROM.write(dcghi6,gtghi6);  //gtghi6   tnghind             
               EEPROM.write(dcghi5,gtghi5);  //gtghi5  cnghind
               EEPROM.write(dcghi4,gtghi4);   //gtghi4  nghind
               EEPROM.write(dcghi3,gtghi3);    //gtghi3  tramd
               EEPROM.write(dcghi2,gtghi2);    //gtghi2   chucd
               EEPROM.write(dcghi1,gtghi1);      //gtghi1  dvd
                 
 //valueghi=giatri1%1000;//lay so le thi chia cho 10(vd 18/10 le 8 )%100=10/%1000=210/%  
    
  delay(500); // delay 5ms để trước khi lưu giá trị tiếp theo  
} 
void doc()
{  
                dcghi=dcghidoc;
                dcghi1=dcghi;
                dcghi2=dcghi+10;
                dcghi3=dcghi+20;
                dcghi4=dcghi+30;
                dcghi5=dcghi+40;
                dcghi6=dcghi+50; 
                dcghi7=dcghi+60;
                dcghi8=dcghi+70;  
                     
               dvl=EEPROM.read(dcghi1);     // dia chi ghi              
               chucl=EEPROM.read(dcghi2);   //dcghi+10;
               traml=EEPROM.read(dcghi3);   //dcghi+20;
               nghinl=EEPROM.read(dcghi4);  //dcghi+30;
               cnghinl=EEPROM.read(dcghi5); //dcghi+40;
               tnghinl=EEPROM.read(dcghi6); //dcghi+50;
                trieul=EEPROM.read(dcghi7); //dcghi+40;
               ctrieul=EEPROM.read(dcghi8); //dcghi+50;           
             
  // value = EEPROM.read(demdoc);       
   delay(500);
}
//HAM XOA BO NHO
void xoabonho()
{
  for(int demxoa=0;demxoa<150;demxoa++)
{
  EEPROM.write(demxoa, 0);
}
  }
 //HET PHAN HAM GHI DOC XOA
void readDS1307()
{
        Wire.beginTransmission(DS1307);
        Wire.write((byte)0x00);
        Wire.endTransmission();
        Wire.requestFrom(DS1307, NumberOfFields);        
        second = bcd2dec(Wire.read() & 0x7f);
        minute = bcd2dec(Wire.read() );
        hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
        wday   = bcd2dec(Wire.read() );
        day    = bcd2dec(Wire.read() );
        month  = bcd2dec(Wire.read() );
        year   = bcd2dec(Wire.read() );
        year += 2000;    
}
/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(byte num)
{
        return ((num/16 * 10) + (num % 16));
}
/* Chuyển từ Decimal sang BCD */
int dec2bcd(byte num)
{
        return ((num/10 * 16) + (num % 10));
} 
void digitalClockDisplay()
{    
       
      
      // if(giaym==39||giaym==92)
     //  {           
      //   Serial.println("GIAYS");            
        // Serial.println(giays);  
       // }        
    
} 
void printDigits(int digits){
    // các thành phần thời gian được ngăn chách bằng dấu :
    Serial.print(":");        
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
} 
/* cài đặt thời gian cho DS1307 */
void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
{
        Wire.beginTransmission(DS1307);
        Wire.write(byte(0x00)); // đặt lại pointer
        Wire.write(dec2bcd(sec));
        Wire.write(dec2bcd(min));
        Wire.write(dec2bcd(hr));
        Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
        Wire.write(dec2bcd(d)); 
        Wire.write(dec2bcd(mth));
        Wire.write(dec2bcd(yr));
        Wire.endTransmission();
}
//18h13p28/03/17 ok
