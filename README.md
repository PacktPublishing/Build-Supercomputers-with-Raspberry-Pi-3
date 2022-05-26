## [Get this title for $10 on Packt's Spring Sale](https://www.packt.com/B06901?utm_source=github&utm_medium=packt-github-repo&utm_campaign=spring_10_dollar_2022)
-----
For a limited period, all eBooks and Videos are only $10. All the practical content you need \- by developers, for developers

# Build Supercomputers with Raspberry Pi 3
This is the code repository for [Build Supercomputers with Raspberry Pi 3](https://www.packtpub.com/hardware-and-creative/build-supercomputers-raspberry-pi-3?utm_source=github&utm_medium=repository&utm_content=978-1-78728-258-2), published by Packt. It contains all the supporting project files necessary to work through the book from start to finish.

## About the Book
This book's mission is to effectively instruct anyone, with basic computer hardware and software skills, on how to construct an affordable Pi3 supercomputer. If you are looking at performing high-level computation with microchips, then this book is for you.

## Instructions and Navigation
All of the code is organized into folders. The commands and instructions will look like the following:

    #include <math.h> // math library
    #include <stdio.h>// Standard Input / Output library

    int main(void)
    {
      long num_rects = 300000;//1000000000;
      long i;
      double x,height,width,area;
      double sum;
      width = 1.0/(double)num_rects; // width of a segment
    
      sum = 0;
    for(i = 0; i < num_rects; i++)
    {
     x = (i+0.5) * width; // x: distance to center of i(th) segment
     height = 4/(1.0 + x*x);
     sum += height; // sum of individual segment heights
    }

    // approximate area of segment (Pi value) 
       area = width * sum;

     printf("\n");
     printf(" Calculated Pi = %.16f\n", area);
     printf("          M_PI = %.16f\n", M_PI);
     printf("Relative error = %.16f\n", fabs(area - M_PI));

     return 0;
    }



## Related products:
* [Building Smart Homes with Raspberry Pi Zero](https://www.packtpub.com/hardware-and-creative/building-smart-homes-raspberry-pi-zero?utm_source=github&utm_medium=repository&utm_content=9781786466952)
* [Getting Started with Raspberry Pi Zero](https://www.packtpub.com/hardware-and-creative/getting-started-raspberry-pi-zero?utm_source=github&utm_medium=repository&utm_content=9781786469465)
* [Raspberry Pi Home Automation with Arduino - Second Edition](https://www.packtpub.com/hardware-and-creative/raspberry-pi-home-automation-arduino-second-edition?utm_source=github&utm_medium=repository&utm_content=9781784399207)

### Suggestions and Feedback
[Click here](https://docs.google.com/forms/d/e/1FAIpQLSe5qwunkGf6PUvzPirPDtuy1Du5Rlzew23UBp2S-P3wB-GcwQ/viewform) if you have any feedback or suggestions. 
