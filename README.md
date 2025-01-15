# Cifrado-por-primos-ordenados

Cifrado de Mensajes con Números Primos y cordenadas(Fracmentos cortos):

Asignación de valores primos a los caracteres: Cada letra y el espacio en blanco se asocian con un número primo, basado en su frecuencia de uso en el idioma español. Los valores son los siguientes:

' ': 2
e: 3, a: 5, o: 7, i: 11, s: 13, r: 17, n: 19, l: 23, d: 29
c: 31, t: 37, u: 41, p: 43, m: 47, g: 53, b: 59, v: 61, f: 67
q: 71, j: 73, y: 79, h: 83, z: 89, x: 97, k: 101, w: 103

Estos son los caracteres permitidos para el cifrado.

Generación del Código y la Clave:

a. Código:

Para generar el código, convierta cada carácter del mensaje a su número primo correspondiente.
Multiplique todos los números primos obtenidos.
Ejemplo:
Mensaje: "holaa"
Primos correspondientes: [83, 7, 23, 5, 5]
Código: 83 × 7 × 23 × 5 × 5 = 334075
b. Clave:

Ordene los números primos obtenidos de menor a mayor, eliminando los repetidos.
Ejemplo: Para [83, 7, 23, 5, 5], el resultado es [5, 7, 23, 83].
Para cada número primo del mensaje original, registre su posición (índice) en el vector ordenado, sumando 1 para empezar desde 1.
Ejemplo:
Primos del mensaje: [83, 7, 23, 5, 5]
Vector ordenado: [5, 7, 23, 83]
Posiciones: [4, 2, 3, 1, 1]
La clave se genera concatenando estas posiciones, separadas por "1".
Resultado: Clave = 513141212
En resumen, para el mensaje "holaa", los resultados son:

Código: 334075
Clave: 1513141212


Descifrado de Mensajes con Números Primos y Coordenadas (Fragmentos cortos):

Se utiliza el codigo y la clave para recuperar el texto original

a. Factorización del Código:
Tome el código cifrado y realice su factorización en números primos para obtener los valores asociados al mensaje original.
Ejemplo:
Código: 334075
Primos factorizados: [83, 7, 23, 5, 5]

b. Eliminación de Repetidos y Ordenación:
Ordene los números primos obtenidos de menor a mayor, eliminando los duplicados.
Ejemplo:
Primos factorizados: [83, 7, 23, 5, 5]
Vector ordenado: [5, 7, 23, 83]

c. Uso de la Clave:
Divida la clave en partes que correspondan a las posiciones en el vector ordenado. Estas posiciones indican el orden correcto de los primos para reconstruir el mensaje original.
Ejemplo:
Clave: 1513141212
Posiciones: [4, 2, 3, 1, 1]
Usando el vector ordenado [5, 7, 23, 83], las posiciones nos dan: [83, 7, 23, 5, 5]

d. Reconstrucción del Mensaje:
Convierta cada número primo de la lista final al carácter correspondiente usando la tabla de valores primos.
Ejemplo:
Primos descifrados: [83, 7, 23, 5, 5]
Caracteres correspondientes: h, o, l, a, a
Mensaje original: "holaa"

En resumen, para el código 334075 y la clave 1513141212:
Mensaje descifrado: "holaa"


Código final:
Finalmente, para evitar el overflow, hay una función para encriptar y desencriptar, dividiéndolos en bloques del tamaño indicado, por defecto 4 letras. 
El resultado es un código con la forma de código1_codigo2_-key1_key2_ y así sucesivamente.

De esta forma, puedes encriptar y desencriptar con una función que requiere el vector con las tuplas de las letras, el tamaño de los sub-bloques y el propio mensaje/código.

Por ejemplo, el texto:
"hola que tal", encriptado queda así: 66815_17466_8510_-15131412_12151413_12151314_

Se puede ver de ejemplo en el código.
