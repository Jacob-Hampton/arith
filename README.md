# arith
This is a C project I completed with my partner, Ethan Oliver, in our Machine Structure and Assembly Programming class.

The project uses bitpacking to compress or decompress an image. Below is the README submitted with the project.

_____________________________________________________________________________

Claire Boals and Ethan Oliver
Comp40 hw4: Arith
10/20/18

Help we received:
Comp40 TA's, StackOverflow, Noah Mendelsohn

Implementation:
We believe that everything has been correctly implemented in our program.

Architecture:
Our solution consists of 9 modules. The 40image module handles command line 
input, and the Compress40 module calls the compression and decompression 
functions, depending on the user’s choice. Our compression module performs 
the necessary math (not including quantizations) on the individual pixels to 
put them into 2x2 blocks, and it interacts with the Quantizer to prepare the 
information for packing. It interacts with Wordpack to actually put the 
information into codewords. Decompress is similar. It performs necessary math 
other than quantizations on the compressed image, and it interacts with 
Quantizer and Wordpack to unquantize and extract the information from the 
codewords. Wordpack interacts with Bitpack to take information and call correct
Bitpack functions. Quantizer is a module which contains all the necessary math 
equations needed to quantize the information in compression and decompression 
of images. Bitpack handles all the bitwise operations needed to create the 
codewords and is only used by Wordpack. The compressed and decompressed image 
read/write modules simply handle the interactions between files and images as 
they are represented in our solution. 

How many hours spent:
Analyzing - 20 hours
Solving - 20 hours
