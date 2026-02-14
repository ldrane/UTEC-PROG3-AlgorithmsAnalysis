#include <iostream>
#include <cmath>

// ================================================================================
// PROBLEMA 1: INCREMENTOS DEPENDIENTES
// ================================================================================
/*
ANÁLISIS MATEMÁTICO:

Code:
    void algorithm_A(int n) {
        int count = 0;                          // O(1)
        for (int i = 1; i <= n; i++) {          // Ejecuta n veces
            for (int j = i; j <= n; j += i) {   // Ejecuta n/i veces
                count++;                        // O(1)
            }
        }
    }

Análisis de costo (bucle interno):
- Línea "for j":
   i=1: j va 1->n con +1 = n iteraciones
   i=2: j va 2->n con +2 = n/2 iteraciones
   i=3: j va 3->n con +3 = n/3 iteraciones
   ...
   i=n: j va n->n con +n = 1 iteración
  
Costo total del bucle interno:
  T(n) = Σ(i=1 a n) (n/i)

Transformación matemática:
  T(n) <= Σ(i=1 a n) (n/i)
       = n * Σ(i=1 a n) (1/i)       -> Acotamos superiormente
       = n * H_n                    -> H_n = serie armónica

       Propiedad conocida de H_n (extraída de Cormen Part VIII Appendix: Mathematical Background, chapter A)
       La serie armónica satisface:
        H_n <= 1 + log2(n)

       = n * (1 + log2(n))   -> Aplicamos la cota
       = n + n*log2(n)
       = O(n log n)

Conclusión: T(n) = O(n log n)

Rol de la serie armónica:
 La serie armónica aparece naturalmente porque el bucle interno se ejecuta n/i veces cuando i varía de 1 a n.
 Su crecimiento logarítmico (no lineal) es lo que hace que:
            T(n) = n * H_n = n * O(log n) = O(n log n)

 Sin la serie armónica (con bucles de incremento constante), tendríamos O(n²). Entonces, llego a la conclusión que la
 serie armónica reduce la complejidad a O(n log n), lo cual considero desde ahora que es la razón por la que analizar
 bucles con incrementos variables como j += i es importante en la práctica a tener cuenta para optimizar algoritmos.
*/


// ================================================================================
// PROBLEMA 2: REGIÓN TRIANGULAR DE CÓMPUTO
// ================================================================================
/*
ANÁLISIS MATEMÁTICO:

Code:
    void algorithm_B(int n) {
        int count = 0;                      // O(1)
        for (int i = 1; i <= n; i++) {      // Ejecuta n veces
            for (int j = 1; j <= n-i+1; j++) {  // Ejecuta (n-i+1) veces
                count++;                   // O(1)
            }
        }
    }

Análisis de costo (bucle interno):

- Línea "for j":
  i=1: j va 1→n        = n iteraciones
  i=2: j va 1→(n-1)    = (n-1) iteraciones
  i=3: j va 1→(n-2)    = (n-2) iteraciones
  ...
  i=n: j va 1→1        = 1 iteración

Costo Total:
  T(n) = Σ(i=1 a n)*(n - i + 1)
       = Σ(i=1 a n)*(n - i + 1)

Sustituimos k = n - i + 1 (cuando i=1, k=n; cuando i=n, k=1):
  T(n) = Σ(k=1 a n) k
       = 1 + 2 + 3 + ... + n
       = n(n+1)/2
       = n²/2 + n/2  --> Término dominante es n², ya que por definición:  T(n) = n²/2 + n/2 <= n² para todo n >= 1

Conclusión: T(n) = O(n²)
*/

