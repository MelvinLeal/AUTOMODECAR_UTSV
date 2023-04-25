# AUTOMODECAR_UTSV
En este repositorio se encuentra todo lo relacionado a la competencia TMR 2023 

## Requerimientos:

* Ubuntu 20.04
* ROS Noetic
* Webots 2022a: https://github.com/cyberbotics/webots/releases/download/R2022a/webots_2022a_amd64.deb

## Instalación:

Nota: se asume que ya se tiene instalado Ubuntu y ROS.

* Seguir las instrucciones para instalar Webots: https://cyberbotics.com/doc/guide/installing-webots
* Seguir el tutorial para el uso de Webots con ROS: https://cyberbotics.com/doc/guide/tutorial-9-using-ros
* $ cd
* $ git clone https://github.com/mnegretev/TMR-2023-AutoModelCar
* $ cd TMR-2023-AutoModelCar
* $ cd catkin_ws
* $ catkin_make -j2 -l2
* $ echo "source ~/TMR-2023-AutoModelCar/catkin_ws/devel/setup.bash" >> ~/.bashrc
* $ source ~/.bashrc

## Pruebas

Una vez instalado y compilado el repositorio, se pueden ejecutar los ambientes de simulación con los respectivos archivos 'launch':

* Navegación autónoma sin obstáculos: roslaunch tmr2023 navigation_no_obstacles.launch

## Tópicos relevantes

### Tópicos publicados:

* ``/camera/rgb/raw`` (sensor_msgs/Image): Imagen RGB de la cámara
* ``/point_cloud`` (sensor_msgs/PointCloud2): Nube de puntos generada por el Lidar

### Tópicos suscritos:

* ``/speed`` (std\_msgs/Float64): Velocidad lineal deseada en [km/h]
* ``/steering`` (std\_msgs/Float64): Ángulo de las llantas delanteras en [rad]

## Demo

Se puede ejecutar una demostración de navegación sin obstáculos con el comando
roslaunch demo demo.launch max_speed:=60

## contacto
maa19190211.mleal@alumnos.utsv.edu.mx
