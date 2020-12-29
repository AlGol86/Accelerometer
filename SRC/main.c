#include "stm8s.h"
#include "gy_521.h"
#include "main.h"

struct{
int buffer[20];
long int summa;
char b_pointer;
char hyst_f;
} average;

main()
{
	initGY_521();
	out_init(c3,pp);
	while (1){
    if ( check_condition_GY_521(6000, 1500, AXEL_Y)) out(c3,on);
    else    out(c3,off);
	}
}
