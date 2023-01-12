

Multiple files

|file0|file1|file2|file3|...|fileN|


~~~
src/lrzip-next -vfUn -m 1 -R 9 -vv -N 19  -o compressionTest/aoe1.lrzip  compressionTest/aoe1.tar
LZ4 Threshold testing disabled due to Filtering and/or Compression type (gzip, lzo, rzip).
The following options are in effect for this COMPRESSION.
Threading is ENABLED. Number of CPUs detected: 2
Detected 104,857,600 bytes ram
Nice Value: 19
Show Progress
Max Verbose
Overwrite Files
Output Filename Specified: compressionTest/aoe1.lrzip
Temporary Directory set as: /tmp/
Compression mode is: RZIP pre-processing only. LZ4 Compressibility testing disabled
Compression level 7
RZIP Compression level 9
MD5 Hashing Used
Using Unlimited Window size
Storage time in seconds 1,386,967,204
Input file(s) size: 226,539,520
Succeeded in testing 34,951,168 sized mmap for rzip pre-processing
Compression window is larger than ram, will proceed with unlimited mode possibly much slower
Will take 1 pass
Chunk size: 226,539,520
Byte width: 4
Per Thread Memory Overhead is 0
Succeeded in testing 34,952,533 sized malloc for back end compression
Using only 1 thread to compress up to 34,955,264 bytes
Beginning rzip pre-processing phase
hashsize = 4,194,304.  bits = 22. 64MB
Total:  5%  Chunk:  5%
Starting sweep for mask 1
Total:  6%  Chunk:  6%
Starting sweep for mask 3
Total: 11%  Chunk: 11%
Starting sweep for mask 7
Total: 16%  Chunk: 16%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Writing initial chunk bytes value 4 at 20
Writing EOF flag as 1
Writing initial header at 26
Compthread 0 seeking to 22 to store length 4
Compthread 0 seeking to 26 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 39
Total: 21%  Chunk: 21%
Starting sweep for mask 15
Total: 32%  Chunk: 32%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Total: 33%  Chunk: 33%
Compthread 0 seeking to 35 to store length 4
Compthread 0 seeking to 34,955,303 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 34,955,316
Total: 40%  Chunk: 40%
Starting sweep for mask 31
Total: 47%  Chunk: 47%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Compthread 0 seeking to 34,955,312 to store length 4
Compthread 0 seeking to 69,910,580 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 69,910,593
Total: 64%  Chunk: 64%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Compthread 0 seeking to 69,910,589 to store length 4
Compthread 0 seeking to 104,865,857 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 104,865,870
Total: 80%  Chunk: 80%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Compthread 0 seeking to 104,865,866 to store length 4
Compthread 0 seeking to 139,821,134 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 139,821,147
Total: 84%  Chunk: 84%
Starting sweep for mask 63
Total: 98%  Chunk: 98%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Compthread 0 seeking to 139,821,143 to store length 4
Compthread 0 seeking to 174,776,411 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 174,776,424
Total: 99%  Chunk: 99%
2,796,202 total hashes -- 58,819 in primary bucket (2.104%)
Malloced 34,951,168 for checksum ckbuf
Starting thread 0 to compress 500,732 bytes from stream 0
Compthread 0 seeking to 9 to store length 4
Compthread 0 seeking to 209,731,688 to write header
Thread 0 writing 500,732 compressed bytes from stream 0
Compthread 0 writing data at 209,731,701
Starting thread 0 to compress 3,163,607 bytes from stream 1
Compthread 0 seeking to 174,776,420 to store length 4
Compthread 0 seeking to 210,232,433 to write header
Thread 0 writing 3,163,607 compressed bytes from stream 1
Compthread 0 writing data at 210,232,446
MD5: e97176711ad2241778e09ca55d8b0845

matches=50,116 match_bytes=13,644,329
literals=49,972 literal_bytes=212,895,191
true_tag_positives=1,084,729 false_tag_positives=37,653,653
inserts=11,201,611 match 0.064
(null) - Compression Ratio: 1.062. bpb: 7.536. Average Compression Speed:  0.303MB/s.
Total time: 00:11:52.64
~~~