// ================================================================================
// PROBLEMA 3: ALGORITMO ITERATIVO
// ================================================================================
/*
ANÁLISIS MATEMÁTICO:

Code:
    void algorithm_C(int n) {
        int i = n;                      // O(1)
        while (i > 1) {                 // log2(n) veces
            i = i / 2;                  // O(1)
            for (int j = 0; j < i; j++) {  // Ejecuta i veces
                // operación constante   // O(1)
            }
        }
    }

Análisis de costo por línea (while loop):
- Línea "while (i > 1)":
  Iteración 1: i = n
  Iteración 2: i = n/2
  Iteración 3: i = n/4
  Iteración 4: i = n/8
   ...
  * Iteración k: i = n/2^(k-1)
  
  El bucle termina cuando i <= 1, es decir, cuando n/2^k <= 1, lo que ocurre después de k = log2(n) iteraciones

Por lo tanto, el costo total de operaciones es:
    T(n) = n + n/2 + n/4 + n/8 + ... + n/2^(log2(n))
         = Σ(k=0 a log2(n)) (n/2^k)
         = n * Σ(k=0 a log2(n)) (1/2^k)

Serie geométrica - Demostración por inducción:
  Debemos demostrar que: Σ(k=0 a log2(n)) (n/2^k) <= 2n

  PROPOSICIÓN GENERAL (sobre variable m):
  Para hacerlo, demostramos una proposición más general:
    Para todo entero m >= 0: Σ(k=0 a m) (1/2^k) <= 2

  Justificación de por qué usé m: Yo lo veo como que si probamos que la desigualdad vale para cualquier m >= 0, entonces
  automáticamente vale cuando m = log2(n).


  DEMOSTRACIÓN POR INDUCCIÓN MATEMÁTICA:

    Caso Base (m = 0):
        Σ(k=0 a 0) (1/2^k) = 1/2^0 = 1

    ¿Cumple 1 <= 2? SÍ

    Paso Inductivo:
        Hipótesis de Inducción:
            Asumimos que Σ(k=0 a m) (1/2^k) <= 2  ... para un m genérico

        Necesitamos demostrar: Σ(k=0 a m+1) (1/2^k) <= 2

        Desarrollo:
        Σ(k=0 a m+1) (1/2^k) = Σ(k=0 a m) (1/2^k) + 1/2^(m+1)
                                  <= 2 + 1/2^(m+1)    --> aplicamos HI

    Entonces ahora  el término 1/2^(m+1) es positivo pero decreciente.

    Usamos la fórmula exacta de la serie geométrica convergente:

    Σ(k=0 a m) (1/2^k) = (1 - (1/2)^(m+1)) / (1 - 1/2)
                       = 2(1 - (1/2)^(m+1))
                       = 2 - 2*(1/2)^(m+1)
                       = 2 - 1/2^m

    Por lo tanto:
    Σ(k=0 a m+1) (1/2^k) = [2 - 1/2^m] + 1/2^(m+1)
                          = 2 - 1/2^m + 1/2^(m+1)
                          = 2 + 1/2^(m+1) - 1/2^m
                          = 2 + 1/2^(m+1) - 2/2^(m+1)
                          = 2 - 1/2^(m+1)
                          < 2  CUMPLE  --> porque 1/2^(m+1) > 0

Conclusión por principio de inducción matemática:
    Σ(k=0 a m) (1/2^k) <= 2  para todo m >= 0

APLICACIÓN AL PROBLEMA ORIGINAL:
    Como demostramos que la proposición es válida para cualquier m >= 0, podemos establecer m = log2(n) (que es un
    entero >= 0):
            Σ(k=0 a log2(n)) (1/2^k) <= 2

    Multiplicando ambos lados por n (que es positivo):
        n * Σ(k=0 a log2(n)) (1/2^k) <= n * 2 = 2n

    Por lo tanto:
        T(n) = Σ(k=0 a log2(n)) (n/2^k) <= 2n

 De la demostración anterior, hemos establecido que:
    T(n) <= 2n

Aplicamos la definición formal de notación Big-O:

Definición: T(n) = O(g(n)) si y solo si existen constantes positivas
c > 0 y n0 > 0 tales que T(n) <= c*g(n) para todo n >= n0.

En nuestro caso:
    T(n) <= 2n = 2*n

    Esto satisface la definición con:
    - g(n) = n
    - c = 2
    - n0 = 1

    Verificación: Para todo n >= 1, T(n) <= 2*n ... CUMPLE

CONCLUSIÓN:
    T(n) = O(n)
*/


