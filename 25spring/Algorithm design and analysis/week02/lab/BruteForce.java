//package week02.lab;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

public class BruteForce {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        String[] boys = new String[n];
        HashMap<String, Integer> boyIndex = new HashMap<>();
        String[] girls = new String[n];
        HashMap<String, Integer> girlIndex = new HashMap<>();
        for (int i = 0; i < boys.length; i++) {
            String name = in.next();
            boys[i] = name;
            boyIndex.put(name, i);
        }
        for (int i = 0; i < girls.length; i++) {
            String name = in.next();
            girls[i] = name;
            girlIndex.put(name, i);
        }
        int[][] boyPre = new int[n][n];
        for (int i = 0; i < boyPre.length; i++) {
            for (int j = 0; j < boyPre[0].length; j++) {
                boyPre[i][j] = girlIndex.get(in.next());
            }
        }
        int[][] girlPre = new int[n][n];
        for (int i = 0; i < girlPre.length; i++) {
            for (int j = 0; j < girlPre[0].length; j++) {
                girlPre[i][j] = boyIndex.get(in.next());
            }
        }
        // System.out.println(Arrays.toString(boys));
        // System.out.println(Arrays.toString(girls));
        // System.out.println(Arrays.deepToString(boyPre));
        // System.out.println(Arrays.deepToString(girlPre));
        int[] match = new int[n];
        for (int i = 0; i < n; i++)
            match[i] = i;
        genPermutations(match, 0, n, boyPre, girlPre, boys, girls);
        in.close();
    }

    static void genPermutations(int[] match, int start, int n, int[][] boyPre, int[][] girlPre, String[] boys,
            String[] girls) {
        if (start == n) {
            if (checkStability(n, match, boyPre, girlPre))
                printMatching(match, boys, girls);
            return;
        }
        for (int i = start; i < n; i++) {
            swap(match, start, i);
            genPermutations(match, start + 1, n, boyPre, girlPre, boys, girls);
            swap(match, start, i);
        }
    }

    static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    static boolean checkStability(int n, int[] match, int[][] boyPre, int[][] girlPre) {
        int[] girlToBoy = new int[n]; // girlToBoy[i] 表示女生 i 当前的匹配对象
        for (int i = 0; i < n; i++) {
            girlToBoy[match[i]] = i; // match[b] 表示男生 b 配对的女生
        }

        for (int b = 0; b < n; b++) { // 遍历所有男生
            int currentGirl = match[b]; // 男生 b 当前的匹配对象
            for (int j = 0; j < n; j++) { // 遍历男生 b 的偏好列表
                int preferredGirl = boyPre[b][j]; // 男生更喜欢的女生
                if (preferredGirl == currentGirl)
                    break; // 遇到了当前匹配者，停止检查
                int preferredGirlMatch = girlToBoy[preferredGirl]; // 该女生目前的匹配对象
                // 检查女生是否更喜欢 b 而不是她的当前匹配者
                for (int k = 0; k < n; k++) {
                    if (girlPre[preferredGirl][k] == b)
                        return false; // 女生也更喜欢这个男生，匹配不稳定
                    if (girlPre[preferredGirl][k] == preferredGirlMatch)
                        break; // 女生更喜欢当前配对，继续
                }
            }
        }
        return true;
    }

    static void printMatching(int[] match, String[] boys, String[] girls) {
        for (int i = 0; i < match.length; i++) {
            System.out.print(boys[i] + " " + girls[match[i]] + " ");
        }
        System.out.println();
    }
}