~~~
src/lrzip-next -vfUn -m 1 -R 9 -vv -N 19  -o compressionTest/aoe1.lrzip  compressionTest/aoe1.tar
LZ4 Threshold testing disabled due to Filtering and/or Compression type (gzip, lzo, rzip).
The following options are in effect for this COMPRESSION.
Threading is ENABLED. Number of CPUs detected: 2
Detected 104,857,600 bytes ram
Nice Value: 19
Show Progress
Max Verbose
Overwrite Files
Output Filename Specified: compressionTest/aoe1.lrzip
Temporary Directory set as: /tmp/
Compression mode is: RZIP pre-processing only. LZ4 Compressibility testing disabled
Compression level 7
RZIP Compression level 9
MD5 Hashing Used
Using Unlimited Window size
Storage time in seconds 1,386,967,798
Input file(s) size: 226,539,520
Succeeded in testing 34,951,168 sized mmap for rzip pre-processing
Compression window is larger than ram, will proceed with unlimited mode possibly much slower
Will take 1 pass
Chunk size: 226,539,520
Byte width: 4
Per Thread Memory Overhead is 0
Succeeded in testing 34,952,533 sized malloc for back end compression
Using only 1 thread to compress up to 34,955,264 bytes
Beginning rzip pre-processing phase
hashsize = 4,194,304.  bits = 22. 64MB
Total:  5%  Chunk:  5%
Starting sweep for mask 1
Total:  6%  Chunk:  6%
Starting sweep for mask 3
Total: 11%  Chunk: 11%
Starting sweep for mask 7
Total: 16%  Chunk: 16%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Writing initial chunk bytes value 4 at 20
Writing EOF flag as 1
Writing initial header at 26
Compthread 0 seeking to 22 to store length 4
Compthread 0 seeking to 26 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 39
Total: 21%  Chunk: 21%
Starting sweep for mask 15
Total: 32%  Chunk: 32%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Total: 34%  Chunk: 34%
Compthread 0 seeking to 35 to store length 4
Compthread 0 seeking to 34,955,303 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 34,955,316
Total: 40%  Chunk: 40%
Starting sweep for mask 31
Total: 47%  Chunk: 47%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Compthread 0 seeking to 34,955,312 to store length 4
Compthread 0 seeking to 69,910,580 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 69,910,593
Total: 64%  Chunk: 64%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Compthread 0 seeking to 69,910,589 to store length 4
Compthread 0 seeking to 104,865,857 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 104,865,870
Total: 80%  Chunk: 80%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Compthread 0 seeking to 104,865,866 to store length 4
Compthread 0 seeking to 139,821,134 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 139,821,147
Total: 84%  Chunk: 84%
Starting sweep for mask 63
Total: 98%  Chunk: 98%
Starting thread 0 to compress 34,955,264 bytes from stream 1
Compthread 0 seeking to 139,821,143 to store length 4
Compthread 0 seeking to 174,776,411 to write header
Thread 0 writing 34,955,264 compressed bytes from stream 1
Compthread 0 writing data at 174,776,424
Total: 99%  Chunk: 99%
2,796,202 total hashes -- 58,819 in primary bucket (2.104%)
Malloced 34,951,168 for checksum ckbuf
Starting thread 0 to compress 500,732 bytes from stream 0
Compthread 0 seeking to 9 to store length 4
Compthread 0 seeking to 209,731,688 to write header
Thread 0 writing 500,732 compressed bytes from stream 0
Compthread 0 writing data at 209,731,701
Starting thread 0 to compress 3,163,607 bytes from stream 1
Compthread 0 seeking to 174,776,420 to store length 4
Compthread 0 seeking to 210,232,433 to write header
Thread 0 writing 3,163,607 compressed bytes from stream 1
Compthread 0 writing data at 210,232,446
MD5: e97176711ad2241778e09ca55d8b0845

matches=50,116 match_bytes=13,644,329
literals=49,972 literal_bytes=212,895,191
true_tag_positives=1,084,729 false_tag_positives=37,653,653
inserts=11,201,611 match 0.064
(null) - Compression Ratio: 1.062. bpb: 7.536. Average Compression Speed:  0.344MB/s.
Total time: 00:10:27.30
~~~



Original lrzip

