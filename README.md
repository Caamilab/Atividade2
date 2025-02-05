# Projeto: Sequência de LEDs com Controle por Botão na BitDogLab

Este projeto implementa uma **sequência de controle de LEDs** utilizando o microcontrolador **Raspberry Pi Pico W**. Um botão é usado para ativar uma sequência de estados nos LEDs (vermelho, verde e azul), que alternam entre diferentes padrões até desligarem completamente. A sequência é gerenciada por temporizadores.

## Funcionalidades

- Controle de três LEDs (vermelho, verde e azul) com diferentes padrões.
- Ativação da sequência por meio de um botão.
- Gerenciamento automático da sequência com temporização.
- Utilização de debounce para evitar múltiplas leituras do botão.

## Como Funciona

1. **Estados dos LEDs**:
   - Estado 0: Todos os LEDs ligados.
   - Estado 1: Dois LEDs ligados (vermelho e verde).
   - Estado 2: Apenas o LED vermelho ligado.
   - Estado 3: Todos os LEDs desligados.

2. **Ativação pelo Botão**:
   - Ao pressionar o botão, a sequência é iniciada.
   - O sistema utiliza debounce para evitar leituras incorretas do botão.

3. **Sequência Temporizada**:
   - Cada estado dura 3 segundos antes de passar ao próximo.
   - Após o estado final (todos os LEDs desligados), a sequência é concluída e o sistema aguarda nova interação com o botão.

## Instruções de Uso

1. Ligue a BitDogLab a uma fonte de alimentação USB ou ao computador.
2. Pressione o botão conectado ao pino GPIO para iniciar a sequência de LEDs:
- Os LEDs alternarão entre os estados descritos na seção **Como Funciona**.
3. Após a conclusão da sequência (todos os LEDs desligados), pressione novamente o botão para reiniciar.

