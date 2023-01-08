timeprog
========

Este programa permite medir el tiempo de ejecución de un programa determindo que será pasado como un argumento junto a los argumentos del programa a medir.

Esta medición la hace por medio de una función que lo que hace es medir el tiempo concreto de la vida del proceso en ejecución. Dicho proceso es nuestro programa a medir

Uso
---

Suponiendo que ya se encuentra en la carpeta /build de /Timeprog :

1. Ejecuta usando ./timeprog <programa> <arg1> <arg2> <arg3> ... <argn>


Donde:
- `<programa>` es el nombre del programa a cronometrar
- `<arg1> <arg2> <arg3> ... <argn>` son los argumentos a pasarle al programa a cronometrar

La salida en pantalla de este programa es la salida del programa invocado,
con el tiempo de CPU que tardo en ejecutar (En ms), y el tiempo real que tardo en ejecutar (en s).
