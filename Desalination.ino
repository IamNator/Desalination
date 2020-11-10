
/*  
*  AUTHOR: NATOR VERINUMBE
*  DATE: 11/05/2020
*  DESCRIPTION: This code is part of a larger project, dropping this here for future reference
*/


// #define WL_RESERVE_SENSOR_ECHO A0//Water Level Reserve (digital Input)
// #define WL_STORAGE_SENSOR_ECHO A2//Water Level Storage (digital Input)

// #define WL_RESERVE_SENSOR_TR A1//Water Level Reserve (digital Input)
// #define WL_STORAGE_SENSOR_TR A3//Water Level Storage (digital Input)


#define WL_BOILER_FULL 4//Water Level Boiler full (digital Input)
#define WL_BOILER_EMPTY 3//water level Boiler Empty (digital Input)

// #define TEMP_SENSOR  A7//has to be an anology pin

// #define PUMP_TO_RESERVE   7 //digital Output
#define VALVE_TO_BOILER 10 //digital Output
// #define PUMP_TO_MEMBRANE 5 //digital Output

// #define BOILER 6 //digital Output 

 #define BAUD 9600 

// //Variable
// #define WLR_FULL 1 //Water Level Reserve Full
// #define WLS_FULL 1 //Water Level Storage Full

#define WLB_FULL 1 //Water Level Boiler (when boiler is full)
#define WLB_EMPTY 0 //When Boiler is empty
#define WLB_NORMAL 56 //When it's neither full not empty

// float time = 0;
// float distance = 0; 
// int isfull = 0;
bool isNotBoilerFull = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  
  // pinMode(WL_RESERVE_SENSOR_ECHO, INPUT); //digital Input
  // pinMode(WL_STORAGE_SENSOR_ECHO, INPUT); //digital Input
  // pinMode(WL_RESERVE_SENSOR_TR, OUTPUT); //digital Input
  // pinMode(WL_STORAGE_SENSOR_TR, OUTPUT); //digital Input
  
  pinMode(WL_BOILER_FULL, INPUT_PULLUP); //digital Input
  pinMode(WL_BOILER_EMPTY, INPUT_PULLUP); //digital Input
  
  // pinMode(TEMP_SENSOR, INPUT);  //analog Input

  // pinMode(PUMP_TO_RESERVE, OUTPUT);  //digital Output
  pinMode(VALVE_TO_BOILER, OUTPUT); //digital Output
  // pinMode(PUMP_TO_MEMBRANE, OUTPUT); //digital Output
  // pinMode(BOILER, OUTPUT);//digital Output
  
}

void loop() {
 

   // put your main code here, to run repeatedly:
//   if (WLReserve() < WLR_FULL){
//     digitalWrite(PUMP_TO_RESERVE, HIGH);
//   } else {
//     digitalWrite(PUMP_TO_RESERVE, LOW);
//   }
// //ERROR--needs adjustments
  if (WLBoiler() == WLB_EMPTY){
     isNotBoilerFull = true;
    }

  if ( (WLBoiler() == WLB_EMPTY) ||  (isNotBoilerFull)  ){ //Tank is only filled up when it's empty
    digitalWrite(VALVE_TO_BOILER, HIGH);
    if (WLBoiler() == WLB_FULL){
     isNotBoilerFull = false;
    }
  } else {
    digitalWrite(VALVE_TO_BOILER, LOW);
  }

  // int wl_boiler = WLBoiler();
  // int boiler_temp = BoilerTemp();
  // Serial.print("WLBoiler : ");
  // Serial.println(wl_boiler);


  // if( (wl_boiler != WLB_EMPTY) && (boiler_temp < 95) ){
  //   digitalWrite(BOILER, HIGH);
  // } else {
  //   digitalWrite(BOILER, LOW);
  // }
  
  // // if( (BoilerTemp() >= 95) && (WLStorage() < WLS_FULL) && (WLBoiler() != WLB_EMPTY) ){
  //    digitalWrite(PUMP_TO_MEMBRANE, HIGH);
  // } else {
  //   digitalWrite(PUMP_TO_MEMBRANE, LOW);
  // }

}

//***********************************************************************FUNCTION DEFINITION********************************************

// uint8_t BoilerTemp(){
//   uint8_t temp = 0;
//   temp = ( analogRead(TEMP_SENSOR) - 32 ) / 1.8 ; //Reads and converts from farenheit to celcius
//   // Serial.print("Boiler Temp : ");
//   // Serial.println(temp);
//   return temp; 
// }


// uint8_t WLReserve(){ //Water Level Reserve
//    uint8_t water_level = WLR_FULL; 
//    digitalWrite(WL_RESERVE_SENSOR_TR,LOW);
//    delayMicroseconds(2);
//    digitalWrite(WL_RESERVE_SENSOR_TR,HIGH);
//    delayMicroseconds(10);
//    digitalWrite(WL_RESERVE_SENSOR_TR,LOW);
//    delayMicroseconds(2);
//    time=pulseIn(WL_RESERVE_SENSOR_ECHO,HIGH);
   
//    distance=time*340/20000;
//  return (water_level - distance);
// }


int WLBoiler(){ //Water Level Boiler

  bool level_high = digitalRead(WL_BOILER_FULL);
  bool level_low = digitalRead(WL_BOILER_EMPTY);
  
  if(level_low){ //the pin is grounded when it's active
    Serial.println("WL_BOILER_EMPTY ");
    return WLB_EMPTY;
  } else if(level_high == 0){ //the pin is grounded when it's active
    Serial.println("WL_BOILER_FULL");
    return WLB_FULL;
  } else {
    Serial.println("WLB_NORMAL");
    return WLB_NORMAL;
  }

}


// uint8_t WLStorage(){ //Water Level Storage
//   uint8_t water_level = WLS_FULL;
//    digitalWrite(WL_STORAGE_SENSOR_TR,LOW);
//    delayMicroseconds(2);
//    digitalWrite(WL_STORAGE_SENSOR_TR,HIGH);
//    delayMicroseconds(10);
//    digitalWrite(WL_STORAGE_SENSOR_TR,LOW);
//    delayMicroseconds(2);
//      time=pulseIn(WL_STORAGE_SENSOR_ECHO,HIGH);
   
//    distance=time*340/20000;
//   return (water_level - distance);
// }




 
