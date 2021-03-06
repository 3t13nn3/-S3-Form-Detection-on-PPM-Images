# -S3-Form-Detection-on-PPM-Images

A second University year project made with C and [OpenGL utility toolkit](https://www.opengl.org/resources/libraries/glut/) about detection of forms on ppm P6 images format.

This project aims to isolate forms on an image step by step. We can select the step we want.

There are steps we can select in the application:
  * Original Image
  * High Contrast Pixels
  * High Contrast Connex Pixels
  * Aligned Pixels
  * Forms

If you are a french speaker, I invite you to check the [Report of this project](https://github.com/3t13nn3/-S3-Form-Detection-on-PPM-Images/blob/master/Rapport/RAPPORT.pdf) for more details.

## Prerequisites

- [OpenGL](https://www.opengl.org/) & [OpenGL utility toolkit](https://www.opengl.org/resources/libraries/glut/) installed
- An image with the ```.ppm (p6)``` extension if you won't use mine

## How to use - *Linux Project*

### Compilation

Compile the program with ```make```.

### Utilisation

Lauch the binary as ```./Exe Media/myPicture.ppm``` and wait until the image appear.

Click on the image and you will be able to select the feature you want.

### Clean files

Clean object files and binary by ```make clean```.

## Exemple of Execution

Here is some picture that illustrate execution:

- ***Original Image (by default)***
![Original Image (by default)](https://github.com/3t13nn3/-S3-Form-Detection-on-PPM-Images/blob/master/Screen/1.png)

- ***High Contrast Pixels***
![High Contrast Pixels](https://github.com/3t13nn3/-S3-Form-Detection-on-PPM-Images/blob/master/Screen/2.png)

- ***High Contrast Connex Pixels***
![High Contrast Connex Pixels](https://github.com/3t13nn3/-S3-Form-Detection-on-PPM-Images/blob/master/Screen/3.png)

- ***Aligned Pixels***
![Aligned Pixels](https://github.com/3t13nn3/-S3-Form-Detection-on-PPM-Images/blob/master/Screen/4.png)

- ***Forms***
![Forms](https://github.com/3t13nn3/-S3-Form-Detection-on-PPM-Images/blob/master/Screen/5.png)


## Author

* **Etienne PENAULT** - *Programmation Impérative II* - Paris VIII