// ================================================================================
// PROBLEMA 4: BUCLES DEPENDIENTES
// ================================================================================
/*
ANÁLISIS MATEMÁTICO:

Code:
    void algorithm_D(int n) {
        int count = 0;                  // O(1)
        for (int i = 1; i <= n; i++) {  // Ejecuta n veces
            int k = 1;                  // O(1)
            while (k < i) {             // Incógnita a encontrar en REQUERIMIENTO 1
                count++;                // O(1)
                k = k * 2;              // O(1)
            }
        }
    }

REQUERIMIENTO 1: DETERMINE CUÁNTAS VECES SE EJECUTA EL BUCLE INTERNO PARA UN VALOR FIJO DE i

Para cada valor fijo de i en el bucle interno
Estado de k en cada iteración:
 Antes de iterar: k = 1
 Después de iter. 1: k = 1*2 = 2^1
 Después de iter. 2: k = 2*2 = 2²
 Después de iter. 3: k = 2²*2 = 2³
 ...
 Después de iter. m: k = 2^m

El bucle se ejecuta mientras k < i. Termina cuando 2^m >= i.

Esto ocurre cuando:
    2^m >= i
    m >= log2(i)
    m = log2(i)

Sin embargo, quiero contar el número de veces que se ejecuta count++, que es:
    m = log2(i)  (si i > 1)
    m = 0           (si i = 1)

Entonces, concluyo que para un valor fijo i, el bucle interno se ejecuta log2(i) veces.

Verificación con ejemplos:
- i = 1:  log2(1) = 0   iteraciones  (k=1, no entra al while)
- i = 2:  log2(2) = 1   iteración    (k: 1->2, termina)
- i = 3:  log2(3) = 1   iteración    (k: 1->2, termina)
- i = 4:  log2(4) = 2   iteraciones  (k: 1->2->4, termina)
- i = 5:  log2(5) = 2   iteraciones  (k: 1->2->4, termina)
- i = 8:  log2(8) = 3   iteraciones  (k: 1->2->4->8, termina)


REQUERIMIENTO 2: MODELE EL TIEMPO TOTAL MEDIANTE UNA SUMATORIA

El bucle externo itera desde i = 1 hasta i = n.
Para cada valor de i, el bucle interno se ejecuta log2(i) veces.

Entonces, el tiempo total sería:
    T(n) = Σ(i=1 a n) log2(i)

Aplicamos transformación para obtener una cota:
Usando que log2(i) <= log2(i) para todo i >= 1:
    T(n) = Σ(i=1 a n) log2(i)
         <= Σ(i=1 a n) log2(i)


Por propiedad de logaritmos tenemos que:
    Σ(i=1 a n) log2(i) = log2(1) + log2(2) + log2(3) + ... + log2(n)
                       = log2(1*2*3*...*n)
                       = log2(n!)

Por lo tanto, el tiempo total se puede modelar como:
    T(n) = Σ(i=1 a n) log2(i)
    T(n) <= log2(n!)


REQUERIMIENTO 3: JUSTIFIQUE RIGUROSAMENTE LA COMPLEJIDAD FINAL

Hemos establecido que: T(n) <= log2(n!)

Busco demostrar que log2(n!) tiene complejidad O(n log n).

PROPOSICIÓN:
    Para todo n >= 1: log2(n!) <= n*log2(n)

DEMOSTRACIÓN:
    log2(n!) = log2(1*2*3*...*n)
             = log2(1) + log2(2) + log2(3) + ... + log2(n)
             = Σ(i=1 a n) log2(i)

    Veo que para todo i <= n, tenemos log2(i) <= log2(n)

    Por lo tanto, cada término de la suma es menor o igual a log2(n):

    log2(n!) = Σ(i=1 a n) log2(i)
             <= Σ(i=1 a n) log2(n)     cada término <= log2(n)
             = log2(n) + log2(n) + ... + log2(n)  n términos
             = n*log2(n)

    Por lo tanto: log2(n!) <= n*log2(n) ---> DEMOSTRADO

CONCLUSIÓN USANDO DEFINICIÓN FORMAL DE BIG-O:

Definición: T(n) = O(g(n)) si existen constantes c > 0 y n0 > 0 tales que T(n) <= c*g(n) para todo n >= n0.

Del análisis:
    T(n) <= log2(n!) <= n*log2(n)
    Esto significa: T(n) <= 1*n*log2(n)

    Con las constantes:
    - g(n) = n*log2(n)
    - c = 1
    - n0 = 1

    Se verifica que para todo n >= 1: T(n) <= 1*n*log2(n)

Por lo tanto, según la definición formal de Big-O:
    T(n) = O(n log n)
*/


