Our application uses OpenCV to work. To Install OpenCV folllowing the steps mentioned in the links

https://medium.com/@pokhrelsuruchi/setting-up-opencv-for-python-and-c-in-ubuntu-20-04-6b0331e37437

https://google.github.io/mediapipe/getting_started/install.html#installing-on-debian-and-ubuntu

Next we need g++ to run .cpp programs, to install

sudo apt-get install g++

open the zip file.

move to the unzipped folder and run the following code to compile the code.

g++ -std=c++11 -o run main.cpp `pkg-config --cflags --libs opencv`

./run

// The images are placed in images folder.
Enter the image name as been asked.

 Next the Algorithm and we will get the desired output

  Note: if installing OpenCV has't done correctly the program might not execute.


  From this link you it in virtual box by importing it.

  login with pid: "kappa"

  and move to porject folder and open terminal there

  Enter the following commands to run the program

  g++ -std=c++11 -o run main.cpp `pkg-config --cflags --libs opencv`

./run
    
