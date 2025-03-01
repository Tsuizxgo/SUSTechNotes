package p3;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        permutation(s);
        in.close();
    }

    static void permutation(String s) {
        List<String> ans = new ArrayList<>();
        puermute(s.toCharArray(), 0, ans);
        System.out.println(ans.toString());
    }

    static void swap(char[] chars, int i, int j) {
        char temp = chars[i];
        chars[i] = chars[j];
        chars[j] = temp;
    }

    static void puermute(char[] chars, int index, List<String> ans) {
        if (index == chars.length) {
            ans.add(new String(chars));
        }
        for (int i = index; i < chars.length; i++) {
            swap(chars, index, i);
            System.out.println(Arrays.toString(chars));
            puermute(chars, index + 1, ans);
            System.out.println(Arrays.toString(chars));
            swap(chars, index, i);
        }
    }
}
