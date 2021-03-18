# Brihodakar Large Number System!!!
###### In the Name of Allah, the Most Gracious, the Most Merciful
## What is dis? :/
Brihodakar(বৃহদাকার - Gigantic) Large Number System is my first hobby project in programming, the first time I'm dealing with code that's larger than 100 lines. 

The Brihodakar Large Number System (from now on BLNS) implements basic operations such as addition and subtraction, which it then performs on specially constructed arrays called 'Brihodakar arrays'. Brihodakar arrays are data structures used to contain and display numbers of very large sizes. Brihodakar arrays only work with integers, but has no loss of precision regardless of the size of the integer! Take that, `long double`!

## Why are you making this?
- Good question. First of all, I'm a new programmer and I have no idea about the real world, so there's that. For me, BLNS was quite fun as it was something I wrote up entirely using what I knew and understood, so it was something I could relate to: I needed a challenge that was easy but stimulating, and yet not impossible and a nightmare to wrap my head around...

- Also, try adding 301974818932465466578913243242342347328941234 to 1823749701842756793485627934851. Too big for `unsigned long long int`? `long double` doesn't hold the entire answer? Yeah, I thought so...

- I firstly wanted to handle large numbers in C greater than `unsigned long long` but was disappointed to see that creating custom data types was easier said than done. So then I set out on a reasonably easy way to start using large numbers in C, but turns out that all the `bignum`(big number) libraries are very complex and difficult to start using, even for basic things like addition/subtraction and multiplication/division. So I set out on making a very simple one for myself. As I added more features, it ended up becoming a unique data type unlike others...

## Goals
I intended the following things when making it:
* **Not complicated.** It can become big of course, but shouldn't use things that I do not currently understand, such as `typedefs` and pointer arithmetic. I think expert/proficient C programmers who have spent years using C will cringe at some of the things I do (trust me, it was worse before...): However, you might have to keep those feelings to yourself. At my current level I only know all of the program control statements, very basic knowledge of data types and very basic use of some special quirky tools in C that I have no idea about, but managed to implement it because it was just too convenient to not use (like #define)
* **Easily extendable.** Only as a proof of concept I am currently limiting the size of the array to hold 100-digit numbers, but there's no reason why these principles can't work for larger digit numbers. Hence I expect BLNS to be easily extendable so that just by changing the constant I can work with 10-digit or 10000-digit numbers!
* **Bug-free.** This isn't really a complicated program, so I need to make sure BLNS works properly for ALL numbers. Since addition, subtraction, etc. all these operations are being implemented by the programmer(me! ^\_^ helo!), there is no guarantee that the correct answer is returned by the algorithm that I've invented. For now trial and error seems to show that my algorithm works, but there may be 1 or 2 wierd edge cases. I don't know how to guarantee that my algorithm that I've programmed works for all numbers, but I want to get closer and closer to that point.
I know there are other `bignum` libraries out there which contain more operators of complex types (sqrt, ln, e^ ), use larger numbers, and even in record time, but those libraries are so ridiculously complex that it is completely unusable to me and other newcomers to C. Hence, BLNS also attempts to be...
* **Easily Portable.** One of the good things about simple code is that it can be used very easily in other projects, and BLNS strives to achieve that level of ease. Using the entire BLNS is as simple as adding an `#include` and some `#define`s, and you can always copy and paste only the functions you need directly from the source files. 

## Soo.... How does the BLNS work?

#### Brihodakar arrays
> Basically, it is a string(terminated with 'A') of numbers, so there is no size limit to the number that it can hold except for the size of the array.
Very simple. Obviously I'm not the first person to come up with this, but I haven't really done/seen anything like this before. 

This is how a standard Brihodakar array should look like in memory:

            brihodakar[10] = [1 2 3 4 5 65 0 0 0 0]               (decimal/int view) (human-interpretable input/output format)
            brihodakar[10] = [A(nul)(nul)(nul)(nul)]         (char view)
            brihodakar[10] = [01 02 03 04 05 41 00 00 00 00]      (expected memory dump of relevant bits)

