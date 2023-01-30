#include "typewise-alert.h"
#include <stdio.h>
#include <string.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  switch(coolingType) {
    case PASSIVE_COOLING:
      upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      upperLimit = 45;
      break;
    default:
      upperLimit = 40;
      break;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

/*void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    default:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is normal, everything cool :)\n");
      break;
  }*/
}

char* Format_sendToController_Test(BreachType breachType) {
  const unsigned short header = 0xfeed;
  static char buffer[20]= "0xfeed :";
  static char strBreachType[9];
  switch(breachType) {
    case TOO_LOW:
	  strBreachType = " TOO_LOW";
	  strcat(buffer,strBreachType);
      break;
    case TOO_HIGH:
	  strBreachType = " TOO_HIGH";
	  strcat(buffer,strBreachType);
      break;
    default:
	  strBreachType = " NORMAL";
	  strcat(buffer,strBreachType);
      break;
  }
  
  return buffer;
}

void sendToController(BreachType breachType) {
  printf("%x",Format_sendToController_Test(breachType));
}

char * Format_sendToEmail(BreachType breachType)
{
  //const char* recepient = "a.b@c.com";
  static char message[70]= "To: a.b@c.com\n";
  static char alarm[50];
  
  switch(breachType) {
    case TOO_LOW:
	    alarm = "Hi, the temperature is too low\n";
	    strcat(message,alarm);
      break;
    case TOO_HIGH:
      alarm = "Hi, the temperature is too high\n";
	    strcat(message,alarm);
      break;
    default:
	    alarm = "Hi, the temperature is normal, everything cool :)\n";
	    strcat(message,alarm);
      break;
  }
  return message;
}


void sendToEmail(BreachType breachType) {
  printf("%x",Format_sendToEmail(breachType));
}


