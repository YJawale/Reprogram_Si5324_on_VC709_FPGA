# Reprogram_Si5324_on_VC709_FPGA
This repository will guide you through how to reprogram your Si5324 clock on VC709 FPGA board via IIC (I2C) interface. 
A very nice guide on how to find the registers and the values to be filled for a specific frequency: https://adaptivesupport.amd.com/s/question/0D52E00006hpZjySAE/howto-use-the-si5324-as-a-clock-generator
This repository will help you once you export the register map from the software (DSPLLsim) mentioned in the above linked post. So please go through the post first :)
I have been working on reprogramming si5324 for a while but did not find much documentation online so here I am , posting whatever I was able to achieve. 
One thing about Si5324 is that it needs to be reset before it can be accessed, through a GPIO pin (being done by the C program I uploaded so you're fine).
The clock hides at address 0x68 behind the 8-channel-mux present at 0x74 on VC709 board, on the 8th channel. 
