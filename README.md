## What is this?

This repository contains the code, data, and analysis for a project I had to complete for my CS 3341 class (Foundations of Modern Computing) my Junior year at SMU. The project itself is a multithreaded job system that allows for multiple threads and jobs to be completed at once via multiple cores running simultaneously. There is a step by step analysis I was required to complete for my class called "Analysis.pdf" which describes the pros and cons of specific parts of the code as well as a detailed description of what it does. 


## What did it teach me?

By completing this project I successfully managed to learn three major things:

    1. I learned how to manage multithreading and how to utilize multiple cores.
    2. I learned how to utilize memory control and understood the necessity behind halting specific tasks in order to protect the data that may be required from another task. I also learned the pros and cons of different synchronization mechanisms as well as how to use them.
    3. I learned how to automatically compile code and run commands in the command line using a pipe. This also allows me to automatically run a job which will compile only specific files without needing to recompile the entire project. I can also use the command line and jobs through the JobSystem to automate anything I could do through the command line.


## How is this useful?

Almost all modern computers have multiple cores in them, so the idea of using a single core to do all the work of a specific program may seem ridiculous and you may ask, well why would anyone do it this way? That would be a wonderful question, and most of the time, it is simply because people do not know how or don't want to commit the time to creating the JobSystem and specific jobs. It is a much more difficult process than just using one core, so on small projects, it saves time by not needing to debug, manage memory, or write code. Even still though, on some large projects, people may choose to refrain from multiprocessing, this is because of the complexity that the program brings. If any memory is poorly managed or there are any impropper synchronization mechanisms being used, it could lead to data corruption, hence leading some people to decide to stay away from it if working with sensitive data. However, overall, having a proper JobSystem in most modern projects will only improve the functionality and runtime of the program without causing any major looming cons apart from more overhead, complexity, and error potential.