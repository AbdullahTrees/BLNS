# Brihodakar Large Number System!!!

Information

    Basically, it is a string(terminated with 'A') of numbers, so there is no size limit to the number that it can hold except for the size of the array.
    = I intended the following things when making it:   1) Not complicated (it can become big of course, but shouldn't use things that I do not currently understand, such as typedefs and pointer arithmetic
                                                        2) Easily extendable. For only a proof of concept I am currently limiting the size of the array to hold 100-digit numbers, but there's no reason why these principles can't work for larger digit numbers. Hence I expect BLNS to be easily extendable so that just by changing the constant I can work with 10-digit or 10000-digit numbers.
                                                        3) Bug-free. This isn't really a complicated program, so I need to make sure BLNS works properly for ALL numbers. Since addition, subtraction, etc. all these operations are being implemented by the programmer(me!), there is no guarantee that the correct answer is returned by the algorithm that I've invented. For now trial and error seems to show that my algorithm works, but there may be 1 or 2 wierd edge cases. Idk how to guarantee that my algorithm that I've programmed works for all numbers, but I want to get to that point.

    = Why are you making this?
    Good question. First of all, I'm a new programmer and have no idea about the real-world, so there's that. I need a challenge that's easy and not impossible
    Also, try adding 301974818932465466578913243242342347328941234 to 1823749701842756793485627934851. Too big for unsigned long long int? Long double doesn't hold the entire answer? Yeah, I thought so...

    = Soo.... How does the BLNS work?
    Very simple. This is how a standard Brihodakar array should look like in memory:
            brihodakar[10] = [1 2 3 4 5 65 0 0 0 0]  (decimal/int view) (human-interpretable input/output format)
            brihodakar[10] = [A(nul)(nul)(nul)(nul)]  (char view)
            brihodakar[10] = [01 02 03 04 05 41 00 00 00 00]   (expected memory dump of relevant bits)

        Expected data:  Integers 0 through 9 = digits
                        'A' = Terminating character
                        'S' = Terminating character implying negative character?? (not implemented yet, I need a way to define negative numbers tho).

        Unexpected data: ANYTHING ELSE!

    = Oh, since I'm not some savant, I decided to implement addition and subtraction in the way humans normally add numbers. This means...
        1) When numbers are different sizes, addition is going to be utter chaos. We need to convert arrays to Big-Endian (basically significant digits at the very end, while still retaining the same order)
        2) Per digit addition (this means implementing carrying, overflow, etc. manually, so...

        This is what a Big-Endian array should look like:
                brihodakar1[15] = [0 0 0 0 0 0 0 0 1 2 3 4 5 6 A]
                brihodakar2[15] = [0 0 0 0 0 0 0 0 1 2 3 4 5 6 A]
        lets add those 2...
                brihodakar3[15] = [0 0 0 0 0 0 0 0 2 4 6 9 1 2 A]

        If we try displaying that right now with our display_num() function, there's gonna be a lot of useless zeroes in the front, hence array_management() can convert Big-Endian Brihodakar arrays to Standard, and vice versa.

    = A getche() loop cycles and takes in character inputs from the keyboard and stores numbers into the Brihodakar array PER DIGIT. The 'char' data type is only really being used for smaller memory footprint,
        Instead of storing the characters 0 through 9, we instead store the numbers 0 through 9, directly into the array, for easier calculation(imagine having to subtract - '0' all the time, eww).
        Displaying the array is also very simple. printf("%d", brihodakar[number]) works as C does not distinguish between chars and ints, and allows one to be treated like the other.

    = The following things work and I'm pretty sure should be bug-free... Please still check them and comment, of course.
        display_num(); copy_array(); input_to_array();   // feel free to still check them out of course, humans can never guarantee anything
      The following things CURRENTLY DON'T WORK AND I HAVE NO IDEA WHY...
        add_array(); // this works when max_num_size = 100, but breaks and falls into an infinite loop when it's 105. Displays garbage in the arrays. Somehow it's getting corrupted

    = Any other questions, be sure to let me know in Discord!
