#include "stm8s.h"
#include "gy_521.h"
#include "main.h"

void setRegAddrGY_521(char reg_addr){
  start_iic(GY_521_addr,bit_write);
  send_byte (reg_addr);
  stop_iic();
}

void setValueGY_521(char reg_addr,char value){
	start_iic(GY_521_addr,bit_write);
  send_byte (reg_addr);
  send_byte (value);
  stop_iic();
}

char getValueGY_521(char reg_addr){
	setRegAddrGY_521(reg_addr);
  return getByteGY_521();
}

char getByteGY_521(){
	char data_byte;
  start_iic(GY_521_addr,bit_read);
  data_byte=receive_byte(NOT_ACK);
  stop_iic();
  return data_byte;
}

void getBurstGY_521(char* data, char n){
	char i;
  start_iic(GY_521_addr,bit_read);
	for(i=0;i<n-1;i++){
  *(data+i)=receive_byte(ACK);
  }
  *(data+(n-1))=receive_byte(NOT_ACK);
  stop_iic();
  
}

void initGY_521(){
	getValueGY_521(MPU6050_PWR_MGMT_1);
	setValueGY_521(MPU6050_PWR_MGMT_1,0);
}

int get_TXYZ_GY_521(char data_type){
	char array[2];
	int T,XYZT;
	setRegAddrGY_521(MPU6050_ACCEL_XOUT_H+data_type);
	getBurstGY_521(array, 2);
	XYZT=(array[0]<<8)+array[1];
	if (data_type == TEMP)	{XYZT/=34;return XYZT+365;}
	else return XYZT;
}

int get_average_GY_521(char data_type){
	extern  struct{
int buffer[20];
long int summa;
char b_pointer;
char hyst_f;
} average;

	average.summa-=average.buffer[average.b_pointer];
	average.buffer[average.b_pointer]=get_TXYZ_GY_521(data_type);
	average.summa+=average.buffer[average.b_pointer];
	if(++average.b_pointer>19) average.b_pointer=0;
	return average.summa/20;
}

char check_condition_GY_521(int threshold, int hyst, char data_type){
	extern  struct{
       int buffer[20];
       long int summa;
       char b_pointer;
       char hyst_f;
       } average;

  int val=get_average_GY_521(data_type);
	
  if     (val > (threshold+hyst)) {average.hyst_f=1;return 1;}
  else if(val < threshold) {average.hyst_f=0;return 0;}
  else if (average.hyst_f) return 1;
  else return 0;
}

