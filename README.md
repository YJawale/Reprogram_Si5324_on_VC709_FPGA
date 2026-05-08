# Reprogram_Si5324_on_VC709_FPGA
This repository will guide you through how to reprogram your Si5324 clock on VC709 FPGA board via IIC (I2C) interface. 
A very nice guide on how to find the registers and the values to be filled for a specific frequency: https://adaptivesupport.amd.com/s/question/0D52E00006hpZjySAE/howto-use-the-si5324-as-a-clock-generator
This repository will help you once you export the register map from the software (DSPLLsim) mentioned in the above linked post. So please go through the post first :)

I have been working on reprogramming si5324 for a while but did not find much documentation online so here I am , posting whatever I was able to achieve. 
First have a block design with Microblaze, IIC, UART and GPIO interface on vivado, and add the constraints for reset mentioned below:

set_property PACKAGE_PIN AT36 [get_ports si5324_rst]
set_property IOSTANDARD LVCMOS18 [get_ports si5324_rst]

My block design - <img width="1560" height="537" alt="image" src="https://github.com/user-attachments/assets/c9d8c097-c325-411c-bc14-c9a64ffdef28" />



After this, write bitstream and export the hardware to SDK/Vitis (I was using Vivado 2018.3, thus SDK for me). 
There, create a new application project with 'Hello World' template, and paste the C-Program I have uploaded in this repository.
Just replace the values in the tx[] arrays as per your  requirement, whatever you have to write to registers, which you will find after following the above linked tutorial (You will end up with a text file which includes what registers have to be filled with what values)

One thing about Si5324 is that it needs to be reset before it can be accessed, through a GPIO pin (being done by the C program I uploaded so you're fine).

The clock hides at address 0x68 behind the 8-channel-mux present at 0x74 on VC709 board, on the 8th channel. 

So first you need to reset the Si5324 clock with the GPIO port, then write to the Mux to open the 8th channel, and only then can you write the registers. 

I spent days on this with minimal documentation, so made this repository>
If it helped, please leave a star :)