**Expected data:**  
* Integers 0 through 9 = digits
* 'A' = Terminating character
* 'S' = Terminating character implying negative character?? (not implemented yet, I need a way to define negative numbers tho).
**Unexpected data:** *ANYTHING ELSE!*

#### Storing a user-generated number into an array (stdin -> array)
A getche() loop cycles and takes in character inputs from the keyboard and stores numbers into the Brihodakar array PER DIGIT. (The 'char' data type is only really being used for smaller memory footprint)
Instead of storing the *characters* 0 through 9, we instead store the *numbers* 0 through 9, directly into the array, for easier calculation (imagine having to subtract `- '0'` all the time, eww).

#### Addition/Subtraction
Since I'm not some savant, I decided to implement addition and subtraction in *the way humans normally add and subtract numbers*. This means...
 1) When numbers are different sizes, addition is going to be utter chaos. We need to convert arrays to Big-Endian (basically significant digits at the very end, while still retaining the same order). If you think about it, this is basically how kindergartners add and subtract numbers
 2) Per digit addition/subtraction (this means implementing carrying, overflow, etc. manually)

This is what a Big-Endian array should look like and how two numbers get added, does this look familiar?:
```
             brihodakar1[15] = [0 0 0 0 0 0 0 0 1 2 3 4 5 6 A]
         +   brihodakar2[15] = [0 0 0 0 0 0 0 0 1 2 3 4 5 6 A]
 let's add those 2...       -----------------------------------
             brihodakar3[15] = [0 0 0 0 0 0 0 0 2 4 6 9 1 2 A]
```
Sadly this does mean that my code is heavily unoptimized and BLNS is slower/clunkier than other `bignum` libraries like [GMP](https://gmplib.org/) or [InfInt](https://sercantutar.github.io/infint/). But I'm content as I'm only a beginner who didn't know what `#include` meant 3 months ago.

#### Displaying the stored number
Displaying the array is also very simple. `printf("%d", brihodakar[array_index])` works as C does not distinguish between `char`s and `int`s, and allows one to be treated like the other. Now we can just generate a `for` loop and stuff that into a function! And that's how `display_num` was born...|

And that's how it was for quite a while. Until someone in a Programming Discord Server pointed out that `printf` format specifiers can slow a program down noticeably, being fine with 100-500 digit numbers, but

#### Array Management
If we try displaying that right now with our `display_num()` function, there's gonna be a lot of useless zeroes in the front, hence `array_management()` can convert Big-Endian Brihodakar arrays to Standard, and vice versa.

## What else?
Any other questions, be sure to let me know in Discord!
Found a bug? THANKS! Please open an issue! Or maybe let me know in Discord, that too!
Want to copy this code? NooOOooOoo, this is something I wrote up in less than 2 months after learning C, I'm sure you can figure this kid-stuff out by yourself if you really need it... (so I guess you *can* copy it...)

## Credits
As this is my first project, I'd like to mention something about me learning programming. Programming was notoriously difficult for me, even though I first started at the age of 7 or 8, trying off Visual Basic from a Video Tutorial and typing in Hello World in C from my sister's university books. The problem was not that I wasn't being able to solve problems, but rather that programming was something quite mundane and something in which I lacked rigor and understanding. 

Around this time, one of the earliest personal rolemodels I had was my own brother-in-law. He showed me how putting `return 10` instead of `return 0` could make the application output stop before exiting, and also showed me refactoring code in Scratch. I didn't really have anyone else around who was a programmer: I can't explain why, but I remember these moments quite fondly.

10 years down the line, I tried learning C# and Python only to stop halfway and get distracted by academic work. But amazingly, the very same university book that my sister was studying from 10 years ago was the one that I could finally concentrate on and get started. Using this book, within the span of a year I was for the first time able to feel as if I'd learnt something. I definitely haven't yet finished the book, but I was starting to get my small immature hands to grab one of the most important key skills required to code: to read, understand and apply logic.
