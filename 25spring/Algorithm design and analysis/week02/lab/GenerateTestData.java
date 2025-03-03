package week02.lab;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

public class GenerateTestData {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(args[0]))) {
            Random random = new Random();
            // Generate random array size between 10 and 10000
            int n = random.nextInt(9991) + 10; // 10 ~ 10,000
            writer.write(n + "\n");
            // Generate random array elements
            for (int i = 0; i < n; i++) {
                writer.write(random.nextInt(10000) + " ");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