// ================================================================================
// PROBLEMA 5: CONDICIÓN DEPENDIENTE
// ================================================================================
/*
ANÁLISIS MATEMÁTICO:

Code:
    void algorithm_E(int n) {
        int count = 0;                      // O(1)
        for (int i = 1; i <= n; i++) {      // Ejecuta n veces
            for (int j = 1; j <= i; j++) {  // Ejecuta i veces
                if ((i + j) % 2 == 0) {     // O(1)
                    count++;                // O(1)
                }
            }
        }
    }


REQUERIMIENTO 1: DETERMINE EL NÚMERO EXACTO DE ITERACIONES DEL BUCLE INTERNO

El bucle interno "for (int j = 1; j <= i; j++)" se ejecuta para cada valor de i del bucle externo. Entonces, para un
 valor fijo de i, el bucle interno ejecuta exactamente i iteraciones.

Número total de ejecuciones de los dos bucles anidados:
    Total = Σ(i=1 a n) i = 1 + 2 + 3 + ... + n = n(n+1)/2 ---> Fórmula estándar de suma de enteros positivos


 REQUERIMIENTO 2: ANALICE CUÁNTAS VECES SE CUMPLE LA CONDICIÓN (i+j)%2==0

Bueno, la condición (i+j) % 2 == 0 es verdadera cuando i+j es PAR.

Entonces, una suma es par cuando:
  - Ambos sumandos son pares
  ó
  - Cuando ambos sumandos son impares

Concluyendo, i+j es par cuando i y j tienen la misma paridad.


ANÁLISIS PARA UN i FIJO:

Caso 1: i es IMPAR
Si i es impar, necesitamos que j sea IMPAR para que i+j sea par. Los valores impares de j en el rango [1, i] son:
 {1, 3, 5, ..., i}

Cantidad de valores: i/2

Ejemplos mental que usé para validar:
  i=5 (impar)
  Valores pares de i+j: j pertenece a {1, 3, 5} -> (5+1=6, 5+3=8, 5+5=10)
  Cantidad: 5/2 = 3

Caso 2: i es PAR
Si i es par, necesitamos que j sea PAR para que i+j sea par. Los valores pares de j en el rango [1, i] son:
{2, 4, 6, ..., i}

Cantidad de valores: i/2

Ejemplo mental que usé para validar: i=6 (par)
  Valores pares de i+j: j pertenece a {2, 4, 6} -> (6+2=8, 6+4=10, 6+6=12)
  Cantidad: 6/2 = 3

Entonces, llego a la conclusión que para cualquier i (par o impar), el número de iteraciones donde se cumple la condición
 es: (i+1)/2

Verificación:
- i=1 (impar): 1/2 = 1, (1+1)/2 = 1 = 1 ... CUMPLE
- i=2 (par):   2/2 = 1,  (2+1)/2 = 1.5 = 1 ... CUMPLE
- i=3 (impar): ⌈3/2⌉ = 2, (3+1)/2 = 2 = 2 ... CUMPLE
- i=4 (par):   4/2 = 2,  (4+1)/2 = 2.5 = 2 ... CUMPLE
- i=5 (impar): ⌈5/2⌉ = 3, (5+1)/2 = 3 = 3  ... CUMPLE

================================================================================
REQUERIMIENTO 3: DEMUESTRE COMPLEJIDAD USANDO Big Θ (Big Theta)
================================================================================

Costo total del algoritmo:

T(n) = Σ(i=1 a n) (i+1)/2

T(n) <=  Σ(i=1 a n) (i+1)/2
     = (1/2) * Σ(i=1 a n) (i+1)
     = (1/2) * [Σ(i=1 a n) i + Σ(i=1 a n) 1]
     = (1/2) * [n(n+1)/2 + n]
     = (1/2) * [(n(n+1) + 2n)/2]
     = (1/2) * [(n² + n + 2n)/2]
     = (1/2) * [(n² + 3n)/2]
     = (n² + 3n)/4
     = n²/4 + 3n/4

DEMOSTRACIÓN DE COTA INFERIOR
Necesitamos demostrar: T(n) >= c1*n² para algún c1 > 0 y n >= n0

De T(n) = n²/4 + 3n/4, tomamos c1 = 1/8 (que es menor que 1/4):

T(n) = n²/4 + 3n/4 >= n²/8  ¿Se cumple para todo n?

Comprobación algebraica:
n²/4 + 3n/4 >= n²/8  ---> Multiplico 8 ambos lados
2n² + 6n >= n²
n² + 6n >= 0
n(n + 6) >= 0  ... Verdadero para todo n >= 1

Entonces: T(n) >= (1/8)*n² para todo n >= 1


DEMOSTRACIÓN DE COTA SUPERIOR
Necesitamos demostrar: T(n) <= c2*n² para algún c2 > 0 y n >= n0

De T(n) = n²/4 + 3n/4, tomamos c2 = 1:

T(n) = n²/4 + 3n/4 <= n²  ¿Se cumple para todo n?

Comprobación algebraica:
n²/4 + 3n/4 <= n²
Multiplicar por 4:
n² + 3n <= 4n²
3n <= 3n²
n <= n²
1 <= n  ... Verdadero para todo n >= 1

Entonces: T(n) <= 1*n² para todo n >= 1

CONCLUSIÓN (Big Theta):
Definición: T(n) = Θ(g(n)) si existen constantes c1 > 0, c2 > 0 y n0 > 0
tales que c1*g(n) <= T(n) <= c2*g(n) para todo n >= n0

Entonces, ya demostrado que:
  (1/8)*n² <= T(n) <= 1*n² para todo n >= 1

Por lo tanto, con c1 = 1/8, c2 = 1 y n0 = 1:
    T(n) = Θ(n²)


REQUERIMIENTO 4: DEMUESTRE COMPLEJIDAD USANDO Big O

Definición formal de Big-O:
T(n) = O(g(n)) si existen constantes c > 0 y n0 > 0 tales que T(n) <= c*g(n) para todo n >= n0

De la demostración anterior, ya sabemos que:
T(n) = n²/4 + 3n/4 <= 1*n² para todo n >= 1

Demostración algebraica:
  n²/4 + 3n/4 <= n²
  n² + 3n <= 4n²
  3n <= 3n²
  n <= n² ---> verdadero para todo n >= 1

Por lo tanto, tomando c = 1 y n0 = 1:
    T(n) <= 1*n² para todo n >= 1

Entonces, por definición formal de Big-O:
    T(n) = O(n²)

*/

