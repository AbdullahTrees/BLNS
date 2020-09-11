# Brihodakar Large Number System!!!

## What is dis? :/
Brihodakar(বৃহদাকার) Large Number System is my first hobby project in programming, the first time I'm dealing with code that's larger than 100 lines. 

The Brihodakar Large Number System (from now on BLNS) implements basic operations such as addition and subtraction, which it then performs on specially constructed arrays called 'Brihodakar arrays'. Brihodakar arrays are data structures used to contain and display numbers of very large sizes.

## Why are you making this?
Good question. First of all, I'm a new programmer and I have no idea about the real world, so there's that. For me, BLNS was quite fun as it was something I wrote up entirely using what I knew and understood, so it was something I could relate to: I need a challenge that's easy and not impossible...

Also, try adding 301974818932465466578913243242342347328941234 to 1823749701842756793485627934851. Too big for unsigned long long int? Long double doesn't hold the entire answer? Yeah, I thought so...

## Goals
I intended the following things when making it:
* **Not complicated.** It can become big of course, but shouldn't use things that I do not currently understand, such as `typedefs` and pointer arithmetic. I think expert/proficient C programmers who have spent years using C will cringe at some of the things I do (trust me, it was worse before...): However, you might have to keep those feelings to yourself. At my current level I only know all of the program control statements, very basic knowledge of data types and very basic use of some special quirky tools in C that I have no idea about, but managed to implement it because it was just too convenient to not use (like #define)
* **Easily extendable.** Only as a proof of concept I am currently limiting the size of the array to hold 100-digit numbers, but there's no reason why these principles can't work for larger digit numbers. Hence I expect BLNS to be easily extendable so that just by changing the constant I can work with 10-digit or 10000-digit numbers!
* **Bug-free.** This isn't really a complicated program, so I need to make sure BLNS works properly for ALL numbers. Since addition, subtraction, etc. all these operations are being implemented by the programmer(me! ^\_^ helo!), there is no guarantee that the correct answer is returned by the algorithm that I've invented. For now trial and error seems to show that my algorithm works, but there may be 1 or 2 wierd edge cases. I don't know how to guarantee that my algorithm that I've programmed works for all numbers, but I want to get closer and closer to that point.

## Soo.... How does the BLNS work?

##### Brihodakar arrays
> Basically, it is a string(terminated with 'A') of numbers, so there is no size limit to the number that it can hold except for the size of the array.
Very simple. Obviously I'm not the first person to come up with this, but I haven't really done/seen anything like this before. 

This is how a standard Brihodakar array should look like in memory:

            brihodakar[10] = [1 2 3 4 5 65 0 0 0 0]               (decimal/int view) (human-interpretable input/output format)
            brihodakar[10] = [A(nul)(nul)(nul)(nul)]         (char view)
            brihodakar[10] = [01 02 03 04 05 41 00 00 00 00]      (expected memory dump of relevant bits)

Expected data:  
* Integers 0 through 9 = digits
* 'A' = Terminating character
* 'S' = Terminating character implying negative character?? (not implemented yet, I need a way to define negative numbers tho).
Unexpected data: *ANYTHING ELSE!*

##### Storing a user-generated number into an array (stdin -> array)
A getche() loop cycles and takes in character inputs from the keyboard and stores numbers into the Brihodakar array PER DIGIT. (The 'char' data type is only really being used for smaller memory footprint)
Instead of storing the *characters* 0 through 9, we instead store the *numbers* 0 through 9, directly into the array, for easier calculation (imagine having to subtract `- '0'` all the time, eww).

##### Addition/Subtraction
Since I'm not some savant, I decided to implement addition and subtraction in *the way humans normally add and subtract numbers*. This means...
 1) When numbers are different sizes, addition is going to be utter chaos. We need to convert arrays to Big-Endian (basically significant digits at the very end, while still retaining the same order). If you think about it, this is basically how kindergartners add and subtract numbers
 2) Per digit addition/subtraction (this means implementing carrying, overflow, etc. manually)

This is what a Big-Endian array should look like and how two numbers get added, does this look familiar?:
```
             brihodakar1[15] = [0 0 0 0 0 0 0 0 1 2 3 4 5 6 A]
         +   brihodakar2[15] = [0 0 0 0 0 0 0 0 1 2 3 4 5 6 A]
     let's add those 2...     ---------------------------------
             brihodakar3[15] = [0 0 0 0 0 0 0 0 2 4 6 9 1 2 A]
```

##### Displaying the stored number
Displaying the array is also very simple. `printf("%d", brihodakar[array_index])` works as C does not distinguish between `char`s and `int`s, and allows one to be treated like the other. Now we can just generate a `for` loop and stuff that into a function! And that's how `display_num` was born...


If we try displaying that right now with our `display_num()` function, there's gonna be a lot of useless zeroes in the front, hence array_management() can convert Big-Endian Brihodakar arrays to Standard, and vice versa.


    = The following things work and I'm pretty sure should be bug-free... Please still check them and comment, of course.
        display_num(); copy_array(); input_to_array();   // feel free to still check them out of course, humans can never guarantee anything
      The following things CURRENTLY DON'T WORK AND I HAVE NO IDEA WHY...
        add_array(); // this works when max_num_size = 100, but breaks and falls into an infinite loop when it's 105. Displays garbage in the arrays. Somehow it's getting corrupted

    = Any other questions, be sure to let me know in Discord!
