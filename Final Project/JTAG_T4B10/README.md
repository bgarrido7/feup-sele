# JTAG

## Lógica do Programa

O JTAG é controlado pela seguinte máquina de estados:


**TAP state machine:**

<img src="https://github.com/bgarrido7/feup-sele/blob/master/Final%20Project/JTAG_T4B10/images/state_macine.gif">


Esta tem como entradas o TMS e o TDI que, juntamente com um sinal de clock, fazem a transição de estado.
Depedendo do estado, serão realizadas instruções que irão escrever o valor correto em TDI

## Funções implementadas

as seguintes funções são usadas para seguir a lógia da seguinte máquina de estados:

### TAPclk(int value)

  Dependendo do valor de entrada, envia combinações diferentes de TMS e TDO (TDI do JTAG a ser testado).
  Juntamente com um sinal de clock, avançando para o estado seguinte da TAP state machine.
  
  Esta função permite tambem colocar bits no registo de dados e de Instruction Register, se a state machine estiver no estado shift DR ou shift IR respetivamente

  **NOTA:** sempre que este pedaço de código está presente nas funções
  >
    TAPclk(TMS0);
    TAPclk(TMS0);
    TAPclk(0);
  >
  
  faz com que o estado final da máquina de estados após qualquer função, seja sempre **run test idle**
  
  
  ### read_TDI(int n)
    
   Utilizando a função TAPclk(), coloca a zero o valor do data register, de modo a obter no TDI (do arduino) o valor que se pretende ler.
   Uma vez que o primeiro bit recebido é o LSB, é necessário inverter os valores obtidos.
   
   
    
### read_TDI_b() 
  
   Esta função é inspirada na anterior, com a difereneça de que lê apenas 1 bit. É utilizada para ler o estado do botão
   
### test_reset()

  Coloca a 1 o TMS, durante 5 ciclos de relógio consequentes. Isto para colocar a TAP state machine no estado test reset
  
 ### setup()
  
  Aqui são definidoes os inputs e output do arduino, e coloca em test reset os registos e as instruções
  
### shift_IR()

  A state machine transita para o estado shift IR, a partir do estado test reset, update IR ou update DR
  
 ### read_IDCODE()

  Usada para colocar o Instruction Register a 0001 (instrução correspondente ao IDCODE). 
  
  No estado shift DR, é feita a leitura do IDCODE
  
  ### shift_DR()
  
  A state machine transita para o estado shift DR, a partir do estado test reset, update IR ou update DR
  
  ### print_button_state()
  
   Usada para colocar o Instruction Register a 0010 (instrução correspondente ao SAMPLE AND PREHOLD, de modo a poder aceder aos valores internos). 
   No data register, lê o 4º bit que corresponde ao estado do botão, segundo o BSDL
   
  ### write_led1
   Usada para colocar o Instruction Register a 0110 (instrução correspondente ao EXTEST, de modo a poder interferir com o boundary scan sem mudar variáveis internas do circuito integrado). 
    
   No Data Register, as posições 19, 20 e 129 são colocadas a 1 para que o output do led seja definido como ligado. A posições 129 tem este valor para evitar ativar o reset
    
   ### write_led0
   
   Semelhante ao write_led1() mas o valor do led é definido como 0, ou seja, desligado
    
   ### loop()
    
Dependendo dos comandos inseridos pelo utilizados, o código faz o seguinte:
  * **d:** imprime o IDCODE do PIC32 em binário e em hexadecimal
  * **b:**  imprime o estado do botão connetado ao pino 29 do ChipKIT.
  * **1:** liga o LED D5 da placa ChipKIT
  * **0:** desliga o LED D5 da placa ChipKIT
    