// ================================================================================
// PROBLEMA 6: RECURSIVO CON DIVISIÓN
// ================================================================================
/*
ANÁLISIS MATEMÁTICO:

Code:
    int R(int n) {
        if (n <= 1)              // O(1)
            return 1;            // O(1)
        return R(n/3) + 1;       // O(1) + T(n/3)
    }


REQUERIMIENTO 1: DEFINA LA RECURRENCIA QUE MODELA EL TIEMPO DE EJECUCIÓN
- Caso Base: Si n <= 1, se ejecuta una operación de costo O(1)
- Caso Recursivo: Si n > 1, se ejecuta una operación O(1) más una llamada recursiva T(n/3)

Por lo tanto, la recurrencia que modela el tiempo de ejecución es:
    T(n) = { c        si n <= 1
           { T(n/3) + c  si n > 1

donde c es una constante que representa el trabajo no recursivo (O(1)).


REQUERIMIENTO 2: RESUELVA LA RECURRENCIA USANDO EXPANSIÓN ITERATIVA

Iniciamos con: T(n) = T(n/3) + c

EXPANSIÓN 1:
Sustituimos T(n/3):
  T(n) = [T(n/3²) + c] + c = T(n/3²) + 2c

EXPANSIÓN 2:
Sustituimos T(n/3²):
  T(n) = [T(n/3³) + c] + 2c = T(n/3³) + 3c

EXPANSIÓN 3:
Sustituimos T(n/3³):
  T(n) = [T(n/3) + c] + 3c = T(n/3^4) + 4c

PATRÓN GENERAL:
Después de k expansiones:
  T(n) = T(n/3^k) + k*c

DETERMINACIÓN DE k (número de expansiones hasta el caso base):

El proceso se detiene cuando n/3^k <= 1, es decir:
  n <= 3^k
 log3(n) <= k --> Tomamos logaritmo base 3 en ambos lados

Entonces, el menor entero k que satisface esto es: k = log3(n)


ÚLTIMA SUSTITUCIÓN:
Cuando k = log3(n), tenemos n/3^k <= 1, lo que significa que T(n/3^k) cae en el caso base y por tanto T(n/3^k) = c

Sustituyendo en la expansión:
  T(n) = T(n/3^k) + k*c
       = c + log3(n)*c
       = c(1 + log3(n))

================================================================================
REQUERIMIENTO 3: DETERMINE FORMALMENTE LA COMPLEJIDAD TEMPORAL EN Big-O
================================================================================

De la expansión anterior que obtuve:
  T(n) = c(1 + ⌈log3(n)⌉)
       = c + c*⌈log3(n)⌉

Entonces, como log3(n) <= log3(n) + 1 para todo n >= 1:
  T(n) <= c + c*(log3(n) + 1)
       = c + c*log3(n) + c
       = 2c + c*log3(n)
       <= 3c*log3(n)    para n >= 2

Usando la propiedad log_a(x) = log_b(x) / log_b(a):
  log3(n) = log2(n) / log2(3)

Por lo tanto:
  T(n) <= 3c*log2(n) / log2(3)
       = (3c / log2(3))*log2(n)

Tomando que b = 3c / log2(3):
  T(n) <= b*log2(n)    para n >= 2

APLICACIÓN DE DEFINICIÓN FORMAL DE Big-O:

Definición: T(n) = O(g(n)) si existen constantes c > 0 y n0 > 0 tales que
T(n) <= c*g(n) para todo n >= n0

Con esto ya se demuestra  que existen constantes: b = 3c / log2(3) > 0,  n0 = 2 y g(n) = log2(n) tales que:
T(n) <= b*log2(n) para todo n >= n0

Entonces, por definición formal de Big-O:
T(n) = O(log n)

================================================================================
REQUERIMIENTO 4: CALCULE LA PROFUNDIDAD MÁXIMA DE LA RECURSIÓN
================================================================================
Entiendo que cuando piden profundidad de la recursión piden el número de niveles de llamadas recursivas hasta alcanzar
 el caso base.

ANÁLISIS NIVEL POR NIVEL:
Nivel 0 (llamada inicial):        n
Nivel 1 (después de R(n/3)):      n/3
Nivel 2 (después de R(n/9)):      n/3²
Nivel 3 (después de R(n/27)):     n/3³
...
Nivel k:                          n/3^k


DETERMINACIÓN DE LA PROFUNDIDAD:
El caso base se alcanza cuando n/3^k <= 1, es decir:
  n <= 3^k
  log3(n) <= k

El número de niveles (contando desde nivel 0) es:
  Profundidad = log3(n) + 1
(Sumo "+1" porque conté el nivel 0 además del número de expansiones)

EJEMPLOS NUMÉRICOS:
Para n = 1:
  Profundidad = log3(1) + 1 = 0 + 1 = 1
  Llamadas: R(1) -> retorna inmediatamente

Para n = 3:
  Profundidad = log3(3) + 1 = 1 + 1 = 2
  Llamadas: R(3) -> R(1) -> retorna

Para n = 9:
  Profundidad = log3(9) + 1 = 2 + 1 = 3
  Llamadas: R(9) -> R(3) -> R(1) -> retorna

Para n = 27:
  Profundidad = log3(27) + 1 = 3 + 1 = 4
  Llamadas: R(27) -> R(9) -> R(3) -> R(1) -> retorna

CONCLUSIÓN:
La profundidad máxima de la recursión es:
    Profundidad = log3(n) + 1 --> log3(n) iteraciones

*/


