# JTAG

- **TAPclk(int value)**

  dependendo do valor de **value**, envia combinações diferentes de TMS e TDO (TDI do JTAG a ser testado).
  juntamente com um clock, avançando para o estado seguinte da TAP state machine


**TAP state machine**
<img src=https://www.google.com/url?sa=i&source=images&cd=&cad=rja&uact=8&ved=2ahUKEwjAse3muvnmAhWsz4UKHQGoAzEQjRx6BAgBEAQ&url=https%3A%2F%2Fwww.xjtag.com%2Fabout-jtag%2Fjtag-a-technical-overview%2Ftap_state_machine%2F&psig=AOvVaw2pJisXWGjs6tKW5nWL1PgG&ust=1578760351637035>

  esta função permite tambem colocar bits no registo de dados e de IR se a state machine estiver no estado data shift ou IR shift
