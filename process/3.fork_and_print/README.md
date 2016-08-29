# Description 

The parent printfs string "Hello,", then forks one child, then printf "I'm parent\n".
And the child printf "I'm child\n".

How about the output?

# Answer

Hello, I'm parent
Hello, I'm child
or
Hello, I'm child
Hello, I'm parent

# Conclusion
Because the printf uses the line buffer by default, so the "Hello," is not printed acutally
when parent forks child. Then the line buffer is inherited by child. 

So the child also could print "Hello, " likes its parent.




