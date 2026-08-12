---
title: "VeloMetrics"
author: "Eric Huang"
description: "DIY bike computer made from scratch"
created_at: "7/1/26"
---

# July 1: Brainstormed UI layout 
I Sketched out initial concepts for the bike computer interface and what data to display and how to split it across screens.

Photos:
![alt text](<Screenshot 2026-07-04 131647.png>)

**Total time spent: 1h**


# July 5: Figured out how to get LVGL components on the LVGL simulator
Got the LVGL simulator running on desktop so I can prototype UI components without having to flash the ESP32 every time I change something. This is going to save a lot of iteration time later on.

Photos:
![alt text](<Screenshot 2026-07-04 133214.png>)
**Total time spent: 1h**



# July 10: Made a lot of different components & objects, made the simulator adaptable by flickering through screens and increasing values
Made a variety of components and objects for the interface. To make the simulator more useful for testing, I set it up to cycle through screens automatically and animate values so I can see how the UI behaves with changing data rather than static placeholders. It was offcenter so I will fix that later. Overall the UI is working as intended.

Photos:
![alt text](<Screenshot 2026-07-07 125859.png>)
![alt text](<Screenshot 2026-07-07 130757.png>)
**Total time spent: 2h**



# July 15: Wired Screen up to ESP32, got the UI flashing, Added platformio
Going into this project, I had quite a bit of Arduino experience. But I wondered, is it possible to start microcontroller projects without using the Arduino IDE? After doing some research, I figured out that you could use the platformio extension to run microcontrollers directly on VSCode. It was quite a difficult process to get platformio working however, as you had to define a lot of things that the Arduino IDE would otherwise do for you immediately. It look a lot of tinkering to get the code to work out the way it did, and to finally display on the screen. Before I figured it out it was flashing the same error code and trying to reset itself multiple times because it couldn't find the right upload connection. But after specifying the connection I wanted it to use in the platformio.ini file it finally displayed. This was the longest part of setting it up, the wiring was relatively easy. 

Photos:
![alt text](image.png)
**Total time spent: 2h**


# July 17: Changed some fonts up to make the UI look more appealing

Now that I got the UI to work on the screen, I decided to experiment with some fonts and colors to make the UI look less monotone. I decided to go with a futuristic kind of font that is still legible. Because I am using LVGL to display information on the LCD I have to convert the new fonts to a way LVGL can read. This was a rather tricky process because I have to individually download every font size and font and convert it to LVGL. There were also a lot of errors while using this new font, because I had to declare it in the ui.h folder as a c file, but vscode was reading it as a c++ file. Had to search up the problem and then fix it. Additionally, with my simulator, it was having all kind of errors because VS Studio couldnt access the stuff i was storing in the ui.h folder so I had to completely reinvent how I used the simulator. Instead of making static pointers that are only available in the ui.cpp folder i removed it and then extern it in the ui.h folder so it was universal and all folders could access it. This also made it easier to use the LVGL simulator because I didn't have to copy paste the code every time I changed it to the LVGL cpp file, I could just change the functions themsleves and have the simulator still work. 

Photos:
![alt text](image-6.png)
**Total time spent: 2h**


# July 23: Made the UI prettier

I thought the UI was pretty basic and there wasn't that much going on, it was just numbers. I decided to rewrite the UI to make it look cleaner and look like a actual bike computer UI. It looks pretty cool and slick now. Additionally I made the header section independent of each screen by putting it on the base screen, so now its not affected by the other screens PLUS i dont need to add a additional pointer to the header objects everytime i make a new screen. Also I realized that the font folder didn't include symbols like degrees and im too lazy to add a new one to include the degree symbol so I just removed it. Maybe in the future ill put it back.

Photos:
![alt text](image-5.png)
![alt text](image-4.png)
**Total time spent: 2h**

# July 25: Started testing and making the gps screen

I started with wiring up the gps module up to the rest of the components. I ran into some issues as the gps was not locking on to any sattlelites so i thought that i mightve been a wiring issue so i used a led to test my setup and it was correct. otherwise, I troubleshooted by making sure the platformio was locking onto the esp32 correctly off rip. The wiring wasn't the issue, I just had to wait for the gps a little. Took a decent while of troubleshooting by testing if my gps module was actually sending data to my esp32, where i used a byte test. It was, so I decided to wait and eventually it connected to my location. Will start testing irl next.

Photos:
![alt text](image-1.png)
![alt text](image-2.png)
![alt text](image-3.png)
**Total time spent: 2h**

# August 6: Started making the CAD enclosure

# August 7: Made a few design aspect decisions 

Sd card mechanisms, sliding shield to protect it when not in use, easy access and storage