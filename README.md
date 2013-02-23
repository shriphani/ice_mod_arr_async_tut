ice_mod_arr_async_tut
=====================

Ice Sample App for Master/Slave combination where the Master maintains global state.

To compile:

     g++ -I. -I/path/to/ice/installation/include -c Assign.cpp Master.cpp
     g++ -I. -I/path/to/ice/installation/include -c Assign.cpp Slave.cpp
     g++ -o master Assign.o Master.o -L/path/to/ice/installation/lib -lIce -lIceUtil
     g++ -o slave Assign.o Slave.o -L/path/to/ice/installation/lib -lIce -lIceUtil

To run master:

        ./master

To spin up a bunch of slaves:

        for i in {1..5}; do ./slave $i > log_$i.txt &; done; 
