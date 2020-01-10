# JTAG


## Funções implementadas

as seguintes funções são usadas para seguir a lógia da seguinte máquina de estados:

**TAP state machine**


<img src="https://github.com/bgarrido7/feup-sele/blob/master/Final%20Project/JTAG_T4B10/images/state_macine.gif">


### TAPclk(int value)

  Dependendo do valor de **value**, envia combinações diferentes de TMS e TDO (TDI do JTAG a ser testado).
  juntamente com um clock, avançando para o estado seguinte da TAP state machine.
  
  Esta função permite tambem colocar bits no registo de dados e de IR se a state machine estiver no estado data shift ou IR shift

  ### read_TDI(int n)
    
   Utilizando a função TAPclk(), coloca a zero o valor do data register, de modo a obter no TDI (do arduino) o número de valroes que se pretende ler.
   Uma vez que o primeiro bit recebido é o LSB, é necessário inverter os valores obtidos.
    
### read_TDI_b() 
  
   Esta função é inspirada na anterior, com a difereneça de que lê apenas 1 bit. É utilizada para ler o estado do botão
   
### test_reset()

  Insere o valor de "1" no TMS, durante 5 ciclos de relógio consequentes. Isto para colocar a TAP state machine no estado test reset
  
 ### setup()
  
  Aqui são definidoes os inputs e output do arduino, coloca em test reset os registos e as instruções
  
### shift_IR()

  A partir do estado test reset, update IR ou update DR, a state machine transita para o estado shift IR
  
 ### read_IDCODE()

  Usada colocar o Instruction Register a 0001 (instrução correspondente ao IDCODE). É também feita a leitura do IDCODE no shift DR
  
  ### shift_DR()
  
  A partir do estado test reset, update IR ou update DR, a state machine transita para o estado shift DR 
  
  ### print_button_state()
  
   Usada colocar o Instruction Register a 0010 (instrução correspondente ao sample and prehold, de modo a poder aceder aos valores internos). 
   No data register, lê o 4º bit que corresponde ao estado do botão, segundo o  BSDL
   
  ### write_led1
   Usada colocar o Instruction Register a 0110 (instrução correspondente ao sextest, de modo a opder interferir com o boundary scan sem mudar variáveis internas do circuito integrado). 
    
   No Data Register, as posições 19, 20 e 129 são colocadas a 1 para que o led seja definido como ligado no output. A posições 129 tem este valor para evitar ativar o reset
    
   ### write_led0
   
   Semelhante ao write_led1 mas o valor do led é definido como 0
    
   ### loop()
    
   Onde são lidos os comandos e executadas as funções, infinitamente
    
    
