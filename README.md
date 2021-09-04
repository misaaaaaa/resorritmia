# resorritmia
Arduino based binary and ternary clock generator

https://www.youtube.com/watch?v=5FrmmSOtLdw

De comportamiento similar a múltiples metrónomos sincronizados, Resorritmia es un generador de señales de clock de 9 subdivisiones [1, 2, 3, 4, 6, 8, 9, 12, 16], las cuales pueden ser utilizadas de forma simultánea. Esto puede ser usado de base para el diseño de futuras máquinas de estado, aparatos capaces de recibir señales y realizar instrucciones sencillar (contar, sumar, mover, sonar o prender). Al poseer un reloj común, pueden generar sincronías rítmicas entre los elementos que se conecten. Un comportamiento habitual en circuitos integrados como el CD4040BE, que divide en potencias de 2. Este módulo además incorpora divisiones en 3, permitiendo rítmicas ternarias, similares a las que se encuentran en la música latinoamericana 

![image](https://github.com/misaaaaaa/resorritmia/blob/main/img/pattern.jpg)

## Especificaciones:

- 9 salidas independientes, con divisiones por 1, 2, 3, 4, 6, 8, 9, 12, 16; de triggers positivos de aproximadamente 30ms de duración
- Control de velocidad a través de potenciómetro
- Control de velocidad a través de señal externa (Control de Voltaje)
- Botón de reset
- Reset a través de señal externa (trigger positivo)
- Pantalla de visualización basada en el circuito integrado MAX7219
- Programada en Arduino Nano

## A futuro:

- Desarrollar PCB con grilla de leds de forma circular
- Proteger entradas y salidas del Arduino a través de transistores
- Optimizar la entrada de CV de clock para que el procesamiento sea analógico
- ¿Cambio de microcontrolador?
- ¿Es necesaria la pantalla?
