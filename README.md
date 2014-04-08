typingtest
==========
Run `make` to compile. If it doesn't work, run:
> g++ main.cc

Once compiled, run:
> ./tt.out

You will then be prompted for an input file. Enter a text file (eg. `input.txt`) to begin. Highscores are saved in `\<input\>.hs`.

### Options
-f \<file\>  
&nbsp;&nbsp;&nbsp; Use the given \<file\> as the input file.

-r  
&nbsp;&nbsp;&nbsp; Randomize the order of the lines in the input file.

-d  
&nbsp;&nbsp;&nbsp; Turn on debugging.

-l \<limit\> 
&nbsp;&nbsp;&nbsp; Limit the number of lines read in to \<limit\>.
