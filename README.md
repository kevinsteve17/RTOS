# Sistemas Operativos en Tiempo Real
# Proyecto 1 - The Scheduler

## Integrantes
- Fernando Paris
- Esteban Rivera
- Kevin Viquez

## GIT
- https://github.com/kevinsteve17/RTOS.git

## Procedimiento
1. Extraer folder
2. El folder comprimido contiene los siguientes folder:

- Proyecto 1
- Proyecto 1/CppApplication_1
- Proyecto 1/CppApplication_1/nbproject
- Proyecto 1/CppApplication_1/nbproject/private
- Proyecto 1/Documentation

3. Para compilar el proyecto, se debe de ejecutar el comando `make` desde el folder `Proyecto 1/CppApplication_1`. Despues de compilar y vincular el programa se crearan 2 folders:

- Proyecto 1/CppApplication_1/build
- Proyecto 1/CppApplication_1/dist/Debug/GNU-Linux

4. El ejecutable se encontrara en el folder:
- Proyecto 1/CppApplication_1/dist/Debug/GNU-Linux

5. Antes de ejecutarlo es necesario copiar el archivo de configuration al folder del ejecutable, este archivo se encuentra en:
- Proyecto 1/CppApplication_1/SchedulerSettings

6. Para ejecutar el binario se usa el comando `./cppapplication_1`

7. Una vez corriendo el programa, presionar el boton `Start` del GUI

8. Cuando la aplicacion termine de ejecutar los procesos, presionar el boton de X en la esquina superior de la ventana para cerrarla

9. Se pueden modificar los parametros del archivo de configuracion para diferentes pruebas. La unica restriccion para los casos de Lottery Scheduling, es que la cantidad de tiquetes del sistema debe ser igual a la sumatoria de las prioridades de los procesos.
