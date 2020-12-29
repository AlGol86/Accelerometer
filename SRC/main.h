#include "stm8s.h"
#include "gy_521.h"


#define PORT_iic       GPIOB
#define pin_sda        4
#define bit_sda                           (1<<pin_sda)
#define pin_clk        5
#define bit_clk                           (1<<pin_clk)

#define bit_read    1
#define bit_write   0
#define ACK 1 //acknowledge
#define NOT_ACK 0 //not acknowledge

typedef enum {
on,off,c3,c4,c5,c6,c7,b5,od,pp} out_data_t;

//iic
void sys_del_us(char del_us);
char start_iic (char adr, char read_write_bit);
char send_byte (char data_byte);
unsigned char receive_byte (char acknowledge);
void stop_iic (void);

void out(out_data_t pin_out,out_data_t event );
void out_init(out_data_t pin_out,out_data_t od_pp_out);