// ================================================================================
// PROBLEMA 7: RECURSIÓN CON TRABAJO LINEAL
// ================================================================================
/*
ANÁLISIS MATEMÁTICO:

Code:
    int S(int n) {
        if (n <= 1)              // O(1)
            return 1;            // O(1)
        int sum = 0;             // O(1)
        for (int i = 0; i < n; i++) {  // Ejecuta n veces
            sum += S(n/2);       // O(1) + T(n/2), n veces en total
        }
        return sum;              // O(1)
    }


REQUERIMIENTO 1: MODELAR EL TIEMPO DE EJECUCIÓN MEDIANTE UNA RECURRENCIA


ANÁLISIS DEL ALGORITMO:
1. Caso base: Si n <= 1, retorna 1 inmediatamente → T(1) = Θ(1)

2. Caso recursivo (n > 1):
   - El bucle for ejecuta n iteraciones
   - En cada iteración se llama a S(n/2)
   - Cada llamada S(n/2) es la misma (n/2 no cambia dentro del bucle)
   - Operaciones por iteración: suma y asignación Θ(1)

Costo total del caso recursivo:
   - n iteraciones del bucle: n * Θ(1) = Θ(n)
   - n llamadas a S(n/2): n * T(n/2)
   - Total: T(n) = n * T(n/2) + Θ(n)

RECURRENCIA OBTENIDA:
T(n) = n * T(n/2) + cn,  para n > 1, donde c es una constante
T(1) = d,  donde d es una constante

Para simplificar, asumo que n = 2^k


REQUERIMIENTO 2: RESOLVER LA RECURRENCIA USANDO EXPANSIÓN

Elegí el method por expansión (iteración):

T(n) = n * T(n/2) + cn

EXPANSIÓN 1:
T(n) = n * T(n/2) + cn
     = n * [n/2 * T(n/4) + c(n/2)] + cn
     = n * (n/2) * T(n/4) + n * c(n/2) + cn
     = (n²/2) * T(n/4) + (cn²/2) + cn


EXPANSIÓN 2:
T(n) = (n²/2) * T(n/4) + cn(n/2 + 1)
     = (n²/2) * [n/4 * T(n/8) + c(n/4)] + cn(n/2 + 1)
     = (n²/2) * (n/4) * T(n/8) + (n²/2) * c(n/4) + cn(n/2 + 1)
     = (n³/8) * T(n/8) + c(n³/8) + cn(n/2 + 1)
     = (n³/8) * T(n/8) + cn(n²/8 + n/2 + 1)

EXPANSIÓN 3:
T(n) = (n³/2³) * [n/8 * T(n/16) + c(n/8)] + cn³/8 + cn²/2 + cn
     = (n^4/2³*2³) * T(n/16) + (n³/2³) * c(n/8) + cn³/8 + cn²/2 + cn
     = (n^4/2^6) * T(n/16) + cn^4/2^6 + cn³/8 + cn²/2 + cn

PATRÓN GENERAL (después de i niveles):
   El denominador del coeficiente principal acumula potencias de 2: 0 + 1 + 2 + ... + (i-1)
   Suma de exponentes = i(i-1)/2

   T(n) = ( n^i / 2^(i(i-1)/2) ) * T(n/2^i) + [Serie de términos]

   Sustitución (Para llegar al caso base):
   n/2^i = 1  =>  2^i = n  =>  i = log2(n) = k

   Analizamos el término dominante (el primero):
   Coef = n^k / 2^(k(k-1)/2)

   Como n = 2^k, entonces n^k = (2^k)^k = 2^(k^2).

   Coef = 2^(k²) / 2^( (k² - k)/2 )
        = 2^( k² - k²/2 + k/2 )
        = 2^( k²/2 + k/2 )

   Sustituyendo k = log2(n):
   T(n) = 2^( (log2 n)² / 2 )

REQUERIMIENTO 3: COMPLEJIDAD TEMPORAL FINAL

   T(n) = Θ( 2^( (log n)² / 2 ) )

   Investigando un poco, encontré que a esto se le conoce como una complejidad "Cuasi-polinomial" (super-polinomial),
   que crece mucho más rápido que O(n log n) o O(n^2), pero más lento que O(2^n).
 */
