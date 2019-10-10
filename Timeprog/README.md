timeprog
========

Programa bastante sencillo y simple (e inseguro), que mide el tiempo de ejecucion de otro programa
que se le pase como argumento (Junto con la lista de argumentos de dicho programa).

Uso
---

Asumiendo que se esta en la carpeta de "build/":
`./timeprog <programa> <arg1> <arg2> <arg3> ... <argn>`

Donde:
- `<programa>` es el nombre del programa a cronometrar
- `<arg1> <arg2> <arg3> ... <argn>` son los argumentos a pasarle al programa a cronometrar

La salida en pantalla de este programa es el nombre del programa invocado (con sus argumentos),
junto con los tiempos de inicio, tiempo de finalizacion, y tiempo de ejecucion del programa invocado.