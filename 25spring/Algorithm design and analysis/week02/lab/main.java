//package week02.lab;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

public class main {
    public static void main(String[] args) {
        long startTime = System.currentTimeMillis(); // Record start time
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        HashMap<String, Node> boysMap = new HashMap<>();
        HashMap<String, Node> girlsMap = new HashMap<>();
        Queue<Node> freeBoys = new LinkedList<>();
        Node[] boys = new Node[n];
        for (int i = 0; i < n; i++) {
            String name = in.next();
            boys[i] = new Node(name, n);
            boysMap.put(name, boys[i]);
            freeBoys.add(boys[i]);
        }
        Node[] girls = new Node[n];
        for (int i = 0; i < n; i++) {
            String name = in.next();
            girls[i] = new Node(name, n);
            girlsMap.put(name, girls[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                String name = in.next();
                boys[i].likes[j] = girlsMap.get(name);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                String name = in.next();
                girls[i].likes[j] = boysMap.get(name);
                girls[i].rankMap.put(name, j);
            }
        }
        while (!freeBoys.isEmpty()) {
            Node boy = freeBoys.poll();
            for (Node girl : boy.likes) {
                if (girl.ifFree) {
                    boy.date(girl);
                    break;
                } else {
                    if (!prefer(girl, boy)) {
                        freeBoys.add(girl.date);
                        boy.date(girl);
                        break;
                    }
                }
            }
        }
        for (Node boy : boys) {
            System.out.print(boy.name + " " + boy.date.name + " ");
        }

        long endTime = System.currentTimeMillis();
        long elapsedTime = endTime - startTime;
        System.out.println();
        System.out.println("Time taken: " + elapsedTime + " milliseconds");
        in.close();
    }

    static boolean prefer(Node girl, Node comBoy) {
        return girl.rankMap.get(girl.date.name) < girl.rankMap.get(comBoy.name);
    }

    static boolean allDated(Node[] nodes) {
        for (Node node : nodes) {
            if (node.ifFree) {
                return false;
            }
        }
        return true;
    }
}

class Node {
    String name;
    boolean ifFree;
    Node date;
    Node[] likes;
    Map<String, Integer> rankMap;

    public Node(String name, int n) {
        this.name = name;
        this.ifFree = true;
        this.likes = new Node[n];
        this.date = null;
        this.rankMap = new HashMap<>();
    }

    public void date(Node lover) {
        // 双方都清空
        if (lover.date != null) {
            lover.date.ifFree = true;
            lover.date.date = null;
        }
        // 前任被删
        if (this.date != null) {
            Node ex = this.date;
            ex.ifFree = true;
            ex.date = null;
        }
        // 现任上位
        this.date = lover;
        this.ifFree = false;
        lover.date = this;
        lover.ifFree = false;
    }
}
