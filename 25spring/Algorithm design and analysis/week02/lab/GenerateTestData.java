//package week02.lab;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class GenerateTestData {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter n: ");
        int n = in.nextInt();
        in.close();

        String fileName = args[0]; // 直接赋值
        String[] boys = new String[n];
        String[] girls = new String[n];
        for (int i = 0; i < n; i++) {
            boys[i] = "m" + (i + 1);
            girls[i] = "w" + (i + 1);
        }

        // 打乱顺序
        List<String> shuffledBoys = Arrays.asList(boys.clone());
        List<String> shuffledGirls = Arrays.asList(girls.clone());
        Collections.shuffle(shuffledBoys);
        Collections.shuffle(shuffledGirls);

        try (PrintWriter writer = new PrintWriter(new FileWriter(fileName))) {
            writer.println(n);
            writer.println(String.join(" ", boys));
            writer.println(String.join(" ", girls));
            for (String boy : boys) {
                Collections.shuffle(shuffledGirls);
                writer.println(String.join(" ", shuffledGirls));
            }
            for (String girl : girls) {
                Collections.shuffle(shuffledBoys);
                writer.println(String.join(" ", shuffledBoys));
            }
            System.out.println("Test data generated in data.in");
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}
