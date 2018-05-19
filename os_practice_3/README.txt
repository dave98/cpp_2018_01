Este programa fue compilado en Cygwin, basta la ejecución del <<make>>.
SO: windows 8.1

Condiciones de Ejecución para windows.

1: Habilitar Cygserver dentro de Cygwin. Es probable que se necesiten algunas librerías que se pueden obtener del instalador del Cygwin.
  Link https://superuser.com/questions/738105/how-to-install-cygserver
  Dejar el Cygserver por defecto. Una vez habilitado, Cygserver se mantendrá activo hasta que se desactive directamente desde consola.
2: Cerrar la consola en donde se habilitó el Cygserver.
3: Abrir cinco consolaS del Cygwin en modo administrador.
  # Hacer clic en el icono del Cygwin y seleccionar "Ejecutar como Administrador"
4: En la primera ventana ejecutar "make file" y después "make". Esto compilará automaticamente el código y generará cinco ejecutables en el directorio principal.
5: Asignar cada ejecutable a cada ventana del Cygwin de la siguiente manera:
  -> Primera ventana : "./signal.exe"
  -> Segunda Ventana : "./writer.exe"
  -> Tercera Ventana : "./reader.exe"
  -> Cuarta Ventana : "./sh_reader.exe"
  -> Quinta Ventana : "./queue.exe"
6: Ejecutar las ventanas asignadas en el mismo orden.
  # Los programas estarán en espera hasta que se inserten los datos necesarios en el programa que envía las señales.
7: En el único programa en donde se insertan los datos es el que envía las señales (Primera ventana). Se solicitará el ID del proceso objetivo y la cantidad de señales a enviar.
8: Escribir el ID que se muestra en la segunda ventana en espera.
9: Escribir el número de señales a enviar.
10: Presionar "ENTER". La ventana que envía las señales comenzará su ejecución activando el resto de las ventanas.

# En la primera ventana en ejecución se muestra el número de señales enviadas. Finalizadas, el programa acabará con su ejecución.
# En la segunda ventana se muestra el número de señales recibidas.
# La tercerá ventana lee los números en el <<pipe>>. Después los clasifica y los envía al <<share memory>> o al <<queue>>. Esta ventana muestra la cantidad de datos recbidos, el número recibido y el lugar a donde se va a enviar.

# Insertar demasiadas señales puede decaer en un desborde en el share memory.
