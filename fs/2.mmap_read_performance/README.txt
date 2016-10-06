# Description  

Firstly, we use mmap to read one file with 1024, 2048, 4096, 
and 5120 bytes for 1000000 times.
Then we read another file with 1024, 2048, 4096 and 5120 bytes
for 1000000 times too.

# Conclusion 

The performane of mmap read is worser than direct read.


