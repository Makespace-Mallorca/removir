# <img src="./img/removir_logo.png" width="50" /> RemoVir <img src="./img/removir_logo.png" width="50" />
## Este repositorio contiene todos los recursos: instrucciones, código, documentación y datos para ayudarte a reciclar un Split (evaporador interior de aire acondicionado) a un eficiente filtro HEPA

Podrás montar un **purificador de aire con filtro HEPA** por poco más del coste de los filtros y lo más importante. Ayudarás a mantener el medio ambiente mientras proteges del contagio de COVID-19 el espacio que más necesites.

<img src="./img/TablaRiesgosCOVID.png" width="400" align="left" />

```text
Hemos querido enfocar nuestros esfuerzos a este tipo 
de dispositivos porque creemos que pueden ser una 
importante ayuda a evitar contagios. Las últimas 
evidencias científicas demuestran la transmisión de 
virus por aerosoles, es decir, por el mismo hecho de 
respirar. Esto aumenta el nivel de COV (Compuestos 
Orgánicos Volátiles entre los que se encuentra el 
virus SARS-CoV-2) algo que va correlacionado con la 
concentración de CO2. Esta evidencia hace necesaria 
una correcta ventilación de los espacios cerrados. 
Lo que es tan importante como mantener una distancia 
mínima.
```

Este proyecto parte de la aportación de Ernesto Gutiérrez [@erguro1973](https://twitter.com/erguro1973) y de los asistente a varios talleres realizados en el [Fablab de Mallorca](http://fablabmallorca.com/) y organizados por la [Asociación de Makers Mallorca](https://makespacemallorca.org/).

<img src="./img/removir_poster.png" width="400" align="right" />

**¿Con que vamos a trabajar?**
* Análisis de flujos de aire.
* Control de motores.
* Uso de filtros HEPA.
* Programación y uso de microcontroladores.

<br>
<br>
<br>
<img src="./img/IMG_9772.JPG" width="400" align="right" />

## Primer RemoVir, un _Mínimo Producto Viable_
Hemos trabajado sobre un Split marca ¿?. Que ha resultado muy adecuado tanto para la sustitución de la electrócnica como para acomodar los filtros HEPA. Aunque se trata de un MPV. pretendemos que alcance un nivel H13 o superior según el estándar europeo EN 1822-1:2009. Incorporaremos un completo sistemas de medición de calidad de aire, CO2, COV, temperatura, humedad y presión atmosférica de manera que sea capaz de adaptar su funcionamiento a las condiciones detectadas.

### Certificación
Como nos gusta saber si el trabajo está bien hecho, y sobre todo, si cumple su función. Una vez instalado mediremos los parámetros de operación como caudal de aire, reducción de COV, etc... para sacar conclusiones sobre mejoras en la siguiente iteracción.
<br>
Llegado el momento vamos a trabajar sobre la conocida hoja de excel de la Universidad de Hardvard que [tenéis aqui](https://github.com/Makespace-Mallorca/removir/blob/main/doc/Harvard-CU%20Boulder%20Portable%20Air%20Cleaner%20Calculator%20for%20Schools.v1.1.xlsx). Considerando esta plantilla se puede realizar el cálculo del CADR ( CLEAN AIR DELIVERY RATE) necesario del purificador, según el tamaño de la habitación, siendo este un parámetro que se indica en todos estos tipos de elementos. Como orientación, para una habitación media de 50m2 y un nivel de renovación bajo sería necesario al menos uno aparato con capacidad de 400 l/min.



