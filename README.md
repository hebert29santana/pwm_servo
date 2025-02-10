# Controle de Servo Motor com LED RGB no Raspberry Pi Pico W
Este projeto demonstra como controlar um servo motor e um LED RGB usando um Raspberry Pi Pico W. O servo motor é movido suavemente entre 0° e 180°, enquanto o LED RGB muda de cor para indicar a posição atual do servo.

## Componentes Necessários
Raspberry Pi Pico W
Servo Motor (5V)
LED RGB (ânodo comum ou cátodo comum)
Resistores (220Ω para cada canal do LED RGB, se necessário)
Fios e protoboard

## Conexões
### Servo Motor
Vermelho (VCC): Conecte ao pino VBUS (5V) do Pico.
Marrom/Preto (GND): Conecte ao GND do Pico.
Amarelo/Laranja (Sinal): Conecte ao GPIO 22 do Pico.

### LED RGB
Verde: Conecte ao GPIO 11 do Pico.
Azul: Conecte ao GPIO 12 do Pico.
Vermelho: Conecte ao GPIO 13 do Pico.
GND (cátodo comum): Conecte ao GND do Pico.

### Código
O código está escrito em C e utiliza a biblioteca hardware/pwm.h para controlar o servo motor e o LED RGB.

## Funcionalidades
### Posicionamento do Servo:
0° (500µs)
90° (1470µs)
180° (2400µs)

### Movimentação Suave:
Incrementos de 5µs com atraso de 10ms entre ajustes.

### Controle do LED RGB:
Vermelho: Servo em 180°.
Verde: Servo em 90°.
Azul: Servo em 0°.

Transição de Cores: Durante a movimentação suave, o LED muda de Azul para Vermelho e vice-versa.

## Cálculos
### Frequência do PWM (Servo Motor)
O servo motor requer um sinal PWM com frequência de 50Hz (período de 20ms). O Raspberry Pi Pico tem um clock de 125MHz. Para gerar um sinal de 50Hz, usamos a seguinte fórmula:

![image](https://github.com/user-attachments/assets/43c4c341-fc2f-436f-af55-aeae35a2e33a)
![image](https://github.com/user-attachments/assets/989eaee4-7944-45a5-bde5-7759a314c974)
![image](https://github.com/user-attachments/assets/e2a3b3d9-0bcd-4011-b4c1-f81d1f49d743)

### Controle do LED RGB
O LED RGB é controlado usando PWM com um período de 8 bits (0-255). Cada canal (Vermelho, Verde, Azul) é ajustado individualmente para criar diferentes cores.
Vermelho: pwm_set_gpio_level(LED_VERMELHO_PIN, valor)
Verde: pwm_set_gpio_level(LED_VERDE_PIN, valor)
Azul: pwm_set_gpio_level(LED_AZUL_PIN, valor)

## Como Usar
Conecte os componentes conforme o diagrama.
Compile o código usando o VSCode com o ambiente configurado para o Raspberry Pi Pico.
Carregue o código no Pico.
Observe o servo motor se movendo e o LED RGB mudando de cor.

## Explicação do Comportamento do LED RGB
Servo em 180°: LED Vermelho.
Servo em 90°: LED Verde.
Servo em 0°: LED Azul.
Movimentação Suave: Transição de cores entre Azul e Vermelho.

Link do Vídeo: https://drive.google.com/file/d/1obTwc2o8VLfbg47oXXMivdCZBKVbvV7W/view?usp=sharing

## Código Completo
O código completo está disponível no arquivo pwm_servo.c deste repositório.

## Licença
Este projeto está licenciado sob a MIT License. Sinta-se à vontade para usar e modificar conforme necessário.
