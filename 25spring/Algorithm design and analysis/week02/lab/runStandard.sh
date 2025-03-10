#!/bin/bash
javac main.java
# Single test case
java GenerateTestData data.in
java main < data.in > output_standardOnly.out
