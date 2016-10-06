# Description  

Firstly, we use mmap to write one file with 1024, 2048, 4096, 
and 5120 bytes for 1000000 times.
Then we write another file with 1024, 2048, 4096 and 5120 bytes
for 1000000 times too.

# Conclusion 

The performane of mmap write is worser than direct write.


