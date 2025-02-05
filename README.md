# Temporização one shot

Este projeto tem como objetivo testar a funcionalidade de um temporização one shot
em um Raspberry Pi Pico W.

# Estrutura do código
O código consiste em ativar três LEDs ao apertar um botão ativando uma interrupção,
em que é primeiro ativado uma flag(variável led_ativado) que serve como deboucing
e é configurado um temporizador de ativação única de 1s.
Após esse tempo é chamado uma função de callback que desliga o primeiro LED,
e configura outro temporizador de ativação única de 1s,
isso ocorre de forma repetida até desligar todos os LEDs, 
desativando a flag led_ativado e permitindo que o ciclo se repita caso apertem o botão novamente.


A função principal(int main) não processa nenhuma informação referente a ligar ou desligar os LEDs,
em que está disponível para realizar outras tarefas,
para representar isso é utilizado um printf com a mensagem "Processador ocupado em outra tarefa".

# Vídeo demonstrativo do código 
https://drive.google.com/file/d/1-cuY1IIYEOzWovKV6CnAtrKI13D2A6ar/view?usp=drivesdk

