# sha-bench
Benchmarking linux kernel sha1 implementations

How to run
----------

make && ./test

Results
-------

 Intel(R) Xeon(R) CPU E5-2680 v3 @ 2.50GHz

    Implementation: native
     Result: 127472272531951331940158434155305718461562518521000000000000000000000000000
     Time elapsed: 0.217409 for 1000000 rounds
    Implementation: ssse3
     Result: 127472272531951331940158434155305718461562518521000000000000000000000000000
     Time elapsed: 0.113001 for 1000000 rounds
    Implementation: avx
     Result: 127472272531951331940158434155305718461562518521000000000000000000000000000
     Time elapsed: 0.106489 for 1000000 rounds
    Implementation: avx2
     Result: 127472272531951331940158434155305718461562518521000000000000000000000000000
     Time elapsed: 0.118119 for 1000000 rounds
    Implementation: ni
    unsupported
