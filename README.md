# 1337-42-ls
For each operand that names a file of a type other than directory, ls displays its name as well as any requested, associated information.  
For each operand that names a file of type directory, ls displays the names of files contained within that directory, as well as any requested, associated information.  
If no operands are given, the contents of the current directory are displayed.  
If more than one operand is given, non-directory operands are displayed first; directory and non-directory operands are sorted separately and in lexicographical order.

## The real ls options
ls [-ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1] [file ...]

## My ls options
ls [-1laRrt.] [file ...]  
>-1 : My default options, (The numeric digit ``one''.)  Force output to be one entry per line.  This is the default when output is not to a terminal.  

>-l : (The lowercase letter ``ell''.)  List in long format.  (See below.)  If the output is to a terminal, a total sum for all the file sizes is output on a line before the long listing.

>-a : Include directory entries whose names begin with a dot (.).

>-R : Recursively list subdirectories encountered.

>-r : Reverse the order of the sort to get reverse lexicographical order or the oldest entries first (or largest files last, if combined with sort by size

>-t : Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

[Fore more info about the project click here]()

## Video

## Bugs

There are memory leaks on my ft_ls, that time when I coded it, I didnt know there was a great tools like Valgrind that helps find where the memory leak is in your code.
