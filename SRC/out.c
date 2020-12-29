#include "stm8s.h"
#include "gy_521.h"
#include "main.h"

void out_init(out_data_t pin_out,out_data_t od_pp_out) {
  switch(pin_out){
	  case c3: {
		if(od_pp_out==pp){
	  GPIOC->DDR|=1<<3;
	  GPIOC->CR1|=1<<3;
	  GPIOC->CR2|=1<<3;
	  GPIOC->ODR&=~(1<<3);
	  }
	  break;}
		case b5: {
			if(od_pp_out==pp){      //push-pull
	        GPIOB->DDR|=1<<5; 
	        GPIOB->CR1|=1<<5;
	        GPIOB->CR2|=1<<5;
	        GPIOB->ODR&=~(1<<5);
      }
			else{                  //open drain
				  GPIOB->ODR|=1<<5;
				  GPIOB->CR1&=~(1<<5);
					GPIOB->DDR|=1<<5;
	        GPIOB->CR2|=1<<5;
		  }    
		  break;}
		}
}

void out(out_data_t pin_out,out_data_t event ){ //set pinout
	switch(pin_out){
	case c3: {
	if(event==on) 
	GPIOC->ODR|=(1<<3); 
	else 
	GPIOC->ODR&=~(1<<3);
	break;}
	
	case b5: {
	if(event==on) 
	GPIOB->ODR|=(1<<5); 
	else 
	GPIOB->ODR&=~(1<<5);
	break;}
	}
}