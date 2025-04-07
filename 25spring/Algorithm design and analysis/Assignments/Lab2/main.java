package Assignments.Lab2;

import java.util.*;

public class main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int c = scanner.nextInt();
        int t = scanner.nextInt();

        if (t < 0) {
            t = 0;
        }

        int[] tuzi = new int[n];
        int[] nests = new int[m];

        for (int i = 0; i < n; i++) {
            tuzi[i] = scanner.nextInt();
        }
        for (int i = 0; i < m; i++) {
            nests[i] = scanner.nextInt();
        }

        Arrays.sort(tuzi);
        Arrays.sort(nests);

        int[] num = new int[m];
        int ans = 0;
        int startSearch = 0;

        for (int i = 0; i < n; i++) {
            int leftMost = tuzi[i] - t;
            int rightMost = tuzi[i] + t;

            for (int j = startSearch; j < m; j++) {
                if (nests[j] >= leftMost && nests[j] <= rightMost && num[j] < c) {
                    num[j]++;
                    if (num[j] >= c) {
                        startSearch++;
                    }
                    ans++;
                    break;
                } else {
                    startSearch++;
                }
            }
        }

        System.out.println(ans);
        scanner.close();
    }
}