package a1p1;

import java.io.*;
import java.util.*;

public class CS401_K142268_A1P1 {
//	private static final String FILENAME = "D:\\A1-in1.txt";
//	private static final String FILENAME = "D:\\A1-tc2.txt";
//	private static final String FILENAME = "D:\\A1-tc3.txt";
	private static final String FILENAME = "D:\\A1-tc4.txt";
//	private static final String FILENAME = "D:\\A1-tc5.txt";
//	private static final String FILENAME = "D:\\A1-tc6.txt";

	public static int m, n, init_x, init_y;
	static int final_x, final_y;
	public static void main(String args[]){
		File file = new File(FILENAME);
		try {

	        Scanner sc = new Scanner(file);
	        n = sc.nextInt();
	        m = sc.nextInt();
	        init_x = sc.nextInt();
	        init_y = sc.nextInt();
	        final_x = sc.nextInt();
	        final_y = sc.nextInt();

	        int i =0;
	        int j=0;
	        
	        int [][] maze = new int[n][m];
	        
	        while (sc.hasNext()) {
	        	if(j==m){
	        		j=0;
	        		i++;
	        	}
	            int num = sc.nextInt();
	            maze[i][j] = num;
	            j++;
	        }
	        sc.close();  
	        System.out.println(n+" "+m);
	        System.out.println(init_x+" "+init_y);
	        System.out.println(final_x+" "+final_y);
	        
	        for(i=0;i<n;i++){
	        	for(j=0;j<m;j++){
	        		System.out.print(maze[i][j]+" ");
	        	}
	        	System.out.println();
	        }

	        PrintStream out = new PrintStream(new FileOutputStream("output.txt"));
	        System.setOut(out);
	        
	        System.out.println(n+" "+m);
	        System.out.println(init_x+" "+init_y);
	        System.out.println(final_x+" "+final_y);
	        
	        for(i=0;i<n;i++){
	        	for(j=0;j<m;j++){
	        		System.out.print(maze[i][j]+" ");
	        	}
	        	System.out.println();
	        }
	    } 
	    catch (FileNotFoundException e) {
	        e.printStackTrace();
	    }	
	}
}