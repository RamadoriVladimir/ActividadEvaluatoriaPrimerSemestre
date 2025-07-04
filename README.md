# ActividadEvaluatoriaPrimerSemestre

Este proyecto es una aplicación de control de clima para un datacenter, implementada con un servidor HTTP en C++ (utilizando Crow), una interfaz web con HTML y JS, y un sistema de persistencia de datos basado en SQLite. Todo extendiendo la aplicacion de consola original del final de algoritmos 2, por lo que quedaron algunos tests usados en el desarrollo que ya no funcionan al recompilarlos. El uso del servidor proxy en Node.js, me fue importante para evitar errores de CORS.

La aplicación permite la monitorización y ajuste de la temperatura y humedad de un entorno de datacenter. Ofrece dos vías de interacción: un menú de consola para operaciones directas y una interfaz web intuitiva para un control remoto. Todos los cambios significativos en el clima del datacenter son registrados y persistidos, creando un historial de operaciones.

Para usarla es necesario compilar el servidor en c++ que se encarga del servidor HTTP y los verbos REST, ejecutarlo y en mi caso usar el servidor proxy con node para el funcionamiento de las peticiones http efectuadas desde el html.
