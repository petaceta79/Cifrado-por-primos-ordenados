# Cifrado-por-primos-ordenados

## Índice

- [Cifrado de Mensajes con Números Primos y Coordenadas](#cifrado-de-mensajes-con-números-primos-y-coordenadas-fragmentos-cortos)
- [Cifrado con Números Coprimos e Inverso Modular](#cifrado-con-números-coprimos-e-inverso-modular-criptografía-básica)
- [Fusión de los Dos Métodos](#fusión-de-los-dos-métodos)

## Cifrado de Mensajes con Números Primos y Coordenadas (Fragmentos Cortos)

### 1. Asignación de Valores Primos a los Caracteres

Cada letra y el espacio en blanco se asocian con un número primo, basado en su frecuencia de uso en el idioma español. Los valores son los siguientes:

| Caracter | Número Primo |
|----------|--------------|
| ' '      | 2            |
| e        | 3            |
| a        | 5            |
| o        | 7            |
| i        | 11           |
| s        | 13           |
| r        | 17           |
| n        | 19           |
| l        | 23           |
| d        | 29           |
| c        | 31           |
| t        | 37           |
| u        | 41           |
| p        | 43           |
| m        | 47           |
| g        | 53           |
| b        | 59           |
| v        | 61           |
| f        | 67           |
| q        | 71           |
| j        | 73           |
| y        | 79           |
| h        | 83           |
| z        | 89           |
| x        | 97           |
| k        | 101          |
| w        | 103          |

**Estos son los caracteres permitidos para el cifrado.**

---

### 2. Generación del Código y la Clave

#### a. **Código:**

1. Convierte cada carácter del mensaje a su número primo correspondiente.
2. Multiplica todos los números primos obtenidos.

**Ejemplo**:

Mensaje: **"holaa"**

Primos correspondientes: `[83, 7, 23, 5, 5]`

Código:  
`83 × 7 × 23 × 5 × 5 = 334075`

---

#### b. **Clave:**

1. Ordena los números primos obtenidos de menor a mayor, eliminando los repetidos.
   
**Ejemplo**:

Primos: `[83, 7, 23, 5, 5]`  
Vector ordenado: `[5, 7, 23, 83]`

2. Para cada número primo del mensaje original, registra su posición (índice) en el vector ordenado, sumando 1 para empezar desde 2.

**Ejemplo**:

Primos del mensaje: `[83, 7, 23, 5, 5]`  
Vector ordenado: `[5, 7, 23, 83]`  
Posiciones: `[4, 2, 3, 1, 1]`

La clave se genera concatenando estas posiciones, separadas por "1" y un "1" al inicio.

**Resultado**:  
Clave: `1513141212`

---

#### En resumen, para el mensaje **"holaa"**:

- Código: `334075`
- Clave: `1513141212`

---

### 3. Descifrado de Mensajes con Números Primos y Coordenadas (Fragmentos Cortos)

El proceso de descifrado utiliza el código y la clave para recuperar el texto original.

#### a. **Factorización del Código:**

1. Toma el código cifrado y realiza su factorización en números primos para obtener los valores asociados al mensaje original.

**Ejemplo**:

Código: `334075`  
Primos factorizados: `[83, 7, 23, 5, 5]`

#### b. **Eliminación de Repetidos y Ordenación:**

Ordena los números primos obtenidos de menor a mayor, eliminando los duplicados.

Primos factorizados: `[83, 7, 23, 5, 5]`  
Vector ordenado: `[5, 7, 23, 83]`

#### c. **Uso de la Clave:**

Divide la clave en partes que correspondan a las posiciones en el vector ordenado. Estas posiciones indican el orden correcto de los primos para reconstruir el mensaje original.

**Ejemplo**:

Clave: `1513141212`  
Posiciones: `[4, 2, 3, 1, 1]`  
Usando el vector ordenado `[5, 7, 23, 83]`, las posiciones nos dan: `[83, 7, 23, 5, 5]`

#### d. **Reconstrucción del Mensaje:**

Convierte cada número primo de la lista final al carácter correspondiente usando la tabla de valores primos.

**Ejemplo**:

Primos descifrados: `[83, 7, 23, 5, 5]`  
Caracteres correspondientes: `h, o, l, a, a`  
Mensaje original: `"holaa"`

---

#### En resumen, para el código `334075` y la clave `1513141212`:

- **Mensaje descifrado**: `"holaa"`

---

### 4. Código Final

Finalmente, para evitar el overflow, hay una función para encriptar y desencriptar, dividiéndolos en bloques del tamaño indicado (por defecto 4 letras). El resultado es un código con la forma de código1_codigo2_-key1_key2_ y así sucesivamente.
De esta forma, puedes encriptar y desencriptar con una función que requiere el vector con las tuplas de las letras, el tamaño de los sub-bloques y el propio mensaje/código.

**Ejemplo**:

El texto `"hola que tal"`, encriptado queda así: 66815_17466_8510_-15131412_12151413_12151314_

## Cifrado con Números Coprimos e Inverso Modular (Criptografía Básica)

Este sistema de cifrado se basa en propiedades de la aritmética modular, especialmente en el uso de **números coprimos** e **inversos modulares**. Es simple pero ilustrativo de algunos fundamentos de la criptografía moderna.

---

### 1. Generación de Claves

Para cifrar y descifrar, se necesitan tres valores:

- `m`: el **módulo**, un número aleatorio dentro de un rango definido.
- `c₁`: la **clave de cifrado**, un número coprimo con `m`.
- `c₂`: la **clave de descifrado**, es el **inverso modular** de `c₁` módulo `m`.

#### a. Selección del Módulo `m`

Se genera aleatoriamente un número grande dentro de un rango definido, por ejemplo, entre 99,999,999 y 999,999,999.

#### b. Generación de `c₁`: un número coprimo con `m`

Se selecciona aleatoriamente un número en `[1, m-1]` que cumpla `gcd(c₁, m) = 1`.

#### c. Cálculo de `c₂`: el inverso modular

Se usa el algoritmo de **Euclides Extendido** para resolver la ecuación:

```
c₁ · c₂ ≡ 1 mod m
```

El resultado `c₂` permite descifrar el mensaje cifrado.

---

### 2. Cifrado del Mensaje

Para cifrar un mensaje (que debe ser un número entero), se usa la fórmula:

```
mensaje_cifrado = (mensaje × c₁) mod m
```

---

### 3. Descifrado del Mensaje

Para recuperar el mensaje original, se utiliza:

```
mensaje_descifrado = (mensaje_cifrado × c₂) mod m
```

Dado que `c₂` es el inverso modular de `c₁`, esta operación revierte el cifrado.

---

### 4. Ejemplo

Supongamos que:

- Mensaje original: `12345`
- Claves generadas:
  - `m = 179265841`
  - `c₁ = 78965432`
  - `c₂ = 10438745`

#### Cifrado:

```
mensaje_cifrado = (12345 × 78965432) mod 179265841
= 146372913
```

#### Descifrado:

```
mensaje_descifrado = (146372913 × 10438745) mod 179265841
= 12345
```

## Fusión de los Dos Métodos

El objetivo es mejorar la seguridad aplicando el cifrado por congruencias a la clave más vulnerable del primer cifrado, dificultando aún más la comprensión ajena del mismo y el cálculo de la solución.

### Funcinoamiento 
Aplica el primer cifrado con numeros primos, pero cifra con congruencias cada numero que indica la posicion de las letras. Necesitando poseer el mensaje cifrado, la clave y el numero modular.

#### Ejemplos

**Palabra a encriptar:**  
hola  
**Mensaje cifrado:**
```
66815_-70816131_
```
**Clave:** 161821273  
**Valor modular:** 170509041

---

**Palabra a encriptar:**  
el sol se esconde tras las montaas doradas la brisa suave lleva cantos de aves y el rio serpentea lento bajo el cielo tranquilo mientras la noche pinta sombras y estrellas que brillan con calma en la oscuridad silenciosa las hojas caen sin prisa sobre la tierra fria y los suenos se tejen en el aire como hilos de luz que nunca se rompen el mundo respira lento y el tiempo parece olvidar su paso dejando solo paz y un susurro que invita a sonar despierto  
**Mensaje cifrado:**
```
1794_4186_234_119567_3774_2990_6110_24605_3770_17255_2990_10030_1430_162565_3174_1830_108965_5278_1830_6162_276_2618_28509_6327_690_9842_150745_276_23529_8806_276545_3542_29469_40885_460_342209_2838_7030_252343_2210_6162_43401_2990_17466_253759_4370_8246_167555_570_460_115661_27115_8294_40641_5005_2990_84826_4030_570_5434_104533_910_6018_8510_9537_11390_8690_4186_3198_3458_2886_12483_228_690_1122_71393_41998_5278_5658_518158_4674_5890_1326_42441_2622_73226_6902_18447_3910_14763_948_18722_42441_7310_558_108031_4930_45838_910_31755_7714_14651_38270_12956_20254_154037_40754_1254_124135_260_11305_2262_24123_1036_-183853065_183853065_168685468_46298052_170275068_104381013_104381013_106741569_104381013_104381013_104381013_170275068_123438261_104381013_169480268_185426769_107499708_104381013_169488216_104381013_87660477_205242156_169488216_87660477_109073412_123438261_109073412_87660477_124983252_170275068_88471173_123438261_124983252_204455304_166345677_169488216_170275068_123438261_169488216_126556956_46298052_124983252_126556956_205242156_124983252_126556956_126556956_107499708_107499708_166345677_87684321_188545464_47084904_107499708_188545464_23363970_23363970_104381013_188545464_188545464_204455304_170275068_205242156_186184908_169480268_170275068_186184908_23363970_167943225_126556956_186184908_165558825_87660477_183853065_123438261_169464372_23363970_104381013_169488216_47084904_169488216_123438261_186184908_185426769_107499708_24150822_124983252_167943225_186184908_167943225_165558825_109073412_24150822_23363970_105151969_167943225_126556956_104381013_185426769_109073412_123438261_169464372_166369521_165558825_107499708_166353625_170275068_169488216_126556956_86086773_183853065_23363970_124983252_186161064_
```
**Clave:** 21749509  
**Valor modular:** 222477603
