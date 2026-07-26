---
title: "VeloMetrics"
author: "Eric Huang"
description: "DIY bike computer made from scratch"
created_at: "7/1/26"
---

# July 1: Brainstormed UI layout 


**Total time spent: 1h**


# July 5: Figured out how to get LVGL components on the LVGL simulator

**Total time spent: 1h**



# July 10: Made a lot of different components & objects, made the simulator adaptable by flickering through screens and increasing values

**Total time spent: 2h**



# July 15: Wired Screen up to ESP32, got the UI flashing, Added platformio
Going into this project, I had quite a bit of Arduino experience. But I wondered, is it possible to start microcontroller projects without using the Arduino IDE? After doing some research, I figured out that you could use the platformio extension to run microcontrollers directly on VSCode. It was quite a difficult process to get platformio working however, as you had to define a lot of things that the Arduino IDE would otherwise do for you immediately. It look a lot of tinkering to get the code to work out the way it did, and to finally display on the screen. Before I figured it out it was flashing the same error code and trying to reset itself multiple times because it couldn't find the right connection. But after specifying the connection I wanted it to use in the platformio.ini file it all worked out at the end and finally displayed. This was the longest part of setting it up, the wiring was relatively easy. 

Photos:
![alt text](image.png)
**Total time spent: 2h**


# July 17: Changed some fonts up to make the UI look more appealing

Now that I got the UI to work on the screen, I'm not worried about that anymore. I decided to experiment with some fonts and colors to make the UI look less monotone. I decided to go with a futuristic kind of font that is still legible. Because I am using LVGL to display information on the LCD I have to convert the new fonts to a way LVGL can read. This was a rather tricky process because I have to individually download every font size and font and convert it to LVGL. There were also a lot of errors while using this new font, because I had to declare it in the ui.h folder as a c file, but vscode was reading it as a c++ file. Had to search up the problem and then fix it. Additionally, with my simulator, it was having all kind of errors because VS Studio couldnt access the stuff i was storing in the ui.h folder so I had to completely reinvent how I used the simulator. Instead of making static pointers that are only available in the ui.cpp folder i removed it and then extern it in the ui.h folder so it was universal and all folders could access it. This also made it easier to use the LVGL simulator because I didn't have to copy paste the code every time I changed it to the LVGL cpp file, I could just change the functions themsleves and have the simulator still work. 

**Total time spent: 2.5h**


# July 23: Made the UI prettier

I thought the UI was pretty basic and there wasn't that much going on, it was just numbers. I decided to rewrite the UI to make it look cleaner and look like a actual bike computer UI. It looks pretty cool and slick now. Additionally I made the header section independent of each screen by putting it on the base screen, so now its not affected by the other screens PLUS i dont need to add a additional pointer to the header objects everytime i make a new scren.

**Total time spent: 2h**

# July 25: Started testing and making the gps screen

I start with wiring up the gps module up to the rest of the components. I ran into some issues as the gps was not locking on to any sattlelites so i thought that i mightve been a wiring issue so i used a led to test my setup and it was correct. 