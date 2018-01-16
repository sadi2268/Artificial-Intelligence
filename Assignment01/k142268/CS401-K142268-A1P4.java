package a1p1;
import java.io.*;
import java.util.*;

class Node {	
	public State location;
	public Node parent;
	public int path_cost;
	
	Node(State state){
		this.location=state;
		this.parent=null;
		this.path_cost=0;
	}
	Node(State state, Node parent){
		this.location= state;
		this.parent=parent;
		this.path_cost = parent.path_cost+1;
	}
}
class State {
	int x;
	int y;
	
	State(int x, int y){
		this.x=x;
		this.y=y;
	}
}

public class CS401_K142268_A1P4 {
//	private static final String FILENAME = "D:\\A1-tc1.txt";
//	private static final String FILENAME = "D:\\A1-tc2.txt";
//	private static final String FILENAME = "D:\\A1-tc3.txt";
//	private static final String FILENAME = "D:\\A1-tc4.txt";
//	private static final String FILENAME = "D:\\A1-tc5.txt";
	private static final String FILENAME = "D:\\A1-tc6.txt";

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
	        PrintStream out = new PrintStream(new FileOutputStream("output.txt"));
	        System.setOut(out);
	        iterativeDeepening(maze);
	    } 
	    catch (FileNotFoundException e) {
	        e.printStackTrace();
	    }	
	}
	public static void iterativeDeepening(int[][] matrix){
		for (int depth=0; depth<m*n;depth++){
			int [][] myInt = new int[matrix.length][];
			for(int i = 0; i < matrix.length; i++)
			    myInt[i] = matrix[i].clone();
			boolean pathExistDepthLimited = depthLimited(myInt,depth );
			if(pathExistDepthLimited)
				break;
			/*
			System.out.print(depth);
	        System.out.println(pathExistDepthLimited? "YES" : "NO" );
	        */
		}
	}
	
	public static boolean depthLimited(int[][] matrix, int depth){
		int[][] new_matrix = matrix;
		List<Node> frontier =new ArrayList<Node>();
	        frontier.add(new Node(new State(init_x,init_y)));
	        boolean pathExists = false;
	        while(!frontier.isEmpty()){
	        	Node current = frontier.remove(frontier.size()-1);
	        	if(current.location.x==final_x && current.location.y==final_y && new_matrix[current.location.x][current.location.y]==0){
	        		pathExists = true;
	        		if(pathExists){
	        			printPath(current);
	                }
	        		break;
	        	}
	        	else if(current.path_cost>=depth){
	        		pathExists=false;
	        		break;
	        	}
	        	new_matrix[current.location.x][current.location.y]=1;
	        	List<Node> neighbours = getNeighbours(frontier, new_matrix, current);
	        	frontier.addAll(neighbours);
	        }       
	        return pathExists;
	}
	public static void printPath(Node current){
		List<Node> path = new ArrayList<Node>();
		while(current!=null){
			path.add(current);
			current=current.parent;
		}
		int total_cost = path.size();
		while(path.size()>0){
			Node step = path.remove(path.size()-1);
			System.out.println(step.location.x+" "+step.location.y);
		}
		System.out.println(total_cost);
	}

    public static boolean isPresent(List<Node> my_list, int a, int b){
    	int size = my_list.size();
    	for(Node iter : my_list){
    		if(iter.location.x==a && iter.location.y==b){
    			return true;
    		}
    	}
    	return false;
    }
    
    public static List<Node> getNeighbours(List<Node> my_list, int[][]matrix, Node node){
    	List<Node> children = new ArrayList<Node>();
    	//Up
        if(isValidPoint(matrix, node.location.x-1, node.location.y)) {
        	if(!isPresent(my_list, node.location.x-1, node.location.y)){
        	children.add(new Node(new State(node.location.x-1, node.location.y),node));
        	}
        }
        //Down
        if(isValidPoint(matrix, node.location.x+1, node.location.y)) {
        	if(!isPresent(my_list,node.location.x+1, node.location.y)){
            children.add(new Node(new State(node.location.x+1, node.location.y),node));
        	}
        }
        //Right
        if(isValidPoint(matrix, node.location.x, node.location.y+1)) {
        	if(!isPresent(my_list, node.location.x, node.location.y+1)){
            children.add(new Node(new State(node.location.x, node.location.y+1),node));
        	}
        }
        //Left
        if(isValidPoint(matrix, node.location.x, node.location.y-1)) {
        	if(!isPresent(my_list, node.location.x, node.location.y-1)){
            children.add(new Node(new State(node.location.x, node.location.y-1),node));
        	}
        }
        //LeftUp
        if(isValidPoint(matrix, node.location.x-1, node.location.y - 1)) {
        	if(!isPresent(my_list, node.location.x-1, node.location.y - 1)){
            children.add(new Node(new State(node.location.x-1, node.location.y - 1),node));
        	}
        }
        //LeftDown
        if(isValidPoint(matrix, node.location.x+1, node.location.y - 1)) {
        	if(!isPresent(my_list,node.location.x+1, node.location.y - 1)){
            children.add(new Node(new State(node.location.x+1, node.location.y - 1),node));
        	}
        }
        //RightUp
        if(isValidPoint(matrix, node.location.x-1, node.location.y +1)) {
        	if(!isPresent(my_list,node.location.x-1, node.location.y +1)){
            children.add(new Node(new State(node.location.x-1, node.location.y +1),node));
        	}
        }
        //RightDown
        if(isValidPoint(matrix, node.location.x+1, node.location.y + 1)) {
        	if(!isPresent(my_list, node.location.x+1, node.location.y + 1)){
            children.add(new Node(new State(node.location.x+1, node.location.y + 1),node));
        	}
        }
        return children;
    }
    public static boolean isValidPoint(int[][] matrix, int x, int y) {
        return !(x < 0 || x >= n || y < 0 || y >= m) && (matrix[x][y] != 1);
    }
}