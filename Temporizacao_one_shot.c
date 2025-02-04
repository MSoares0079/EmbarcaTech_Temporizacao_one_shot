#include <stdio.h>
#include "pico/stdlib.h"

#define LED_AZUL 11//LED verde 
#define LED_VERDE 12//LED verde 
#define LED_VERMELHO 13//LED vermelho 
#define button_A 5//Pino do botão A
#define button_B  6//Pino do botão B

bool led_ativado = false;//Váriavel que funciona como um flag para o botão de interrupção
void gpio_irq_handler(uint gpio, uint32_t events);
int64_t turn_off_callback1(alarm_id_t id, void *user_data);
int64_t turn_off_callback2(alarm_id_t id, void *user_data);
int64_t turn_off_callback3(alarm_id_t id, void *user_data);

int main()
{
    stdio_init_all();
    //Inicialização dos LEDs
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL,GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE,GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO,GPIO_OUT);
    //Inicialização dos botões
    gpio_init(button_A);
    gpio_set_dir(button_A,GPIO_IN);
    gpio_pull_up(button_A);
    gpio_init(button_B);
    gpio_set_dir(button_B,GPIO_IN);
    gpio_pull_up(button_B);
    //Ativando as interrupções nos botões
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled(button_B, GPIO_IRQ_EDGE_FALL,true);
    while(true){
        sleep_ms(100);
        printf("Processador ocupado em outra tarefa\n");//Indica que o processador poderia estar ocupado tratando de outra tarefa
    }
    return 0;

}

void gpio_irq_handler(uint gpio, uint32_t events){
    if(!led_ativado){
        led_ativado = true;//Serve como deboucing uma vez que não permite a chamada repetida da interrução
        //Ligando os três LEDs
        gpio_put(LED_AZUL,true);
        gpio_put(LED_VERDE,true);
        gpio_put(LED_VERMELHO,true);
        add_alarm_in_ms(3000, turn_off_callback1, NULL, false);//Ativa um temporizador oneshot com o callback 1
    }
    
}

int64_t turn_off_callback1(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, false);// Desliga o primeiro LED 
    add_alarm_in_ms(3000, turn_off_callback2, NULL, false);//Ativa um temporizador oneshot com o callback 2    
    return 0;//Indica que o alarme não deve se repetir.
}
int64_t turn_off_callback2(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, false);// Desliga o segundo LED
    add_alarm_in_ms(3000, turn_off_callback3, NULL, false);//Ativa um temporizador oneshot com o callback 3
    return 0;//Indica que o alarme não deve se repetir.
}
int64_t turn_off_callback3(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, false);// Desliga o último LED
    led_ativado = false;//Permite que a interrupção do botão reinicie o ciclo.
    return 0;//Indica que o alarme não deve se repetir.
}