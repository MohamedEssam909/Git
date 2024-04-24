#include "GPS.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

float currentLongitude,currentLatitude,currentSpeed;
float toDegree(float angle){     //convert recieved lat,long to Degree 
int degree=(int)angle/100;
float minutes=angle-(float)degree*100;
	return (degree+ (minutes/60));
}


float toRadian(float angle){ //convert recieved lat,long to Radian
return angle*PI/180;
}


float currentLongitude,currentLatitude,currentSpeed;
char GPS_logName[]="$GPRMC,";
char GPS[80];
char* token;
char GPS_formated[12][20];


void GPS_read(){
char correct_log=1;
char recievedChar;
char GPSarrayCounter=0;
do{	
for(char i=0;i<strlen(GPS_logName);i++){     //Checking Correct Log	
if(UART_func()!=GPS_logName[i])
    correct_log=0;          
	 
}
}while(correct_log);

strcpy(GPS,"");

do{
recievedChar=UART_func();
GPS[GPSarrayCounter++]=recievedChar;
}while(recievedChar!='*');

}




void GPS_format(){

char GPS_formated_counter=0;
token=strtok(GPS,",");

do{
strcpy(GPS_formated[GPS_formated_counter],token);
token=strtok(NULL,",");
GPS_formated_counter++;
}while(token!=NULL);



if(strcmp(GPS_formated[1],"A")==0){ //Checking data validity
	currentLongitude=(strcmp(GPS_formated[5],"E")==0)?atof(GPS_formated[4]):-atof(GPS_formated[4]);
  currentLatitude=(strcmp(GPS_formated[3],"N")==0)?atof(GPS_formated[2]):-atof(GPS_formated[2]);
	currentSpeed=atof(GPS_formated[6]);//if 0 don't take new points
}

}



float getCurrentLongitude(){
return currentLongitude;
}

float getCurrentLatitude(){
return currentLatitude;
}

float getCurrentSpeed(){
return currentSpeed;
}
