#!/bin/bash
javac GenerateTestData.java
javac BruteForce.java
javac main.java
# Single test case
java GenerateTestData data.in
java BruteForce < data.in > output_custom.out
java main < data.in > output_standard.out

if grep -Fx -f "output_standard.out" "output_custom.out" > /dev/null; then
echo "Test Passed"
else
echo "Test Failed"
fi
# Batch testing (5 cases)
for i in {1..5}; do
java GenerateTestData "data_$i.in"
java BruteForce < "data_$i.in" > "output_custom_$i.out"
java main < "data_$i.in" > "output_standard_$i.out"


if grep -Fx -f "output_custom_$i.out" "output_standard_$i.out" > /dev/null; then
	echo "Case $i: Passed"
else
	echo "Case $i: Failed"
fi
done
