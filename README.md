# Convolutional encoder and Viterbi decoder

## Running: 
```
git clone git@github.com:xanderlifeftoahacked/yadro_testtask.git
cd yadro_testtask
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./main
```
### Dependencies:
* CMake
* GNUPlot
* Boost (GNUPlot dependency)

Note, that Cassini polynoms test may require some time (you can adjust parameters in `utils::test_codec` call `(main.cpp)`)

### Details:
Programm generates random bit-sequences, codes them, adds noise with different probability, then decodes them and compares with original ones. 

Encoder and Decoder classes support any generator polynomials (passed in parameters as vector of bools)

### Result: 
![image](https://github.com/user-attachments/assets/6105a232-4380-4c5a-bdb9-f134ac2501f2)
