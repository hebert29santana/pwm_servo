/*
    Hebert Costa Vaz Santana
    TIC370101235
    Grupo 7
*/

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22          // GPIO 22 para o servo
#define LED_VERDE_PIN 11      // GPIO 11 para o LED Verde
#define LED_AZUL_PIN 12       // GPIO 12 para o LED Azul
#define LED_VERMELHO_PIN 13   // GPIO 13 para o LED Vermelho
#define MIN_PULSE_WIDTH 500   // 0 graus (500µs)
#define MID_PULSE_WIDTH 1470  // 90 graus (1470µs)
#define MAX_PULSE_WIDTH 2400  // 180 graus (2400µs)
#define PULSE_INCREMENT 5     // Incremento de 5µs
#define DELAY_MS 10           // Atraso de 10ms entre ajustes

// Função para configurar o PWM do servo
void set_servo_pulse_width(uint pulse_width_us) {
    uint16_t wrap = 39062; // Período de 20ms (50Hz) com clock de 125MHz e divisor de 64
    uint16_t level = (pulse_width_us * wrap) / 20000; // Converte microssegundos para nível PWM
    pwm_set_gpio_level(SERVO_PIN, level);
}

// Função para mover o servo suavemente entre dois pulsos
void move_servo_smoothly(uint start_pulse, uint end_pulse) {
    if (start_pulse < end_pulse) {
        // Movimento crescente (ex.: 0° a 180°)
        for (uint pulse = start_pulse; pulse <= end_pulse; pulse += PULSE_INCREMENT) {
            set_servo_pulse_width(pulse);
            sleep_ms(DELAY_MS);
        }
    } else {
        // Movimento decrescente (ex.: 180° a 0°)
        for (uint pulse = start_pulse; pulse >= end_pulse; pulse -= PULSE_INCREMENT) {
            set_servo_pulse_width(pulse);
            sleep_ms(DELAY_MS);
        }
    }
}

// Função para controlar o LED RGB
void set_led_color(uint8_t vermelho, uint8_t verde, uint8_t azul) {
    pwm_set_gpio_level(LED_VERMELHO_PIN, vermelho); // Canal Vermelho
    pwm_set_gpio_level(LED_VERDE_PIN, verde);       // Canal Verde
    pwm_set_gpio_level(LED_AZUL_PIN, azul);         // Canal Azul
}

int main() {
    // Inicializa o GPIO do servo
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num_servo = pwm_gpio_to_slice_num(SERVO_PIN);

    // Configura o PWM do servo
    pwm_config config_servo = pwm_get_default_config();
    pwm_config_set_clkdiv(&config_servo, 64.f); // Divisor de clock para 50Hz
    pwm_config_set_wrap(&config_servo, 39062);  // Período de 20ms
    pwm_init(slice_num_servo, &config_servo, true);

    // Inicializa os GPIOs do LED RGB
    gpio_set_function(LED_VERDE_PIN, GPIO_FUNC_PWM);    // Canal Verde
    gpio_set_function(LED_AZUL_PIN, GPIO_FUNC_PWM);     // Canal Azul
    gpio_set_function(LED_VERMELHO_PIN, GPIO_FUNC_PWM); // Canal Vermelho

    // Configura o PWM do LED RGB
    pwm_config config_led = pwm_get_default_config();
    pwm_config_set_clkdiv(&config_led, 4.f); // Divisor de clock para maior resolução
    pwm_config_set_wrap(&config_led, 255);   // Período de 8 bits (0-255)
    pwm_init(pwm_gpio_to_slice_num(LED_VERDE_PIN), &config_led, true);
    pwm_init(pwm_gpio_to_slice_num(LED_AZUL_PIN), &config_led, true);
    pwm_init(pwm_gpio_to_slice_num(LED_VERMELHO_PIN), &config_led, true);

    // 1. Posiciona o servo em 180 graus (2.400µs) - LED Vermelho
    set_servo_pulse_width(MAX_PULSE_WIDTH);
    set_led_color(255, 0, 0); // LED Vermelho
    sleep_ms(5000); // Aguarda 5 segundos

    // 2. Posiciona o servo em 90 graus (1.470µs) - LED Verde
    set_servo_pulse_width(MID_PULSE_WIDTH);
    set_led_color(0, 255, 0); // LED Verde
    sleep_ms(5000); // Aguarda 5 segundos

    // 3. Posiciona o servo em 0 graus (500µs) - LED Azul
    set_servo_pulse_width(MIN_PULSE_WIDTH);
    set_led_color(0, 0, 255); // LED Azul
    sleep_ms(5000); // Aguarda 5 segundos

    // 4. Movimentação periódica suave entre 0° e 180° - LED RGB variando
    while (true) {
        // Move o servo de 0° a 180° - LED muda de Azul para Vermelho
        move_servo_smoothly(MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
        for (int i = 0; i <= 255; i++) {
            set_led_color(i, 0, 255 - i); // Transição de Azul para Vermelho
            sleep_ms(DELAY_MS);
        }

        // Move o servo de 180° a 0° - LED muda de Vermelho para Azul
        move_servo_smoothly(MAX_PULSE_WIDTH, MIN_PULSE_WIDTH);
        for (int i = 0; i <= 255; i++) {
            set_led_color(255 - i, 0, i); // Transição de Vermelho para Azul
            sleep_ms(DELAY_MS);
        }
    }
}