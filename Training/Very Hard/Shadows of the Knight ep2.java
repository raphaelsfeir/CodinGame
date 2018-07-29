import java.util.*;
import java.io.*;
import java.math.*;

class Player {
    static Zone chaud, froid, actuel;
    static int larg, haut;
    static int x, y;
    static int lastX, lastY;
    static boolean trouveX=false, firstChance=true, outside=false;
    static char bombDir = 'U';
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        larg = in.nextInt();
        haut = in.nextInt();
        init();
        int rounds = in.nextInt();
        x = in.nextInt();
        y = in.nextInt();
        while (true) {
            bombDir = in.next().charAt(0);
            move();
            System.out.println(x+" "+y);
        }
    }
    public static void init() {
        actuel = new Zone(0,larg-1);
        froid = new Zone(0,larg-1);
        chaud = new Zone(0,larg-1);
        x = y = lastX = lastY = 0;
    }
    public static void move() {
        int tmpX = x;
        int tmpY = y;
        switch (bombDir) {
            case 'W':
            actuel.update(chaud);
            break;
            case 'C':
            actuel.update(froid);
            break;
            case 'S':
            if (!firstChance) {if (!trouve()) return;}
            break;
        }
        if (actuel.low>=actuel.high) {if (!trouve()) return;}
        firstChance = false;
        if (trouveX) y = recup(y,haut-1);
        else x = recup(x,larg-1);
        lastX = tmpX;
        lastY = tmpY;
    }
    public static boolean trouve() {
        int tmpX = x;
        int tmpY = y;
        if (trouveX) y = (actuel.low+actuel.high)/2;
        else {
            x = (actuel.low+actuel.high)/2;
            trouveX = true;
            actuel.update(0,haut-1);
            chaud.update(actuel);
            froid.update(actuel);
        }
        firstChance = true;
        return (x==tmpX&&y==tmpY);
    }
    public static int recup(int val,int limite) {
        int low = actuel.low;
        int high = actuel.high;
        int give = low + high - val;
        if (outside) {
            if (val==0) {give = (give-0)/2;}
            else if (val==limite) {give = (limite+give)/2;}
        }
        outside = false;
        if (give==val) give=val+1;
        if (give<0) {give = 0; outside = true;}
        else if (give>limite) {give = limite; outside = true;}
        int middle = (give+val)/2;
        int lower = (give+val-1)/2;
        int higher = (give+val+1)/2;
        if (give>val) {
            chaud.update(higher,high);
            froid.update(low,lower);
        }
        else if (give<val) {
            chaud.update(low,lower);
            froid.update(higher,high);
        }
        return give;
    }
    public static class Zone {
        int low, high;
        public Zone(int low,int high) {
            this.low = low;
            this.high = high;
        }
        public void update(Zone z) {
            this.low = z.low;
            this.high = z.high;
        }
        public void update(int low,int high) {
            this.low = low;
            this.high = high;
        }
    }
}
