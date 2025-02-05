#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos GPIO
const uint RED_LED_PIN = 11;    // LED vermelho
const uint GREEN_LED_PIN = 12; // LED verde
const uint BLUE_LED_PIN = 13;  // LED azul
const uint BUTTON_PIN = 5;     // Botão

// Variáveis globais
bool leds_active = false; // Indica se os LEDs estão ativos
int led_state = 0;        // Estado atual dos LEDs

// Função de callback para gerenciar os estados dos LEDs
int64_t led_sequence_callback(alarm_id_t id, void *user_data) {
    switch (led_state) {
        case 0: // Todos os LEDs ligados
            gpio_put(RED_LED_PIN, true);
            gpio_put(GREEN_LED_PIN, true);
            gpio_put(BLUE_LED_PIN, true);
            led_state = 1;
            break;
        case 1: // Dois LEDs ligados
            gpio_put(RED_LED_PIN, true);
            gpio_put(GREEN_LED_PIN, true);
            gpio_put(BLUE_LED_PIN, false);
            led_state = 2;
            break;
        case 2: // Apenas um LED ligado
            gpio_put(RED_LED_PIN, true);
            gpio_put(GREEN_LED_PIN, false);
            gpio_put(BLUE_LED_PIN, false);
            led_state = 3;
            break;
        case 3: // Todos os LEDs desligados
            gpio_put(RED_LED_PIN, false);
            gpio_put(GREEN_LED_PIN, false);
            gpio_put(BLUE_LED_PIN, false);
            leds_active = false; // Permite nova interação com o botão
            led_state = 0;
            return 0; // Finaliza a sequência de temporização
    }

    // Reagenda o próximo estado após 3 segundos (3000 ms)
    return 3000000;
}

int main() {
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    // Configuração do botão como entrada com pull-up interno
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (true) {
        // Verifica se o botão foi pressionado e os LEDs não estão ativos
        if (gpio_get(BUTTON_PIN) == 0 && !leds_active) {
            sleep_ms(50); // Debounce

            if (gpio_get(BUTTON_PIN) == 0) { // Confirmação da pressão do botão após debounce
                leds_active = true; // Marca os LEDs como ativos

                // Inicia a sequência de LEDs com o primeiro estado imediatamente
                add_alarm_in_ms(1, led_sequence_callback, NULL, false);
            }
        }

        sleep_ms(10); // Pausa para reduzir o uso da CPU
    }

    return 0;
}