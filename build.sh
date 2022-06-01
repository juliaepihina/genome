echo 'Building meter...'
cd meter
g++ main.cpp -o meter
cp meter ../bin

echo 'Building tester...'
cd ../tester
g++ *.cpp -o tester
cp tester ../bin

echo 'Building solver...'
cd ../solver
g++ *.cpp -o solver
cp solver ../bin
cd ..

echo 'Building algorithm #2'
cd GenomeAssembly
g++ --std=c++14 -O  -c src/main.cpp -o build/main.o
g++ --std=c++14 -O  -c src/DeBruijnGraph.cpp -o build/DeBruijnGraph.o
g++ --std=c++14 -O  -c src/KMerifier.cpp -o build/KMerifier.o
g++ --std=c++14 -O  -o build/GA.exe build/main.o build/DeBruijnGraph.o build/KMerifier.o
cp build/GA.exe ../bin
chmod +x ../bin/GA.exe
cd ..
