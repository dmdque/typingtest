typingtest
==========
![Screenshot 1](img/screenshot-1.png)

You can watch a video demo [here](https://www.youtube.com/watch?v=8xy7ie34lR8).

### Compiling and Running
Run `make` to compile. You may need to install xorg-dev (`sudo apt-get install xorg-dev`). If it doesn't work, run:
> g++ main.cc -o tt.out

Once compiled, run:
> ./tt.out

You will then be prompted for an input file. Enter a text file (eg. `input.txt`) to begin. Highscores are saved in `<file>.hs`.

### Options
-f \<file\>  
&nbsp;&nbsp;&nbsp; Use the given \<file\> as the input file.

-r  
&nbsp;&nbsp;&nbsp; Randomize the order of the lines in the input file.

-d  
&nbsp;&nbsp;&nbsp; Turn on debugging.

-l \<limit\>  
&nbsp;&nbsp;&nbsp; Limit the number of lines read in to \<limit\>.

