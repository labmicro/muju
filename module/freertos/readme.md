# Implementation Notes
----------------------------

**Table of Contents**

- [English version](#english-version)
- [Versión en español](#versión-en-español)

## English Version

For the implementation of FreeRTOS V10.2.0, the source code was copied to the `source` folder and the `includes` folder was moved without changes with respect to the compressed file with the official distribution downloaded from the site [https://www.freertos.org /a00104.html]()

In the `portable` folder, the unused compilers were removed, leaving only the `GCC` folder and within it, the unused ports were also removed, leaving only the `ARM_CM3` and `ARM_CM4F` folders, all this without making any changes to their content.

In the `MemMang` folder, the `heap_4.c` file was modified adding an attribute to the definition of the ucHeap vector to locate it in the second bank of RAM memory. Thus the original code

```c
PRIVILEGED_DATA static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
```

it was changed by

```c
__attribute__ ((section(".data.$RAM2"))) PRIVILEGED_DATA static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
```

**Other implementations of the dynamic memory manager were not modified or tested**.

## Versión en Español

Para la implementación de FreeRTOS V10.2.0 se copió el código fuente en la carpeta `source` y se movió la carpeta `includes` sin cambios respecto al archivo comprimido con la distribución oficial descargada del sitio [https://www.freertos.org/a00104.html]()

En la carpeta `portable` se eliminaron los compiladores no utilizados dejando únicamente la carpeta `GCC` y dentro de la misma se eliminaron también las portaciones no utilizados dejando únicamente las carpetas `ARM_CM3` y `ARM_CM4F`, todo esto sin realizar ninguna modificación en el contenido de las mismas.

En la carpeta `MemMang` se modificó el archivo `heap_4.c` agregando un atributo a la definición del vector ucHeap para ubicar al mismo en el segundo banco de memoria RAM. De esta forma el código original

```c
PRIVILEGED_DATA static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
```

se cambió por

```c
__attribute__ ((section(".data.$RAM2"))) PRIVILEGED_DATA static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
```

**Las otras implementación del gestor de memoria dinámica no se modificaron ni se probaron**.

06/03/2019, Esteban Volentini <evolentini@gmail.com>
