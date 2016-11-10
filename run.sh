#!/usr/bin/env bash

#TO COMPILE and RUN on MAC OSX
if [ "$(uname)" == "Darwin" ]; then
  clang++ -std=c++11 -stdlib=libc++ ./src/Graph.cpp ./src/AdjacencyList.cpp ./src/CSVhandler.cpp ./src/DigitalWallet.cpp -o digitalWallet
  ./digitalWallet ./paymo_input/batch_payment.txt ./paymo_input/stream_payment.txt ./paymo_output/output1.txt ./paymo_output/output2.txt ./paymo_output/output3.txt

#TO COMPILE and RUN on LINUX
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
   g++ -std=c++0x ./src/Graph.cpp ./src/AdjacencyList.cpp ./src/CSVhandler.cpp ./src/DigitalWallet.cpp  -o digitalWallet -Wall -g
   ./digitalWallet ./paymo_input/batch_payment.txt ./paymo_input/stream_payment.txt ./paymo_output/output1.txt ./paymo_output/output2.txt ./paymo_output/output3.txt

#TO COMPILE and RUN on WINDOWS
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
   echo "Honestly, didn't try compiling under Windows!"

fi
