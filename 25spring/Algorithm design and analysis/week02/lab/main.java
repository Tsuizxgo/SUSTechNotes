package week02.lab;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        HashMap<String, Node> boysMap = new HashMap<>();
        HashMap<String, Node> girlsMap = new HashMap<>();
        Node[] boys = new Node[n];
        for (int i = 0; i < n; i++) {
            String name = in.next();
            boys[i] = new Node(name, n);
            boysMap.put(name, boys[i]);
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
            }
        }
        HashMap<String, String> ans = new HashMap<>();
        // for (Node node : boys) {
        // System.out.print(node.name + " " + Arrays.toString(node.likes));
        // }
        // System.out.println();
        // for (Node node : girls) {
        // System.out.print(node.name + " " + Arrays.toString(node.likes));
        // }
        while (!allDated(boys)) {
            for (Node boy : boys) {
                if (boy.ifFree) {
                    for (Node girl : boy.likes) {
                        if (girl.ifFree) {
                            ans.remove(boy.name);
                            boy.date(girl);
                            ans.put(boy.name, girl.name);
                            break;
                        } else {
                            if (prefer(girl, boy)) {
                                continue;
                            } else {
                                ans.remove(girl.date.name);
                                girl.date(boy);
                                ans.put(boy.name, girl.name);
                                break;
                            }
                        }
                    }
                }
            }
        }
        for (Map.Entry<String, String> entry : ans.entrySet()) {
            System.out.println(entry.getKey() + " " + entry.getValue());
        }
    }

    static boolean prefer(Node girl, Node comBoy) {
        Node now = girl.date;
        int nowIndex = 0;
        int comIndex = 0;
        for (int i = 0; i < girl.likes.length; i++) {
            if (now.name == girl.likes[i].name)
                nowIndex = i;
            if (comBoy.name == girl.likes[i].name)
                comIndex = i;
        }
        if (nowIndex < comIndex) {
            // 原配赢
            return true;
        } else
            return false; // 新来的boy赢
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

    public Node(String name, int n) {
        this.name = name;
        this.ifFree = true;
        this.likes = new Node[n];
        this.date = null;
    }

    public void date(Node lover) {
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
