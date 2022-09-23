# Bubble-Trouble-Game 

## CS101 Course Project

>This course was offered in the first semister of my Undergraduate Program at **IIT Bombay** to teach us the fundamentals of **Computer Science** through **C++**


## Dowload Project
To get the project files simply clone the following repository using
```
git clone https://github.com/23-ryan/Bubble-Trouble-Game
```
Or you can also just download it from [here](https://github.com/23-ryan/Bubble-Trouble-Game/tree/main/src).

## Project Details
Checkout this smaple [vedio](https://drive.google.com/file/d/1B2NvzijTvISc9HEp8fQIVN_S_LTWHFmC/view?usp=drivesdk)


<p align="center">
    <img width="500" height="300" src="https://github.com/23-ryan/Bubble-Trouble-Game/blob/main/Gifs/game1.gif">
</p>


- ### Basic Description
    >This is a simple game made through **C++** using a special library **_Simple Cpp_** which allows us to use **GUI** using **C++** code. The main goal of this projets was to let us well accquianted with the basic functionalities of **C++** Language, a better understanding of **objects** and **classes** and also to get a hands on experience with a somewhat large code. 


<p align="center">
    <img width="500" height="300" src="https://github.com/23-ryan/Bubble-Trouble-Game/blob/main/Gifs/game2.gif">
</p>


- ### Specific Details
    - The basic objects it contains are **Shooter**, **Bullets**, **Bubbles**. Some other elements are **Timer**, **Score** and **Life**.
    - **Collisions** were introduced among the objects according to basic properties.
    - **Bubbles** move in a **parabolic** trajectory.
    - Whenever a bubble hits the shooter its **body color** gets changed and its **life** decreases by one.
    - Bullets disappear when they hits any bubble.
    - **Score counter** also updates accordingly, when any bullet make a successful hit with a bubble
    - Timer has also been added and set to a reasonable frame rate.
    - The game could end in these ways:
        - When the player gets devoid of **time**.
        - When the **life** of shooter ends
        - When you make all the bubbles disappear.
    
### NOTE
The library is just a simple graphic library and its for beginners to give its users a good experience of programming.
So the **graphics** rendering is not very good, also there are noticable fluctuations in the **frame rate**.

