
/*  
*  AUTHOR: NATOR VERINUMBE
*  DATE: 11/05/2020
*  DESCRIPTION: This code is part of a larger project, dropping this here for future reference
*/


#define WL_RESERVE_SENSOR_ECHO A0//Water Level Reserve (digital Input)
#define WL_STORAGE_SENSOR_ECHO A2//Water Level Storage (digital Input)

#define WL_RESERVE_SENSOR_TR A1//Water Level Reserve (digital Input)
#define WL_STORAGE_SENSOR_TR A3//Water Level Storage (digital Input)


#define WL_BOILER_FULL 4//Water Level Boiler full (digital Input)
#define WL_BOILER_EMPTY 3//water level Boiler Empty (digital Input)

#define TEMP_SENSOR  A7//has to be an anology pin

#define PUMP_TO_RESERVE   7 //digital Output
#define VALVE_TO_BOILER 10 //digital Output
#define PUMP_TO_MEMBRANE 5 //digital Output

#define BOILER 6 //digital Output 

#define BAUD 9600 

 
#define WLR_FULL 100 //Water Level Reserve Full
#define WLS_FULL 100 //Storage capacity of Tank  default = 100cm

#define WLB_FULL 1 //Water Level Boiler (when boiler is full)
#define WLB_EMPTY 0 //When Boiler is empty
#define WLB_NORMAL 56 //When it's neither full not empty


<<<<<<< HEAD
// int isfull = 0;
bool isNotBoilerFull = true;
=======
float time = 0;
float distance = 0; 
int isfull = 0;
bool isBoilerFull = false;
>>>>>>> 2c002f8f15dc34495d38e5577464b385d22cc4b7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  
  pinMode(WL_RESERVE_SENSOR_ECHO, INPUT); //digital Input
  pinMode(WL_STORAGE_SENSOR_ECHO, INPUT); //digital Input
  pinMode(WL_RESERVE_SENSOR_TR, OUTPUT); //digital Input
  pinMode(WL_STORAGE_SENSOR_TR, OUTPUT); //digital Input
  
  pinMode(WL_BOILER_FULL, INPUT_PULLUP); //digital Input
  pinMode(WL_BOILER_EMPTY, INPUT_PULLUP); //digital Input
  
  pinMode(TEMP_SENSOR, INPUT);  //analog Input

  //pinMode(PUMP_TO_RESERVE, OUTPUT);  //digital Output
   pinMode(VALVE_TO_BOILER, OUTPUT); //digital Output
   pinMode(PUMP_TO_MEMBRANE, OUTPUT); //digital Output
   pinMode(BOILER, OUTPUT);//digital Output
  
}

volatile float wl_reserve;
volatile float wl_boiler; 
volatile float boiler_temp;

void loop() {
  wl_reserve = WLReserve();
  wl_boiler = WLBoiler();

  Serial.print("WLReserve : ");
  Serial.println(wl_reserve);

//**************************For Filling up Reserve Tank*********************
  
  if (wl_reserve < 90){  //When water level is less then 90cm/100cm of Reservoir Tank
    digitalWrite(PUMP_TO_RESERVE, HIGH);
  } else {
    digitalWrite(PUMP_TO_RESERVE, LOW);
  }
<<<<<<< HEAD
  
=======
//ERROR--needs adjustments
  if ( (WLBoiler() == WLB_EMPTY) ||  !(isBoilerFull)  ){ //Tank is only filled up when it's empty
    digitalWrite(VALVE_TO_BOILER, HIGH);
    if (WLBoiler() == WLB_FULL){
     isBoilerFull = true; 
    }
  } else {
    digitalWrite(VALVE_TO_BOILER, LOW);
  }

  int wl_boiler = WLBoiler();
  int boiler_temp = BoilerTemp();
  Serial.print("WLBoiler : ");
  Serial.println(wl_boiler);
>>>>>>> 2c002f8f15dc34495d38e5577464b385d22cc4b7

// //*****************************For Filling up Boiler Tank when Empty****************
//   if ( wl_boiler == WLB_EMPTY){
//      isNotBoilerFull = true;
//     }

//   if ( (wl_boiler == WLB_EMPTY) ||  (isNotBoilerFull)  ){ //Tank is only filled up when it's empty
//     digitalWrite(VALVE_TO_BOILER, HIGH);
//     if (wl_boiler == WLB_FULL){
//      isNotBoilerFull = false;
//     }
//   } else {
//     digitalWrite(VALVE_TO_BOILER, LOW);
//   }

//   //*************Boiler Temperature********************

//   if( (wl_boiler != WLB_EMPTY) && ( boiler_temp < 95) ){
//     digitalWrite(BOILER, HIGH);
//   } else {
//     digitalWrite(BOILER, LOW);
//   }
  
// //*******************Pump to Membrane ***********************
//    if( (boiler_temp >= 95/*C*/) && (WLStorage() < 90/*cm*/) && (wl_boiler != WLB_EMPTY) ){
//      digitalWrite(PUMP_TO_MEMBRANE, HIGH);
//   } else {
//     digitalWrite(PUMP_TO_MEMBRANE, LOW);
//   }


}

//***********************************************************************FUNCTION DEFINITION********************************************

uint8_t BoilerTemp(){
  uint8_t temp = 0;
  temp = (analogRead(TEMP_SENSOR) * 51 /105); //Reads and converts from farenheit to celcius
 // Serial.print("Boiler Temp : ");
 // Serial.println(temp);
  return temp; 
}


uint8_t WLReserve(){ //Water Level Reserve
volatile float time = 0;
volatile float distance = 0;
  
   digitalWrite(WL_RESERVE_SENSOR_TR,LOW);
   delayMicroseconds(2);
   digitalWrite(WL_RESERVE_SENSOR_TR,HIGH);
   delayMicroseconds(10);
   digitalWrite(WL_RESERVE_SENSOR_TR,LOW);
   delayMicroseconds(2);
   time=pulseIn(WL_RESERVE_SENSOR_ECHO,HIGH);
   
   distance=time*350/20000;
 return (distance);
}


int WLBoiler(){ //Water Level Boiler

  bool level_high = digitalRead(WL_BOILER_FULL);
  bool level_low = digitalRead(WL_BOILER_EMPTY);
  
  if(level_low){ //the pin is grounded when it's active
   // Serial.println("WL_BOILER_EMPTY ");
    return WLB_EMPTY;
  } else if(level_high == 0){ //the pin is grounded when it's active
  //  Serial.println("WL_BOILER_FULL");
    return WLB_FULL;
  } else {
  //  Serial.println("WLB_NORMAL");
    return WLB_NORMAL;
  }

}


uint8_t WLStorage(){ //Water Level Storage
  volatile float time = 0;
  volatile float distance = 0; 

   digitalWrite(WL_STORAGE_SENSOR_TR,LOW);
   delayMicroseconds(2);
   digitalWrite(WL_STORAGE_SENSOR_TR,HIGH);
   delayMicroseconds(10);
   digitalWrite(WL_STORAGE_SENSOR_TR,LOW);
   delayMicroseconds(2);
   time=pulseIn(WL_STORAGE_SENSOR_ECHO,HIGH);

    distance=time*350/20000;
  //  Serial.print("Storage Tank : ");
  //  Serial.println(distance);
  return (WLS_FULL - distance);
}




 
