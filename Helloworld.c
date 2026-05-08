#include "xparameters.h"
#include "xiic_l.h"
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdlib.h>
#include "xgpio.h"
#include "sleep.h"

#define IIC_BASE_ADDRESS    XPAR_AXI_IIC_0_BASEADDR
#define SI5324_I2C_ADDR      0X68
#define mux_addy 			0x74


int main(void)
{
	  init_platform();
	  print("Code Begin \n");

    //Change these values as per your requirement. 
    //Each array's [0]th element is the register to which it starts writing from, since the XIIC_SEND function auto increments registers, the following hex values get filled in the respective registers in correct order,
    //starting from the register mentioned in the [0]th element
    //Assign these registers in order
    u8 tx_0_to_11[13] = {0, 0x54, 0xE4, 0x22, 0x15, 0x92, 0xED, 0x2D , 0x2A, 0x00, 0xC0 , 0x08 , 0x40};
    u8 tx_19_to_25[8] = {19,0x29, 0x3E, 0xFF, 0xDF, 0x1F, 0x3F, 0x60};
    u8 tx_31_to_36[7] = {31, 0x00,0x00,0x01,0x00,0x00,0x01};
    u8 tx_40_to_48[10] = {40,0xC1,0xB5,0x7F,0x00,0x59,0x48,0x00,0x59,0x48};
    u8 tx_55[2] = {55, 0x00};
    u8 tx_131_132[3] = {131, 0x1F,0x02};
    u8 tx_137_to_139[4] = {137, 0x01,0x0F,0xFF};
    u8 tx_142[2] = {142,0x00};
	  u8 tx_143[2] = {143,0x00};
	  u8 tx_136[2] = {136,0x40};

    u8 open_chn= 0b10000000;
    //open channel on mux
    XIic_Send(IIC_BASE_ADDRESS, mux_addy, &open_chn, 1, XIIC_STOP);
	
    //reset to enable si5324 on mux
	  XGpio gpio;
	  XGpio_Initialize(&gpio, XPAR_AXI_GPIO_0_DEVICE_ID);
	  XGpio_SetDataDirection(&gpio, 1, 0x00);   // channel 1 = output
	  XGpio_DiscreteWrite(&gpio, 1, 0x01);      // drive HIGH = deassert reset
	  xil_printf("Si5324 reset deasserted\r\n");

	  //Wait for Si5324 to stabilize after reset
	  // Datasheet says minimum 1ms, use 10ms to be safe
	  usleep(10000);


    //0 to 11
    unsigned sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_0_to_11, 13, XIIC_STOP);
    xil_printf("Wrote %d should be 13\n",sentt);

    //19 to 25
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_19_to_25, 8, XIIC_STOP);
    xil_printf("Wrote %d should be 8\n",sentt);

    //31 to 36
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_31_to_36, 7, XIIC_STOP);
    xil_printf("Wrote %d should be 7\n",sentt);

    //40 to 48
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_40_to_48, 10, XIIC_STOP);
    xil_printf("Wrote %d should be 10\n",sentt);

    //55
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_55, 2, XIIC_STOP);
    xil_printf("Wrote %d should be 2\n",sentt);

    //131 to 132
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_131_132, 3, XIIC_STOP);
    xil_printf("Wrote %d should be 3\n",sentt);

    //137 to 139
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_137_to_139, 4, XIIC_STOP);
    xil_printf("Wrote %d should be 4\n",sentt);

    //142
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_142, 2, XIIC_STOP);
    xil_printf("Wrote %d should be 2\n",sentt);

    //143
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_143, 2, XIIC_STOP);
    xil_printf("Wrote %d should be 2\n",sentt);

    //136
    sentt = XIic_Send(IIC_BASE_ADDRESS, SI5324_I2C_ADDR, tx_136, 2, XIIC_STOP);
    xil_printf("Wrote %d should be 2\n",sentt);

    		//shut mux channel
    		open_chn = 0x00;
    		XIic_Send(IIC_BASE_ADDRESS, mux_addy, &open_chn, 1, XIIC_STOP);
    		cleanup_platform();

return 0;
}
