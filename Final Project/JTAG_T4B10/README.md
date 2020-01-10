# JTAG

- **TAPclk(int value)**

  dependendo do valor de **value**, envia combinações diferentes de TMS e TDO (TDI do JTAG a ser testado).
  juntamente com um clock, avançando para o estado seguinte da TAP state machine


**TAP state machine**
<img src="https://github.com/bgarrido7/feup-sele/blob/master/Final%20Project/JTAG_T4B10/images/state_macine.gif">

  esta função permite tambem colocar bits no registo de dados e de IR se a state machine estiver no estado data shift ou IR shift