~~~
lrzip -vfUn -m 1 -vv -N 19  -o compressionTest/aoe2.lrzip  compressionTest/aoe1.tar
The following options are in effect for this COMPRESSION.
Threading is ENABLED. Number of CPUs detected: 2
Detected 104857600 bytes ram
Compression level 7
Nice Value: 19
Show Progress
Max Verbose
Overwrite Files
Output Filename Specified: compressionTest/aoe2.lrzip
Temporary Directory set as: ./
Compression mode is: RZIP pre-processing only
Using Unlimited Window size
Storage time in seconds 1386967732
File size: 226539520
Enabling sliding mmap mode and using mmap of 34951168 bytes with window of 226539520 bytes
Succeeded in testing 34951168 sized mmap for rzip pre-processing
Compression window is larger than ram, will proceed with unlimited mode possibly much slower
Will take 1 pass
Chunk size: 226539520
Byte width: 4
Succeeded in testing 34952533 sized malloc for back end compression
Using only 1 thread to compress up to 34952533 bytes
Beginning rzip pre-processing phase
hashsize = 4194304.  bits = 22. 64MB
Starting sweep for mask 1
Starting sweep for mask 3
Starting sweep for mask 7
Sliding main buffer to offset 34951168
Starting thread 0 to compress 34952533 bytes from stream 1
Writing initial chunk bytes value 4 at 24
Writing EOF flag as 1
Writing initial header at 30
Compthread 0 seeking to 22 to store length 4
Compthread 0 seeking to 26 to write header
Thread 0 writing 34952533 compressed bytes from stream 1
Compthread 0 writing data at 39
Starting sweep for mask 15
Sliding main buffer to offset 69902336
Starting thread 0 to compress 34952533 bytes from stream 1
Compthread 0 seeking to 35 to store length 4
Compthread 0 seeking to 34952572 to write header
Thread 0 writing 34952533 compressed bytes from stream 1
Compthread 0 writing data at 34952585
Starting sweep for mask 31
Sliding main buffer to offset 104853504
Starting thread 0 to compress 34952533 bytes from stream 1
Compthread 0 seeking to 34952581 to store length 4
Compthread 0 seeking to 69905118 to write header
Thread 0 writing 34952533 compressed bytes from stream 1
Compthread 0 writing data at 69905131
Sliding main buffer to offset 139804672
Starting thread 0 to compress 34952533 bytes from stream 1
Compthread 0 seeking to 69905127 to store length 4
Compthread 0 seeking to 104857664 to write header
Thread 0 writing 34952533 compressed bytes from stream 1
Compthread 0 writing data at 104857677
Sliding main buffer to offset 174755840
Starting thread 0 to compress 34952533 bytes from stream 1
Starting sweep for mask 63
Compthread 0 seeking to 104857673 to store length 4
Compthread 0 seeking to 139810210 to write header
Thread 0 writing 34952533 compressed bytes from stream 1
Compthread 0 writing data at 139810223
Sliding main buffer to offset 209707008
Starting thread 0 to compress 34952533 bytes from stream 1
2796202 total hashes -- 59783 in primary bucket (2.138%)
Malloced 34951168 for checksum ckbuf
Compthread 0 seeking to 139810219 to store length 4
Compthread 0 seeking to 174762756 to write header
Thread 0 writing 34952533 compressed bytes from stream 1
Compthread 0 writing data at 174762769
Starting thread 0 to compress 488253 bytes from stream 0
Compthread 0 seeking to 9 to store length 4
Compthread 0 seeking to 209715302 to write header
Thread 0 writing 488253 compressed bytes from stream 0
Compthread 0 writing data at 209715315
Starting thread 0 to compress 3435965 bytes from stream 1
Compthread 0 seeking to 174762765 to store length 4
Compthread 0 seeking to 210203568 to write header
Thread 0 writing 3435965 compressed bytes from stream 1
Compthread 0 writing data at 210203581
MD5: e97176711ad2241778e09ca55d8b0845
matches=48842 match_bytes=13388357
literals=48785 literal_bytes=213151163
true_tag_positives=547213 false_tag_positives=7933137
inserts=11327277 match 0.063
compressionTest/aoe1.tar - Compression Ratio: 1.060. Average Compression Speed: 10.800MB/s.
Total time: 00:00:20.07

~~~


