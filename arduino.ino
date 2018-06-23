#include "Servo.h"//서보모터를 사용하기 위한 헤더파일 호출
Servo LKservo; //서보변수 선언

//모터드라이버핀과 아두이노의 연결번호
#define EA 3
#define EB 11
#define M_IN1 4
#define M_IN2 5
#define M_IN3 13
#define M_IN4 12

//초음파센서 아두이노핀
#define echo 6
#define trig 7

//서보모터 아두이노핀
#define servo_motor 2

int motorA_vector = 1;//모터의 회전방향이 반대일시 0을 1로 1을 0으로 바꿔주시면 모터의 회전방향이 바뀝니다.
int motorB_vector = 1;//모터의 회전방향이 반대일시 0을 1로 1을 0으로 바꿔주시면 모터의 회전방향이 바뀝니다.
int motor_speed = 170;//모터 스피드
int angle = 60;
char cmd;


void setup()
{
  Serial.begin(9600);//시리얼 통신속도를 9600로 한다.
  //모터관련 핀들을 출력으로 설정한다.
  pinMode(EA, OUTPUT);
  pinMode(EB, OUTPUT);
  pinMode(M_IN1, OUTPUT);
  pinMode(M_IN2, OUTPUT);
  pinMode(M_IN3, OUTPUT);
  pinMode(M_IN4, OUTPUT);


  pinMode(trig, OUTPUT);  //trig 출력 설정
  pinMode(echo, INPUT);  //echo 입력설정
  LKservo.attach(servo_motor);  //서보모터 핀설정
  LKservo.write(60);  //서보모터 값을 넣는다 (0~180 까지)
  delay(2000);//2초 지연
}

void loop()
{
  if(Serial.available()){
    cmd = Serial.read();
    if(cmd=='a'){
      //Serial.println("I received a");
      for(int i=LKservo.read();i<120;i++){
      LKservo.write(i);
      delay(50);
      }
      Serial.flush();
    }
    else if(cmd=='s'){
      for(int i=LKservo.read();i>0;i--){
      LKservo.write(i);
      delay(50);
      }
      Serial.flush();
    }
    else{
      Serial.println("!!!!!!!!!!!!!");
      Serial.flush();
    }
  }
}

int read_ultrasonic(void){  //초음파센서값 읽어오는 함수
  float return_time, howlong;  //시간값과 거리값을 저장하는 변수를 만든다.

  //초음파 센서는 초음파를 발사 후 돌아오는 시간을 역산하여 거리값으로 계산한다.

  digitalWrite(trig, HIGH);//초음파 발사
  delay(5);
  digitalWrite(trig, LOW);

  return_time = pulseIn(echo, HIGH);//돌아오는 시간
  howlong = ((float)(340 * return_time) / 10000) / 2; //시간을 거리로 계산
  return howlong;//거리값 리턴
}

void motor_con(int M1, int M2){

 if(M1>0){  //모터A 정회전
   digitalWrite(M_IN1,motorA_vector);
   digitalWrite(M_IN2,!motorA_vector);
 }
 else if(M1<0){  //모터A 역회전
   digitalWrite(M_IN1,!motorA_vector);
   digitalWrite(M_IN2,motorA_vector);
 }
 else{        //모터 A 정지
   digitalWrite(M_IN1,LOW);
   digitalWrite(M_IN2,LOW);
 }

 if(M2>0){    //모터B 정회전
   digitalWrite(M_IN3,motorB_vector);
   digitalWrite(M_IN4,!motorB_vector);
 }
 else if(M2<0){  //모터B 역회전
   digitalWrite(M_IN3,!motorB_vector);
   digitalWrite(M_IN4,motorB_vector);
 }
 else{          //모터 B 정지
   digitalWrite(M_IN3,LOW);
   digitalWrite(M_IN4,LOW);
 }
 analogWrite(EA,abs(M1)); //A모터 속도값
 analogWrite(EB,abs(M2)); //B모터 속도값
}
